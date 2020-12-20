#include "Game.h"

void Game::update()
{
	//Update INput ---
	glfwPollEvents();
}

void Game::render()
{		
	//UPDATE INPUT

	//updateInput(window);

	//DRAW
	//CLEAR

	glClearColor(0.0f, 0.0f, 0.0f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//Use program

	//update uniforms
	this->shaders[SHADER_CORE_PROGRAM]->set1i(this->textures[TEX_EARTH0]->getTextureUnit(), "texture0");
	this->shaders[SHADER_CORE_PROGRAM]->set1i(this->textures[TEX_WALL1]->getTextureUnit(), "texture1");
	this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	ProjectionMatrix = glm::perspective(
		glm::radians(fov),
		static_cast<float>(framebufferWidth) / framebufferHeight,
		nearPlane,
		farPlane
	);

	
	
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->use();



	this->textures[TEX_EARTH0]->bind();
	this->textures[TEX_WALL1]->bind();

	this->meshes[MESH_QUAD]->render(this->shaders[SHADER_CORE_PROGRAM]);
	

	glfwSwapBuffers(window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Game::framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}


void Game::initGLFW()
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR:: GLFW INIT FAIL";
		glfwTerminate();

	}

}

void Game::initGLEW()
{
	glewExperimental = GL_TRUE;

	//ERROR
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR MAIN.CPP GLEW FAILED" << "\n";
		glfwTerminate();
	}

}

void Game::OpenGLOptions()
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void Game::initMatrices()

{
	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);
}


void Game::initWindow(const char* title,
	bool resizable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE)

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_WINDOW something failed";
		glfwTerminate();
	}

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwSetFramebufferSizeCallback(this->window, Game::framebuffer_resize_callback);

	glfwMakeContextCurrent(this->window);

}

void Game::initShaders()
{

	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"Resource/vertex_core.shader", "Resource/fragment_core.shader"));

}

void Game::initTextures()
{
	this->textures.push_back(new Texture("Resource/textures/earth.png", STBI_rgb_alpha, 0));
	this->textures.push_back(new Texture("Resource/textures/wall.jpg", STBI_rgb, 1));
}

void Game::initMaterials()
{
	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), this->textures[TEX_EARTH0]->getTextureUnit(), this->textures[TEX_WALL1]->getTextureUnit()));

}

void Game::initMeshes()
{
	this->meshes.push_back(
		new Mesh(&Quad(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f))
	);
}

void Game::initLights()
{
	this->lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}

void Game::initUniforms()
{

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix,"ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "cameraPos");



	
}


Game::Game(
	const char* title,
	const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
	const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
	bool resizable
)
	: WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR), 
	GL_VERSION_MINOR(GL_VERSION_MINOR)
{
	this->window = nullptr;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;

	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);

	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;
	glm::mat4 ProjectionMatrix(1.f);

	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		nearPlane,
		farPlane
	);

	
	this->initGLFW();
	this->initWindow(title, resizable);
	this->initGLEW();
	this->OpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initMeshes();
	this->initLights();
	this->initUniforms();

}

Game::~Game()
{

	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < this->shaders.size(); i++)
		delete this->shaders[i];

	for (size_t i = 0; i < this->shaders.size(); i++)
		delete this->textures[i];

	for (size_t i = 0; i < this->materials.size(); i++)
		delete this->materials[i];

	for (size_t i = 0; i < this->meshes.size(); i++)
		delete this->meshes[i];

	for (size_t i = 0; i < this->lights.size(); i++)
		delete this->lights[i];


}

int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

void Game::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}
