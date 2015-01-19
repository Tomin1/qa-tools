/* ------------------------------------------------------------------------- *
* Copyright (C) 2015 Jolla Ltd.
* Contact: Matti Kosola <matti.kosola@jolla.com>
* License: GPLv2
* ------------------------------------------------------------------------- */

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/reboot.h>
#include <sys/syscall.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
    /* supported parameters */
    char *str1 = "bootloader";
    char *str2 = "recovery";

    if ( argc != 2 || ( strcmp(str1, argv[1]) != 0 && strcmp(str2, argv[1]) != 0) )
    {
        printf("Usage: \"%s bootloader\" or \"%s recovery\"\n", argv[0], argv[0]);
        return (EXIT_SUCCESS);
    }

    pid_t parent_pid = getppid();

    pid_t pid = fork();

    if (pid < 0)
    {
        fprintf (stderr, "Forking failed!\n");
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        pause();
        exit(EXIT_SUCCESS);
    }

    setsid();

    if (parent_pid > 1)
    {
        kill(parent_pid,SIGKILL);
    }
        
    sync();
    sleep(2);
    syscall(__NR_reboot, LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2,
            LINUX_REBOOT_CMD_RESTART2, argv[1]);
    return EXIT_SUCCESS;
}
