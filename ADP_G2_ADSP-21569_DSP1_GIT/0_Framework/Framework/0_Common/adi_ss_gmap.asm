/*******************************************************************************
Copyright (c) 2014-2015 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
******************************************************************************
 * @file:    adi_ss_gmap.asm
 * @brief:   GMAP structure
 * @version: $Revision$
 * @date:    $Date$
   * Developed by: Automotive Software and Systems team, Bangalore, India                  
*****************************************************************************/
/*! \addtogroup Group_name
 *  @{
 */


.section/DM seg_dmda;

/* Variables for flag fields */
.var _Block0_L1_space_flag;
.var _Block1_L1_space_flag;
.var _Block2_L1_space_flag;
.var _Block3_L1_space_flag;
.var _Block_L3_code_space_flag;
.var _Block_L3_data_space_flag;
.var _Block_L2_data_space_flag;

/* These variables are allocated in the ldf */
.extern _Block0_L1_space;
.extern _Block0_L1_space_length;
.extern _Block1_L1_space;
.extern _Block1_L1_space_length;
.extern _Block2_L1_space;
.extern _Block2_L1_space_length;
.extern _Block3_L1_space;
.extern _Block3_L1_space_length;
.extern _Block_L3_code_space;
.extern _Block_L3_code_space_length;
.extern _Block_L3_data_space;
.extern _Block_L3_data_space_length;
.extern _Block_L2_data_space;
.extern _Block_L2_data_space_length;

#define NUM_BLOCKS 7
#define SIZE_GMAP (NUM_BLOCKS*2 + 1)

/* GMAP structure */

.global _GMAP;

.ALIGN 4;
_GMAP:
    .var = NUM_BLOCKS;
	.var = _Block0_L1_space;
	.var = _Block0_L1_space_length;
	.var = _Block0_L1_space_flag;
	.var = _Block1_L1_space;
	.var = _Block1_L1_space_length;
	.var = _Block1_L1_space_flag;
	.var = _Block2_L1_space;
	.var = _Block2_L1_space_length;
	.var = _Block2_L1_space_flag;
	.var = _Block3_L1_space;
	.var = _Block3_L1_space_length;
	.var = _Block3_L1_space_flag;
	.var = _Block_L3_code_space;
	.var = _Block_L3_code_space_length;
	.var = _Block_L3_code_space_flag;	
	.var = _Block_L3_data_space;
	.var = _Block_L3_data_space_length;
	.var = _Block_L3_data_space_flag;
	.var = _Block_L2_data_space;
	.var = _Block_L2_data_space_length;	
	.var = _Block_L2_data_space_flag;
._GMAP.end:
