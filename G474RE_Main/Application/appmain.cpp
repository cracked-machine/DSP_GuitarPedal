/*
 * 		appmain.cpp
 *
 *  	Created on: Apr 2, 2021
 *      Author: Chris Sutton
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

// STM HAL Framework
#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_tim.h"
#include "stm32g4xx_hal_tim_ex.h"
#include "stm32g4xx_hal_dac.h"
#include "stm32g4xx_hal_dac_ex.h"
#include "stm32g4xx_hal_gpio.h"
#include "stm32g4xx_hal_gpio_ex.h"

// STM32Cube generated HAL init code
#include "tim.h"
#include "dac.h"
#include "gpio.h"

// C++ STL
#include <array>
#include <iostream>

// CMSIS DSP
#include <arm_math.h>

// DSP functions
#include <testdistortion.hpp>
#include <testfilter.hpp>
#include <testreverb.hpp>
#include <testcompression.hpp>

// set by HAL_TIM_PeriodElapsedCallback to signal work to be done
bool isTimer6Callback = false;
bool isTimer7Callback = false;

// enable_passthru overrides the other FX
bool enable_passthru = false;
// if enable_passthru is false, at *least one* of the below must be true
bool enable_compression = false;
bool enable_pre_distortion = false;
bool enable_filter = true;
bool enable_post_distortion = false;
bool enable_post_reverb = false;
bool enable_pre_reverb_gain = false;


// convenience gain attribute
#define PRE_REVERB_GAIN 0.4

///// TEST DATA
#define LUT_SIZE 	64
#define BLOCK_SIZE	LUT_SIZE / 1

// https://www.daycounter.com/Calculators/Sine-Generator-Calculator.phtml
// NumPoints=64, MaxAmpl=4095, NumPerRow=8, Dec
std::array<uint32_t, 64> input_sine_sample_u32 {

	2048,2248,2447,2642,2831,3013,3185,3346,
	3495,3630,3750,3853,3939,4007,4056,4085,
	4095,4085,4056,4007,3939,3853,3750,3630,
	3495,3346,3185,3013,2831,2642,2447,2248,
	2048,1847,1648,1453,1264,1082,910,749,
	600,465,345,242,156,88,39,10,
	0,10,39,88,156,242,345,465,
	600,749,910,1082,1264,1453,1648,1847
};

// https://www.daycounter.com/Calculators/Triangle-Wave-Generator-Calculator.phtml
// NumPoints=64, MaxAmpl=4095, NumPerRow=8, Dec
std::array<uint32_t,LUT_SIZE> input_triangle_sample_u32 {

	128,256,384,512,640,768,896,1024,
	1152,1280,1408,1536,1664,1792,1920,2048,
	2175,2303,2431,2559,2687,2815,2943,3071,
	3199,3327,3455,3583,3711,3839,3967,4095,
	3967,3839,3711,3583,3455,3327,3199,3071,
	2943,2815,2687,2559,2431,2303,2175,2048,
	1920,1792,1664,1536,1408,1280,1152,1024,
	896,768,640,512,384,256,128,0

};

// https://www.daycounter.com/Calculators/Triangle-Wave-Generator-Calculator.phtml
// NumPoints=64, MaxAmpl=4095, NumPerRow=8, Dec
std::array<uint32_t,LUT_SIZE> input_square_sample_u32 {

	4095,4095,4095,4095,4095,4095,4095,4095,
	4095,4095,4095,4095,4095,4095,4095,4095,
	4095,4095,4095,4095,4095,4095,4095,4095,
	4095,4095,4095,4095,4095,4095,4095,4095,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0

};

// should be "input_sine_sample_u32" or "input_triangle_sample"_u32 or "input_unit_sample_u32"
#define TEST_SAMPLE input_triangle_sample_u32

size_t input_data_count = 0;
size_t input_data_index = 0;

// used to hold the data whilst it is converted between uint32_t and float32_t
std::array<float32_t, BLOCK_SIZE>	input_f32;
std::array<float32_t, BLOCK_SIZE> 	output_f32;
std::array<uint32_t, BLOCK_SIZE> 	output_u32;


// C++ STL
#include <array>


#ifdef __cplusplus
	extern "C"
	{
#endif

void processBlock();
void doBlinky();

void appmain()
{
	initReverb();
	initCompression();
	initFilter();

	// enable dac and its trigger (tim6)
	HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, output_u32.data(), BLOCK_SIZE, DAC_ALIGN_12B_R);
	TIM6->PSC = 0;
	TIM6->ARR = 511;
	HAL_TIM_Base_Start_IT(&htim6);

	// enable timer for blinky
	TIM7->PSC = 8095;
	TIM7->ARR = 8095;
	HAL_TIM_Base_Start_IT(&htim7);


	while(1)
	{
		if(isTimer6Callback)
		{
			processBlock();
			isTimer6Callback = false;
		}
		if(isTimer7Callback)
		{
			doBlinky();
			isTimer7Callback = false;
		}
	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// Timer callback for DAC trigger
	if(htim->Instance == TIM6)
	{
		isTimer6Callback = true;
	}

	// Timer callback for blinky
	if(htim->Instance == TIM7)
	{
		isTimer7Callback = true;
	}

}

void processBlock()
{

	// wrap the lut_index
	input_data_index = input_data_count & ( TEST_SAMPLE.size() - 1 );

	// convert to CMSIS DSP friendly 32bit floating point format
	// Note we only increment within current DISTORTION_BLOCK_SIZE
	for(size_t i = 0; i < BLOCK_SIZE; i++)
		input_f32[i] = (float32_t) TEST_SAMPLE[ input_data_index + i ];

	if(enable_passthru)
	{
		// just copy input to output and skip below FX
		output_f32 = input_f32;
	}
	else
	{
		if(enable_pre_distortion)
		{
			// process each data sample with distortion
			for(size_t i = 0; i < BLOCK_SIZE; i++)
				input_f32[i] = doDistortion(input_f32[i]);
		}

		if(enable_filter)
		{
			// process block with filter
			doFilter(input_f32.data(), output_f32.data(), BLOCK_SIZE);
		}
		else
		{
			// no filter
			output_f32 = input_f32;
		}

		if(enable_compression)
		{
			// process each data sample with compression
			for(size_t i = 0; i < BLOCK_SIZE; i++)
				output_f32[i] = doCompression(output_f32[i]);
		}

		if(enable_post_distortion)
		{
			// process each data sample with distortion
			for(size_t i = 0; i < BLOCK_SIZE; i++)
				output_f32[i] = doDistortion(output_f32[i]);
		}

		if(enable_pre_reverb_gain)
		{
			// process each data sample with gain
			for(size_t i = 0; i < BLOCK_SIZE; i++)
				output_f32[i] = output_f32[i] * PRE_REVERB_GAIN;
		}

		if(enable_post_reverb)
		{
			// process each data sample with reverb
			for(size_t i = 0; i < BLOCK_SIZE; i++)
				output_f32[i] = doReverb(output_f32[i]);
		}


	}


	// convert back to DAC friendly 32bit unsigned int format
	for(size_t i = 0; i < BLOCK_SIZE; i++)
		output_u32[i] = (uint32_t)output_f32[i];

	// increment the lookup table by entire block
	input_data_count = input_data_count + BLOCK_SIZE;

}

void doBlinky()
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}



#ifdef __cplusplus
	}
#endif

