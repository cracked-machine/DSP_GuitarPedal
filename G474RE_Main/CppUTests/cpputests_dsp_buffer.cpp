/*
 *  	more_tests.cpp
 *
 *  	Created on: Apr 2, 2021
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

#include "dsp_buffer.hpp"


TEST_GROUP(DspBufferGroup)
{
   void setup()
   {
	  // Init stuff
   }

   void teardown()
   {
	  // Uninit stuff
   }
};
TEST(DspBufferGroup, DspBuffer_set24BitSample_PositionZero)  // pass
{
	const size_t size = 10;
	dsp_double_buffer<uint16_t, size> buf;
	uint32_t left_sample = 0;
	uint32_t right_sample = 0;
	CHECK_FALSE(buf.set24BitSample(&left_sample, &right_sample, 0));
}

TEST(DspBufferGroup, DspBuffer_set24BitSample_PositionHalfSize)  // pass
{
	const size_t size = 10;
	dsp_double_buffer<uint16_t, size> buf;
	uint32_t left_sample = 0;
	uint32_t right_sample = 0;
	CHECK_FALSE(buf.set24BitSample(&left_sample, &right_sample, size / 2));
}

TEST(DspBufferGroup, DspBuffer_set24BitSample_PositionAtSize)  // fail
{
	const size_t size = 10;
	dsp_double_buffer<uint16_t, size> buf;
	uint32_t left_sample = 0;
	uint32_t right_sample = 0;
	CHECK_TRUE(buf.set24BitSample(&left_sample, &right_sample, size));
}

TEST(DspBufferGroup, DspBuffer_set24BitSample_PositionOverSize)  // fail
{
	const size_t size = 10;
	dsp_double_buffer<uint16_t, size> buf;
	uint32_t left_sample = 0;
	uint32_t right_sample = 0;
	CHECK_TRUE(buf.set24BitSample(&left_sample, &right_sample, size+1));
}
