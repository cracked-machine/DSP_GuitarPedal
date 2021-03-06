/*
 *  	test_audio_buffer.cpp
 *
 *  	Created on: 5 Apr 2021
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

#include "CppUTest/TestHarness.h"
#include <audio_buffer.hpp>
#include <array>

// https://www.daycounter.com/Calculators/Triangle-Wave-Generator-Calculator.phtml
// NumPoints=64, MaxAmpl=4095, NumPerRow=8, Dec
std::array<uint32_t, 64> test_tri_lut_u32 {

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
std::array<q31_t, 64> test_tri_lut_q31 {

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
std::array<float, 64> test_tri_lut_f32 {

	128.0,  256.0,  384.0,  512.0,  640.0,  768.0,  896.0,  1024.0,
	1152.0, 1280.0, 1408.0, 1536.0, 1664.0, 1792.0, 1920.0, 2048.0,
	2175.0, 2303.0, 2431.0, 2559.0, 2687.0, 2815.0, 2943.0, 3071.0,
	3199.0, 3327.0, 3455.0, 3583.0, 3711.0, 3839.0, 3967.0, 4095.0,
	3967.0, 3839.0, 3711.0, 3583.0, 3455.0, 3327.0, 3199.0, 3071.0,
	2943.0, 2815.0, 2687.0, 2559.0, 2431.0, 2303.0, 2175.0, 2048.0,
	1920.0, 1792.0, 1664.0, 1536.0, 1408.0, 1280.0, 1152.0, 1024.0,
	896.0,  768.0,  640.0,  512.0,  384.0,  256.0,  128.0,  0.0

};

TEST_GROUP(AudioBufferInputOutputGroup)
{
};

TEST(AudioBufferInputOutputGroup, AudioBufferInputOutputUint32)
{

	bool result = true;
	size_t lut_count = 0;
	size_t lut_index = 0;

	audiobuffer_u32 buf;
	uint32_t* rxBuf = buf.get_rxBuf();

	while(lut_count < (test_tri_lut_u32.size()))
	{
		// increment the LUT position (circular)
		lut_index = lut_count & ( test_tri_lut_u32.size() - 1 );

		// reset the buffer pointers back to default buffer allocation
		buf.reset();

		// copy LUT value into rxbuf pointer (bufferA)
		*rxBuf = test_tri_lut_u32[lut_index];

		// swap the buffer pointers buffer allocation
		buf.swap();

		lut_count++;

		if(test_tri_lut_u32[lut_index] != *(buf.get_txBuf()))
			result = false;

	}

    CHECK(result);
}
/*
TEST(AudioBufferInputOutputGroup, AudioBufferInputOutputFloat32)
{

	bool result = true;
	size_t lut_count = 0;
	size_t lut_index = 0;

	audiobuffer_f32 buf;
	float* rxBuf;

	while(lut_count < (test_tri_lut_f32.size()))
	{
		// increment the LUT position (circular)
		lut_index = lut_count & ( test_tri_lut_f32.size() - 1 );

		// reset the buffer pointers back to default buffer allocation
		buf.reset();

		// copy LUT value into rxbuf pointer (bufferA)
		*rxBuf = test_tri_lut_f32[lut_index];

		// swap rxBuf and txBuf pointer
		buf.swap();

		//let DMA read txBuf

		lut_count++;

		if(test_tri_lut_f32[lut_index] != *(buf.get_txBuf()))
			result = false;
	}

    CHECK(result);
}

TEST(AudioBufferInputOutputGroup, AudioBufferInputOutputQ32)
{

	bool result = true;
	size_t lut_count = 0;
	size_t lut_index = 0;

	audiobuffer_q31 buf;
	q31_t* rxBuf;

	while(lut_count < (test_tri_lut_q31.size()))
	{
		// increment the LUT position (circular)
		lut_index = lut_count & ( test_tri_lut_q31.size() - 1 );

		// reset the buffer pointers back to default buffer allocation
		buf.reset();

		// copy LUT value into rxbuf pointer (bufferA)
		*rxBuf = test_tri_lut_q31[lut_index];

		// swap rxBuf and txBuf pointer
		buf.swap();

		//let DMA read txBuf

		lut_count++;

		if(test_tri_lut_q31[lut_index] != *(buf.get_txBuf()))
			result = false;
	}

    CHECK(result);
}
*/
