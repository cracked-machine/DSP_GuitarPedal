/*
 * test_src.cpp
 *
 *  Created on: Apr 2, 2021
 *      Author: chris
 */

#include "test_src.hpp"

#ifdef __cplusplus
	extern "C"
	{
#endif

	void run_cpputests()
	{
		const char * av_override[] = { };
		CommandLineTestRunner::RunAllTests(0, av_override);
	}

	TEST_GROUP(FirstTestGroup)
	{
	};
	TEST(FirstTestGroup, FirstTest) // failure
	{
	    FAIL("Embedded Area");
	}

	TEST(FirstTestGroup, SecondTest) // successful
	{
	    CHECK_EQUAL_ZERO(0);
	}

#ifdef __cplusplus
	}
#endif

