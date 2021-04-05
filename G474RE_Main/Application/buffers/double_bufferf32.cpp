/*
 *  	double_bufferf32.cpp
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

#include "double_bufferf32.hpp"


double_bufferf32::double_bufferf32()
{
	_rxBuf = &_bufA;
	_txBuf = &_bufB;
	isSwappedBuffers = false;
}

float* double_bufferf32::get_rxBuf()
{
	return _rxBuf;
}

float* double_bufferf32::get_txBuf()
{
	return _txBuf;
}

void double_bufferf32::swap()
{
	// make sure we can't go above maximum STM32 DAC output
	if(*_rxBuf > CLAMP_UL)
		*_rxBuf = CLAMP_UL;

	switch(isSwappedBuffers)
	{
		case true:
			_rxBuf = &_bufA;
			_txBuf = &_bufB;
			isSwappedBuffers = false;
			break;

		case false:
			_rxBuf = &_bufB;
			_txBuf = &_bufA;
			isSwappedBuffers = true;
			break;
	}
}


