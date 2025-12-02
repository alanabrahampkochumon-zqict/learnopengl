#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

const GLchar* VERTEX_SOURCE = "#version 330 core\n"
							"layout(location = 0) in vec3 position;\n"
							"\n"
							"void main()\n"
							"{\n"
							"	gl_Position = vec4(position.xyz, 1.0);\n"
							"}\0";

const GLchar* FRAGMENT_SHADER = "#version 330 core\n"
								"layout(location = 0) out vec4 fragColor;\n"
								"\n"
								"void main()\n"
								"{\n"
								"	fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
								"}\0";

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


	// Wireframe Mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enable this to draw in wireframe

	// Exercise
	float vertex2[] = {
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	 	 0.0f, -0.5f, 0.0f,

		 0.0f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	// VAO
	GLuint vertexArrayObject2;
	glGenVertexArrays(1, &vertexArrayObject2);
	glBindVertexArray(vertexArrayObject2);

	// VBO
	GLuint vertexBufferObject2;
	glGenBuffers(1, &vertexBufferObject2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex2), vertex2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	// Vertex Data
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	// VBO
	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Element Buffer Object
	GLuint elementBufferObject;
	glGenBuffers(1, &elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Vertex Shader
	const GLuint vertexShader =	glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VERTEX_SOURCE, nullptr);
	glCompileShader(vertexShader);

	// Checking for compilation errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
	}


	// Fragment Shader
	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FRAGMENT_SHADER, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED\n" << infoLog << "\n";
	}

	// Create Program
	const GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	// Program Error Checking
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING FAILED\n" << infoLog << "\n";
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
	glEnableVertexAttribArray(0);

	glUseProgram(program);

	// Window Loop
	while (!glfwWindowShouldClose(window))
	{
		handleInput(window); // Handle Inputs

		// Rendering calls
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Change clear color
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program);
		glBindVertexArray(vertexArrayObject2);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

