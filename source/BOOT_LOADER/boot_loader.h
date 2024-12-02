/*
 * boot_loader.h
 *
 *  Created on: Oct 30, 2024
 *      Author: thanhdatpham
 */

#ifndef BOOT_LOADER_BOOT_LOADER_H_
#define BOOT_LOADER_BOOT_LOADER_H_

void JumpToApplication(uint32_t appAddress);
void boot();

#endif /* BOOT_LOADER_BOOT_LOADER_H_ */
