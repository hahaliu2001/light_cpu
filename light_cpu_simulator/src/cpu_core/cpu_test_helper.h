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
#define SET_CPU_REG(index, val)			(cpu_write_int_to_4char(val, get_cpu()->CpuCore.R[index]))

#define SET_CPU_SR_FLAG_N(val)			(get_cpu()->CpuCore.SRCh[0] = (get_cpu()->CpuCore.SRCh[0] & 0X7f) | ((val & 1) << 7))
#define SET_CPU_SR_FLAG_Z(val)			(get_cpu()->CpuCore.SRCh[0] = (get_cpu()->CpuCore.SRCh[0] & 0Xbf) | ((val & 1) << 6))
#define SET_CPU_SR_FLAG_C(val)			(get_cpu()->CpuCore.SRCh[0] = (get_cpu()->CpuCore.SRCh[0] & 0Xdf) | ((val & 1) << 5))
#define SET_CPU_SR_FLAG_V(val)			(get_cpu()->CpuCore.SRCh[0] = (get_cpu()->CpuCore.SRCh[0] & 0Xef) | ((val & 1) << 4))

#define GET_CPU_REG(index)				(cpu_get_int_from_4char(get_cpu()->CpuCore.R[index]) )
#define GET_CPU_PC_REG()				(cpu_get_int_from_4char(get_cpu()->CpuCore.R[31]) )
#define GET_CPU_LR_REG()				(cpu_get_int_from_4char(get_cpu()->CpuCore.R[30]) )
#define GET_CPU_SR_REG()				(cpu_get_int_from_4char(get_cpu()->CpuCore.R[29]) )

//#define READ_CPU_SRCH(dst)				(cpu_move_from_4byte_to_4byte(get_cpu()->CpuCore.SRCh, dst) )
#define SET_CPU_SRCH(val)			    (cpu_write_int_to_4char(val, get_cpu()->CpuCore.SRCh))
#define GET_CPU_SRCH()				    (cpu_get_int_from_4char(get_cpu()->CpuCore.SRCh) )

#define GET_CPU_SR_FLAG_N(val)			((get_cpu()->CpuCore.SRCh[0] >> 7) & 1)
#define GET_CPU_SR_FLAG_Z(val)			((get_cpu()->CpuCore.SRCh[0] >> 6) & 1)
#define GET_CPU_SR_FLAG_C(val)			((get_cpu()->CpuCore.SRCh[0] >> 5) & 1)
#define GET_CPU_SR_FLAG_V(val)			((get_cpu()->CpuCore.SRCh[0] >> 4) & 1)

#define SET_CPU_INT_INPUT(pos, val)     (get_cpu()->CpuCore.INT_input[(pos)] = val)
#define SET_CPU_INT_STATUS(pos, val)    (get_cpu()->CpuCore.INT_STATUS[(pos)] = val)
#define SET_CPU_INT_MASK(pos, val)      (get_cpu()->CpuCore.INT_MASK[(pos)] = val)
#define SET_CPU_INT_PRIORITY(pos, val)  (get_cpu()->CpuCore.INT_priority[(pos)] = val)
#define SET_CPU_ACTIVE_INT_RETURN_PC(pos, val) (cpu_write_int_to_4char(val, get_cpu()->CpuCore.INT_ReturnPC[(pos)]))
#define SET_CPU_ACTIVE_INT_PRIORITY(pos, val)  (get_cpu()->CpuCore.ActiveIntId[(pos)] = val)
#define SET_CPU_ACTIVE_INT_POS(val)     (get_cpu()->CpuCore.ActiveIntPos = val)

#define GET_CPU_INT_INPUT(pos)          (get_cpu()->CpuCore.INT_input[(pos)])
#define GET_CPU_INT_STATUS(pos)         (get_cpu()->CpuCore.INT_STATUS[(pos)])
#define GET_CPU_INT_MASK(pos)           (get_cpu()->CpuCore.INT_MASK[(pos)])
#define GET_CPU_INT_PRIORITY(pos)       (get_cpu()->CpuCore.INT_priority[(pos)])
#define GET_CPU_ACTIVE_INT_RETURN_PC(pos) (cpu_get_int_from_4char(get_cpu()->CpuCore.INT_ReturnPC[(pos)]))
#define GET_CPU_ACTIVE_INT_PRIORITY(pos)  (get_cpu()->CpuCore.ActiveIntId[(pos)])
#define GET_CPU_ACTIVE_INT_POS()        (get_cpu()->CpuCore.ActiveIntPos)

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
#define SET_INST_TYPE2_IMM(ch, value)   		{ch[2] = (((value >> 8 ) & 0x7) | (ch[2] & 0xF8)); ch[3] = (value & 0XFF);}

#define SET_INST_TYPE3_IMM(ch, value)   		{ch[1] = ((value >> 16) & 0xFF); ch[2] = ((value >> 8) & 0xFF);ch[3] = (value & 0XFF);}

#define SET_INST_TYPE4_RD(ch, value)   			(ch[1] = (((value & 0X1F) << 0) | (ch[1] & 0xE0)))
#define SET_INST_TYPE4_IMM(ch, value)   		{ch[2] = ((value >> 8) & 0xFF); ch[3] = (value & 0XFF);}

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

#define SET_TYPE1_MPY(ch, RD, RB, RA)					SET_TYPE1_INSTRUCTION(ch, OP_MPY, 0, 0, 0, 0, 0, RD, RB, RA)

#define SET_TYPE1_MOVE(ch, RD, RB)						SET_TYPE1_INSTRUCTION(ch, OP_MOV, 0, 0, 0, 0, 0, RD, RB, 0)

#define SET_TYPE1_CMP(ch, RB, RA)						SET_TYPE1_INSTRUCTION(ch, OP_CMP, 0, 0, 0, 0, 0, 0, RB, RA)

#define SET_TYPE1_ARITH_SHIFT(ch, RD, RB, RA)			SET_TYPE1_INSTRUCTION(ch, OP_SHIFT, 0, 0, 0, 0, 0, RD, RB, RA)
#define SET_TYPE1_LOGIC_SHIFT(ch, RD, RB, RA)			SET_TYPE1_INSTRUCTION(ch, OP_SHIFT, 1, 0, 0, 0, 0, RD, RB, RA)

#define SET_TYPE1_AND(ch, RD, RB, RA)			        SET_TYPE1_INSTRUCTION(ch, OP_AND, 0, 0, 0, 0, 0, RD, RB, RA)
#define SET_TYPE1_NOT_AND(ch, RD, RB, RA)			    SET_TYPE1_INSTRUCTION(ch, OP_AND, 1, 0, 0, 0, 0, RD, RB, RA)
#define SET_TYPE1_OR(ch, RD, RB, RA)			        SET_TYPE1_INSTRUCTION(ch, OP_AND, 1, 1, 1, 0, 0, RD, RB, RA)
#define SET_TYPE1_NOT_OR(ch, RD, RB, RA)			    SET_TYPE1_INSTRUCTION(ch, OP_AND, 0, 1, 1, 0, 0, RD, RB, RA)

#define SET_TYPE1_XOR(ch, RD, RB, RA)			        SET_TYPE1_INSTRUCTION(ch, OP_XOR, 0, 0, 0, 0, 0, RD, RB, RA)
#define SET_TYPE1_NOT_XOR(ch, RD, RB, RA)			    SET_TYPE1_INSTRUCTION(ch, OP_XOR, 1, 0, 0, 0, 0, RD, RB, RA)

#define SET_TYPE1_NOT(ch, RD, RB)			            SET_TYPE1_INSTRUCTION(ch, OP_NOT, 0, 0, 0, 0, 0, RD, RB, 0)

#define SET_TYPE1_LD_4_BYTE(ch, C, D, E, RD, RB, RA)	SET_TYPE1_INSTRUCTION(ch, OP_LD, 1, 0, C, D, E, RD, RB, RA)
#define SET_TYPE1_LD_UNSIGNED_1_BYTE(ch, RD, RB, RA)	SET_TYPE1_INSTRUCTION(ch, OP_LD, 0, 0, 0, 0, 0, RD, RB, RA)
#define SET_TYPE1_LD_SIGNED_1_BYTE(ch, RD, RB, RA)	    SET_TYPE1_INSTRUCTION(ch, OP_LD, 0, 0, 1, 0, 0, RD, RB, RA)
#define SET_TYPE1_LD_UNSIGNED_2_BYTE(ch, RD, RB, RA)	SET_TYPE1_INSTRUCTION(ch, OP_LD, 0, 1, 0, 0, 0, RD, RB, RA)
#define SET_TYPE1_LD_SIGNED_2_BYTE(ch, RD, RB, RA)	    SET_TYPE1_INSTRUCTION(ch, OP_LD, 0, 1, 1, 0, 0, RD, RB, RA)

#define SET_TYPE1_ST_1_BYTE(ch, RD, RB, RA)		        SET_TYPE1_INSTRUCTION(ch, OP_ST, 0, 0, 0, 0, 0, RD, RB, RA)
#define SET_TYPE1_ST_2_BYTE(ch, RD, RB, RA)		        SET_TYPE1_INSTRUCTION(ch, OP_ST, 0, 1, 0, 0, 0, RD, RB, RA)
#define SET_TYPE1_ST_4_BYTE(ch, C, D, E, RD, RB, RA)	SET_TYPE1_INSTRUCTION(ch, OP_ST, 1, 0, C, D, E, RD, RB, RA)

#define SET_TYPE2_UNSIGNED_ADD(ch, RD, RB, IMM)			SET_TYPE2_INSTRUCTION(ch, OP_ADD, 0, 0, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_UNSIGNED_ADDC(ch, RD, RB, IMM)		SET_TYPE2_INSTRUCTION(ch, OP_ADD, 1, 0, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_SIGNED_ADD(ch, RD, RB, IMM)			SET_TYPE2_INSTRUCTION(ch, OP_ADD, 0, 1, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_SIGNED_ADDC(ch, RD, RB, IMM)		    SET_TYPE2_INSTRUCTION(ch, OP_ADD, 1, 1, 0, 0, 0, RD, RB, IMM)

#define SET_TYPE2_UNSIGNED_SUB(ch, RD, RB, IMM)			SET_TYPE2_INSTRUCTION(ch, OP_SUB, 0, 0, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_UNSIGNED_SUBC(ch, RD, RB, IMM)		SET_TYPE2_INSTRUCTION(ch, OP_SUB, 1, 0, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_SIGNED_SUB(ch, RD, RB, IMM)			SET_TYPE2_INSTRUCTION(ch, OP_SUB, 0, 1, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_SIGNED_SUBC(ch, RD, RB, IMM)		    SET_TYPE2_INSTRUCTION(ch, OP_SUB, 1, 1, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_UNSIGNED_RSUB(ch, RD, RB, IMM)		SET_TYPE2_INSTRUCTION(ch, OP_SUB, 0, 0, 1, 0, 0, RD, RB, IMM)
#define SET_TYPE2_UNSIGNED_RSUBC(ch, RD, RB, IMM)		SET_TYPE2_INSTRUCTION(ch, OP_SUB, 1, 0, 1, 0, 0, RD, RB, IMM)
#define SET_TYPE2_SIGNED_RSUB(ch, RD, RB, IMM)			SET_TYPE2_INSTRUCTION(ch, OP_SUB, 0, 1, 1, 0, 0, RD, RB, IMM)
#define SET_TYPE2_SIGNED_RSUBC(ch, RD, RB, IMM)		    SET_TYPE2_INSTRUCTION(ch, OP_SUB, 1, 1, 1, 0, 0, RD, RB, IMM)

#define SET_TYPE2_UNSIGNED_MPY(ch, RD, RB, IMM)			SET_TYPE2_INSTRUCTION(ch, OP_MPY, 0, 0, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_SIGNED_MPY(ch, RD, RB, IMM)			SET_TYPE2_INSTRUCTION(ch, OP_MPY, 1, 0, 0, 0, 0, RD, RB, IMM)

#define SET_TYPE2_ARITH_SHIFT(ch, RD, RB, IMM)			SET_TYPE2_INSTRUCTION(ch, OP_SHIFT, 1, 0, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_LOGIC_SHIFT(ch, RD, RB, IMM)			SET_TYPE2_INSTRUCTION(ch, OP_SHIFT, 0, 0, 0, 0, 0, RD, RB, IMM)

#define SET_TYPE2_LD_4_BYTE(ch, RD, RB, IMM)		    SET_TYPE2_INSTRUCTION(ch, OP_LD, 1, 0, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_LD_UNSIGNED_1_BYTE(ch, RD, RB, IMM)	SET_TYPE2_INSTRUCTION(ch, OP_LD, 0, 0, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_LD_SIGNED_1_BYTE(ch, RD, RB, IMM)	    SET_TYPE2_INSTRUCTION(ch, OP_LD, 0, 0, 1, 0, 0, RD, RB, IMM)
#define SET_TYPE2_LD_UNSIGNED_2_BYTE(ch, RD, RB, IMM)	SET_TYPE2_INSTRUCTION(ch, OP_LD, 0, 1, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_LD_SIGNED_2_BYTE(ch, RD, RB, IMM)	    SET_TYPE2_INSTRUCTION(ch, OP_LD, 0, 1, 1, 0, 0, RD, RB, IMM)

#define SET_TYPE2_ST_1_BYTE(ch, RD, RB, IMM)		    SET_TYPE2_INSTRUCTION(ch, OP_ST, 0, 0, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_ST_2_BYTE(ch, RD, RB, IMM)		    SET_TYPE2_INSTRUCTION(ch, OP_ST, 0, 1, 0, 0, 0, RD, RB, IMM)
#define SET_TYPE2_ST_4_BYTE(ch, RD, RB, IMM)		    SET_TYPE2_INSTRUCTION(ch, OP_ST, 1, 0, 0, 0, 0, RD, RB, IMM)

#define SET_TYPE2_SWI(ch, RB)		                    SET_TYPE2_INSTRUCTION(ch, OP_SWI, 0, 0, 0, 0, 0, 0, RB, 0)
#define SET_TYPE2_SWI_IMM(ch, IMM)		                SET_TYPE2_INSTRUCTION(ch, OP_SWI, 1, 0, 0, 0, 0, 0, 0, IMM)

#define SET_TYPE2_MOVE_INNER_WRITE(ch, TYPE, RD, RB)	SET_TYPE2_INSTRUCTION(ch, OP_MOV_INNER, 0, ((TYPE >> 3) & 1), ((TYPE >> 2) & 1), ((TYPE >> 1) & 1), ((TYPE >> 0) & 1), RD, RB, 0x7FF)
#define SET_TYPE2_MOVE_INNER_READ(ch, TYPE, RD, RB)	    SET_TYPE2_INSTRUCTION(ch, OP_MOV_INNER, 1, ((TYPE >> 3) & 1), ((TYPE >> 2) & 1), ((TYPE >> 1) & 1), ((TYPE >> 0) & 1), RD, RB, 0x7FF)

#define SET_TYPE2_MOVE_INNER_WRITE_IMM(ch, TYPE, RD, IMM)	SET_TYPE2_INSTRUCTION(ch, OP_MOV_INNER, 0, ((TYPE >> 3) & 1), ((TYPE >> 2) & 1), ((TYPE >> 1) & 1), ((TYPE >> 0) & 1), RD, 0, IMM)
#define SET_TYPE2_MOVE_INNER_READ_IMM(ch, TYPE, RD, IMM)	SET_TYPE2_INSTRUCTION(ch, OP_MOV_INNER, 1, ((TYPE >> 3) & 1), ((TYPE >> 2) & 1), ((TYPE >> 1) & 1), ((TYPE >> 0) & 1), RD, 0, IMM)

#define SET_TYPE3_AJMP(ch, COND, IMM)	                SET_TYPE3_INSTRUCTION(ch, T3_OP_AJMP, 0, ((COND >> 3) & 1), ((COND >> 2) & 1), ((COND >> 1) & 1), ((COND >> 0) & 1), IMM)
#define SET_TYPE3_AJMPL(ch, COND, IMM)	                SET_TYPE3_INSTRUCTION(ch, T3_OP_AJMP, 1, ((COND >> 3) & 1), ((COND >> 2) & 1), ((COND >> 1) & 1), ((COND >> 0) & 1), IMM)

#define SET_TYPE3_RJMP(ch, COND, IMM)	                SET_TYPE3_INSTRUCTION(ch, T3_OP_RJMP, 0, ((COND >> 3) & 1), ((COND >> 2) & 1), ((COND >> 1) & 1), ((COND >> 0) & 1), IMM)
#define SET_TYPE3_RJMPL(ch, COND, IMM)	                SET_TYPE3_INSTRUCTION(ch, T3_OP_RJMP, 1, ((COND >> 3) & 1), ((COND >> 2) & 1), ((COND >> 1) & 1), ((COND >> 0) & 1), IMM)

#define SET_TYPE4_AJMP(ch, COND, RD, IMM)	            SET_TYPE4_INSTRUCTION(ch, OP_AJMP, 0, ((COND >> 3) & 1), ((COND >> 2) & 1), ((COND >> 1) & 1), ((COND >> 0) & 1), RD, IMM)
#define SET_TYPE4_AJMPL(ch, COND, RD, IMM)	            SET_TYPE4_INSTRUCTION(ch, OP_AJMP, 1, ((COND >> 3) & 1), ((COND >> 2) & 1), ((COND >> 1) & 1), ((COND >> 0) & 1), RD, IMM)

#define SET_TYPE4_RJMP(ch, COND, RD, IMM)	            SET_TYPE4_INSTRUCTION(ch, OP_RJMP, 0, ((COND >> 3) & 1), ((COND >> 2) & 1), ((COND >> 1) & 1), ((COND >> 0) & 1), RD, IMM)
#define SET_TYPE4_RJMPL(ch, COND, RD, IMM)	            SET_TYPE4_INSTRUCTION(ch, OP_RJMP, 1, ((COND >> 3) & 1), ((COND >> 2) & 1), ((COND >> 1) & 1), ((COND >> 0) & 1), RD, IMM)

#define SET_TYPE4_UNSIGNED_MOV(ch, RD, IMM)	            SET_TYPE4_INSTRUCTION(ch, OP_MOV, 0, 0, 0, 0, 0, RD, IMM)
#define SET_TYPE4_SIGNED_MOV(ch, RD, IMM)	            SET_TYPE4_INSTRUCTION(ch, OP_MOV, 1, 0, 0, 0, 0, RD, IMM)

#define SET_TYPE4_UNSIGNED_CMP(ch, RD, IMM)	            SET_TYPE4_INSTRUCTION(ch, OP_CMP, 0, 0, 0, 0, 0, RD, IMM)
#define SET_TYPE4_SIGNED_CMP(ch, RD, IMM)	            SET_TYPE4_INSTRUCTION(ch, OP_CMP, 1, 0, 0, 0, 0, RD, IMM)

#define SET_TYPE4_LD_4_BYTE(ch, RD, IMM)		        SET_TYPE4_INSTRUCTION(ch, OP_LD, 1, 0, 0, 0, 0, RD, IMM)
#define SET_TYPE4_LD_UNSIGNED_1_BYTE(ch, RD, IMM)	    SET_TYPE4_INSTRUCTION(ch, OP_LD, 0, 0, 0, 0, 0, RD, IMM)
#define SET_TYPE4_LD_SIGNED_1_BYTE(ch, RD, IMM)	        SET_TYPE4_INSTRUCTION(ch, OP_LD, 0, 0, 1, 0, 0, RD, IMM)
#define SET_TYPE4_LD_UNSIGNED_2_BYTE(ch, RD, IMM)	    SET_TYPE4_INSTRUCTION(ch, OP_LD, 0, 1, 0, 0, 0, RD, IMM)
#define SET_TYPE4_LD_SIGNED_2_BYTE(ch, RD, IMM)	        SET_TYPE4_INSTRUCTION(ch, OP_LD, 0, 1, 1, 0, 0, RD, IMM)

#define SET_TYPE4_ST_1_BYTE(ch, RD, IMM)		        SET_TYPE4_INSTRUCTION(ch, OP_ST, 0, 0, 0, 0, 0, RD, IMM)
#define SET_TYPE4_ST_2_BYTE(ch, RD, IMM)		        SET_TYPE4_INSTRUCTION(ch, OP_ST, 0, 1, 0, 0, 0, RD, IMM)
#define SET_TYPE4_ST_4_BYTE(ch, RD, IMM)		        SET_TYPE4_INSTRUCTION(ch, OP_ST, 1, 0, 0, 0, 0, RD, IMM)

#define SET_ERROR_INST(ch)                              SET_TYPE1_INSTRUCTION(ch, (0b1111), 0, 0, 0, 0, 0, 0, 0, 0)
#endif /* CPU_TEST_HELPER_H_ */
