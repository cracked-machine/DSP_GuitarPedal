/*
 * appmain.cpp
 *
 *  Created on: Apr 2, 2021
 *      Author: chris
 */


#include "appmain.hpp"

#include <iostream>
#include "test_src.hpp"

#ifdef __cplusplus
	extern "C"
	{
#endif

	void appmain()
	{

		run_cpputests();

		while(1)
		{
			std::cout << "AppMain" << std::endl;
		}

	}

#ifdef __cplusplus
	}
#endif

