#pragma once

#include "imgui.h"

#include "file_dialog.h"

#include "light/light.h"
#include "camera/camera.h"
#include "renderer/renderer.h"
#include "model/model_loader.h"
#include "framebuffer/framebuffer.h"


namespace Bubble
{
	class ModelExplorer
	{
		Ref<Model> SelectedModel = nullptr;

		// Draw selected model
		Camera ActiveCamera;
		Framebuffer ActiveViewport;
		glm::vec3 Translation;
		glm::vec3 Scale;
		glm::vec3 Rotation;

	private:
		void DrawSelectedModel();

	public:
		ModelExplorer();
		void Draw(bool* is_open);
	};

}