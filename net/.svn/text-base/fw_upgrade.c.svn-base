/*
 *
 *  firmware upgrade
 *
 */

#include <common.h>
#include <image.h>
#include <spi_api.h>

struct fw_image_type firmware_image_type[] =
{
    {
        .name	=	"Firmware",
        .magic	= 	FIRMWARE_MAGIC,
        .type	=	FIRMWARE_TYPE
    },
    {
        .name	=	"U-boot",
        .magic	= 	UBOOT_MAGIC,
        .type	=	NOR_UBOOT_TYPE
    },
    {
        .name	=	"RT3050 EEPROM",
        .magic	= 	RT3050_EEPROM_MAGIC,
        .type	=	EEPROM_TYPE
    },
    {
        .name	=	"RT3052 EEPROM",
        .magic	= 	RT3052_EEPROM_MAGIC,
        .type	=	EEPROM_TYPE
    },
    {
        .name	=	"RT3350 EEPROM",
        .magic	= 	RT3350_EEPROM_MAGIC,
        .type	=	EEPROM_TYPE
    },
    {
        .name	=	"RT3352 EEPROM",
        .magic	= 	RT3352_EEPROM_MAGIC,
        .type	=	EEPROM_TYPE
    },
    {
        .name	=	"RT5350 EEPROM",
        .magic	= 	RT5350_EEPROM_MAGIC,
        .type	=	EEPROM_TYPE,
    },
    {
        .name	=	"MT7620 EEPROM v3",
        .magic	= 	MT7620_EEPROM_MAGIC_V3,
        .type	=	EEPROM_TYPE,
    },
    {
        .name	=	"MT7620 EEPROM v4",
        .magic	= 	MT7620_EEPROM_MAGIC_V4,
        .type	=	EEPROM_TYPE,
    },
    {
        .name	=	"MT7620 EEPROM v5",
        .magic	= 	MT7620_EEPROM_MAGIC_V5,
        .type	=	EEPROM_TYPE,
    }
};

int image_type=-1;
//extern int do_reset(cmd_tbl_t *, int, int, char *[]);
static void system_reset(void)
{
	  printf("\nSYSTEM RESET!!!\n\n");
	  udelay(500);
	  do_reset(NULL, 0, 0, NULL);
	  return;
}

int firmware_check(const unsigned char *load_addr)
{
    int broken = 0,i=0;
    unsigned long len = 0, chksum = 0;
    image_header_t hdr1 ;
    unsigned char *hdr1_addr;
    hdr1_addr = load_addr;

    memmove(&hdr1, (char *)hdr1_addr, sizeof(image_header_t));

    printf("\n=================================================\n");
    printf("\nCheck image:\n");
	printf ("Image type           \t--> ");
	for (i=0;i< sizeof(firmware_image_type)/sizeof(firmware_image_type[0]);i++)
	{
	if (*(unsigned long int *)load_addr == firmware_image_type[i].magic){
		printf ("%s \n",firmware_image_type[i].name);
		image_type=firmware_image_type[i].type;
		}
	}
	if (image_type==-1){
	printf ("Unknow Magic:0x%x! \n",*(unsigned long int *)load_addr);
	broken = 1;goto end;
	}
//	printf ("Data Magic:0x%x! \n",*(unsigned long int *)(load_addr+0x40));
	#if defined(CFG_ENV_IS_IN_SPI) && !defined(MT7620_ASIC_BOARD)
	if(image_type==NOR_UBOOT_TYPE){
	printf("SPI flash not support NOR U-boot Image!\n");
	broken = 1;goto end;
	}
	#endif
	if (image_type!=FIRMWARE_TYPE)
	goto end;
	if (*(unsigned long int *)(load_addr+FIRMWARE_TAG_LEN) == UBOOT_MAGIC)
	{
	 printf("U-Boot SPI Image      \t--> Yes\n");
	image_type=SPI_UBOOT_TYPE;
#if defined(MT7620_ASIC_BOARD)
	printf("MT7620 does not support SPI U-boot Image!\n");
        broken = 1;goto end;
#endif
	}
#if 0
    /* Check header magic number */
    printf ("Image Header Magic Number --> ");
    if (ntohl(hdr1.ih_magic) != IH_MAGIC)
    {
        printf("Failed!Header Magic:0x%x.\n",ntohl(hdr1.ih_magic));
     	 broken = 1;goto end;
    }
    else
        printf("OK! Header Magic:0x%x\n",ntohl(hdr1.ih_magic));
#endif

    /* Check header crc */
    /* Skip crc checking if there is no valid header, or it may hang on due to broken header length */

    if (broken == 0)
    {
        printf("Image Header Checksum \t--> ");
        len  = sizeof(image_header_t);
        chksum = ntohl(hdr1.ih_hcrc);
        hdr1.ih_hcrc = 0;
        if (crc32(0, (char *)&hdr1, len) != chksum)
        {
            broken = 1;
            printf("Failed\n");goto end;
        }
        else
            printf("OK\n");
    }

    /* Check data crc */
    /* Skip crc checking if there is no valid header, or it may hang on due to broken data length */
    if (broken == 0)
    {
        printf("Image Data Checksum   \t--> ");
        len = ntohl(hdr1.ih_size);
        chksum = ntohl(hdr1.ih_dcrc);
        if (crc32(0, (char *)(hdr1_addr + sizeof(image_header_t)), len) != chksum)
        {
            broken = 1;
            printf("Failed\n");goto end;
        }
        else
            printf("OK\n");
    }

end:
    printf("\n=================================================\n");

    return broken;
}

#if defined (CFG_ENV_IS_IN_SPI)
extern unsigned long int flash_size;
#endif
int
do_firmware_upgrade(const unsigned char *load_addr, ulong copysize,int image_type)
{
//	printf("loadaddr=0x%x size=0x%x image_type=%d \n",(unsigned long int *)load_addr,copysize,image_type);
	int rrc = 0;
	ulong count = 0;
	uint32_t e_end = 0;
	e_end = CFG_KERN_ADDR + count;
	switch(image_type)
	{
	case FIRMWARE_TYPE:
	printf("Upgrade linux kernel block !!\n");
#if defined (CFG_ENV_IS_IN_NAND)
				rrc=ranand_erase_write((u8 *)load_address, CFG_KERN_ADDR-CFG_FLASH_BASE, copysize);
#elif defined (CFG_ENV_IS_IN_SPI)
				rrc=raspi_erase_write((u8 *)load_addr, CFG_KERN_ADDR-CFG_FLASH_BASE, copysize);

#else //CFG_ENV_IS_IN_FLASH
				e_end = CFG_KERN_ADDR + copysize;
				if (0 != get_addr_boundary(&e_end))
					break;
				printf("Erase linux kernel block !!\n");
				printf("From 0x%X To 0x%X\n", CFG_KERN_ADDR, e_end);
				flash_sect_erase(CFG_KERN_ADDR, e_end);
				rrc = flash_write((uchar *)load_addr, (ulong)CFG_KERN_ADDR, copysize);
#endif
	if (rrc) 
	{
	  printf("done. %d bytes written\n", copysize);
	  //system_reset();
	}
	break;
	case SPI_UBOOT_TYPE:
#if defined(MT7620_ASIC_BOARD)
	printf("MT7620 does not support SPI U-boot Image!\n");
	break;
#endif
	case NOR_UBOOT_TYPE:
#if defined(CFG_ENV_IS_IN_SPI) && !defined(MT7620_ASIC_BOARD)
	if(image_type==NOR_UBOOT_TYPE){
	printf("SPI flash not support NOR U-boot Image!\n");
	break;
	}
#else
	if(image_type==SPI_UBOOT_TYPE){
	printf("NOR flash not support SPI U-boot Image!\n");
	break;
	}
#endif

	printf("Upgrade U-Boot !!\n");
#if defined (CFG_ENV_IS_IN_NAND)
				rrc=ranand_erase_write((u8 *)load_address, CFG_KERN_ADDR-CFG_FLASH_BASE, copysize);
#elif defined (CFG_ENV_IS_IN_SPI)
				rrc=raspi_erase_write((u8 *)load_addr, 0, copysize);

#else //CFG_ENV_IS_IN_FLASH
				e_end = CFG_FLASH_BASE + copysize;
				if (0 != get_addr_boundary(&e_end))
				break;
				flash_sect_protect(0, CFG_FLASH_BASE, e_end);
				printf("Erase U-boot block !!\n");
				printf("From 0x%X To 0x%X\n", CFG_FLASH_BASE, e_end);
				flash_sect_erase(CFG_FLASH_BASE, e_end);
				rrc = flash_write((uchar *)load_addr, (ulong)CFG_FLASH_BASE, copysize);
#endif	
	break;
	case EEPROM_TYPE:
#if defined (CFG_ENV_IS_IN_NAND)
				rrc=ranand_erase_write((u8 *)load_addr, CFG_FACTORY_ADDR-CFG_FLASH_BASE, copysize);
#elif defined (CFG_ENV_IS_IN_SPI)
				rrc=raspi_erase_write((u8 *)load_addr,CFG_FACTORY_ADDR-CFG_FLASH_BASE, copysize);

#else //CFG_ENV_IS_IN_FLASH
				//protect off eeprom
				flash_sect_protect(0, CFG_FACTORY_ADDR, CFG_FACTORY_ADDR+CFG_FACTORY_SIZE-1);
				//erase eeprom
				printf("Erase EEPROM block From 0x%X To 0x%X\n", CFG_FACTORY_ADDR, CFG_FACTORY_ADDR+CFG_FACTORY_SIZE-1);
				flash_sect_erase(CFG_FACTORY_ADDR, CFG_FACTORY_ADDR+CFG_FACTORY_SIZE-1);

				printf("Write EEPROM block From 0x%X To 0x%X\n", CFG_FACTORY_ADDR, CFG_FACTORY_ADDR+CFG_FACTORY_SIZE-1);				
				//cp.uboot            
				rrc = flash_write((uchar *)load_addr, (ulong)CFG_FACTORY_ADDR, count);
				flash_sect_protect(1, CFG_FACTORY_ADDR, CFG_FACTORY_ADDR+CFG_FACTORY_SIZE-1);
#endif		
	break;
	}
return 0;
}
