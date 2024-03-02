#include <iostream>
/**
 * 'glad.h' should always come before any header file that includes 'gl.h'
 */
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <CrosslyGL/Shader.h>

using CrosslyGL::Shader;

int main(int argc, char** argv)
{
	/**
	 * Configuring the window as an OpenGL render context.
	 * The OpenGL version is 4.1 core and the window shouldn't be resizable.
	 */
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	
	/**
	 * Creating the window with width and height of 800 by 600 and title 'Creating a window'.
	 */
	GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", nullptr, nullptr);

	/**
	 * Validating that the window has been created.
	 */
	if (window == nullptr)
	{
		std::cout << "glfwCreateWindow failed!" << std::endl;
		std::cin.get();
		glfwTerminate();
		return -1;
	}

	/**
	 * Setting the window as the current render context.
	 * Meaning that when fetching OpenGL function pointers from the driver
	 * the version should be OpenGL 4.1 core.
	 */
	glfwMakeContextCurrent(window);

	/**
	 * Fetching the affore mentioned OpenGL functions and validating.
	 */
	if (gladLoadGL() == 0)
	{
		std::cout << "gladLoadGL failed!" << std::endl;
		std::cin.get();
		glfwDestroyWindow(window);
		return -1;
	}

	/**
	* Setting vsync to on.
	*/
	glfwSwapInterval(1);

	{

		float triangle[6] = {
			0.0f, 0.5f,
			-.5f, -.5f,
			0.5f, -.5f,
		};

		unsigned int VAO, VBO;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, triangle, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, reinterpret_cast<void*>(0));
		glEnableVertexAttribArray(0);

		Shader triangleShader = Shader();
		triangleShader.attach(Shader::compileShaderFromMemory(
R"(#version 410 core
layout (location = 0) in vec2 aPos;
void main()
{
	gl_Position = vec4(aPos, 0.0, 1.0);
})", GL_VERTEX_SHADER))
			.attach(Shader::compileShaderFromMemory(
R"(#version 410 core
layout (location = 0) out vec4 oColor;
void main()
{
	oColor = vec4(1.0);
})", GL_FRAGMENT_SHADER))
			.link()
			.use();

		/**
		 * The application loop that checks if the window is meant to be closed before exiting.
		 */
		while (!glfwWindowShouldClose(window))
		{
			/**
			 * Clearing the color channel.
			 * This can also clear depth and stencils but for now only clears the color buffer.
			 */
			glClear(GL_COLOR_BUFFER_BIT);


			glDrawArrays(GL_TRIANGLES, 0, 3);

			/**
			 * Swapping the front and back buffer as OpenGL is double buffered by default.
			 */
			glfwSwapBuffers(window);

			/**
			 * Checking for any input events for example closing the window.
			 */
			glfwPollEvents();
		}

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
	/**
	 * Destroying the render context.
	 * Any OpenGL objects should be destroyed before this point.
	 */
	glfwDestroyWindow(window);
	/**
	 * Terminating the render context.
	 */
	glfwTerminate();
	std::cout << R"(Exiting "Triangle" application...)" << std::endl;
	std::cin.get();
	return 0;
}