#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <glad/glad.h>

namespace CrosslyGL
{

	class Shader
	{
	public:
		Shader() {
			m_Program = glCreateProgram();
		}
		~Shader() {
			glDeleteProgram(m_Program);
		}
		Shader& attach(unsigned int shader, bool del = true) {
			glAttachShader(m_Program, shader);
			return *this;
		}
		Shader& link() {
			glLinkProgram(m_Program);
			validateProgram(m_Program, GL_LINK_STATUS);
			return *this;
		}
		void use() {
			glUseProgram(m_Program);
		}
		void setFloat(const std::string& name, const float value) {
			glUniform1f(getUniformLocation(name), value);
		}
		void setVec3(const std::string& name, const float* const value) {
			glUniform3fv(getUniformLocation(name), 1, value);
		}
	public:
		static unsigned int compileShaderFromFile(const char* url, unsigned int type) {
			unsigned int shader = glCreateShader(type);
			std::ifstream file(url);
			if (file.is_open()) {
				std::stringstream ss;
				ss << file.rdbuf();
				std::string sourceStr = ss.str();
				const char* source = sourceStr.c_str();
				glShaderSource(shader, 1, &source, nullptr);
				glCompileShader(shader);
				validateShader(shader, GL_COMPILE_STATUS);
			}
			else {
				std::string message = "File not found ";
				message += url;
				throw std::exception(message.c_str());
			}
			file.close();
			return shader;
		}
		static unsigned int compileShaderFromMemory(const char* src, unsigned int type) {
			unsigned int shader = glCreateShader(type);
			glShaderSource(shader, 1, &src, nullptr);
			glCompileShader(shader);
			validateShader(shader, GL_COMPILE_STATUS);
			return shader;
		}
	protected:
		static void validateShader(unsigned int shader, unsigned int pname) {
			int success;
			glGetShaderiv(shader, pname, &success);
			if (!success) {
				char infoLog[512];
				glGetShaderInfoLog(shader, 512, nullptr, infoLog);
				std::cout << infoLog;
				std::cin.get();
			}
		}
		static void validateProgram(unsigned int program, unsigned int pname) {
			int success;
			glGetProgramiv(program, pname, &success);
			if (!success) {
				char infoLog[512];
				glGetProgramInfoLog(program, 512, nullptr, infoLog);
				std::cout << infoLog;
				std::cin.get();
			}
		}
	private:
		int getUniformLocation(const std::string& name)
		{
			if (m_UniformCache.find(name) != m_UniformCache.end()) {
				return m_UniformCache.at(name);
			}
			int loc = glGetUniformLocation(m_Program, name.c_str());
			if (loc < 0) std::cout << "Uniform '" << name << "' is unused or not present in shader!" << std::endl;
			return m_UniformCache[name] = loc;
		}
	private:
		unsigned int m_Program{};
		std::unordered_map<std::string, int> m_UniformCache;
	};

}