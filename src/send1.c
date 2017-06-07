#include "LPC11xx.h"                    // Device header
#define UART_BPS 9600
char GcRcvBuf[20];
void UART_SendByte(uint8_t ucDat)
{
	LPC_UART->THR=ucDat;
	while((LPC_UART->LSR&0x40)==0);
}
void UART_SendStr(char * pucStr)
{
	while(1)
	{
	if(*pucStr=='\0')break;
	UART_SendByte (*pucStr++);
	}
}	
		
void LedInit(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |=(1<<6);
	LPC_GPIO2->DIR =0xff;
}

int main(void)
{
	uint32_t i;
	uint32_t ulADCData;
	uint32_t ulADCBuf;
	UART_Init ();
	ADC_Init();
	LedInit();
	while(1)
	{
		ulADCData=0;
		for(i=0;i<10;i++)
		{
			LPC_ADC->CR|=(1<<24);
			while((LPC_ADC->DR[7]&0x80000000)==0);
			LPC_ADC->CR|=(1<<24);
			while((LPC_ADC->DR[7]&0x80000000)==0);
			ulADCBuf=LPC_ADC->DR[0];
			ulADCBuf=(ulADCBuf>>6)&0x3ff;
			ulADCData+=ulADCBuf;
		}
	ulADCData=ulADCData/10;
	ulADCData=(ulADCData*3300)/1024;	
	GPIOInit();
	sprintf(GcRcvBuf,"VINO=%4d mV\r\n",ulADCData);
	UART_SendStr(GcRcvBuf);		
	Delay (200);
	}
}