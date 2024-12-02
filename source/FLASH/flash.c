/*
 * flash.c
 *
 *  Created on: Nov 1, 2024
 *      Author: thanhdatpham
 */
#include <stdint.h>
#include "fsl_debug_console.h"
#include <stdbool.h>

#define FLASH_SECTOR_SIZE 1024

void Init_Flash(void)
{
    FTFA->FSTAT = FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_FPVIOL_MASK;
    PRINTF("Flash Inited.\r\n");
}

void Flash_Erase(uint32_t address)
{
    if (address % FLASH_SECTOR_SIZE != 0) return;

    FTFA->FSTAT = FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_FPVIOL_MASK;

    FTFA->FCCOB0 = 0x09;
    FTFA->FCCOB1 = (address >> 16) & 0xFF;
    FTFA->FCCOB2 = (address >> 8) & 0xFF;
    FTFA->FCCOB3 = address & 0xFF;

    FTFA->FSTAT |= FTFA_FSTAT_CCIF_MASK;

    while (!(FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK));

    if (FTFA->FSTAT & (FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_FPVIOL_MASK))
    {
        PRINTF("Error erasing flash at address 0x%X\r\n", address);
        FTFA->FSTAT = FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_FPVIOL_MASK;
    }
    else
    {
        //PRINTF("Flash erased at address 0x%X\r\n", address);
    }
}

void Flash_EraseMultiSector(uint32_t startAddress, uint32_t sectorCount)
{

    if (startAddress % FLASH_SECTOR_SIZE != 0) return;


    for (uint32_t i = 0; i < sectorCount; i++)
    {
        uint32_t address = startAddress + i * FLASH_SECTOR_SIZE;

        Flash_Erase(address);

        //PRINTF("Erased sector %d at address 0x%X\r\n", i + 1, address);
    }
    PRINTF("FLASH CLEAR!\r\n");
}

void Flash_Write(uint32_t address, uint32_t data)
{

    if (address % 4 != 0) return;

    FTFA->FSTAT = FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_FPVIOL_MASK;

    FTFA->FCCOB0 = 0x06;
    FTFA->FCCOB1 = (address >> 16) & 0xFF;
    FTFA->FCCOB2 = (address >> 8) & 0xFF;
    FTFA->FCCOB3 = address & 0xFF;
    FTFA->FCCOB4 = (data >> 24) & 0xFF;
    FTFA->FCCOB5 = (data >> 16) & 0xFF;
    FTFA->FCCOB6 = (data >> 8) & 0xFF;
    FTFA->FCCOB7 = data & 0xFF;

    __disable_irq();

    FTFA->FSTAT |= FTFA_FSTAT_CCIF_MASK;

    while (!(FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK));
    __enable_irq();

    if (FTFA->FSTAT & (FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_FPVIOL_MASK))
    {
        FTFA->FSTAT = FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_FPVIOL_MASK;
    }
}

uint32_t Flash_Read(uint32_t address)
{
	uint32_t data = *(uint32_t*)address;
	 return data;
}

void Flash_ReadRange(uint32_t startAddr, uint32_t endAddr)
{
    uint32_t addr = startAddr;

    PRINTF("Reading data from 0x%X to 0x%X:\r\n", startAddr, endAddr);

    while (addr <= endAddr)
    {
        uint32_t data = *(uint32_t*)addr;
        PRINTF("Address 0x%X: 0x%X\r\n", addr, data);
        addr += 4;
    }
}

bool Flash_VerifyData(uint32_t address, const uint32_t *data, uint32_t length)
{
    for (uint32_t i = 0; i < length; i += 4)
    {
    	uint32_t word = (data[i+3] << 24) | (data[i+2] << 16) | (data[i+1] << 8) | data[i];
        uint32_t readData = Flash_Read(address + i);
        if (readData != word)
        {
            PRINTF("Verification failed at address 0x%08X. Expected: 0x%08X, Read: 0x%08X\r\n", address + i, word, readData);
            return false;
        }
    }
    PRINTF("Verification successful!\r\n");
    return true;
}
