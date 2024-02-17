#include <iostream>
/**
 * 'glad.h' should always come before any header file that includes 'gl.h'
 */
#include <glad/glad.h>
#include <glfw/glfw3.h>

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
	GLFWwindow* window = glfwCreateWindow(800, 600, "Creating a window", nullptr, nullptr);

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

		/**
		 * Swapping the front and back buffer as OpenGL is double buffered by default.
		 */
		glfwSwapBuffers(window);

		/**
		 * Checking for any input events for example closing the window.
		 */
		glfwPollEvents();
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
	std::cout << R"(Exiting "Creating a window" application...)" << std::endl;
	std::cin.get();
	return 0;
}