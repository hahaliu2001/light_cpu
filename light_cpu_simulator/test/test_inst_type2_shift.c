/*
 * test_inst_type2_shift.c
 *
 *  Created on: Sep 16, 2017
 *      Author: jie
 */
#include "cpu_external.h"
#include "mem.h"
#include "cpu_test_helper.h"
#include "unity.h"
#include "unity_fixture.h"

#undef  TESTNAME
#define TESTNAME inst_type2_shift

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, test_left_shift)
{
    int InstSize;
    int RegOff = 10;
	int RB, RD;
    unsigned int IMM1, IMM2;
    unsigned int Value1, Value2;
		
	//given
	InstSize = 2;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB = 1;
	RD = 7;
    IMM1 = 6;
    Value1 = 0x12345678;

    SET_CPU_REG(RB, Value1);
	SET_TYPE2_ARITH_SHIFT(InstMem[0], RD, RB, IMM1);
    
    IMM2 = 0x7;
    Value2 = 0x89abcdef;

    SET_CPU_REG((RB + RegOff), Value2);
	SET_TYPE2_ARITH_SHIFT(InstMem[1], (RD + RegOff), (RB + RegOff), IMM2);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL((Value1 << (unsigned int)((int)(IMM1 << 21) >> 21)), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((Value2 << (unsigned int)((int)(IMM2 << 21) >> 21)), GET_CPU_REG((RD + RegOff)));
}

SET_TEST(TESTNAME, test_logic_right_shift)
{
    int InstSize;
    int RegOff = 10;
	int RB, RD;
    unsigned int IMM1, IMM2;
    unsigned int Value1, Value2;
		
	//given
	InstSize = 2;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB = 1;
	RD = 7;
    IMM1 = (unsigned int)(-6);
    Value1 = 0x12345678;

    SET_CPU_REG(RB, Value1);
	SET_TYPE2_LOGIC_SHIFT(InstMem[0], RD, RB, IMM1);
    
    IMM2 = (unsigned int)(-7);
    Value2 = 0x89abcdef;

    SET_CPU_REG((RB + RegOff), Value2);
	SET_TYPE2_LOGIC_SHIFT(InstMem[1], (RD + RegOff), (RB + RegOff), IMM2);

	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((Value1 >> 6), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((Value2 >> 7), GET_CPU_REG((RD + RegOff)));

}

SET_TEST(TESTNAME, test_arithmetical_right_shift)
{
    int InstSize;
    int RegOff = 10;
	int RB, RD;
    unsigned int IMM1, IMM2;
    unsigned int Value1, Value2;
		
	//given
	InstSize = 2;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB = 1;
	RD = 7;
    IMM1 = (unsigned int)(-6);
    Value1 = 0x12345678;

    SET_CPU_REG(RB, Value1);
	SET_TYPE2_ARITH_SHIFT(InstMem[0], RD, RB, IMM1);
    
    IMM2 = (unsigned int)(-7);
    Value2 = 0x89abcdef;

    SET_CPU_REG((RB + RegOff), Value2);
	SET_TYPE2_ARITH_SHIFT(InstMem[1], (RD + RegOff), (RB + RegOff), IMM2);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL(((unsigned int)((int)Value1 >> 6)), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL(((unsigned int)((int)Value2 >> 7)), GET_CPU_REG((RD + RegOff)));
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));
    SET_RUN_TEST_CASE(TESTNAME, test_left_shift);
	SET_RUN_TEST_CASE(TESTNAME, test_logic_right_shift);
    SET_RUN_TEST_CASE(TESTNAME, test_arithmetical_right_shift);
}


