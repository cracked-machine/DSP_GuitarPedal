/*
 *  	sine_lookup_table.hpp
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

#ifndef SINE_LOOKUP_TABLE_HPP_
#define SINE_LOOKUP_TABLE_HPP_

#include <array>

std::array<uint32_t, 64> sine_lut {

	0x80,0x8c,0x98,0xa5,0xb0,0xbc,0xc6,0xd0,
	0xda,0xe2,0xea,0xf0,0xf5,0xfa,0xfd,0xfe,
	0xff,0xfe,0xfd,0xfa,0xf5,0xf0,0xea,0xe2,
	0xda,0xd0,0xc6,0xbc,0xb0,0xa5,0x98,0x8c,
	0x80,0x73,0x67,0x5a,0x4f,0x43,0x39,0x2f,
	0x25,0x1d,0x15,0xf,0xa,0x5,0x2,0x1,
	0x0,0x1,0x2,0x5,0xa,0xf,0x15,0x1d,
	0x25,0x2f,0x39,0x43,0x4f,0x5a,0x67,0x73
};



#endif /* SINE_LOOKUP_TABLE_HPP_ */