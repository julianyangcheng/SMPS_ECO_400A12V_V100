#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define run_status_led_gpio_port GPIOC
#define run_status_led_gpio_pin GPIO_Pin_3
#define run_status_led_gpio_mode GPIO_Mode_Out_PP

#define mode_status_led_gpio_port GPIOC
#define mode_status_led_gpio_pin GPIO_Pin_1
#define mode_status_led_gpio_mode GPIO_Mode_Out_PP

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬

/* �������IO�ĺ� */
#define run_status_led_TOGGLE		 digitalToggle(run_status_led_gpio_port,run_status_led_gpio_pin)
#define run_status_led_OFF		   digitalHi(run_status_led_gpio_port,run_status_led_gpio_pin)
#define run_status_led_ON			   digitalLo(run_status_led_gpio_port,run_status_led_gpio_pin)

#define mode_status_led_TOGGLE		 digitalToggle(mode_status_led_gpio_port,mode_status_led_gpio_pin)
#define mode_status_led_OFF		     digitalHi(mode_status_led_gpio_port,mode_status_led_gpio_pin)
#define mode_status_led_ON			   digitalLo(mode_status_led_gpio_port,mode_status_led_gpio_pin)

void status_led_gpio_config(void);
#endif //__LED_H
