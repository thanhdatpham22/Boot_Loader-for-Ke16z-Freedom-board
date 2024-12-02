/*
 * app1.c
 *
 *  Created on: Oct 30, 2024
 *      Author: thanhdatpham
 */

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

#include "uart.h"
#include "user_queue.h"
#include "flash.h"
#include "boot_loader.h"

#define APP1_ADDRESS 0x8000U
#define APP2_ADDRESS 0xC100U
/*******************************************************************************
 * Code
 ******************************************************************************/

int sw3_check(void)
{
	 if (GPIO_PinRead(BOARD_SW3_GPIO, BOARD_SW3_PIN) == 0)
	{
		return 1;
	}
	return 0;
}

void application(void)
{
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	PRINTF("Bootloader Application Started\r\n");

	while (1)
	{
		if (sw3_check() == 1)
		{

			PRINTF("Waiting for SREC data...\r\n");
			boot();

		}
		else
		{
			PRINTF("Press HOLD SW3 then PRESS RESET and then RELEASE the RESET while STILL PRESSING SW3 to enter boot mode.\r\n ");
			PRINTF("Switch pressed, jumping to application...\r\n");
			JumpToApplication(APP1_ADDRESS);

		}
	}
}
