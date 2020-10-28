
#include "shader.h"


namespace Bubble
{
	std::vector<std::pair<std::string, Ref<Shader>>> Shader::s_OpenedShaders;

    void Shader::ParseShaders(const std::string& path, std::string& vertex, std::string& fragment, std::string& geometry)
    {
        enum ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2 };
        ShaderType type = NONE;
        
        std::ifstream stream(path);
        if (!stream.is_open())
        {
            throw std::runtime_error("Incorrect shader file path: " + path);
        }
    
        std::string line;
        std::stringstream shaders[3];
    
        while (std::getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    type = VERTEX;
                }
                else if (line.find("fragment") != std::string::npos)
                {
                    type = FRAGMENT;
                }
                else if (line.find("geometry") != std::string::npos)
                {
                    type = GEOMETRY;
                }
            }
            else if (type == NONE) {
                continue;
            }
            else {
                shaders[type] << line << '\n';
            }
        }
        vertex = shaders[VERTEX].str();
        fragment = shaders[FRAGMENT].str();
        geometry = shaders[GEOMETRY].str();
    }

    void Shader::CompileShaders(const std::string& vertex_source, const std::string& fragment_source, const std::string& geometry_source)
    {
        // Vertex shaders
        GLint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        const char* cvertex_source = vertex_source.c_str();
        glcall(glShaderSource(vertex_shader, 1, &cvertex_source, NULL));
        glcall(glCompileShader(vertex_shader));
        {
            GLint success;
            glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                GLint max_length = 0;
                glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);
    
                std::string log;
                log.resize(max_length);
                glGetShaderInfoLog(vertex_shader, max_length, &max_length, (GLchar*)log.data());
                glDeleteShader(vertex_shader);
    
                // free resources
    			glDeleteShader(vertex_shader);
    
                LOG_CORE_ERROR("VERTEX SHADER ERROR: {0} \n {1}", mName, log);
    			throw std::runtime_error("Shader compilation failed");
            }
        }
            
        // Fragment shader
        GLint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* cfragment_source = fragment_source.c_str();
        glcall(glShaderSource(fragment_shader, 1, &cfragment_source, NULL));
        glcall(glCompileShader(fragment_shader));
        {
            GLint success;
            glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                GLint max_length = 0;
				std::string log;

                glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);
                log.resize(max_length);
                glGetShaderInfoLog(fragment_shader, max_length, &max_length, (GLchar*)log.data());
                glDeleteShader(fragment_shader);

				// free recourses
				glDeleteShader(vertex_shader);
				glDeleteShader(fragment_shader);

                LOG_CORE_ERROR("FRAGMENT SHADER ERROR: : {0} \n {1}", mName, log);
				throw std::runtime_error("Shader compilation failed");
            }
        }
        
        // Geometry shader
        GLint geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
        if (geometry_source.size())
        {
            const char* cgeometry_source = geometry_source.c_str();
            glcall(glShaderSource(geometry_shader, 1, &cgeometry_source, NULL));
            glcall(glCompileShader(geometry_shader));
            {
                GLint success;
                glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    GLint max_length = 0;
					std::string log;

                    glGetShaderiv(geometry_shader, GL_INFO_LOG_LENGTH, &max_length);
                    log.resize(max_length);
                    glGetShaderInfoLog(geometry_shader, max_length, &max_length, (GLchar*)log.data());

					// free resources
					glDeleteShader(geometry_shader);
					glDeleteShader(vertex_shader);
					glDeleteShader(fragment_shader);

                    LOG_CORE_ERROR("GEOMETRY SHADER ERROR: {0} \n {1}", mName, log);
					throw std::runtime_error("Shader compilation failed");
                }
            }
        }
		// Shader program
		mShaderID = glCreateProgram();

		// Link shaders
        glcall(glAttachShader(mShaderID, vertex_shader));
        glcall(glAttachShader(mShaderID, fragment_shader));
        if (geometry_source.size())
        {
            glcall(glAttachShader(mShaderID, geometry_shader));
        }
        glcall(glLinkProgram(mShaderID));
        
        {
            GLint success;
            glGetProgramiv(mShaderID, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                GLint max_length = 0;
				std::string log;

                glGetShaderiv(geometry_shader, GL_INFO_LOG_LENGTH, &max_length);
                log.resize(max_length);
                glGetProgramInfoLog(mShaderID, max_length, NULL, (GLchar*)log.data());

                // free resources
				glDeleteShader(geometry_shader);
				glDeleteShader(vertex_shader);
				glDeleteShader(fragment_shader);
                glDeleteProgram(mShaderID);

                LOG_CORE_ERROR("LINLING SHADER ERROR: {0} \n {1}", mName, log);
                throw std::runtime_error("Shader compilation failed");
            }
        }

        // Now it's a part of shader program
        glDeleteShader(geometry_shader);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    int Shader::GetUni(const std::string& uniformname) const
    {
        glcall(glUseProgram(mShaderID));
        if (mUniformCache.find(uniformname) != mUniformCache.end())
        {
            return mUniformCache[uniformname];
        }

        int unifromid = glGetUniformLocation(mShaderID, uniformname.c_str());
        if (unifromid == -1)
        {
            LOG_CORE_WARN("Shader: {0} doesn't have uniform: {1}", mName, uniformname);
        }
        mUniformCache[uniformname] = unifromid;
        return unifromid;
    }

    // =================== Contructors ====================

    Shader::Shader(const std::string& path)
    {
		std::string vertexSource, fragmentSource, geometry;
        mName = path.substr(path.find_last_of('/') + 1);
        
        ParseShaders(path, vertexSource, fragmentSource, geometry);
        CompileShaders(vertexSource, fragmentSource, geometry);
    }

	Shader::Shader(const std::string& name,
                   const std::string& vertex,
                   const std::string& fragment,
                   const std::string& geometry /*= std::string()*/)
        : mName(name)
	{
        CompileShaders(vertex, fragment, geometry);
	}

	void Shader::Bind() const
	{
        glcall(glUseProgram(mShaderID));
	}

	void Shader::Unbind() const
	{
        glcall(glUseProgram(0));
	}


	// lone int 
    void Shader::SetUni1i(const std::string& mName, const int& val) const
    {
        glcall(glUniform1i(GetUni(mName), val));
    }

    // float vec
    void Shader::SetUni1f(const std::string& mName, const float& val) const
    {
        glcall(glUniform1f(GetUni(mName), val));
    }

    void Shader::SetUni2f(const std::string& mName, const glm::vec2& val) const
    {
        glcall(glUniform2f(GetUni(mName), val.x, val.y));
    }

    void Shader::SetUni3f(const std::string& mName, const glm::vec3& val) const
    {
        glcall(glUniform3f(GetUni(mName), val.x, val.y, val.z));
    }

    void Shader::SetUni4f(const std::string& mName, const glm::vec4& val) const
    {
        glcall(glUniform4f(GetUni(mName), val.x, val.y, val.z, val.w));
    }

    // float matrices
    void Shader::SetUniMat3(const std::string& mName, const glm::mat3& val) const
    {
        glcall(glUniformMatrix3fv(GetUni(mName), 1, GL_FALSE, glm::value_ptr(val)));
    }

    void Shader::SetUniMat4(const std::string& mName, const glm::mat4& val) const
    {
        glcall(glUniformMatrix4fv(GetUni(mName), 1, GL_FALSE, glm::value_ptr(val)));
    }

	
	Ref<Shader> Shader::Open(const std::string& path)
	{
        for (auto path_shader : s_OpenedShaders)
        {
            if (path_shader.first == path) {
                return path_shader.second;
            }
        }
        return CreateRef<Shader>(path);
	}


}