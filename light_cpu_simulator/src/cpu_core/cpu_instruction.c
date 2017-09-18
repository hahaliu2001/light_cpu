/*
 * cpu_instruction.c

 *
 *  Created on: Sep 9, 2017
 *      Author: jie
 */
#include "cpu_core.h"
#include "cpu_instruction.h"

static unsigned int CheckCondFlag(unsigned int Cond,unsigned int N,unsigned int Z,unsigned int C,unsigned int V);

unsigned int Format1_ADD_EX_stage	(void)
{
    CPU *pCpu= get_cpu();
	unsigned long long int s1,s2,d;
    unsigned int dLow32,dHigh32;

    s1 = (unsigned long long int)pCpu->Src1;
    s2 = (unsigned long long int)pCpu->Src2;
    if (pCpu->InstFlag.reg.A) //ADDC
    {
        d = s1 + s2 + (unsigned long long int)GET_SR_FLAG_C(pCpu->CpuCore.SRCh);
    }
    else
    {
        d = s1 + s2;
    }
    dLow32 = (unsigned int)d;
    dHigh32 = (unsigned int)(d>>32);
    //update dest
    *pCpu->dst = dLow32;

    //update SR falg bit
    SET_SR_FLAG_Z(pCpu->CpuCore.SRCh,(dLow32 == 0));
    SET_SR_FLAG_N(pCpu->CpuCore.SRCh,(dLow32 >> 31) & 1);
    SET_SR_FLAG_C(pCpu->CpuCore.SRCh,(dHigh32 & 1));

    /*V is set to 1 when two signed value add together and below condition happen:
      1. positive + positve = negative
      2. negative + negative = positive*/
    SET_SR_FLAG_V(pCpu->CpuCore.SRCh,((((int)pCpu->Src1 <0) && ((int)pCpu->Src2 <0) && ((int)dLow32 >0))
                                || (((int)pCpu->Src1 >0) && ((int)pCpu->Src2 >0) && ((int)dLow32 <0))));

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}

unsigned int Format1_ADD_MEM_stage	(void){ return 0;}
unsigned int Format1_ADD_WB_stage	(void){ return 0;}

unsigned int Format1_SUB_EX_stage	(void)
{
    CPU *pCpu= get_cpu();
	unsigned long long int s1,s2,d;
    unsigned int dLow32,dHigh32;

    s1 = (unsigned long long int)pCpu->Src1;
    s2 = (unsigned long long int)(0 - pCpu->Src2);
    if (pCpu->InstFlag.reg.A) //SBC
    {
        d = s1 + s2 + (unsigned long long int)GET_SR_FLAG_C(pCpu->CpuCore.SRCh) - 1;
    }
    else
    {
        d = s1 + s2;
    }
    dLow32 = (unsigned int)d;
    dHigh32 = (unsigned int)(d>>32);
    //update dest
    *pCpu->dst = dLow32;

    //update SR falg bit
    SET_SR_FLAG_Z(pCpu->CpuCore.SRCh,(dLow32==0));
    SET_SR_FLAG_N(pCpu->CpuCore.SRCh,(dLow32 >> 31) & 1);
    SET_SR_FLAG_C(pCpu->CpuCore.SRCh,(dHigh32 & 1));

    /*V is set to 1 when two signed value sub together and below condition happen:
      1. positive - negative = negative
      2. negative - positive = positive*/
    SET_SR_FLAG_V(pCpu->CpuCore.SRCh,((((int)pCpu->Src1 >0) && ((int)pCpu->Src2 <0) && ((int)dLow32 <0))
                                || (((int)pCpu->Src1 <0) && ((int)pCpu->Src2 >0) && ((int)dLow32 >0))));

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format1_SUB_MEM_stage	(void){ return 0;}
unsigned int Format1_SUB_WB_stage	(void){ return 0;}

unsigned int Format1_MPY_EX_stage	(void)
{
    CPU *pCpu= get_cpu();

    *pCpu->dst = pCpu->Src1 *  pCpu->Src2;

    //update SR flag bit
    SET_SR_FLAG_Z(pCpu->CpuCore.SRCh,(*pCpu->dst==0));
    SET_SR_FLAG_N(pCpu->CpuCore.SRCh,(*pCpu->dst >> 31) & 1);

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format1_MPY_MEM_stage	(void){ return 0;}
unsigned int Format1_MPY_WB_stage	(void){ return 0;}


unsigned int Format1_MOV_EX_stage	(void)
{
    CPU *pCpu= get_cpu();

    *pCpu->dst = pCpu->Src1;

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format1_MOV_MEM_stage	(void){ return 0;}
unsigned int Format1_MOV_WB_stage	(void){ return 0;}

unsigned int Format1_CMP_EX_stage	(void)
{
    CPU *pCpu= get_cpu();
    unsigned long long int s1,s2,d;
    unsigned int dLow32,dHigh32;


    s1 = (unsigned long long int)pCpu->Src1;
    s2 = (unsigned long long int)(0 - pCpu->Src2);
    d = s1 + s2;

    dLow32 = (unsigned int)d;
    dHigh32 = (unsigned int)(d>>32);

    //update SR falg bit
    SET_SR_FLAG_Z(pCpu->CpuCore.SRCh,(dLow32==0));
    SET_SR_FLAG_N(pCpu->CpuCore.SRCh,(dLow32 >> 31) & 1);
    SET_SR_FLAG_C(pCpu->CpuCore.SRCh,(dHigh32 & 1));

    /*V is set to 1 when two signed value sub together and below condition happen:
      1. positive - negative = negative
      2. negative - positive = positive*/
    SET_SR_FLAG_V(pCpu->CpuCore.SRCh,((((int)pCpu->Src1 >0) && ((int)pCpu->Src2 <0) && ((int)dLow32 <0))
                                || (((int)pCpu->Src1 <0) && ((int)pCpu->Src2 >0) && ((int)dLow32 >0))));

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format1_CMP_MEM_stage	(void){ return 0;}
unsigned int Format1_CMP_WB_stage	(void){ return 0;}

unsigned int Format1_SHIFT_EX_stage	(void)
{
    unsigned long long int s1,d;
    unsigned int dLow32,dHigh32;
    int i32Shift;
    CPU *pCpu= get_cpu();

    i32Shift = (int)pCpu->Src2;

    if (i32Shift >=0) //left shift is the same for logical and arithmetical shift
    {
        s1 = (unsigned long long int)pCpu->Src1;
        d = s1 << i32Shift;
        dLow32 = (unsigned int)d;
        dHigh32 = (unsigned int)(d>>32);
        *pCpu->dst = dLow32;
        //set flag
        SET_SR_FLAG_C(pCpu->CpuCore.SRCh,(dHigh32 != 0));
        SET_SR_FLAG_Z(pCpu->CpuCore.SRCh,(0 == dLow32));
    }
    else  //for right shift
    {
        if (pCpu->InstFlag.reg.A) //logic shift
        {
           *pCpu->dst = (unsigned int)((int)pCpu->Src1 >> (-i32Shift));
        }
        else  //arithmetical shift
        {
            *pCpu->dst = (unsigned int)pCpu->Src1 >> (-i32Shift);
        }
        SET_SR_FLAG_Z(pCpu->CpuCore.SRCh,(0 == *pCpu->dst));
        SET_SR_FLAG_C(pCpu->CpuCore.SRCh,0);
    }

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format1_SHIFT_MEM_stage(void){ return 0;}
unsigned int Format1_SHIFT_WB_stage(void){ return 0;}

unsigned int Format1_AND_EX_stage	(void)
{
    CPU *pCpu= get_cpu();
    unsigned int Ra,Rb,Rd;

    if (pCpu->InstFlag.reg.B)
    {
        Rb = ~pCpu->Src1;
    }
    else
    {
        Rb = pCpu->Src1;
    }

    if (pCpu->InstFlag.reg.C)
    {
        Ra = ~pCpu->Src2;
    }
    else
    {
        Ra = pCpu->Src2;
    }

    Rd = Ra & Rb;

    if (pCpu->InstFlag.reg.A)
    {
        *pCpu->dst = ~Rd;
    }
    else
    {
        *pCpu->dst = Rd;
    }
    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format1_AND_MEM_stage	(void){ return 0;}
unsigned int Format1_AND_WB_stage	(void){ return 0;}

unsigned int Format1_XOR_EX_stage	(void)
{
    CPU *pCpu= get_cpu();
    unsigned int Ra,Rb,Rd;

    if (pCpu->InstFlag.reg.B)
    {
        Rb = ~pCpu->Src1;
    }
    else
    {
        Rb = pCpu->Src1;
    }

    if (pCpu->InstFlag.reg.C)
    {
        Ra = ~pCpu->Src2;
    }
    else
    {
        Ra = pCpu->Src2;
    }

    Rd = Ra ^ Rb;

    if (pCpu->InstFlag.reg.A)
    {
        *pCpu->dst = ~Rd;
    }
    else
    {
        *pCpu->dst = Rd;
    }
    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format1_XOR_MEM_stage	(void){ return 0;}
unsigned int Format1_XOR_WB_stage	(void){ return 0;}

unsigned int Format1_NOT_EX_stage	(void)
{
    CPU *pCpu= get_cpu();
    *pCpu->dst = ~pCpu->Src1;

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format1_NOT_MEM_stage	(void){ return 0;}
unsigned int Format1_NOT_WB_stage	(void){ return 0;}


/* calculate mem address*/
unsigned int Format1_LD_EX_stage	(void)
{
    CPU *pCpu= get_cpu();

    pCpu->Src1 = (unsigned int)((int)pCpu->Src1 + (int)pCpu->Src2); //src1 save mem address

    //update stage
    pCpu->stage = CPU_STAGE_MEM;
    return 0;
}
/*read from data mem*/
unsigned int Format1_LD_MEM_stage	(void)
{
    CPU *pCpu= get_cpu();
    unsigned int *pDataMem = (unsigned int*)(pCpu->DataMemBase);
    pCpu->Src2 = pDataMem[pCpu->Src1>>2]; //read data with 4 bytes align

    //update stage
    pCpu->stage = CPU_STAGE_WB;
    return 0;
}
/*write back to register,check read byte/2 byte/4 bytes and signed flag
  the CPU is designed for big endian mode, shall check compiler endian mode and do different work*/
unsigned int Format1_LD_WB_stage	(void)
{
    CPU *pCpu= get_cpu();
    unsigned char *pCh = (unsigned char *)(&pCpu->Src2);
    unsigned int RdSize = pCpu->InstFlag.reg.A*2 + pCpu->InstFlag.reg.B;
    int Update = pCpu->InstFlag.reg.C * 4 + pCpu->InstFlag.reg.D * 2 + pCpu->InstFlag.reg.E;
    unsigned char c0,c1,c2,c3;
    unsigned int u32Value;
    int i32Value;

    switch (RdSize)
    {
    case 0: //read one byte
        c0 = pCh[pCpu->Src1 & 0x3]; // pCpu->Src1 & 0x3 return byte location in 4 bytes
        if (pCpu->InstFlag.reg.C) //if signed extension
        {
            i32Value = (int)c0;
            i32Value = (i32Value << 24) >> 24;
            *pCpu->dst = (unsigned int)i32Value;
        }
        else
        {
            *pCpu->dst = (unsigned int)c0;
        }
        break;
    case 1: //read 2 bytes
        c0 = pCh[((pCpu->Src1 >> 1) & 1) << 1];
        c1 = pCh[(((pCpu->Src1 >> 1) & 1) << 1)+1];
        u32Value = ((unsigned int)c0 << 8) + (unsigned int)c1;
        if (pCpu->InstFlag.reg.C) //if signed extension
        {
            i32Value = (int)u32Value;
            i32Value = (i32Value << 16) >> 16;
            *pCpu->dst = (unsigned int)i32Value;
        }
        else
        {
            *pCpu->dst = u32Value;
        }
        break;
    case 2:  //four byte
        c0 = pCh[0];
        c1 = pCh[1];
        c2 = pCh[2];
        c3 = pCh[3];
        u32Value = ((unsigned int)c0 << 24) + ((unsigned int)c1 << 16) +((unsigned int)c2 << 8) +(unsigned int)c3;
        *pCpu->dst = u32Value;
        if (pCpu->Src1Reg)
        {
            switch (Update)
            {
            case 0: *pCpu->Src1Reg += 0; break;
            case 1: *pCpu->Src1Reg += 1; break;
            case 2: *pCpu->Src1Reg += 2; break;
            case 3: *pCpu->Src1Reg += 4; break;
            case 4: *pCpu->Src1Reg -= 0; break;
            case 5: *pCpu->Src1Reg -= 1; break;
            case 6: *pCpu->Src1Reg -= 2; break;
            case 7: *pCpu->Src1Reg -= 4; break;
            }
        }
        break; 
    default:
        return 1;

    }

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}

unsigned int Format1_ST_EX_stage	(void)
{

    return Format1_LD_EX_stage();
}
unsigned int Format1_ST_MEM_stage	(void)
{
    CPU *pCpu= get_cpu();
    unsigned int u32Value = *pCpu->dst;
    unsigned int u32Addr = pCpu->Src1;
    unsigned char c0,c1,c2,c3;
    unsigned int RdSize = pCpu->InstFlag.reg.A*2 + pCpu->InstFlag.reg.B;
    int Update = pCpu->InstFlag.reg.C * 4 + pCpu->InstFlag.reg.D * 2 + pCpu->InstFlag.reg.E;

    switch (RdSize)
    {
    case 0: //write one LSB byte
        pCpu->DataMemBase[u32Addr] = (unsigned char)(u32Value >> 0);
        break;
    case 1: //write two LSB bytes
        pCpu->DataMemBase[u32Addr] = (unsigned char)(u32Value >> 8);
        pCpu->DataMemBase[u32Addr + 1] = (unsigned char)(u32Value >> 0);
        break;
    case 2: //write four bytes
        c0 = (unsigned char)(u32Value >> 24); 
        c1 = (unsigned char)(u32Value >> 16);
        c2 = (unsigned char)(u32Value >> 8);
        c3 = (unsigned char)(u32Value >> 0);
        pCpu->DataMemBase[u32Addr+0] = c0;
        pCpu->DataMemBase[u32Addr+1] = c1;
        pCpu->DataMemBase[u32Addr+2] = c2;
        pCpu->DataMemBase[u32Addr+3] = c3;
        if (pCpu->Src1Reg)
        {
            switch (Update)
            {
            case 0: *pCpu->Src1Reg += 0; break;
            case 1: *pCpu->Src1Reg += 1; break;
            case 2: *pCpu->Src1Reg += 2; break;
            case 3: *pCpu->Src1Reg += 4; break;
            case 4: *pCpu->Src1Reg -= 0; break;
            case 5: *pCpu->Src1Reg -= 1; break;
            case 6: *pCpu->Src1Reg -= 2; break;
            case 7: *pCpu->Src1Reg -= 4; break;
            }
        }
        break;
    default:
        return 1;
    }

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format1_ST_WB_stage	(void){ return 0;}

unsigned int Format2_ADD_EX_stage	(void)
{
    int i32Value;
    CPU *pCpu= get_cpu();
    i32Value  =   pCpu->Src2;
    if (pCpu->InstFlag.reg.B) //if signed data
    {
        i32Value = (i32Value << 21) >> 21; //signed extended from 10bits to 32 bits
    }
    pCpu->Src2 =   (unsigned int)i32Value;
    return Format1_ADD_EX_stage();
}
unsigned int Format2_ADD_MEM_stage	        (void){ return 0;}
unsigned int Format2_ADD_WB_stage           (void){ return 0;}

unsigned int Format2_SUB_EX_stage	        (void)
{
    unsigned int d1,d2;
    int i32Value;
    CPU *pCpu= get_cpu();
    d1 = pCpu->Src1;

    i32Value = (int)pCpu->Src2;
    if (pCpu->InstFlag.reg.B) //if signed data
    {
        i32Value = (i32Value << 21) >> 21; //signed extended from 10bits to 32 bits
    }
    d2 =   (unsigned int)i32Value;

    if (pCpu->InstFlag.reg.C) //reserve, Imme - Rb
    {
        pCpu->Src1 = d2;
        pCpu->Src2 = d1;
    }
    else
    {
        pCpu->Src1 = d1;
        pCpu->Src2 = d2;
    }
    return Format1_SUB_EX_stage();
}
unsigned int Format2_SUB_MEM_stage	        (void){ return 0;}
unsigned int Format2_SUB_WB_stage           (void){ return 0;}


unsigned int Format2_MPY_EX_stage	        (void)
{
    int i32Value;
    CPU *pCpu= get_cpu();
    i32Value = (int)pCpu->Src2;
    if (pCpu->InstFlag.reg.A) //if signed data
    {
        i32Value = (i32Value << 21) >> 21; //signed extended from 10bits to 32 bits
    }
    pCpu->Src2 =   (unsigned int)i32Value;
    return Format1_MPY_EX_stage();
}
unsigned int Format2_MPY_MEM_stage	        (void){ return 0;}
unsigned int Format2_MPY_WB_stage           (void){ return 0;}

unsigned int Format2_SHIFT_EX_stage	        (void)
{
    CPU *pCpu= get_cpu();
    int i32Value = (int)pCpu->Src2;
    i32Value = (i32Value << 21) >> 21; //signed extended from 10bits to 32 bits
    pCpu->Src2 = (unsigned int)i32Value;
    return Format1_SHIFT_EX_stage();
}
unsigned int Format2_SHIFT_MEM_stage	    (void){ return 0;}
unsigned int Format2_SHIFT_WB_stage         (void){ return 0;}

unsigned int Format2_LD_EX_stage	        (void)
{
    CPU *pCpu= get_cpu();
    int i32Value = (int)pCpu->Src2;
    i32Value = (i32Value << 21) >> 21; //signed extended from 10bits to 32 bits
    pCpu->Src1 = (unsigned int)((int)pCpu->Src1 + i32Value); //src1 save mem address

    //update stage
    pCpu->stage = CPU_STAGE_MEM;
    return 0;
}
unsigned int Format2_LD_MEM_stage	        (void)
{
    return Format1_LD_MEM_stage();
}
unsigned int Format2_LD_WB_stage            (void)
{
    return Format1_LD_WB_stage();
}

unsigned int Format2_ST_EX_stage	        (void)
{
    return Format2_LD_EX_stage();
}
unsigned int Format2_ST_MEM_stage	        (void)
{
    return Format1_ST_MEM_stage();
}
unsigned int Format2_ST_WB_stage            (void){ return 0;}

unsigned int Format2_SWI_EX_stage	        (void){ return 0;}
unsigned int Format2_SWI_MEM_stage	        (void){ return 0;}
unsigned int Format2_SWI_WB_stage           (void){ return 0;}

unsigned int Format2_MOV_INNER_EX_stage	    (void){ return 0;}
unsigned int Format2_MOV_INNER_MEM_stage	(void){ return 0;}
unsigned int Format2_MOV_INNER_WB_stage     (void){ return 0;}

unsigned int Format3_AJMP_EX_stage(void)
{
    //first based on conditioan flag and SR flage to see if need jump or not
    // A is Jump with link flag,when 1, save PC to R30
    /*B,C,D define jump condition
       condition:  	B/C/D	Z	N
    unconditional	0x1	    x	x
    equeal	        010 	1	x
    not-equal	    000 	0	x
    large	        100 	0	0
    large-equal	    110 	1	0
    small	        101 	0	1
    small-equal	    111 	1	1
     */
    unsigned int Z,N,C,V;
    unsigned int A,B,Cx,D,E;
    CPU *pCpu= get_cpu();

    A = pCpu->InstFlag.reg.A;
    B = pCpu->InstFlag.reg.B;
    Cx = pCpu->InstFlag.reg.C;
    D = pCpu->InstFlag.reg.D;
    E = pCpu->InstFlag.reg.E;

    Z = GET_SR_FLAG_Z(pCpu->CpuCore.SRCh);
    N = GET_SR_FLAG_N(pCpu->CpuCore.SRCh);
    C = GET_SR_FLAG_C(pCpu->CpuCore.SRCh);
    V = GET_SR_FLAG_V(pCpu->CpuCore.SRCh);

    if(CheckCondFlag(B*8+Cx*4+D*2+E,N,Z,C,V))
    {
        // when need jump
        if (A)
        {
            pCpu->CpuCore.R[30] = pCpu->CpuCore.R[31];
        }
        pCpu->CpuCore.R[31] = (pCpu->Src1 << 2) ; //address is in 4 bytes,shall left by 4
    }

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format3_AJMP_MEM_stage	        (void){ return 0;}
unsigned int Format3_AJMP_WB_stage          (void){ return 0;}


unsigned int Format3_RJMP_EX_stage	        (void)
{
    CPU *pCpu= get_cpu();
    int i32Value = (int)(pCpu->Src1);
    i32Value = (i32Value << 8) >> 8;
    //RJMP shall jump to current location + i32Value, while R[31] point to next instruction location, 
    // so "- 1" is needed
    pCpu->Src1 = i32Value + (pCpu->CpuCore.R[31] >> 2) - 1; 
    return Format3_AJMP_EX_stage();
}
unsigned int Format3_RJMP_MEM_stage	        (void){ return 0;}
unsigned int Format3_RJMP_WB_stage          (void){ return 0;}


unsigned int Format4_AJMP_EX_stage	        (void)
{
    CPU *pCpu= get_cpu();
    int i32Value = (int)(pCpu->Src1);
    i32Value = (i32Value << 16) >> 14;
    pCpu->Src1 = (i32Value + *pCpu->dst) >> 2;

    return Format3_AJMP_EX_stage();
}
unsigned int Format4_AJMP_MEM_stage	        (void){ return 0;}
unsigned int Format4_AJMP_WB_stage          (void){ return 0;}

unsigned int Format4_RJMP_EX_stage	        (void)
{
    CPU *pCpu= get_cpu();
    int i32Value = (int)(pCpu->Src1);
    i32Value = (i32Value << 16) >> 14;
    //RJMP shall jump to current location + i32Value, while R[31] point to next instruction location, 
    // so "- 1" is needed
    pCpu->Src1 = (unsigned int)((i32Value + *pCpu->dst + pCpu->CpuCore.R[31] - 1) >> 2);
    return Format3_AJMP_EX_stage();
}
unsigned int Format4_RJMP_MEM_stage	        (void){ return 0;}
unsigned int Format4_RJMP_WB_stage          (void){ return 0;}


unsigned int Format4_MOV_EX_stage	        (void)
{
    CPU *pCpu= get_cpu();
    int i32Value = (int)(pCpu->Src1);
    if (pCpu->InstFlag.reg.A) //signed
    {
        i32Value = (i32Value << 16) >> 16;
        pCpu->Src1 = (unsigned int)i32Value;
    }
    return Format1_MOV_EX_stage();
}
unsigned int Format4_MOV_MEM_stage	        (void){ return 0;}
unsigned int Format4_MOV_WB_stage           (void){ return 0;}

unsigned int Format4_CMP_EX_stage	        (void)
{
    CPU *pCpu= get_cpu();
    int i32Value = (int)(pCpu->Src1);
    if (pCpu->InstFlag.reg.A) //signed
    {
        i32Value = (i32Value << 16) >> 16;
        pCpu->Src1 = (unsigned int)i32Value;
    }
    pCpu->Src2 = pCpu->Src1;
    pCpu->Src1 = *pCpu->dst;
    return Format1_CMP_EX_stage();
}
unsigned int Format4_CMP_MEM_stage	        (void){ return 0;}
unsigned int Format4_CMP_WB_stage           (void){ return 0;}

unsigned int Format4_LD_EX_stage	        (void)
{
    CPU *pCpu= get_cpu();

   //update stage
    pCpu->stage = CPU_STAGE_MEM;
    return 0;
}
unsigned int Format4_LD_MEM_stage	        (void)
{
    return Format1_LD_MEM_stage();
}
unsigned int Format4_LD_WB_stage            (void)
{
    return Format1_LD_WB_stage();
}

unsigned int Format4_ST_EX_stage	        (void)
{
    return Format4_LD_EX_stage();
}
unsigned int Format4_ST_MEM_stage	        (void)
{
    return Format1_ST_MEM_stage();
}
unsigned int Format4_ST_WB_stage            (void){ return 0;}

unsigned int Format1_ID_stage(void)
{
    CPU *pCpu= get_cpu();
    unsigned int DstReg,SrcReg;

    pCpu->InstFlag.reg.A = GET_INST_TYPE1_2_4_FLAG_A(pCpu->InstCh); //
    pCpu->InstFlag.reg.B = GET_INST_TYPE1_2_4_FLAG_B(pCpu->InstCh);
    pCpu->InstFlag.reg.C = GET_INST_TYPE1_2_4_FLAG_C(pCpu->InstCh);
    pCpu->InstFlag.reg.D = GET_INST_TYPE1_2_4_FLAG_D(pCpu->InstCh);
    pCpu->InstFlag.reg.E = GET_INST_TYPE1_2_4_FLAG_E(pCpu->InstCh);

    DstReg  = GET_INST_TYPE1_RD(pCpu->InstCh);
    pCpu->dst =    &pCpu->CpuCore.R[DstReg];

    SrcReg  =   GET_INST_TYPE1_RB(pCpu->InstCh);
    pCpu->Src1 =   pCpu->CpuCore.R[SrcReg];

    pCpu->Src1Reg = &pCpu->CpuCore.R[SrcReg];

    SrcReg  =   GET_INST_TYPE1_RA(pCpu->InstCh);
    pCpu->Src2 =   pCpu->CpuCore.R[SrcReg];

    //move to next stage
    pCpu->stage = CPU_STAGE_EX;
    return 0;
}

unsigned int Format2_ID_stage(void)
{
    CPU *pCpu= get_cpu();
    unsigned int DstReg,SrcReg;

    pCpu->InstFlag.reg.A = GET_INST_TYPE1_2_4_FLAG_A(pCpu->InstCh); //
    pCpu->InstFlag.reg.B = GET_INST_TYPE1_2_4_FLAG_B(pCpu->InstCh);
    pCpu->InstFlag.reg.C = GET_INST_TYPE1_2_4_FLAG_C(pCpu->InstCh);
    pCpu->InstFlag.reg.D = GET_INST_TYPE1_2_4_FLAG_D(pCpu->InstCh);
    pCpu->InstFlag.reg.E = GET_INST_TYPE1_2_4_FLAG_E(pCpu->InstCh);

    DstReg  = GET_INST_TYPE2_RD(pCpu->InstCh);
    pCpu->dst =    &pCpu->CpuCore.R[DstReg];

    SrcReg  =   GET_INST_TYPE2_RB(pCpu->InstCh);
    pCpu->Src1 =   pCpu->CpuCore.R[SrcReg];
    pCpu->Src1Reg = 0;
    pCpu->Src2  =   GET_INST_TYPE2_IMM(pCpu->InstCh);

    //move to next stage
    pCpu->stage = CPU_STAGE_EX;
    return 0;

}

unsigned int Format3_ID_stage(void)
{
    CPU *pCpu= get_cpu();

    pCpu->InstFlag.reg.A = GET_INST_TYPE3_FLAG_A(pCpu->InstCh); //
    pCpu->InstFlag.reg.B = GET_INST_TYPE3_FLAG_B(pCpu->InstCh);
    pCpu->InstFlag.reg.C = GET_INST_TYPE3_FLAG_C(pCpu->InstCh);
    pCpu->InstFlag.reg.D = GET_INST_TYPE3_FLAG_D(pCpu->InstCh);
    pCpu->InstFlag.reg.E = GET_INST_TYPE3_FLAG_E(pCpu->InstCh);

    pCpu->Src1  =   GET_INST_TYPE3_IMM(pCpu->InstCh);
    pCpu->Src1Reg = 0;
    //move to next stage
    pCpu->stage = CPU_STAGE_EX;
    return 0;

}
unsigned int Format4_ID_stage(void)
{
    CPU *pCpu= get_cpu();
    unsigned int DstReg;

    pCpu->InstFlag.reg.A = GET_INST_TYPE1_2_4_FLAG_A(pCpu->InstCh); //
    pCpu->InstFlag.reg.B = GET_INST_TYPE1_2_4_FLAG_B(pCpu->InstCh);
    pCpu->InstFlag.reg.C = GET_INST_TYPE1_2_4_FLAG_C(pCpu->InstCh);
    pCpu->InstFlag.reg.D = GET_INST_TYPE1_2_4_FLAG_D(pCpu->InstCh);
    pCpu->InstFlag.reg.E = GET_INST_TYPE1_2_4_FLAG_E(pCpu->InstCh);

    DstReg  = GET_INST_TYPE4_RD(pCpu->InstCh);
    pCpu->dst =    &pCpu->CpuCore.R[DstReg];

    pCpu->Src1  =   GET_INST_TYPE4_IMM(pCpu->InstCh);
    pCpu->Src1Reg = 0;
    //move to next stage
    pCpu->stage = CPU_STAGE_EX;
    return 0;
}


unsigned int InitInstTable(S_INSTRCTION_CONTEXT *Format1InstMenu,
                           S_INSTRCTION_CONTEXT *Format2InstMenu,
                           S_INSTRCTION_CONTEXT *Format3InstMenu,
                           S_INSTRCTION_CONTEXT *Format4InstMenu)
{
    int m;
    //first reset all to 0
    for (m=0;m<16;m++)
    {
        //format 1
        Format1InstMenu[m].func_EX_stage = 0;
        Format1InstMenu[m].func_ID_stage = 0;
        Format1InstMenu[m].func_MEM_stage = 0;
        Format1InstMenu[m].func_WB_stage = 0;
        Format1InstMenu[m].OpName = m;

        //format 2
        Format2InstMenu[m].func_EX_stage = 0;
        Format2InstMenu[m].func_ID_stage = 0;
        Format2InstMenu[m].func_MEM_stage = 0;
        Format2InstMenu[m].func_WB_stage = 0;
        Format2InstMenu[m].OpName = m;

        //format 4
        Format4InstMenu[m].func_EX_stage = 0;
        Format4InstMenu[m].func_ID_stage = 0;
        Format4InstMenu[m].func_MEM_stage = 0;
        Format4InstMenu[m].func_WB_stage = 0;
        Format4InstMenu[m].OpName = m;

    }
    for (m=0; m<2;m++)
    {
        //format 3
        Format3InstMenu[m].func_EX_stage = 0;
        Format3InstMenu[m].func_ID_stage = 0;
        Format3InstMenu[m].func_MEM_stage = 0;
        Format3InstMenu[m].func_WB_stage = 0;
        Format3InstMenu[m].OpName = m;

    }

    /* format 1 menu init*/
    Format1InstMenu[0].func_ID_stage 	= Format1_ID_stage;
    Format1InstMenu[0].func_EX_stage 	= Format1_ADD_EX_stage;
    Format1InstMenu[0].func_MEM_stage 	= Format1_ADD_MEM_stage;
    Format1InstMenu[0].func_WB_stage 	= Format1_ADD_WB_stage;
    Format1InstMenu[1].func_ID_stage 	= Format1_ID_stage		;
    Format1InstMenu[1].func_EX_stage 	= Format1_SUB_EX_stage		;
    Format1InstMenu[1].func_MEM_stage 	= Format1_SUB_MEM_stage		;
    Format1InstMenu[1].func_WB_stage 	= Format1_SUB_WB_stage		;
	Format1InstMenu[2].func_ID_stage 	= Format1_ID_stage	;
    Format1InstMenu[2].func_EX_stage 	= Format1_MPY_EX_stage	;
    Format1InstMenu[2].func_MEM_stage 	= Format1_MPY_MEM_stage	;
    Format1InstMenu[2].func_WB_stage 	= Format1_MPY_WB_stage	;
    Format1InstMenu[5].func_ID_stage 	= Format1_ID_stage	;
    Format1InstMenu[5].func_EX_stage 	= Format1_MOV_EX_stage	;
    Format1InstMenu[5].func_MEM_stage 	= Format1_MOV_MEM_stage	;
    Format1InstMenu[5].func_WB_stage 	= Format1_MOV_WB_stage	;
	Format1InstMenu[6].func_ID_stage 	= Format1_ID_stage	;
    Format1InstMenu[6].func_EX_stage 	= Format1_CMP_EX_stage	;
    Format1InstMenu[6].func_MEM_stage 	= Format1_CMP_MEM_stage	;
    Format1InstMenu[6].func_WB_stage 	= Format1_CMP_WB_stage	;
	Format1InstMenu[7].func_ID_stage 	= Format1_ID_stage ;
    Format1InstMenu[7].func_EX_stage 	= Format1_SHIFT_EX_stage	;
    Format1InstMenu[7].func_MEM_stage 	= Format1_SHIFT_MEM_stage;
    Format1InstMenu[7].func_WB_stage 	= Format1_SHIFT_WB_stage ;
	Format1InstMenu[8].func_ID_stage 	= Format1_ID_stage	;
    Format1InstMenu[8].func_EX_stage 	= Format1_AND_EX_stage	;
    Format1InstMenu[8].func_MEM_stage 	= Format1_AND_MEM_stage	;
    Format1InstMenu[8].func_WB_stage 	= Format1_AND_WB_stage	;
	Format1InstMenu[9].func_ID_stage 	= Format1_ID_stage	;
    Format1InstMenu[9].func_EX_stage 	= Format1_XOR_EX_stage	;
    Format1InstMenu[9].func_MEM_stage 	= Format1_XOR_MEM_stage	;
    Format1InstMenu[9].func_WB_stage 	= Format1_XOR_WB_stage	;
	Format1InstMenu[10].func_ID_stage 	= Format1_ID_stage	;
    Format1InstMenu[10].func_EX_stage 	= Format1_NOT_EX_stage	;
    Format1InstMenu[10].func_MEM_stage 	= Format1_NOT_MEM_stage	;
    Format1InstMenu[10].func_WB_stage 	= Format1_NOT_WB_stage	;
	Format1InstMenu[11].func_ID_stage 	= Format1_ID_stage	;
    Format1InstMenu[11].func_EX_stage 	= Format1_LD_EX_stage	;
    Format1InstMenu[11].func_MEM_stage 	= Format1_LD_MEM_stage	;
    Format1InstMenu[11].func_WB_stage 	= Format1_LD_WB_stage	;
	Format1InstMenu[12].func_ID_stage 	= Format1_ID_stage	;
    Format1InstMenu[12].func_EX_stage 	= Format1_ST_EX_stage	;
    Format1InstMenu[12].func_MEM_stage 	= Format1_ST_MEM_stage	;
    Format1InstMenu[12].func_WB_stage 	= Format1_ST_WB_stage	;

    //format 2
    	Format2InstMenu[0].func_ID_stage 	= Format2_ID_stage			;
    Format2InstMenu[0].func_EX_stage 	= Format2_ADD_EX_stage			;
    Format2InstMenu[0].func_MEM_stage 	= Format2_ADD_MEM_stage		;
    Format2InstMenu[0].func_WB_stage 	= Format2_ADD_WB_stage			;
    Format2InstMenu[1].func_ID_stage 	= Format2_ID_stage		;
    Format2InstMenu[1].func_EX_stage 	= Format2_SUB_EX_stage		;
    Format2InstMenu[1].func_MEM_stage 	= Format2_SUB_MEM_stage		;
    Format2InstMenu[1].func_WB_stage 	= Format2_SUB_WB_stage		;
	Format2InstMenu[2].func_ID_stage 	= Format2_ID_stage		;
    Format2InstMenu[2].func_EX_stage 	= Format2_MPY_EX_stage		;
    Format2InstMenu[2].func_MEM_stage 	= Format2_MPY_MEM_stage		;
    Format2InstMenu[2].func_WB_stage 	= Format2_MPY_WB_stage		;
	Format2InstMenu[7].func_ID_stage 	= Format2_ID_stage 	;
    Format2InstMenu[7].func_EX_stage 	= Format2_SHIFT_EX_stage	;
    Format2InstMenu[7].func_MEM_stage 	= Format2_SHIFT_MEM_stage	;
    Format2InstMenu[7].func_WB_stage 	= Format2_SHIFT_WB_stage 	;
	Format2InstMenu[11].func_ID_stage 	= Format2_ID_stage		;
    Format2InstMenu[11].func_EX_stage 	= Format2_LD_EX_stage		;
    Format2InstMenu[11].func_MEM_stage 	= Format2_LD_MEM_stage		;
    Format2InstMenu[11].func_WB_stage 	= Format2_LD_WB_stage		;
	Format2InstMenu[12].func_ID_stage 	= Format2_ID_stage		;
    Format2InstMenu[12].func_EX_stage 	= Format2_ST_EX_stage		;
    Format2InstMenu[12].func_MEM_stage 	= Format2_ST_MEM_stage		;
    Format2InstMenu[12].func_WB_stage 	= Format2_ST_WB_stage		;
	Format2InstMenu[13].func_ID_stage 	= Format2_ID_stage	    	;
    Format2InstMenu[13].func_EX_stage 	= Format2_SWI_EX_stage	    	;
    Format2InstMenu[13].func_MEM_stage 	= Format2_SWI_MEM_stage	    	;
    Format2InstMenu[13].func_WB_stage 	= Format2_SWI_WB_stage       	;
	Format2InstMenu[14].func_ID_stage 	= Format2_ID_stage		;
    Format2InstMenu[14].func_EX_stage 	= Format2_MOV_INNER_EX_stage		;
    Format2InstMenu[14].func_MEM_stage 	= Format2_MOV_INNER_MEM_stage	;
    Format2InstMenu[14].func_WB_stage 	= Format2_MOV_INNER_WB_stage 	;

    //format 3
    Format3InstMenu[0].func_ID_stage 	= Format3_ID_stage			;
    Format3InstMenu[0].func_EX_stage 	= Format3_AJMP_EX_stage			;
    Format3InstMenu[0].func_MEM_stage 	= Format3_AJMP_MEM_stage		;
    Format3InstMenu[0].func_WB_stage 	= Format3_AJMP_WB_stage  		;
    Format3InstMenu[1].func_ID_stage 	= Format3_ID_stage		;
    Format3InstMenu[1].func_EX_stage 	= Format3_RJMP_EX_stage		;
    Format3InstMenu[1].func_MEM_stage 	= Format3_RJMP_MEM_stage		;
    Format3InstMenu[1].func_WB_stage 	= Format3_RJMP_WB_stage  	;

    //format 4
    Format4InstMenu[3].func_ID_stage 	= Format4_ID_stage		;
    Format4InstMenu[3].func_EX_stage 	= Format4_AJMP_EX_stage		;
    Format4InstMenu[3].func_MEM_stage 	= Format4_AJMP_MEM_stage	;
    Format4InstMenu[3].func_WB_stage 	= Format4_AJMP_WB_stage 	;
	Format4InstMenu[4].func_ID_stage 	= Format4_ID_stage		;
    Format4InstMenu[4].func_EX_stage 	= Format4_RJMP_EX_stage		;
    Format4InstMenu[4].func_MEM_stage 	= Format4_RJMP_MEM_stage	;
    Format4InstMenu[4].func_WB_stage 	= Format4_RJMP_WB_stage 	;
	Format4InstMenu[5].func_ID_stage 	= Format4_ID_stage		;
    Format4InstMenu[5].func_EX_stage 	= Format4_MOV_EX_stage		;
    Format4InstMenu[5].func_MEM_stage 	= Format4_MOV_MEM_stage		;
    Format4InstMenu[5].func_WB_stage 	= Format4_MOV_WB_stage  	;
	Format4InstMenu[6].func_ID_stage 	= Format4_ID_stage		;
    Format4InstMenu[6].func_EX_stage 	= Format4_CMP_EX_stage		;
    Format4InstMenu[6].func_MEM_stage 	= Format4_CMP_MEM_stage		;
    Format4InstMenu[6].func_WB_stage 	= Format4_CMP_WB_stage  	;
	Format4InstMenu[11].func_ID_stage 	= Format4_ID_stage		;
    Format4InstMenu[11].func_EX_stage 	= Format4_LD_EX_stage		;
    Format4InstMenu[11].func_MEM_stage 	= Format4_LD_MEM_stage		;
    Format4InstMenu[11].func_WB_stage 	= Format4_LD_WB_stage   	;
	Format4InstMenu[12].func_ID_stage 	= Format4_ID_stage		;
    Format4InstMenu[12].func_EX_stage 	= Format4_ST_EX_stage		;
    Format4InstMenu[12].func_MEM_stage 	= Format4_ST_MEM_stage		;
    Format4InstMenu[12].func_WB_stage 	= Format4_ST_WB_stage   	;
    return 0;
}

/* for Jump instruction, check conditioanl flags*/
static unsigned int CheckCondFlag(unsigned int Cond,unsigned int N,unsigned int Z,unsigned int C,unsigned int V)
{
    switch (Cond)
    {
    case COND_EQ: //EQ
        return Z;
    case COND_NE: //NE
        return (1 - Z);
    case COND_CS: //CS
        return C;
    case COND_CC: //CC
        return (1 - C);
    case COND_MI: //MI
        return N;
    case COND_PL: //PL
        return (1 - N);
    case COND_VS: //VS
        return V;
    case COND_VC: //VC
        return (1 - V);
    case COND_HI: //HI
        return C && (1-Z);
    case COND_LS: //LS
        return (1-C) || Z;
    case COND_GE: //GE
        return (N == V);
    case COND_LT: //LT
        return (N != V);
    case COND_GT: //GT
        return (1 - Z) && ( N == V);
    case COND_LE: //LE
        return Z || (N != V);
    case COND_AL: //AL
        return 1;
    case COND_RSV: //RSV
        return 0;
    }
    return 0;
}


