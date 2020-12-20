#include "Libs.h"

#include "Shader.h"
#include "Texture.h"
#include "Game.h"





Vertex vertices[] =
{
	//Position						//Color								//TexCoord				//Normals
	glm::vec3(-0.5f, 0.5f, 0.f),	glm::vec3(1.f, 0.f, 0.f),			glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, 1.f),
	glm::vec3(-0.5f, -0.5f, 0.f),	glm::vec3(0.f, 1.f, 0.f),			glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),
	glm::vec3(0.5f, -0.5f, 0.f),	glm::vec3(0.f, 0.f, 1.f),			glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, 1.f),

	glm::vec3(0.5f, 0.5f, 0.f),		glm::vec3(1.f, 0.f, 0.f),			glm::vec2(1.f, 1.f),	glm::vec3(1.f, 0.f, 1.f),
	
	
};

unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =
{
	0, 1, 2,
	3, 0, 2
};

unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}


void updateInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void updateInput(GLFWwindow* window, Mesh &mesh)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.f, -0.01f));
		//position.z -= 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{

		mesh.move(glm::vec3(0.f, 0.f, +0.01f));
		//position.z += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{

		mesh.move(glm::vec3(0.01f, 0.f, 0.f));
		//position.x -= 0.001f;
	}if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(-0.01f, 0.f, 0.f));
		//position.x += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		mesh.rotate(glm::vec3(0.0f, 1.f, 0.f));
		//rotation.y += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		mesh.rotate(glm::vec3(0.0f, -1.f, 0.f));
		//rotation.y -= 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		mesh.scaleUp(glm::vec3(.1f));
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		mesh.scaleUp(glm::vec3(-.1f));
	}

	

}



void MoveTriangle(GLFWwindow* window, float& triangle_pos)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		triangle_pos += 0.0001;
		glUniform1f(0, triangle_pos);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		triangle_pos -= 0.0001;
		glUniform1f(0, triangle_pos);
}


//bool loadShaders(GLuint &program)
//{
//	bool loadsuccess = true;
//	char infoLog[512];
//	GLint success;
//
//	std::string temp = "";
//	std::string src = "";
//
//	std::ifstream in_file;
//
//	//Vertex
//
//	in_file.open("Resource/vertex_core.shader");
//
//	if (in_file.is_open())
//	{
//		while (std::getline(in_file, temp))
//			src += temp + "\n";
//	}
//	else
//	{
//		std::cout << "ERROR::LOAD SHADERS:: COULD NOT OPEN VERTEX FILE" << "\n";
//		loadsuccess = false;
//	}
//
//	in_file.close();
//
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	const GLchar* vertSrc = src.c_str();
//	glShaderSource(vertexShader, 1, &vertSrc, NULL);
//	glCompileShader(vertexShader);
//
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "Error::LOADSHARES::COULD_NOT_COMPILE_VERTEX_SHADER" << "\n";
//		std::cout << infoLog << "\n";
//		loadsuccess = false;
//	}
//
//	temp = "";
//	src = "";
//
//	//Fragment
//
//	in_file.open("Resource/fragment_core.shader");
//
//	if (in_file.is_open())
//	{
//		while (std::getline(in_file, temp))
//			src += temp + "\n";
//	}
//	else
//	{
//		std::cout << "ERROR::LOAD SHADERS:: COULD NOT OPEN FRAGMENT FILE" << "\n";
//		loadsuccess = false;
//	}
//
//	in_file.close();
//
//	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	const GLchar* fragSrc = src.c_str();
//	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
//	glCompileShader(fragmentShader);
//
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//
//	if (!success)
//	{
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//		std::cout << "Error::LOADSHARES::COULD_NOT_COMPILE_FRAGMENT_SHADER" << "\n";
//		std::cout << infoLog << "\n";
//		loadsuccess = false;
//	}
//	
//	//Program
//
//	program = glCreateProgram();
//	glAttachShader(program, vertexShader);
//	glAttachShader(program, fragmentShader);
//
//	glLinkProgram(program);
//
//	glGetProgramiv(program, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(program, 512, NULL, infoLog);
//		std::cout << "ERROR::Loadshaders:: could not link program" << "\n";
//		std::cout << infoLog << "\n";
//		loadsuccess = false;
//
//	}
//
//	//End
//
//	glUseProgram(0);
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	return loadsuccess;
//
//}


GLFWwindow* createWindow(
	const char* title,
	const int width, const int height,
	int& fbWidth, int& fbHeight,
	int GLmajorVer, int GLminorVer,
	bool resizable
)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLmajorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLminorVer);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE)

	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);


	glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	glfwMakeContextCurrent(window);

	return window;

}

int main()
{
	
	Game game("Youtube tutorial",
		640, 480, 4, 5, false);


	

	while (!game.getWindowShouldClose())
	{
		game.update();
		game.render();

		

		//End draw
	}


return 0;
	//End of Program
}

