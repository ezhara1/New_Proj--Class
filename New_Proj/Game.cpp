#include "Game.h"

void Game::update()
{
	this->updateDt();
	this->updateInput();
	
	//this->meshes[0]->rotate(glm::vec3(0.f, 0.05f, 0.f));

	this->models[0]->rotate(glm::vec3(0.f, 0.01f, 0.f));
	//this->models[1]->rotate(glm::vec3(0.f, 0.01f, 0.f));
	//this->models[2]->rotate(glm::vec3(0.f, 0.01f, 0.f));


	/*std::cout << "DT: " << this->dt << "\n"
		<< "Mouse offsetX: " << this->mouseOffsetX << " Mouse offsetY:" << this->mouseOffsetY << "\n";*/

}

void Game::updateDt()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;

	
}


void Game::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
			
	}


	//calc offset

	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY;

	//Set last X and Y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;


}


void Game::updateKeyboardInput()
{

	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwWindowShouldClose(this->window);
	}


	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->camera.move(this->dt, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camera.move(this->dt, BACKWARD);

	}

	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camera.move(this->dt, LEFT);

	}

	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camera.move(this->dt, RIGHT);
	}

	if (glfwGetKey(this->window, GLFW_KEY_C) == GLFW_PRESS)
	{
		this->camPosition.y += 0.01f;

	}

	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		this->camPosition.y -= 0.01f;
	}



}

void Game::updateInput()
{
	glfwPollEvents();
	
	this->updateKeyboardInput();
	this->updateMouseInput();

	this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);
	
}

void Game::render()
{		
	//UPDATE INPUT

	//updateInput(window);

	//DRAW
	//CLEAR

	glClearColor(0.0f, 0.0f, 0.0f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	
	////update Uniforms

	this->updateUniforms();

	//this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);


	////Use program
	//
	//this->shaders[SHADER_CORE_PROGRAM]->use();



	//this->textures[TEX_EARTH0]->bind(1);
	//this->textures[TEX_WALL1]->bind(0);

	//this->meshes[MESH_QUAD]->render(this->shaders[SHADER_CORE_PROGRAM]);
	
	for (auto&i : this->models)			
		i->render(this->shaders[SHADER_CORE_PROGRAM]);

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
	this->textures.push_back(new Texture("Resource/textures/earth.png", STBI_rgb_alpha));
	this->textures.push_back(new Texture("Resource/textures/wall.jpg", STBI_rgb));
}

void Game::initMaterials()
{
	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(2.f), 0, 1));

}


void Game::initOBJModels()
{
	

}

void Game::initModels()
{
	std::vector<Mesh*> meshes;

	

	/*meshes.push_back(
	new Mesh(&Pyramid(),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f))
		);
	meshes.push_back(
		new Mesh(
			&Quad(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);*/

	/*this->models.push_back(new Model(
		glm::vec3(0.f),
		this->materials[0],
		this->textures[TEX_WALL1],
		this->textures[TEX_WALL1],
		meshes
	));

	this->models.push_back(new Model(
		glm::vec3(0.f, 1.f, 1.f),
		this->materials[0],
		this->textures[TEX_WALL1],
		this->textures[TEX_WALL1],
		meshes
	));*/

	this->models.push_back(new Model(
		glm::vec3(2.f, 0.f, 2.f),
		this->materials[0],
		this->textures[TEX_WALL1],
		this->textures[TEX_WALL1],
		"Resource/OBJ files/teddy.obj"
	));

	for (auto*& i : meshes)
		delete i;

	meshes.clear();
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

void Game::updateUniforms()
{

	//Update view matrix (camera)

	this->ViewMatrix = this->camera.getViewMatrix();

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");


	//update uniforms

	//this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	
	
	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);



	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");
}


Game::Game(
	const char* title,
	const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
	const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
	bool resizable
)
	: WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR), 
	GL_VERSION_MINOR(GL_VERSION_MINOR),
	camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))

{
	this->window = nullptr;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;

	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);

	//this->ViewMatrix = glm::mat4(1.f);
	//this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

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

	this->dt = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;
	
	this->lastMouseX = 0.0;
	this->lastMouseY = 0.0;
	this->mouseX = 0.0;
	this->mouseY = 0.0;
	this->mouseOffsetX = 0.0;
	this->mouseOffsetY = 0.0;
	this->firstMouse = true;
	
	this->initGLFW();
	this->initWindow(title, resizable);
	this->initGLEW();
	this->OpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initOBJModels();
	
	this->initModels();
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

	for (auto*& i : this->models)
		delete i;

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

