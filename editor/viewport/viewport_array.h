#pragma once

#include "viewport.h"

#include <vector>


namespace Bubble
{
	class ViewportArray
	{
		std::vector<Viewport> m_Viewports;
		std::vector<char> m_IsOpen;

	public:
		void Erase(int idx);
		void Push(Viewport&& viewport);
		int Size();

		void RemoveNotActiveViewports();
		
		Viewport& operator[] (int idx);
		char& IsOpen(int idx);

		std::vector<Viewport>::iterator begin();
		std::vector<Viewport>::iterator end();
	};
}