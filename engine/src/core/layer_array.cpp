
#include "layer_array.h"


namespace Bubble
{
	void LayerArray::Push(Layer* layer)
	{
		mLayers.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerArray::Remove(int id)
	{
		mLayers[id]->OnDetach();
		mLayers.erase(mLayers.begin() + id);
	}

	void LayerArray::Insert(int id, Layer* layer)
	{
		mLayers.emplace(mLayers.begin() + id, layer);
		layer->OnAttach();
	}

	void LayerArray::Swap(int id_1, int id_2)
	{
		std::swap(mLayers[id_1], mLayers[id_2]);
	}

	Layer* LayerArray::operator [] (int id)
	{
		return mLayers[id].get();
	}

}