/*
1.��Ŀ���ƣ������콢��-STM32�ۺϲ��԰�SYN6288�����ϳ�ģ����Գ���
2.��ʾģ�飺��
3.ʹ�������keil5 for ARM
4.������λ������
5.��Ŀ��ɣ�����SYN6288�����ϳ�ģ��
6.��Ŀ���ܣ�������ת�������������ʶ�����������Ĭ�ϲ�����9600��
7.��Ҫԭ������ο�SYN6288�����ֲ�
8.�����ַ��https://lssz.tmall.com ���Ա��������������콢�ꡱ
9.��Ȩ�����������콢�����г��������������Ȩ�����뱾���Ʒ���׳��ۣ��벻Ҫ����������׷���䷨�����Σ�
���߶��壺
		VCC--5V
		RXD--PB10
		TXD--PB11
		GND--GND
*/
#include "sys.h"
#include "delay.h"
#include "stdio.h"
#include "usart.h"
#include "syn6288.h"
#include "led.h"
#include "sr501.h"


/**************оƬ��������*********************/
u8 SYN_StopCom[] = {0xFD, 0X00, 0X02, 0X02, 0XFD}; //ֹͣ�ϳ�
u8 SYN_SuspendCom[] = {0XFD, 0X00, 0X02, 0X03, 0XFC}; //��ͣ�ϳ�
u8 SYN_RecoverCom[] = {0XFD, 0X00, 0X02, 0X04, 0XFB}; //�ָ��ϳ�
u8 SYN_ChackCom[] = {0XFD, 0X00, 0X02, 0X21, 0XDE}; //״̬��ѯ
u8 SYN_PowerDownCom[] = {0XFD, 0X00, 0X02, 0X88, 0X77}; //����POWER DOWN ״̬����

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();
	USART3_Init(9600);
	SR501_Init();
	LED_Init();
	LED0=1;
	LED1=1;
	while(1)
	{		
	//ѡ�񱳾�����2��(0���ޱ�������  1-15���������ֿ�ѡ)
    //m[0~16]:0��������Ϊ������16���������������
    //v[0~16]:0�ʶ�����Ϊ������16�ʶ��������
    //t[0~5]:0�ʶ�����������5�ʶ��������
    //���������ù�����ο������ֲ�
		LED0=0;
		delay_ms(2000);
		if(SR501_Statue()==SET)
		{
			delay_ms(5);
			LED1=0;
			delay_ms(10);
			if(SR501_Statue()==SET)
			SYN_FrameInfo(2,"[v7][m0][t5]����");
			delay_ms(1500);
		}
		else
		{
			LED1=1;
			delay_ms(100);
		}
		delay_ms(1000);
		
		
		
		//��ͣ�ϳɣ���ʱû���õ�������չʾ�����÷�
		//YS_SYN_Set(SYN_SuspendCom);
	}
}


