#include "stdafx.h"
#include "CppUnitTest.h"
#include "../emulator/State.c"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace emulator_test
{		
	TEST_CLASS(StateTest)
	{
	public:
		TEST_METHOD(ResetState)
		{
			// Set State8080 values
			State8080 *state = Get_State();

			state->a = 0xa;
			state->h = 0xf;
			state->psw.cy = 1;
			state->psw.z = 1;

			uint8_t expected = 0;

			// Reset all State8080 values
			Reset_State();

			// Check
			Assert::AreEqual(state->a, (uint8_t)0);
			Assert::AreEqual(state->h, (uint8_t)0);
			Assert::AreEqual(state->psw.cy, (uint8_t)0);
			Assert::AreEqual(state->psw.z, (uint8_t)0);
		}
	};
}