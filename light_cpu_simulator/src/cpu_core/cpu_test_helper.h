/*
 * cpu_test_helper.h
 *
 *  Created on: Sep 11, 2017
 *      Author: jie
 */

#ifndef CPU_TEST_HELPER_H_
#define CPU_TEST_HELPER_H_
#include "cpu_core.h"

/*below MACRO is used to access CPU core registers*/
#define SET_CPU_REG(index, val)			(get_cpu()->CpuCore.R[index] = val)

#define SET_CPU_SR_FLAG_N(val)			(get_cpu()->CpuCore.SRCh[0] = (get_cpu()->CpuCore.SRCh[0] & 0X7f) | ((val & 1) << 7))
#define SET_CPU_SR_FLAG_Z(val)			(get_cpu()->CpuCore.SRCh[0] = (get_cpu()->CpuCore.SRCh[0] & 0Xbf) | ((val & 1) << 6))
#define SET_CPU_SR_FLAG_C(val)			(get_cpu()->CpuCore.SRCh[0] = (get_cpu()->CpuCore.SRCh[0] & 0Xdf) | ((val & 1) << 5))
#define SET_CPU_SR_FLAG_V(val)			(get_cpu()->CpuCore.SRCh[0] = (get_cpu()->CpuCore.SRCh[0] & 0Xef) | ((val & 1) << 4))

#define GET_CPU_REG(index)				(get_cpu()->CpuCore.R[index] )
#define GET_CPU_PC_REG()				(get_cpu()->CpuCore.R[31] )
#define GET_CPU_LR_REG()				(get_cpu()->CpuCore.R[30] )
#define GET_CPU_SR_REG()				(get_cpu()->CpuCore.R[29] )

#define GET_CPU_SR_FLAG_N(val)			((get_cpu()->CpuCore.SRCh[0] >> 7) & 1)
#define GET_CPU_SR_FLAG_Z(val)			((get_cpu()->CpuCore.SRCh[0] >> 6) & 1)
#define GET_CPU_SR_FLAG_C(val)			((get_cpu()->CpuCore.SRCh[0] >> 5) & 1)
#define GET_CPU_SR_FLAG_V(val)			((get_cpu()->CpuCore.SRCh[0] >> 4) & 1)

/*below MACRO is used to generate cpu instructions */
#define SET_INST_FORMAT_TYPE(ch, value)			(ch[0] = (((value & 0x03) << 6) | (ch[0] & 0x3F)))

#define SET_INST_TYPE1_2_4_OPCODE(ch, value)	(ch[0] = (((value & 0x0F) << 2) | (ch[0] & 0xC3)))
#define SET_INST_TYPE1_2_4_FLAG_A(ch, value)    (ch[0] = (((value & 0X01) << 1) | (ch[0] & 0xFD)))
#define SET_INST_TYPE1_2_4_FLAG_B(ch, value)    (ch[0] = (((value & 0X01) << 0) | (ch[0] & 0xFE)))
#define SET_INST_TYPE1_2_4_FLAG_C(ch, value)    (ch[1] = (((value & 0X01) << 7) | (ch[1] & 0x7F)))
#define SET_INST_TYPE1_2_4_FLAG_D(ch, value)    (ch[1] = (((value & 0X01) << 6) | (ch[1] & 0xBF)))
#define SET_INST_TYPE1_2_4_FLAG_E(ch, value)    (ch[1] = (((value & 0X01) << 5) | (ch[1] & 0xDF)))

#define SET_INST_TYPE3_OPCODE(ch, value)      	(ch[0] = (((value & 0x01) << 5) | (ch[0] & 0xDF)))
#define SET_INST_TYPE3_FLAG_A(ch, value)      	(ch[0] = (((value & 0x01) << 4) | (ch[0] & 0xEF)))
#define SET_INST_TYPE3_FLAG_B(ch, value)      	(ch[0] = (((value & 0x01) << 3) | (ch[0] & 0xF7)))
#define SET_INST_TYPE3_FLAG_C(ch, value)      	(ch[0] = (((value & 0x01) << 2) | (ch[0] & 0xFB)))
#define SET_INST_TYPE3_FLAG_D(ch, value)      	(ch[0] = (((value & 0x01) << 1) | (ch[0] & 0xFD)))
#define SET_INST_TYPE3_FLAG_E(ch, value)      	(ch[0] = (((value & 0x01) << 0) | (ch[0] & 0xFE)))

#define SET_INST_TYPE1_RD(ch, value)   			(ch[2] = (((value & 0X1F) << 2) | (ch[2] & 0x83)))
#define SET_INST_TYPE1_RB(ch, value)   			{ch[2] = (((value & 0X18) >> 3) | (ch[2] & 0xFC)); ch[3] = (((value & 0X07) << 5) | (ch[3] & 0x1F));}
#define SET_INST_TYPE1_RA(ch, value)   			(ch[3] = (((value & 0X1F) << 0) | (ch[3] & 0xE0)))

#define SET_INST_TYPE2_RD(ch, value)   			(ch[1] = (((value & 0X1F) << 0) | (ch[1] & 0xE0)))
#define SET_INST_TYPE2_RB(ch, value)   			(ch[2] = (((value & 0X1F) << 3) | (ch[2] & 0x07)))
#define SET_INST_TYPE2_IMM(ch, value)   		{ch[2] = (((value >> 8 ) & 0x7) | (ch[2] & 0xF8))); ch[3] = (value & 0XFF);}

#define SET_INST_TYPE3_IMM(ch, value)   		{ch[1] = ((value >> 16) & 0xFF); ch[2] = ((value >> 8) & 0xFF);ch[3] = (value & 0XFF);}

#define SET_INST_TYPE4_RD(ch, value)   			(ch[1] = (((value & 0X1F) << 0) | (ch[1] & 0xE0)))
#define SET_INST_TYPE4_IMM(ch, value)   		{ch[2] = (((value >> 8) & 0xFF); ch[3] = (value & 0XFF);}

//
#define SET_TYPE1_INSTRUCTION(ch, OPCODE, A, B, C, D, E, RD, RB, RA) \
{ \
	SET_INST_FORMAT_TYPE(ch, 0); \
	SET_INST_TYPE1_2_4_OPCODE(ch, OPCODE); \
	SET_INST_TYPE1_2_4_FLAG_A(ch, A); \
	SET_INST_TYPE1_2_4_FLAG_B(ch, B); \
	SET_INST_TYPE1_2_4_FLAG_C(ch, C); \
	SET_INST_TYPE1_2_4_FLAG_D(ch, D); \
	SET_INST_TYPE1_2_4_FLAG_E(ch, E); \
	SET_INST_TYPE1_RD(ch, RD);		  \
	SET_INST_TYPE1_RB(ch, RB);		  \
	SET_INST_TYPE1_RA(ch, RA);		  \
}

#define SET_TYPE2_INSTRUCTION(ch, OPCODE, A, B, C, D, E, RD, RB, IMM) \
{ \
	SET_INST_FORMAT_TYPE(ch, 1); \
	SET_INST_TYPE1_2_4_OPCODE(ch, OPCODE); \
	SET_INST_TYPE1_2_4_FLAG_A(ch, A); \
	SET_INST_TYPE1_2_4_FLAG_B(ch, B); \
	SET_INST_TYPE1_2_4_FLAG_C(ch, C); \
	SET_INST_TYPE1_2_4_FLAG_D(ch, D); \
	SET_INST_TYPE1_2_4_FLAG_E(ch, E); \
	SET_INST_TYPE2_RD(ch, RD);		  \
	SET_INST_TYPE2_RB(ch, RB);		  \
	SET_INST_TYPE2_IMM(ch, IMM);		  \
}

#define SET_TYPE3_INSTRUCTION(ch, OPCODE, A, B, C, D, E, IMM) \
{ \
	SET_INST_FORMAT_TYPE(ch, 2); \
	SET_INST_TYPE3_OPCODE(ch, OPCODE); \
	SET_INST_TYPE3_FLAG_A(ch, A); \
	SET_INST_TYPE3_FLAG_B(ch, B); \
	SET_INST_TYPE3_FLAG_C(ch, C); \
	SET_INST_TYPE3_FLAG_D(ch, D); \
	SET_INST_TYPE3_FLAG_E(ch, E); \
	SET_INST_TYPE3_IMM(ch, IMM);		  \
}

#define SET_TYPE4_INSTRUCTION(ch, OPCODE, A, B, C, D, E, RD, IMM) \
{ \
	SET_INST_FORMAT_TYPE(ch, 3); \
	SET_INST_TYPE1_2_4_OPCODE(ch, OPCODE); \
	SET_INST_TYPE1_2_4_FLAG_A(ch, A); \
	SET_INST_TYPE1_2_4_FLAG_B(ch, B); \
	SET_INST_TYPE1_2_4_FLAG_C(ch, C); \
	SET_INST_TYPE1_2_4_FLAG_D(ch, D); \
	SET_INST_TYPE1_2_4_FLAG_E(ch, E); \
	SET_INST_TYPE4_RD(ch, RD);		  \
	SET_INST_TYPE4_IMM(ch, IMM);		  \
}

// SET ALL INSTRUCTION HERE
#define SET_TYPE1_ADD(ch, RD, RB, RA)					SET_TYPE1_INSTRUCTION(ch, OP_ADD, 0, 0, 0, 0, 0, RD, RB, RA)
#define SET_TYPE1_ADDC(ch, RD, RB, RA)					SET_TYPE1_INSTRUCTION(ch, OP_ADD, 1, 0, 0, 0, 0, RD, RB, RA)

#define SET_TYPE1_SUB(ch, RD, RB, RA)					SET_TYPE1_INSTRUCTION(ch, OP_SUB, 0, 0, 0, 0, 0, RD, RB, RA)
#define SET_TYPE1_SUBC(ch, RD, RB, RA)					SET_TYPE1_INSTRUCTION(ch, OP_SUB, 1, 0, 0, 0, 0, RD, RB, RA)


#endif /* CPU_TEST_HELPER_H_ */
