#include "usart.h"
#include "sys.h" 
#include "sr501.h"


//初始化GPIOA.0
void SR501_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//配置为下拉输入模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

u8 SR501_Statue(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1)
	{
		return 1;
	}
	return 0;
}