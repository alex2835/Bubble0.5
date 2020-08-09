#pragma once

#include "gl_assert/gl_assert.h"
#include "log/log.h"

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <exception>


namespace Bubble
{
    struct Shader
    {
	private:
        uint32_t m_ShaderID;
        std::string m_Name;
		std::unordered_map<std::string, int> m_UniformCache;

    private:
        void ParseShaders(const std::string& path, std::string& vertex, std::string& fragment, std::string& geometry);
        void CompileShaders(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometry);
        int GetUni(const std::string& name);

    public:
        Shader(const std::string& path);

        Shader(const std::string& vertex,
               const std::string& fragment,
               const std::string& geometry = std::string());

        void Bind();
        void Unbind();

        // lone int 
        void SetUni1i(const std::string& name, const int& val);

        // float vec
        void SetUni1f(const std::string& name, const float& val);
        void SetUni2f(const std::string& name, const glm::vec2& val);
        void SetUni3f(const std::string& name, const glm::vec3& val);
        void SetUni4f(const std::string& name, const glm::vec4& val);

        // float matrices
        void SetUniMat3(const std::string& name, const glm::mat3& val);
        void SetUniMat4(const std::string& name, const glm::mat4& val);

    };
}