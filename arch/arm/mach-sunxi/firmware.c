/*
 * Copyright (C) 2012 Samsung Electronics.
 * huangshr<huangshr@allwinnertech.com>
 *
 * This program is free software,you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/firmware.h>
#include <linux/secure/te_protocol.h>
#include <mach/hardware.h>
#include <mach/sunxi-smc.h>
#include "./pm/mem_hwspinlock.h"

uint32_t sunxi_do_smc(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
	struct smc_param param;
	
	param.a0 = arg0;
	param.a1 = arg1;
	param.a2 = arg2;
	param.a3 = arg3;
	sunxi_smc_call(&param);
	
	return param.a0;
}

static u32 sunxi_sec_read_reg(void __iomem *reg)
{
	u32 value;
	u32 phys_addr;

	phys_addr = (u32)reg > (u32)IO_ADDRESS(0) ? ((u32)reg - (u32)IO_ADDRESS(0)) : (u32)reg;

	value = sunxi_do_smc(TEE_SMC_PLAFORM_OPERATION, TE_SMC_READ_REG,phys_addr, 0);
	return value;
}

static u32 sunxi_sec_write_reg(u32 value, void __iomem *reg)
{
	u32 ret;
	u32 phys_addr;

	phys_addr = (u32)reg > (u32)IO_ADDRESS(0) ? ((u32)reg - (u32)IO_ADDRESS(0)) : (u32)reg;

	ret = sunxi_do_smc(TEE_SMC_PLAFORM_OPERATION, TE_SMC_WRITE_REG, phys_addr, value);
	return ret;
}

static u32 sunxi_sec_send_command(u32 arg0, u32 arg1, u32 arg2, u32 arg3)
{
	u32 ret;
	ret = sunxi_do_smc(arg0, arg1, arg2, arg3);
	return ret;
}

static u32 sunxi_load_arisc(void *image, u32 image_size, void *para, u32 para_size, u32 para_offset)
{
	u32 ret;
	struct tee_load_arisc_param *param;
	
	if ((image == NULL) || (image_size == 0) || 
	    (para == NULL) || (para_size == 0)) {
		return -EINVAL;
	}
	
	/* allocte param buffer */
	param = kzalloc(sizeof(struct tee_load_arisc_param), GFP_KERNEL);
	if (param == NULL) {
		pr_err("%s: allocate param buffer failed\n", __func__);
		return -ENOMEM;
	}

	/* initialize params */
	if ((u32)image > (u32)IO_ADDRESS(0)) {
		/* sram memory */
		param->image_phys = (u32)image - (u32)IO_ADDRESS(0);
	} else {
		/* dram memory */
		param->image_phys = (u32)virt_to_phys(image);
	}
	param->image_size = image_size;
	if ((u32)para > (u32)IO_ADDRESS(0)) {
		/* sram memory */
		param->para_phys = (u32)para - (u32)IO_ADDRESS(0);
	} else {
		/* dram memory */
		param->para_phys = (u32)virt_to_phys(para);
	}
	param->para_size   = para_size;
	param->para_offset = para_offset;
	
	/* do smc call */
	ret = sunxi_do_smc(TEE_SMC_PLAFORM_OPERATION, TE_SMC_LOAD_ARISC, 
	                    (u32)virt_to_phys(param), 0);
	
	kfree(param);
	
	return ret;
}

static u32 sunxi_sec_set_secondary_entry(void *entry)
{
	u32 ret;
	
	ret = sunxi_do_smc(TEE_SMC_PLAFORM_OPERATION, TE_SMC_SET_SMP_BOOTENTRY, (u32)entry, 0);
	
	return ret;
}

static u32 sunxi_sec_suspend(void)
{
	u32 ret;
	ret = sunxi_do_smc(TEE_SMC_PM_SUSPEND, 0, 0, 0);
	return ret;
}

/*
 * note: the function main to get monitor vector to save for resume
 */
static u32 sunxi_sec_suspend_prepare(void)
{
	u32 ret;
	ret = sunxi_do_smc(TEE_SMC_PLAFORM_OPERATION, TE_SMC_SUSPEND_PAREPER, 0, 0);
	return ret;
}

/* brief
 * arg0: command type as TEE_SMC_PLAFORM_OPERATION
 * arg1: set standby status mode.(clear or get or set)
 * arg2: standby reg physical address.
 * arg3: value to set when set.
 */
static u32 sunxi_sec_set_standby_status(u32 command_type, u32 setting_type, u32 addr, u32 val)
{
	u32 ret_val = 0;
	u32 phys_addr;

	phys_addr = (u32)addr > (u32)IO_ADDRESS(0) ? ((u32)addr - (u32)IO_ADDRESS(0)) : (u32)addr;
	switch(setting_type){
		case TE_SMC_STANDBY_STATUS_CLEAR:
			ret_val = sunxi_do_smc(TEE_SMC_PLAFORM_OPERATION, TE_SMC_READ_REG, phys_addr, 0);
			if (!hwspin_lock_timeout(MEM_RTC_REG_HWSPINLOCK, 20000)) {
				ret_val = sunxi_do_smc(TEE_SMC_PLAFORM_OPERATION, TE_SMC_STANDBY_STATUS_CLEAR, phys_addr, ret_val);
				hwspin_unlock(MEM_RTC_REG_HWSPINLOCK);
			}
			break;
		case TE_SMC_STANDBY_STATUS_SET:
			if (!hwspin_lock_timeout(MEM_RTC_REG_HWSPINLOCK, 20000)) {
				ret_val = sunxi_do_smc(TEE_SMC_PLAFORM_OPERATION, TE_SMC_STANDBY_STATUS_SET, phys_addr, val);
				hwspin_unlock(MEM_RTC_REG_HWSPINLOCK);
			}
			asm volatile ("dsb");
			asm volatile ("isb");

			break;
		case TE_SMC_STANDBY_STATUS_GET:
			if (!hwspin_lock_timeout(MEM_RTC_REG_HWSPINLOCK, 20000)) {
				ret_val = sunxi_do_smc(TEE_SMC_PLAFORM_OPERATION, TE_SMC_STANDBY_STATUS_GET, phys_addr, val);
				hwspin_unlock(MEM_RTC_REG_HWSPINLOCK);
			}
			break;
		default:
			break;
	}

	return ret_val;
}

static const struct firmware_ops sunxi_firmware_ops = {
	.read_reg	     = sunxi_sec_read_reg,
	.write_reg	     = sunxi_sec_write_reg,
	.send_command	     = sunxi_sec_send_command,
	.load_arisc          = sunxi_load_arisc,
	.set_secondary_entry = sunxi_sec_set_secondary_entry,
	.suspend_prepare     = sunxi_sec_suspend_prepare,
	.suspend             = sunxi_sec_suspend,
	.set_standby_status  = sunxi_sec_set_standby_status,
};

void __init sunxi_firmware_init(void)
{
	register_firmware_ops(&sunxi_firmware_ops);
}
