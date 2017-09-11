
/******************************************************************************
*  Ralink U-boot GPIO funtion
* 	lintel<lintel.huang@gmail.com>
*   GPIO Funtions:
*   gpio_set_dir gpio_set gpio_get 
*      
******************************************************************************/

#include <common.h>
#include <gpio.h>


#if defined(HG255D_BOARD) || defined(HG256_BOARD)
//HG255D
#define RESET_BTN_BIT			GPIO_4
#define WLAN_BTN_BIT			GPIO_10
#define WPS_BTN_BIT			GPIO_0
#define POWER_LED_BIT			GPIO_8
#define READY_LED_BIT			POWER_LED_BIT
#define HG255D_GPIO_LED_WPS		GPIO_12
#define HG255D_GPIO_LED_WLAN		GPIO_9

//rt-n13u
#elif defined(RT_N13U_BOARD)
#define RESET_BTN_BIT			GPIO_10	
#define WPS_BTN_BIT			GPIO_0
#define POWER_LED_BIT			GPIO_7
#define READY_LED_BIT			POWER_LED_BIT

//ZBT-AP8100RT
#elif defined(ZBT_AP8100RT_BOARD)
//#define RESET_BTN_BIT			GPIO_0
#define RESET_BTN_BIT			GPIO_14
#define POWER_LED_BIT			GPIO_7
#define READY_LED_BIT			POWER_LED_BIT

//BL-RT3052
#elif defined(BL_RT3052_BOARD)
#define RESET_BTN_BIT			GPIO_0
#define SYS_LED_BIT			GPIO_14
#define READY_LED_BIT			SYS_LED_BIT

//ZBT AP2001
#elif defined(AP2001_BOARD)
#define RESET_BTN_BIT			GPIO_10
#define SYS_LED_BIT			GPIO_13
#define READY_LED_BIT			SYS_LED_BIT


//ZBT-WR83052RT
#elif defined(ZBT_WR83052RT_BOARD)
//#define RESET_BTN_BIT			GPIO_0
#define RESET_BTN_BIT			GPIO_10
#define SEC_LED_BIT			GPIO_14
#define READY_LED_BIT			SEC_LED_BIT

//WCR-HP-GN-CH
#elif defined(WCR_GN_BOARD) 
#define RESET_BTN_BIT			GPIO_10	
#define WPS_BTN_BIT			GPIO_0
#define DIAG_LED_BIT			GPIO_7
#define READY_LED_BIT			DIAG_LED_BIT

//FON2405E
#elif defined(FON2405E_BOARD) 
#define RESET_BTN_BIT			GPIO_10	
#define LAN_LED_BIT			GPIO_11
#define WPS_LED_BIT			GPIO_14
#define READY_LED_BIT			LAN_LED_BIT

//WAP120NF
#elif defined(WAP120NF_BOARD)
#define RESET_BTN_BIT			GPIO_10	
#define WLAN_BTN_BIT			GPIO_13
#define WPS_BTN_BIT			GPIO_0
#define POWER_LED_BIT			GPIO_9
#define READY_LED_BIT			POWER_LED_BIT

//FWR-601
#elif defined(FWR601_BOARD)
#define RESET_BTN_BIT			GPIO_10	
#define POWER_LED_BIT			GPIO_14
#define READY_LED_BIT			POWER_LED_BIT

//ZBT_WR8305RT_BOARD
#elif defined(ZBT_WR8305RT_BOARD)
#define RESET_BTN_BIT			GPIO_1
#define SYS_LED_BIT			GPIO_0
#define READY_LED_BIT			SYS_LED_BIT
#elif defined(RY1_BOARD) || defined(WR856N_BOARD)
#define RESET_BTN_BIT			GPIO_1
#define SYS_LED_BIT			GPIO_0
#define READY_LED_BIT			SYS_LED_BIT
//AP8101RT
#elif defined(ZBT_AP8101RT_BOARD)
#define RESET_BTN_BIT			GPIO_10
#define WPS_BTN_BIT			GPIO_0  /* AP8101-RT-B use GPIO0 for ResetBTN*/
#define SYS_LED_BIT			GPIO_14
#define READY_LED_BIT			SYS_LED_BIT
//AP8102RT
#elif defined(ZBT_AP8102RT_BOARD)
#define RESET_BTN_BIT			GPIO_0
#define SYS_LED_BIT			GPIO_1
#define READY_LED_BIT			SYS_LED_BIT
//MW305R
#elif defined(MW305R_BOARD)
#define RESET_BTN_BIT			GPIO_1
#define SYS_LED_BIT			GPIO_2
#define READY_LED_BIT			SYS_LED_BIT
//DIR_620
#elif defined(DIR_620_BOARD)
#define RESET_BTN_BIT			GPIO_1
#define WPS_BTN_BIT			GPIO_2 
#define SYS_LED_BIT			GPIO_0
#define READY_LED_BIT			SYS_LED_BIT
//PBX220_BOARD PBX230_BOARD
#elif defined(PBX220_BOARD) || defined(PBX230_BOARD)
#define RESET_BTN_BIT			GPIO_1
#define WPS_BTN_BIT			GPIO_2 
#define SYS_LED_BIT			GPIO_0
#define READY_LED_BIT			SYS_LED_BIT
//MT7620A EVB
#elif defined(MT7620A_EVB_BOARD)
//#define RESET_BTN_BIT			GPIO_13
#define RESET_BTN_BIT			GPIO_2
#define WPS_BTN_BIT			GPIO_13 
#define SYS_LED_BIT			GPIO_9
#define READY_LED_BIT			SYS_LED_BIT
//RY2
#elif defined(RY2_BOARD)
#define RESET_BTN_BIT			GPIO_11
#define SYS_LED_BIT			GPIO_14
#define READY_LED_BIT			SYS_LED_BIT
//BR100
#elif defined(BR100_BOARD)
#define WPS_BTN_BIT			GPIO_14
#define RESET_BTN_BIT			GPIO_13
#define SYS_LED_BIT			GPIO_9
#define READY_LED_BIT			SYS_LED_BIT
//M100
#elif defined(M100_BOARD)
#define RESET_BTN_BIT			GPIO_13
#define SYS_LED_BIT			GPIO_9
#define READY_LED_BIT			SYS_LED_BIT
//AP7620A_BOARD
#elif defined(AP7620A_BOARD)
#define RESET_BTN_BIT			GPIO_2
#define SYS_LED_BIT			GPIO_9
#define READY_LED_BIT			SYS_LED_BIT
#else
//WCR-HP-GN-CH
#define RESET_BTN_BIT			GPIO_10	
#define WPS_BTN_BIT			GPIO_0
#define POWER_LED_BIT			GPIO_13
#define READY_LED_BIT			POWER_LED_BIT
#endif

#define SYSCFG_OFFSET		0x10
#define UARTF_PCM_MODE_SHIFT	6

/*
6 R/W UARTF_PCM_MODE
0: Set 4 of UART-Full pins as normal UART function
1: Set 4 of UART-Full pins as normal PCM function
1��b0
*/
#define GPIOMODE_OFFSET		0x60
#define UARTF_GPIO_MODE_SHIFT	1
/*
1 R/W UARTF_GPIO_MODE
0:Normal Mode
1:GPIO Mode
Control GPIO[6:3]
100b1
*/
void gpio_init();
void LEDON(void);
void LEDOFF(void);

void uart_pcm_mode(unsigned x)
{
	unsigned long int reg_val;

	reg_val = le32_to_cpu(*(volatile u_long *)(SYSCTR_ADDR + SYSCFG_OFFSET));

	if (x == 0)
		reg_val &= ~(1<<UARTF_PCM_MODE_SHIFT);
	else if(x == 1)
		reg_val |= (1<<UARTF_PCM_MODE_SHIFT) ;

	*(volatile u_long *)(SYSCTR_ADDR + SYSCFG_OFFSET) = le32_to_cpu(reg_val);

}


void uart_gpio_mode(unsigned x)
{
	unsigned long int reg_val;

	reg_val = le32_to_cpu(*(volatile u_long *)(SYSCTR_ADDR +GPIOMODE_OFFSET));

	if (0 == x)
		reg_val &=~(1<<UARTF_GPIO_MODE_SHIFT);
	else if(1 == x)
		reg_val |= (1<<UARTF_GPIO_MODE_SHIFT);

	*(volatile u_long *)(SYSCTR_ADDR + GPIOMODE_OFFSET) = le32_to_cpu(reg_val);

}


/*
set the direction of the gpio
0:input
1:output
*/

void set_gpio_dir(unsigned int dir,unsigned int nGpio)
{
	unsigned long reg_val;
#ifndef MT7621_ASIC_BOARD
	if (0 == dir)
	{
		le32_to_cpu(*(volatile u_long *)REG_PIODIR)&=~nGpio;
		*(volatile u32 *)(REG_PIODIR) &= cpu_to_le32(~nGpio);
		*(volatile u32 *)(REG_PIODIR) &= cpu_to_le32(0);
	}
	else 
		if(1 == dir)
		{
			le32_to_cpu(*(volatile u_long *)REG_PIODIR)|=nGpio;
			*(volatile u32 *)(REG_PIODIR) |= cpu_to_le32(nGpio);
		}
#endif
}

//gpio funtions
void set_gpio_dirout(unsigned int pin,unsigned int dir)
{
	printf("GPIO Pin%d set to %s.\n",pin,dir==0?"input":"output");
	volatile u32 * reg = 0;
	u32 data;

	if	(pin < 24)	{ reg = (volatile u32 *)REG_PIODIR; }
	else return -1;

	data = le32_to_cpu(*reg);
	if (!dir)	data |= (1 << pin);
	else		data &= ~(1 << pin);

	*reg = cpu_to_le32(data);
}


void gpio_set(unsigned int pin,unsigned int value)
{
	printf("GPIO Pin%d set to %s.\n",pin,value==0?"low":"high");
	volatile u32 * reg = 0;
	u32 data;

	if	(pin < 24)	{ reg = (volatile u32 *)REG_PIODIR; }
	else return -1;

	data = le32_to_cpu(*reg);
	if (!value)	data |= (1 << pin);
	else		data &= ~(1 << pin);

	*reg = cpu_to_le32(data);
	return 0;
}

int gpio_get(unsigned int pin)
{
	volatile u32 * reg = 0;
	u32 data;

	if(pin < 24){ reg = (volatile u32 *)REG_PIODATA; }
	else return -1;

	data = le32_to_cpu(*reg);
	data &= (1<<pin);
	printf("GPIO Pin%d is %s.\n",pin,(data ? "High" : "Low"));
	return data ? 1 : 0;
}

void gpio_init()
{
        unsigned long gpiomode;

	printf("\nGPIO Init:\n");	// tmp test
        gpiomode = le32_to_cpu(*(volatile u32 *)(REG_GPIOMODE));
	gpiomode &= ~(0x7<<2);  //clear bit[2:4]UARTF_SHARE_MODE
#if defined(ZBT_AP8100RT_BOARD)
	printf("\tUARTF_SHARE_MODE:GPIO+UART\n");
        gpiomode |= (0x5<<2); //Only RX TX CTS_N RTS_N not work in GPIO Mode. GPIO+UART
#elif defined(M100_BOARD)
	printf("\tUARTF_SHARE_MODE:GPIO+I2S\n");
        gpiomode |= (0x6<<2);  //Only I2S interface not work in GPIO Mode. GPIO+I2S
#else
	printf("\tUARTF_SHARE_MODE:GPIO\n");
        gpiomode |= RALINK_GPIOMODE_DFT;
#endif

        *(volatile u32 *)(REG_GPIOMODE) = cpu_to_le32(gpiomode);
#if defined(HG255D_BOARD) || defined(HG256_BOARD)	
	printf("\tSPI_GPIO_MODE:GPIO\n");
        gpiomode = le32_to_cpu(*(volatile u32 *)(REG_GPIOMODE));
        gpiomode &= ~0x2;  //clear bit[6] SPI_GPIO_MODE
        gpiomode |= 0x2;
        *(volatile u32 *)(REG_GPIOMODE) = cpu_to_le32(gpiomode);
#endif
#if defined(HG255D_BOARD) || defined(HG256_BOARD) || defined(MW305R_BOARD) || defined(DIR_620_BOARD) \
	|| defined(ZBT_WR8305RT_BOARD) || defined(ZBT_AP8102RT_BOARD)|| defined(AP2001_BOARD)|| defined(RY1_BOARD) \
	|| defined(WR856N_BOARD) || defined(AP7620A_BOARD) || defined(PBX220_BOARD) \
	|| defined(PBX230_BOARD) || defined(MT7620A_EVB_BOARD) || defined(BR100_BOARD) 
	
	printf("\tI2C_GPIO_MODE:GPIO\n");
        gpiomode = le32_to_cpu(*(volatile u32 *)(REG_GPIOMODE));
        gpiomode &= ~0x1;  //clear bit[1] I2C_GPIO_MODE
        gpiomode |= 0x1;
        *(volatile u32 *)(REG_GPIOMODE) = cpu_to_le32(gpiomode);
#endif

#if defined(RY2_BOARD)
	printf("\tNFI_GPIO_MODE:GPIO\n");
        gpiomode = le32_to_cpu(*(volatile u32 *)(REG_GPIOMODE));
        gpiomode &= ~(0x3<<18);  //clear bit[1] NFI_GPIO_MODE
        gpiomode |= (0x2<<18);
        *(volatile u32 *)(REG_GPIOMODE) = cpu_to_le32(gpiomode);	
#endif

//add luo
// setup PA --> gpio mode
#if defined(MT7620A_EVB_BOARD)
        gpiomode = le32_to_cpu(*(volatile u32 *)(REG_GPIOMODE));
        gpiomode &= ~(0x1<<20); 
        gpiomode |= (0x1<<20);
        *(volatile u32 *)(REG_GPIOMODE) = cpu_to_le32(gpiomode);	


        gpiomode = le32_to_cpu(*(volatile u32 *)(REG_PIODIR));
        gpiomode |= (1<<20);
        gpiomode |= (1<<21);
        *(volatile u32 *)(REG_PIODIR) = cpu_to_le32(gpiomode);	

        gpiomode = le32_to_cpu(*(volatile u32 *)(REG_PIODATA));
        gpiomode &= ~(0x1<<20);
        gpiomode &= ~(0x1<<21);
        *(volatile u32 *)(REG_PIODATA) = cpu_to_le32(gpiomode);	
#endif


	
#if defined(MT7620A_EVB_BOARD) || defined(RY2_BOARD)
	led_control(0);
#endif
	
#if defined(PBX230_BOARD) || defined(M100_BOARD)
	printf("\tGE1_GPIO_MODE:GPIO\n");
        gpiomode = le32_to_cpu(*(volatile u32 *)(REG_GPIOMODE));
        gpiomode &= ~(1<<9);  //clear bit[1] I2C_GPIO_MODE
        gpiomode |= (1<<9);
        *(volatile u32 *)(REG_GPIOMODE) = cpu_to_le32(gpiomode);
	
	printf("\tGE2_GPIO_MODE:GPIO\n");
        gpiomode = le32_to_cpu(*(volatile u32 *)(REG_GPIOMODE));
        gpiomode &= ~(1<<10);  //clear bit[1] I2C_GPIO_MODE
        gpiomode |= (1<<10);
        *(volatile u32 *)(REG_GPIOMODE) = cpu_to_le32(gpiomode);
#endif
#if defined(PBX230_BOARD)
// 	printf("\nSLIC:FXS+FXO \n");	
// 	/* On PBX30,GPIO26 GPIO25 control the FXS/FXO config,so we swithc to FXS/FXO after power on */
// 	*(volatile u_long *)(PRGIO_ADDR + 0x4c)|= (1<<(26-24));
// 	*(volatile u_long *)(PRGIO_ADDR + 0x48) |= (1<<(26-24));
// 	
// 	*(volatile u_long *)(PRGIO_ADDR + 0x4c)|= (1<<(25-24));	
// 	*(volatile u_long *)(PRGIO_ADDR + 0x48) |= (1<<(25-24));
	
	led_control(0);
#endif	
	

#if defined(RESET_BTN_BIT)
        set_gpio_dir(0,RESET_BTN_BIT);
#endif
#if defined(WPS_BTN_BIT)
        set_gpio_dir(0,WPS_BTN_BIT);
#endif
#if defined(WLAN_BTN_BIT)
        set_gpio_dir(0,WLAN_BTN_BIT);
#endif
        set_gpio_dir(1,READY_LED_BIT);

	printf("GPIO_MODE_REG:0x%x\n",le32_to_cpu(*(volatile u_long *)REG_GPIOMODE));
	printf("ReadyLED Bit:0x%x\n",READY_LED_BIT);
	
}

void led_control(int state)
{
#if defined(MT7620_ASIC_BOARD)
#if defined(ZBT_WR8305RT_BOARD) 
// || defined(AP7620A_BOARD) /*ZBT_WR83052RT_BOARD*/
// LED use GPIO38 SPI_HOLD
	if(1 == state)	// off
	{
		*(volatile u_long *)(PRGIO_ADDR + 0x4c)|= (1<<14);
		*(volatile u_long *)(PRGIO_ADDR + 0x48) |= (1<<14);
//		set_gpio_dir(0,READY_LED_BIT);//set the corresponding gpio pin as output
	}
	else	// on
	{
		le32_to_cpu(*(volatile u_long *)(PRGIO_ADDR + 0x4c))|=(1<<14);
		
		le32_to_cpu(*(volatile u_long *)(PRGIO_ADDR + 0x48))&=~(1<<14);
//		le32_to_cpu(*(volatile u_long *)REG_PIOPOL)|=READY_LED_BIT;
	}
#elif defined(AP7620A_BOARD) || defined(RY2_BOARD)
	if(1 == state)	// off
	{
		le32_to_cpu(*(volatile u_long *)REG_PIODATA)|=READY_LED_BIT;
		le32_to_cpu(*(volatile u_long *)REG_PIOPOL)&=~READY_LED_BIT;
//		set_gpio_dir(0,READY_LED_BIT);//set the corresponding gpio pin as output
	}
	else	// on
	{
		set_gpio_dir(1,READY_LED_BIT);//set the corresponding gpio pin as output
		le32_to_cpu(*(volatile u_long *)REG_PIODATA)&=~READY_LED_BIT;
//		le32_to_cpu(*(volatile u_long *)REG_PIOPOL)|=READY_LED_BIT;
	}
#elif defined(PBX220_BOARD)
// LED use GPIO39 SPI_HOLD
	if(1 == state)	// off
	{
		*(volatile u_long *)(PRGIO_ADDR + 0x4c)|= (1<<15);
		*(volatile u_long *)(PRGIO_ADDR + 0x48) |= (1<<15);
//		set_gpio_dir(0,READY_LED_BIT);//set the corresponding gpio pin as output
	}
	else	// on
	{
		le32_to_cpu(*(volatile u_long *)(PRGIO_ADDR + 0x4c))|=(1<<15);
		
		le32_to_cpu(*(volatile u_long *)(PRGIO_ADDR + 0x48))&=~(1<<15);
//		le32_to_cpu(*(volatile u_long *)REG_PIOPOL)|=READY_LED_BIT;
	}
#elif defined(PBX230_BOARD)
	if(1 == state)	// off
	{
		*(volatile u_long *)(PRGIO_ADDR + 0x4c)|= (1<<9);
		*(volatile u_long *)(PRGIO_ADDR + 0x48) |= (1<<9);
//		set_gpio_dir(0,READY_LED_BIT);//set the corresponding gpio pin as output
	}
	else	// on
	{
		le32_to_cpu(*(volatile u_long *)(PRGIO_ADDR + 0x4c))|=(1<<9);
		
		le32_to_cpu(*(volatile u_long *)(PRGIO_ADDR + 0x48))&=~(1<<9);
//		le32_to_cpu(*(volatile u_long *)REG_PIOPOL)|=READY_LED_BIT;
	}
#else
 	if(1 == state)	// off
 	{
 		*(volatile u_long *)(PRGIO_ADDR + 0x9c)|= 0x1;
 		*(volatile u_long *)(PRGIO_ADDR + 0x98) |= 0x1;
 //		set_gpio_dir(0,READY_LED_BIT);//set the corresponding gpio pin as output
 	}
 	else	// on
 	{
 		le32_to_cpu(*(volatile u_long *)(PRGIO_ADDR + 0x9c))|=0x1;
 		
 		le32_to_cpu(*(volatile u_long *)(PRGIO_ADDR + 0x98))&=~0x1;
 //		le32_to_cpu(*(volatile u_long *)REG_PIOPOL)|=READY_LED_BIT;
 	}
#endif /* ZBT_WR8305RT_BOARD */
#else
#ifndef MT7621_ASIC_BOARD
	if(1 == state)	// off
	{
		le32_to_cpu(*(volatile u_long *)REG_PIODATA)|=READY_LED_BIT;
		le32_to_cpu(*(volatile u_long *)REG_PIOPOL)&=~READY_LED_BIT;
//		set_gpio_dir(0,READY_LED_BIT);//set the corresponding gpio pin as output
	}
	else	// on
	{
		set_gpio_dir(1,READY_LED_BIT);//set the corresponding gpio pin as output
		le32_to_cpu(*(volatile u_long *)REG_PIODATA)&=~READY_LED_BIT;
//		le32_to_cpu(*(volatile u_long *)REG_PIOPOL)|=READY_LED_BIT;
	}
#endif
#endif
}

unsigned long detect_button(void)
{
	unsigned long tmp0;
	unsigned long tmp3, tmp1, tmp2;

	tmp0 = le32_to_cpu(*(volatile u_long *)REG_PIODATA);
		
#if 0
	tmp1 = le32_to_cpu(*(volatile u_long *)REG_PIODIR);
	tmp2 = le32_to_cpu(*(volatile u_long *)REG_PIOPOL);
	
	printf("before LEDON:\n");	 // tmp test
	printf("data:%x, dir:%x, pol:%x\n", tmp0, tmp1, tmp2);

	printf("test LEDON\n");
	LEDON();
	udelay(2000000);

	printf("test LEDOFF\n");
	LEDOFF();

	udelay(2000000);
	printf("test LEDON\n");
	LEDON();
	
	tmp0 = le32_to_cpu(*(volatile u_long *)REG_PIODATA);
	tmp1 = le32_to_cpu(*(volatile u_long *)REG_PIODIR);
	tmp2 = le32_to_cpu(*(volatile u_long *)REG_PIOPOL);
	printf("after LEDON:\n");	 // tmp test
	printf("data:%x, dir:%x, pol:%x\n", tmp0, tmp1, tmp2);
#endif

	if(!(tmp0 & RESET_BTN_BIT))
	{/*reset button pressed*/
		printf("\nReset button pressed!\n");
		return 1;	// disable for tmp
		
	}
#if defined(WLAN_BTN_BIT)
	else if(!(tmp0 & WLAN_BTN_BIT))
	{/*WLAN button pressed*/
			printf("\nWLAN button pressed!\n");
			return 2;
	}
#endif
#if defined(WPS_BTN_BIT)
	else if(!(tmp0 & WPS_BTN_BIT))
	{/*WPS button pressed*/
			printf("\nWPS button pressed!\n");
			return 3;
	}
#endif
	else 
	{
		return 0;
	}
}

void LEDON(void)
{
	led_control(0);
}

void LEDOFF(void)
{
	led_control(1);	// disable for tmp
}
