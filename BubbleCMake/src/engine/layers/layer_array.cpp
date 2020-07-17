
//#include "pch.h"
#include "layer_array.h"


namespace Bubble
{
	void LayerArray::push_back(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerArray::remove(int id)
	{
		m_Layers[id]->OnDetach();
		m_Layers.erase(m_Layers.begin() + id);
	}

	void LayerArray::emplace(int id, Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + id, layer);
		layer->OnAttach();
	}

	void LayerArray::swap(int id_1, int id_2)
	{
		std::swap(m_Layers[id_1], m_Layers[id_2]);
	}

	std::unique_ptr<Layer>& LayerArray::operator [] (int id)
	{
		return m_Layers[id];
	}

	LayerArray::~LayerArray() {}
}