/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2016; Damm Stanger 
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                      APPLICATION CONFIGURATION
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                           STM32F407	FCUV2	
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : Dammstanger
*********************************************************************************************************
*/

#ifndef  APP_CFG_MODULE_PRESENT
#define  APP_CFG_MODULE_PRESENT
/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/
#define TASK_START_PRIO                          	3u
#define TASK_LED_PRIO                           	30u
#define TASK_SENSOR_PRO_PRIO						11u
#define	TASK_DATALOG_PRIO							20u	
/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define	TASK_START_STK_SIZE                    	512u

#define	TASK_LED_STK_SIZE                      	256u

#define	TASK_SENSOR_PRO_STK_SIZE				200u

#define TASK_DATALOG_STK_SIZE					200u

/*
*********************************************************************************************************
*                  内存警报阈值				TASK STACK SIZES LIMIT
*********************************************************************************************************
*/

#define  TASK_START_STK_SIZE_PCT_FULL             90u		// 百分之%	
#define  TASK_START_STK_SIZE_LIMIT 			(TASK_START_STK_SIZE     * (100u - TASK_START_STK_SIZE_PCT_FULL))    / 100u

#define  TASK_LED_STK_SIZE_PCT_FULL              90u
#define  TASK_LED_STK_SIZE_LIMIT  			(TASK_LED_STK_SIZE      * (100u - TASK_LED_STK_SIZE_PCT_FULL))     / 100u

#define  TASK_SENSOR_PRO_STK_SIZE_PCT_FULL              90u
#define  TASK_SENSOR_PRO_STK_SIZE_LIMIT     (TASK_SENSOR_PRO_STK_SIZE      * (100u - TASK_SENSOR_PRO_STK_SIZE_PCT_FULL))     / 100u

#define  TASK_DATALOG_STK_SIZE_PCT_FULL             90u
#define  TASK_DATALOG_STK_SIZE_LIMIT     (TASK_DATALOG_STK_SIZE    * (100u - TASK_DATALOG_STK_SIZE_PCT_FULL))    / 100u


/*
*********************************************************************************************************
*                                        uC/LIB CONFIGURATION
*********************************************************************************************************
*/

//#define  LIB_MEM_CFG_OPTIMIZE_ASM_EN            DEF_DISABLED
//#define  LIB_MEM_CFG_ARG_CHK_EXT_EN             DEF_DISABLED
//#define  LIB_MEM_CFG_ALLOC_EN                   DEF_DISABLED
//#define  LIB_MEM_CFG_HEAP_SIZE                  (1 * 1024L)

/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/
#ifndef  TRACE_LEVEL_OFF
#define  TRACE_LEVEL_OFF                0
#endif

#ifndef  TRACE_LEVEL_INFO
#define  TRACE_LEVEL_INFO               1
#endif

#ifndef  TRACE_LEVEL_DBG
#define  TRACE_LEVEL_DBG                2
#endif

#define  APP_CFG_TRACE_LEVEL             TRACE_LEVEL_OFF
#define  APP_CFG_TRACE                   printf

#define  BSP_CFG_TRACE_LEVEL             TRACE_LEVEL_OFF
#define  BSP_CFG_TRACE                   printf

#define  APP_TRACE_INFO(x)               ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_CFG_TRACE x) : (void)0)
#define  APP_TRACE_DBG(x)                ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_DBG)   ? (void)(APP_CFG_TRACE x) : (void)0)

#define  BSP_TRACE_INFO(x)               ((BSP_CFG_TRACE_LEVEL  >= TRACE_LEVEL_INFO) ? (void)(BSP_CFG_TRACE x) : (void)0)
#define  BSP_TRACE_DBG(x)                ((BSP_CFG_TRACE_LEVEL  >= TRACE_LEVEL_DBG)  ? (void)(BSP_CFG_TRACE x) : (void)0)





#endif
