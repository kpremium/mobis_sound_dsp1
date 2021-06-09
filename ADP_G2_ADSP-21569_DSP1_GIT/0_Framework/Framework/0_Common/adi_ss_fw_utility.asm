/******************************************************************************
 Copyright (c) 2012 - Analog Devices Inc. All Rights Reserved.
 This software is proprietary & confidential to Analog Devices, Inc. 
 and its licensors. 
 ****************************************************************************** 

 Title: SigmaStudio for SHARC Application

 Description: Contains routine to check whether non floating point number is
 			  present in output.

 ******************************************************************************/ 
#include <platform_include.h>

/************* Defines ****************/
#define FLOAT_SCALE     -31
#define TRUNC_SCALE     23
#define BIT_SHIFT 	    8
#define MAX_VALUE_24BIT 8388607
.global IsNanInf.;
.global CopyFix2Float.;
.global CopyFloat2Fix.;

.section/pm/DOUBLE32 ss_fw_code_fast;
IsNanInf.:
//-------------------------------------------------------------------
//   Procedure statistics:
//   Frame size            = 10 words
//   Scratch registers used:{r0-r2,r4,r8,r12,i12,acc,mcc}
//   Call preserved registers used:{i7}
//   r4 = BufferPointer, r8 = nBufLength, r0 = return value
//   Return value = Non 0 value if input INF/NAN/IND else 0
//	 A single-precision NaN value is one whose mantissa is not zero and 
//	 whose exponent is set to the maximum - the sign bit is ignored). 
//-------------------------------------------------------------------

	/* Store value of registers/DAGS used */
	modify(i7,-9)(nw);
	dm(-9,i6) = r1;
	r1=i0;
	dm(-8,i6) = r1;
	r1=m0;
	dm(-7,i6) = r1;
	bit set mode1 BITM_REGF_MODE1_PEYEN;
	nop; nop;
	i0 = r4;
	m0 = 2;
	r8=	ASHIFT r8 by -1;
	r0 = r0 - r0, r4 = dm(i0,m0);
	
	LCNTR = r8, do (pc,IsNanInf_LoopEnd) until LCE;	
	if ne jump exit_loop_NAN (la);	// Jump out of loop if a non floating point number detected	
  	r1 = fext r4 by 0:23;          	// Extract mantissa, bits 0-23
  	if not sz r0 = m0;		// If mantissa not 0 r0 = Non 0 value
  	r1 = fext r4 by 23:8 (se);      // Extract exponent, bits 23-30 and sign-extend   
  	if not sz r0 = r0 - r0;		// If mantissa not 0 and exponent is zero r0 = Non 0 value else r0 = r0-r0 = 0
   	r1 = r1+1, r4 = dm(i0,m0);      // R1 becomes zero if exponent was max r0 = Non 0 value           
  	if eq r0 = m0;          	// if exponent == max return Non 0 value (NAN and INF)
  	r0 = r0 + r0;			// Dummy operation to get flag to check if NAN/INF/IND has occurred in any one of the processing element
  	if ne s0=r0;   			// Assign R0 and S0 to Non zero value to call exit loop if any one of the processing element detected NAN and INF  
	IsNanInf_LoopEnd:r1 = r0 + r0;	// Dummy operation to get flag to check if NAN/INF/IND has occurred
      	
    
	/* Restore values */
exit_loop_NAN:	
	bit clr mode1 BITM_REGF_MODE1_PEYEN;
	nop; nop;	
	r1=dm(-7,i6);
	m0=r1;
	r1=dm(-8,i6);
	i0=r1;	
	r1=dm(-9,i6);
	
	/* Return nResult*/
	i12=dm(m7,i6);
	jump (m14,i12) (db);  rframe; nop;
IsNanInf..end:



.section/pm/DOUBLE32 ss_fw_code_fast;
CopyFix2Float.:

	modify(i7,-7)(nw);
	dm(-6,i6)=r9;
	dm(-5,i6)=r14;
	dm(-4,i6)=r15;
	r2=m3;
	dm(-3,i6)=r2;
	r2=i5;
	dm(-2,i6)=r2;
	r0=ASHIFT r12 by -1;
	r2=0;
	
	/* Check for 0 value of the loop count */
	r0=r0+r2;
	if eq jump exit_loop_Fix2Float;
	r2=2;
	r0=r0-1, m4=r2;
	r0=r0-1,m3=r2;
	i4=r8;
	i5=r4;
	r14=dm(1,i6);
	s14=r14;
	
	bit set mode1 BITM_REGF_MODE1_PEYEN;
	nop; nop;
	r1=FLOAT_SCALE;
	r9=BIT_SHIFT;
	r15=0;
	
	r14 = r14+r15,r2=dm(i5,m4);

	if ne r15=r9;
	r4=lshift r2 by r15;
	f8= FLOAT r4 BY r1,r2=dm(i5,m4);
		
	lcntr=r0, do (pc,CopyFix2Float_loop_end) until lce;
	r4=lshift r2 by r15, dm(i4,m3)=r8;
CopyFix2Float_loop_end:
	f8= FLOAT r4 BY r1,r2=dm(i5,m4);

	r4=lshift r2 by r15, dm(i4,m3)=r8;
	f8= FLOAT r4 BY r1;
	dm(i4,m3)=r8;
	
exit_loop_Fix2Float:	
	bit clr mode1 BITM_REGF_MODE1_PEYEN;
	nop; nop;
	r9=dm(-6,i6);
	r14=dm(-5,i6);
	r15=dm(-4,i6);
	m3=dm(-3,i6);
	i5=dm(-2,i6);
	i12=dm(m7,i6);
	jump (m14,i12) (db); rframe; nop;
	
CopyFix2Float..end:


.section/pm/DOUBLE32 ss_fw_code_fast;
CopyFloat2Fix.:

	modify(i7,-7)(nw);
	dm(-6,i6)=r9;
	dm(-5,i6)=r14;
	dm(-4,i6)=r15;
	r2=m3;
	dm(-3,i6)=r2;
	r2=i5;
	dm(-2,i6)=r2;
	r0=0;
	r2= ASHIFT r12 by -1;
	
	/* Check for 0 value of the loop count */	
	r2=r2+r0;
	if eq jump exit_loop_Float2Fix;	
	
	m4=2;
	i4=r8;
	r12=r2-1, i5=r4;
	m3=2;
	r14=dm(1,i6);
	s14=r14;
	bit set mode1 BITM_REGF_MODE1_PEYEN;
	nop; nop;
	r1=TRUNC_SCALE;
	b12 = r10;
	r10=MAX_VALUE_24BIT;
	
	r9=BIT_SHIFT;
	r15=0;
	r14 = r14+r15,r8=dm(i5,m4);
	
	if eq r15=r9;
	
	
	lcntr=r12, do (pc,CopyFloat2Fix_loop_end) until lce;
	r2=trunc f8 by r1;
	r4=clip r2 by r10, r8=dm(i5,m4);
	comp(r4,r2);
	if ne r0=m6;	
	r4 = lshift r4 by r15;
	//r4 = lshift r4 by -1;            /* This must be commented if the SPORT MFD is set to 1 */
CopyFloat2Fix_loop_end:	
 	dm(i4,m3)=r4;	

	r2=trunc f8 by r1;
	r4=clip r2 by r10;
	comp(r4,r2);
	if ne r0=m6;	
	r4 = lshift r4 by r15;	
	//r4 = lshift r4 by -1;          /* This must be commented if the SPORT MFD is set to 1 */
	dm(i4,m3)=r4;

	r10 = b12;
exit_loop_Float2Fix:	
	bit clr mode1 BITM_REGF_MODE1_PEYEN;
	nop; nop;	
	r9=dm(-6,i6);
	r14=dm(-5,i6);
	r15=dm(-4,i6);
	m3=dm(-3,i6);
	i5=dm(-2,i6);
	i12=dm(m7,i6);
	jump (m14,i12) (db); rframe; nop;
		
CopyFloat2Fix..end:

