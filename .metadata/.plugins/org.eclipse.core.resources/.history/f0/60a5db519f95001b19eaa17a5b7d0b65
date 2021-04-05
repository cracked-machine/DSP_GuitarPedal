/*
 *  	double_buffer16.hpp
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

#ifndef DOUBLE_BUFFER16_HPP_
#define DOUBLE_BUFFER16_HPP_

#include <stdint.h>
#include <array>

// INIT:
////////
// Call get_rxBuf() to set I2S receive DMA destination.
// RX Buffer is BufferA { L: 2x16bits, R: 2x16bits } and BufferB { L: 2x16bits, R: 2x16bits }

// Call get_txBuf() to set I2S transmit DMA source.
// TX Buffer is BufferA { L: 2x16bits, R: 2x16bits } and BufferB { L: 2x16bits, R: 2x16bits }

// LOOP:
////////
// Call get_rxBufFrame() to receive new sample from BufferA/BufferB,
// Process the sample
// Call get_txBufFrame() to transmit the processed sample to BufferA/BufferB
// Call swap() to switch BufferA/BufferB

class double_buffer16
{
public:

	double_buffer16();

	uint16_t* get_rxBuf();
	uint16_t* get_txBuf();

	void get_rxBufFrame(uint32_t* left_sample, uint32_t* right_sample);
	void get_txBufFrame(uint32_t* left_sample, uint32_t* right_sample);

	void swap();

private:

	bool isSwappedBuffers;



	std::array<uint16_t,8> _rxBuf;
	std::array<uint16_t,8> _txBuf;

};




#endif /* DOUBLE_BUFFER16_HPP_ */
