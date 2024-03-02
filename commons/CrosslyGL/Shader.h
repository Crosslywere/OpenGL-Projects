#pragma once

#include <iostream>
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
		static unsigned int compileShaderFromMemory(const char* src, unsigned int type) {
			unsigned int shader = glCreateShader(type);
			glShaderSource(shader, 1, &src, nullptr);
			glCompileShader(shader);
			validateShader(shader, GL_COMPILE_STATUS);
			return shader;
		}
	private:
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
		unsigned int m_Program{};
	};

}