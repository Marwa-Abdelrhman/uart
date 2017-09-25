/*
 * UART.h
 *
 * Created: Apr15,2017 11:03:18 AM
 *  Author: Marwa
 */ 


#ifndef UART_H_
#define UART_H_


#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

void UART_init(void);
void UART_sendByte(uint8 data);
uint8 UART_recieveByte(void);
void UART_sendString(const uint8 *str);
void UART_recieveString(uint8 *str);



#endif /* UART_H_ */