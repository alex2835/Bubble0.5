
#include "loader.h"


namespace Bubble
{
	Scope<std::unordered_map<std::string, Ref<Skybox>>> Loader::sLoadedSkyboxes;


	Ref<Skybox> Loader::LoadSkybox(std::string path)
	{
		if (auto model = sLoadedSkyboxes->find(path);
			model != sLoadedSkyboxes->end())
		{
			return model->second;
		}

		Ref<Skybox> skybox = CreateRef<Skybox>();

		auto [orig_data, orig_spec] = Texture2D::OpenRawImage(path);

		if (!orig_data)
			throw std::runtime_error("Skybox loading failed: " + path);

		Texture2DSpecification spec = orig_spec;
		int width = orig_spec.Width / 4;
		int height = orig_spec.Height / 3;

		spec.Width = width;
		spec.Height = height;

		int channels;
		if (spec.DataFormat == GL_RED) {
			channels = 1;
		}
		else if (spec.DataFormat == GL_RGB) {
			channels = 3;
		}
		else if (spec.DataFormat == GL_RGBA) {
			channels = 4;
		}

		uint8_t* data[6];
		for (int i = 0; i < 6; i++)
		{
			data[i] = new uint8_t[width * height * channels];
		}

		// Parse 6 textures from single image
		// 0-left 1-front 2-right 3-back
		for (int i = 0; i < 4; i++)
		{
			for (int y = 0; y < height; y++)
			{
				int y_offset = height;
				int raw_y_coord = (y + y_offset) * orig_spec.Width * channels;
				int raw_width = width * channels;
				memmove(&data[i][y * raw_width], &orig_data[raw_y_coord + raw_width * i], raw_width);
			}
		}
		// 4-top
		for (int y = 0; y < height; y++)
		{
			int y_offset = height * 2;
            int raw_y_coord = (y + y_offset) * orig_spec.Width * channels;
            int raw_width = width * channels;
			memmove(&data[4][y * raw_width], &orig_data[raw_y_coord + raw_width], raw_width);
		}
		// 5-bottom
		for (int y = 0; y < height; y++) {
            int raw_y_coord = y * orig_spec.Width * channels;
            int raw_width = width * channels;
			memmove(&data[5][y * raw_width], &orig_data[raw_y_coord + raw_width], raw_width);
		}

		// Reorder to: right, left, top, bottom, front, back
		std::swap(data[0], data[2]);
		std::swap(data[1], data[2]);
		std::swap(data[2], data[4]);
		std::swap(data[3], data[5]);
		std::swap(data[2], data[3]);
		
		skybox->mSkybox = Cubemap(data, spec);

		for (int i = 0; i < 6; i++)
		{
			delete data[i];
		}
		sLoadedSkyboxes->emplace(path, skybox);
		return skybox;
	}

	Ref<Skybox> Loader::LoadSkyboxFromDir(const std::string& dir, const std::string& ext)
	{
		Ref<Skybox> skybox = CreateRef<Skybox>();
		skybox->mSkybox = Cubemap(dir, ext);
		sLoadedSkyboxes->emplace(dir, skybox);
		return skybox;
	}

}