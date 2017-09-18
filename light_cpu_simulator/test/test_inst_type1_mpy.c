/*
 * test_inst_type1_mpy.c
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
#define TESTNAME inst_type1_mpy

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, test_type1_unsigned_mpy_with_small_positive_input)
{
	int InstSize, i,Value;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value = 5;
	for (i=0; i < 15; i++)
	{
		reset_cpu((unsigned char *)InstMem, InstSize * 4,
				(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
				(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

		//get

		//when
		RA = i;
		RB = i + 14;
		RD = i+7;

		SET_TYPE1_MPY(InstMem[0], RD, RB, RA);
		SET_CPU_REG(RA, Value);
		SET_CPU_REG(RB, (Value * 2));

		while (!run_cpu())
		{
		}

		//expected
		TEST_ASSERT_EQUAL((unsigned int)(Value * Value * 2), GET_CPU_REG(RD));

		//update
		Value *= 2;
	}
}

SET_TEST(TESTNAME, test_type1_unsigned_mpy_with_big_positive_input)
{
	int InstSize, i,Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = 0x00005FFF;
	Value2 = 0xFFFFEFFF;
	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//get

	//when
	i = 0;
	RA = i;
	RB = i + 14;
	RD = i+7;

	SET_TYPE1_MPY(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL((unsigned int)(Value1 * Value2), GET_CPU_REG(RD));

}

SET_TEST(TESTNAME, should_set_Z_flag_when_result_is_zero)
{
	int InstSize, i,Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = 0x0;
	Value2 = 0xFFFFEFFF;
	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//get

	//when
	i = 0;
	RA = i;
	RB = i + 14;
	RD = i+7;

	SET_TYPE1_MPY(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_Z());
	TEST_ASSERT_EQUAL((unsigned int)(Value1 * Value2), GET_CPU_REG(RD));

}

SET_TEST(TESTNAME, should_set_N_flag_when_result_is_negative)
{
	int InstSize, i,Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = 0x10;
	Value2 = 0xFFFFEFFF;
	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//get

	//when
	i = 0;
	RA = i;
	RB = i + 14;
	RD = i+7;

	SET_TYPE1_MPY(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_N());
	TEST_ASSERT_EQUAL((unsigned int)(Value1 * Value2), GET_CPU_REG(RD));

}


SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, test_type1_unsigned_mpy_with_small_positive_input);
	SET_RUN_TEST_CASE(TESTNAME, test_type1_unsigned_mpy_with_big_positive_input);
	SET_RUN_TEST_CASE(TESTNAME, should_set_Z_flag_when_result_is_zero);
	SET_RUN_TEST_CASE(TESTNAME, should_set_N_flag_when_result_is_negative);
}

