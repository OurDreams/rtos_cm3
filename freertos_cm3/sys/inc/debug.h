/**
 ******************************************************************************
 * @file       debug.h
 * @brief      API include file of debug.h.
 * @details    This file including all API functions's declare of debug.h.
 *
 ******************************************************************************
 */
 
#ifndef _DEBUG_H_
#define _DEBUG_H_
/*-----------------------------------------------------------------------------
Section: Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>

/*-----------------------------------------------------------------------------
Section: Macro Definitions
-----------------------------------------------------------------------------*/

/** lower two bits indicate debug level
 * - 0 all
 * - 1 warning
 * - 2 serious
 * - 3 severe
 */
#define DBG_INFO            0x00    /*  normal information like function call ... */
#define DBG_WARNING         0x01    /*  bad chec  ksums, dropped packets, ... */
#define DBG_SERIOUS         0x02    /*  memory allocation failures, ... */
#define DBG_SEVERE          0x03    /*   */

#define DBG_MASK_LEVEL      0x03

/** flag for SYS_DEBUG to enable that debug message */
#define SYS_DBG_ON          0x80U
/** flag for SYS_DEBUGF to disable that debug message */
#define SYS_DBG_OFF         0x00U



#ifndef SYS_DEBUG
#define SYS_DEBUG(debug,msg) \
      do { \
          if ((debug & DBG_MASK_LEVEL) >= sysDebugMask) {\
              printf msg; }\
      }while(0)




#ifndef SYS_ASSERT
#define SYS_ASSERT(assertion) \
        {if (assertion) sysAssert(__FUNCTION__,__LINE__);}
#endif

#ifndef SYS_ERROR
#define SYS_ERROR(expression)\
        {if (expression) { \
            sysError(__FUNCTION__,__LINE__);}\
        }
#endif



#endif
extern int sysDebugMask;
extern void sysAssert(const char* funcname, int line);
extern void sysError(const char* funcname, int line);


#endif /* _DEBUG_H_*/
/*--------------------------End of debug.h----------------------------*/
