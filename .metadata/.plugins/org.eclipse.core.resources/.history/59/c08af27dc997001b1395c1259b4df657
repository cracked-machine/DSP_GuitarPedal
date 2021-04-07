/*
 *  	testfilter_main.cpp
 *
 *  	Created on: Apr 6, 2021
 *		
 * 		MIT License
 *
 * 		Copyright (c) [2021] [Chris Sutton]
 *
 * 		Permission is hereby granted, free of charge, to any person obtaining a copy
 * 		of this software and associated documentation files (the "Software"), to deal
 * 		in the Software without restriction, including without limitation the rights
 * 		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * 		copies of the Software, and to permit persons to whom the Software is
 * 		furnished to do so, subject to the following conditions:
 *
 * 		The above copyright notice and this permission notice shall be included in all
 * 		copies or substantial portions of the Software.
 *
 * 		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * 		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * 		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * 		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * 		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * 		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * 		SOFTWARE.
 */


#include <testfilter.hpp>

//#define ENABLE_IIR
#define ENABLE_FIR


///// FIR FILTER
	#define FIR_NUM_TAPS 55

	// the FIR filter instance
	arm_fir_instance_f32 s_ch1_f32;

	// LPF FIR coeffcients for fc=1KHz fs=48 N=55
	float32_t lpf_fir_coeffs_1khz_f32[FIR_NUM_TAPS] = {
		-0.000324f, -0.000208f, -0.000072f, 0.000119f, 0.000403f, 0.000822f, 0.001417f, 0.002225f, 0.003281f, 0.004611f, 0.006232f, 0.008153f, 0.010369f, 0.012863f, 0.015606f, 0.018557f, 0.021663f, 0.024861f, 0.028083f, 0.031251f, 0.034287f, 0.037113f, 0.039654f, 0.041838f, 0.043606f, 0.044906f, 0.045702f, 0.045970f, 0.045702f, 0.044906f, 0.043606f, 0.041838f, 0.039654f, 0.037113f, 0.034287f, 0.031251f, 0.028083f, 0.024861f, 0.021663f, 0.018557f, 0.015606f, 0.012863f, 0.010369f, 0.008153f, 0.006232f, 0.004611f, 0.003281f, 0.002225f, 0.001417f, 0.000822f, 0.000403f, 0.000119f, -0.000072f, -0.000208f, -0.000324f
	};

	// fir state variables
	static float32_t firState[64 + (FIR_NUM_TAPS - 1)];
/////

///// IIR FILTER
	#define IIR_NUM_TAPS 1

	// IIR filter instance
	arm_biquad_casd_df1_inst_f32 iir_inst_f32;

	// https://www.earlevel.com/main/2013/10/13/biquad-calculator-v2/
	// Earlevel uses difference equation so b0/b1 have been negated to match positive feedback of CMSIS equation

	// LPF IIR coefficients for fc=1KHz fs=44.1KHz Q=0.707 G=6db
	const float32_t lpf_iir_coeffs_1khz_f32[] = {	0.00460399444634034,		//a0
													0.00920798889268068,		//a1
													0.00460399444634034,		//a2
													1.7990948352036205,			//b0
													-0.8175108129889816 };		//b1

	// LPF IIR coefficients for fc=500Hz fs=44.1KHz Q=0.707 G=6db
	const float32_t lpf_iir_coeffs_500hz_f32[] = {	0.0012074046354035072,		//a0
													0.0024148092708070144,		//a1
													0.0012074046354035072,		//a2
													1.8993325472756315,			//b0
													-0.9041621658172454 };		//b1

	static float32_t iirState[64 + (IIR_NUM_TAPS - 1)];
/////

#ifdef __cplusplus
	extern "C"
	{
#endif

void initFilter()
{
	arm_biquad_cascade_df1_init_f32(	&iir_inst_f32,
										IIR_NUM_TAPS,
										lpf_iir_coeffs_1khz_f32,
										iirState);

	arm_fir_init_f32(	&s_ch1_f32,
						FIR_NUM_TAPS,
						(float32_t *)&lpf_iir_coeffs_500hz_f32,
						(float32_t *)&firState,
						64);

}


void doFilter(  const float32_t * pSrc, float32_t * pDst, uint32_t blockSize )
{

	// filter type (or no filter)
	#ifdef ENABLE_IIR
		arm_biquad_cascade_df1_f32( &iir_inst_f32, pSrc, pDst, blockSize);
	#endif
	#ifdef ENABLE_FIR
		arm_fir_f32(&s_ch1_f32, pSrc, pDst, blockSize);
	#endif


}


#ifdef __cplusplus
	}
#endif



