/**
  ******************************************************************************
  * @file    FMC_SDRAM/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    11-November-2013
  * @brief   Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and
  *         peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_it.h"
#include <includes.h>
#include "port.h"
#include "bsp_rs232_usart.h"


#include "Timer5.h"
#include "relay.h"
#include "mb.h"
#include "bsp_led.h"   
#include "modbus.h"

#include "Timer1.h"
/** @addtogroup STM32F429I_DISCOVERY_Examples
  * @{
  */

/** @addtogroup FMC_SDRAM
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f429_439xx.s).                         */
/******************************************************************************/

/**
  * @}
  */ 
/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RS232_USART_IRQHandler(void)
{
	OSIntEnter(); 	    //进入中断
	
	if(USART_GetITStatus(RS232_USART, USART_IT_RXNE) == SET)
	{		
		prvvUARTRxISR();	//创建中断处理程序
		USART_ClearITPendingBit(RS232_USART, USART_IT_RXNE);	
	}

	if(USART_GetITStatus(RS232_USART, USART_IT_TXE) == SET)
	{
		prvvUARTTxReadyISR();
	}

	OSIntExit();	                                       //退出中断	
}
/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

//void ADVANCE_TIM_IRQHandler(void)
//{
//		if ( TIM_GetITStatus( ADVANCE_TIM, TIM_IT_Update) != RESET ) 
//	{	
//		Timer1_cout++;
//		if(Timer1_cout>10)
//		{
//			LED3_TOGGLE;
//		}	
//		TIM_ClearITPendingBit(ADVANCE_TIM , TIM_IT_Update); 
//	}
//}


void TIM2_IRQHandler(void)
{
	TIMERExpiredISR();
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void GENERAL_TIM_IRQHandler(void)           //Timer4
{
	Timer3_cout++;
	
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

void GENERAL_TIM4_IRQHandler(void)
{
	CPU_SR_ALLOC();  
	OS_CRITICAL_ENTER();                                //进入临界段，不希望下面串口打印遭到中断
	
	Timer4_cout++;
	
  printf(" %f 计时\r\n",Timer4_cout);
	OS_CRITICAL_EXIT();                                //进入临界段，不希望下面串口打印遭到中断
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}

union LianHeTi test_data9;
union LianHeTi test_data10;

union LianHeTi test_data11;
union LianHeTi test_data12;
union LianHeTi test_data13;

union LianHeTi test_data15;

union LianHeTi test_data16;
union LianHeTi test_data17;
union LianHeTi test_data18;
union LianHeTi test_data19;



//USHORT   usSRegHoldBuf[100];
void TIM5_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
}



/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



