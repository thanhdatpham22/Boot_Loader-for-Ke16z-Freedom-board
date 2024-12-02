/*
 * srec.h
 *
 *  Created on: Oct 30, 2024
 *      Author: thanhdatpham
 */

#ifndef SREC_LAYER_SREC_H_
#define SREC_LAYER_SREC_H_

//#include <stdint.h>

bool getNibble( const char **s, unsigned char *nb);
bool getByte(const char **s, unsigned char *b);
//bool parseFile(FILE *fp);
bool parseLine(unsigned lineNum, const char * line, unsigned *recordCount,
			   unsigned *addr, unsigned char *data, unsigned *dataLen);
unsigned get_address(const char *data);

#endif /* SREC_LAYER_SREC_H_ */
