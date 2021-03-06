/*
 *  	fir_manager.hpp
 *
 *  	Created on: 6 Apr 2021
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

#ifndef FIR_MANAGER_HPP_
#define FIR_MANAGER_HPP_

// STM HAL Framework
#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_tim.h"
#include "stm32g4xx_hal_tim_ex.h"
#include "stm32g4xx_hal_dac.h"
#include "stm32g4xx_hal_dac_ex.h"

// CMSIS DSP
#include <arm_math.h>

#include <array>

template <class T, class D>
class fir_manager
{
public:
	fir_manager(T pTimer, D pDac)
	{
		theTimer = pTimer;
		theDac = pDac;

		arm_fir_init_f32(	&theFir, NUM_TAPS, (float32_t *)&lpf_fir_coeffs_1khz_f32, (float32_t *)theState.data(),	BLOCK_SIZE);

		lut_count = 0;
		sine_lut_index = 0;
		lut_index = 0;
	}

	void start();
	void update();


private:

	static const size_t BLOCK_SIZE = 1;
	static const size_t NUM_TAPS = 55;


	T theTimer;
	D theDac;

	float32_t input;
	float32_t output;
	uint32_t dma_output;

	// LPF FIR data for fc=1(KHz) fs=48 N=55
	std::array<float32_t, NUM_TAPS> lpf_fir_coeffs_1khz_f32 { -0.000324f, -0.000208f, -0.000072f, 0.000119f, 0.000403f, 0.000822f, 0.001417f, 0.002225f, 0.003281f, 0.004611f, 0.006232f, 0.008153f, 0.010369f, 0.012863f, 0.015606f, 0.018557f, 0.021663f, 0.024861f, 0.028083f, 0.031251f, 0.034287f, 0.037113f, 0.039654f, 0.041838f, 0.043606f, 0.044906f, 0.045702f, 0.045970f, 0.045702f, 0.044906f, 0.043606f, 0.041838f, 0.039654f, 0.037113f, 0.034287f, 0.031251f, 0.028083f, 0.024861f, 0.021663f, 0.018557f, 0.015606f, 0.012863f, 0.010369f, 0.008153f, 0.006232f, 0.004611f, 0.003281f, 0.002225f, 0.001417f, 0.000822f, 0.000403f, 0.000119f, -0.000072f, -0.000208f, -0.000324f };

	arm_fir_instance_f32 theFir;
	std::array<float32_t, BLOCK_SIZE + (NUM_TAPS - 1)> theState;

	size_t lut_count;
	size_t sine_lut_index;
	size_t lut_index;

	static const size_t LUT_SIZE = 64;
	std::array<uint32_t,LUT_SIZE> test_tri_stl {

		128,256,384,512,640,768,896,1024,
		1152,1280,1408,1536,1664,1792,1920,2048,
		2175,2303,2431,2559,2687,2815,2943,3071,
		3199,3327,3455,3583,3711,3839,3967,4095,
		3967,3839,3711,3583,3455,3327,3199,3071,
		2943,2815,2687,2559,2431,2303,2175,2048,
		1920,1792,1664,1536,1408,1280,1152,1024,
		896,768,640,512,384,256,128,0

	};

};


template <class T, class D>
void fir_manager<T, D>::start()
{
	HAL_DAC_Start_DMA(&theDac, DAC_CHANNEL_1, (uint32_t*)dma_output, 1, DAC_ALIGN_12B_R);
	HAL_TIM_Base_Start_IT(&theTimer);

}

template <class T, class D>
void fir_manager<T, D>::update()
{
	// increments the lookup table index
	lut_index = lut_count & ( test_tri_stl.size() - 1 );

	//data_point[0] = test_tri[lut_index];

	float input = (float32_t)test_tri_stl[lut_index];

	arm_fir_f32(&theFir, &input, &output, BLOCK_SIZE);

	dma_output = (uint32_t)output;

	lut_count++;
}

#endif /* FIR_MANAGER_HPP_ */
