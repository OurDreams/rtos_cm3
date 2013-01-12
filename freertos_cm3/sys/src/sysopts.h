/**
 ******************************************************************************
 * @file       sysopts.h
 * @brief      系统配置文件.
 * @details    This file including all API functions's declare of sysopts.h.
 *
 ******************************************************************************
 */
 

#ifndef _SYSOPTS_H_
#define _SYSOPTS_H_
/*-----------------------------------------------------------------------------
Section: Includes
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
Section: Macro Definitions
-----------------------------------------------------------------------------*/
#define MEM_BOUNDS_CHECK
#define MEM_CHECK_VALUE 2000


/**
 *  定义处理器的最大中断数量
 */
#define MAX_INT_COUNT 103

#if MAX_INT_COUNT > 103
#error "超出最大中断数"
#endif

/**
 *  定义CPU的主频72MHZ
 */
#define SYS_CPU_CLOCK_HZ  72000000

/**
 *  定义时钟周期终端的频率
 */
#define  SYS_TICKS_PER_SECOND       100

/**
 *  定义操作系统任务的最高优先级
 */
#define  MAX_TASK_PRIORITIES        8

#define MAXTASKNUM 32     ///<  守护任务监控的最大任务数为32，注意该值不能大于32
#define MAXCHECKTIME 300 ///< 守护任务监测的时间周期，单位秒
#define MAXRESETDELAY 120  ///< 守护任务重启前等待其他任务安全退出的时间




#endif
/*--------------------------End of sysopts.h----------------------------*/
