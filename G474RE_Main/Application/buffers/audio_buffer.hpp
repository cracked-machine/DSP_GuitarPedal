/*
 *  	audio_buffer.hpp
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

#ifndef AUDIO_BUFFER_HPP_
#define AUDIO_BUFFER_HPP_

#include <stdint.h>
#include <stdio.h>
#include <arm_math.h>

template <class T>
class audio_buffer
{
public:

	explicit audio_buffer()
	{
		_rxBuf = &_bufA;
		_txBuf = &_bufB;
		isSwappedBuffers = false;
	}

	T* get_rxBuf();
	T* get_txBuf();
	void receive_clock_in(T* data_input);
	void transmit_clock_out(T* data_output);
	void transmit_clock_out();

	void reset();
	void swap();

private:

	// upper limit for STM32 DAC
	const size_t CLAMP_UL = 4095;

	bool isSwappedBuffers;

	T _bufA;
	T _bufB;

	T* _rxBuf;
	T* _txBuf;

};

template <class T>
void audio_buffer<T>::receive_clock_in(T* data_input)
{
	// copy data value into rxbuf pointer
	*_rxBuf = *data_input;

	// swap rxBuf and txBuf pointer
	this->swap();
}

template <class T>
void audio_buffer<T>::transmit_clock_out(T* data_output)
{
	// copy value from txBuf pointer
	*data_output = *_txBuf;

	// swap rxBuf and txBuf pointer
	this->swap();


}

template <class T>
void audio_buffer<T>::transmit_clock_out()
{
	// copy value from txBuf pointer
	//*data_output = *_txBuf;

	// swap rxBuf and txBuf pointer
	this->swap();


}

template <class T>
T* audio_buffer<T>::get_rxBuf()
{
	return _rxBuf;
}

template <class T>
T* audio_buffer<T>::get_txBuf()
{
	return _txBuf;
}

template <class T>
void audio_buffer<T>::reset()
{
	_rxBuf = &_bufA;
	_txBuf = &_bufB;
	isSwappedBuffers = false;
}

template <class T>
void audio_buffer<T>::swap()
{
	// make sure we can't go above maximum STM32 DAC output
	if(*_rxBuf > CLAMP_UL)
		*_rxBuf = CLAMP_UL;
/*
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
*/
	_rxBuf = &_bufB;
	_txBuf = &_bufA;
	isSwappedBuffers = true;
}


typedef audio_buffer<uint32_t> 	audiobuffer_u32;
typedef audio_buffer<float> 	audiobuffer_f32;
typedef audio_buffer<q31_t> 	audiobuffer_q31;

#endif /* AUDIO_BUFFER_HPP_ */
