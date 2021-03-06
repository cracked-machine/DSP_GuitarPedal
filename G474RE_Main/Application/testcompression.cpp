/*
 *  	testcompression.cpp
 *
 *  	Created on: Apr 7, 2021
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

/*
 *
 * Base on this implementation - https://github.com/YetAnotherElectronicsChannel/STM32_DSP_COMPRESSOR
 *
 */

#include <stdint.h>
#include <math.h>

// 0 = no gain reduction
// 1 = attack
// 2 = gain reduction
// 3 = release
enum CompStates {S_NoOperation, S_Attack, S_GainReduction, S_Release };
enum CompStates State = S_NoOperation;



int32_t Attack, Release, Hold, TimeOut;
float gainreduce, gain_step_attack, gain_step_release, gain, threshold;

#ifdef __cplusplus
	extern "C"
	{
#endif

		void initCompression()
		{
			// 1 sample = 1/96kHz = ~10us
			//Attack -> 30 ms -> 3000
			//Release -> 20 ms -> 2000
			//Hold -> 10ms -> 1000
			Attack = 3000;
			Release = 2000;
			Hold = 1000;

			//threshold -20dB below limit -> 0.1 * 2^31
			threshold = 0.3f * 2147483648;

			//compression ratio: 6:1 -> -6dB = 0.5
			gainreduce = 0.5f;

			gain_step_attack = (1.0f - gainreduce) / Attack;
			gain_step_release = (1.0f - gainreduce) / Release;

			//initial gain = 1.0 -> no compression
			gain = 1.5f;
		}

		float doCompression (float inSample)
		{

			float inSampleF = (float)inSample;

				if (fabs(inSampleF) > threshold) {
					if (gain >=  gainreduce) {
						if (State==S_NoOperation) {
							State=S_Attack;
							TimeOut = Attack;
						}
						else if (State==S_Release) {
							State=S_Attack;
							TimeOut = Attack;
						}
					}
					if (State==S_GainReduction) TimeOut = Hold;

				}

				if (fabs(inSampleF) < threshold && gain <= 1.0f) {
					if (TimeOut==0 && State==S_GainReduction) {
						State=S_Release;
						TimeOut = Release;
					}
				}
				switch (State) {

					case S_Attack:
						if (TimeOut>0 && gain > gainreduce) {
							gain -= gain_step_attack;
							TimeOut--;
						}
						else {
							State=S_GainReduction;
							TimeOut = Hold;
						}
						break;


					case S_GainReduction:
						if (TimeOut>0) TimeOut--;
						else {
							State=S_Release;
							TimeOut = Release;
						}
						break;


					case S_Release:
						if (TimeOut>0 && gain<1.0f) {
							TimeOut--;
							gain += gain_step_release;
						}
						else {
							State=S_NoOperation;
						}
						break;

					case S_NoOperation:
						if (gain < 1.0f) gain = 1.0F;
						break;

					default:

						break;

				}




				float outSampleF = inSample*gain;

				return (int) outSampleF;
		}

#ifdef __cplusplus
	}
#endif




