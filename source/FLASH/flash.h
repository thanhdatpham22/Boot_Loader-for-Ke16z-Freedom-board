/*
 * flash.h
 *
 *  Created on: Nov 1, 2024
 *      Author: thanhdatpham
 */

#ifndef FLASH_FLASH_H_
#define FLASH_FLASH_H_

void Init_Flash(void);
uint32_t Flash_Read(uint32_t address);
void Flash_ReadRange(uint32_t startAddr, uint32_t endAddr);
void Flash_Erase(uint32_t address);
void Flash_EraseMultiSector(uint32_t startAddress, uint32_t sectorCount);
void Flash_Write(uint32_t address, uint32_t data);
bool Flash_VerifyData(uint32_t address, const uint8_t *data, uint32_t length) ;

#endif /* FLASH_FLASH_H_ */
