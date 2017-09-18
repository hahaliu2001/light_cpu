/*
 * test_inst_type4_cmp.c
 *
 *  Created on: Sep 17, 2017
 *      Author: jie
 */

#include "cpu_external.h"
#include "mem.h"
#include "cpu_test_helper.h"
#include "unity.h"
#include "unity_fixture.h"

#undef  TESTNAME
#define TESTNAME inst_type4_cmp

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, should_set_Z_flag_when_RD_is_equal_to_unsigned_IMM)
{
	int InstSize, Value1, Value2;
	int RD;

	//given
	InstSize = 1;
	Value1 = 0x1111;
    Value2 = 0x1111;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
    RD = 14;
	
	SET_TYPE4_UNSIGNED_CMP(InstMem[0], RD, Value2);
	SET_CPU_REG(RD, Value1);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_Z());
}

SET_TEST(TESTNAME, should_set_Z_flag_when_RD_is_equal_to_signed_IMM)
{
	int InstSize, Value1, Value2;
	int RD;

	//given
	InstSize = 1;
	Value1 = 0xfffff111;
    Value2 = 0x0000f111;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
    RD = 14;
    SET_CPU_REG(RD, Value1);
	
	SET_TYPE4_SIGNED_CMP(InstMem[0], RD, Value2);
	
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_Z());
}

SET_TEST(TESTNAME, should_set_N_flag_when_RD_is_smmaller_than_unsigned_IMM)
{
	int InstSize, Value1, Value2;
	int RD;

	//given
	InstSize = 1;
	Value1 = 0x1111;
    Value2 = 0xf111;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
    RD = 14;
	
	SET_TYPE4_UNSIGNED_CMP(InstMem[0], RD, Value2);
	SET_CPU_REG(RD, Value1);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_N());
}


SET_TEST(TESTNAME, should_set_N_flag_when_RD_is_smmaller_than_signed_IMM)
{
	int InstSize, Value1, Value2;
	int RD;

	//given
	InstSize = 1;
	Value1 = 0xfffff011;
    Value2 = 0xf111;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
    RD = 14;
	
	SET_TYPE4_SIGNED_CMP(InstMem[0], RD, Value2);
	SET_CPU_REG(RD, Value1);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_N());
}

SET_TEST(TESTNAME, should_set_C_flag_when_RD_is_larger_than_unsigned_IMM)
{
	int InstSize, Value1, Value2;
	int RD;

	//given
	InstSize = 1;
	Value1 = 0xf1111;
    Value2 = 0xf111;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
    RD = 14;
	
	SET_TYPE4_UNSIGNED_CMP(InstMem[0], RD, Value2);
	SET_CPU_REG(RD, Value1);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(1, GET_CPU_SR_FLAG_C());
}

SET_TEST(TESTNAME, should_N_flag_equal_to_V_flag_when_RD_is_larger_than_signed_IMM)
{
	int InstSize, Value1, Value2;
	int RD;

	//given
	InstSize = 1;
	Value1 = 0x111;
    Value2 = 0xff11;

	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when
    RD = 14;
	
	SET_TYPE4_SIGNED_CMP(InstMem[0], RD, Value2);
	SET_CPU_REG(RD, Value1);
	
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(GET_CPU_SR_FLAG_N(), GET_CPU_SR_FLAG_V());
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, should_set_Z_flag_when_RD_is_equal_to_unsigned_IMM);
    SET_RUN_TEST_CASE(TESTNAME, should_set_Z_flag_when_RD_is_equal_to_signed_IMM);
    SET_RUN_TEST_CASE(TESTNAME, should_set_N_flag_when_RD_is_smmaller_than_unsigned_IMM);
    SET_RUN_TEST_CASE(TESTNAME, should_set_N_flag_when_RD_is_smmaller_than_signed_IMM);
    SET_RUN_TEST_CASE(TESTNAME, should_set_C_flag_when_RD_is_larger_than_unsigned_IMM);
    SET_RUN_TEST_CASE(TESTNAME, should_N_flag_equal_to_V_flag_when_RD_is_larger_than_signed_IMM);
}


