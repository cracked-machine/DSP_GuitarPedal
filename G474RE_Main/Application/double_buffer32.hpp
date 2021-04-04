/*
 *  	double_buffer32.hpp
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

#ifndef DOUBLE_BUFFER32_HPP_
#define DOUBLE_BUFFER32_HPP_

#include <stdint.h>


// this is a ping pong buffer swaps
// one 32bit word data item at a time

// assign get_txBuf() to your DMA destination
// assign get_rxBuf() to your DMA source

// process the get_rxBuf() data
// use swap() to send new rx to DMA dest and replace old tx with DMA source.

class double_buffer32
{
public:

	double_buffer32();

	uint32_t* get_rxBuf();
	uint32_t* get_txBuf();

	void swap();

private:

	// upper limit for STM32 DAC
	const uint16_t CLAMP_UL = 4095;

	bool isSwappedBuffers;

	uint32_t _bufA;
	uint32_t _bufB;

	uint32_t* _rxBuf;
	uint32_t* _txBuf;

};


#endif /* DOUBLE_BUFFER32_HPP_ */
