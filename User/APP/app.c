/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                       IAR Development Kits
*                                              on the
*
*                                    STM32F429II-SK KICKSTART KIT
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : YS
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include <includes.h>
#include <os.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 TCB:声明起始任务控制块
*********************************************************************************************************
*/
static OS_TCB AppTaskStartTCB;

static OS_TCB AppTaskLed1TCB;
static OS_TCB AppTaskLed2TCB;

/*
*********************************************************************************************************
*                                                STACKS：声明起始任务的任务堆栈
*********************************************************************************************************
*/
static CPU_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];

static CPU_STK AppTaskLed1Stk [APP_TASK_LED1_STK_SIZE];
static CPU_STK AppTaskLed2Stk [APP_TASK_LED2_STK_SIZE];

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES：声明起始任务函数
*********************************************************************************************************
*/
static void AppTaskStart(void *p_arg);

static void AppTaskLed1(void * p_arg);
static void AppTaskLed2(void * p_arg);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/
int main(void)
{
	OS_ERR  err;

	OSInit(&err);                                               /* Init uC/OS-III.                                      */

	OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                /* Create the start task                                */
							 (CPU_CHAR   *)"App Task Start",
							 (OS_TASK_PTR ) AppTaskStart,
							 (void       *) 0,
							 (OS_PRIO     ) APP_TASK_START_PRIO,
							 (CPU_STK    *)&AppTaskStartStk[0],
							 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10,
							 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE,
							 (OS_MSG_QTY  ) 5u,
							 (OS_TICK     ) 0u,
							 (void       *) 0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
							 (OS_ERR     *)&err);

	OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */	
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/
static void AppTaskStart(void *p_arg)
{
	CPU_INT32U  cpu_clk_freq;
	CPU_INT32U  cnts;
	OS_ERR      err;

 (void)p_arg;

	BSP_Init();                                                 /* Initialize BSP functions                             */
	CPU_Init();

	cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine SysTick reference freq.                    */
	cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;        /* Determine nbr SysTick increments                     */
	OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).              */

	Mem_Init();                                                 /* Initialize Memory Management Module                  */

#if OS_CFG_STAT_TASK_EN > 0u
	OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
	CPU_IntDisMeasMaxCurReset();
#endif

	OSTaskCreate((OS_TCB     *)&AppTaskLed1TCB,                /* Create the Led1 task                                */
							 (CPU_CHAR   *)"App Task Led1",
							 (OS_TASK_PTR ) AppTaskLed1,
							 (void       *) 0,
							 (OS_PRIO     ) APP_TASK_LED1_PRIO,
							 (CPU_STK    *)&AppTaskLed1Stk[0],
							 (CPU_STK_SIZE) APP_TASK_LED1_STK_SIZE / 10,
							 (CPU_STK_SIZE) APP_TASK_LED1_STK_SIZE,
							 (OS_MSG_QTY  ) 5u,
							 (OS_TICK     ) 0u,
							 (void       *) 0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
							 (OS_ERR     *)&err);
							 
	OSTaskCreate((OS_TCB     *)&AppTaskLed2TCB,                /* Create the Led2 task                                */
							 (CPU_CHAR   *)"App Task Led2",
							 (OS_TASK_PTR ) AppTaskLed2,
							 (void       *) 0,
							 (OS_PRIO     ) APP_TASK_LED2_PRIO,
							 (CPU_STK    *)&AppTaskLed2Stk[0],
							 (CPU_STK_SIZE) APP_TASK_LED2_STK_SIZE / 10,
							 (CPU_STK_SIZE) APP_TASK_LED2_STK_SIZE,
							 (OS_MSG_QTY  ) 5u,
							 (OS_TICK     ) 0u,
							 (void       *) 0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
							 (OS_ERR     *)&err);

	OSTaskDel(&AppTaskStartTCB, & err );	
}

/*
*********************************************************************************************************
*                                          LED1 TASK
*********************************************************************************************************
*/
static void AppTaskLed1(void * p_arg)
{
	OS_ERR      err;

 (void)p_arg;

	while(1) 
	{                                          /* Task body, always written as an infinite loop.       */		 		
		(void)eMBPoll();
		Relay_control();
		set_zero(enable,enable,enable,enable);
		
		OSTimeDly(2, OS_OPT_TIME_DLY, &err);
	}	
}


/*
*********************************************************************************************************
*                                          LED2 TASK
*********************************************************************************************************
*/
static void AppTaskLed2(void * p_arg)
{
	OS_ERR      err;   

 (void)p_arg;

	OSTimeDly (200, OS_OPT_TIME_DLY, &err);
	
	/**
	 * 2020.10.14添加reset();，如果AD有问题马上注释掉reset();
	 * 该函数作用：在AD芯片上电后先对其复位一次，防止AD每次开机对不上
	 */
	reset();
	OSTimeDly (200, OS_OPT_TIME_DLY, &err);
	ADS1256_Init();
	OSTimeDly (200, OS_OPT_TIME_DLY, &err);
	ADS1256_Init();
	OSTimeDly (200, OS_OPT_TIME_DLY, &err);
	ADS1256_Init();
	OSTimeDly (200, OS_OPT_TIME_DLY, &err);
	ADS1256_Init();
	OSTimeDly (200, OS_OPT_TIME_DLY, &err);
	Setzero_Init();
	OSTimeDly (100, OS_OPT_TIME_DLY, &err);

	while(DEF_TRUE) 
	{ 
		/** 
		 * Task body, always written as an infinite loop.
		 *
		 * 接近开关部分，没有单独写函数  出现问题马上屏蔽掉  
		 */
		if (GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_10) == 1)	//远离调压阀侧接近开关不亮时为1
		{
			ucSCoilBuf[10] |= 0x10;														//85=1	
		}
		else
		{
			ucSCoilBuf[10] &= 0xef;														//85=0
		}
		
		if (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3) == 1)		//靠近调压阀侧接近开关不亮时为1
		{
			ucSCoilBuf[10] |= 0x20;														//86=1
		}
		else
		{
			ucSCoilBuf[10] &= 0xdf; 													//86=0
		}
		//接近开关部分结束，没有单独写函数  出现问题马上屏蔽掉   

		Step();
		caijitongdao(enable,enable,enable,enable);
		out_start_stop();                        
		OSTimeDly(2, OS_OPT_TIME_DLY, &err);	//当前运行的任务推迟运行
	}
}

/*
*********************************************************************************************************
*                                          LED3 TASK
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                          MPM270 TASK:传感器数据采集
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                          Modbus TASK：与触摸屏通讯
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                          teset TASK：气密性检测
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*                                          other TASK:其他简单的扫描动作，如继电器开启关闭吧，外部启停
*********************************************************************************************************
*/






