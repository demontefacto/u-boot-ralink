#define SYSCTR_ADDR	0xB0000000
#define IRQ_ADDR 	0xB0000200
#define PRGIO_ADDR 	0xB0000600
#define GPIO_0                    (0x0001)
#define GPIO_1                    (1<<1)
#define GPIO_2                    (1<<2)
#define GPIO_3                    (1<<3)
#define GPIO_4                    (1<<4)
#define GPIO_5                    (1<<5)
#define GPIO_6                    (1<<6)
#define GPIO_7                    (1<<7)
#define GPIO_8                    (1<<8)
#define GPIO_9                    (1<<9)
#define GPIO_10                   (1<<10)
#define GPIO_11                   (1<<11)
#define GPIO_12                   (1<<12)
#define GPIO_13                   (1<<13)
#define GPIO_14                   (1<<14)
#define GPIO_15                   (1<<15)
#define GPIO_16                   (1<<16)
#define GPIO_17                   (1<<17)
#define GPIO_18                   (1<<18)
#define GPIO_19                   (1<<19)
#define GPIO_20                   (1<<20)
#define GPIO_21                   (1<<21)
#define GPIO_22                   (1<<22)
#define GPIO_23                   (1<<23)

#define REG_PIODIR		(PRGIO_ADDR + 0x24)
#define REG_PIODATA		(PRGIO_ADDR + 0x20)
#define REG_PIOPOL		(PRGIO_ADDR + 0x28)
#define REG_GPIOMODE		(SYSCTR_ADDR + 0x60)
#define RALINK_GPIOMODE_DFT     0x1C

#define REG_INTENA		(IRQ_ADDR + 0x34)
#define REG_INTDIS		(IRQ_ADDR + 0x38)
void set_gpio_dir(unsigned int dir,unsigned int nGpio);

void set_gpio_dirout(unsigned int nGpio,unsigned int dir);
void gpio_set(unsigned int nGpio,unsigned int value);
int gpio_get(unsigned int nGpio);

unsigned long detect_button(void);

void LEDON(void);
void LEDOFF(void);
void led_control(int state);
