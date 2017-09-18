/*
 * test_inst_type1_and.c
 *
 *  Created on: Sep 13, 2017
 *      Author: jie
 */

#include "cpu_external.h"
#include "mem.h"
#include "cpu_test_helper.h"
#include "unity.h"
#include "unity_fixture.h"

#undef  TESTNAME
#define TESTNAME inst_type1_and

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, test_type1_and)
{
	int InstSize, i,Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = 0xAAAAAAAA;
    Value2 = 0x0000FFFF;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
    RD = i;
	
	SET_TYPE1_AND(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((Value2 & Value1), GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, test_type1_not_and)
{
	int InstSize, i,Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = 0xAAAAAAAA;
    Value2 = 0x0000FFFF;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
    RD = i;
	
	SET_TYPE1_NOT_AND(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(~(unsigned int)(Value2 & Value1), GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, test_type1_or)
{
	int InstSize, i,Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = 0xAAAAAAAA;
    Value2 = 0x0000FFFF;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
    RD = i;
	
	SET_TYPE1_OR(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value2 | Value1), GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, test_type1_not_or)
{
	int InstSize, i,Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = 0xAAAAAAAA;
    Value2 = 0x0000FFFF;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
    RD = i;
	
	SET_TYPE1_NOT_OR(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(~(unsigned int)(Value2 | Value1), GET_CPU_REG(RD));
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, test_type1_and);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_not_and);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_or);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_not_or);
}

