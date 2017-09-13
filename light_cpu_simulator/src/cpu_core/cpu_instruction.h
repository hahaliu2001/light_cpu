/*
 * cpu_instruction.h
 *
 *  Created on: Sep 9, 2017
 *      Author: jie
 */

#ifndef CPU_INSTRUCTION_H_
#define CPU_INSTRUCTION_H_

/* MACROs used to parse instruction, refer to documents in ./doc folder*/
#define GET_INST_FORMAT_TYPE(ch)       ((ch[0] >> 6) & 3)

#define GET_INST_TYPE1_2_4_OPCODE(ch)  ((ch[0] >> 2) & 0xF)
#define GET_INST_TYPE1_2_4_FLAG_A(ch)  ((ch[0] >> 1) & 1)
#define GET_INST_TYPE1_2_4_FLAG_B(ch)  (ch[0]  & 1)
#define GET_INST_TYPE1_2_4_FLAG_C(ch)  ((ch[1] >> 7) & 1)
#define GET_INST_TYPE1_2_4_FLAG_D(ch)  ((ch[1] >> 6) & 1)
#define GET_INST_TYPE1_2_4_FLAG_E(ch)  ((ch[1] >> 5) & 1)

#define GET_INST_TYPE3_OPCODE(ch)      ((ch[0] >> 5) & 1)
#define GET_INST_TYPE3_FLAG_A(ch)      ((ch[0] >> 4) & 1)
#define GET_INST_TYPE3_FLAG_B(ch)      ((ch[0] >> 3) & 1)
#define GET_INST_TYPE3_FLAG_C(ch)      ((ch[0] >> 2) & 1)
#define GET_INST_TYPE3_FLAG_D(ch)      ((ch[0] >> 1) & 1)
#define GET_INST_TYPE3_FLAG_E(ch)      ((ch[0] >> 0) & 1)

#define GET_INST_TYPE1_RD(ch)          ((ch[2] >> 2) & 0x1F)
#define GET_INST_TYPE1_RB(ch)      	   (((ch[2] & 3) << 3) | ((ch[3] >> 5) & 7))
#define GET_INST_TYPE1_RA(ch)          ((ch[3] >> 0) & 0x1F)

#define GET_INST_TYPE2_RD(ch)          ((ch[1] >> 0) & 0x1F)
#define GET_INST_TYPE2_RB(ch)          ((ch[2]  >> 3) & 0x1F)
#define GET_INST_TYPE2_IMM(ch)     	   (((ch[2] & 7)<<8) | ch[3])

#define GET_INST_TYPE3_IMM(ch) 		   ((ch[1] << 16) | (ch[2] << 8) | ch[3])

#define GET_INST_TYPE4_RD(ch)          (ch[1] & 0x1F)
#define GET_INST_TYPE4_IMM(ch)     	   ( (ch[2] << 8) | ch[3])

/*instruction opcode for format type 1,2,4*/
#define		OP_ADD			0b0000
#define		OP_SUB			0b0001
#define		OP_MPY			0b0010
#define		OP_AJMP			0b0011
#define		OP_RJMP			0b0100
#define		OP_MOV			0b0101
#define		OP_CMP			0b0110
#define		OP_SHIFT		0b0111
#define		OP_AND			0b1000
#define		OP_XOR			0b1001
#define		OP_NOT			0b1010
#define		OP_LD			0b1011
#define		OP_ST			0b1100
#define		OP_SWI			0b1101
#define		OP_MOV_INNER	0b1110

/*instruction opcode for format type 3*/
#define     T3_OP_AJMP      0b00
#define     T3_OP_RJMP      0b01

typedef struct
{
    unsigned int        OpName  ;               //instruction name
    unsigned int        (*func_ID_stage)(void); //function pointer on ID stage
    unsigned int        (*func_EX_stage)(void); //function pointer on EX stage
    unsigned int        (*func_MEM_stage)(void); //function pointer on MEM stage
    unsigned int        (*func_WB_stage)(void); //function pointer on WB stage
}S_INSTRCTION_CONTEXT;

unsigned int InitInstTable(S_INSTRCTION_CONTEXT *Format1InstMenu,
                           S_INSTRCTION_CONTEXT *Format2InstMenu,
                           S_INSTRCTION_CONTEXT *Format3InstMenu,
                           S_INSTRCTION_CONTEXT *Format4InstMenu);



#endif /* CPU_INSTRUCTION_H_ */
