
#include "loader.h"


namespace Bubble
{
	std::vector<std::pair<std::string, Bubble::Ref<Bubble::Skybox>>> Loader::sLoadedSkyboxes;


	Ref<Skybox> Loader::LoadSkybox(std::string path)
	{
		path = NormalizePath(path);

		if (Skybox::SkyboxVertexArray == nullptr) {
			Skybox::InitVertexArray();
		}

		for (const auto& stored_model : sLoadedSkyboxes)
		{
			if (stored_model.first.find(path) != std::string::npos ||
				path.find(stored_model.first) != std::string::npos)
			{
				return stored_model.second;
			}
		}

		Ref<Skybox> skybox = CreateRef<Skybox>();

		auto [orig_data, orig_spec] = Texture2D::OpenRawImage(path);

		if (orig_data == NULL)
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
		for (int i = 0; i < 6; i++) {
			data[i] = new uint8_t[width * height * channels];
		}

		// 0-left 1-front 2-right 3-back
		for (int i = 0; i < 4; i++) {
			for (int y = 0; y < height; y++) {
				memmove(&data[i][y * width * channels], &orig_data[(y + height) * orig_spec.Width * channels + width * channels * i], width * channels);
			}
		}
		// 4-top
		for (int y = 0; y < height; y++) {
			memmove(&data[4][y * width * channels], &orig_data[(y + height * 2) * orig_spec.Width * channels + width * channels], width * channels);
		}
		// 5-bottom
		for (int y = 0; y < height; y++) {
			memmove(&data[5][y * width * channels], &orig_data[y * orig_spec.Width * channels + width * channels], width * channels);
		}

		// Reorder to: right, left, top, bottom, front, back
		std::swap(data[0], data[2]);
		std::swap(data[1], data[2]);
		std::swap(data[2], data[4]);
		std::swap(data[3], data[5]);
		std::swap(data[2], data[3]);

		skybox->mSkybox = Cubemap(data, spec);

		free(orig_data);
		for (int i = 0; i < 6; i++) {
			delete data[i];
		}

		sLoadedSkyboxes.push_back({ path, skybox });
		return skybox;
	}

	Ref<Skybox> Loader::LoadSkyboxFromDir(const std::string& dir, const std::string& ext)
	{
		if (Skybox::SkyboxVertexArray == nullptr) {
			Skybox::InitVertexArray();
		}
		Ref<Skybox> skybox = CreateRef<Skybox>();
		skybox->mSkybox = Cubemap(dir, ext);
		sLoadedSkyboxes.push_back({ dir, skybox });
		return skybox;
	}

}