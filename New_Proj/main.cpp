#include "Libs.h"
#include "Shader.h"
#include "Texture.h"

Vertex vertices[] =
{
	//Position						//Color								//TexCoord				//Normals
	glm::vec3(-0.5f, 0.5f, 0.f),	glm::vec3(1.f, 0.f, 0.f),			glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, -1.f),
	glm::vec3(-0.5f, -0.5f, 0.f),	glm::vec3(0.f, 1.f, 0.f),			glm::vec2(0.f, 0.f),	glm::vec3(0.f, 1.f, -1.f),
	glm::vec3(0.5f, -0.5f, 0.f),	glm::vec3(0.f, 0.f, 1.f),			glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, -1.f),

	glm::vec3(0.5f, 0.5f, 0.f),		glm::vec3(1.f, 0.f, 0.f),			glm::vec2(1.f, 1.f),	glm::vec3(1.f, 0.f, -1.f),
	
	
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

void updateInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position.z -= 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position.z += 0.001f;
	}if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position.x -= 0.001f;
	}if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position.x += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		rotation.y += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		rotation.y -= 0.01f;
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

int main()
{
	//INIT GLFW

	glfwInit();

	//Create Window
	const int WINDOW_HEIGHT = 480;
	const int WINDOW_WIDTH = 640;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE)

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "NEW WINDOW", NULL, NULL);


	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(window);

	//INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)

	glewExperimental = GL_TRUE;

	//ERROR
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR MAIN.CPP GLEW FAILED" << "\n";
		glfwTerminate();
	}

	//MODEL

	//Shader INIT

	Shader core_program("Resource/vertex_core.shader", "Resource/fragment_core.shader", "");

	/*GLuint core_program;
	if (!loadShaders(core_program))
		glfwTerminate();*/

	//VAO
	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//GEN VBO AND BIND AND SEND DATA
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//GEN EBO AND BIND AND SEND DATA
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//SET VERTEX ARRAY ATTRIBPOINTER AND ENABLE (INPUT ASSEMBLY)
	//Position
	//GLuint attribLocPos = glGetAttribLocation(core_program.getId(), "vertex_position");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	//Color
	//GLuint attribLocCol = glGetAttribLocation(core_program.getId(), "vertex_color");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	//Texcoord
	//GLuint attribLocTC = glGetAttribLocation(core_program.getId(), "vertex_texcoord");
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);
	//Normal
	//GLuint attribLocNor = glGetAttribLocation(core_program.getId(), "vertex_normal");
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);



	//BIND VAO 0
	glBindVertexArray(0);


	


	//Texture 0
	/*int image_width = 0;
	int image_height = 0;
	int nrofChannels = 0;
	unsigned char* image = stbi_load("Resource/textures/earth.png", &image_width, &image_height, &nrofChannels, STBI_rgb_alpha);

	GLuint texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else {
		std::cout << "Error texture loading failed" << "\n";
	}

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);*/

	Texture texture0("Resource/textures/earth.png", STBI_rgb_alpha, 0);
	Texture texture1("Resource/textures/wall.jpg", STBI_rgb, 1);

	Material material0(glm::vec3(0.1f), glm::vec3(2.0f), glm::vec3(0.f),
		texture0.getTextureUnit(), texture1.getTextureUnit());

	////Texture 1
	//int image_width1 = 0;
	//int image_height1 = 0;
	//int nrofChannels1 = 0;
	//unsigned char* image1 = stbi_load("Resource/textures/wall.jpg", &image_width1, &image_height1, &nrofChannels1, STBI_rgb);

	//GLuint texture1;
	//glGenTextures(1, &texture1);
	//glBindTexture(GL_TEXTURE_2D, texture1);


	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



	//if (image1)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width1, image_height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
	//	glGenerateMipmap(GL_TEXTURE_2D);

	//}
	//else {
	//	std::cout << "Error texture loading failed" << "\n";
	//}

	//glActiveTexture(0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//stbi_image_free(image1);

	//INIT MATRICES
	glm::vec3 position(0.f);
	glm::vec3 rotation(0.f);
	glm::vec3 scale(1.f);

	glm::mat4 ModelMatrix(1.f);
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	ModelMatrix = glm::scale(ModelMatrix, scale);

	glm::vec3 camPosition(0.f, 0.f, 1.f);
	glm::vec3 worldUp(0.f, 1.f, 0.f);
	glm::vec3 camFront(0.f, 0.f, -1.f);
	glm::mat4 ViewMatrix(1.f);
	ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

	float fov = 90.0f;
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;
	glm::mat4 ProjectionMatrix(1.0f);

	ProjectionMatrix = glm::perspective(
		glm::radians(fov),
		static_cast<float>(framebufferWidth) / framebufferHeight,
		nearPlane,
		farPlane
	);	



	//LIGHTS
	glm::vec3 lightPos0(0.f, 0.f, 1.f);

	//core_program.use();
	
	core_program.setMat4fv(ModelMatrix, "ModelMatrix");
	core_program.setMat4fv(ViewMatrix, "ViewMatrix");
	core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	core_program.setVec3f(lightPos0, "lightPos0");
	core_program.setVec3f(camPosition, "cameraPos");

	//core_program.unuse();


	//MAIN LOOP




	//OPENGL OPTIONS

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float count = 0.f;
	float pi = 3.14;
	float count2 = 0.0f;
	float trianglePos = 0.00;

	while (!glfwWindowShouldClose(window))
	{
		//UPDATE INPUT
		glfwPollEvents();
		updateInput(window);
		MoveTriangle(window, trianglePos);

		//UPDATE 

		//DRAW
		//CLEAR

		glClearColor(0.0f, 0.0f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			

		//Use program

		//core_program.use();


		//update uniforms
		core_program.set1i(0, "texture0");
				
		core_program.set1i(1, "texture1");

		
		
		//Material 0
		material0.sendToShader(core_program);


		//Move Rotate Scale
		//if (cos(count*pi) >= 0)
		/*{
			position.x = cos(count*pi);
			position.y = sin(count*pi);
			count += 0.001f;
		}

		count2 += 0.05f;

		position.z -= -0.001f;

		if (count2 > 20.0f)
		{
			position.z = -10.00f;
			count2 = 10.00f;
		}*/


		/*if (cos(count*pi) < 0)
		{
			position.x += 0.001f;
			position.y += 0.001f;
			count += 0.0005f;
		}*/

		//rotation.y -= 0.01f;
		
		updateInput(window, position, rotation, scale);

		ModelMatrix = glm::mat4(1.f);
		ModelMatrix = glm::translate(ModelMatrix, position);
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		ModelMatrix = glm::scale(ModelMatrix, scale);

		core_program.setMat4fv(ModelMatrix, "ModelMatrix");

		
		
		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

		//ProjectionMatrix = glm::mat4(1.f);
		ProjectionMatrix = glm::perspective(
			glm::radians(fov),
			static_cast<float>(framebufferWidth) / framebufferHeight,
			nearPlane,
			farPlane
		);
		
		core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");
		core_program.use();
		

		//Activate Texture
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture0.getId());
		
		texture0.bind();
		texture1.bind();

		
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture1.getId());



		//Bind vertex array object

		glBindVertexArray(VAO);
		
		
		//Draw
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);


		
		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);



		//End draw
	



}

glfwDestroyWindow(window);
glfwTerminate();
return 0;
	//End of Program
}

