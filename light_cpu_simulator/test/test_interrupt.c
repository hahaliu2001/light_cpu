/*
 * test_interrupt.c
 *
 *  Created on: Sep 24, 2017
 *      Author: jie
 */

#include "cpu_external.h"
#include "mem.h"
#include "cpu_test_helper.h"
#include "unity.h"
#include "unity_fixture.h"

#undef  TESTNAME
#define TESTNAME interrupt_test

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

static int HighIntId, LowIntId; 
static int HighIntPriority, LowIntPriority; 
static int m = 0;
static int RB, RB2, RD; //, Type;
static int RA1, RA2, RA3;
static unsigned int SetIntMask1, SetIntMask2, SetIntGlobalFlag;
static unsigned int InstSize;

static void do_init()
{
    InstSize = INSTRUCTION_MEM_SIZE;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RD = 23; 
    RB = 12; 
    RB2 = 13;
    RA1 = 1; 
    RA2 = 2; 
    RA3 = 3;
    HighIntId = 18; 
    LowIntId = 19;
    HighIntPriority = 10;
    LowIntPriority = 5;

    SET_CPU_INT_INPUT(HighIntId, 1); 
    SET_CPU_INT_INPUT(LowIntId, 1); 
}
static void write_inst_mem()
{
    //set instruction
    m = 0;
    //first set RD = (RB << 16) | RD, then set RD to INT_MASK
    SET_TYPE4_UNSIGNED_MOV(InstMem[m], RB, SetIntMask1); m++;
    SET_TYPE2_LOGIC_SHIFT(InstMem[m], RB, RB, 16);  m++;
    SET_TYPE4_UNSIGNED_MOV(InstMem[m], RD, SetIntMask2); m++;
    SET_TYPE1_OR(InstMem[m], RD, RD, RB);           m++;
    SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_INT_MASK, RD, 0);    m++;

    //set RA
    SET_TYPE4_UNSIGNED_MOV(InstMem[m], RA1, 20); m++;

    //set int priority
    SET_TYPE4_UNSIGNED_MOV(InstMem[m], RD, ((HighIntPriority << 8) | LowIntPriority)); m++;
    SET_TYPE2_MOVE_INNER_WRITE_IMM(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, 4);    m++;

    //set global int flag in SR char
    SET_TYPE2_MOVE_INNER_READ(InstMem[m], INTERNAL_REG_SR, RD, 0);             m++;
    SET_TYPE4_UNSIGNED_MOV(InstMem[m], RB2, SetIntGlobalFlag);                              m++;
    SET_TYPE1_OR(InstMem[m], RD, RD, RB2);                                      m++;  //set char[3] bit 7 to be 1
    SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_SR, RD, 0);    m++;

    SET_TYPE4_UNSIGNED_MOV(InstMem[m], RA1, 30); m++;
    
    //error, normal code will exit here
    SET_ERROR_INST(InstMem[m]); m++;

    //move to HighInt processing
    m = (CPU_ENTRY_RESERVE_SIZE + HighIntId * INT_ENTRY_MEM_SIZE)/4;
    SET_TYPE4_UNSIGNED_MOV(InstMem[m], RA2, 40); m++;
    SET_TYPE2_MOVE_INNER_READ_IMM(InstMem[m], INTERNAL_REG_RETI, 31, HighIntId);    m++;  //int return
    SET_ERROR_INST(InstMem[m]); m++;

    m = (CPU_ENTRY_RESERVE_SIZE + LowIntId * INT_ENTRY_MEM_SIZE)/4;
    SET_TYPE4_UNSIGNED_MOV(InstMem[m], RA3, 50); m++;
    SET_TYPE2_MOVE_INNER_READ_IMM(InstMem[m], INTERNAL_REG_RETI, 31, LowIntId);    m++; //int return
    SET_ERROR_INST(InstMem[m]); m++;
}

SET_TEST(TESTNAME, should_do_int_processing_when_int_mask_is_one)
{
	int Error;
    
    //given
    do_init();

	//when 
    SetIntMask1 = 0x0000; SetIntMask2 = 0x3000;
    SetIntGlobalFlag = 0x80;
    // set register
    
    //write inst mem
    write_inst_mem();

	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    TEST_ASSERT_EQUAL(30, GET_CPU_REG(RA1));
    TEST_ASSERT_EQUAL(40, GET_CPU_REG(RA2));
    TEST_ASSERT_EQUAL(50, GET_CPU_REG(RA3));
}

SET_TEST(TESTNAME, should_not_do_int_processing_when_int_global_is_disabled)
{
	int Error;
    
    //given
    do_init();
    
	//when 
    SetIntMask1 = 0x0000; SetIntMask2 = 0x0000;
    SetIntGlobalFlag = 0x80;
    // set register
    
    //write inst mem
    write_inst_mem();

	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    TEST_ASSERT_EQUAL(30, GET_CPU_REG(RA1));
    TEST_ASSERT_EQUAL(0, GET_CPU_REG(RA2));
    TEST_ASSERT_EQUAL(0, GET_CPU_REG(RA3));
}

SET_TEST(TESTNAME, should_preempt_int_processing_when_higher_priority_swi_int_come)
{
	int Error;
    
    //given
    do_init();
    
    SET_CPU_INT_INPUT(HighIntId, 0); 
    SET_CPU_INT_INPUT(LowIntId, 1); 

    //when 
    SetIntMask1 = 0x0000; SetIntMask2 = 0x3000;
    SetIntGlobalFlag = 0x80;
    // set register
    
    //write inst mem
    write_inst_mem();

    m = (CPU_ENTRY_RESERVE_SIZE + LowIntId * INT_ENTRY_MEM_SIZE)/4;
    SET_TYPE4_UNSIGNED_MOV(InstMem[m], RA3, 50); m++;
    SET_TYPE2_SWI_IMM(InstMem[m], (HighIntId - INTERNAL_INT_NUM - EXTERNAL_INT_NUM)); m++;
    SET_TYPE2_MOVE_INNER_READ_IMM(InstMem[m], INTERNAL_REG_RETI, 31, LowIntId);    m++; //int return
    SET_ERROR_INST(InstMem[m]); m++;


	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    TEST_ASSERT_EQUAL(30, GET_CPU_REG(RA1));
    TEST_ASSERT_EQUAL(40, GET_CPU_REG(RA2));
    TEST_ASSERT_EQUAL(50, GET_CPU_REG(RA3));
}

SET_TEST(TESTNAME, should_not_preempt_int_processing_when_lower_priority_swi_int_come)
{
	int Error;
    
    //given
    do_init();
    
    SET_CPU_INT_INPUT(HighIntId, 1); 
    SET_CPU_INT_INPUT(LowIntId, 0); 

    //when 
    SetIntMask1 = 0x0000; SetIntMask2 = 0x3000;
    SetIntGlobalFlag = 0x80;
    // set register
    
    //write inst mem
    write_inst_mem();

    m = (CPU_ENTRY_RESERVE_SIZE + HighIntId * INT_ENTRY_MEM_SIZE)/4;
    SET_TYPE4_UNSIGNED_MOV(InstMem[m], RA2, 40); m++;
    SET_TYPE2_SWI_IMM(InstMem[m], (LowIntId - INTERNAL_INT_NUM - EXTERNAL_INT_NUM)); m++;
    SET_ERROR_INST(InstMem[m]); m++;
    SET_TYPE2_MOVE_INNER_READ_IMM(InstMem[m], INTERNAL_REG_RETI, 31, LowIntId);    m++; //int return
    


	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    TEST_ASSERT_EQUAL(20, GET_CPU_REG(RA1));
    TEST_ASSERT_EQUAL(40, GET_CPU_REG(RA2));
    TEST_ASSERT_EQUAL(0,  GET_CPU_REG(RA3));
}

SET_TEST(TESTNAME, should_not_preempt_int_processing_when_equal_priority_swi_int_come)
{
	int Error;
    
    //given
    do_init();
    
    HighIntPriority = 10;
    LowIntPriority = 10;

    SET_CPU_INT_INPUT(HighIntId, 1); 
    SET_CPU_INT_INPUT(LowIntId, 0); 

    //when 
    SetIntMask1 = 0x0000; SetIntMask2 = 0x3000;
    SetIntGlobalFlag = 0x80;
    // set register
    
    //write inst mem
    write_inst_mem();

    m = (CPU_ENTRY_RESERVE_SIZE + HighIntId * INT_ENTRY_MEM_SIZE)/4;
    SET_TYPE4_UNSIGNED_MOV(InstMem[m], RA2, 40); m++;
    SET_TYPE2_SWI_IMM(InstMem[m], (LowIntId - INTERNAL_INT_NUM - EXTERNAL_INT_NUM)); m++;
    SET_ERROR_INST(InstMem[m]); m++;
    SET_TYPE2_MOVE_INNER_READ_IMM(InstMem[m], INTERNAL_REG_RETI, 31, LowIntId);    m++; //int return
    


	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    TEST_ASSERT_EQUAL(20, GET_CPU_REG(RA1));
    TEST_ASSERT_EQUAL(40, GET_CPU_REG(RA2));
    TEST_ASSERT_EQUAL(0,  GET_CPU_REG(RA3));
}

SET_TEST(TESTNAME, should_not_do_int_processing_when_int_mask_is_zero)
{
	int Error;
    
    //given
    do_init();

	//when 
    SetIntMask1 = 0x0000; SetIntMask2 = 0x0000;
    SetIntGlobalFlag = 0x80;
    // set register
    
    //write inst mem
    write_inst_mem();

	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    TEST_ASSERT_EQUAL(30, GET_CPU_REG(RA1));
    TEST_ASSERT_EQUAL(0, GET_CPU_REG(RA2));
    TEST_ASSERT_EQUAL(0, GET_CPU_REG(RA3));
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, should_do_int_processing_when_int_mask_is_one);
    SET_RUN_TEST_CASE(TESTNAME, should_not_do_int_processing_when_int_global_is_disabled);
    SET_RUN_TEST_CASE(TESTNAME, should_preempt_int_processing_when_higher_priority_swi_int_come);
    SET_RUN_TEST_CASE(TESTNAME, should_not_preempt_int_processing_when_lower_priority_swi_int_come);
    SET_RUN_TEST_CASE(TESTNAME, should_not_preempt_int_processing_when_equal_priority_swi_int_come);
    SET_RUN_TEST_CASE(TESTNAME, should_not_do_int_processing_when_int_mask_is_zero);
}


