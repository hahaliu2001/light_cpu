/*
 * mem.h
 *
 *  Created on: Sep 9, 2017
 *      Author: jie
 */

#ifndef MEM_H_
#define MEM_H_

#define DATA_MEM_SIZE 1024
#define INSTRUCTION_MEM_SIZE 1024
#define STACK_MEM_SIZE 1024

extern unsigned char DataMem[DATA_MEM_SIZE][4];
extern unsigned char InstMem[INSTRUCTION_MEM_SIZE][4];
extern unsigned char StackMem[STACK_MEM_SIZE][4];

void init_mem(unsigned char *Mem, int MemSize);

void read_mem(unsigned char *Mem, int MemAddr, unsigned char *ReadMemData);

void write_mem(unsigned char *Mem, int MemAddr, unsigned char *WriteMemData);

void write_mem_from_string(unsigned char *Mem, char *DataString);

#endif /* MEM_H_ */
