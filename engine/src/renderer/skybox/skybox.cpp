
#include "skybox.h"


namespace Bubble
{
	VertexArray* Skybox::s_VertexArray = nullptr;

	// Positions          
	float SkyboxVertices[] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	Skybox::Skybox(const std::string& dir, const std::string& ext)
		: m_Skybox(dir, ext)
	{
		if (s_VertexArray == nullptr) {
			InitVertexArray();
		}
	}

	Skybox::Skybox(const std::string& file)
	{
		if (s_VertexArray == nullptr) {
			InitVertexArray();
		}

		auto [orig_data, orig_spec] = Texture2D::OpenRawImage(file);

		if (orig_data == NULL) {
			throw std::runtime_error("Skybox loading failed: " + file);
		}

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
		// Sort to: right, left, top, bottom, front, back
		std::swap(data[0], data[2]);
		std::swap(data[1], data[2]);
		std::swap(data[2], data[4]);
		std::swap(data[3], data[5]);
		std::swap(data[2], data[3]);

		m_Skybox = Cubemap(data, spec);

		free(orig_data);
		for (int i = 0; i < 6; i++) {
			delete data[i];
		}
	}

	void Skybox::Bind(int slot)
	{
		s_VertexArray->Bind();
		glActiveTexture(GL_TEXTURE0 + slot);
		m_Skybox.Bind();
	}

	Skybox Skybox::LoadFromDir(const std::string& dir, const std::string& ext)
	{
		Skybox skybox(dir, ext);
		return skybox;
	}

	Skybox Skybox::LoadFromFile(const std::string& file)
	{
		Skybox skybox(file);
		return skybox;
	}

	void Skybox::InitVertexArray()
	{
		s_VertexArray = new VertexArray();
		VertexBuffer vb = VertexBuffer(SkyboxVertices, sizeof(SkyboxVertices));
		
		BufferLayout layout{
			{GLSLDataType::Float3, "Position" }
		};

		vb.SetLayout(layout);
		s_VertexArray->AddVertexBuffer(std::move(vb));
	}

}

