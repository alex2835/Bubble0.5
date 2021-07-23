#pragma once

#include "base.h"
#include "layer.h"

#include <vector>
#include <memory>


namespace Bubble
{
	class LayerArray
	{
		std::vector<Scope<Layer>> mLayers;

	public:
		void Push(Layer* layer);
		void Remove(int id);
		void Insert(int id, Layer* layer);
		void Swap(int id_1, int id_2);

		std::vector<Scope<Layer>>::iterator begin() { return mLayers.begin(); }
		std::vector<Scope<Layer>>::iterator end() { return mLayers.end(); }

		Layer* operator [] (int id);
		
		~LayerArray() = default;
	};
}