/*
 * test_inst_type1_st.c
 *
 *  Created on: Sep 15, 2017
 *      Author: jie
 */

#include "cpu_external.h"
#include "mem.h"
#include "cpu_test_helper.h"
#include "unity.h"
#include "unity_fixture.h"

#undef  TESTNAME
#define TESTNAME inst_type1_st

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, test_type1_st_4_bytes)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RA, RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, DataMemAddrOffset1, DataMemAddrOffset2;
    
	//given
	InstSize = 2;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    DataMemAddrOffset1 = 8;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), 0);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), 0);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RA = 0;
    RB = 1;
    RD = 2;
    SET_CPU_REG(RA, DataMemAddrOffset1);
	SET_CPU_REG(RB, DataMemAddrBase1);
    SET_CPU_REG(RD, Value1);
	SET_TYPE1_ST_4_BYTE(InstMem[0], RD, RB, RA);

    SET_CPU_REG((RA + RegOff), DataMemAddrOffset2);
	SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
    SET_CPU_REG((RD + RegOff), Value2);
	SET_TYPE1_ST_4_BYTE(InstMem[1], (RD + RegOff), (RB + RegOff), (RA + RegOff));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), read_4_bytes_from_mem((unsigned char *)DataMem, DataMemAddrBase1 + DataMemAddrOffset1));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), read_4_bytes_from_mem((unsigned char *)DataMem, DataMemAddrBase2 + DataMemAddrOffset2));
}

SET_TEST(TESTNAME, test_type1_st_1_bytes)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RA, RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, DataMemAddrOffset1, DataMemAddrOffset2;
    
	//given
	InstSize = 8;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    DataMemAddrOffset1 = 8;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), 0);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), 0);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RB = 0;
    RA = 1;
    RD = 5;
    SET_CPU_REG(RB, DataMemAddrBase1);
    SET_CPU_REG(RA, DataMemAddrOffset1);
    SET_CPU_REG((RA + 1), (DataMemAddrOffset1 + 1));
    SET_CPU_REG((RA + 2), (DataMemAddrOffset1 + 2));
    SET_CPU_REG((RA + 3), (DataMemAddrOffset1 + 3));

    SET_CPU_REG((RD + 0), (Value1 >> 24));
    SET_CPU_REG((RD + 1), (Value1 >> 16));
    SET_CPU_REG((RD + 2), (Value1 >> 8));
    SET_CPU_REG((RD + 3), (Value1 >> 0));

	SET_TYPE1_ST_1_BYTE(InstMem[0], (RD + 0), RB, (RA + 0));
    SET_TYPE1_ST_1_BYTE(InstMem[1], (RD + 1), RB, (RA + 1));
    SET_TYPE1_ST_1_BYTE(InstMem[2], (RD + 2), RB, (RA + 2));
    SET_TYPE1_ST_1_BYTE(InstMem[3], (RD + 3), RB, (RA + 3));

    SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
    SET_CPU_REG((RA + RegOff + 0), (DataMemAddrOffset2 + 0));
    SET_CPU_REG((RA + RegOff + 1), (DataMemAddrOffset2 + 1));
    SET_CPU_REG((RA + RegOff + 2), (DataMemAddrOffset2 + 2));
    SET_CPU_REG((RA + RegOff + 3), (DataMemAddrOffset2 + 3));

    SET_CPU_REG((RD + RegOff + 0), (Value2 >> 24));
    SET_CPU_REG((RD + RegOff + 1), (Value2 >> 16));
    SET_CPU_REG((RD + RegOff + 2), (Value2 >> 8));
    SET_CPU_REG((RD + RegOff + 3), (Value2 >> 0));

	SET_TYPE1_ST_1_BYTE(InstMem[4], (RD + RegOff + 0), (RB + RegOff), (RA + RegOff + 0));
    SET_TYPE1_ST_1_BYTE(InstMem[5], (RD + RegOff + 1), (RB + RegOff), (RA + RegOff + 1));
    SET_TYPE1_ST_1_BYTE(InstMem[6], (RD + RegOff + 2), (RB + RegOff), (RA + RegOff + 2));
    SET_TYPE1_ST_1_BYTE(InstMem[7], (RD + RegOff + 3), (RB + RegOff), (RA + RegOff + 3));

    while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), read_4_bytes_from_mem((unsigned char *)DataMem, DataMemAddrBase1 + DataMemAddrOffset1));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), read_4_bytes_from_mem((unsigned char *)DataMem, DataMemAddrBase2 + DataMemAddrOffset2));
}

SET_TEST(TESTNAME, test_type1_st_2_bytes)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RA, RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, DataMemAddrOffset1, DataMemAddrOffset2;
    
	//given
	InstSize = 4;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    DataMemAddrOffset1 = 8;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), 0);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), 0);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RB = 0;
    RA = 1;
    RD = 5;
    SET_CPU_REG(RB, DataMemAddrBase1);
    SET_CPU_REG(RA, DataMemAddrOffset1);
    SET_CPU_REG((RA + 1), (DataMemAddrOffset1 + 2));
    
    SET_CPU_REG((RD + 0), (Value1 >> 16));
    SET_CPU_REG((RD + 1), (Value1 >> 0));
    
	SET_TYPE1_ST_2_BYTE(InstMem[0], (RD + 0), RB, (RA + 0));
    SET_TYPE1_ST_2_BYTE(InstMem[1], (RD + 1), RB, (RA + 1));
    
    SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
    SET_CPU_REG((RA + RegOff + 0), (DataMemAddrOffset2 + 0));
    SET_CPU_REG((RA + RegOff + 1), (DataMemAddrOffset2 + 2));
    
    SET_CPU_REG((RD + RegOff + 0), (Value2 >> 16));
    SET_CPU_REG((RD + RegOff + 1), (Value2 >> 0));

	SET_TYPE1_ST_2_BYTE(InstMem[2], (RD + RegOff + 0), (RB + RegOff), (RA + RegOff + 0));
    SET_TYPE1_ST_2_BYTE(InstMem[3], (RD + RegOff + 1), (RB + RegOff), (RA + RegOff + 1));
    
    while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), read_4_bytes_from_mem((unsigned char *)DataMem, DataMemAddrBase1 + DataMemAddrOffset1));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), read_4_bytes_from_mem((unsigned char *)DataMem, DataMemAddrBase2 + DataMemAddrOffset2));
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, test_type1_st_4_bytes);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_st_1_bytes);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_st_2_bytes);
}

