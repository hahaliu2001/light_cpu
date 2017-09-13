/*
 * mem.c
 *
 *  Created on: Sep 9, 2017
 *      Author: jie
 */

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

unsigned char DataMem[DATA_MEM_SIZE][4];
unsigned char InstMem[INSTRUCTION_MEM_SIZE][4];
unsigned char StackMem[STACK_MEM_SIZE][4];

#define MEM_INIT_VALUE	0x00
void init_mem(unsigned char *Mem, int MemSizeIn4Bytes)
{
	int i;
	for (i=0; i<MemSizeIn4Bytes * 4; i++) 
	{
		Mem[i] = MEM_INIT_VALUE;
	}
	
}

void read_mem(unsigned char *Mem, int MemAddr, unsigned char *ReadMemData)
{
	ReadMemData[0] = Mem[MemAddr];
	ReadMemData[1] = Mem[MemAddr + 1];
	ReadMemData[2] = Mem[MemAddr + 2];
	ReadMemData[3] = Mem[MemAddr + 3];
}

void write_mem(unsigned char *Mem, int MemAddr, unsigned char *WriteMemData)
{
	Mem[MemAddr] 	 = WriteMemData[0];
	Mem[MemAddr + 1] = WriteMemData[1];
	Mem[MemAddr + 2] = WriteMemData[2];
	Mem[MemAddr + 3] = WriteMemData[3];
}

void write_mem_from_string(unsigned char *Mem, char *DataString)
{
	char HexChar[4];
	char hexbyte[3] = {0} ;
	int d;
	//first convert the string to hex char
	for( d = 0; d < 8; d += 2 )
    {
        // Assemble a digit pair into the hexbyte string
        hexbyte[0] = DataString[d] ;
        hexbyte[1] = DataString[d+1] ;
 
        // Convert the hex pair to an integer
        sscanf( hexbyte, "%X", &HexChar[d/2] ) ;
 
        // Show the integer has a hex pair with prefix
        //printf( "0x%2.2X\n", HexChar[d/2] ) ;
    }
	
	Mem[0] = HexChar[0];
	Mem[1] = HexChar[1];
	Mem[2] = HexChar[2];
	Mem[3] = HexChar[3];
}

