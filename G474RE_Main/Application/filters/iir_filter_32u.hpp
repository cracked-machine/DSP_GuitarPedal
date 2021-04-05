/*
 *  	iir_filter_32u.hpp
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

#ifndef IIR_FILTER_32U_HPP_
#define IIR_FILTER_32U_HPP_

#include <stdint.h>

class iir_filter_32u
{

public:

	iir_filter_32u() : in_z1(0.0f), in_z2(0.0f), out_z1(0.0f), out_z2(0.0f)
	{

	}
	void process(float *input, float *output);


private:
	//300Hz high-pass, 96k
	/*
	float a0 = 0.9862117951198142f;
	float a1 = -1.9724235902396283f;
	float a2 = 0.9862117951198142f;
	float b1 = -1.972233470205696f;
	float b2 = 0.9726137102735608f;
	*/

	// 10KHz low-pass, 44.1KHz
/*	float a0 = 0.2513790015131591;
	float a1 = 0.5027580030263182;
	float a2 = 0.2513790015131591;
	float b1 = -0.17124071441396285;
	float b2 = 0.1767567204665992;
*/
	// 500Hz low-pass, 96KHz
	float a0 = 0.00025668462720233523;
	float a1 = 0.0005133692544046705;
	float a2 = 0.00025668462720233523;
	float b1 = -1.916632007760119;
	float b2 = 0.9176587462689284;

	float in_z1;
	float in_z2;
	float out_z1;
	float out_z2;

	float input;
	float output;
};



#endif /* IIR_FILTER_32U_HPP_ */