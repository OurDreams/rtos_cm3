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

#define  ROOTSTACKSIZE  (1000)      /* ����root task��ջ��С */

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
 * ��ں���
 * 1. CPU��س�ʼ��
 * 2. ϵͳ�δ��ʼ��
 * 3.
 * 4. ����root����
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
    //���ж� ��ϵͳ��Ƶ
    //�ж��������ʼ��
    //IO��ʼ��TTY��ʼ��
    sysHwInit0();

    if (OK != mem_init((unsigned long)&heap_low, (unsigned long)(&cstack_top - 0x200)))
    {
        printf("mem_init err!\n");
        while(1);
    }

    /*���������ʱ�ӽ��ĳ�ʼ��*/
    (void)taskSpawn((const signed char*)"root", 1, ROOTSTACKSIZE, (OSFUNCPTR)rootTask,0);


    /* Start scheduler */
    vTaskStartScheduler();

    /* We should never get here as control is now taken by the scheduler */
    for( ;; );


    return 0;
}
