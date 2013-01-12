/**
 ******************************************************************************
 * @file       sysopts.h
 * @brief      ϵͳ�����ļ�.
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
 *  ���崦����������ж�����
 */
#define MAX_INT_COUNT 103

#if MAX_INT_COUNT > 103
#error "��������ж���"
#endif

/**
 *  ����CPU����Ƶ72MHZ
 */
#define SYS_CPU_CLOCK_HZ  72000000

/**
 *  ����ʱ�������ն˵�Ƶ��
 */
#define  SYS_TICKS_PER_SECOND       100

/**
 *  �������ϵͳ�����������ȼ�
 */
#define  MAX_TASK_PRIORITIES        8

#define MAXTASKNUM 32     ///<  �ػ������ص����������Ϊ32��ע���ֵ���ܴ���32
#define MAXCHECKTIME 300 ///< �ػ��������ʱ�����ڣ���λ��
#define MAXRESETDELAY 120  ///< �ػ���������ǰ�ȴ���������ȫ�˳���ʱ��




#endif
/*--------------------------End of sysopts.h----------------------------*/
