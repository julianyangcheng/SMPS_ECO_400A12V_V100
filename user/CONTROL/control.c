#include "control.h"
#include "key.h"
#include "led.h"
#include "adc.h"
#include "dma.h"
#include "dac.h"
#include "usart.h"
#include "pbdata.h"
#include "myrtu.h"
#include "nvic.h"


extern __IO uint16_t Given_value;
extern __IO uint16_t Uo_value;
extern __IO uint16_t Io_value;

__IO uint16_t Loc_Run_Status=     0x0000;
     uint16_t Remo_Run_Status=    0x0000;
		 
uint8_t timer_bit = 0;
__IO uint16_t U_giv =            0x0000;
uint16_t I_set = 0;
uint16_t Remo_U_giv = 0x0000;
float Remo_U_GIV_Value = 0;

extern uint16_t Loc_Remo_Flag;
extern USHORT Flag   ;
extern USHORT Status ;
extern USHORT Given  ;
extern USHORT Io     ;
extern USHORT Uo     ;
extern USHORT Alarm  ;



void CC_Mode(void)
{

			if(U_giv<=Max_set)
			{
				DAC_SetDualChannelData(DAC_DATA_ALIGN, I_set, 3227);
			}
//			else if(U_giv<=10)
//			{
//				DAC_SetDualChannelData(DAC_DATA_ALIGN, 0, 3227);
//			}
			else
			{
				DAC_SetDualChannelData(DAC_DATA_ALIGN, 3200, 3227);
			}
}
void CV_Mode(void)
{

			if(U_giv<=Max_set)
			{
				DAC_SetDualChannelData(DAC_DATA_ALIGN, 3227, I_set);
			}
//			else if(U_giv<=10)
//			{
//				DAC_SetDualChannelData(DAC_DATA_ALIGN, 3227, 0);
//			}
			else
			{
				DAC_SetDualChannelData(DAC_DATA_ALIGN, 3227, 3200);
			}
}

void Remo_CC_Mode(void)
{
		
			if(Remo_U_giv<=Max_set)
			{
				DAC_SetDualChannelData(DAC_DATA_ALIGN, Remo_U_giv, 3227);
			}
			else if(Remo_U_giv<=5)
			{
				DAC_SetDualChannelData(DAC_DATA_ALIGN, 0, 3227);
			}
			else
			{
				DAC_SetDualChannelData(DAC_DATA_ALIGN, 3200, 3227);
			}
}

void Remo_CV_Mode(void)
{
		
			if(Remo_U_giv<=Max_set)
			{
				DAC_SetDualChannelData(DAC_DATA_ALIGN, 3227, Remo_U_giv);	
			}
			else if(Remo_U_giv<=5)
			{
				DAC_SetDualChannelData(DAC_DATA_ALIGN, 3227, 0);
			}
			else
			{
				DAC_SetDualChannelData(DAC_DATA_ALIGN, 3227, 3200);	
			}	
}


void GET_Loc_GPIO(void)
{
	//��ʼ��cc��cv������
	if(GPIO_ReadInputDataBit(KEY0_INT_GPIO_PORT,KEY0_INT_GPIO_PIN)==SET)
		{
			Loc_Run_Status |=Bit_cc_cv;			
		}
		else
		{
			Loc_Run_Status &= ~Bit_cc_cv;			
		}
		//��ʼ��Զ�أ����ؿ��Ʋ���
	if(GPIO_ReadInputDataBit(KEY1_INT_GPIO_PORT, KEY1_INT_GPIO_PIN)==SET)
	{
			Loc_Remo_Flag |= Bit_Loc_Remo;
	}
	else
	{
			Loc_Remo_Flag &= ~Bit_Loc_Remo;
	}
	//��ʼ��timer������
	if(GPIO_ReadInputDataBit(KEY2_INT_GPIO_PORT, KEY2_INT_GPIO_PIN)==RESET)
	{
			Loc_Run_Status |= Bit_Timer;
	}
	else
	{
			Loc_Run_Status &= ~Bit_Timer;
	}
	
	//��ʼ��Run,Stop������
  if(GPIO_ReadInputDataBit(KEY3_INT_GPIO_PORT,KEY3_INT_EXTI_LINE)==SET)
	{
			Loc_Run_Status &= ~Bit_run_stop;
	}
	else
	{
			Loc_Run_Status |= Bit_run_stop;
	}
 if(GPIO_ReadInputDataBit(KEY4_INT_GPIO_PORT,KEY4_INT_EXTI_LINE)==SET) //�ߵ�ƽΪ���յ������ź�
		{
			Loc_Run_Status &= ~Bit_alarm; //0Ϊ����
		}
	else
		{
			Loc_Run_Status |= Bit_alarm; //1Ϊ����
		}	
}

void control(uint16_t Loc_Remo_Flag)
{
	//GET_Loc_GPIO();
	Flag=Loc_Remo_Flag;
	if(Loc_Remo_Flag==0x0001)
	{
		/*------------����GPIO �ⲿ�ж�-------------------*/
		EXTI->IMR |= EXTI_Line3; 
		EXTI->IMR |= EXTI_Line0; 
		EXTI->IMR |= EXTI_Line2; 
		/*-------------ʹ��ADCת��------------------------*/
		ADC1->CR2 |= (0x01<<0);
		ADC_Value_Converter();
		U_giv = Given_value;
		I_set = (3103*U_giv)/Max_set;
		timer_bit = GPIO_ReadInputDataBit(KEY2_INT_GPIO_PORT, KEY2_INT_GPIO_PIN);
		
		if( ( ( Loc_Run_Status&(0x01<<0) )==SET ) && ( ( Loc_Run_Status&(0x01<<2) ) ==  0x04) )
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_3);
			//run_status_led_OFF;
		}
		else
		{
			GPIO_ResetBits(GPIOC, GPIO_Pin_3);
			//run_status_led_ON;
		}
		if(Loc_Run_Status&(0x01<<1))
		{
			CC_Mode();
		}
		else
		{	
			CV_Mode();
		}
		//DAC_SetDualChannelData(DAC_DATA_ALIGN, 1024, 1024);
	usRegInputBuf[0] = Loc_Run_Status;
	usRegInputBuf[1] = U_giv;
	usRegInputBuf[2] = Io_value;
	usRegInputBuf[3] = Uo_value;
	usRegInputBuf[4] = Alarm;
	usRegInputBuf[5] = Loc_Remo_Flag;
	usRegInputBuf[6] = 0xeeee;
	}
	else
	{
		/*�ر�GPIO�ж�*/
		EXTI->IMR &= ~(EXTI_Line3); 
		EXTI->IMR &= ~(EXTI_Line0);  
		EXTI->IMR &= ~(EXTI_Line2);  
		/*�ر�ADC����*/
		//ADC1->CR2 ^= (0x01<<0);
		
		ADC_Value_Converter();
		
		/*���ݽ���*/
		Remo_Run_Status=usRegHoldingBuf[0];
		Remo_U_giv = usRegHoldingBuf[1];
		
		if(Remo_Run_Status&(0x01<<0))
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_3);
			//run_status_led_ON;
		}
		else
		{
			GPIO_ResetBits(GPIOC, GPIO_Pin_3);
			//run_status_led_OFF;
		}
		if(Remo_Run_Status&(0x01<<1))
			
		{
			Remo_CC_Mode();

		}
		else
		{
			Remo_CV_Mode();
			
		}
	usRegInputBuf[0] = Remo_Run_Status;
	usRegInputBuf[1] = Remo_U_giv;
	usRegInputBuf[2] = Io_value;
	usRegInputBuf[3] = Uo_value;
	usRegInputBuf[4] = Alarm;
	usRegInputBuf[5] = Loc_Remo_Flag;
	usRegInputBuf[6] = 0x1111;	
	}
}


