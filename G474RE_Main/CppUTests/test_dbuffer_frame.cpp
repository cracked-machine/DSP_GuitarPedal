/*
 *  	test_dbuffer_frame.cpp
 *
 *  	Created on: Apr 3, 2021
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

TEST_GROUP(DbufferFrameGroup)
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

TEST(DbufferFrameGroup, DbufferFrameSwapPass)
{
	const size_t dsp_buf_size = 8;

	double_buffer<uint16_t, dsp_buf_size> test_dbuf;

	DBufFrame current_frame = test_dbuf.get_current_buf_frame();

	DBufFrame swapped_frame = test_dbuf.swap_current_buf_frame();

	CHECK_FALSE(current_frame == swapped_frame);	// pass

	swapped_frame = test_dbuf.swap_current_buf_frame();

	CHECK(current_frame == swapped_frame);			// pass
}

