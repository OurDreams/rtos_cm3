#include <stdio.h>
#include <string.h>
#include <types.h>
#include <intLib.h>
#include <taskLib.h>
#include <memLib.h>
#include <shell.h>

extern char heap_low; /* Defined by the linker */
extern char cstack_top;

extern void sysHwInit0(void);
extern void vTaskStartScheduler( void );
/* Two magic cookies used to detect data section misalignment */
#define TRAP_VALUE_1    0x12348765
#define TRAP_VALUE_2    0x5a5ac3c3
static volatile uint32_t   trapValue1  = TRAP_VALUE_1;
static volatile uint32_t   trapValue2  = TRAP_VALUE_2;

const char_t const * the_rtos_logo =
#if 0
        " \\|/\n"
        "--O-- The CM3 RTOS is starting...\n"
        " /|\\\n";
#else
    "\r\r\r _____    _____   _____    _____  \n"
    "|  _  \\  |_   _| /  _  \\ /  ___/ \n"
    "| |_| |    | |   | | | | | |___  \n"
    "|  _  /    | |   | | | | \\___  \\ \n"
    "| | \\ \\    | |   | |_| |  ___| | \n"
    "|_|  \\_\\   |_|   \\_____/ /_____/ \n";
#endif

#define  ROOTSTACKSIZE  (1000)      /* 定义root task堆栈大小 */

static void
rootTask(void *p_arg)
{
    //printf version
    printf("....STM32F103 APP START...\n");
    printf(the_rtos_logo);

    shell_init();

    taskDelete(NULL);
}

/*
 * 入口函数
 * 1. CPU相关初始化
 * 2. 系统滴答初始化
 * 3.
 * 4. 创建root任务
 */
int32_t main(void)
{
    /*
     * This trap will catch improper loading of the data section.
     * We check the magic cookie values to make sure the data section is
     * in the expected memory location. We do not want
     * to proceed further if the data segment is not correct.
     *
     * Data section misalignment can occur when there is a change in tool
     * chain, build rules, compiler, host utilites,  etc.
     */

    while (trapValue1 != TRAP_VALUE_1 || trapValue2 != TRAP_VALUE_2)
    {
    /* infinite loop */;
    }
    //关中断 设系统主频
    //中断向量表初始化
    //IO初始化TTY初始化
    sysHwInit0();

    if (OK != mem_init((unsigned long)&heap_low, (unsigned long)(&cstack_top - 0x200)))
    {
        printf("mem_init err!\n");
        while(1);
    }

    /*起根任务，做时钟节拍初始化*/
    (void)taskSpawn((const signed char*)"root", 1, ROOTSTACKSIZE, (OSFUNCPTR)rootTask,0);


    /* Start scheduler */
    vTaskStartScheduler();

    /* We should never get here as control is now taken by the scheduler */
    for( ;; );


    return 0;
}
