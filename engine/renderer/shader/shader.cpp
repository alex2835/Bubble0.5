
#include "shader.h"


namespace Bubble
{
        void Shader::ParseShaders(const std::string& path, std::string& vertex, std::string& fragment, std::string& geometry)
        {
            enum Type { NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2 } type = NONE;
            
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
                else if (type == NONE)
                {
                    continue;
                }
                else
                {
                    shaders[type] << line << '\n';
                }
            }
            vertex = shaders[VERTEX].str();
            fragment = shaders[FRAGMENT].str();
            geometry = shaders[GEOMETRY].str();
        }

        void Shader::CompileShaders(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometry)
        {
            // Vertex shaders
            GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
            const char* cvertexSource = vertexSource.c_str();
            glShaderSource(vertexShader, 1, &cvertexSource, NULL);
            glCompileShader(vertexShader);
            {
                GLint success;
                glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    GLint maxLength = 0;
                    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

                    std::string log;
                    log.resize(maxLength);
                    glGetShaderInfoLog(vertexShader, maxLength, &maxLength, (GLchar*)log.data());
                    glDeleteShader(vertexShader);

                    // free recourses
					glDeleteShader(vertexShader);

                    LOG_CORE_ERROR("VERTEX SHADER ERROR:", m_Name, "\n" ,  log);
					throw std::runtime_error("Shader compilation failed");
                }
            }
            
            // Fragment shader
            GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            const char* cfragmentSource = fragmentSource.c_str();
            glShaderSource(fragmentShader, 1, &cfragmentSource, NULL);
            glCompileShader(fragmentShader);
            {
                GLint success;
                glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    GLint maxLength = 0;
					std::string log;

                    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
                    log.resize(maxLength);
                    glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, (GLchar*)log.data());
                    glDeleteShader(fragmentShader);

					// free recourses
					glDeleteShader(vertexShader);
					glDeleteShader(fragmentShader);

                    LOG_CORE_ERROR("FRAGMENT SHADER ERROR:", m_Name, "\n", log);
					throw std::runtime_error("Shader compilation failed");
                }
            }
            
            // Geometry shader
            GLint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
            if (geometry.size())
            {
                const char* cgeometrySource = geometry.c_str();
                glShaderSource(geometryShader, 1, &cgeometrySource, NULL);
                glCompileShader(geometryShader);
                {
                    GLint success;
                    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
                    if (!success)
                    {
                        GLint maxLength = 0;
						std::string log;

                        glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &maxLength);
                        log.resize(maxLength);
                        glGetShaderInfoLog(geometryShader, maxLength, &maxLength, (GLchar*)log.data());

						// free recourses
						glDeleteShader(geometryShader);
						glDeleteShader(vertexShader);
						glDeleteShader(fragmentShader);

                        LOG_CORE_ERROR("GEOMETRY SHADER ERROR:", m_Name, "\n", log);
						throw std::runtime_error("Shader compilation failed");
                    }
                }
            }

			// Shader program
			m_ShaderID = glCreateProgram();

			// Link shaders
            glAttachShader(m_ShaderID, vertexShader);
            glAttachShader(m_ShaderID, fragmentShader);
            if (geometry.size())
            {
                glAttachShader(m_ShaderID, geometryShader);
            }
            glLinkProgram(m_ShaderID);
            
            {
                GLint success;
                glGetProgramiv(m_ShaderID, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    GLint maxLength = 0;
					std::string log;

                    glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &maxLength);
                    log.resize(maxLength);
                    glGetProgramInfoLog(m_ShaderID, maxLength, NULL, (GLchar*)log.data());

                    // free recourses
					glDeleteShader(geometryShader);
					glDeleteShader(vertexShader);
					glDeleteShader(fragmentShader);
                    glDeleteProgram(m_ShaderID);

                    LOG_CORE_ERROR("LINLING SHADER ERROR: ", m_Name, "\n", log);
                    throw std::runtime_error("Shader compilation failed");
                }
            }
            // Now it's a part of shader program
            glDeleteShader(geometryShader);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }

        int Shader::GetUni(const std::string& uniform_name)
        {
            Bind();
            if (m_UniformCache.find(uniform_name) != m_UniformCache.end())
            {
                return m_UniformCache[uniform_name];
            }

            int unifrom_id = glGetUniformLocation(m_ShaderID, uniform_name.c_str());
            if (unifrom_id == -1)
            {
                LOG_CORE_ERROR("Shader: {0} doesn't have uniform: {1}", m_Name, uniform_name);
            }
            m_UniformCache[uniform_name] = unifrom_id;
            return unifrom_id;
        }

        // =================== Contructors ====================

        Shader::Shader(const std::string& path)
        {
			std::string vertexSource, fragmentSource, geometry;
            m_Name = path.substr(path.find_last_of('/') + 1);
            
            ParseShaders(path, vertexSource, fragmentSource, geometry);
            CompileShaders(vertexSource, fragmentSource, geometry);
        }

		Shader::Shader(const std::string& vertex,
                       const std::string& fragment,
                       const std::string& geometry /*= std::string()*/)
		{
            m_Name = "No name";
            CompileShaders(vertex, fragment, geometry);
		}

		void Shader::Bind()
		{
            glUseProgram(m_ShaderID);
		}

		void Shader::Unbind()
		{
            glUseProgram(0);
		}

        // lone int 
        void Shader::SetUni1i(const std::string& m_Name, const int& val)
        {
            glcall(glUniform1i(GetUni(m_Name), val));
        }

        // float vec
        void Shader::SetUni1f(const std::string& m_Name, const float& val)
        {
            glcall(glUniform1f(GetUni(m_Name), val));
        }
        void Shader::SetUni2f(const std::string& m_Name, const glm::vec2& val)
        {
            glcall(glUniform2f(GetUni(m_Name), val.x, val.y));
        }
        void Shader::SetUni3f(const std::string& m_Name, const glm::vec3& val)
        {
            glcall(glUniform3f(GetUni(m_Name), val.x, val.y, val.z));
        }
        void Shader::SetUni4f(const std::string& m_Name, const glm::vec4& val)
        {
            glcall(glUniform4f(GetUni(m_Name), val.x, val.y, val.z, val.w));
        }

        // float matrices
        void Shader::SetUniMat3(const std::string& m_Name, const glm::mat3& val)
        {
            glUniformMatrix3fv(GetUni(m_Name), 1, GL_FALSE, glm::value_ptr(val));
        }
        void Shader::SetUniMat4(const std::string& m_Name, const glm::mat4& val)
        {
            glUniformMatrix4fv(GetUni(m_Name), 1, GL_FALSE, glm::value_ptr(val));
        }

}