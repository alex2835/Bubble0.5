
#include "viewport_array.h"

namespace Bubble
{
	void ViewportArray::Erase(int idx)
	{
		mViewports.erase(mViewports.begin() + idx);
		mIsOpen.erase(mIsOpen.begin() + idx);
	}

	void ViewportArray::Push(Viewport&& viewport)
	{
		std::string name = viewport.Name;
		auto viewport_iterator = begin();

		while (viewport_iterator != end())
		{
			viewport_iterator = std::find_if(begin(), end(),
				[&name](const Viewport& viewport)
				{
					return name == viewport.Name;
				}
			);

			// Viewport with this name already exist
			if (viewport_iterator != end())
			{
				name += "*";
			}
		}

		if (name != viewport.Name)
		{
			viewport.Name = name;
		}

		mViewports.push_back(std::move(viewport));
		mIsOpen.push_back(true);
	}

	int ViewportArray::Size()
	{
		return mViewports.size();
	}

	void ViewportArray::RemoveNotActiveViewports()
	{
		for (int i = 1; i < Size(); i++)
		{
			if (!mIsOpen[i])
			{
				Erase(i);
			}
		}
	}

	Viewport& ViewportArray::operator[] (int idx)
	{
		return mViewports[idx];
	}
	
	char& ViewportArray::IsOpen(int idx)
	{
		return mIsOpen[idx];
	}

	std::vector<Viewport>::iterator ViewportArray::begin() { return mViewports.begin(); }
	std::vector<Viewport>::iterator ViewportArray::end() { return mViewports.end(); }
}