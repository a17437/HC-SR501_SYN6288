/*
1.项目名称：绿深旗舰店-STM32综合测试板SYN6288语音合成模块测试程序
2.显示模块：无
3.使用软件：keil5 for ARM
4.配套上位机：无
5.项目组成：绿深SYN6288语音合成模块
6.项目功能：将文字转化成语音，并朗读出来，出厂默认波特率9600。
7.主要原理：具体参考SYN6288数据手册
8.购买地址：https://lssz.tmall.com 或淘宝上搜索“绿深旗舰店”
9.版权声明：绿深旗舰店所有程序都申请软件著作权。均与本店产品配套出售，请不要传播，以免追究其法律责任！
接线定义：
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


/**************芯片设置命令*********************/
u8 SYN_StopCom[] = {0xFD, 0X00, 0X02, 0X02, 0XFD}; //停止合成
u8 SYN_SuspendCom[] = {0XFD, 0X00, 0X02, 0X03, 0XFC}; //暂停合成
u8 SYN_RecoverCom[] = {0XFD, 0X00, 0X02, 0X04, 0XFB}; //恢复合成
u8 SYN_ChackCom[] = {0XFD, 0X00, 0X02, 0X21, 0XDE}; //状态查询
u8 SYN_PowerDownCom[] = {0XFD, 0X00, 0X02, 0X88, 0X77}; //进入POWER DOWN 状态命令

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();
	USART3_Init(9600);
	SR501_Init();
	LED_Init();
	LED0=1;
	LED1=1;
	while(1)
	{		
	//选择背景音乐2。(0：无背景音乐  1-15：背景音乐可选)
    //m[0~16]:0背景音乐为静音，16背景音乐音量最大
    //v[0~16]:0朗读音量为静音，16朗读音量最大
    //t[0~5]:0朗读语速最慢，5朗读语速最快
    //其他不常用功能请参考数据手册
		LED0=0;
		delay_ms(2000);
		if(SR501_Statue()==SET)
		{
			delay_ms(5);
			LED1=0;
			delay_ms(10);
			if(SR501_Statue()==SET)
			SYN_FrameInfo(2,"[v7][m0][t5]警告");
			delay_ms(1500);
		}
		else
		{
			LED1=1;
			delay_ms(100);
		}
		delay_ms(1000);
		
		
		
		//暂停合成，此时没有用到，用于展示函数用法
		//YS_SYN_Set(SYN_SuspendCom);
	}
}


