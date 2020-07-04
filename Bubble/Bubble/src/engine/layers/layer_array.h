#pragma once

#include "layer.h"


namespace Bubble
{
	struct LayerArray
	{
		std::vector<std::unique_ptr<Layer>> layers;

		void push_back(Layer* layer);
		void remove(int id);
		void emplace(int id, Layer* layer);
		void swap(int id_1, int id_2);

		std::unique_ptr<Layer>& operator [] (int id);
		~LayerArray();
	};
}