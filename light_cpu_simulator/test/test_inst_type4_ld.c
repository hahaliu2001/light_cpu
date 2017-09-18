/*
 * test_inst_type4_ld.c
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
#define TESTNAME inst_type4_ld

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
    init_mem((unsigned char *)InstMem, INSTRUCTION_MEM_SIZE);
    init_mem((unsigned char *)DataMem, DATA_MEM_SIZE);
    init_mem((unsigned char *)StackMem, STACK_MEM_SIZE);
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, test_type4_ld_4_bytes)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RD1, RD2;
    unsigned int IMM1, IMM2;
    
	//given
	InstSize = 2;
	Value1 = 0x12345678;    Value2 = 0x89abcdef;
    IMM1 = 8; IMM2 = 16;
    RD1 = 2; RD2 = 5;
    
    write_mem_from_int((unsigned char *)DataMem, ((IMM1 >> 2) << 2), Value1);
    write_mem_from_int((unsigned char *)DataMem, ((IMM2 >> 2) << 2), Value2);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register

    //write instruction memory
    SET_TYPE4_LD_4_BYTE(InstMem[0], RD1, IMM1);
    SET_TYPE4_LD_4_BYTE(InstMem[1], RD2, IMM2);
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), GET_CPU_REG(RD1));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), GET_CPU_REG(RD2));
}

SET_TEST(TESTNAME, test_type4_ld_unsigned_1_byte)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RD1, RD2;
    unsigned int IMM1, IMM2;
    
	//given
	InstSize = 8;
	Value1 = 0x12345678;    Value2 = 0x89abcdef;
    IMM1 = 8; IMM2 = 16;
    RD1 = 2; RD2 = 10;
    
    write_mem_from_int((unsigned char *)DataMem, ((IMM1 >> 2) << 2), Value1);
    write_mem_from_int((unsigned char *)DataMem, ((IMM2 >> 2) << 2), Value2);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register

    //write instruction memory
    SET_TYPE4_LD_UNSIGNED_1_BYTE(InstMem[0], (RD1 + 0), (IMM1 + 0));
    SET_TYPE4_LD_UNSIGNED_1_BYTE(InstMem[1], (RD1 + 1), (IMM1 + 1));
    SET_TYPE4_LD_UNSIGNED_1_BYTE(InstMem[2], (RD1 + 2), (IMM1 + 2));
    SET_TYPE4_LD_UNSIGNED_1_BYTE(InstMem[3], (RD1 + 3), (IMM1 + 3));
    SET_TYPE4_LD_UNSIGNED_1_BYTE(InstMem[4], (RD2 + 0), (IMM2 + 0));
    SET_TYPE4_LD_UNSIGNED_1_BYTE(InstMem[5], (RD2 + 1), (IMM2 + 1));
    SET_TYPE4_LD_UNSIGNED_1_BYTE(InstMem[6], (RD2 + 2), (IMM2 + 2));
    SET_TYPE4_LD_UNSIGNED_1_BYTE(InstMem[7], (RD2 + 3), (IMM2 + 3));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value1 >> 24)), GET_CPU_REG((RD1 + 0)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value1 >> 16)), GET_CPU_REG((RD1 + 1)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value1 >> 8) ), GET_CPU_REG((RD1 + 2)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value1 >> 0) ), GET_CPU_REG((RD1 + 3)));

    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value2 >> 24)), GET_CPU_REG((RD2 + 0)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value2 >> 16)), GET_CPU_REG((RD2 + 1)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value2 >> 8) ), GET_CPU_REG((RD2 + 2)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value2 >> 0) ), GET_CPU_REG((RD2 + 3)));
}

SET_TEST(TESTNAME, test_type4_ld_signed_1_byte)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RD1, RD2;
    unsigned int IMM1, IMM2;
    
	//given
	InstSize = 8;
	Value1 = 0x12345678;    Value2 = 0x89abcdef;
    IMM1 = 8; IMM2 = 16;
    RD1 = 2; RD2 = 10;
    
    write_mem_from_int((unsigned char *)DataMem, ((IMM1 >> 2) << 2), Value1);
    write_mem_from_int((unsigned char *)DataMem, ((IMM2 >> 2) << 2), Value2);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register

    //write instruction memory
    SET_TYPE4_LD_SIGNED_1_BYTE(InstMem[0], (RD1 + 0), (IMM1 + 0));
    SET_TYPE4_LD_SIGNED_1_BYTE(InstMem[1], (RD1 + 1), (IMM1 + 1));
    SET_TYPE4_LD_SIGNED_1_BYTE(InstMem[2], (RD1 + 2), (IMM1 + 2));
    SET_TYPE4_LD_SIGNED_1_BYTE(InstMem[3], (RD1 + 3), (IMM1 + 3));
    SET_TYPE4_LD_SIGNED_1_BYTE(InstMem[4], (RD2 + 0), (IMM2 + 0));
    SET_TYPE4_LD_SIGNED_1_BYTE(InstMem[5], (RD2 + 1), (IMM2 + 1));
    SET_TYPE4_LD_SIGNED_1_BYTE(InstMem[6], (RD2 + 2), (IMM2 + 2));
    SET_TYPE4_LD_SIGNED_1_BYTE(InstMem[7], (RD2 + 3), (IMM2 + 3));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value1 >> 24)), GET_CPU_REG((RD1 + 0)));
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value1 >> 16)), GET_CPU_REG((RD1 + 1)));
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value1 >> 8) ), GET_CPU_REG((RD1 + 2)));
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value1 >> 0) ), GET_CPU_REG((RD1 + 3)));

    TEST_ASSERT_EQUAL((unsigned int)((char)(Value2 >> 24)), GET_CPU_REG((RD2 + 0)));
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value2 >> 16)), GET_CPU_REG((RD2 + 1)));
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value2 >> 8) ), GET_CPU_REG((RD2 + 2)));
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value2 >> 0) ), GET_CPU_REG((RD2 + 3)));
}

SET_TEST(TESTNAME, test_type4_ld_unsigned_2_byte)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RD1, RD2;
    unsigned int IMM1, IMM2;
    
	//given
	InstSize = 4;
	Value1 = 0x12345678;    Value2 = 0x89abcdef;
    IMM1 = 8; IMM2 = 16;
    RD1 = 2; RD2 = 10;
    
    write_mem_from_int((unsigned char *)DataMem, ((IMM1 >> 2) << 2), Value1);
    write_mem_from_int((unsigned char *)DataMem, ((IMM2 >> 2) << 2), Value2);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register

    //write instruction memory
    SET_TYPE4_LD_UNSIGNED_2_BYTE(InstMem[0], (RD1 + 0), (IMM1 + 0));
    SET_TYPE4_LD_UNSIGNED_2_BYTE(InstMem[1], (RD1 + 1), (IMM1 + 2));
    SET_TYPE4_LD_UNSIGNED_2_BYTE(InstMem[2], (RD2 + 0), (IMM2 + 0));
    SET_TYPE4_LD_UNSIGNED_2_BYTE(InstMem[3], (RD2 + 1), (IMM2 + 2));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)((unsigned short)(Value1 >> 16)), GET_CPU_REG((RD1 + 0)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned short)(Value1 >>  0)), GET_CPU_REG((RD1 + 1)));

    TEST_ASSERT_EQUAL((unsigned int)((unsigned short)(Value2 >> 16)), GET_CPU_REG((RD2 + 0)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned short)(Value2 >>  0)), GET_CPU_REG((RD2 + 1)));
}

SET_TEST(TESTNAME, test_type4_ld_signed_2_byte)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RD1, RD2;
    unsigned int IMM1, IMM2;
    
	//given
	InstSize = 4;
	Value1 = 0x12345678;    Value2 = 0x89abcdef;
    IMM1 = 8; IMM2 = 16;
    RD1 = 2; RD2 = 10;
    
    write_mem_from_int((unsigned char *)DataMem, ((IMM1 >> 2) << 2), Value1);
    write_mem_from_int((unsigned char *)DataMem, ((IMM2 >> 2) << 2), Value2);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register

    //write instruction memory
    SET_TYPE4_LD_SIGNED_2_BYTE(InstMem[0], (RD1 + 0), (IMM1 + 0));
    SET_TYPE4_LD_SIGNED_2_BYTE(InstMem[1], (RD1 + 1), (IMM1 + 2));
    SET_TYPE4_LD_SIGNED_2_BYTE(InstMem[2], (RD2 + 0), (IMM2 + 0));
    SET_TYPE4_LD_SIGNED_2_BYTE(InstMem[3], (RD2 + 1), (IMM2 + 2));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)((short)(Value1 >> 16)), GET_CPU_REG((RD1 + 0)));
    TEST_ASSERT_EQUAL((unsigned int)((short)(Value1 >>  0)), GET_CPU_REG((RD1 + 1)));

    TEST_ASSERT_EQUAL((unsigned int)((short)(Value2 >> 16)), GET_CPU_REG((RD2 + 0)));
    TEST_ASSERT_EQUAL((unsigned int)((short)(Value2 >>  0)), GET_CPU_REG((RD2 + 1)));
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, test_type4_ld_4_bytes);
    SET_RUN_TEST_CASE(TESTNAME, test_type4_ld_unsigned_1_byte);
    SET_RUN_TEST_CASE(TESTNAME, test_type4_ld_signed_1_byte);
    SET_RUN_TEST_CASE(TESTNAME, test_type4_ld_unsigned_2_byte);
    SET_RUN_TEST_CASE(TESTNAME, test_type4_ld_signed_2_byte);
}

