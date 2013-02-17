/**
 ******************************************************************************
 * @file      excTest.c
 * @brief     �쳣���Գ���.
 * @details   This file including all API functions's
 *            implement of memtest.c.
 *
 ******************************************************************************
 */


/*------------------------------------------------------------------------------ 
Section: Includes 
------------------------------------------------------------------------------*/
#if 1 //def INCLUDE_EXC_TEST

#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <shell.h>
#include <taskLib.h>
#include <string.h>


/*------------------------------------------------------------------------------ 
Section: Macro Definitions 
------------------------------------------------------------------------------*/ 
/* NONE */ 
 
/*------------------------------------------------------------------------------ 
Section: Private Type Definitions 
------------------------------------------------------------------------------*/ 
/* NONE */ 
 
/*------------------------------------------------------------------------------ 
Section: Global Variables 
------------------------------------------------------------------------------*/ 
#define SHCSR 0xE000ED24
 
/*------------------------------------------------------------------------------ 
Section: Private Variables 
------------------------------------------------------------------------------*/ 
static SEM_ID semExcTst;
static int testid;
static unsigned int * pTst;
FUNCPTR     _func_excTest;
/*------------------------------------------------------------------------------ 
Section: Private Function Prototypes 
------------------------------------------------------------------------------*/ 
/*
 * 1����shell�е���et -1����tExcTest����
 * 2������et 0 ����usage fault
 * 3������et 1 ����bus fault
 * 4������et 2 ���Գ����쳣
 * 5������et 3 ���Զ�ջ���
 * 6������et 4 ����malloc���
 * 7������et 5 ����heap����ͷ�����޸�
 * 8������et 6 ����logMsg��logBuf
 * 9������et 7 �����ֹ������쳣
 *
 *
 */

void testHeapOver()
{
    for (int i=0;i<2000;i++)
    {

        void* p = malloc(100);
        printf("i=%d,p=0x%x \n",i,p);
    }

}

void testMemModify()
{
    uint8_t* p = malloc(1000);
    p+=1000;
    *p = 0xFF;
    *(p+1) = 0xEE;
    free(p);
}

void testStackOver()
{
    /*
     * tExcTest�����ջ�ռ�Ϊ512���ֽ�,ջ�ռ���ʼ��ַ
     * ������TCB���ƿ飬��ջ�ռ��쳣ʱ�����׸���TCB��
     * ���ݣ���������л�ʱ�������޷�������쳣��
     * ����printf���õ�200�ֽ�ջ�ռ䣬��˵�BLEN��Ϊ
     * 300ʱ��������tExcTest��TCB���ݣ���BLEN��Ϊ500
     * ʱ�����޸�ǰһ�������ջ���ݣ����ǰһ���������
     * �쳣��������ջ����¼�Ҳ�ܹ�����
     */
    #define BLEN 500
    uint8_t a[BLEN];
    printf("a[BLEN] addr = 0x%x \n",(unsigned int)a);
    memset(a,0xff,BLEN);

}

void taskloop()
{
    while(1)
    {
        semTake(semExcTst, WAIT_FOREVER);
        switch (testid){
            case 0 : /* usage fault */
                _func_excTest(0);
                break;
            case 1 : /* bus fault */
                pTst = (unsigned int *)0xD00ED000;
                printf("pTst value: %08x \n\r",*pTst);
                break;
            case 2 :
                pTst = 456 / 0;
                printf("pTst value: %08x \n\r",*pTst);
                break;
            case 3 :

                testStackOver();
                break;
            case 4 :
                testHeapOver();
                break;
            case 5 :
                testMemModify();


#if 0
              __asm(
                   "MRS R0  MSP"
                   "LDR R1  =0x01"
                   "MSR R1  FAULTMASK  "
                    );
#endif
                 break;
            case 6 :
                break;
            case 7 :
                *(volatile uint32_t*) (SHCSR) |= 1<<13; //1<<12 1<<13 1<<14 �ֹ������쳣
                break;
            case 8 :
                //test_timer_irq_exec();
                break;
           default:
                printf(".\r\n");
                break;
            }
        
    }

}

void createTask()
{
    semExcTst = semBCreate(0);

    taskSpawn("tExcTest",4,512,(OSFUNCPTR)taskloop,0);
    
}


void exctest(int id)
{
    testid = id;
    semGive(semExcTst);
}
/*------------------------------------------------------------------------------ 
Section: Public Function  
------------------------------------------------------------------------------*/ 

uint32_t do_excTest(cmd_tbl_t * cmdtp, uint32_t argc, uint8_t *argv[])
{   
    int id;

    if (argc != 2) {
        printf ("Usage:\n\r");
        printf ("%s\n\r", cmdtp->usage);
        return 1;
    }

    sscanf((int8_t *)argv[1], "%d", &id);


    if (id == -1)
        createTask();
    else
        exctest(id);

    return 0;
}
SHELL_CMD(
	et,	CFG_MAXARGS,		do_excTest,
 	"et \r\t id(-1,0,1,2) \r\t\t\t\t Test exception handler \n\r"
);

#endif
 
/*------------------------------End of excTest.c---------------------------------*/ 

