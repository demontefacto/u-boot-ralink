#include <common.h>
#include <command.h>
#include <gpio.h>

int do_ledon(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
int do_ledoff(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);

U_BOOT_CMD(
    ledon, 1, 1, do_ledon,
	"ledon\t -set led on\n",
	NULL
);

U_BOOT_CMD(
    ledoff, 1, 1, do_ledoff,
	"ledoff\t -set led off\n",
	NULL
);


int do_ledon(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    LEDON();

    return 0;
}

int do_ledoff(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    LEDOFF();

    return 0;
}


