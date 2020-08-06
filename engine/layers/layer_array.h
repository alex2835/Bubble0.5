#pragma once

#include "layer.h"
#include <vector>
#include <memory>

namespace Bubble
{
	struct LayerArray
	{
		std::vector<std::unique_ptr<Layer>> m_Layers;

		void Push(Layer* layer);
		void Remove(int id);
		void Emplace(int id, Layer* layer);
		void Swap(int id_1, int id_2);

		std::vector<std::unique_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<std::unique_ptr<Layer>>::iterator end() { return m_Layers.end(); }

		std::unique_ptr<Layer>& operator [] (int id);
		
		~LayerArray() = default;
	};
}