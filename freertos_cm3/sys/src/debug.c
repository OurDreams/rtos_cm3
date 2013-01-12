/**
 ******************************************************************************
 * @file      debug.c
 * @brief     调试模块的实现.
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
//#include <intLib.h>
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
 * @brief      系统断言调试输出.
 * @param[in]  funcname : 函数名称
 * @param[in]  line          : 代码行数
 *
 * @details
 *      通过SYS_ASSERT宏进行调用，在调试端口输出断言信息，并调用
 *      事件记录的钩子函数。该函数将终止原有任务的继续执行。
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
 * @brief      系统错误调试输出.
 * @param[in]  funcname : 函数名称
 * @param[in]  line     : 代码行数
 *
 * @details
 *      通过SYS_ERROR宏进行调用，在调试端口输出错误信息，并调用
 *      事件记录的钩子函数。该函数不会终止原有任务的继续执行。
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


/*----------------------------debug.c--------------------------------*/
