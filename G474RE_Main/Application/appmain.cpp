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
#include <cpputests_main.hpp>
#include "appmain.hpp"

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

// Application sources
#include "dsp_buffer.hpp"
#include "sine_lookup_table.hpp"

size_t x = 0;
uint8_t *it = (uint8_t*)sine_lut.begin();


#ifdef __cplusplus
	extern "C"
	{
#endif
	size_t size = 10;
	dsp_double_buffer<uint16_t, 10> my_buf;

	void appmain()
	{

		uint16_t *tmpRx = my_buf.getRxBuf();
		std::cout << tmpRx[0] << std::endl;



		//std::cout << my_buf._rxBuf[0] << std::endl;

/*
		buf = std::unique_ptr<int[]>(new int[size]);
		//std::unique_ptr<int[]> buf(new int[size]);
		for (size_t i = 0; i < size; ++i) {
			buf[i] = (i == 0) ? 1 : i * buf[i-1];
		}
		int *bufarray = buf.get();
*/
		run_all_tests();
		std::cout << "Running Loop" << std::endl;

		HAL_TIM_Base_Start_IT(&htim6);
		HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);



		while(1)
		{

		}

	}


	void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	{
		uint8_t index = x++ & (sine_lut.size()-1);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_8B_R, sine_lut[index]);
	}





#ifdef __cplusplus
	}
#endif

