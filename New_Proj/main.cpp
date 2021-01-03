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

