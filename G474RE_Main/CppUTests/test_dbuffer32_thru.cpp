/*
 *  	test_dbuffer32_thru.cpp
 *
 *  	Created on: Apr 4, 2021
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

#include <double_buffer32.hpp>
#include "CppUTest/TestHarness.h"

TEST_GROUP(Dbuffer32ThruGroup)
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

/*
 * 		Dbuffer32Thru
 *
 * 		@Brief		check output == input, after buffer swap.
 * 					Expected result: pass
 */

TEST(Dbuffer32ThruGroup, Dbuffer32ThruSwap)
{
	uint32_t input = 2048;
	double_buffer32 *dbuf32 = new double_buffer32();
	uint32_t *dbuf32Rx = dbuf32->get_rxBuf();

	*dbuf32Rx = input;

	// process the rx buffer data here
	// do nothing

	//swap the rx buffer data out to the tx buffer pointer
	dbuf32->swap();

	uint32_t *output = dbuf32->get_txBuf();


	CHECK(input == *output);
	delete dbuf32;
}

/*
 * 		Dbuffer32ThruAboveUpperThreshold
 *
 * 		@Brief		check upper limit threshold.
 * 					Expected result: pass
 */
TEST(Dbuffer32ThruGroup, Dbuffer32ThruAboveUpperThreshold)
{
	uint32_t input = 4096;

	double_buffer32 *dbuf32 = new double_buffer32();
	uint32_t *dbuf32Rx = dbuf32->get_rxBuf();

	*dbuf32Rx = input;

	// process the rx buffer data here
	// do nothing

	//swap the rx buffer data out to the tx buffer pointer
	dbuf32->swap();

	uint32_t *output = dbuf32->get_txBuf();


	CHECK(4095 == *output);
	delete dbuf32;
}

