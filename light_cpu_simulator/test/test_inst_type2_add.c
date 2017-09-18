/*
 * test_inst_type2_add.c
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
#define TESTNAME inst_type2_add

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, test_type2_unsigned_add)
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
    IMM1 = 0x166;
    Value1 = 0x12345678;

    SET_CPU_REG(RB, Value1);
	SET_TYPE2_UNSIGNED_ADD(InstMem[0], RD, RB, IMM1);
    
    IMM2 = 0x766;
    Value2 = 0x89abcdef;

    SET_CPU_REG((RB + RegOff), Value2);
	SET_TYPE2_UNSIGNED_ADD(InstMem[1], (RD + RegOff), (RB + RegOff), IMM2);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL((Value1 + IMM1), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((Value2 + IMM2), GET_CPU_REG((RD + RegOff)));
}

SET_TEST(TESTNAME, test_type2_signed_add)
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
    IMM1 = 0x166;
    Value1 = 0x12345678;

    SET_CPU_REG(RB, Value1);
	SET_TYPE2_SIGNED_ADD(InstMem[0], RD, RB, IMM1);
    
    IMM2 = 0x766;
    Value2 = 0x89abcdef;

    SET_CPU_REG((RB + RegOff), Value2);
	SET_TYPE2_SIGNED_ADD(InstMem[1], (RD + RegOff), (RB + RegOff), IMM2);

	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(((unsigned int)((int)Value1 + ((int)(IMM1 << 21) >> 21))), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL(((unsigned int)((int)Value2 + ((int)(IMM2 << 21) >> 21))), GET_CPU_REG((RD + RegOff)));
}

SET_TEST(TESTNAME, test_type2_unsigned_addc_when_c_is_zero)
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
    IMM1 = 0x166;
    Value1 = 0x12345678;

    SET_CPU_SR_FLAG_C(0);

    SET_CPU_REG(RB, Value1);
	SET_TYPE2_UNSIGNED_ADDC(InstMem[0], RD, RB, IMM1);
    
    IMM2 = 0x766;
    Value2 = 0x89abcdef;

    SET_CPU_REG((RB + RegOff), Value2);
	SET_TYPE2_UNSIGNED_ADDC(InstMem[1], (RD + RegOff), (RB + RegOff), IMM2);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL((Value1 + IMM1), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((Value2 + IMM2), GET_CPU_REG((RD + RegOff)));
}

SET_TEST(TESTNAME, test_type2_unsigned_addc_when_c_is_one)
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
    IMM1 = 0x166;
    Value1 = 0x12345678;

    SET_CPU_SR_FLAG_C(1);

    SET_CPU_REG(RB, Value1);
	SET_TYPE2_UNSIGNED_ADDC(InstMem[0], RD, RB, IMM1);
    
    IMM2 = 0x766;
    Value2 = 0x89abcdef;

    SET_CPU_REG((RB + RegOff), Value2);
	SET_TYPE2_UNSIGNED_ADDC(InstMem[1], (RD + RegOff), (RB + RegOff), IMM2);

	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL((Value1 + IMM1 + 1), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((Value2 + IMM2), GET_CPU_REG((RD + RegOff)));
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, test_type2_unsigned_add);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_signed_add);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_unsigned_addc_when_c_is_zero);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_unsigned_addc_when_c_is_one);
}
