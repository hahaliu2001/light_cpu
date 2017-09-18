/*
 * test_inst_type1_ld.c
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
#define TESTNAME inst_type1_ld

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, test_type1_ld_4_bytes_with_RB_increase_by_0)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RA, RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, DataMemAddrOffset1, DataMemAddrOffset2;
    unsigned int Update;
    
	//given
	InstSize = 2;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    DataMemAddrOffset1 = 8;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    Update = 0;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), Value1);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), Value2);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RA = 0;
    RB = 1;
    RD = 2;
    SET_CPU_REG(RA, DataMemAddrOffset1);
	SET_CPU_REG(RB, DataMemAddrBase1);
	SET_TYPE1_LD_4_BYTE(InstMem[0], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), RD, RB, RA);

    SET_CPU_REG((RA + RegOff), DataMemAddrOffset2);
	SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
	SET_TYPE1_LD_4_BYTE(InstMem[1], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), (RD + RegOff), (RB + RegOff), (RA + RegOff));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), GET_CPU_REG((RD + RegOff)));
    TEST_ASSERT_EQUAL((DataMemAddrBase1 + 0), GET_CPU_REG(RB));
    TEST_ASSERT_EQUAL((DataMemAddrBase2 + 0), GET_CPU_REG((RB + RegOff)));
}

SET_TEST(TESTNAME, test_type1_ld_4_bytes_with_RB_increase_by_1)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RA, RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, DataMemAddrOffset1, DataMemAddrOffset2;
    unsigned int Update;
    
	//given
	InstSize = 2;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    DataMemAddrOffset1 = 8;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    Update = 1;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), Value1);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), Value2);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RA = 0;
    RB = 1;
    RD = 2;
    SET_CPU_REG(RA, DataMemAddrOffset1);
	SET_CPU_REG(RB, DataMemAddrBase1);
	SET_TYPE1_LD_4_BYTE(InstMem[0], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), RD, RB, RA);

    SET_CPU_REG((RA + RegOff), DataMemAddrOffset2);
	SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
	SET_TYPE1_LD_4_BYTE(InstMem[1], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), (RD + RegOff), (RB + RegOff), (RA + RegOff));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), GET_CPU_REG((RD + RegOff)));
    TEST_ASSERT_EQUAL((DataMemAddrBase1 + 1), GET_CPU_REG(RB));
    TEST_ASSERT_EQUAL((DataMemAddrBase2 + 1), GET_CPU_REG((RB + RegOff)));
}

SET_TEST(TESTNAME, test_type1_ld_4_bytes_with_RB_increase_by_2)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RA, RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, DataMemAddrOffset1, DataMemAddrOffset2;
    unsigned int Update;
    
	//given
	InstSize = 2;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    DataMemAddrOffset1 = 8;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    Update = 2;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), Value1);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), Value2);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RA = 0;
    RB = 1;
    RD = 2;
    SET_CPU_REG(RA, DataMemAddrOffset1);
	SET_CPU_REG(RB, DataMemAddrBase1);
	SET_TYPE1_LD_4_BYTE(InstMem[0], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), RD, RB, RA);

    SET_CPU_REG((RA + RegOff), DataMemAddrOffset2);
	SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
	SET_TYPE1_LD_4_BYTE(InstMem[1], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), (RD + RegOff), (RB + RegOff), (RA + RegOff));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), GET_CPU_REG((RD + RegOff)));
    TEST_ASSERT_EQUAL((DataMemAddrBase1 + 2), GET_CPU_REG(RB));
    TEST_ASSERT_EQUAL((DataMemAddrBase2 + 2), GET_CPU_REG((RB + RegOff)));
}

SET_TEST(TESTNAME, test_type1_ld_4_bytes_with_RB_increase_by_4)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RA, RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, DataMemAddrOffset1, DataMemAddrOffset2;
    unsigned int Update;
    
	//given
	InstSize = 2;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    DataMemAddrOffset1 = 8;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    Update = 3;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), Value1);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), Value2);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RA = 0;
    RB = 1;
    RD = 2;
    SET_CPU_REG(RA, DataMemAddrOffset1);
	SET_CPU_REG(RB, DataMemAddrBase1);
	SET_TYPE1_LD_4_BYTE(InstMem[0], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), RD, RB, RA);

    SET_CPU_REG((RA + RegOff), DataMemAddrOffset2);
	SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
	SET_TYPE1_LD_4_BYTE(InstMem[1], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), (RD + RegOff), (RB + RegOff), (RA + RegOff));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), GET_CPU_REG((RD + RegOff)));
    TEST_ASSERT_EQUAL((DataMemAddrBase1 + 4), GET_CPU_REG(RB));
    TEST_ASSERT_EQUAL((DataMemAddrBase2 + 4), GET_CPU_REG((RB + RegOff)));
}

SET_TEST(TESTNAME, test_type1_ld_4_bytes_with_RB_decrease_by_0)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RA, RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, DataMemAddrOffset1, DataMemAddrOffset2;
    unsigned int Update;
    
	//given
	InstSize = 2;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    DataMemAddrOffset1 = 8;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    Update = 4;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), Value1);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), Value2);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RA = 0;
    RB = 1;
    RD = 2;
    SET_CPU_REG(RA, DataMemAddrOffset1);
	SET_CPU_REG(RB, DataMemAddrBase1);
	SET_TYPE1_LD_4_BYTE(InstMem[0], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), RD, RB, RA);

    SET_CPU_REG((RA + RegOff), DataMemAddrOffset2);
	SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
	SET_TYPE1_LD_4_BYTE(InstMem[1], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), (RD + RegOff), (RB + RegOff), (RA + RegOff));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), GET_CPU_REG((RD + RegOff)));
    TEST_ASSERT_EQUAL((DataMemAddrBase1 - 0), GET_CPU_REG(RB));
    TEST_ASSERT_EQUAL((DataMemAddrBase2 - 0), GET_CPU_REG((RB + RegOff)));
}

SET_TEST(TESTNAME, test_type1_ld_4_bytes_with_RB_decrease_by_1)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RA, RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, DataMemAddrOffset1, DataMemAddrOffset2;
    unsigned int Update;
    
	//given
	InstSize = 2;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    DataMemAddrOffset1 = 8;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    Update = 5;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), Value1);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), Value2);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RA = 0;
    RB = 1;
    RD = 2;
    SET_CPU_REG(RA, DataMemAddrOffset1);
	SET_CPU_REG(RB, DataMemAddrBase1);
	SET_TYPE1_LD_4_BYTE(InstMem[0], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), RD, RB, RA);

    SET_CPU_REG((RA + RegOff), DataMemAddrOffset2);
	SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
	SET_TYPE1_LD_4_BYTE(InstMem[1], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), (RD + RegOff), (RB + RegOff), (RA + RegOff));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), GET_CPU_REG((RD + RegOff)));
    TEST_ASSERT_EQUAL((DataMemAddrBase1 - 1), GET_CPU_REG(RB));
    TEST_ASSERT_EQUAL((DataMemAddrBase2 - 1), GET_CPU_REG((RB + RegOff)));
}

SET_TEST(TESTNAME, test_type1_ld_4_bytes_with_RB_decrease_by_2)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RA, RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, DataMemAddrOffset1, DataMemAddrOffset2;
    unsigned int Update;
    
	//given
	InstSize = 2;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    DataMemAddrOffset1 = 8;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    Update = 6;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), Value1);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), Value2);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RA = 0;
    RB = 1;
    RD = 2;
    SET_CPU_REG(RA, DataMemAddrOffset1);
	SET_CPU_REG(RB, DataMemAddrBase1);
	SET_TYPE1_LD_4_BYTE(InstMem[0], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), RD, RB, RA);

    SET_CPU_REG((RA + RegOff), DataMemAddrOffset2);
	SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
	SET_TYPE1_LD_4_BYTE(InstMem[1], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), (RD + RegOff), (RB + RegOff), (RA + RegOff));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), GET_CPU_REG((RD + RegOff)));
    TEST_ASSERT_EQUAL((DataMemAddrBase1 - 2), GET_CPU_REG(RB));
    TEST_ASSERT_EQUAL((DataMemAddrBase2 - 2), GET_CPU_REG((RB + RegOff)));
}

SET_TEST(TESTNAME, test_type1_ld_4_bytes_with_RB_decrease_by_4)
{
	int InstSize;
    unsigned int Value1, Value2;
	int RA, RB, RD;
    int RegOff = 10;
    unsigned int DataMemAddrBase1, DataMemAddrBase2, DataMemAddrOffset1, DataMemAddrOffset2;
    unsigned int Update;
    
	//given
	InstSize = 2;
	Value1 = 0x12345678;
    Value2 = 0x89ABCDEF;
    DataMemAddrBase1 = 100;
    DataMemAddrOffset1 = 8;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    Update = 7;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), Value1);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), Value2);

    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    RA = 0;
    RB = 1;
    RD = 2;
    SET_CPU_REG(RA, DataMemAddrOffset1);
	SET_CPU_REG(RB, DataMemAddrBase1);
	SET_TYPE1_LD_4_BYTE(InstMem[0], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), RD, RB, RA);

    SET_CPU_REG((RA + RegOff), DataMemAddrOffset2);
	SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
	SET_TYPE1_LD_4_BYTE(InstMem[1], ((Update >> 2) & 1), ((Update >> 1) & 1), ((Update >> 0) & 1), (RD + RegOff), (RB + RegOff), (RA + RegOff));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)(Value1), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((unsigned int)(Value2), GET_CPU_REG((RD + RegOff)));
    TEST_ASSERT_EQUAL((DataMemAddrBase1 - 4), GET_CPU_REG(RB));
    TEST_ASSERT_EQUAL((DataMemAddrBase2 - 4), GET_CPU_REG((RB + RegOff)));
}

SET_TEST(TESTNAME, test_type1_ld_unsigned_1_byte)
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
    DataMemAddrOffset1 = 8 ;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), Value1);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), Value2);

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


	SET_TYPE1_LD_UNSIGNED_1_BYTE(InstMem[0], RD, RB, RA);
    SET_TYPE1_LD_UNSIGNED_1_BYTE(InstMem[1], (RD + 1), RB, (RA + 1));
    SET_TYPE1_LD_UNSIGNED_1_BYTE(InstMem[2], (RD + 2), RB, (RA + 2));
    SET_TYPE1_LD_UNSIGNED_1_BYTE(InstMem[3], (RD + 3), RB, (RA + 3));

    SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
    SET_CPU_REG((RA + RegOff + 0), (DataMemAddrOffset2 + 0));
    SET_CPU_REG((RA + RegOff + 1), (DataMemAddrOffset2 + 1));
    SET_CPU_REG((RA + RegOff + 2), (DataMemAddrOffset2 + 2));
    SET_CPU_REG((RA + RegOff + 3), (DataMemAddrOffset2 + 3));
	
	SET_TYPE1_LD_UNSIGNED_1_BYTE(InstMem[4], (RD + RegOff), (RB + RegOff), (RA + RegOff));
    SET_TYPE1_LD_UNSIGNED_1_BYTE(InstMem[5], (RD + RegOff + 1), (RB + RegOff), (RA + RegOff + 1));
    SET_TYPE1_LD_UNSIGNED_1_BYTE(InstMem[6], (RD + RegOff + 2), (RB + RegOff), (RA + RegOff + 2));
    SET_TYPE1_LD_UNSIGNED_1_BYTE(InstMem[7], (RD + RegOff + 3), (RB + RegOff), (RA + RegOff + 3));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value1 >> 24)), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value1 >> 16)), GET_CPU_REG((RD + 1)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value1 >> 8) ), GET_CPU_REG((RD + 2)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value1 >> 0) ), GET_CPU_REG((RD + 3)));

    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value2 >> 24)), GET_CPU_REG((RD + RegOff)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value2 >> 16)), GET_CPU_REG((RD + RegOff + 1)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value2 >> 8) ), GET_CPU_REG((RD + RegOff + 2)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned char)(Value2 >> 0) ), GET_CPU_REG((RD + RegOff + 3)));
}

SET_TEST(TESTNAME, test_type1_ld_signed_1_byte)
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
    DataMemAddrOffset1 = 8 ;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), Value1);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), Value2);

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


	SET_TYPE1_LD_SIGNED_1_BYTE(InstMem[0], RD, RB, RA);
    SET_TYPE1_LD_SIGNED_1_BYTE(InstMem[1], (RD + 1), RB, (RA + 1));
    SET_TYPE1_LD_SIGNED_1_BYTE(InstMem[2], (RD + 2), RB, (RA + 2));
    SET_TYPE1_LD_SIGNED_1_BYTE(InstMem[3], (RD + 3), RB, (RA + 3));

    SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
    SET_CPU_REG((RA + RegOff + 0), (DataMemAddrOffset2 + 0));
    SET_CPU_REG((RA + RegOff + 1), (DataMemAddrOffset2 + 1));
    SET_CPU_REG((RA + RegOff + 2), (DataMemAddrOffset2 + 2));
    SET_CPU_REG((RA + RegOff + 3), (DataMemAddrOffset2 + 3));
	
	SET_TYPE1_LD_SIGNED_1_BYTE(InstMem[4], (RD + RegOff), (RB + RegOff), (RA + RegOff));
    SET_TYPE1_LD_SIGNED_1_BYTE(InstMem[5], (RD + RegOff + 1), (RB + RegOff), (RA + RegOff + 1));
    SET_TYPE1_LD_SIGNED_1_BYTE(InstMem[6], (RD + RegOff + 2), (RB + RegOff), (RA + RegOff + 2));
    SET_TYPE1_LD_SIGNED_1_BYTE(InstMem[7], (RD + RegOff + 3), (RB + RegOff), (RA + RegOff + 3));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value1 >> 24)), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value1 >> 16)), GET_CPU_REG((RD + 1)));
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value1 >> 8) ), GET_CPU_REG((RD + 2)));
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value1 >> 0) ), GET_CPU_REG((RD + 3)));

    TEST_ASSERT_EQUAL((unsigned int)((char)(Value2 >> 24)), GET_CPU_REG((RD + RegOff)));
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value2 >> 16)), GET_CPU_REG((RD + RegOff + 1)));
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value2 >> 8) ), GET_CPU_REG((RD + RegOff + 2)));
    TEST_ASSERT_EQUAL((unsigned int)((char)(Value2 >> 0) ), GET_CPU_REG((RD + RegOff + 3)));
}

SET_TEST(TESTNAME, test_type1_ld_unsigned_2_byte)
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
    DataMemAddrOffset1 = 8 ;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), Value1);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), Value2);

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
    
	SET_TYPE1_LD_UNSIGNED_2_BYTE(InstMem[0], RD, RB, RA);
    SET_TYPE1_LD_UNSIGNED_2_BYTE(InstMem[1], (RD + 1), RB, (RA + 1));
    
    SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
    SET_CPU_REG((RA + RegOff + 0), (DataMemAddrOffset2 + 0));
    SET_CPU_REG((RA + RegOff + 1), (DataMemAddrOffset2 + 2));
    
	SET_TYPE1_LD_UNSIGNED_2_BYTE(InstMem[2], (RD + RegOff), (RB + RegOff), (RA + RegOff));
    SET_TYPE1_LD_UNSIGNED_2_BYTE(InstMem[3], (RD + RegOff + 1), (RB + RegOff), (RA + RegOff + 1));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)((unsigned short)(Value1 >> 16)), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned short)(Value1 >> 0 )), GET_CPU_REG((RD + 1)));
    
    TEST_ASSERT_EQUAL((unsigned int)((unsigned short)(Value2 >> 16)), GET_CPU_REG((RD + RegOff)));
    TEST_ASSERT_EQUAL((unsigned int)((unsigned short)(Value2 >> 0 )), GET_CPU_REG((RD + RegOff + 1)));
    
}

SET_TEST(TESTNAME, test_type1_ld_signed_2_byte)
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
    DataMemAddrOffset1 = 8 ;
    DataMemAddrBase2 = 200;
    DataMemAddrOffset2 = 16;
    
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase1 + DataMemAddrOffset1), Value1);
    write_mem_from_int((unsigned char *)DataMem, (DataMemAddrBase2 + DataMemAddrOffset2), Value2);

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
    
	SET_TYPE1_LD_SIGNED_2_BYTE(InstMem[0], RD, RB, RA);
    SET_TYPE1_LD_SIGNED_2_BYTE(InstMem[1], (RD + 1), RB, (RA + 1));
    
    SET_CPU_REG((RB + RegOff), DataMemAddrBase2);
    SET_CPU_REG((RA + RegOff + 0), (DataMemAddrOffset2 + 0));
    SET_CPU_REG((RA + RegOff + 1), (DataMemAddrOffset2 + 2));
    
	SET_TYPE1_LD_SIGNED_2_BYTE(InstMem[2], (RD + RegOff), (RB + RegOff), (RA + RegOff));
    SET_TYPE1_LD_SIGNED_2_BYTE(InstMem[3], (RD + RegOff + 1), (RB + RegOff), (RA + RegOff + 1));
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL((unsigned int)((short)(Value1 >> 16)), GET_CPU_REG(RD));
    TEST_ASSERT_EQUAL((unsigned int)((short)(Value1 >> 0 )), GET_CPU_REG((RD + 1)));
    
    TEST_ASSERT_EQUAL((unsigned int)((short)(Value2 >> 16)), GET_CPU_REG((RD + RegOff)));
    TEST_ASSERT_EQUAL((unsigned int)((short)(Value2 >> 0 )), GET_CPU_REG((RD + RegOff + 1)));
    
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, test_type1_ld_4_bytes_with_RB_increase_by_0);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_ld_4_bytes_with_RB_increase_by_1);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_ld_4_bytes_with_RB_increase_by_2);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_ld_4_bytes_with_RB_increase_by_4);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_ld_4_bytes_with_RB_decrease_by_0);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_ld_4_bytes_with_RB_decrease_by_1);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_ld_4_bytes_with_RB_decrease_by_2);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_ld_4_bytes_with_RB_decrease_by_4);

    SET_RUN_TEST_CASE(TESTNAME, test_type1_ld_unsigned_1_byte);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_ld_signed_1_byte);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_ld_unsigned_2_byte);
    SET_RUN_TEST_CASE(TESTNAME, test_type1_ld_signed_2_byte);
}

