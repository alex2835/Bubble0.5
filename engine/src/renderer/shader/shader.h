#pragma once

#include "renderer_base.h"
#include "texture/texture.h"
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
    class Shader
    {
		std::string mName;
        uint32_t mShaderID;
		mutable std::unordered_map<std::string, int> mUniformCache;

    private:
        void ParseShaders(const std::string& path, std::string& vertex, std::string& fragment, std::string& geometry);
        void CompileShaders(const std::string& vertex_source, const std::string& fragment_source, const std::string& geometry_source);
        int GetUni(const std::string& name) const;

    public:
        Shader(const std::string& path);

        Shader(const std::string& name,
               const std::string& vertex,
               const std::string& fragment,
               const std::string& geometry = std::string());

        void Bind() const;
        void Unbind() const;
        
        // lone int 
        void SetUni1i(const std::string& name, const int& val) const;

        // float vec
        void SetUni1f(const std::string& name, const float& val) const;
        void SetUni2f(const std::string& name, const glm::vec2& val) const;
        void SetUni3f(const std::string& name, const glm::vec3& val) const;
        void SetUni4f(const std::string& name, const glm::vec4& val) const;

        // float matrices
        void SetUniMat3(const std::string& name, const glm::mat3& val) const;
        void SetUniMat4(const std::string& name, const glm::mat4& val) const;

        static Ref<Shader> Open(const std::string& path);
    private:
        static std::vector<std::pair<std::string, Ref<Shader>>> s_OpenedShaders;
    };
}