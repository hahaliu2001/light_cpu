/*
 * cpu_instruction.h
 *
 *  Created on: Sep 9, 2017
 *      Author: jie
 */

#ifndef CPU_INSTRUCTION_H_
#define CPU_INSTRUCTION_H_

#define CPU_BIG_ENDIAN      1
#define CPU_LITTLE_ENDIAN   0
/* CPU could support big endian or little indian, here define*/
/*difference between big endian and little endian 
  assume data 0x12345678 store in address 0, 1,2,3
  address        0   1   2   3
  big endian    12  34  56  78
  little endian 78  56  34  12*/
//#ifndef CPU_ENDIAN
#define CPU_ENDIAN CPU_BIG_ENDIAN
//#endif


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


/*
BCDE	Suffix 	Flags 							Meaning
0000	EQ 		Z set 							equal
0001	NE		Z clear 						not equal
0010	CS		C set 							unsigned higher or same
0011	CC		C clear 						unsigned lower
0100	MI		N set 							signed negative
0101	PL		N clear 						signed positive or zero
0110	VS		V set 							overflow
0111	VC		V clear 						no overflow
1000	HI		C set and Z clear 				unsigned higher
1001	LS		C clear or Z set 				unsigned lower or same
1010	GE		N equals V 						signed greater or equal
1011	LT		N not equal to V 				signed less than
1100	GT		Z clear AND (N equals V)		signed greater than
1101	LE		Z set OR (N not equal to V)		signed less than or equal
1110	AL		(ignored) 						always
1111	RSV		not used
*/
/*       conditional flags, BCDE below is CPU instruction flags  */
/*     Suffix                 BCDE          Flags                           Meaning*/
#define COND_EQ 			0b0000		//  Z set 							equal
#define COND_NE				0b0001		//  Z clear 						not equal
#define COND_CS				0b0010		//  C set 							unsigned higher or same
#define COND_CC				0b0011		//  C clear 						unsigned lower
#define COND_MI				0b0100		//  N set 							signed negative
#define COND_PL				0b0101		//  N clear 						signed positive or zero
#define COND_VS				0b0110		//  V set 							overflow
#define COND_VC				0b0111		//  V clear 						no overflow
#define COND_HI				0b1000		//  C set and Z clear 				unsigned higher
#define COND_LS				0b1001		//  C clear or Z set 				unsigned lower or same
#define COND_GE				0b1010		//  N equals V 						signed greater or equal
#define COND_LT				0b1011		//  N not equal to V 				signed less than
#define COND_GT				0b1100		//  Z clear AND (N equals V)		signed greater than
#define COND_LE				0b1101		//  Z set OR (N not equal to V)		signed less than or equal
#define COND_AL				0b1110		//  (ignored) 						always
#define COND_RSV			0b1111		//  not used

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

/* cpu internal Register Index for mov_inner instruction*/
//     CPU internal Reg                  BCDE
#define INTERNAL_REG_SR                   0b0000      //SR
#define INTERNAL_REG_INT_INPUT            0b0001      //32 bits input int pins
#define INTERNAL_REG_INT_STATUS           0b0010      //32 bits int status
#define INTERNAL_REG_INT_MASK             0b0011      //32 bits int mask
#define INTERNAL_REG_INT_PRIORITY         0b0100      //int priority, each int occupy 8 bits
#define INTERNAL_REG_INT_RETURN_PC        0b0101      //return PC address for active registere
#define INTERNAL_REG_ACTIVE_INT_ID        0b0110      //active register id
#define INTERNAL_REG_ACTIVE_INT_POS       0b0111      //active register pos which is also current active INT number                                                      
#define INTERNAL_REG_RETI                 0b1101      //when it is used, return ACTIVE_INT_RETURN_PC and update ActiveIntPos
                        
unsigned int cpu_get_int_from_4char(unsigned char *Src);
void cpu_write_int_to_4char(unsigned int u32Src, unsigned char *Dst);
void cpu_move_from_4byte_to_4byte(unsigned char *pSrc, unsigned char *pDst);
void cpu_add_int_to_4byte(unsigned char *pSrc1, unsigned int u32Src2, unsigned char *pDst);

#endif /* CPU_INSTRUCTION_H_ */
