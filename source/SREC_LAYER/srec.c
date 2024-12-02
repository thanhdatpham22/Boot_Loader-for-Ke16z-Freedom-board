/*
 * srec.c
 *
 *  Created on: Oct 30, 2024
 *      Author: thanhdatpham
 */
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "srec.h"
#include "fsl_debug_console.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
******************************************************************************/
/* Function implementations */

bool getNibble( const char **s, unsigned char *nb)
{
    /* Get the first character in the current string */
    /* By dereferencing the pointer to a pointer to a character */
    char ch = **s;
    /* Increment the char pointer so the string is consumed */
    *s = *s + 1;
    /* Convert the hex digit character to numbers, store in byte `b` */
    if((ch >= '0') && (ch <= '9'))
    {
        *nb = ch - '0';
        return true;
    }
    if ( (ch >= 'A') && (ch <= 'F') )
    {
        *nb = ch - 'A' + 10;
        return true;
    }
    if ( (ch >= 'a') && (ch <= 'f') )
    {
        *nb = ch - 'a' + 10;
        return true;
    }
    PRINTF("Unexpected character found, '%c'\r\n",ch);
    return false;

}

bool getByte(const char **s, unsigned char *b)
{
    unsigned char low_4byte;
    unsigned char high_4byte;
    if(getNibble(s, &high_4byte) && getNibble(s, &low_4byte))
    {
        *b = high_4byte << 4 | low_4byte;
        return true;
    }
    return false;
}

bool parseLine(unsigned lineNum, const char *line, unsigned *recordCount, unsigned *addr, unsigned char *data, unsigned *dataLen)
{
    if (line[0] != 'S')
    {
        PRINTF("Line[%d]: Not a valid S-Record (first char not 'S')", lineNum);
        return false;
    }

    if (!isdigit(line[1]))
    {
        PRINTF("Line %d: Unsupported record type, found : '%c'", lineNum, line[1]);
        return false;
    }

    const char *s = &line[2];
    unsigned char byteCount;

    if (!getByte(&s, &byteCount))
    {
        PRINTF("Line %d: Invalid byte count\n", lineNum);
        return false;
    }

    unsigned char checksumCalc = byteCount;
    for (int i = 0; i < (byteCount - 1); i++)
    {
        if (!getByte(&s, &data[i]))
        {
            PRINTF("Line %d: Error reading data at byte %d\n", lineNum, i + 1);
            return false;
        }
        checksumCalc += data[i];
    }

    checksumCalc = ~checksumCalc;
    unsigned char checksumRead;
    if (!getByte(&s, &checksumRead))
    {
        PRINTF("Line %d: Error reading checksum\n", lineNum);
        return false;
    }
    if (checksumRead != checksumCalc)
    {
        PRINTF("Line %d: Checksum mismatch (expected 0x%02X, calculated 0x%02X)\n", lineNum, checksumRead, checksumCalc);
        return false;
    }

    char rcType = line[1];
    unsigned addrLen;

    switch (rcType)
    {
        case '0': // Header record
            addrLen = 2;
            *recordCount += 1;
            *addr = 0;
            *dataLen = byteCount - addrLen - 1;
            memmove(data, data + addrLen, *dataLen);
            //PRINTF("S0 record: Header information.\n");
            break;

        case '1': // Data record with 2-byte address
            addrLen = 2;
            *recordCount += 1;
            break;

        case '2': // Data record with 3-byte address
            addrLen = 3;
            *recordCount += 1;
            break;

        case '3': // Data record with 4-byte address
            addrLen = 4;
            *recordCount += 1;
            break;

        case '5': // Record count with 2-byte address
            addrLen = 2;
            *recordCount += 1;
            //PRINTF("S5 record: Record count.\n");
            *dataLen = 0; /*Have not data to Process*/
            return true;

        case '7': // Start address with 4-byte address
            addrLen = 4;
            //PRINTF("S7 record: Start address (4 bytes).\n");
            *dataLen = 0;
            return true;

        case '8': // Start address with 3-byte address
            addrLen = 3;
            //PRINTF("S8 record: Start address (3 bytes).\n");
            *dataLen = 0;
            return true;

        case '9': // Start address with 2-byte address
            addrLen = 2;
            //PRINTF("S9 record: Start address (2 bytes).\n");
            *dataLen = 0;
            return true;

        default:
            PRINTF("Unsupported S record type detected '%c'", rcType);
            return false;
    }

    /* Assign addresses from data to record types that require addresses */
    *addr = 0;
    for (unsigned i = 0; i < addrLen; i++)
    {
        *addr = (*addr << 8) | data[i];
    }

    /* Delete the address part in data and assign dataLen*/
    *dataLen = byteCount - addrLen - 1;
    memmove(data, data + addrLen, *dataLen);
    return true;
}


void printArray(unsigned char *buf, size_t size)
{

	if ( size == 0 )
    {
		printf("--");
	}
	for ( size_t i = 0; i < size; i++ )
    {
		printf("0x%02X ", *buf++);
	}
}
