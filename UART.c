/*
 * UART.c
 *
 * Created: Apr15,2017 11:03:04 AM
 *  Author: Marwa
 */ 

#include "UART.h"



void UART_init(void)
{
	/*
	*Double Speed Mode
	*/
	UCSRA|=(1<<U2X);
	/*
	*enable receiver
	*enable transmitter
	*/
	UCSRB=(1<<RXEN)|(1<<TXEN);
	/*
	* 8_bits data UCSZ0,UCSZ1
	* set USART Register Select for writing the UCSRC
	*/
	
	UCSRC=(1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);
	
	/*
	*Baud Rate =9600 B/sec UBRRL
	*F-micro=8MHz
	 */
	UBRRH=0;
	UBRRL=103;
	
}

void UART_sendByte(uint8 data)

{
	/*put data into data register UDR*/
	UDR=data; 
	
   /*wait until it becomes 1, which indicates that entire frame is sent and register is empty*/
	while((BIT_IS_CLEAR(UCSRA,TXC))){}
	
	/* TXC is cleared when a Transmit Complete Interrupt is executed, by setting it*/
	SET_BIT(UCSRA,TXC);
		
}


uint8 UART_recieveByte(void)

{
	/*wait until data is received in register,it becomes 1 */
	while((BIT_IS_CLEAR(UCSRA,RXC))) {}
	
	/* return data*/
	return UDR;
	
}

void UART_sendString(const uint8 *str)

{
	uint8 i=0;
	while(str[i]!='\0')
	{
		UART_sendByte(str[i]);
		i++;
	}
	
	
}

void UART_recieveString(uint8 *str)

{
	uint8 i=0;
	str[0]=UART_recieveByte();
	while(str[i]!='#') /*indicates string's end*/
	{
		i++;
		str[i]=UART_recieveByte();
		
	}
	str[i]='\0';
	
}

