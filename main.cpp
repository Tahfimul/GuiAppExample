#include "libraries/includes/glad/glad.h"
#include "libraries/includes/GLFW/glfw3.h"
#include <iostream>
#include <math.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

const int WINDOW_HEIGHT = 400;
const int WINDOW_WIDTH = 400;

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform float size;\n"
"void main()\n"
"{\n"

"   gl_Position = vec4(size*aPos.x, size*aPos.y, size*aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"

"   FragColor = color;\n"
"}\n\0";


int main()
{
	glfwInit();

	//Set OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Set profile to use modern functions from OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a window of size 400x400 with a title
	GLFWwindow * window = glfwCreateWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "GUIAppExample", nullptr, nullptr);

	//Check if window creation fails
	if(window==nullptr)
	{
		std::cout<<"Creation of window failed"<<std::endl;

		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	//Specify window viewport for OpenGL to render custom color
	glViewport(0,0,WINDOW_HEIGHT,WINDOW_WIDTH);

	//Vertex Shader - Step 1 of Grpahics Pipeline
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach Vertex Shader source to Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//In order for machine to understand
	glCompileShader(vertexShader);

	//Fragment Shader - Step 5 of graphics pipeline
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach fragment shader source to fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	//In order for machine to understand
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Wrap/Link all shaders to shader program and generates an executable for each shader object
	glLinkProgram(shaderProgram);


	//Now that the executables are generated, there is no longer a need for
	//the shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper right corner
	};


	// Create reference containers for the Vertex Array Object and the Vertex Buffer Object
	// to send a bulk of instructions from CPU to GPU since this operation is expensive
	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the VAO to Make it the current Vertex Array Object
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Store vertices to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Variables to be changed in the ImGUI window
	bool drawTriangle = true;
	float size = 1.0f;
	float color[4] = {0.5f, 0.6f, 1.0f, 0.3f};

	//Exporting variables to shaders
	glUseProgram(shaderProgram);
	glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
	glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);


	//swap back and front buffers to display the front buffer color
	glfwSwapBuffers(window);


	while(!glfwWindowShouldClose(window))
	{
		//Set the color for the front buffer
		glClearColor(0.7f, 0.8f, 0.1f, 1.0f);

		//Clear the back buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//Let ImGui know to create a new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);

		// Draw the triangle using the GL_TRIANGLES primitive
		if (drawTriangle)
			glDrawArrays(GL_TRIANGLES, 0, 3);

		//Set Header title and text object using ImGui
		ImGui::Begin("GuiAppExample");
		ImGui::Text("Hello from the GuiAppExample!");
		ImGui::Checkbox("Draw Triangle", &drawTriangle);
		ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
		ImGui::ColorEdit4("Color Picker", color);
		ImGui::End();

		// Export variables to shader
		glUseProgram(shaderProgram);
		glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
		glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);

		//Stage Frame to be rendered
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);


		glfwPollEvents();

	}


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	//Delete all objects created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}

