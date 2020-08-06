
//#include "pch.h"
#include "layer_array.h"


namespace Bubble
{
	void LayerArray::Push(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerArray::Remove(int id)
	{
		m_Layers[id]->OnDetach();
		m_Layers.erase(m_Layers.begin() + id);
	}

	void LayerArray::Emplace(int id, Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + id, layer);
		layer->OnAttach();
	}

	void LayerArray::Swap(int id_1, int id_2)
	{
		std::swap(m_Layers[id_1], m_Layers[id_2]);
	}

	std::unique_ptr<Layer>& LayerArray::operator [] (int id)
	{
		return m_Layers[id];
	}

}