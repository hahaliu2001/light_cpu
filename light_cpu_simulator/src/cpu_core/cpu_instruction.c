/*
 * cpu_instruction.c

 *
 *  Created on: Sep 9, 2017
 *      Author: jie
 */
#include "cpu_core.h"
#include "cpu_instruction.h"

static unsigned int CheckCondFlag(unsigned int Cond,unsigned int N,unsigned int Z,unsigned int C,unsigned int V);

static void cpu_int_add_core(unsigned int u32Src1, unsigned int u32Src2, unsigned int InputC, 
                 unsigned char *N, unsigned char *Z, unsigned char *C, unsigned char *V, unsigned int *pu32Dst)
{
    //do add
    unsigned long long int s1,s2,d;
    unsigned int dLow32,dHigh32;

    s1 = (unsigned long long int)u32Src1;
    s2 = (unsigned long long int)u32Src2;
    d = s1 + s2 + (unsigned long long int)InputC;
    
    dLow32 = (unsigned int)d;
    dHigh32 = (unsigned int)(d>>32);
    //update dest
    *pu32Dst = dLow32;

    //update SR falg bit
    *Z = (dLow32 == 0);
    *N = ((dLow32 >> 31) & 1);
    *C = (dHigh32 & 1);

    /*V is set to 1 when two signed value add together and below condition happen:
      1. positive + positve = negative
      2. negative + negative = positive*/
    *V = ((((int)u32Src1 <0) && ((int)u32Src2 <0) && ((int)dLow32 >0))
      || (((int)u32Src1 >0) && ((int)u32Src2 >0) && ((int)dLow32 <0)));
}

#if (CPU_ENDIAN == CPU_BIG_ENDIAN)

unsigned int cpu_get_int_from_4char(unsigned char *Src)
{
    return ((((unsigned int)(Src[0])) << 24) + (((unsigned int)(Src[1])) << 16) + (((unsigned int)(Src[2])) << 8) + (((unsigned int)(Src[3])) << 0));
}

void cpu_write_int_to_4char(unsigned int u32Src, unsigned char *Dst)
{
    Dst[0] = (unsigned char)((u32Src >> 24) & 0xff);
    Dst[1] = (unsigned char)((u32Src >> 16) & 0xff);
    Dst[2] = (unsigned char)((u32Src >> 8) & 0xff);
    Dst[3] = (unsigned char)((u32Src >> 0) & 0xff);
}

#else
unsigned int cpu_get_int_from_4char(unsigned char *Src)
{
    return ((((unsigned int)(Src[3])) << 24) + (((unsigned int)(Src[2])) << 16) + (((unsigned int)(Src[1])) << 8) + (((unsigned int)(Src[0])) << 0));
}

void cpu_write_int_to_4char(unsigned int u32Src, unsigned char *Dst)
{
    Dst[3] = (unsigned char)((u32Src >> 24) & 0xff);
    Dst[2] = (unsigned char)((u32Src >> 16) & 0xff);
    Dst[1] = (unsigned char)((u32Src >> 8) & 0xff);
    Dst[0] = (unsigned char)((u32Src >> 0) & 0xff);
}
#endif

void cpu_move_from_4byte_to_4byte(unsigned char *pSrc, unsigned char *pDst)
{
    pDst[0] = pSrc[0];
    pDst[1] = pSrc[1];
    pDst[2] = pSrc[2];
    pDst[3] = pSrc[3];
}

void cpu_add_int_to_4byte(unsigned char *pSrc1, unsigned int u32Src2, unsigned char *pDst)
{
    unsigned int u32Src1, u32Dst;
    
    u32Src1 = cpu_get_int_from_4char(pSrc1);
    
    u32Dst = u32Src1 + u32Src2;
    
    cpu_write_int_to_4char(u32Dst, pDst);
}

void cpu_sub_int_from_4byte(unsigned char *pSrc1, unsigned int u32Src2, unsigned char *pDst)
{
    unsigned int u32Src1, u32Dst;
    
    u32Src1 = cpu_get_int_from_4char(pSrc1);
    
    u32Dst = u32Src1 - u32Src2;
    
    cpu_write_int_to_4char(u32Dst, pDst);
}

void cpu_int_add(unsigned char *Src1, unsigned char *Src2, unsigned int InputC, 
                 unsigned char *N, unsigned char *Z, unsigned char *C, unsigned char *V, unsigned char *Dst)
{
    unsigned int u32Src1, u32Src2, u32Dst;
    
    u32Src1 = cpu_get_int_from_4char(Src1);
    u32Src2 = cpu_get_int_from_4char(Src2);
    
    cpu_int_add_core(u32Src1, u32Src2, InputC, N, Z, C, V, &u32Dst);

    cpu_write_int_to_4char(u32Dst, Dst);
    
}

void cpu_int_sub(unsigned char *Src1, unsigned char *Src2, unsigned int InputC, 
                 unsigned char *N, unsigned char *Z, unsigned char *C, unsigned char *V, unsigned char *Dst)
{
    unsigned int u32Src1, u32Src2, u32Dst;

    u32Src1 = cpu_get_int_from_4char(Src1);
    u32Src2 = cpu_get_int_from_4char(Src2);
    u32Src2 = (unsigned int)(0 - (int)u32Src2 - 1);

    cpu_int_add_core(u32Src1, u32Src2, InputC, N, Z, C, V, &u32Dst);

    cpu_write_int_to_4char(u32Dst, Dst);
}

void cpu_int_mpy(unsigned char *Src1, unsigned char *Src2, 
                 unsigned char *N, unsigned char *Z, unsigned char *Dst)
{
    unsigned int u32Src1, u32Src2, u32Dst;
    
    u32Src1 = cpu_get_int_from_4char(Src1);
    u32Src2 = cpu_get_int_from_4char(Src2);
    
    u32Dst = u32Src1 *  u32Src2;

    //update SR flag bit
    *Z = (u32Dst == 0);
    *N = (u32Dst >> 31) & 1;
    
    cpu_write_int_to_4char(u32Dst, Dst);
    
}

unsigned int Format1_ADD_EX_stage	(void)
{
    CPU *pCpu= get_cpu();
    unsigned char InputC, N, Z, C, V;

    if (pCpu->InstFlag.reg.A) //ADDC
    {
        InputC = GET_SR_FLAG_C(pCpu->CpuCore.SRCh);
    }
    else
    {
        InputC = 0;
    }

    cpu_int_add(pCpu->Src1, pCpu->Src2, InputC, &N, &Z, &C, &V, pCpu->dst);
                 
    //update SR falg bit
    SET_SR_FLAG_Z(pCpu->CpuCore.SRCh, Z);
    SET_SR_FLAG_N(pCpu->CpuCore.SRCh, N);
    SET_SR_FLAG_C(pCpu->CpuCore.SRCh, C);
    SET_SR_FLAG_V(pCpu->CpuCore.SRCh, V);

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}

unsigned int Format1_ADD_MEM_stage	(void){ return 0;}
unsigned int Format1_ADD_WB_stage	(void){ return 0;}

unsigned int Format1_SUB_EX_stage	(void)
{
    CPU *pCpu= get_cpu();
    unsigned char InputC, N, Z, C, V;

    if (pCpu->InstFlag.reg.A) //ADDC
    {
        InputC = GET_SR_FLAG_C(pCpu->CpuCore.SRCh);
    }
    else
    {
        InputC = 1;
    }

    cpu_int_sub(pCpu->Src1, pCpu->Src2, InputC, &N, &Z, &C, &V, pCpu->dst);
                 
    //update SR falg bit
    SET_SR_FLAG_Z(pCpu->CpuCore.SRCh, Z);
    SET_SR_FLAG_N(pCpu->CpuCore.SRCh, N);
    SET_SR_FLAG_C(pCpu->CpuCore.SRCh, C);
    SET_SR_FLAG_V(pCpu->CpuCore.SRCh, V);

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format1_SUB_MEM_stage	(void){ return 0;}
unsigned int Format1_SUB_WB_stage	(void){ return 0;}

unsigned int Format1_MPY_EX_stage	(void)
{
    CPU *pCpu= get_cpu();
    unsigned char N, Z;
    cpu_int_mpy(pCpu->Src1, pCpu->Src2, &N, &Z, pCpu->dst);

    //update SR flag bit
    SET_SR_FLAG_Z(pCpu->CpuCore.SRCh, Z);
    SET_SR_FLAG_N(pCpu->CpuCore.SRCh, N);

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format1_MPY_MEM_stage	(void){ return 0;}
unsigned int Format1_MPY_WB_stage	(void){ return 0;}


unsigned int Format1_MOV_EX_stage	(void)
{
    CPU *pCpu= get_cpu();

    cpu_move_from_4byte_to_4byte(pCpu->Src1, pCpu->dst);

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format1_MOV_MEM_stage	(void){ return 0;}
unsigned int Format1_MOV_WB_stage	(void){ return 0;}

unsigned int Format1_CMP_EX_stage	(void)
{
    CPU *pCpu= get_cpu();
    unsigned char InputC, N, Z, C, V;
    unsigned char NotUsedDst[4];

    InputC = 1;

    cpu_int_sub(pCpu->Src1, pCpu->Src2, InputC, &N, &Z, &C, &V, NotUsedDst);
                 
    //update SR falg bit
    SET_SR_FLAG_Z(pCpu->CpuCore.SRCh, Z);
    SET_SR_FLAG_N(pCpu->CpuCore.SRCh, N);
    SET_SR_FLAG_C(pCpu->CpuCore.SRCh, C);
    SET_SR_FLAG_V(pCpu->CpuCore.SRCh, V);

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format1_CMP_MEM_stage	(void){ return 0;}
unsigned int Format1_CMP_WB_stage	(void){ return 0;}

static void cpu_int_shift_core(unsigned int u32Src1, unsigned int u32Src2, unsigned char A, unsigned char *Z, unsigned char *C, unsigned int *pu32Dst)
{
    unsigned long long int s1,d;
    unsigned int dLow32,dHigh32;
    int i32Shift;
    
    i32Shift = (int)u32Src2;

    if (i32Shift >=0) //left shift is the same for logical and arithmetical shift
    {
        s1 = (unsigned long long int)u32Src1;
        d = s1 << i32Shift;
        dLow32 = (unsigned int)d;
        dHigh32 = (unsigned int)(d>>32);
        *pu32Dst = dLow32;
        //set flag
        *C = (dHigh32 != 0);
        *Z = (0 == dLow32);
    }
    else  //for right shift
    {
        if (A) //arithmetical shift
        {
           *pu32Dst = (unsigned int)((int)u32Src1 >> (-i32Shift));
        }
        else  // logic shift
        {
            *pu32Dst = (unsigned int)u32Src1 >> (-i32Shift);
        }
        *Z = (0 == *pu32Dst);
        *C = 0;
    }
}
unsigned int Format1_SHIFT_EX_stage	(void)
{
    unsigned int u32Src1, u32Src2, u32Dst;
    unsigned char C, Z;
    CPU *pCpu= get_cpu();

    u32Src1 = cpu_get_int_from_4char(pCpu->Src1);
    u32Src2 = cpu_get_int_from_4char(pCpu->Src2);
    
    cpu_int_shift_core(u32Src1, u32Src2, pCpu->InstFlag.reg.A, &Z, &C, &u32Dst);

    cpu_write_int_to_4char(u32Dst, pCpu->dst);

    SET_SR_FLAG_C(pCpu->CpuCore.SRCh, C);
    SET_SR_FLAG_Z(pCpu->CpuCore.SRCh, Z);

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
    unsigned int u32Src1, u32Src2;

    u32Src1 = cpu_get_int_from_4char(pCpu->Src1);
    u32Src2 = cpu_get_int_from_4char(pCpu->Src2);

    if (pCpu->InstFlag.reg.B)
    {
        Rb = ~u32Src1;
    }
    else
    {
        Rb = u32Src1;
    }

    if (pCpu->InstFlag.reg.C)
    {
        Ra = ~u32Src2;
    }
    else
    {
        Ra = u32Src2;
    }

    Rd = Ra & Rb;

    if (pCpu->InstFlag.reg.A)
    {
        cpu_write_int_to_4char(~Rd, pCpu->dst);
    }
    else
    {
        cpu_write_int_to_4char(Rd, pCpu->dst);
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
    unsigned int u32Src1, u32Src2;

    u32Src1 = cpu_get_int_from_4char(pCpu->Src1);
    u32Src2 = cpu_get_int_from_4char(pCpu->Src2);

    if (pCpu->InstFlag.reg.B)
    {
        Rb = ~u32Src1;
    }
    else
    {
        Rb = u32Src1;
    }

    if (pCpu->InstFlag.reg.C)
    {
        Ra = ~u32Src2;
    }
    else
    {
        Ra = u32Src2;
    }

    Rd = Ra ^ Rb;

    if (pCpu->InstFlag.reg.A)
    {
        cpu_write_int_to_4char(~Rd, pCpu->dst);
    }
    else
    {
        cpu_write_int_to_4char(Rd, pCpu->dst);
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
    unsigned int u32Src1, u32Dst;

    u32Src1 = cpu_get_int_from_4char(pCpu->Src1);
    u32Dst = ~u32Src1;

    cpu_write_int_to_4char(u32Dst, pCpu->dst);

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
    unsigned int u32Src1;

    u32Src1 = (unsigned int)((int)cpu_get_int_from_4char(pCpu->Src1) + (int)cpu_get_int_from_4char(pCpu->Src2)); //src1 save mem address
    cpu_write_int_to_4char(u32Src1, pCpu->Src1);

    //update stage
    pCpu->stage = CPU_STAGE_MEM;
    return 0;
}
/*read from data mem*/
unsigned int Format1_LD_MEM_stage	(void)
{
    CPU *pCpu= get_cpu();
    unsigned int u32Src1;
    unsigned char *pMem;
    u32Src1 = cpu_get_int_from_4char(pCpu->Src1);
    
    pMem = &pCpu->DataMemBase[(u32Src1 >> 2) << 2];
    cpu_move_from_4byte_to_4byte(pMem, pCpu->Src2);
    //update stage
    pCpu->stage = CPU_STAGE_WB;
    return 0;
}
/*write back to register,check read byte/2 byte/4 bytes and signed flag
  the CPU is designed for big endian mode, shall check compiler endian mode and do different work*/
unsigned int Format1_LD_WB_stage	(void)
{
    CPU *pCpu= get_cpu();
    unsigned int u32Src1 = cpu_get_int_from_4char(pCpu->Src1);
    unsigned char RdSize = pCpu->InstFlag.reg.A*2 + pCpu->InstFlag.reg.B;
    unsigned char Update = pCpu->InstFlag.reg.C * 4 + pCpu->InstFlag.reg.D * 2 + pCpu->InstFlag.reg.E;
    unsigned char c0,c1,c2,c3;
    unsigned int u32Value;
    int i32Value;

    switch (RdSize)
    {
    case 0: //read one byte
        c0 = pCpu->Src2[u32Src1 & 0x3]; // pCpu->Src1 & 0x3 return byte location in 4 bytes
        if (pCpu->InstFlag.reg.C) //if signed extension
        {
            i32Value = (int)c0;
            i32Value = (i32Value << 24) >> 24;
            cpu_write_int_to_4char((unsigned int)i32Value, pCpu->dst);
        }
        else
        {
            cpu_write_int_to_4char((unsigned int)c0, pCpu->dst);
        }
        break;
    case 1: //read 2 bytes
        c0 = pCpu->Src2[((u32Src1 >> 1) & 1) << 1]; 
        c1 = pCpu->Src2[(((u32Src1 >> 1) & 1) << 1)+1];
        u32Value = ((unsigned int)c0 << 8) + (unsigned int)c1;
        if (pCpu->InstFlag.reg.C) //if signed extension
        {
            i32Value = (int)u32Value;
            i32Value = (i32Value << 16) >> 16;
            cpu_write_int_to_4char((unsigned int)i32Value, pCpu->dst);
        }
        else
        {
            cpu_write_int_to_4char((unsigned int)u32Value, pCpu->dst);
        }
        break;
    case 2:  //four byte
        c0 = pCpu->Src2[0];
        c1 = pCpu->Src2[1];
        c2 = pCpu->Src2[2];
        c3 = pCpu->Src2[3];
        u32Value = ((unsigned int)c0 << 24) + ((unsigned int)c1 << 16) +((unsigned int)c2 << 8) +(unsigned int)c3;
        cpu_write_int_to_4char((unsigned int)u32Value, pCpu->dst);
        if (pCpu->Src1Reg)
        {
            switch (Update)
            {
            case 0: cpu_add_int_to_4byte(pCpu->Src1Reg, 0, pCpu->Src1Reg); break;
            case 1: cpu_add_int_to_4byte(pCpu->Src1Reg, 1, pCpu->Src1Reg); break;
            case 2: cpu_add_int_to_4byte(pCpu->Src1Reg, 2, pCpu->Src1Reg); break;
            case 3: cpu_add_int_to_4byte(pCpu->Src1Reg, 4, pCpu->Src1Reg); break;
            case 4: cpu_sub_int_from_4byte(pCpu->Src1Reg, 0, pCpu->Src1Reg); break;
            case 5: cpu_sub_int_from_4byte(pCpu->Src1Reg, 1, pCpu->Src1Reg); break;
            case 6: cpu_sub_int_from_4byte(pCpu->Src1Reg, 2, pCpu->Src1Reg); break;
            case 7: cpu_sub_int_from_4byte(pCpu->Src1Reg, 4, pCpu->Src1Reg); break;
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
    unsigned int u32Value = cpu_get_int_from_4char(pCpu->dst);
    unsigned int u32Addr = cpu_get_int_from_4char(pCpu->Src1);
    unsigned char c0,c1,c2,c3;
    unsigned char RdSize = pCpu->InstFlag.reg.A*2 + pCpu->InstFlag.reg.B;
    unsigned char Update = pCpu->InstFlag.reg.C * 4 + pCpu->InstFlag.reg.D * 2 + pCpu->InstFlag.reg.E;

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
            case 0: cpu_add_int_to_4byte(pCpu->Src1Reg, 0, pCpu->Src1Reg); break;
            case 1: cpu_add_int_to_4byte(pCpu->Src1Reg, 1, pCpu->Src1Reg); break;
            case 2: cpu_add_int_to_4byte(pCpu->Src1Reg, 2, pCpu->Src1Reg); break;
            case 3: cpu_add_int_to_4byte(pCpu->Src1Reg, 4, pCpu->Src1Reg); break;
            case 4: cpu_sub_int_from_4byte(pCpu->Src1Reg, 0, pCpu->Src1Reg); break;
            case 5: cpu_sub_int_from_4byte(pCpu->Src1Reg, 1, pCpu->Src1Reg); break;
            case 6: cpu_sub_int_from_4byte(pCpu->Src1Reg, 2, pCpu->Src1Reg); break;
            case 7: cpu_sub_int_from_4byte(pCpu->Src1Reg, 4, pCpu->Src1Reg); break;
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
    i32Value = (int)cpu_get_int_from_4char(pCpu->Src2);
    if (pCpu->InstFlag.reg.B) //if signed data
    {
        i32Value = (i32Value << 21) >> 21; //signed extended from 10bits to 32 bits
    }
    cpu_write_int_to_4char((unsigned int)i32Value, pCpu->Src2);

    return Format1_ADD_EX_stage();
}
unsigned int Format2_ADD_MEM_stage	        (void){ return 0;}
unsigned int Format2_ADD_WB_stage           (void){ return 0;}

unsigned int Format2_SUB_EX_stage	        (void)
{
    unsigned int d1,d2;
    int i32Value;
    CPU *pCpu= get_cpu();
    d1 = cpu_get_int_from_4char(pCpu->Src1);

    i32Value = (int)cpu_get_int_from_4char(pCpu->Src2);
    if (pCpu->InstFlag.reg.B) //if signed data
    {
        i32Value = (i32Value << 21) >> 21; //signed extended from 10bits to 32 bits
    }
    d2 =   (unsigned int)i32Value;

    if (pCpu->InstFlag.reg.C) //reserve, Imme - Rb
    {
        cpu_write_int_to_4char(d2, pCpu->Src1);
        cpu_write_int_to_4char(d1, pCpu->Src2);
    }
    else
    {
        cpu_write_int_to_4char(d1, pCpu->Src1);
        cpu_write_int_to_4char(d2, pCpu->Src2);
    }
    return Format1_SUB_EX_stage();
}
unsigned int Format2_SUB_MEM_stage	        (void){ return 0;}
unsigned int Format2_SUB_WB_stage           (void){ return 0;}


unsigned int Format2_MPY_EX_stage	        (void)
{
    int i32Value;
    CPU *pCpu= get_cpu();
    i32Value = (int)cpu_get_int_from_4char(pCpu->Src2);
    if (pCpu->InstFlag.reg.A) //if signed data
    {
        i32Value = (i32Value << 21) >> 21; //signed extended from 10bits to 32 bits
    }
    cpu_write_int_to_4char((unsigned int)i32Value, pCpu->Src2);
    return Format1_MPY_EX_stage();
}
unsigned int Format2_MPY_MEM_stage	        (void){ return 0;}
unsigned int Format2_MPY_WB_stage           (void){ return 0;}

unsigned int Format2_SHIFT_EX_stage	        (void)
{
    unsigned int u32Src1, u32Src2, u32Dst;
    unsigned char C, Z;
    CPU *pCpu= get_cpu();
    int i32Value;

    u32Src1 = cpu_get_int_from_4char(pCpu->Src1);
    u32Src2 = cpu_get_int_from_4char(pCpu->Src2);

    i32Value = u32Src2;
    i32Value = (i32Value << 21) >> 21; //signed extended from 10bits to 32 bits
    u32Src2 = (unsigned int)i32Value;

    cpu_int_shift_core(u32Src1, u32Src2, pCpu->InstFlag.reg.A, &Z, &C, &u32Dst);

    cpu_write_int_to_4char(u32Dst, pCpu->dst);

    SET_SR_FLAG_C(pCpu->CpuCore.SRCh, C);
    SET_SR_FLAG_Z(pCpu->CpuCore.SRCh, Z);

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format2_SHIFT_MEM_stage	    (void){ return 0;}
unsigned int Format2_SHIFT_WB_stage         (void){ return 0;}

unsigned int Format2_LD_EX_stage	        (void)
{
    CPU *pCpu= get_cpu();
    unsigned int u32Src1;
    int i32Value = (int)cpu_get_int_from_4char(pCpu->Src2);

    i32Value = (i32Value << 21) >> 21; //signed extended from 10bits to 32 bits
    u32Src1 = (unsigned int)((int)cpu_get_int_from_4char(pCpu->Src1) + i32Value); //src1 save mem address
    cpu_write_int_to_4char(u32Src1, pCpu->Src1);

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

unsigned int Format2_SWI_EX_stage	        (void)
{ 
    CPU *pCpu= get_cpu();
    unsigned int u32Src1;
    if (pCpu->InstFlag.reg.A) //ADDC
    {
        u32Src1 = cpu_get_int_from_4char(pCpu->Src2);
    }
    else
    {
        u32Src1 = cpu_get_int_from_4char(pCpu->Src1);
    }

    pCpu->CpuCore.INT_input[INTERNAL_INT_NUM + EXTERNAL_INT_NUM + (u32Src1 & (SWI_NUM - 1))] = 1;

    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
unsigned int Format2_SWI_MEM_stage	        (void){ return 0;}
unsigned int Format2_SWI_WB_stage           (void){ return 0;}

static void Format2_MOV_INNER_EX_stage_read_from(CPU *pCpu)
{
    unsigned int Type, i;
    unsigned int B,Cx,D,E;
    unsigned char *pDstInCh = (unsigned char *)pCpu->dst;
    unsigned int Ctrl; 
    B = pCpu->InstFlag.reg.B;
    Cx = pCpu->InstFlag.reg.C;
    D = pCpu->InstFlag.reg.D;
    E = pCpu->InstFlag.reg.E;
    Type = B*8+Cx*4+D*2+E;

    if (cpu_get_int_from_4char(pCpu->Src2) == 0x7FF)
    {
        Ctrl = cpu_get_int_from_4char(pCpu->Src1);
    }
    else
    {
        Ctrl = cpu_get_int_from_4char(pCpu->Src2);
    }

    switch (Type) 
    {
    case INTERNAL_REG_SR:
        cpu_move_from_4byte_to_4byte(pCpu->CpuCore.SRCh, pDstInCh);
        break;
    case INTERNAL_REG_INT_INPUT:
        for (i = 0; i< 4;i++)
        {
            pDstInCh[i] = ((pCpu->CpuCore.INT_input[i * 8 + 0] & 1) << 7)
                        | ((pCpu->CpuCore.INT_input[i * 8 + 1] & 1) << 6)
                        | ((pCpu->CpuCore.INT_input[i * 8 + 2] & 1) << 5)
                        | ((pCpu->CpuCore.INT_input[i * 8 + 3] & 1) << 4)
                        | ((pCpu->CpuCore.INT_input[i * 8 + 4] & 1) << 3)
                        | ((pCpu->CpuCore.INT_input[i * 8 + 5] & 1) << 2)
                        | ((pCpu->CpuCore.INT_input[i * 8 + 6] & 1) << 1)
                        | ((pCpu->CpuCore.INT_input[i * 8 + 7] & 1) << 0);
        }
        break;
    case INTERNAL_REG_INT_STATUS:
        for (i = 0; i< 4;i++)
        {
            pDstInCh[i] = ((pCpu->CpuCore.INT_STATUS[i * 8 + 0] & 1) << 7)
                        | ((pCpu->CpuCore.INT_STATUS[i * 8 + 1] & 1) << 6)
                        | ((pCpu->CpuCore.INT_STATUS[i * 8 + 2] & 1) << 5)
                        | ((pCpu->CpuCore.INT_STATUS[i * 8 + 3] & 1) << 4)
                        | ((pCpu->CpuCore.INT_STATUS[i * 8 + 4] & 1) << 3)
                        | ((pCpu->CpuCore.INT_STATUS[i * 8 + 5] & 1) << 2)
                        | ((pCpu->CpuCore.INT_STATUS[i * 8 + 6] & 1) << 1)
                        | ((pCpu->CpuCore.INT_STATUS[i * 8 + 7] & 1) << 0);
        }
        break;
    case INTERNAL_REG_INT_MASK:
        for (i = 0; i< 4;i++)
        {
            pDstInCh[i] = ((pCpu->CpuCore.INT_MASK[i * 8 + 0] & 1) << 7)
                        | ((pCpu->CpuCore.INT_MASK[i * 8 + 1] & 1) << 6)
                        | ((pCpu->CpuCore.INT_MASK[i * 8 + 2] & 1) << 5)
                        | ((pCpu->CpuCore.INT_MASK[i * 8 + 3] & 1) << 4)
                        | ((pCpu->CpuCore.INT_MASK[i * 8 + 4] & 1) << 3)
                        | ((pCpu->CpuCore.INT_MASK[i * 8 + 5] & 1) << 2)
                        | ((pCpu->CpuCore.INT_MASK[i * 8 + 6] & 1) << 1)
                        | ((pCpu->CpuCore.INT_MASK[i * 8 + 7] & 1) << 0);
        }
        break;
    case INTERNAL_REG_INT_PRIORITY:
        for (i = 0; i< 4;i++)
        {
            pDstInCh[i] = pCpu->CpuCore.INT_priority[(Ctrl & 7) * 4 + i];
        }
        break;
    case INTERNAL_REG_INT_RETURN_PC:
        cpu_move_from_4byte_to_4byte(pCpu->CpuCore.INT_ReturnPC[Ctrl], pDstInCh);
        break;
    case INTERNAL_REG_ACTIVE_INT_ID:
        cpu_write_int_to_4char((unsigned int)pCpu->CpuCore.ActiveIntId[Ctrl], pDstInCh);
        break;
    case INTERNAL_REG_ACTIVE_INT_POS:
        cpu_write_int_to_4char((unsigned int)pCpu->CpuCore.ActiveIntPos, pDstInCh);
        break;
    case INTERNAL_REG_RETI: 
        cpu_move_from_4byte_to_4byte(pCpu->CpuCore.INT_ReturnPC[Ctrl], pDstInCh);
        pCpu->CpuCore.ActiveIntPos--;
        break;
         
    }
}

static void Format2_MOV_INNER_EX_stage_write_to(CPU *pCpu)
{
    unsigned int Type, i;
    unsigned int B,Cx,D,E;
    unsigned char *pDstInCh = (unsigned char *)pCpu->dst;
    unsigned int Ctrl;
    B = pCpu->InstFlag.reg.B;
    Cx = pCpu->InstFlag.reg.C;
    D = pCpu->InstFlag.reg.D;
    E = pCpu->InstFlag.reg.E;
    Type = B*8+Cx*4+D*2+E;

    if (cpu_get_int_from_4char(pCpu->Src2) == 0x7FF)
    {
        Ctrl = cpu_get_int_from_4char(pCpu->Src1);
    }
    else
    {
        Ctrl = cpu_get_int_from_4char(pCpu->Src2);
    }

    switch (Type)
    {
    case INTERNAL_REG_SR:
        cpu_move_from_4byte_to_4byte(pDstInCh, pCpu->CpuCore.SRCh);
        break;
    case INTERNAL_REG_INT_STATUS:
        for (i = 0; i< 4;i++)
        {
            pCpu->CpuCore.INT_STATUS[i * 8 + 0] = (pDstInCh[i] >> 7) & 1;
            pCpu->CpuCore.INT_STATUS[i * 8 + 1] = (pDstInCh[i] >> 6) & 1;
            pCpu->CpuCore.INT_STATUS[i * 8 + 2] = (pDstInCh[i] >> 5) & 1;
            pCpu->CpuCore.INT_STATUS[i * 8 + 3] = (pDstInCh[i] >> 4) & 1;
            pCpu->CpuCore.INT_STATUS[i * 8 + 4] = (pDstInCh[i] >> 3) & 1;
            pCpu->CpuCore.INT_STATUS[i * 8 + 5] = (pDstInCh[i] >> 2) & 1;
            pCpu->CpuCore.INT_STATUS[i * 8 + 6] = (pDstInCh[i] >> 1) & 1;
            pCpu->CpuCore.INT_STATUS[i * 8 + 7] = (pDstInCh[i] >> 0) & 1;
        }
        break;
    case INTERNAL_REG_INT_MASK:
        for (i = 0; i< 4;i++)
        {
            pCpu->CpuCore.INT_MASK[i * 8 + 0] = (pDstInCh[i] >> 7) & 1;
            pCpu->CpuCore.INT_MASK[i * 8 + 1] = (pDstInCh[i] >> 6) & 1;
            pCpu->CpuCore.INT_MASK[i * 8 + 2] = (pDstInCh[i] >> 5) & 1;
            pCpu->CpuCore.INT_MASK[i * 8 + 3] = (pDstInCh[i] >> 4) & 1;
            pCpu->CpuCore.INT_MASK[i * 8 + 4] = (pDstInCh[i] >> 3) & 1;
            pCpu->CpuCore.INT_MASK[i * 8 + 5] = (pDstInCh[i] >> 2) & 1;
            pCpu->CpuCore.INT_MASK[i * 8 + 6] = (pDstInCh[i] >> 1) & 1;
            pCpu->CpuCore.INT_MASK[i * 8 + 7] = (pDstInCh[i] >> 0) & 1;
        }
        break;
    case INTERNAL_REG_INT_PRIORITY:
        for (i = 0; i< 4;i++)
        {
            pCpu->CpuCore.INT_priority[(Ctrl & 7) * 4 + i] = pDstInCh[i];
        }
        break;
    case  INTERNAL_REG_INT_RETURN_PC:
        cpu_move_from_4byte_to_4byte(pDstInCh, pCpu->CpuCore.INT_ReturnPC[Ctrl]);
        break;
    case INTERNAL_REG_ACTIVE_INT_ID:
        pCpu->CpuCore.ActiveIntId[Ctrl] = (unsigned char)cpu_get_int_from_4char(pDstInCh);
    case INTERNAL_REG_RETI: 
        break;
    }
}
unsigned int Format2_MOV_INNER_EX_stage	    (void)
{ 
    CPU *pCpu= get_cpu();

    if (pCpu->InstFlag.reg.A)  //read from CPU internal registers
    {
        Format2_MOV_INNER_EX_stage_read_from(pCpu);
    }
    else
    {
        Format2_MOV_INNER_EX_stage_write_to(pCpu);
    }
    //update stage
    pCpu->stage = CPU_STAGE_IF;
    return 0;
}
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
    unsigned int u32Src1 = cpu_get_int_from_4char(pCpu->Src1);

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
            cpu_move_from_4byte_to_4byte(pCpu->CpuCore.R[31], pCpu->CpuCore.R[30]);
        }
        cpu_write_int_to_4char((u32Src1 << 2), pCpu->CpuCore.R[31]); //address is in 4 bytes,shall left by 4
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
    int i32Value = (int)cpu_get_int_from_4char(pCpu->Src1);
    int i32Pc = (int)cpu_get_int_from_4char(pCpu->CpuCore.R[31]);
    i32Value = (i32Value << 8) >> 8;
    //RJMP shall jump to current location + i32Value, while R[31] point to next instruction location, 
    // so "- 1" is needed
    cpu_write_int_to_4char(i32Value + (i32Pc >> 2) - 1, pCpu->Src1);
    return Format3_AJMP_EX_stage();
}
unsigned int Format3_RJMP_MEM_stage	        (void){ return 0;}
unsigned int Format3_RJMP_WB_stage          (void){ return 0;}


unsigned int Format4_AJMP_EX_stage	        (void)
{
    CPU *pCpu= get_cpu();
    int i32Value = (int)cpu_get_int_from_4char(pCpu->Src1);
    int i32Dst = (int)cpu_get_int_from_4char(pCpu->dst);
    i32Value = (i32Value << 16) >> 14;
     
    cpu_write_int_to_4char((i32Value + i32Dst) >> 2, pCpu->Src1);

    return Format3_AJMP_EX_stage();
}
unsigned int Format4_AJMP_MEM_stage	        (void){ return 0;}
unsigned int Format4_AJMP_WB_stage          (void){ return 0;}

unsigned int Format4_RJMP_EX_stage	        (void)
{
    CPU *pCpu= get_cpu();
    int i32Value = (int)cpu_get_int_from_4char(pCpu->Src1);
    int i32Pc = (int)cpu_get_int_from_4char(pCpu->CpuCore.R[31]);
    int i32Dst = (int)cpu_get_int_from_4char(pCpu->dst);

    i32Value = (i32Value << 16) >> 14;
    //RJMP shall jump to current location + i32Value, while R[31] point to next instruction location, 
    // so "- 1" is needed
     
    cpu_write_int_to_4char((unsigned int)((i32Value + i32Dst + i32Pc - 1) >> 2), pCpu->Src1);
    return Format3_AJMP_EX_stage();
}
unsigned int Format4_RJMP_MEM_stage	        (void){ return 0;}
unsigned int Format4_RJMP_WB_stage          (void){ return 0;}


unsigned int Format4_MOV_EX_stage	        (void)
{
    CPU *pCpu= get_cpu();
    int i32Value = (int)cpu_get_int_from_4char(pCpu->Src1);
    if (pCpu->InstFlag.reg.A) //signed
    {
        i32Value = (i32Value << 16) >> 16;
        cpu_write_int_to_4char((unsigned int)i32Value, pCpu->Src1);
    }
    return Format1_MOV_EX_stage();
}
unsigned int Format4_MOV_MEM_stage	        (void){ return 0;}
unsigned int Format4_MOV_WB_stage           (void){ return 0;}

unsigned int Format4_CMP_EX_stage	        (void)
{
    CPU *pCpu= get_cpu();
    int i32Value = (int)cpu_get_int_from_4char(pCpu->Src1);
    if (pCpu->InstFlag.reg.A) //signed
    {
        i32Value = (i32Value << 16) >> 16;
        cpu_write_int_to_4char((unsigned int)i32Value, pCpu->Src1);
    }
    cpu_move_from_4byte_to_4byte(pCpu->Src1, pCpu->Src2);
    cpu_move_from_4byte_to_4byte(pCpu->dst, pCpu->Src1);
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
    pCpu->dst =    pCpu->CpuCore.R[DstReg];

    SrcReg  =   GET_INST_TYPE1_RB(pCpu->InstCh);
    cpu_move_from_4byte_to_4byte(pCpu->CpuCore.R[SrcReg], pCpu->Src1);
    
    pCpu->Src1Reg = pCpu->CpuCore.R[SrcReg];

    SrcReg  =   GET_INST_TYPE1_RA(pCpu->InstCh);
    cpu_move_from_4byte_to_4byte(pCpu->CpuCore.R[SrcReg], pCpu->Src2);
    
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

    DstReg = GET_INST_TYPE2_RD(pCpu->InstCh);
    pCpu->dst = pCpu->CpuCore.R[DstReg];

    SrcReg = GET_INST_TYPE2_RB(pCpu->InstCh);
    cpu_move_from_4byte_to_4byte(pCpu->CpuCore.R[SrcReg], pCpu->Src1);
    pCpu->Src1Reg = 0;
    cpu_write_int_to_4char((unsigned int)GET_INST_TYPE2_IMM(pCpu->InstCh), pCpu->Src2);
    
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

    cpu_write_int_to_4char((unsigned int)GET_INST_TYPE3_IMM(pCpu->InstCh), pCpu->Src1);
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
    pCpu->dst =    pCpu->CpuCore.R[DstReg];

    cpu_write_int_to_4char((unsigned int)GET_INST_TYPE4_IMM(pCpu->InstCh), pCpu->Src1);
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


