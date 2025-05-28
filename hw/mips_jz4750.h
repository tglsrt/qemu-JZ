/*
 * ingenic JZ Soc
 *
 * Copyright (C) 2009 yajin<yajin@vm-kernel.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 or
 * (at your option) version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#ifndef _MIPS_JZ4750_H_
#define _MIPS_JZ4750_H_

#include "qemu-common.h"



#define JZ4750_SRAM_SIZE	0x4000 /* Placeholder, check JZ4750 specific */
#define JZ4750_SRAM_BASE 0x80000000 /* Placeholder, check JZ4750 specific */
#define JZ4750_SDRAM_BASE 0x80004000 /* Placeholder, check JZ4750 specific */

#define JZ4750_PHYS_BASE(a) ((a)-0xa0000000) /* Placeholder, check JZ4750 specific */

#define	JZ4750_CPM_BASE	0xB0000000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_INTC_BASE	0xB0001000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_TCU_BASE	0xB0002000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_WDT_BASE	0xB0002000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_RTC_BASE	0xB0003000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_GPIO_BASE	0xB0010000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_AIC_BASE	0xB0020000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_ICDC_BASE	0xB0020000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_MSC_BASE	0xB0021000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_UART0_BASE	0xB0030000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_I2C_BASE	0xB0042000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_SSI_BASE	0xB0043000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_SADC_BASE	0xB0070000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_EMC_BASE	0xB3010000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_DMAC_BASE	0xB3020000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_UHC_BASE	0xB3030000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_UDC_BASE	0xB3040000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_LCD_BASE	0xB3050000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_SLCD_BASE	0xB3050000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_CIM_BASE	0xB3060000 /* Placeholder, check JZ4750 specific */
#define	JZ4750_ETH_BASE	0xB3100000 /* Placeholder, check JZ4750 specific */

/* Clock Control Register */ /* TODO: Verify these for JZ4750 */
#define CPM_CPCCR_I2CS		(1 << 31)
#define CPM_CPCCR_CLKOEN	(1 << 30)
#define CPM_CPCCR_UCS		(1 << 29)
#define CPM_CPCCR_UDIV_BIT	23
#define CPM_CPCCR_UDIV_MASK	(0x3f << CPM_CPCCR_UDIV_BIT)
#define CPM_CPCCR_CE		(1 << 22)
#define CPM_CPCCR_PCS		(1 << 21)
#define CPM_CPCCR_LDIV_BIT	16
#define CPM_CPCCR_LDIV_MASK	(0x1f << CPM_CPCCR_LDIV_BIT)
#define CPM_CPCCR_MDIV_BIT	12
#define CPM_CPCCR_MDIV_MASK	(0x0f << CPM_CPCCR_MDIV_BIT)
#define CPM_CPCCR_PDIV_BIT	8
#define CPM_CPCCR_PDIV_MASK	(0x0f << CPM_CPCCR_PDIV_BIT)
#define CPM_CPCCR_HDIV_BIT	4
#define CPM_CPCCR_HDIV_MASK	(0x0f << CPM_CPCCR_HDIV_BIT)
#define CPM_CPCCR_CDIV_BIT	0
#define CPM_CPCCR_CDIV_MASK	(0x0f << CPM_CPCCR_CDIV_BIT)


/* I2S Clock Divider Register */
#define CPM_I2SCDR_I2SDIV_BIT	0
#define CPM_I2SCDR_I2SDIV_MASK	(0x1ff << CPM_I2SCDR_I2SDIV_BIT)

/* LCD Pixel Clock Divider Register */
#define CPM_LPCDR_PIXDIV_BIT	0
#define CPM_LPCDR_PIXDIV_MASK	(0x1ff << CPM_LPCDR_PIXDIV_BIT)

/* MSC Clock Divider Register */
#define CPM_MSCCDR_MSCDIV_BIT	0
#define CPM_MSCCDR_MSCDIV_MASK	(0x1f << CPM_MSCCDR_MSCDIV_BIT)

/* PLL Control Register */
#define CPM_CPPCR_PLLM_BIT	23
#define CPM_CPPCR_PLLM_MASK	(0x1ff << CPM_CPPCR_PLLM_BIT)
#define CPM_CPPCR_PLLN_BIT	18
#define CPM_CPPCR_PLLN_MASK	(0x1f << CPM_CPPCR_PLLN_BIT)
#define CPM_CPPCR_PLLOD_BIT	16
#define CPM_CPPCR_PLLOD_MASK	(0x03 << CPM_CPPCR_PLLOD_BIT)
#define CPM_CPPCR_PLLS		(1 << 10)
#define CPM_CPPCR_PLLBP		(1 << 9)
#define CPM_CPPCR_PLLEN		(1 << 8)
#define CPM_CPPCR_PLLST_BIT	0
#define CPM_CPPCR_PLLST_MASK	(0xff << CPM_CPPCR_PLLST_BIT)





#define JZ_FMT_plx "%llx"

uint32_t jz4750_badwidth_read8(void *opaque, target_phys_addr_t addr);
uint32_t jz4750_badwidth_read16(void *opaque, target_phys_addr_t addr);
uint32_t jz4750_badwidth_read32(void *opaque, target_phys_addr_t addr);
void jz4750_badwidth_write8(void *opaque, target_phys_addr_t addr,
                                    uint32_t value);
void jz4750_badwidth_write16(void *opaque, target_phys_addr_t addr,
                                    uint32_t value);
void jz4750_badwidth_write32(void *opaque, target_phys_addr_t addr,
                                    uint32_t value);

#define IO_ACCESS_VERBOSE			1

#ifdef IO_ACCESS_VERBOSE
#define JZ4750_8B_REG(paddr)		\
        fprintf(stderr, "%s: 8-bit register " JZ_FMT_plx "\n",	\
                        __FUNCTION__, paddr)
#define JZ4750_16B_REG(paddr)		\
        fprintf(stderr, "%s: 16-bit register " JZ_FMT_plx "\n",	\
                        __FUNCTION__, paddr)
#define JZ4750_32B_REG(paddr)		\
        fprintf(stderr, "%s: 32-bit register " JZ_FMT_plx "\n",	\
                        __FUNCTION__, paddr)
#define JZ4750_RO_REG(paddr)		\
        fprintf(stderr, "%s: write to read only 32-bit register " JZ_FMT_plx "\n",	\
                        __FUNCTION__, paddr)
#define JZ4750_WO_REG(paddr)		\
        fprintf(stderr, "%s: read from write only 32-bit register " JZ_FMT_plx "\n",	\
                        __FUNCTION__, paddr)
#else
#define JZ4750_8B_REG(paddr)
#define JZ4750_16B_REG(paddr)
#define JZ4750_32B_REG(paddr)
#define JZ4750_RO_REG(paddr)	
#define JZ4750_WO_REG(paddr)
#endif



/*forward define*/
struct jz_state_s;


/*mips_jz4750_clk.c*/ /* Assuming this file will be renamed or its functions adapted */
struct clk {
    const char *name;
    const char *alias;
    struct clk *parent;
    struct clk *child1;
    struct clk *sibling;

    uint32_t flags;
    int id;

    int running;		/* Is currently ticking */
    int enabled;		/* Is enabled, regardless of its input clk */
    unsigned long rate;		/* Current rate (if .running) */
    unsigned int divisor;	/* Rate relative to input (if .enabled) */
    unsigned int multiplier;	/* Rate relative to input (if .enabled) */
    //int usecount;	
};
typedef struct clk *jz_clk;
void jz_clk_init(struct jz_state_s *mpu,uint32_t osc_extal_freq);
jz_clk jz_findclk(struct jz_state_s *mpu, const char *name);
void jz_clk_get(jz_clk clk);
void jz_clk_put(jz_clk clk);
void jz_clk_onoff(jz_clk clk, int on);
void jz_clk_canidle(jz_clk clk, int can);
void jz_clk_setrate(jz_clk clk, int divide, int multiply);
int64_t jz_clk_getrate(jz_clk clk);
void jz_clk_reparent(jz_clk clk, jz_clk parent); /* Assuming these clk functions are generic or will be adapted */

/*mips_jz4750.c*/
struct jz_state_s *jz4750_init(unsigned long sdram_size, uint32_t osc_extal_freq);

enum jz_cpu_model { /* Keep jz4740 and jz4730 if this struct is shared or for compatibility */
        jz4740,
        jz4730,
        jz4750
    };
#define cpu_is_jz4730(cpu)		(cpu->mpu_model == jz4730) /* Keep for compatibility if needed */
#define cpu_is_jz4740(cpu)		(cpu->mpu_model == jz4740) /* Keep for compatibility if needed */
#define cpu_is_jz4750(cpu)		(cpu->mpu_model == jz4750)

struct jz_state_s { /* This struct definition is now for JZ4750 context primarily */
 	enum jz_cpu_model mpu_model;
	CPUState *env;
	unsigned long sdram_size;
    unsigned long sram_size;

	jz_clk clks;

	struct jz4750_cpm_s *cpm;
	struct jz4750_emc_s *emc;
	struct jz4750_gpio_s *gpio;
	struct jz4750_rtc_s *rtc;
	struct jz4750_tcu_s *tcu;
	struct jz4750_lcdc_s *lcdc;
	struct jz4750_dma_s *dma;
	struct jz4750_sadc_s *sadc;
	
};

#endif
