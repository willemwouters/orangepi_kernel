/*
 * Copyright (C) 2013 Allwinnertech, kevin.z.m <kevin@allwinnertech.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Adjustable factor-based clock implementation
 */

#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/clk-private.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/module.h>
#include "clk-sunxi.h"
#include "clk-periph.h"
#define NEW_RATE_CALULATE 1

static u8 sunxi_clk_periph_get_parent(struct clk_hw *hw)
{
    u8 parent;
    unsigned long reg, flags = 0;
    struct sunxi_clk_periph *periph = to_clk_periph(hw);

    if(!periph->mux.reg)
        return 0;
    if(periph->lock)
    {
        spin_lock_irqsave(periph->lock, flags);
        reg = periph_readl(periph,periph->mux.reg);
        parent = GET_BITS(periph->mux.shift, periph->mux.width, reg);
        spin_unlock_irqrestore(periph->lock, flags);
    }
    else
    {
        reg = periph_readl(periph,periph->mux.reg);
        parent = GET_BITS(periph->mux.shift, periph->mux.width, reg); 
    }
    return parent;
}


static int sunxi_clk_periph_set_parent(struct clk_hw *hw, u8 index)
{
    unsigned long reg, flags = 0;
    struct sunxi_clk_periph *periph = to_clk_periph(hw);

    if(periph->flags & CLK_READONLY)
        return 0;
		
    if(!periph->mux.reg)
        return 0;
    if(periph->lock)
    {
        spin_lock_irqsave(periph->lock, flags);
        reg = periph_readl(periph,periph->mux.reg);
        reg = SET_BITS(periph->mux.shift, periph->mux.width, reg, index);
        periph_writel(periph,reg, periph->mux.reg);
        spin_unlock_irqrestore(periph->lock, flags);
    }
    else
    {
        reg = periph_readl(periph,periph->mux.reg);
        reg = SET_BITS(periph->mux.shift, periph->mux.width, reg, index);
        periph_writel(periph,reg, periph->mux.reg);
    }
    return 0;
}

static int __sunxi_clk_periph_enable_shared(struct sunxi_clk_periph *periph)
{
    unsigned long reg;
    struct sunxi_clk_periph_gate *gate = &periph->gate;
    if(!periph->com_gate)
        return -1;        

    if(!periph->com_gate->val)
    {
        /* de-assert module */
        if(gate->reset && !(periph->flags & CLK_IGNORE_AUTORESET) && IS_SHARE_RST_GATE(periph)) {
            reg = periph_readl(periph,gate->reset);
            reg = SET_BITS(gate->rst_shift, 1, reg, 1);
            periph_writel(periph,reg, gate->reset);
        }
        /* enable bus gating */
        if(gate->bus && IS_SHARE_BUS_GATE(periph)) {
            reg = periph_readl(periph,gate->bus);
            reg = SET_BITS(gate->bus_shift, 1, reg, 1);
            periph_writel(periph,reg, gate->bus);
        }

        /* enable module gating */
        if(gate->enable&& IS_SHARE_MOD_GATE(periph)) {
            reg = periph_readl(periph,gate->enable);
            reg = SET_BITS(gate->enb_shift, 1, reg, 1);
            periph_writel(periph,reg, gate->enable);
        }

        /* enable dram gating */
        if(gate->dram&& IS_SHARE_MBUS_GATE(periph)) {
            reg = periph_readl(periph,gate->dram);
            reg = SET_BITS(gate->ddr_shift, 1, reg, 1);
            periph_writel(periph,reg, gate->dram);
        }       
    }
    periph->com_gate->val |= 1 << periph->com_gate_off;

    return 0;
}
static int sunxi_clk_periph_enable_shared(struct sunxi_clk_periph *periph)
{
    unsigned long flags = 0;
    int ret = 0;
    if(!periph->com_gate)
        return -1;        
    if(periph->lock)
    {
        spin_lock_irqsave(periph->lock, flags);
        ret = __sunxi_clk_periph_enable_shared(periph);
        spin_unlock_irqrestore(periph->lock, flags);
    }
    else
        ret = __sunxi_clk_periph_enable_shared(periph);
    return ret;        
}
static int __sunxi_clk_periph_enable(struct clk_hw *hw)
{
    unsigned long reg;
    struct sunxi_clk_periph *periph = to_clk_periph(hw);
    struct sunxi_clk_periph_gate *gate = &periph->gate;

    /* de-assert module */
    if(gate->reset && !(periph->flags & CLK_IGNORE_AUTORESET) && !IS_SHARE_RST_GATE(periph)) {
        reg = periph_readl(periph,gate->reset);
        reg = SET_BITS(gate->rst_shift, 1, reg, 1);
        periph_writel(periph,reg, gate->reset);
    }

    /* enable bus gating */
    if(gate->bus && !IS_SHARE_BUS_GATE(periph)) {
        reg = periph_readl(periph,gate->bus);
        reg = SET_BITS(gate->bus_shift, 1, reg, 1);
        periph_writel(periph,reg, gate->bus);
    }

    /* enable module gating */
    if(gate->enable&& !IS_SHARE_MOD_GATE(periph)) {
        reg = periph_readl(periph,gate->enable);
        if(periph->flags & CLK_REVERT_ENABLE)
            reg = SET_BITS(gate->enb_shift, 1, reg, 0);
        else
            reg = SET_BITS(gate->enb_shift, 1, reg, 1);
        periph_writel(periph,reg, gate->enable);
    }

    /* enable dram gating */
    if(gate->dram&& !IS_SHARE_MBUS_GATE(periph)) {
        reg = periph_readl(periph,gate->dram);
        reg = SET_BITS(gate->ddr_shift, 1, reg, 1);
        periph_writel(periph,reg, gate->dram);
    }

    return 0;
}
static int sunxi_clk_periph_enable(struct clk_hw *hw)
{
    unsigned long flags = 0;
    int ret = 0;
    struct sunxi_clk_periph *periph = to_clk_periph(hw);

    if(periph->flags & CLK_READONLY)
        return 0;
		
    if(periph->com_gate)
        sunxi_clk_periph_enable_shared(periph);

    if(periph->lock)
    {
        spin_lock_irqsave(periph->lock, flags);
        ret = __sunxi_clk_periph_enable(hw);
        spin_unlock_irqrestore(periph->lock, flags);        
    }
    else
        ret = __sunxi_clk_periph_enable(hw);  
        
    return ret;
}
static int __sunxi_clk_periph_is_enabled(struct clk_hw *hw)
{
    int state = 1;
    unsigned long reg;
    struct sunxi_clk_periph *periph = to_clk_periph(hw);
    struct sunxi_clk_periph_gate *gate = &periph->gate;

    /* enable bus gating */
    if(gate->bus) {
        reg = periph_readl(periph,gate->bus);
        state &= GET_BITS(gate->bus_shift, 1, reg);
    }

    /* enable module gating */
    if(gate->enable) {
        reg = periph_readl(periph,gate->enable);
        state &= GET_BITS(gate->enb_shift, 1, reg);
    }
    /* de-assert module */
    if(gate->reset) {
        reg = periph_readl(periph,gate->reset);
        state &= GET_BITS(gate->rst_shift, 1, reg);
    }

    /* enable dram gating */
    if(gate->dram) {
        reg = periph_readl(periph,gate->dram);
        state &= GET_BITS(gate->ddr_shift, 1, reg);
    }

    return state;
}
static int sunxi_clk_periph_is_enabled(struct clk_hw *hw)
{
    int state = 0;
    unsigned long flags = 0;
    struct sunxi_clk_periph *periph = to_clk_periph(hw);

    if(periph->lock)
    {
        spin_lock_irqsave(periph->lock, flags);
        state = __sunxi_clk_periph_is_enabled(hw);
        spin_unlock_irqrestore(periph->lock, flags);
    }
    else
        state = __sunxi_clk_periph_is_enabled(hw);    
    return state;
}
static void __sunxi_clk_periph_disable_shared(struct sunxi_clk_periph *periph)
{
    unsigned long reg;
    struct sunxi_clk_periph_gate *gate = &periph->gate;
    if(!periph->com_gate->val)
     return ;

    periph->com_gate->val &= ~(1 << periph->com_gate_off);      

    if(!periph->com_gate->val)
    {
        /* disable dram gating */
        if(gate->dram&& IS_SHARE_MBUS_GATE(periph)) {
            reg = periph_readl(periph,gate->dram);
            reg = SET_BITS(gate->ddr_shift, 1, reg, 0);
            periph_writel(periph,reg, gate->dram);
        }

        /* disable module gating */
        if(gate->enable&& IS_SHARE_MOD_GATE(periph)) {
            reg = periph_readl(periph,gate->enable);
            reg = SET_BITS(gate->enb_shift, 1, reg, 0);
            periph_writel(periph,reg, gate->enable);
        }

        /* disable bus gating */
        if(gate->bus&& IS_SHARE_BUS_GATE(periph)) {
            reg = periph_readl(periph,gate->bus);
            reg = SET_BITS(gate->bus_shift, 1, reg, 0);
            periph_writel(periph,reg, gate->bus);
        }
        /* assert module */
        if(gate->reset && !(periph->flags & CLK_IGNORE_AUTORESET) && IS_SHARE_RST_GATE(periph)) {
            reg = periph_readl(periph,gate->reset);
            reg = SET_BITS(gate->rst_shift, 1, reg, 0);
            periph_writel(periph,reg, gate->reset);
        }
    }
   
}
static void sunxi_clk_periph_disable_shared(struct sunxi_clk_periph *periph)
{
    unsigned long flags = 0;
    
    if(!periph->com_gate->val)
     return ;

    if(periph->lock)
    {
        spin_lock_irqsave(periph->lock, flags);
        __sunxi_clk_periph_disable_shared(periph);        
        spin_unlock_irqrestore(periph->lock, flags);
    }
    else
        __sunxi_clk_periph_disable_shared(periph);         
}
static void __sunxi_clk_periph_disable(struct clk_hw *hw)
{
    unsigned long reg;
    struct sunxi_clk_periph *periph = to_clk_periph(hw);
    struct sunxi_clk_periph_gate *gate = &periph->gate;

    /* disable dram gating */
    if(gate->dram&& !IS_SHARE_MBUS_GATE(periph)) {
        reg = periph_readl(periph,gate->dram);
        reg = SET_BITS(gate->ddr_shift, 1, reg, 0);
        periph_writel(periph,reg, gate->dram);
    }

    /* disable module gating */
    if(gate->enable&& !IS_SHARE_MOD_GATE(periph)) {
        reg = periph_readl(periph,gate->enable);
        if(periph->flags & CLK_REVERT_ENABLE)
            reg = SET_BITS(gate->enb_shift, 1, reg, 1);
        else
            reg = SET_BITS(gate->enb_shift, 1, reg, 0);

        periph_writel(periph,reg, gate->enable);
    }

    /* disable bus gating */
    if(gate->bus&& !IS_SHARE_BUS_GATE(periph)) {
        reg = periph_readl(periph,gate->bus);
        reg = SET_BITS(gate->bus_shift, 1, reg, 0);
        periph_writel(periph,reg, gate->bus);
    }

    /* assert module */
    if(gate->reset && !(periph->flags & CLK_IGNORE_AUTORESET) &&!IS_SHARE_RST_GATE(periph)) {
        reg = periph_readl(periph,gate->reset);
        reg = SET_BITS(gate->rst_shift, 1, reg, 0);
        periph_writel(periph,reg, gate->reset);
    }
}
static void sunxi_clk_periph_disable(struct clk_hw *hw)
{
    unsigned long flags = 0;
    struct sunxi_clk_periph *periph = to_clk_periph(hw);

    if(periph->flags & CLK_READONLY)
        return ;

    if(periph->lock)
    {
        spin_lock_irqsave(periph->lock, flags);
        __sunxi_clk_periph_disable(hw);
        spin_unlock_irqrestore(periph->lock, flags);
    }
    else
        __sunxi_clk_periph_disable(hw);    
    if(periph->com_gate)
        sunxi_clk_periph_disable_shared(periph);        
}

static unsigned long sunxi_clk_periph_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
    unsigned long reg, flags = 0;
    struct sunxi_clk_periph *periph = to_clk_periph(hw);
    struct sunxi_clk_periph_div *divider = &periph->divider;
    unsigned long div, div_m = 0, div_n = 0;
    u64 rate = parent_rate;

    if(!divider->reg)
        return parent_rate;

	if(periph->lock)
    {
        spin_lock_irqsave(periph->lock, flags);
        reg = periph_readl(periph,divider->reg);
        if(divider->mwidth)
            div_m = GET_BITS(divider->mshift, divider->mwidth, reg);
        if(divider->nwidth)
            div_n = GET_BITS(divider->nshift, divider->nwidth, reg);
        div = (div_m+1)*(1<<div_n);
        do_div(rate, div);
        spin_unlock_irqrestore(periph->lock, flags);
    }
    else
    {
        reg = periph_readl(periph,divider->reg);
        if(divider->mwidth)
            div_m = GET_BITS(divider->mshift, divider->mwidth, reg);
        if(divider->nwidth)
            div_n = GET_BITS(divider->nshift, divider->nwidth, reg);
        div = (div_m+1)*(1<<div_n);
        do_div(rate, div);
    }
    return rate;
}


static long sunxi_clk_periph_round_rate(struct clk_hw *hw, unsigned long rate, unsigned long *prate)
{
    struct sunxi_clk_periph *periph = to_clk_periph(hw);
    struct sunxi_clk_periph_div *divider = &periph->divider;
#ifdef NEW_RATE_CALULATE
    unsigned long i=0,factor_m=0,factor_n=0,found=0;
#endif
    unsigned long div, div_m = 0, div_n = 0;
    u64 parent_rate = (*prate+rate/2-1);

    do_div(parent_rate, rate);
    div = parent_rate;
    if(!div)
        return *prate;

    parent_rate = *prate;
    div_m = 1<<divider->mwidth;
    if(divider->nwidth) {
        div_n = 1<<divider->nwidth;
        div_n = 1<<(div_n-1);
    } else
        div_n = 1;
#ifndef NEW_RATE_CALULATE
    if(div <= div_m) {
        do_div(parent_rate, div);
    } else if((div <= div_m*2) && (div_n >= 2)) {
        div &= ~(1<<0);
        do_div(parent_rate, div);
    } else if((div <= div_m*4) && (div_n >= 4)) {
        div &= ~(3<<0);
        do_div(parent_rate, div);
    } else if((div <= div_m*8) && (div_n >= 8)) {
        div &= ~(7<<0);
        do_div(parent_rate, div);
    } else if((div <= div_m*16) && (div_n >= 16)) {
        div &= ~(15<<0);
        do_div(parent_rate, div);
    } else if((div <= div_m*32) && (div_n >= 32)) {
        div &= ~(31<<0);
        do_div(parent_rate, div);
    } else if((div <= div_m*64) && (div_n >= 64)) {
        div &= ~(63<<0);
        do_div(parent_rate, div);
    } else if((div <= div_m*128) && (div_n >= 128)) {
        div &= ~(127<<0);
        do_div(parent_rate, div);
    } else {
        do_div(parent_rate, div_m*div_n);
    }
#else //NEW_RATE_CALULATE
    while(i < (1<<divider->nwidth))
    {
        if(div <= div_m)
        {
            factor_m = div-1;
            factor_n = i;
            do_div(parent_rate, (factor_m+1)*(1 << factor_n));
            found = 1;
            break;
        }
        div = div >>1;
        i++;

         if(!div)
        {
            factor_m = 0;
            factor_n = i;
            do_div(parent_rate, (factor_m+1)*(1 << factor_n));
            found = 1;
            break;
        }
    }
    if(!found)
    {
        factor_m = (div >div_m?div_m:div)-1;
        factor_n = (1<<divider->nwidth) -1;
        do_div(parent_rate, (factor_m+1)*(1 << factor_n));
    }
#endif
    return parent_rate;
}

static int __sunxi_clk_periph_set_rate(struct clk_hw *hw, unsigned long rate, unsigned long parent_rate)
{
#ifdef NEW_RATE_CALULATE
    unsigned long i=0,factor_m=0,factor_n=0,found=0;
#endif
    unsigned long reg;
    struct sunxi_clk_periph *periph = to_clk_periph(hw);
    struct sunxi_clk_periph_div *divider = &periph->divider;
    unsigned long div, div_m = 0, div_n = 0;
    u64 tmp_rate = parent_rate;

	if(periph->flags & CLK_READONLY)
        return 0;
		
	if(!divider->reg)
		return 0;

    do_div(tmp_rate, rate);
    div = tmp_rate;
    if(!div)
        div_m = div_n =0;
    else {
        div_m = 1<<divider->mwidth;
        div_n = (1<<divider->nwidth)-1;
		
		if( div > (div_m<<div_n) )
		{
			WARN(1, "clk %s rate is too large : %lu\n",hw->clk->name , rate );
			div = div_m<<div_n;
		}
#ifndef NEW_RATE_CALULATE
        if(div < div_m) {
            div_m = div;
            div_n = 0;
        } else if((div < div_m*2) && (div_n > 0)){
            div_n = 1;
            div_m = div>>1;
        } else if((div < div_m*4) && (div_n > 1)){
            div_n = 2;
            div_m = div>>2;
        } else if((div < div_m*8) && (div_n > 2)){
            div_n = 3;
            div_m = div>>3;
        } else if((div < div_m*16) && (div_n > 3)){
            div_n = 4;
            div_m = div>>4;
        } else if((div < div_m*32) && (div_n > 4)){
            div_n = 5;
            div_m = div>>5;

        } else if((div < div_m*64) && (div_n > 5)){
            div_n = 6;
            div_m = div>>6;
        } else if((div < div_m*128) && (div_n > 6)){
            div_n = 7;
            div_m = div>>7;
        } else {
            div_m = (1<<divider->mwidth);// - 1;
            div_n = (1<<divider->nwidth) - 1;
        }
        if(div_m)
            div_m--;
#else
    found = 0;
    while(i < (1<<divider->nwidth))
    {
        if(div <= div_m)
        {
            factor_m = div-1;
            factor_n = i;
            found = 1;
            break;
        }
        div = div >>1;
        i++;
         if(!div)
        {
            factor_m = 0;
            factor_n = i;
            found = 1;
            break;
        }
    }
    if(!found)
    {
        factor_m = (div >div_m?div_m:div)-1;
        factor_n = (1<<divider->nwidth) -1;
    }
    div_m = factor_m;
    div_n = factor_n;
#endif
    }

    reg = periph_readl(periph,divider->reg);
    if(divider->mwidth)
        reg = SET_BITS(divider->mshift, divider->mwidth, reg, div_m);
    if(divider->nwidth)
        reg = SET_BITS(divider->nshift, divider->nwidth, reg, div_n);
    periph_writel(periph,reg, divider->reg);

    return 0;
}
static int sunxi_clk_periph_set_rate(struct clk_hw *hw, unsigned long rate, unsigned long parent_rate)
{
    unsigned long flags = 0;
    int ret = 0;
    struct sunxi_clk_periph *periph = to_clk_periph(hw);

    if(periph->lock)
    {
        spin_lock_irqsave(periph->lock, flags);
        ret = __sunxi_clk_periph_set_rate(hw,rate,parent_rate);
        spin_unlock_irqrestore(periph->lock, flags);        
    }
    else
        ret = __sunxi_clk_periph_set_rate(hw,rate,parent_rate);
    return ret;
}

static const struct clk_ops sunxi_clk_periph_ops = {

    .get_parent = sunxi_clk_periph_get_parent,
    .set_parent = sunxi_clk_periph_set_parent,

    .recalc_rate = sunxi_clk_periph_recalc_rate,
    .round_rate = sunxi_clk_periph_round_rate,
    .set_rate = sunxi_clk_periph_set_rate,

    .is_enabled = sunxi_clk_periph_is_enabled,
    .enable = sunxi_clk_periph_enable,
    .disable = sunxi_clk_periph_disable,
};
void sunxi_clk_get_periph_ops(struct clk_ops* ops)
{
    memcpy(ops,&sunxi_clk_periph_ops,sizeof(sunxi_clk_periph_ops));
}

struct clk *sunxi_clk_register_periph(const char *name,
            const char **parent_names, int num_parents,unsigned long flags,
            void __iomem  *base, struct sunxi_clk_periph *periph)
{
    struct clk *clk;
    struct clk_init_data init;
#ifdef __SUNXI_ALL_CLK_IGNORE_UNUSED__
		flags |= CLK_IGNORE_UNUSED;
#endif
    init.name = name;
    init.ops = periph->priv_clkops?periph->priv_clkops:&sunxi_clk_periph_ops;
    init.flags = flags;
    init.parent_names = parent_names;
    init.num_parents = num_parents;
    
    /* Data in .init is copied by clk_register(), so stack variable OK */
    periph->hw.init = &init;
    periph->flags = init.flags;
    /* fix registers */
    periph->mux.reg = periph->mux.reg ? (base + (u32 __force)periph->mux.reg) : NULL;
    periph->divider.reg = periph->divider.reg ? (base + (u32 __force)periph->divider.reg) : NULL;
    periph->gate.enable = periph->gate.enable ? (base + (u32 __force)periph->gate.enable) : NULL;
    periph->gate.reset = periph->gate.reset ? (base + (u32 __force)periph->gate.reset) : NULL;
    periph->gate.bus = periph->gate.bus ? (base + (u32 __force)periph->gate.bus) : NULL;
    periph->gate.dram = periph->gate.dram ? (base + (u32 __force)periph->gate.dram) : NULL;
	
    clk = clk_register(NULL, &periph->hw);
    if (IS_ERR(clk))
        return clk;

    return clk;
}


int sunxi_periph_reset_deassert(struct clk *c)
{
    struct clk_hw *hw = __clk_get_hw(c);
    struct sunxi_clk_periph *periph = to_clk_periph(hw);
    struct sunxi_clk_periph_gate *gate = &periph->gate;
    unsigned long reg, flag = 0;
    
    if(periph->flags & CLK_READONLY)
        return 0;

    if((periph->com_gate && periph->com_gate->val)
       && (periph->com_gate->val & periph->com_gate->mask) != (1 << periph->com_gate_off))
       return 1;
       
    if(gate->dram) {
        reg = periph_readl(periph,gate->dram);
        flag = GET_BITS(gate->ddr_shift, 1, reg);
        /* disable dram access */
        reg = SET_BITS(gate->ddr_shift, 1, reg, 0);
        periph_writel(periph,reg, gate->dram);
    }

    if(gate->reset) {
        reg = periph_readl(periph,gate->reset);
        reg = SET_BITS(gate->rst_shift, 1, reg, 1);
        periph_writel(periph,reg, gate->reset);
    }

    /* enable dram access if it is needed */
    if(gate->dram && flag) {
        reg = periph_readl(periph,gate->dram);
        reg = SET_BITS(gate->ddr_shift, 1, reg, 1);
        periph_writel(periph,reg, gate->dram);
    }
    return 0;
}
/*
static void sunxi_periph_auto_reset_disable(struct clk *c)
{
    struct clk_hw *hw = __clk_get_hw(c);
    struct sunxi_clk_periph *periph = to_clk_periph(hw);
    periph->flags |= CLK_IGNORE_AUTORESET;
}
static void sunxi_periph_auto_reset_enable(struct clk *c)
{
    struct clk_hw *hw = __clk_get_hw(c);
    struct sunxi_clk_periph *periph = to_clk_periph(hw);
    periph->flags &= ~CLK_IGNORE_AUTORESET;
}
*/
int sunxi_periph_reset_assert(struct clk *c)
{
    struct clk_hw *hw = __clk_get_hw(c);
    struct sunxi_clk_periph *periph = to_clk_periph(hw);
    struct sunxi_clk_periph_gate *gate = &periph->gate;
    unsigned long reg, flag = 0;

	if(periph->flags & CLK_READONLY)
        return 0;
	
    if((periph->com_gate && periph->com_gate->val)
       && (periph->com_gate->val & periph->com_gate->mask) != (1 << periph->com_gate_off))
       return 1;    
    
    /* disable dram access */
    if(gate->dram) {
        reg = periph_readl(periph,gate->dram);
        flag = GET_BITS(gate->ddr_shift, 1, reg);
        reg = SET_BITS(gate->ddr_shift, 1, reg, 0);
        periph_writel(periph,reg, gate->dram);
    }

    /* assert reset of periph */
    if(gate->reset) {
        reg = periph_readl(periph,gate->reset);
        reg = SET_BITS(gate->rst_shift, 1, reg, 0);
        periph_writel(periph,reg, gate->reset);
    }
    /* enable dram access if it is needed */
    if(gate->dram && flag) {
        reg = periph_readl(periph,gate->dram);
        reg = SET_BITS(gate->ddr_shift, 1, reg, 1);
        periph_writel(periph,reg, gate->dram);
    }
    return 0;
}
EXPORT_SYMBOL(sunxi_periph_reset_assert);
EXPORT_SYMBOL(sunxi_periph_reset_deassert);

