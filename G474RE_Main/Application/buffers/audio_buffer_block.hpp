/*
 *  	audio_buffer_block.hpp
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

#ifndef audio_buffer_block_HPP_
#define audio_buffer_block_HPP_

#include <stdint.h>
#include <stdio.h>
#include <array>
#include <arm_math.h>

template <class T, size_t size>
class audio_buffer_block
{
public:

	explicit audio_buffer_block()
	{
		_rxBuf = &_bufA;
		_txBuf = &_bufB;
		isSwappedBuffers = false;
	}

	std::array<T, size>* get_rxBuf();
	std::array<T, size>* get_txBuf();

	void swap();

private:

	// upper limit for STM32 DAC
	const size_t CLAMP_UL = 4095;

	bool isSwappedBuffers;

	std::array<T, size> _bufA;
	std::array<T, size> _bufB;

	std::array<T, size>* _rxBuf;
	std::array<T, size>* _txBuf;

};

template <class T, size_t size>
std::array<T, size>* audio_buffer_block<T, size>::get_rxBuf()
{
	return _rxBuf;
}

template <class T, size_t size>
std::array<T, size>* audio_buffer_block<T, size>::get_txBuf()
{
	return _txBuf;
}

template <class T, size_t size>
void audio_buffer_block<T, size>::swap()
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

const size_t bufferblocksize = 4;
typedef audio_buffer_block<uint32_t, bufferblocksize> audiobufferblock_u32;
typedef audio_buffer_block<float, bufferblocksize> 	audiobufferblock_f32;
typedef audio_buffer_block<q31_t, bufferblocksize> 	audiobufferblock_q31;

#endif /* audio_buffer_block_HPP_ */
