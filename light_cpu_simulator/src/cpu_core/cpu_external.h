/* =========================================================================
    light CPU simulator Project
    Copyright (c) 2017 Jie Liu
    [Released under MIT License. Please refer to license.txt for details]
============================================================================ */

#ifndef CPU_EXTERNAL_H_
#define CPU_EXTERNAL_H_

/* CPU external interface, outer module can only access functions defined here */
void reset_cpu(	unsigned char *InstMemBase, unsigned int InstMemSizeIn4Bytes,
						unsigned char *DataMemBase, unsigned int DataMemSizeIn4Bytes,
						unsigned char *StackMemBase,unsigned int StackMemSizeInByte4Bytes );

unsigned int run_cpu(void);

#endif /* CPU_CORE_H_ */
