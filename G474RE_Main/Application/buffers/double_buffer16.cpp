/*
 *  	double_buffer16.cpp
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

#include "double_buffer16.hpp"

double_buffer16::double_buffer16()
{
	isSwappedBuffers = false;
}

uint16_t* double_buffer16::get_rxBuf()
{
	return _rxBuf.data();
}

uint16_t* double_buffer16::get_txBuf()
{
	return _txBuf.data();
}

void double_buffer16::get_rxBufFrame(uint32_t* left_sample,
								uint32_t* right_sample)
{

	switch(isSwappedBuffers)
	{
		case false:

			*left_sample = (_rxBuf[0] << 16) | _rxBuf[1];
			*right_sample = (_rxBuf[2] << 16) | _rxBuf[3];

			break;

		case true:

			*left_sample = (_rxBuf[4] << 16) | _rxBuf[5];
			*right_sample = (_rxBuf[6] << 16) | _rxBuf[7];

			break;

	}
}
void double_buffer16::get_txBufFrame(	uint32_t* left_sample,
											uint32_t* right_sample)
{
	switch(isSwappedBuffers)
	{
	case false:

		*left_sample = (_txBuf[0] << 16) | _txBuf[1];
		*right_sample = (_txBuf[2] << 16) | _txBuf[3];

		break;

	case true:

		*left_sample = (_txBuf[4] << 16) | _txBuf[5];
		*right_sample = (_txBuf[6] << 16) | _txBuf[7];

		break;
	}
}

void double_buffer16::swap()
{
	switch(isSwappedBuffers)
	{
		case true:

			isSwappedBuffers = false;
			break;

		case false:

			isSwappedBuffers = true;
			break;
	}
}
