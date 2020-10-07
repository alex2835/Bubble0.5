#pragma once

#include "UI_components/model_loading.h"

namespace Bubble
{
	struct UIArgs
	{
		std::vector<Ref<Model>>* Models;
	};


	class UI
	{
	public:
		bool ModelLoader = true;

		void Draw(UIArgs args);
	};
}