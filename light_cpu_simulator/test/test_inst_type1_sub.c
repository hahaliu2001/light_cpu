/*
 * test_inst_type1_sub.c
 *
 *  Created on: Sep 11, 2017
 *      Author: jie
 */

#include "cpu_external.h"
#include "mem.h"
#include "cpu_test_helper.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(inst_type1_sub);

TEST_SETUP(inst_type1_sub)
{
  //This is run before EACH TEST
	
}

TEST_TEAR_DOWN(inst_type1_sub)
{
	
}

TEST(inst_type1_sub, test_type1_sub_with_small_input)
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

		SET_TYPE1_SUB(InstMem[0], RD, RB, RA);
		SET_CPU_REG(RA, Value);
		SET_CPU_REG(RB, (Value * 2));

		while (!run_cpu())
		{
		}

		//expected
		TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
		TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
		TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

		TEST_ASSERT_EQUAL(Value, (int)GET_CPU_REG(RD));

		//update
		Value *= 2;
	}
}

TEST(inst_type1_sub, should_set_Z_flag_when_result_equal_to_zero)
{
	int InstSize, i,Value;
	int RA, RB, RD;
	
	//given
	InstSize = 1;
	Value = 5;
	
	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//get
	
	//when 
	i = 0;
	RA = i;
	RB = i + 14;
	RD = i+7;

	SET_TYPE1_SUB(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value);
	SET_CPU_REG(RB, Value);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
	TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
	TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

	TEST_ASSERT_EQUAL(1			, GET_CPU_SR_FLAG_Z());
	TEST_ASSERT_EQUAL(0, (int)GET_CPU_REG(RD));
}

TEST(inst_type1_sub, should_set_N_flag_when_result_is_negative)
{
	int InstSize, i,Value;
	int RA, RB, RD;
	
	//given
	InstSize = 1;
	Value = 5;
	
	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//get
	
	//when 
	i = 0;
	RA = i;
	RB = i + 14;
	RD = i+7;

	SET_TYPE1_SUB(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value * 2);
	SET_CPU_REG(RB, Value);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
	TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
	TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

	TEST_ASSERT_EQUAL(1			, GET_CPU_SR_FLAG_N());
	TEST_ASSERT_EQUAL((-Value), (int)GET_CPU_REG(RD));
}

TEST(inst_type1_sub, should_set_C_flag_when_result_produce_carry)
{
	int InstSize, i,Value;
	int RA, RB, RD;
	
	//given
	InstSize = 1;
	Value = 5;
	
	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//get
	
	//when 
	i = 0;
	RA = i;
	RB = i + 14;
	RD = i+7;

	SET_TYPE1_SUB(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value * 2);
	SET_CPU_REG(RB, Value);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
	TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
	TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

	TEST_ASSERT_EQUAL(1			, GET_CPU_SR_FLAG_C());
	TEST_ASSERT_EQUAL((-Value), (int)GET_CPU_REG(RD));
}

TEST(inst_type1_sub, should_set_V_flag_when_positive_minus_negative_and_result_is_negative)
{
	int InstSize, i,Value;
	int RA, RB, RD;
	
	//given
	InstSize = 1;
	Value = 0x7fffffff;
	
	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//get
	
	//when 
	i = 0;
	RA = i;
	RB = i + 14;
	RD = i+7;

	SET_TYPE1_SUB(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, -Value);
	SET_CPU_REG(RB, Value);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
	TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
	TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

	TEST_ASSERT_EQUAL(1			, GET_CPU_SR_FLAG_V());
	TEST_ASSERT_EQUAL((Value * 2), (int)GET_CPU_REG(RD));
}

TEST(inst_type1_sub, should_set_V_flag_when_negative_minus_positive_and_result_is_positive)
{
	int InstSize, i,Value;
	int RA, RB, RD;
	
	//given
	InstSize = 1;
	Value = 0x7fffffff;
	
	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//get
	
	//when 
	i = 0;
	RA = i;
	RB = i + 14;
	RD = i+7;

	SET_TYPE1_SUB(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value);
	SET_CPU_REG(RB, -Value);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
	TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
	TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

	TEST_ASSERT_EQUAL(1			, GET_CPU_SR_FLAG_V());
	TEST_ASSERT_EQUAL((-Value * 2), (int)GET_CPU_REG(RD));
}

TEST_GROUP_RUNNER(inst_type1_sub)
{
	printf("test instruction type 1 sub \n");
	//test type 1 sub
	RUN_TEST_CASE(inst_type1_sub, test_type1_sub_with_small_input);
	RUN_TEST_CASE(inst_type1_sub, should_set_Z_flag_when_result_equal_to_zero);
	RUN_TEST_CASE(inst_type1_sub, should_set_N_flag_when_result_is_negative);
	RUN_TEST_CASE(inst_type1_sub, should_set_C_flag_when_result_produce_carry);
	RUN_TEST_CASE(inst_type1_sub, should_set_V_flag_when_positive_minus_negative_and_result_is_negative);
	RUN_TEST_CASE(inst_type1_sub, should_set_V_flag_when_negative_minus_positive_and_result_is_positive);
	
	//test type 1 subc
	
}
