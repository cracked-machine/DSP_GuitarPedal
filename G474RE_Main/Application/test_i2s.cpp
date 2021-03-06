/*
 *  	test_i2s.cpp
 *
 *  	Created on: Apr 7, 2021
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

#include "test_i2s.hpp"

#include <stm32g4xx_hal.h>
#include <stm32g4xx_hal_i2s.h>

#include "i2s.h"

#include <array>


// https://www.daycounter.com/Calculators/Sine-Generator-Calculator.phtml
// NumPoints=64, MaxAmpl=4095, NumPerRow=8, Dec
std::array<uint16_t, 64> input_sine_sample_i2s {

	2048, 2248, 2447, 2642, 2831, 3013, 3185, 3346,
	3495, 3630, 3750, 3853, 3939, 4007, 4056, 4085,
	4095, 4085, 4056, 4007, 3939, 3853, 3750, 3630,
	3495, 3346, 3185, 3013, 2831, 2642, 2447, 2248,
	2048, 1847, 1648, 1453, 1264, 1082, 910, 749,
	600, 465, 345, 242, 156, 88, 39, 10,
	0, 10, 39, 88, 156, 242, 345, 465,
	600, 749, 910, 1082, 1264, 1453, 1648, 1847
};

// https://www.daycounter.com/Calculators/Triangle-Wave-Generator-Calculator.phtml
// NumPoints=64, MaxAmpl=4095, NumPerRow=8, Dec
std::array<uint16_t,64> input_triangle_sample_i2s {

	128,256,384,512,640,768,896,1024,
	1152,1280,1408,1536,1664,1792,1920,2048,
	2175,2303,2431,2559,2687,2815,2943,3071,
	3199,3327,3455,3583,3711,3839,3967,4095,
	3967,3839,3711,3583,3455,3327,3199,3071,
	2943,2815,2687,2559,2431,2303,2175,2048,
	1920,1792,1664,1536,1408,1280,1152,1024,
	896,768,640,512,384,256,128,0

};

#define I2S_SAMPLE input_triangle_sample_i2s

std::array<uint16_t, 2> i2s_output;
size_t i2s_count;
size_t i2s_index;

#ifdef __cplusplus
	extern "C"
	{
#endif

void test_i2s()
{

	i2s_count = 0;
	i2s_index = 0;
	HAL_I2S_Transmit_DMA(&hi2s3, i2s_output.data(), 2);

}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{

}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	i2s_index = i2s_count & ( I2S_SAMPLE.size() - 1 );

	i2s_output[0] = I2S_SAMPLE[i2s_index] * 8;
	i2s_output[1] = 0;

	i2s_count++;
}


#ifdef __cplusplus
	}
#endif


