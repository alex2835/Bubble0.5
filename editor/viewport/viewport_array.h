#pragma once

#include "viewport.h"

#include <vector>


namespace Editor
{
	struct ViewportArray
	{
		std::vector<Viewport> m_Viewports;
		std::vector<bool> m_IsOpen;

		void Erase(int idx);
		void Push(Viewport&& viewport);
		int Size();

		void RemoveNotActiveViewports();
		
		Viewport& operator[] (int idx);

		std::vector<Viewport>::iterator begin();
		std::vector<Viewport>::iterator end();
	};
}