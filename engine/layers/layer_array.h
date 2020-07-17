#pragma once

#include "layer.h"
#include <vector>
#include <memory>

namespace Bubble
{
	struct LayerArray
	{
		std::vector<std::unique_ptr<Layer>> m_Layers;

		void push_back(Layer* layer);
		void remove(int id);
		void emplace(int id, Layer* layer);
		void swap(int id_1, int id_2);

		std::vector<std::unique_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<std::unique_ptr<Layer>>::iterator end() { return m_Layers.end(); }

		std::unique_ptr<Layer>& operator [] (int id);
		~LayerArray();
	};
}