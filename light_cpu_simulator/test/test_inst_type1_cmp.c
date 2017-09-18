/*
 * test_inst_type1_cmp.c
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
#define TESTNAME inst_type1_cmp

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, should_set_Z_flag_when_two_input_are_equal)
{
	int InstSize, i,Value1, Value2;
	int RA, RB;

	//given
	InstSize = 1;
	Value1 = 0x00001111;
    Value2 = 0x00001111;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
	
	SET_TYPE1_CMP(InstMem[0], RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_Z());
}

SET_TEST(TESTNAME, should_set_N_flag_when_RB_smaller_than_RA)
{
	int InstSize, i,Value1, Value2;
	int RA, RB;

	//given
	InstSize = 1;
	Value1 = 0x00001111;
    Value2 = 0x00000111;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
	
	SET_TYPE1_CMP(InstMem[0], RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_N());
}

SET_TEST(TESTNAME, should_set_C_flag_when_RB_larger_than_RA)
{
	int InstSize, i,Value1, Value2;
	int RA, RB;

	//given
	InstSize = 1;
	Value1 = 0x00001111;
    Value2 = 0x00010111;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
	
	SET_TYPE1_CMP(InstMem[0], RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_C());
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, should_set_Z_flag_when_two_input_are_equal);
    SET_RUN_TEST_CASE(TESTNAME, should_set_N_flag_when_RB_smaller_than_RA);
    SET_RUN_TEST_CASE(TESTNAME, should_set_C_flag_when_RB_larger_than_RA);
}

