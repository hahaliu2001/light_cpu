#include "cpu_external.h"
#include "mem.h"
#include "cpu_test_helper.h"
#include "unity.h"
#include "unity_fixture.h"

#undef  TESTNAME
#define TESTNAME inst_type1_add

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, test_type1_add_with_small_input)
{
	int InstSize, i,Value, Error = 0;
	int RA, RB, RD;
	int EXPECTED_N;
	int EXPECTED_Z;
	int EXPECTED_C;
	int EXPECTED_V;
		
	//given
	InstSize = 1;
	Value = 5;
	for (i=0; i < 15; i++)
	{
		reset_cpu((unsigned char *)InstMem, InstSize * 4,
				(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
				(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

		//get
		EXPECTED_N = GET_CPU_SR_FLAG_N();
		EXPECTED_Z = GET_CPU_SR_FLAG_Z();
		EXPECTED_C = GET_CPU_SR_FLAG_C();
		EXPECTED_V = GET_CPU_SR_FLAG_V();

		//when 
		RA = i;
		RB = i + 14;
		RD = i+7;

		SET_TYPE1_ADD(InstMem[0], RD, RB, RA);
		SET_CPU_REG(RA, Value);
		SET_CPU_REG(RB, (Value * 2));

        Error = 0;
		while (!Error)
		{
            Error = run_cpu();
		}

        //expected
        TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
		TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
		TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

		TEST_ASSERT_EQUAL(EXPECTED_N, GET_CPU_SR_FLAG_N());
		TEST_ASSERT_EQUAL(EXPECTED_Z, GET_CPU_SR_FLAG_Z());
		TEST_ASSERT_EQUAL(EXPECTED_C, GET_CPU_SR_FLAG_C());
		TEST_ASSERT_EQUAL(EXPECTED_V, GET_CPU_SR_FLAG_V());

		TEST_ASSERT_EQUAL((Value * 3), (int)GET_CPU_REG(RD));

		//update
		Value *= 2;
	}
}

SET_TEST(TESTNAME, should_set_Z_flag_when_result_equal_to_zero)
{
	int InstSize, i,Value, Error;
	int RA, RB, RD;
	int EXPECTED_N;
	//int EXPECTED_Z;
	//int EXPECTED_C;
	int EXPECTED_V;
		
	//given
	InstSize = 1;
	Value = 0;
	for (i=0; i < 15; i++)
	{
		reset_cpu((unsigned char *)InstMem, InstSize * 4,
				(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
				(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

		//get
		EXPECTED_N = GET_CPU_SR_FLAG_N();
		//EXPECTED_Z = GET_CPU_SR_FLAG_Z();
		//EXPECTED_C = GET_CPU_SR_FLAG_C();
		EXPECTED_V = GET_CPU_SR_FLAG_V();

		//when 
		RA = i;
		RB = i + 14;
		RD = i+7;

		SET_TYPE1_ADD(InstMem[0], RD, RB, RA);
		SET_CPU_REG(RA, Value);
		SET_CPU_REG(RB, -Value);

		Error = 0;
		while (!Error)
		{
            Error = run_cpu();
		}

		//expected
        
		TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
		TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
		TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

		TEST_ASSERT_EQUAL(EXPECTED_N, GET_CPU_SR_FLAG_N());
		TEST_ASSERT_EQUAL(1			, GET_CPU_SR_FLAG_Z());
		//TEST_ASSERT_EQUAL(EXPECTED_C, GET_CPU_SR_FLAG_C());
		TEST_ASSERT_EQUAL(EXPECTED_V, GET_CPU_SR_FLAG_V());

		TEST_ASSERT_EQUAL(0, (int)GET_CPU_REG(RD));

		//update
		Value += 12;
	}
}

SET_TEST(TESTNAME, should_set_N_flag_when_result_is_negative)
{
	int InstSize, i,Value;
	int RA, RB, RD;
	//int EXPECTED_N;
	int EXPECTED_Z;
	int EXPECTED_C;
	int EXPECTED_V;
		
	//given
	InstSize = 1;
	Value = 0;
	for (i=0; i < 15; i++)
	{
		reset_cpu((unsigned char *)InstMem, InstSize * 4,
				(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
				(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

		//get
		//EXPECTED_N = GET_CPU_SR_FLAG_N();
		EXPECTED_Z = GET_CPU_SR_FLAG_Z();
		EXPECTED_C = GET_CPU_SR_FLAG_C();
		EXPECTED_V = GET_CPU_SR_FLAG_V();

		//when 
		RA = i;
		RB = i + 14;
		RD = i+7;

		SET_TYPE1_ADD(InstMem[0], RD, RB, RA);
		SET_CPU_REG(RA, Value);
		SET_CPU_REG(RB, (-Value * 2 - 5));

		while (!run_cpu())
		{
		}

		//expected
		TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
		TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
		TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

		TEST_ASSERT_EQUAL(1			, GET_CPU_SR_FLAG_N());
		TEST_ASSERT_EQUAL(EXPECTED_Z, GET_CPU_SR_FLAG_Z());
		TEST_ASSERT_EQUAL(EXPECTED_C, GET_CPU_SR_FLAG_C());
		TEST_ASSERT_EQUAL(EXPECTED_V, GET_CPU_SR_FLAG_V());

		TEST_ASSERT_EQUAL((-Value - 5), (int)GET_CPU_REG(RD));

		//update
		Value += 12;
	}
}

SET_TEST(TESTNAME, should_set_C_flag_when_result_produce_carry)
{
	int InstSize, i,Value;
	int RA, RB, RD;
	//int EXPECTED_N;
	//int EXPECTED_Z;
	//int EXPECTED_C;
	//int EXPECTED_V;
		
	//given
	InstSize = 1;
	Value = 0x7fffffff;
	for (i=0; i < 1; i++)
	{
		reset_cpu((unsigned char *)InstMem, InstSize * 4,
				(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
				(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

		//get
		//EXPECTED_N = GET_CPU_SR_FLAG_N();
		//EXPECTED_Z = GET_CPU_SR_FLAG_Z();
		//EXPECTED_C = GET_CPU_SR_FLAG_C();
		//EXPECTED_V = GET_CPU_SR_FLAG_V();

		//when 
		RA = i;
		RB = i + 14;
		RD = i+7;

		SET_TYPE1_ADD(InstMem[0], RD, RB, RA);
		SET_CPU_REG(RA, Value);
		SET_CPU_REG(RB, (Value * 2));

		while (!run_cpu())
		{
		}

		//expected
		TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
		TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
		TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

		//TEST_ASSERT_EQUAL(EXPECTED_N, GET_CPU_SR_FLAG_N());
		//TEST_ASSERT_EQUAL(EXPECTED_Z, GET_CPU_SR_FLAG_Z());
		TEST_ASSERT_EQUAL(1			, GET_CPU_SR_FLAG_C());
		//TEST_ASSERT_EQUAL(EXPECTED_V, GET_CPU_SR_FLAG_V());

		TEST_ASSERT_EQUAL((int)(Value *3), (int)GET_CPU_REG(RD));

		//update
		Value += 12;
	}
}

SET_TEST(TESTNAME, should_set_V_flag_when_two_positive_input_and_result_is_negative)
{
	int InstSize, i,Value;
	int RA, RB, RD;
		
	//given
	InstSize = 1;
	Value = 0x7fffffff;
	
	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
	i = 0;
	RA = i;
	RB = i + 14;
	RD = i+7;

	SET_TYPE1_ADD(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value);
	SET_CPU_REG(RB, Value);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
	TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
	TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

	TEST_ASSERT_EQUAL(1			, GET_CPU_SR_FLAG_V());
	
	TEST_ASSERT_EQUAL((int)(Value * 2), (int)GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, should_set_V_flag_when_two_negative_input_and_result_is_positive)
{
	int InstSize, i,Value;
	int RA, RB, RD;
		
	//given
	InstSize = 1;
	Value = 0x80001111;
	
	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
	i = 0;
	RA = i;
	RB = i + 14;
	RD = i+7;

	SET_TYPE1_ADD(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value);
	SET_CPU_REG(RB, Value);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
	TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
	TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

	TEST_ASSERT_EQUAL(1			, GET_CPU_SR_FLAG_V());
	
	TEST_ASSERT_EQUAL((int)(Value * 2), (int)GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, test_addc_when_c_is_zero)
{
	int InstSize, i,Value;
	int RA, RB, RD;
		
	//given
	InstSize = 1;
	Value = 0x00001111;
	
	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
	i = 0;
	RA = i;
	RB = i + 14;
	RD = i+7;

	SET_TYPE1_ADDC(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value);
	SET_CPU_REG(RB, Value);
	SET_CPU_SR_FLAG_C(0);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
	TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
	TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

	TEST_ASSERT_EQUAL((int)(Value * 2), (int)GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, test_addc_when_c_is_one)
{
	int InstSize, i,Value;
	int RA, RB, RD;
		
	//given
	InstSize = 1;
	Value = 0x00001111;
	
	reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
	i = 0;
	RA = i;
	RB = i + 14;
	RD = i+7;

	SET_TYPE1_ADDC(InstMem[0], RD, RB, RA);
	SET_CPU_REG(RA, Value);
	SET_CPU_REG(RB, Value);
	SET_CPU_SR_FLAG_C(1);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL(4, (UNITY_INT)GET_CPU_PC_REG());
	TEST_ASSERT_EQUAL(0, (UNITY_INT)GET_CPU_LR_REG());
	TEST_ASSERT_EQUAL(STACK_MEM_SIZE, (UNITY_INT)GET_CPU_SR_REG());

	TEST_ASSERT_EQUAL((int)(Value * 2 + 1), (int)GET_CPU_REG(RD));
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));
	//test type 1 add
	SET_RUN_TEST_CASE(TESTNAME, test_type1_add_with_small_input);
	SET_RUN_TEST_CASE(TESTNAME, should_set_Z_flag_when_result_equal_to_zero);
	SET_RUN_TEST_CASE(TESTNAME, should_set_N_flag_when_result_is_negative);
	SET_RUN_TEST_CASE(TESTNAME, should_set_C_flag_when_result_produce_carry);
	SET_RUN_TEST_CASE(TESTNAME, should_set_V_flag_when_two_positive_input_and_result_is_negative);
	SET_RUN_TEST_CASE(TESTNAME, should_set_V_flag_when_two_negative_input_and_result_is_positive);

	//test type 1 addc
	SET_RUN_TEST_CASE(TESTNAME, test_addc_when_c_is_zero);
	SET_RUN_TEST_CASE(TESTNAME, test_addc_when_c_is_one);
}

