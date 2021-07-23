#pragma once

#include <time.h>
#include <chrono>

namespace Bubble
{
	using namespace std::chrono;

	class Time
	{
		float mTime = 0.0f;

	public:
		Time() = default;
		// Time in seconds
		Time(float time);

		float GetSeconds();
		float GetMilliseconds();
	};
	typedef Time DeltaTime;

	class Timer
	{
		static high_resolution_clock::time_point ProgramStartTime;
		high_resolution_clock::time_point mLastTime = Now();
		DeltaTime mDeltatime;

	public:
		void Update();
		DeltaTime GetDeltaTime();

		// Time from the program start
		static Time GetTime();

	private:
		static high_resolution_clock::time_point Now();
	};

}
