#pragma once

#include <vector>
#include "viewport.h"

namespace Editor
{
	struct ImGuiViewports
	{
		std::vector<Viewport> m_Viewports;
		std::vector<bool> m_isOpen;

		void erase(int idx);
		void push_back(Viewport&& viewport);
		void push_back(int width, int height);
		int size();

		void RemoveNotActiveViewports();
		
		Viewport& operator[] (int idx);

		std::vector<Viewport>::iterator begin();
		std::vector<Viewport>::iterator end();

	private:
		int m_NameNumber = 0;
	};

	// Global variable
	extern ImGuiViewports viewports;
}