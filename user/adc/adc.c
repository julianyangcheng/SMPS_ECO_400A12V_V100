#include "adc.h"
//#include "misc.h"

static void ADCx_GPIO_CONFIG(void)
{
	/*GPIO�ṹ������*/
	GPIO_InitTypeDef GPIO_InitStruct;
	/*����GPIO����ʱ��*/
	ADC_GPIO_APBxCLOCK_FUN (ADC_GPIO_CLK, ENABLE);
	/*GPIO����*/
	GPIO_InitStruct.GPIO_Pin = ADC_GPIO_PIN1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;            //ģ������ģʽ      //����ģʽ�²�������GPIO�ٶ�
	GPIO_Init(ADC_PORT1, &GPIO_InitStruct); 
	
	GPIO_InitStruct.GPIO_Pin = ADC_GPIO_PIN2;
	GPIO_Init(ADC_PORT2, &GPIO_InitStruct);  
		

	/*��ʼ��GPIO PA7*/
	GPIO_InitStruct.GPIO_Pin = ADC_GPIO_PIN3; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADC_PORT3, &GPIO_InitStruct); 
		
}

static void ADC_Mode_Config(void)
{
	/*ADC�ṹ������*/
	ADC_InitTypeDef ADC_InitStruct;
	/*��ADC����ʱ��*/
	ADC_APBxCLOCK_FUN (ADCx_CLK, ENABLE);
	/*ADCģʽ����*/
	ADC_InitStruct.ADC_Mode = ADCx_MODE;   
	ADC_InitStruct.ADC_ScanConvMode = ENABLE ;	
	ADC_InitStruct.ADC_DataAlign = ADCx_DataAlign;
	
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_ExternalTrigConv = ADCxTriggerMode;
	ADC_InitStruct.ADC_NbrOfChannel = ADCxCovNum;
	/*��ʼ��ADC����*/
	ADC_Init(ADC_x, &ADC_InitStruct);
	/*ADCʱ�ӷ�Ƶ����*/
	RCC_ADCCLKConfig(ADC_Clk_Div);
	/*ADC�飬ͨ������������������ʱ������*/
	ADC_RegularChannelConfig(ADC_x,ADCx_Channel1, ADCx_Rank1, ADCx_SampHold_Cyc);
	ADC_RegularChannelConfig(ADC_x,ADCx_Channel2, ADCx_Rank2, ADCx_SampHold_Cyc);
	ADC_RegularChannelConfig(ADC_x,ADCx_Channel3, ADCx_Rank3, ADCx_SampHold_Cyc);
	/*DMAʹ��*/
	ADC_DMACmd(ADC_x, ENABLE);
	/*ADCʹ��*/
	ADC_Cmd(ADC_x, ENABLE);
		// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADC_x);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADC_x));
	/*ADCУ׼*/
	ADC_StartCalibration(ADC_x);
	while(ADC_GetCalibrationStatus(ADC_x));
	/*ADC�������ʹ��*/
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
	
}


void ADCx_Init(void)
{
	
	ADCx_GPIO_CONFIG();
	ADC_Mode_Config();
	
}
