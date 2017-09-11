/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
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

#include <common.h>
#include <command.h>
#include <asm/addrspace.h>
//#include "LzmaDecode.h"

//#define MAX_SDRAM_SIZE	(64*1024*1024)
//#define MIN_SDRAM_SIZE	(8*1024*1024)
#define MAX_SDRAM_SIZE	(256*1024*1024)
#define MIN_SDRAM_SIZE	(8*1024*1024)

#ifdef SDRAM_CFG_USE_16BIT
#define MIN_RT2880_SDRAM_SIZE	(16*1024*1024)
#else
#define MIN_RT2880_SDRAM_SIZE	(32*1024*1024)
#endif

#define SDRAM_SIZE_128M	(128*1024*1024)
#define SDRAM_SIZE_64M	(64*1024*1024)
#define SDRAM_SIZE_32M	(32*1024*1024)
#define SDRAM_SIZE_16M	(16*1024*1024)

#if defined(MEMORY_DETECT) && defined(MT7620_ASIC_BOARD)
#define MT7620_SDRAM_CONF_256M	(0x6<<18)
#define MT7620_SDRAM_CONF_128M	(0x5<<18)
#define MT7620_SDRAM_CONF_64M	(0x4<<18)
#define MT7620_SDRAM_CONF_32M	(0x3<<18)
#define MT7620_SDRAM_CONF_16M	(0x2<<18)
#define MT7620_SDRAM_CONF_16M	(0x1<<18)
#endif
/*
 * Check memory range for valid RAM. A simple memory test determines
 * the actually available RAM size between addresses `base' and
 * `base + maxsize'.
 */
long get_ram_size(volatile long *base, long maxsize)
{
	volatile long *addr;
	long           save[32];
	long           cnt;
	long           val;
	long           size=0;
	unsigned long  mem_reg=0;
	int            i,try=0;
printf("Memory Testing.");
//printf("\n0x10000300=0x%x\n",*(volatile u_long *)0x10000300);
//printf("0x10000304=0x%x\n",*(volatile u_long *)0x10000304);

#if defined(ZBT_AP8100RT_BOARD) || defined(ZBT_WR83052RT_BOARD) || defined(WCR_GN_BOARD) 
//Fix Memory to 32M 16Bit
//le32_to_cpu(*(volatile u_long *)0x10000304)=0xa0120300;	
#endif

#if defined(MEMORY_DETECT) && !defined(UBOOT_RAM)
#if defined(RT3052_ASIC_BOARD)
	/* Try Set SDRAM to 512MBit With 32Bit BUS. */ 
	le32_to_cpu(*(volatile u_long *)0x10000300)=0xd1825272;
	le32_to_cpu(*(volatile u_long *)0x10000304)=0xa1220600;	
#elif defined(MT7620_ASIC_BOARD)
	/* Try Set DDR to 512MBit With 16Bit BUS. */ 
	mem_reg=le32_to_cpu(*(volatile u_long *)0x10000344);
	mem_reg&=~(MT7620_SDRAM_CONF_64M<<18);
	mem_reg|=(MT7620_SDRAM_CONF_64M<<18);
	le32_to_cpu(*(volatile u_long *)0x10000344)=mem_reg;
#endif /*RT3052_ASIC_BOARD*/
#endif	
sdram_check:

//printf(" Try%d",try);udelay(1000*50);
printf(".");//udelay(1000*50);
i=0;
#if defined(MEMORY_DETECT) && !defined(UBOOT_RAM)
#if defined(RT3052_ASIC_BOARD)
if(size==SDRAM_SIZE_64M)
{
	le32_to_cpu(*(volatile u_long *)0x10000304)=0xa1120300;
}
else if(size==SDRAM_SIZE_32M)
{
	le32_to_cpu(*(volatile u_long *)0x10000304)=0xa1110600;
}
#elif defined(MT7620_ASIC_BOARD)
if(size==SDRAM_SIZE_128M)
{
	/* Try Set DDR to 512MBit With 16Bit BUS. */ 
	mem_reg=le32_to_cpu(*(volatile u_long *)0x10000344);
	mem_reg&=~(MT7620_SDRAM_CONF_128M<<18);
	mem_reg|=(MT7620_SDRAM_CONF_128M<<18);
	le32_to_cpu(*(volatile u_long *)0x10000344)=mem_reg;
}
if(size==SDRAM_SIZE_64M)
{
	/* Try Set DDR to 512MBit With 16Bit BUS. */ 
	mem_reg=le32_to_cpu(*(volatile u_long *)0x10000344);
	mem_reg&=~(MT7620_SDRAM_CONF_64M<<18);
	mem_reg|=(MT7620_SDRAM_CONF_64M<<18);
	le32_to_cpu(*(volatile u_long *)0x10000344)=mem_reg;
}
else if(size==SDRAM_SIZE_32M)
{
	/* Try Set DDR to 512MBit With 16Bit BUS. */ 
	mem_reg=le32_to_cpu(*(volatile u_long *)0x10000344);
	mem_reg&=~(MT7620_SDRAM_CONF_32M<<18);
	mem_reg|=(MT7620_SDRAM_CONF_32M<<18);
	le32_to_cpu(*(volatile u_long *)0x10000344)=mem_reg;
}
#endif /*RT3052_ASIC_BOARD*/
#endif
	//cnt=16777216 0x1000000  cnt 
	for (cnt = (maxsize / sizeof (long)) >> 1; cnt > 0; cnt >>= 1) {
		addr = base + cnt;	/* pointer arith! */
		save[i++] = *addr;
		
		*addr = ~cnt;

		
	}

	addr = base;
	save[i] = *addr;

	*addr = 0;

	
	if ((val = *addr) != 0) {
		/* Restore the original data before leaving the function.
		 */
		*addr = save[i];
		for (cnt = 1; cnt < maxsize / sizeof(long); cnt <<= 1) {
			addr  = base + cnt;
			*addr = save[--i];
		}
		return (0);
	}

	for (cnt = 1; cnt < maxsize / sizeof (long); cnt <<= 1) {
		addr = base + cnt;	/* pointer arith! */

	//	printf("\n retrieve addr=%08X \n",addr);
			val = *addr;
		*addr = save[--i];
		if (val != ~cnt) {
			size = cnt * sizeof (long);
			
		//	printf("\n The Addr[%08X],do back ring  \n",addr);
			
			/* Restore the original data before leaving the function.
			 */
			for (cnt <<= 1; cnt < maxsize / sizeof (long); cnt <<= 1) {
				addr  = base + cnt;
				*addr = save[--i];
			}
#if defined(MEMORY_DETECT) && !defined(UBOOT_RAM)
/* srart mem detect */
	printf(".");try++;
#if defined(RT3052_ASIC_BOARD)
	if(size==SDRAM_SIZE_16M)
	{
//	  debug("Set MEM 16MB.\n"); 
	  le32_to_cpu(*(volatile u_long *)0x10000304)=0xa1010600;  
	}
	else if(size==SDRAM_SIZE_32M)
	{
//	  debug("Set MEM 32MB.\n"); 
	  le32_to_cpu(*(volatile u_long *)0x10000304)=0xa1110600;
	  if(try==2)
	  goto sdram_check;
	}
	else if(size==SDRAM_SIZE_64M)
	{
//	  debug("Set MEM 64MB.\n"); 
	  le32_to_cpu(*(volatile u_long *)0x10000304)=0xa1120300; 
	  if(try==1)
	  goto sdram_check;
	}
	else if(size==SDRAM_SIZE_128M)
	{
//	  debug("Set MEM 128MB.\n"); 
	  le32_to_cpu(*(volatile u_long *)0x10000304)=0xa1220600;
	}
	else
	{
	   printf("ERROR,SDRAM Bad!Please Check the Board.\n"); 
	}
#elif defined(MT7620_ASIC_BOARD)
	if(size==SDRAM_SIZE_16M)
	{
	  debug("Set MEM 16MB.\n"); 
	/* Try Set DDR to 512MBit With 16Bit BUS. */ 
	mem_reg=le32_to_cpu(*(volatile u_long *)0x10000344);
	mem_reg&=~(MT7620_SDRAM_CONF_16M<<18);
	mem_reg|=(MT7620_SDRAM_CONF_16M<<18);
	le32_to_cpu(*(volatile u_long *)0x10000344)=mem_reg;
	}
	else if(size==SDRAM_SIZE_32M)
	{
	  debug("Set MEM 32MB.\n"); 
	/* Try Set DDR to 512MBit With 16Bit BUS. */ 
	mem_reg=le32_to_cpu(*(volatile u_long *)0x10000344);
	mem_reg&=~(MT7620_SDRAM_CONF_32M<<18);
	mem_reg|=(MT7620_SDRAM_CONF_32M<<18);
	le32_to_cpu(*(volatile u_long *)0x10000344)=mem_reg;
	  if(try==2)
	  goto sdram_check;
	}
	else if(size==SDRAM_SIZE_64M)
	{
	  debug("Set MEM 64MB.\n"); 
	/* Try Set DDR to 512MBit With 16Bit BUS. */ 
	mem_reg=le32_to_cpu(*(volatile u_long *)0x10000344);
	mem_reg&=~(MT7620_SDRAM_CONF_64M<<18);
	mem_reg|=(MT7620_SDRAM_CONF_64M<<18);
	le32_to_cpu(*(volatile u_long *)0x10000344)=mem_reg;
	  if(try==1)
	  goto sdram_check;
	}
	else if(size==SDRAM_SIZE_128M)
	{
	  debug("Set MEM 128MB.\n"); 
	/* Try Set DDR to 512MBit With 16Bit BUS. */ 
	mem_reg=le32_to_cpu(*(volatile u_long *)0x10000344);
	mem_reg&=~(MT7620_SDRAM_CONF_64M<<18);
	mem_reg|=(MT7620_SDRAM_CONF_64M<<18);
	le32_to_cpu(*(volatile u_long *)0x10000344)=mem_reg;
	}
	else
	{
	   printf("ERROR,SDRAM Bad!Please Check the Board.\n"); 
	}
#endif /*RT3052_ASIC_BOARD*/
/* end mem detect */
#endif
			printf("%ldK OK. is ",size/1024);
			return (size);
		}
	}

	return (maxsize);
}



long int initdram(int board_type)
{
	ulong size, max_size       = MAX_SDRAM_SIZE;
	ulong our_address;
  
	asm volatile ("move %0, $25" : "=r" (our_address) :);

	/* Can't probe for RAM size unless we are running from Flash.
	 */
#if 0	 
	#if defined(CFG_RUN_CODE_IN_RAM)

	printf("\n In RAM run \n"); 
    return MIN_SDRAM_SIZE;
	#else

	printf("\n In FLASH run \n"); 
    return MIN_RT2880_SDRAM_SIZE;
	#endif
#endif 
    
#if defined (RT2880_FPGA_BOARD) || defined (RT2880_ASIC_BOARD)
	if (PHYSADDR(our_address) < PHYSADDR(PHYS_FLASH_1))
	{
	    
		//return MIN_SDRAM_SIZE;
		//fixed to 32MB
		printf("\n In RAM run \n");
		return MIN_SDRAM_SIZE;
	}
#endif
	 


	size = get_ram_size((ulong *)CFG_SDRAM_BASE, MAX_SDRAM_SIZE);
	if (size > max_size)
	{
		max_size = size;
	//	printf("\n Return MAX size!! \n");
		return max_size;
	}
//	printf("\n Return Real size =%d !! \n",size);
	return size;
	
}

#define RALINK_SYSCTL_BASE 0x10000000
int checkboard (void)
{
	u8 	Id[10];
	memset(Id, 0, sizeof(Id));
//	puts ("Board: Ralink APSoC ");
#if defined(RT3052_ASIC_BOARD) || defined(RT3352_ASIC_BOARD) || defined(RT5350_ASIC_BOARD) 
	strncpy(Id, (char *)RALINK_SYSCTL_BASE, 6);
	printf("SoC:Ralink %s \n",Id);
#elif defined(MT7620_ASIC_BOARD)
	strncpy(Id, (char *)RALINK_SYSCTL_BASE, 6);
	printf("SoC:MediaTek %s \n",Id);
#else
 	puts ("Board:Ralink APSoC ");
#endif
	return 0;
}

