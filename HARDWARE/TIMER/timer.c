/*
TIM5
CH1-PA0
*/
#include "timer.h"
#include "led.h"
#include "usart.h"
#include "TCS3200.H"


TIM_ICInitTypeDef  TIM5_ICInitStructure;

extern u16 amount;

void TIM5_Cap_Init(void) //��ɫ_tim5_PA0
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ��TIM5ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
					

	//��ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;	//�½��ز���
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 

	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	

	TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5

}


void TIM5_IRQHandler(void)
{
	amount++;		 
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ 
}

