/*
 * test_inst_type2_st.c
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
#define TESTNAME inst_type2_st

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

SET_TEST(TESTNAME, test_type2_st_4_bytes)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, IMM1, IMM2;
    
	//given
	InstSize = 2;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    IMM1 = 8;
    DataMemAddrBase2 = 200;
    IMM2 = 16;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + IMM1), 0);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + IMM2), 0);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RB = 1;
    RD = 2;
    SET_CPU_REG(RB, DataMemAddrBase1);
    SET_CPU_REG(RD, Value1);
	SET_TYPE2_ST_4_BYTE(InstMem[0], RD, RB, IMM1);

    SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
    SET_CPU_REG((RD + RegOff), Value2);
	SET_TYPE2_ST_4_BYTE(InstMem[1], (RD + RegOff), (RB + RegOff), IMM2);
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), read_4_bytes_from_mem((unsigned char *)DataMem, DataMemAddrBase1 + IMM1));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), read_4_bytes_from_mem((unsigned char *)DataMem, DataMemAddrBase2 + IMM2));
}

SET_TEST(TESTNAME, test_type2_st_1_bytes)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, IMM1, IMM2;
    
	//given
	InstSize = 8;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    IMM1 = 8 + 4;
    DataMemAddrBase2 = 200;
    IMM2 = 16 + 4;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + IMM1), 0);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + IMM2), 0);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RB = 0;
    RD = 5;
    SET_CPU_REG(RB, DataMemAddrBase1);
    
    SET_CPU_REG((RD + 0), (Value1 >> 24));
    SET_CPU_REG((RD + 1), (Value1 >> 16));
    SET_CPU_REG((RD + 2), (Value1 >> 8));
    SET_CPU_REG((RD + 3), (Value1 >> 0));

	SET_TYPE2_ST_1_BYTE(InstMem[0], (RD + 0), RB, (IMM1 + 0));
    SET_TYPE2_ST_1_BYTE(InstMem[1], (RD + 1), RB, (IMM1 + 1));
    SET_TYPE2_ST_1_BYTE(InstMem[2], (RD + 2), RB, (IMM1 + 2));
    SET_TYPE2_ST_1_BYTE(InstMem[3], (RD + 3), RB, (IMM1 + 3));

    SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
    
    SET_CPU_REG((RD + RegOff + 0), (Value2 >> 24));
    SET_CPU_REG((RD + RegOff + 1), (Value2 >> 16));
    SET_CPU_REG((RD + RegOff + 2), (Value2 >> 8));
    SET_CPU_REG((RD + RegOff + 3), (Value2 >> 0));

	SET_TYPE2_ST_1_BYTE(InstMem[4], (RD + RegOff + 0), (RB + RegOff), (IMM2 + 0));
    SET_TYPE2_ST_1_BYTE(InstMem[5], (RD + RegOff + 1), (RB + RegOff), (IMM2 + 1));
    SET_TYPE2_ST_1_BYTE(InstMem[6], (RD + RegOff + 2), (RB + RegOff), (IMM2 + 2));
    SET_TYPE2_ST_1_BYTE(InstMem[7], (RD + RegOff + 3), (RB + RegOff), (IMM2 + 3));

    while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), read_4_bytes_from_mem((unsigned char *)DataMem, DataMemAddrBase1 + IMM1));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), read_4_bytes_from_mem((unsigned char *)DataMem, DataMemAddrBase2 + IMM2));
}

SET_TEST(TESTNAME, test_type2_st_2_bytes)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, IMM1, IMM2;
    
	//given
	InstSize = 4;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    IMM1 = 8 + 8;
    DataMemAddrBase2 = 200;
    IMM2 = 16 + 8;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + IMM1), 0);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + IMM2), 0);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RB = 0;
    RD = 5;
    SET_CPU_REG(RB, DataMemAddrBase1);
    
    SET_CPU_REG((RD + 0), (Value1 >> 16));
    SET_CPU_REG((RD + 1), (Value1 >> 0));
    
	SET_TYPE2_ST_2_BYTE(InstMem[0], (RD + 0), RB, (IMM1 + 0));
    SET_TYPE2_ST_2_BYTE(InstMem[1], (RD + 1), RB, (IMM1 + 2));
    
    SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
    
    SET_CPU_REG((RD + RegOff + 0), (Value2 >> 16));
    SET_CPU_REG((RD + RegOff + 1), (Value2 >> 0));

	SET_TYPE2_ST_2_BYTE(InstMem[2], (RD + RegOff + 0), (RB + RegOff), (IMM2 + 0));
    SET_TYPE2_ST_2_BYTE(InstMem[3], (RD + RegOff + 1), (RB + RegOff), (IMM2 + 2));
    
    while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), read_4_bytes_from_mem((unsigned char *)DataMem, DataMemAddrBase1 + IMM1));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), read_4_bytes_from_mem((unsigned char *)DataMem, DataMemAddrBase2 + IMM2));
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, test_type2_st_4_bytes);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_st_1_bytes);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_st_2_bytes);
}

