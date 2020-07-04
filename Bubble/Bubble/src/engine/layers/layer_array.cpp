
#include "pch.h"
#include "layer_array.h"


namespace Bubble
{
	void LayerArray::push_back(Layer* layer)
	{
		layers.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerArray::remove(int id)
	{
		layers[id]->OnDetach();
		layers.erase(layers.begin() + id);
	}

	void LayerArray::emplace(int id, Layer* layer)
	{
		layers.emplace(layers.begin() + id, layer);
		layer->OnAttach();
	}

	void LayerArray::swap(int id_1, int id_2)
	{
		std::swap(layers[id_1], layers[id_2]);
	}

	std::unique_ptr<Layer>& LayerArray::operator [] (int id)
	{
		return layers[id];
	}

	LayerArray::~LayerArray() {}
}