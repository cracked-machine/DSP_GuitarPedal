/*
 *  	testreverb.cpp
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
 * Based on this implementation - https://github.com/YetAnotherElectronicsChannel/STM32_DSP_Reverb
 *
 */


//Schroeder delays from 25k->96k interpolated
//*2 delay extension -> not more possible without external ram
#define l_CB0 3460*2
#define l_CB1 2988*2
#define l_CB2 3882*2
#define l_CB3 4312*2
#define l_AP0 480*2
#define l_AP1 161*2
#define l_AP2 46*2

//define wet 0.0 <-> 1.0
float wet = 1.0f;
//define time delay 0.0 <-> 1.0 (max)
float time = 1.0f;

//define pointer limits = delay time
int cf0_lim, cf1_lim, cf2_lim, cf3_lim, ap0_lim, ap1_lim, ap2_lim;

//define buffer for comb- and allpassfilters
float cfbuf0[l_CB0], cfbuf1[l_CB1], cfbuf2[l_CB2], cfbuf3[l_CB3];
float apbuf0[l_AP0], apbuf1[l_AP1], apbuf2[l_AP2];
//feedback defines as of Schroeder
float cf0_g = 0.805f, cf1_g=0.827f, cf2_g=0.783f, cf3_g=0.764f;
float ap0_g = 0.7f, ap1_g = 0.7f, ap2_g = 0.7f;
//buffer-pointer
int cf0_p=0, cf1_p=0, cf2_p=0, cf3_p=0, ap0_p=0, ap1_p=0, ap2_p=0;

#ifdef __cplusplus
	extern "C"
	{
#endif

float Do_Comb0(float inSample) {
	float readback = cfbuf0[cf0_p];
	float tmp = readback*cf0_g + inSample;
	cfbuf0[cf0_p] = tmp;
	cf0_p++;
	if (cf0_p==cf0_lim) cf0_p = 0;
	return readback;
}

float Do_Comb1(float inSample) {
	float readback = cfbuf1[cf1_p];
	float tmp = readback*cf1_g + inSample;
	cfbuf1[cf1_p] = tmp;
	cf1_p++;
	if (cf1_p==cf1_lim) cf1_p = 0;
	return readback;
}
float Do_Comb2(float inSample) {
	float readback = cfbuf2[cf2_p];
	float tmp = readback*cf2_g + inSample;
	cfbuf2[cf2_p] = tmp;
	cf2_p++;
	if (cf2_p==cf2_lim) cf2_p = 0;
	return readback;
}
float Do_Comb3(float inSample) {
	float readback = cfbuf3[cf3_p];
	float tmp = readback*cf3_g + inSample;
	cfbuf3[cf3_p] = tmp;
	cf3_p++;
	if (cf3_p==cf3_lim) cf3_p = 0;
	return readback;
}


float Do_Allpass0(float inSample) {
	float readback = apbuf0[ap0_p];
	readback += (-ap0_g) * inSample;
	float tmp = readback*ap0_g + inSample;
	apbuf0[ap0_p] = tmp;
	ap0_p++;
	if (ap0_p == ap0_lim) ap0_p=0;
	return readback;
}

float Do_Allpass1(float inSample) {
	float readback = apbuf1[ap1_p];
	readback += (-ap1_g) * inSample;
	float tmp = readback*ap1_g + inSample;
	apbuf1[ap1_p] = tmp;
	ap1_p++;
	if (ap1_p == ap1_lim) ap1_p=0;
	return readback;
}
float Do_Allpass2(float inSample) {
	float readback = apbuf2[ap2_p];
	readback += (-ap2_g) * inSample;
	float tmp = readback*ap2_g + inSample;
	apbuf2[ap2_p] = tmp;
	ap2_p++;
	if (ap2_p == ap2_lim) ap2_p=0;
	return readback;
}

float doReverb(float inSample) {
	float newsample = 	(
						Do_Comb0(inSample)
						//+ Do_Comb1(inSample)
						//+ Do_Comb2(inSample)
						//+ Do_Comb3(inSample)
						)
						/3.0f;
	newsample = Do_Allpass0(newsample);
	newsample = Do_Allpass1(newsample);
	newsample = Do_Allpass2(newsample);
	return newsample;
}

void initReverb()
{
	cf0_lim = (int)(time*l_CB0);
	cf1_lim = (int)(time*l_CB1);
	cf2_lim = (int)(time*l_CB2);
	cf3_lim = (int)(time*l_CB3);
	ap0_lim = (int)(time*l_AP0);
	ap1_lim = (int)(time*l_AP1);
	ap2_lim = (int)(time*l_AP2);
}

#ifdef __cplusplus
	}
#endif


