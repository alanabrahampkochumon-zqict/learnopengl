#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

// Handles window resizing
static void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Handles inputs
static void handleInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
	// Initialize GLFW
	glfwInit();


	/**
	 * Setup OpenGL major, minor versions, and compatibility profile
	 **/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// GLFW Window Creation
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		// Failed to create a window
		std::cout << "Failed to create a GLFW window" << "\n";
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD\n";
	}

	// Set viewport dimensions
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback); // Handle Resizing

	// Window Loop
	while (!glfwWindowShouldClose(window))
	{
		handleInput(window); // Handle Inputs

		// Rendering calls
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Change clear color
		glClear(GL_COLOR_BUFFER_BIT);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

