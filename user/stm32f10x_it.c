/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "nvic.h"
#include "led.h"
#include "control.h"
#include "dac.h"
#include "usart.h"
#include "time.h"
__IO uint16_t ReceivedData;
extern __IO uint16_t Run_Status;
extern __IO uint16_t Send_time;

__IO uint16_t Loc_Remo_Flag = 0x0001;

//__IO uint8_t Loc_Flag = 1 ;
//__IO uint8_t Remo_Flag = 0;


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
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
  {
  }
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
  {
  }
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
  {
  }
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
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
uint16_t  timer = 0;
uint16_t  Tim = 0;
uint16_t Tim1=0;



void KEY0_IRQHandler(void)
{
  //ȷ���Ƿ������PC1�ж�
	if(EXTI_GetITStatus(KEY0_INT_EXTI_LINE) != RESET) 
	{
		/*��PC1,�жϸߵ͵�ƽ*/
		/*����Ǹߵ�ƽ��������CCģʽ��Loc_Run_Status��ڶ�λ��λ*/
		if(GPIO_ReadInputDataBit(KEY0_INT_GPIO_PORT,KEY0_INT_GPIO_PIN)==SET)
		{
			Loc_Run_Status |=Bit_cc_cv;
			
		}
		/*����ǵ͵�ƽ��������CVģʽ��Loc_Run_Status�ڶ�λ��λ*/
		else
		{
			Loc_Run_Status &= ~Bit_cc_cv;			
		}
	}
	else
	{
	}
	/*��λDAC���*/
	DAC_SetDualChannelData(DAC_DATA_ALIGN, 0, 0);
  /*����жϱ�־λ*/
	EXTI_ClearITPendingBit(KEY0_INT_EXTI_LINE);     
	 
}


void KEY1_IRQHandler(void)
{
  //ȷ���Ƿ������EXTI Line�ж�
	if(EXTI_GetITStatus(KEY1_INT_EXTI_LINE) != RESET) 
	{

		if(GPIO_ReadInputDataBit(KEY1_INT_GPIO_PORT, KEY1_INT_GPIO_PIN)==SET)
		{
			Loc_Remo_Flag |= Bit_Loc_Remo;
			DAC_SetDualChannelData(DAC_DATA_ALIGN, 0, 0);
		}
		else
			Loc_Remo_Flag &= ~Bit_Loc_Remo;
	}
	else
	{
	}		
    //����жϱ�־λ
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);     
	 
}




void KEY2_IRQHandler(void)
{
	if(EXTI_GetITStatus(KEY2_INT_EXTI_LINE) != RESET) 
	{
		if(GPIO_ReadInputDataBit(KEY2_INT_GPIO_PORT, KEY2_INT_GPIO_PIN)==RESET)
			Loc_Run_Status |= Bit_Timer;
		else
			Loc_Run_Status &= ~Bit_Timer;
	}
		else
		{}
		
		DAC_SetDualChannelData(DAC_DATA_ALIGN, 0, 0);
		

    //����жϱ�־λ
		EXTI_ClearITPendingBit(KEY2_INT_EXTI_LINE);     
	
}
/*����ֹͣ�ж�PA0--->KEY3*/
void KEY3_IRQHandler(void)
{
  //ȷ���Ƿ������EXTI Line�ж�
	if(EXTI_GetITStatus(KEY3_INT_EXTI_LINE) != RESET) 
	{
    if(GPIO_ReadInputDataBit(KEY3_INT_GPIO_PORT,KEY3_INT_EXTI_LINE)==SET)
		{
			Loc_Run_Status &= ~Bit_run_stop;
			DAC_SetDualChannelData(DAC_DATA_ALIGN, 0, 0);
		}
		else
		{
			Loc_Run_Status |= Bit_run_stop;
		}
				/*��λDA���*/
		
	} 
	else
	{
	}
	EXTI_ClearITPendingBit(KEY3_INT_EXTI_LINE); 
}

/*�����ж�PA1--->KEY4*/
void KEY4_IRQHandler(void)
{
  
	if(EXTI_GetITStatus(KEY4_INT_EXTI_LINE) != RESET) 
	{
    if(GPIO_ReadInputDataBit(KEY4_INT_GPIO_PORT,KEY4_INT_EXTI_LINE)==SET) //�ߵ�ƽΪ���յ������ź�
		{
		Loc_Run_Status &= ~Bit_alarm; //0Ϊ����
		/*�ر�GPIO�ж�*/
		EXTI->IMR &= ~(EXTI_Line3); 
		EXTI->IMR &= ~(EXTI_Line0);  
		EXTI->IMR &= ~(EXTI_Line2);  
		DAC_SetDualChannelData(DAC_DATA_ALIGN, 0, 0);
		}
		else
		{
		Loc_Run_Status |= Bit_alarm; //1Ϊ����
		/*------------����GPIO �ⲿ�ж�-------------------*/
		EXTI->IMR |= EXTI_Line3; 
		EXTI->IMR |= EXTI_Line0; 
		EXTI->IMR |= EXTI_Line2; 
		}
		
	} 
	else
	{
	}
	EXTI_ClearITPendingBit(KEY4_INT_EXTI_LINE); 
}


void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)!= RESET)
	{
		prvvTIMERExpiredISR();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);		
	}
}



void USART1_IRQHandler(void)
{
   if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
   {
				prvvUARTRxISR();
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);			 
   }
	 
	 if(USART_GetITStatus(USART1,USART_IT_TXE) == SET)
   {
        prvvUARTTxReadyISR();
				USART_ClearITPendingBit(USART1, USART_IT_TXE);
   }
}

		


/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

