/*
 * cpu_core.h
 *
 *  Created on: Sep 9, 2017
 *      Author: jie
 */

#ifndef CPU_CORE_H_
#define CPU_CORE_H_

#include "cpu_instruction.h"

#define CPU_MAX_REG_NUM 32
#define	CPU_MAX_INT_NUM	32

#define NO_INT_FLAG     0

#define CPU_ENTRY_RESERVE_SIZE  256 //memory address from 0 - 255 are used to CPU init processing
#define INT_ENTRY_MEM_SIZE  32
#define INTERNAL_INT_NUM    8
#define EXTERNAL_INT_NUM    8
#define SWI_NUM             (CPU_MAX_INT_NUM - INTERNAL_INT_NUM - EXTERNAL_INT_NUM)  //number of SWI

/*there are 5 RISC stage */
#define CPU_STAGE_IF	0 //instruction fetch stage to read instruction from instruction mem
#define CPU_STAGE_ID	1 //instruction decode
#define CPU_STAGE_EX	2 //execute stage
#define CPU_STAGE_MEM	3 //access data memory stage, it may write data to data mem or read from data memory
#define CPU_STAGE_WB 	4 //write back stage, the data that read from data mem can write to register in this stage

#define GET_SR_FLAG_N(ch)  ((ch[0] >> 7) & 1)
#define GET_SR_FLAG_Z(ch)  ((ch[0] >> 6) & 1)
#define GET_SR_FLAG_C(ch)  ((ch[0] >> 5) & 1)
#define GET_SR_FLAG_V(ch)  ((ch[0] >> 4) & 1)
#define GET_SR_FLAG_INT(ch)  ((ch[3] >> 7) & 1)

#define SET_SR_FLAG_N(ch,val)  (ch[0] = (ch[0] & 0x7f) | ((val & 1) << 7))
#define SET_SR_FLAG_Z(ch,val)  (ch[0] = (ch[0] & 0xBf) | ((val & 1) << 6))
#define SET_SR_FLAG_C(ch,val)  (ch[0] = (ch[0] & 0xDf) | ((val & 1) << 5))
#define SET_SR_FLAG_V(ch,val)  (ch[0] = (ch[0] & 0xEf) | ((val & 1) << 4))
#define SET_SR_FLAG_INT(ch,val)  (ch[3] = (ch[3] & 0x7f) | ((val & 1) << 7))

typedef struct
{
	/* CPU internal registers*/
    /*status register,using 4 char instead of int to make code endian independent. 
    SRCh[0] bit 7 : N, negative bit
    SRCh[0] bit 6 : Z, Zero bit
    SRCh[0] bit 5 : C, Carry bit
    SRCh[0] bit 4 : V, overflow bit
    SRCh[3] bit 7 : INT global enable. 1: enable, 0: disable
      */
    unsigned char  SRCh[4]; //
                            
	unsigned char R[CPU_MAX_REG_NUM][4]; //general register,R31 is PC,R30 is link register,R29 is stack registers`
	unsigned char INT_input[CPU_MAX_INT_NUM]; //interrupt. INT 0 -7 are reserved for CPU internal, 8-15 for external, 16-31 for SWI
	unsigned char INT_STATUS[CPU_MAX_INT_NUM]; //interrupt status, 1 is int active
	unsigned char INT_MASK[CPU_MAX_INT_NUM]; //interrupt mask, 1 is enable, 0 is disable
    unsigned char INT_priority[CPU_MAX_INT_NUM]; //from 0 - 31. 0 is highest
    unsigned char INT_ReturnPC[CPU_MAX_INT_NUM][4]; //used to store returning PC address when exit from INT
    unsigned char ActiveIntId[CPU_MAX_INT_NUM];  //0xFF means not under int state
    unsigned int ActiveIntPos;
}CPU_CORE ;

/* below is used to define Flags retrived from instructions */
typedef union
{
    unsigned char Char;
    struct
    {
        unsigned char A     :   1;  
        unsigned char B     :   1;  
        unsigned char C     :   1;  
        unsigned char D     :   1;  
        unsigned char E     :   1;
        unsigned char Rsv2  :   3;

    } reg;
} INST_FLAG_u ;	//

typedef struct
{
    CPU_CORE  CpuCore;

    //instruction memory
	unsigned char *InstMemBase;  //instuction memory base address
	unsigned int InstMemSizeInByte; // instruction size in byte

	//data memory
	unsigned char *DataMemBase;	//data memory base address
	unsigned int DataMemSizeInBtye;	// data memory size in byte

	//stack memory
	unsigned char *StackMemBase;	//stack memory base address, this is highest address of stack
	unsigned int StackMemSizeInBtye;	// stack memory size in byte

    // veriables from instrution
	unsigned char InstCh[4];
    INST_FLAG_u   InstFlag;
	unsigned char Src1[4];
	unsigned char Src2[4];
	unsigned char *dst;
    unsigned char *Src1Reg;

	/* stage destinition */
	unsigned int stage; //current stage
	unsigned int (*stage_if_cb)(void); //IF stage callback
	unsigned int (*stage_id_cb)(void); //ID stage callback
	unsigned int (*stage_ex_cb)(void); //EX stage callback
	unsigned int (*stage_mem_cb)(void); //MEM stage callback
	unsigned int (*stage_wb_cb)(void); //WB stage callback
} CPU;

unsigned int run_cpu_in_if_stage();
unsigned int run_cpu_in_id_stage();
extern CPU* get_cpu();


#endif /* CPU_CORE_H_ */
