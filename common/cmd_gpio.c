#include <common.h>
#include <command.h>
#include <gpio.h>

#if 1
int do_gpio(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);

int do_gpio(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	ulong delay;

	if (argc < 3) {
		printf ("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	if(strncmp(argv[1],"get",3)==0)
	{
	gpio_get(simple_strtoul(argv[2], NULL, 10));
	return 0;
	}
	else if(strncmp(argv[1],"set",3)==0)
	{
	gpio_set(simple_strtoul(argv[2], NULL, 10),simple_strtoul(argv[3], NULL, 10));
	return 0;
	}
	else if(strncmp(argv[1],"dirout",3)==0)
	{
	set_gpio_dirout(simple_strtoul(argv[2], NULL, 10),simple_strtoul(argv[3], NULL, 10));
	 return 0;
	}
	else
	{
		printf ("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	return 0;
}

U_BOOT_CMD(
    gpio, 4, 4, do_gpio,
	"gpio\t -set gpio pins\n",
	"get pins\n"
	"    - get gpio pins status\n"
	"set pins value\n"
	"    - set gpio pins sataus\n"
	"dirout pins in/out\n"
	"    - 0: set gpio  input type(default)\n"
	"    - 1: set gpio output type\n"
);
#endif

int do_gpio_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);

int do_gpio_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
int i;
for(i=0;i<21;i++)
{
 set_gpio_dirout(i,1);

}
#if 0
	ulong delay;

	if (argc < 3) {
		printf ("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	if(strncmp(argv[1],"get",3)==0)
	{
	gpio_get(simple_strtoul(argv[2], NULL, 10));
	return 0;
	}
	else if(strncmp(argv[1],"set",3)==0)
	{
	gpio_set(simple_strtoul(argv[2], NULL, 10),simple_strtoul(argv[3], NULL, 10));
	return 0;
	}
	else if(strncmp(argv[1],"dirout",3)==0)
	{
	 set_gpio_dir(simple_strtoul(argv[3], NULL, 10),simple_strtoul(argv[2], NULL, 10));
	 return 0;
	}
	else
	{
		printf ("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	return 0;
#endif

}

U_BOOT_CMD(
    gpiotest, 4, 4, do_gpio_test,
	"gpiotest\t -test gpio pins\n",
);

