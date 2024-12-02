/*
 * boot_loader.c
 *
 *  Created on: Oct 30, 2024
 *      Author: thanhdatpham
 */
#include <stdint.h>
#include <stdio.h>
#include "fsl_debug_console.h"
#include "cmsis_gcc.h"
#include "core_cm0plus.h"
#include "uart.h"
#include "flash.h"

#define FLASH_SECTOR_SIZE 	1024
#define START_ADDRESS  		0x8000
#define END_ADDRESS			0x10000

void JumpToApplication(uint32_t appAddress)
{
    // 1. Get Stack Pointer (SP) and Reset Handler from application vector table
    uint32_t sp = *((uint32_t*)appAddress);          // Stack Pointer
    uint32_t resetHandlerAddress = *((uint32_t*)(appAddress + 4));  // Reset Handler

    // 2. Check for valid Reset Handler address
    if (resetHandlerAddress == 0xFFFFFFFF || resetHandlerAddress == 0x00000000)
    {
        // Invalid address, not jumping to new app
        PRINTF("Invalid Reset Handler address: 0x%08X\r\n", resetHandlerAddress);
        while (1); // Stop if address is invalid
    }

    // 3. Update Main Stack Pointer (MSP)
    __set_MSP(sp);

    // 4. Disable all interrupts before jumping into a new application
    __disable_irq();

    // 5. Configure SCB->VTOR to point to the new application's vector table
    SCB->VTOR = appAddress;

    // 6. Transfer control to the application's Reset Handler (i.e. ResetISR)
    void (*resetHandler)(void) = (void (*)(void))resetHandlerAddress;
    resetHandler();
    PRINTF("Jumped to APP in Address:  0x%08X\r\n",appAddress);
}

void boot()
{
	Init_UART();
	Init_Queue();
	uint32_t sector_count ;
	sector_count = (END_ADDRESS - START_ADDRESS + FLASH_SECTOR_SIZE - 1) / FLASH_SECTOR_SIZE;
	Flash_EraseMultiSector(START_ADDRESS, sector_count);
	PRINTF("PLEASE SEND FILE SREC!\r\n");
	Handel_Srec();
	while(1);
}
