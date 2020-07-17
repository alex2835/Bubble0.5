
#include "viewports.h"

namespace Editor
{
	void ImGuiViewports::erase(int idx)
	{
		m_Viewports.erase(m_Viewports.begin() + idx);
		m_isOpen.erase(m_isOpen.begin() + idx);
	}

	// Name must be unique
	void ImGuiViewports::push_back(Viewport&& viewport)
	{
		m_Viewports.push_back(std::move(viewport));
		m_isOpen.push_back(true);
	}

	void ImGuiViewports::push_back(int width, int height)
	{
		Viewport viewport(width, height, "Viewport" + std::to_string(m_NameNumber++));
		m_Viewports.push_back(std::move(viewport));
		m_isOpen.push_back(true);
	}

	int ImGuiViewports::size()
	{
		return m_Viewports.size();
	}

	void ImGuiViewports::RemoveNotActiveViewports()
	{
		for (int i = 0; i < size(); i++)
			if (!m_isOpen[i])
				erase(i);
	}

	Viewport& ImGuiViewports::operator[] (int idx)
	{
		return m_Viewports[idx];
	}
	
	std::vector<Viewport>::iterator ImGuiViewports::begin() { return m_Viewports.begin(); }
	std::vector<Viewport>::iterator ImGuiViewports::end() { return m_Viewports.end(); }

	// Global variable definition
	ImGuiViewports viewports;
}