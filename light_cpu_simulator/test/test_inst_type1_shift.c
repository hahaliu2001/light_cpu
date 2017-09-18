/*
 * test_inst_type1_shift.c
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
#define TESTNAME inst_type1_shift

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, should_clear_C_flag_when_left_shift_and_result_not_more_than_32bits)
{
	int InstSize, i;
    unsigned int Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = 3;
    Value2 = 16;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
    RD = i;
	
	SET_TYPE1_ARITH_SHIFT(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_SR_FLAG_C());
    TEST_ASSERT_EQUAL((Value2 << Value1), GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, should_set_C_flag_when_left_shift_and_result_more_than_32bits)
{
	int InstSize, i;
    unsigned int Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = 3;
    Value2 = 0x800ed000;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
    RD = i;
	
	SET_TYPE1_ARITH_SHIFT(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_C());
    TEST_ASSERT_EQUAL((Value2 << Value1), GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, should_set_Z_flag_when_left_shift_and_result_is_zero)
{
	int InstSize, i;
    unsigned int Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = 16;
    Value2 = 0x800e0000;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
    RD = i;
	
	SET_TYPE1_ARITH_SHIFT(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_C());
    TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_Z());
    TEST_ASSERT_EQUAL((Value2 << Value1), GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, should_set_Z_flag_when_logic_right_shift_and_result_is_zero)
{
	int InstSize, i;
    unsigned int Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = (unsigned int)(-16);
    Value2 = 0x0000800e;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
    RD = i;
	
	SET_TYPE1_LOGIC_SHIFT(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_Z());
    TEST_ASSERT_EQUAL((Value2 >> (-Value1)), GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, should_clear_Z_flag_when_logic_right_shift_and_result_is_not_zero)
{
	int InstSize, i;
    unsigned int Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = (unsigned int)(-16);
    Value2 = 0x7654800e;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
    RD = i;
	
	SET_TYPE1_LOGIC_SHIFT(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_SR_FLAG_Z());
    TEST_ASSERT_EQUAL((Value2 >> (-Value1)), GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, should_clear_Z_flag_when_logic_right_shift_negative_value_and_result_is_not_zero)
{
	int InstSize, i;
    unsigned int Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = (unsigned int)(-16);
    Value2 = 0x8654800e;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
    RD = i;
	
	SET_TYPE1_LOGIC_SHIFT(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_SR_FLAG_Z());
    TEST_ASSERT_EQUAL(((unsigned int)((int)Value2 >> (-Value1))), GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, should_clear_Z_flag_when_logic_right_shift_large_number_for_negative_value)
{
	int InstSize, i,Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = -33;
    Value2 = 0x8654800e;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
    RD = i;
	
	SET_TYPE1_LOGIC_SHIFT(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_SR_FLAG_Z());
    TEST_ASSERT_EQUAL((Value2 >> (-Value1)), (int)GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, should_clear_Z_flag_when_arithmetical_right_shift_positive_value_and_result_is_not_zero)
{
	int InstSize, i,Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = -16;
    Value2 = 0x7654800e;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
    RD = i;
	
	SET_TYPE1_ARITH_SHIFT(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_SR_FLAG_Z());
    TEST_ASSERT_EQUAL((Value2 >> (-Value1)), GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, should_set_Z_flag_when_arithmetical_right_shift_positive_value_and_result_is_zero)
{
	int InstSize, i,Value1, Value2;
	int RA, RB, RD;

	//given
	InstSize = 1;
	Value1 = -16;
    Value2 = 0x0000800e;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
	i = 0;
	RA = i;
	RB = i + 14;
    RD = i;
	
	SET_TYPE1_ARITH_SHIFT(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value1);
	SET_CPU_REG(RB, Value2);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_Z());
    TEST_ASSERT_EQUAL((Value2 >> (-Value1)), GET_CPU_REG(RD));
}



SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, should_clear_C_flag_when_left_shift_and_result_not_more_than_32bits);
    SET_RUN_TEST_CASE(TESTNAME, should_set_C_flag_when_left_shift_and_result_more_than_32bits);
    SET_RUN_TEST_CASE(TESTNAME, should_set_Z_flag_when_left_shift_and_result_is_zero);
    SET_RUN_TEST_CASE(TESTNAME, should_set_Z_flag_when_logic_right_shift_and_result_is_zero);
    SET_RUN_TEST_CASE(TESTNAME, should_clear_Z_flag_when_logic_right_shift_and_result_is_not_zero);
    SET_RUN_TEST_CASE(TESTNAME, should_clear_Z_flag_when_logic_right_shift_negative_value_and_result_is_not_zero);
    SET_RUN_TEST_CASE(TESTNAME, should_clear_Z_flag_when_arithmetical_right_shift_positive_value_and_result_is_not_zero);
    SET_RUN_TEST_CASE(TESTNAME, should_set_Z_flag_when_arithmetical_right_shift_positive_value_and_result_is_zero);
    SET_RUN_TEST_CASE(TESTNAME, should_clear_Z_flag_when_logic_right_shift_large_number_for_negative_value);
}

