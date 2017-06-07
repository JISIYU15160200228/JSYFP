#include "LPC11xx.h"                    // Device header
#include "ADC.h"
#include <stdio.h>
#include <string.h>
#define UART_BPS 9600
char GcRcvBuf[20];
	void Delay(uint32_t ulTime)
	{
		uint32_t i;
		i=0;
		while(ulTime--)
		{
			for (i=0;i<5000;i++);
		}
	}
	void ADC_Init(void)
	{
		LPC_SYSCON->SYSAHBCLKCTRL |=(1<<16);
		LPC_IOCON->PIO1_11 &= ~0xBF;
		LPC_IOCON->PIO1_11 |= 0x01;
		LPC_SYSCON->PDRUNCFG &=~(0x01<<4);
		LPC_SYSCON->SYSAHBCLKCTRL |=(0x01<<13);
		LPC_ADC->CR=(1<<7)|
		((SystemCoreClock/1000000-1)<<8)|
		(0<<16)|
		(0<<17)|
		(0<<24)|
		(0<<27);
	}
	void UART_Init(void)
{
	uint16_t usFdiv;
	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);
	LPC_IOCON->PIO1_6&=~0x07;
	LPC_IOCON->PIO1_6|=(1<<0);
	LPC_IOCON->PIO1_7&=~0x07;
	LPC_IOCON->PIO1_7|=(1<<0);
	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<12);
	LPC_SYSCON->UARTCLKDIV=0x01;
	LPC_UART->LCR=0x83;
	usFdiv=(SystemCoreClock/LPC_SYSCON->UARTCLKDIV/16)/UART_BPS;
	LPC_UART->DLM=usFdiv/256;
	LPC_UART->DLL=usFdiv%256;
	LPC_UART->LCR=0x03;
	LPC_UART->FCR=0x07;
}
void GPIOInit(void)
{
	LPC_GPIO2 ->DIR |= 0xFFF;			
	
}
