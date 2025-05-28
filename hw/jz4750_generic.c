/*
 * QEMU jz4750_generic board emulation
 *
 * Copyright (c) 2009 yajin (yajin@vm-kernel.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


/*
 * The emulation target is jz4750_generic board.
 *  http://www.ingenic.cn/eng/productServ/kfyd/Hardware/pffaqQuestionContent.aspx?Category=2&Question=3
 *
 */

#include "hw.h"
#include "pc.h"
#include "fdc.h"
#include "net.h"
#include "boards.h"
#include "smbus.h"
#include "block.h"
#include "flash.h"
#include "mips.h"
#include "pci.h"
#include "qemu-char.h"
#include "sysemu.h"
#include "audio/audio.h"
#include "boards.h"
#include "qemu-log.h"
#include "mips_jz4750.h" /* Updated include */



#define JZ4750_GENERIC_RAM_SIZE       (0x4000000) /*64M */ /* Renamed and assuming same value for now */
#define JZ4750_GENERIC_OSC_EXTAL     (12000000)   /*12MHZ */ /* Renamed and assuming same value for now */

/* jz4750_generic board support */
struct mips_jz4750_generic_s /* Renamed struct */
{
    struct jz_state_s *soc;

    struct nand_bflash_s *nand; /* Assuming NAND support is still desired */
};

static uint32_t jz4750_generic_nand_read8(void *opaque, target_phys_addr_t addr) /* Renamed function */
{
	struct mips_jz4750_generic_s *s = (struct mips_jz4750_generic_s *) opaque;

	switch (addr)
	{
		case 0x8000: /*NAND_COMMAND*/
		case 0x10000: /*NAND_ADDRESS*/
			jz4750_badwidth_read8(s,addr); /* Updated call */
			break;
		case 0x0: /*NAND_DATA*/
			return nandb_read_data8(s->nand);
			break;
		default:
			jz4750_badwidth_read8(s,addr); /* Updated call */
			break;
	}
    return 0;
}

static void jz4750_generic_nand_write8(void *opaque, target_phys_addr_t addr, /* Renamed function */
                uint32_t value)
{
	struct mips_jz4750_generic_s *s = (struct mips_jz4750_generic_s *) opaque;

	//printf("write addr %x value %x \n",addr,value);

    switch (addr)
	{
		case 0x8000: /*NAND_COMMAND*/
			nandb_write_command(s->nand,value);
			break;
		case 0x10000: /*NAND_ADDRESS*/
			nandb_write_address(s->nand,value);
			break;
		case 0x0: /*NAND_DATA*/
			nandb_write_data8(s->nand,value);
			break;
		default:
			jz4750_badwidth_write8(s,addr,value); /* Updated call */
			break;
	}
}


CPUReadMemoryFunc *jz4750_generic_nand_readfn[] = { /* Renamed array */
        jz4750_generic_nand_read8,
        jz4750_badwidth_read16, /* Updated call */
        jz4750_badwidth_read32, /* Updated call */
};
CPUWriteMemoryFunc *jz4750_generic_nand_writefn[] = { /* Renamed array */
        jz4750_generic_nand_write8,
        jz4750_badwidth_write16, /* Updated call */
        jz4750_badwidth_write32, /* Updated call */
};
    
static void jz4750_generic_nand_setup(struct mips_jz4750_generic_s *s) /* Renamed function */
{
	int iomemtype;
	
	/*K9K8G08U0*/ /* Assuming same NAND chip or similar compatible one */
	s->nand = nandb_init(NAND_MFR_SAMSUNG,0xd3);

	iomemtype = cpu_register_io_memory(jz4750_generic_nand_readfn,
                    jz4750_generic_nand_writefn, s);
    cpu_register_physical_memory(0x18000000, 0x20000, iomemtype); /* TODO: Check JZ4750 specific NAND memory map */
}

static int jz4750_generic_nand_read_page(struct mips_jz4750_generic_s *s,uint8_t *buf, uint16_t page_addr) /* Renamed function */
{
	uint8_t *p;
	int i;

	p=(uint8_t *)buf;

	/*send command 0x0*/
	jz4750_generic_nand_write8(s,0x00008000,0);
	/*send page address */
	jz4750_generic_nand_write8(s,0x00010000,page_addr&0xff);
	jz4750_generic_nand_write8(s,0x00010000,(page_addr>>8)&0x7);
	jz4750_generic_nand_write8(s,0x00010000,(page_addr>>11)&0xff);
	jz4750_generic_nand_write8(s,0x00010000,(page_addr>>19)&0xff);
	jz4750_generic_nand_write8(s,0x00010000,(page_addr>>27)&0xff);
	/*send command 0x30*/
	jz4750_generic_nand_write8(s,0x00008000,0x30);

	for (i=0;i<0x800;i++)
	{
		*p++ = jz4750_generic_nand_read8(s,0x00000000);
	}
	return 1;
}

/*read the u-boot from NAND Flash into internal RAM*/
static int jz4750_generic_boot_from_nand(struct mips_jz4750_generic_s *s) /* Renamed function */
{
	uint32_t len;
	uint8_t nand_page[0x800];
	uint32_t nand_pages,i;

	//int fd;
	

	len = 0x2000; /*8K*/ /* Assuming same u-boot size for now */
	
	nand_pages = len/0x800;
	//fd = open("u-boot.bin", O_RDWR | O_CREAT);
	for (i=0;i<nand_pages;i++)
	{
		jz4750_generic_nand_read_page(s,nand_page,i*0x800);
		cpu_physical_memory_write_rom(i * 0x800, nand_page, 0x800); /* TODO: Check JZ4750 boot address */
		//write(fd,nand_page,0x800);
	}
	s->soc->env->active_tc.PC = 0x80000004; /* TODO: Check JZ4750 boot entry point */

	//close(fd);
	return 0;

}


 static int jz4750_generic_rom_emu(struct mips_jz4750_generic_s *s) /* Renamed function */
{
	if (jz4750_generic_boot_from_nand(s)<0)
		return (-1); 
	return (0);
}

static void mips_jz4750_generic_init(ram_addr_t ram_size, int vga_ram_size, /* Renamed function */
                    const char *boot_device, DisplayState * ds,
                    const char *kernel_filename,
                    const char *kernel_cmdline,
                    const char *initrd_filename, const char *cpu_model)
{
    struct mips_jz4750_generic_s *s = (struct mips_jz4750_generic_s *) qemu_mallocz(sizeof(*s));

    if (ram_size < JZ4750_GENERIC_RAM_SIZE + JZ4750_SRAM_SIZE) /* Updated constants */
    {
        fprintf(stderr, "This architecture uses %d bytes of memory\n",
                JZ4750_GENERIC_RAM_SIZE + JZ4750_SRAM_SIZE); /* Updated constants */
        exit(1);
    }
    s->soc = jz4750_init(JZ4750_GENERIC_RAM_SIZE, JZ4750_GENERIC_OSC_EXTAL); /* Updated call and constants */
    jz4750_generic_nand_setup(s);
    if (jz4750_generic_rom_emu(s)<0)
   	{
   		fprintf(stderr,"boot from nand failed for jz4750_generic\n"); /* Updated message */
   		exit(-1);
   	}

}




QEMUMachine mips_jz4750_generic_machine = { /* Renamed machine struct */
    .name = "jz4750_generic", /* Updated name */
    .desc = "JZ4750 generic board", /* Updated description */
    .init = mips_jz4750_generic_init, /* Updated init function */
};

static void mips_jz4750_generic_machine_init(void) /* Renamed function */
{
    qemu_register_machine(&mips_jz4750_generic_machine); /* Updated machine struct */
}

machine_init(mips_jz4750_generic_machine_init); /* Updated function */
