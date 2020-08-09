
#include "viewport_array.h"

namespace Bubble
{
	void ViewportArray::Erase(int idx)
	{
		m_Viewports.erase(m_Viewports.begin() + idx);
		m_IsOpen.erase(m_IsOpen.begin() + idx);
	}

	void ViewportArray::Push(Viewport&& viewport)
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
			viewport.SetName(name);
		}

		m_Viewports.push_back(std::move(viewport));
		m_IsOpen.push_back(true);
	}

	int ViewportArray::Size()
	{
		return m_Viewports.size();
	}

	void ViewportArray::RemoveNotActiveViewports()
	{
		for (int i = 0; i < Size(); i++)
		{
			if (!m_IsOpen[i])
			{
				Erase(i);
			}
		}
	}

	Viewport& ViewportArray::operator[] (int idx)
	{
		return m_Viewports[idx];
	}
	
	std::vector<Viewport>::iterator ViewportArray::begin() { return m_Viewports.begin(); }
	std::vector<Viewport>::iterator ViewportArray::end() { return m_Viewports.end(); }
}