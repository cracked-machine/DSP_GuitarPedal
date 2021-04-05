/*
 * 		appmain.cpp
 *
 *  	Created on: Apr 2, 2021
 *      Author: Chris Sutton
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

// header
#include <double_buffer.hpp>
#include <double_buffer16.hpp>

#include <double_buffer32.hpp>
#include <double_bufferf32.hpp>

#include <audio_buffer.hpp>

#include "iir_filter_32u.hpp"

#include <tests_main.hpp>

#include "appmain.hpp"
#include "sine_lookup_table.hpp"

// c++ std lib
#include <iostream>
#include <memory>
#include <algorithm>

// STM HAL Framework
#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_tim.h"
#include "stm32g4xx_hal_tim_ex.h"
#include "stm32g4xx_hal_dac.h"
#include "stm32g4xx_hal_dac_ex.h"
#include "stm32g4xx_hal_gpio.h"
#include "stm32g4xx_hal_gpio_ex.h"

// STM32Cube generated HAL init code
#include "tim.h"
#include "dac.h"
#include "gpio.h"

// CMSIS DSP
#include <arm_math.h>

size_t count = 0;
size_t sine_lut_index = 0;
size_t lut_index = 0;

#define TEST_LUT tri_lut_f32

#ifdef __cplusplus
	extern "C"
	{
#endif

	// create a uint32_t ping pong buffer
	audiobuffer_u32 t_dbuf;
	uint32_t* t_dbuf_rxptr = t_dbuf.get_rxBuf();

	// settings for output DAC timer to control pitch, offset and amplitude
	uint32_t base_period = 1024;
	float octave_pitch_down = 1;
	float offset = 0.0f;
	float amplitude = 1.0f;


	iir_filter_32u *iir1 = new iir_filter_32u();
	uint32_t *iir_output;
	//arm_fir_instance_f32 S;




	void appmain()
	{

		run_all_tests();

		// clock the data into the double_buffer32 using TIM7
		TIM7->ARR = base_period;
		HAL_TIM_Base_Start_IT(&htim7);

		// clock the DAC output using TIM6 (see HAL_TIM_PeriodElapsedCallback callback)
		TIM6->ARR = base_period * octave_pitch_down;
		HAL_TIM_Base_Start_IT(&htim6);

		// set the txBuff pointer as DMA destination
		//HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, (uint32_t*)dbuf32->get_txBuf(), 1, DAC_ALIGN_12B_R);
		HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, (uint32_t*)t_dbuf.get_txBuf(), 1, DAC_ALIGN_12B_R);


		while(1)
		{

		}

	}

	void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	{
		// the receive timer
		if(htim->Instance == TIM7)
		{
			//rest the rx ptr to Buffer A and tx ptr to Buffer B
			t_dbuf.reset();

			// increment the LUT position (circular)
			lut_index = count & ( TEST_LUT.size() - 1 );

			// assign new data to the rx buffer
			*t_dbuf_rxptr = TEST_LUT[lut_index];

			// process the rx buffer data here
			*t_dbuf_rxptr = *t_dbuf_rxptr * amplitude;
			*t_dbuf_rxptr = *t_dbuf_rxptr + offset;

			//swap the rx ptr to Buffer B and tx ptr to Buffer A
			t_dbuf.swap();

			//increment the counter
			count++;
		}

		// the DAC transmit timer
		if(htim->Instance == TIM6)
		{

		}



	}

#ifdef __cplusplus
	}
#endif

