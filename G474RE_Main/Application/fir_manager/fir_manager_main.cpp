/*
 *  	fir_manager_main.cpp
 *
 *  	Created on: 6 Apr 2021
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

#include "fir_manager.hpp"





#ifdef __cplusplus
	extern "C"
	{
#endif

	typedef fir_manager<TIM_HandleTypeDef, DAC_HandleTypeDef> my_fir_manager;
	my_fir_manager firman(htim6, hdac1);

	void fir_manager_main()
	{

		firman.start();

		while(1)
		{

		}
	}

/*	void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	{
		firman.update();
	}
*/
#ifdef __cplusplus
	}
#endif


