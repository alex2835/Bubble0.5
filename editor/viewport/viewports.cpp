
#include "viewports.h"

namespace Editor
{
	void ImGuiViewports::Erase(int idx)
	{
		m_Viewports.erase(m_Viewports.begin() + idx);
		m_IsOpen.erase(m_IsOpen.begin() + idx);
	}

	void ImGuiViewports::Push(Viewport&& viewport)
	{
		std::string name = viewport.GetName();
		auto viewport_iterator = begin();

		while (viewport_iterator != end())
		{
			viewport_iterator = std::find_if(begin(), end(),
				[&name](const Viewport& viewport)
				{
					return name == viewport.GetName();
				}
			);

			// Viewport with this name already exist
			if (viewport_iterator != end())
			{
				name += "*";
			}
		}

		if (name != viewport.GetName())
		{
			viewport.Rename(name);
		}

		m_Viewports.push_back(std::move(viewport));
		m_IsOpen.push_back(true);
	}

	int ImGuiViewports::Size()
	{
		return m_Viewports.size();
	}

	void ImGuiViewports::RemoveNotActiveViewports()
	{
		for (int i = 0; i < Size(); i++)
		{
			if (!m_IsOpen[i])
			{
				Erase(i);
			}
		}
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