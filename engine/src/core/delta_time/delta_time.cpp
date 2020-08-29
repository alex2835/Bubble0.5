
#include "delta_time.h"

namespace Bubble
{
	void Bubble::DeltaTime::Update(float current_time)
	{
		m_Deltatime = current_time - m_LastTime;
		m_LastTime = current_time;
	}

	float Bubble::DeltaTime::GetSeconds()
	{
		return m_Deltatime;
	}

	float Bubble::DeltaTime::GetMilliseconds()
	{
		return m_Deltatime * 1000.0f;
	}

}