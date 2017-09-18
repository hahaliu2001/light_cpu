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
#define	CPU_MAX_INT_NUM	8

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

#define SET_SR_FLAG_N(ch,val)  (ch[0] = (ch[0] & 0x7f) | ((val & 1) << 7))
#define SET_SR_FLAG_Z(ch,val)  (ch[0] = (ch[0] & 0xBf) | ((val & 1) << 6))
#define SET_SR_FLAG_C(ch,val)  (ch[0] = (ch[0] & 0xDf) | ((val & 1) << 5))
#define SET_SR_FLAG_V(ch,val)  (ch[0] = (ch[0] & 0xEf) | ((val & 1) << 4))

typedef struct
{
	/* CPU internal registers*/
    unsigned char  SRCh[4]; //status register,using 4 char instead of int to make code endian independent.
                            //  SRCh[0] bit 7 : N, negative bit
                            //  SRCh[0] bit 6 : Z, Zero bit
                            //  SRCh[0] bit 5 : C, Carry bit
                            //  SRCh[0] bit 4 : V, overflow bit

	unsigned int R[CPU_MAX_REG_NUM]; //general register,R31 is PC,R30 is link register,R29 is stack registers`
	unsigned char INT; //interrupt
	unsigned char INT_STATUS; //interrupt status
	unsigned char INT_MASK; //interrupt mask, 1 is enable, 0 is disable
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
	unsigned int Src1;
	unsigned int Src2;
	unsigned int *dst;
    unsigned int *Src1Reg;

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
