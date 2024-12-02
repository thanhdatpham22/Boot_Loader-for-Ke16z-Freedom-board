/*
 * uart.c
 *
 *  Created on: Oct 30, 2024
 *      Author: thanhdatpham
 */

#include <string.h>
#include "fsl_lpuart.h"
#include "fsl_debug_console.h"

#include "user_queue.h"
#include "srec.h"
#include "flash.h"
#define UART_BAUDRATE 115200U
#define LPUART_CLK_FREQ CLOCK_GetFreq(kCLOCK_ScgSysOscClk)
#define MAX_DATA_SIZE 50
#define FLASH_SECTOR_SIZE 1024
/*******************************************************************************
 * Ringbuffer Struct
 ******************************************************************************/

/***************************************************************************
 * Global Variables
 ******************************************************************************/

volatile Ringbuffer uartQueue;
volatile uint8_t status = 0;

/*******************************************************************************
 * Declare UART
 ******************************************************************************/
void Init_UART()
{
    lpuart_config_t config;
    config.baudRate_Bps = UART_BAUDRATE;
    config.parityMode = kLPUART_ParityDisabled;
    config.dataBitsCount = kLPUART_EightDataBits;
    config.isMsb = false;
    config.stopBitCount = kLPUART_OneStopBit;
    config.txFifoWatermark = 0;
    config.rxFifoWatermark = 0;
    config.enableRx = 1;
    config.enableTx = 1;

    LPUART_Init(LPUART0, &config, LPUART_CLK_FREQ);
    LPUART_EnableInterrupts(LPUART0, kLPUART_RxDataRegFullInterruptEnable);
	EnableIRQ(LPUART0_IRQn);
	PRINTF("START, UART!\r\n");
}

/*******************************************************************************
 * Main code
 ******************************************************************************/

void LPUART0_IRQHandler(void)
{
	static Line record;
	static uint8_t index = 0;
	if ((kLPUART_RxDataRegFullFlag) & LPUART_GetStatusFlags(LPUART0))
	{
		char data = LPUART_ReadByte(LPUART0);
		//PRINTF("%c", data);
		if(data == 'S')
		{
			index = 0;
		}
		if(data == '\n')
		{
			record.str[index] = '\0';
			status ++ ;
			index = 0;

			enQueue(&uartQueue, record);
		}
		else
		{
			record.str[index] = data;
			index ++;
		}
	}
}

void Handel_Srec(void)
{
	Line record;
	unsigned int recordCount = 0;
	unsigned int lineNum = 0;
	unsigned int addr;
	unsigned char data[MAX_DATA_SIZE];
	unsigned int dataLen;
	uint8_t status_break = 1;
	while(status_break)
	{
		while(status == 0)
		{

		}
		status = 0;

		record = deQueue(&uartQueue);
		lineNum++;
		//PRINTF("%s\r\n",record.str);
		if (!parseLine(lineNum, record.str, &recordCount, &addr, data, &dataLen))
		{
			PRINTF("Error in line %d\r\n", lineNum);
			return;
		}
		else
		{
//			PRINTF("%s\r\n",record.str);
//			PRINTF("Line %d is valid. Address: 0x%X, Data Length: %d, recordType[1]: %c\r\n", lineNum, addr, dataLen,record.str[1]);
			if(record.str[1] == '0' )
			{
				PRINTF("BEGIN WRITE TO FLASH\r\n");
				PRINTF("FLASHING...\r\n");
			}
			if(record.str[1] == '7' || record.str[1] == '8' || record.str[1] == '9')
			{
				PRINTF("END OF WRITE TO FLASH\r\n");
				Flash_VerifyData(addr, data, dataLen);
				PRINTF("Press Reset to jump program\r\n");
				status_break = 0;
			}
			else
			{

				for (unsigned i = 0; i < dataLen; i += 4)
				{
					 uint32_t word = (data[i+3] << 24) | (data[i+2] << 16) | (data[i+1] << 8) | data[i];
					 Flash_Write(addr + i, word);
				}

			}
		}
	}
}


void Init_Queue(void)
{
	InitQueue(&uartQueue);
}
