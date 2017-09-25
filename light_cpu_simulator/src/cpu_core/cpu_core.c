/*
 * cpu_core.c
 *
 *  Created on: Sep 9, 2017
 *      Author: jie
 */

#include "cpu_core.h"
#include "cpu_instruction.h"

CPU Cpu;

/* store all instruction function*/
S_INSTRCTION_CONTEXT gFormat1InstCtxMenu[16];
S_INSTRCTION_CONTEXT gFormat2InstCtxMenu[16];
S_INSTRCTION_CONTEXT gFormat3InstCtxMenu[2] ;
S_INSTRCTION_CONTEXT gFormat4InstCtxMenu[16];

/*function protocol of CPU*/
void reset_cpu(unsigned char *InstMemBase, unsigned int InstMemSize,
		  	   unsigned char *DataMemBase, unsigned int DataMemSize,
		  	   unsigned char *StackMemBase, unsigned int StackMemSize)
{
	int i;

    InitInstTable(gFormat1InstCtxMenu,gFormat2InstCtxMenu,gFormat3InstCtxMenu,gFormat4InstCtxMenu);

	/*reset CPU need reset all register to default value*/
    for (i=0;i<CPU_MAX_REG_NUM;i++)
    {
        Cpu.CpuCore.R[i][0] = 0;
        Cpu.CpuCore.R[i][1] = 0;
        Cpu.CpuCore.R[i][2] = 0;
        Cpu.CpuCore.R[i][3] = 0;
    }

    cpu_write_int_to_4char(0, Cpu.CpuCore.R[31]); //PC = 0
    cpu_write_int_to_4char(0, Cpu.CpuCore.R[30]);  //link reg = 0;
    cpu_write_int_to_4char(StackMemSize/4, Cpu.CpuCore.R[29]);
    
    Cpu.CpuCore.SRCh[0] =   0;
    Cpu.CpuCore.SRCh[1] =   0;
    Cpu.CpuCore.SRCh[2] =   0;
    Cpu.CpuCore.SRCh[3] =   0;
    SET_SR_FLAG_INT(Cpu.CpuCore.SRCh, 0);

    for (i = 0; i < CPU_MAX_INT_NUM; i++)
    {
        Cpu.CpuCore.INT_input[i] = 0;
        Cpu.CpuCore.INT_STATUS[i] = 0;
        Cpu.CpuCore.INT_MASK[i] = 0;
        Cpu.CpuCore.INT_priority[i] = CPU_MAX_INT_NUM - i; //
        Cpu.CpuCore.INT_ReturnPC[i][0] = 0;
        Cpu.CpuCore.INT_ReturnPC[i][1] = 0;
        Cpu.CpuCore.INT_ReturnPC[i][2] = 0;
        Cpu.CpuCore.INT_ReturnPC[i][3] = 0;
        Cpu.CpuCore.ActiveIntId[i] = CPU_MAX_INT_NUM;
    }
    Cpu.CpuCore.ActiveIntPos = 0;
    
	Cpu.DataMemBase = DataMemBase;
	Cpu.DataMemSizeInBtye = DataMemSize;
	Cpu.InstMemBase = InstMemBase;
	Cpu.InstMemSizeInByte = InstMemSize;
	Cpu.StackMemBase = StackMemBase;
	Cpu.StackMemSizeInBtye = StackMemSize;

	Cpu.stage = CPU_STAGE_IF;

    Cpu.stage_if_cb = run_cpu_in_if_stage;
	Cpu.stage_id_cb = run_cpu_in_id_stage;
	Cpu.stage_ex_cb = 0;
	Cpu.stage_mem_cb = 0;
	Cpu.stage_wb_cb = 0;
}
unsigned int run_cpu(void)
{
	unsigned int result = 0; //no error
	switch(Cpu.stage)
	{
	case CPU_STAGE_IF:
		result = Cpu.stage_if_cb();
		break;
	case CPU_STAGE_ID:
		result = Cpu.stage_id_cb();
		break;
	case CPU_STAGE_EX:
		result = Cpu.stage_ex_cb();
		break;
	case CPU_STAGE_MEM:
		result = Cpu.stage_mem_cb();
		break;
	case CPU_STAGE_WB:
		result = Cpu.stage_wb_cb();
		break;
	default:
		result = 1;
	}
	return result;
}

unsigned int run_cpu_in_if_stage()
{
	unsigned int AddrInByte = cpu_get_int_from_4char(Cpu.CpuCore.R[31]);
    unsigned int i;
    unsigned char HighestIntPriority = NO_INT_FLAG;
    unsigned char HighestIntId = 0;
    
	if (AddrInByte & 0x3)
	{	// PC address is not 4 bytes align
		return 1;
	}

    /* check interrupt*/
    for(i = 0; i< CPU_MAX_INT_NUM; i++)
    {
        if ((Cpu.CpuCore.INT_input[i] == 1) && (Cpu.CpuCore.INT_MASK[i] == 1))
        {
            Cpu.CpuCore.INT_STATUS[i] = 1;
            //clear int input
            Cpu.CpuCore.INT_input[i] = 0;
        }
        if ((Cpu.CpuCore.INT_STATUS[i] == 1) && (Cpu.CpuCore.INT_priority[i] > HighestIntPriority))
        {
            HighestIntPriority = Cpu.CpuCore.INT_priority[i];
            HighestIntId = i;
        }
    }

    if(GET_SR_FLAG_INT(Cpu.CpuCore.SRCh) && (HighestIntPriority > NO_INT_FLAG)) //if INT processing is enabled and there is int signal
    {
        //LowestIntPriority is lower than current active int, go to int processing
        if (HighestIntPriority > Cpu.CpuCore.INT_priority[Cpu.CpuCore.ActiveIntId[Cpu.CpuCore.ActiveIntPos]])
        {
            // set avtive int
            Cpu.CpuCore.ActiveIntPos++;
            Cpu.CpuCore.ActiveIntId[Cpu.CpuCore.ActiveIntPos] = HighestIntId;
            cpu_write_int_to_4char(AddrInByte, Cpu.CpuCore.INT_ReturnPC[HighestIntId]);
            
            //clear int status
            Cpu.CpuCore.INT_STATUS[HighestIntId] = 0;

            //set int entry PC 
            AddrInByte = CPU_ENTRY_RESERVE_SIZE + HighestIntId * INT_ENTRY_MEM_SIZE;
            cpu_write_int_to_4char(AddrInByte, Cpu.CpuCore.R[31]);
            
        }
    }

	if(AddrInByte < Cpu.InstMemSizeInByte)
	{
        cpu_move_from_4byte_to_4byte(&Cpu.InstMemBase[AddrInByte], Cpu.InstCh);
		
        cpu_add_int_to_4byte(Cpu.CpuCore.R[31], 4, Cpu.CpuCore.R[31]);

		Cpu.stage = CPU_STAGE_ID;
		return 0;
	}
	else
	{  //CPU PC address is out of instruction memory scope
		return 2; //return error
	}
}

unsigned int run_cpu_in_id_stage()
{
    unsigned int FormatType;
    unsigned int Opcode;
    unsigned int result;

    //parse instruction
    FormatType = GET_INST_FORMAT_TYPE(Cpu.InstCh);

    switch (FormatType)
    {
    case 0: //format 1
        Opcode = GET_INST_TYPE1_2_4_OPCODE(Cpu.InstCh);
        if(gFormat1InstCtxMenu[Opcode].func_ID_stage) //
        {
            Cpu.stage_ex_cb = gFormat1InstCtxMenu[Opcode].func_EX_stage;
            Cpu.stage_mem_cb = gFormat1InstCtxMenu[Opcode].func_MEM_stage;
            Cpu.stage_wb_cb = gFormat1InstCtxMenu[Opcode].func_WB_stage;
            result = gFormat1InstCtxMenu[Opcode].func_ID_stage();
        }
        else
        {
            //printf("wrong instrction! \n");
            return 2;
        }
        break;
    case 1: //format 2
        Opcode = GET_INST_TYPE1_2_4_OPCODE(Cpu.InstCh);
        if(gFormat2InstCtxMenu[Opcode].func_ID_stage) //
        {
            Cpu.stage_ex_cb = gFormat2InstCtxMenu[Opcode].func_EX_stage;
            Cpu.stage_mem_cb = gFormat2InstCtxMenu[Opcode].func_MEM_stage;
            Cpu.stage_wb_cb = gFormat2InstCtxMenu[Opcode].func_WB_stage;
            result = gFormat2InstCtxMenu[Opcode].func_ID_stage();
        }
        else
        {
           // printf("wrong instrction! \n");
            return 3;
        }
        break;
    case 2: //format 3
        Opcode = GET_INST_TYPE3_OPCODE(Cpu.InstCh);
        if(gFormat3InstCtxMenu[Opcode].func_ID_stage) //
        {
            Cpu.stage_ex_cb = gFormat3InstCtxMenu[Opcode].func_EX_stage;
            Cpu.stage_mem_cb = gFormat3InstCtxMenu[Opcode].func_MEM_stage;
            Cpu.stage_wb_cb = gFormat3InstCtxMenu[Opcode].func_WB_stage;
            result = gFormat3InstCtxMenu[Opcode].func_ID_stage();
        }
        else
        {
           // printf("wrong instrction! \n");
            return 2;
        }
        break;
    case 3: //format 4
        Opcode = GET_INST_TYPE1_2_4_OPCODE(Cpu.InstCh);
        if(gFormat4InstCtxMenu[Opcode].func_ID_stage) //
        {
            Cpu.stage_ex_cb = gFormat4InstCtxMenu[Opcode].func_EX_stage;
            Cpu.stage_mem_cb = gFormat4InstCtxMenu[Opcode].func_MEM_stage;
            Cpu.stage_wb_cb = gFormat4InstCtxMenu[Opcode].func_WB_stage;
            result = gFormat4InstCtxMenu[Opcode].func_ID_stage();
        }
        else
        {
          //  printf("wrong instrction! \n");
            return 2;
        }
        break;

    }
    if (result)
    {
        //printf("instruction decosing error. \ n");

    }
    return result;
}

CPU* get_cpu()
{
	return &Cpu;
}
