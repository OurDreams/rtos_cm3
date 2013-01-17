/**
 ******************************************************************************
 * @file      debug.c
 * @brief     ����ģ���ʵ��.
 * @details   This file including all API functions's 
 *            implement of debug.c.	
 *
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
Section: Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <types.h>
#include <taskLib.h>
#include <intLib.h>
#include <debug.h>

/*-----------------------------------------------------------------------------
Section: Type Definitions
-----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
Section: Constant Definitions
-----------------------------------------------------------------------------*/
extern VOIDFUNCPTR _func_evtLogAssertHook;


/*-----------------------------------------------------------------------------
Section: Global Variables
-----------------------------------------------------------------------------*/
int sysDebugMask = DBG_INFO;

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

/**
 *******************************************************************************
 * @brief      ϵͳ���Ե������.
 * @param[in]  funcname : ��������
 * @param[in]  line          : ��������
 *
 * @details
 *      ͨ��SYS_ASSERT����е��ã��ڵ��Զ˿����������Ϣ��������
 *      �¼���¼�Ĺ��Ӻ������ú�������ֹԭ������ļ���ִ�С�
 *      SYS_ASSERT(expression);
 * @note
 *******************************************************************************
 */
extern void sysAssert(const char* funcname,int line)
{
    printf("SYS_ASSERT: \n");
    printf("occurred in function:%s,line:%d \n",funcname,line);
    printf("taskname: %s \n",taskName(NULL));
    if (_func_evtLogAssertHook != NULL)
    {
        _func_evtLogAssertHook(funcname,line);
    }
    intLock();
    while(1);

}

/**
 *******************************************************************************
 * @brief      ϵͳ����������.
 * @param[in]  funcname : ��������
 * @param[in]  line     : ��������
 *
 * @details
 *      ͨ��SYS_ERROR����е��ã��ڵ��Զ˿����������Ϣ��������
 *      �¼���¼�Ĺ��Ӻ������ú���������ֹԭ������ļ���ִ�С�
 *      SYS_ERROR( expression);
 * @note
 *******************************************************************************
 */
extern void sysError(const char* funcname,int line)
{
    printf("SYS_ERROR: \n");
    printf("occurred in function:%s,line:%d \n",funcname,line);
    printf("taskname: %s \n",taskName(NULL));

    if (_func_evtLogAssertHook != NULL)
    {
        _func_evtLogAssertHook(funcname,line);
    }

}

/**
 ******************************************************************************
 * @brief
 * @param[in]  None
 * @param[out] None
 * @retval     None
 *
 * @details
 *
 * @note
 ******************************************************************************
 */
extern void
printbuffer(char_t* format,
            uint8_t* buffer,
            int32_t len)
{
    (void)printf(format);
    for (int32_t i = 0; i < len; i++)
    {
        (void)printf("%02X ", *(buffer + i));
    }
    (void)printf("\r\n");
}
/*----------------------------debug.c--------------------------------*/
