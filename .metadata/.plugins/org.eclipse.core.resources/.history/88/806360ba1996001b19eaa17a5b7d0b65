/*
 *  	test.h
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

#ifndef TEST_H_
#define TEST_H_


#include <audio_buffer_block.hpp>
#include <audio_buffer.hpp>

#include <arm_math.h>




class test {
public:
	test();
	virtual ~test();

	audiobuffer_u32 	abuf_u32;
	audiobuffer_f32 	abuf_f32;
	audiobuffer_q31 	abuf_q31;

	uint32_t* 				rxBuf_u32;
	float*					rxBuf_f32;
	q31_t*					rxBuf_q31;

	audiobufferblock_u32 	abufb_u32;
	audiobufferblock_f32 	abufb_f32;
	audiobufferblock_q31 	abufb_q31;

	std::array<uint32_t, bufferblocksize> *rxBufb_u32;
	std::array<float, bufferblocksize> *rxBufb_f32;
	std::array<q31_t, bufferblocksize> *rxBufb_q31;

};



#endif /* TEST_H_ */
