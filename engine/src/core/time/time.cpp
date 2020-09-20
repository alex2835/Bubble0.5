
#include "time.h"

namespace Bubble
{
	Time::Time(float time)
		: m_Time(time)
	{}

	float Time::GetSeconds()
	{
		return m_Time;
	}

	float Time::GetMilliseconds()
	{
		return m_Time * 1000.0f;
	}

}