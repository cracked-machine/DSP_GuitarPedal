/*
 *  	test.cpp
 *
 *  	Created on: 4 Apr 2021
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

#include <test.h>

test::test() {

	rxBuf_u32 = abuf_u32.get_rxBuf();
	rxBuf_f32 = abuf_f32.get_rxBuf();
	rxBuf_q31 = abuf_q31.get_rxBuf();

	rxBufb_u32 = abufb_u32.get_rxBuf();
	size_t tmp = abufb_u32.get_rxBuf()->size();

	rxBufb_f32 = abufb_f32.get_rxBuf();
	tmp = abufb_u32.get_rxBuf()->size();

	rxBufb_q31 = abufb_q31.get_rxBuf();
	tmp = abufb_u32.get_rxBuf()->size();

	tmp=0;
}

test::~test() {
	// TODO Auto-generated destructor stub
}
