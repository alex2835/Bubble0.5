#pragma once

namespace Bubble
{
	class DeltaTime
	{
		float m_LastTime = 0;
		float m_Deltatime = 0;

	public:
		DeltaTime() {}

		void Update(float current_time);
		
		float GetSeconds();
		float GetMilliseconds();
	};

}