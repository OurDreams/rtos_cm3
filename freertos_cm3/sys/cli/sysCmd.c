/**
 ******************************************************************************
 * @file      sysCmd.c
 * @brief     系统命令行接口实现
 *
 * @copyright      Copyright(C), 2008-2012,Sanxing Electric Co.,Ltd.
 */
 
/*-----------------------------------------------------------------------------
Section: Includes
-----------------------------------------------------------------------------*/
#include <types.h>
#include <shell.h>
//#include <sxLib.h>

/*-----------------------------------------------------------------------------
Section: Type Definitions
-----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
Section: Constant Definitions
-----------------------------------------------------------------------------*/
/* NONE */ 

/*-----------------------------------------------------------------------------
Section: Global Variables
-----------------------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      硬件复位函数，在sysLib.c中实现
 * @details
 *
 * @note
 * @ingroup group_bsp
 *******************************************************************************
 */
extern void
reboot(void) __attribute__ (( weak ));

/*-----------------------------------------------------------------------------
Section: Local Variables
-----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
Section: Local Function Prototypes
-----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
Section: Function Definitions
-----------------------------------------------------------------------------*/

/*----------------------------SHELL CMD FOR MEM-----------------------------*/

/* Shell cmd for task information */
extern uint32_t vTaskInfo();
uint32_t do_task_info (cmd_tbl_t * cmdtp, uint32_t argc, const uint8_t *argv[])
{
    return vTaskInfo();
}

SHELL_CMD(
    i,  CFG_MAXARGS,        do_task_info,
    "i \r\t\t\t\t Summary of tasks' TCBs\r\n"
);

#if 0
/*SHELL CMD FOR NET*/
uint32_t do_reboot(cmd_tbl_t * cmdtp, uint32_t argc, uint8_t *argv[])
{
    //sysReboot();
    reboot();
    return 1;
}

SHELL_CMD(
    reboot, CFG_MAXARGS,        do_reboot,
    "reboot \r\t\t\t\t Reboot \n"
);

uint32_t do_version(cmd_tbl_t * cmdtp, uint32_t argc, uint8_t *argv[])
{
    printf("SXOS version %s.\n",osVersion());
    printf("Kernel: FreeRTOS V6.1.0\n");
    printf("Build on %s.\n",osBuildTime());
    return 1;
}
SHELL_CMD(
    version, CFG_MAXARGS,        do_version,
    "version \r\t\t\t\t Print OS version information \n"
);
#endif
/*----------------------------sysCmd.c--------------------------------*/
