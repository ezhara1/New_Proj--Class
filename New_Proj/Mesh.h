#pragma once

#include<iostream>
#include<vector>
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Primitive.h"


class Mesh
{

private:

	unsigned nrOfVertices;
	unsigned nrOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;

	

	void initVAO(Vertex* vertexArray, const unsigned& nrOfVertices,
		GLuint* indexArray, const unsigned& nrOfIndices)
	{
		
		//Set variables
		this->nrOfVertices = nrOfVertices;
		this->nrOfIndices = nrOfIndices;

		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA
		
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);

		//GEN EBO AND BIND AND SEND DATA
		
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);


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

	}

	void initModelMatrix()
	{
		this->position = glm::vec3(0.f);
		this->rotation = glm::vec3(0.f);
		this->scale = glm::vec3(1.f);
		
		this->ModelMatrix = glm::mat4(1.f);
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);


	}

	void updateUniforms(Shader* shader)
	{
		
		shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
	}

	void updateModelMatrix()
	{

		this->ModelMatrix = glm::mat4(1.f);
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);

	}

	void initVAO(Primitive* primitive)
	{

		//Set variables
		this->nrOfVertices = primitive->getNrOfVertices();
		this->nrOfIndices = primitive->getNrOfIndices();

		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA

		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), primitive->getVertices(), GL_STATIC_DRAW);

		//GEN EBO AND BIND AND SEND DATA

		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), primitive->getIndices(), GL_STATIC_DRAW);


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

	}

	/*void initModelMatrix()
	{
		this->position = glm::vec3(0.f);
		this->rotation = glm::vec3(0.f);
		this->scale = glm::vec3(1.f);

		this->ModelMatrix = glm::mat4(1.f);
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);


	}*/

	/*void updateUniforms(Shader* shader)
	{

		shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
	}*/

	/*void updateModelMatrix()
	{

		this->ModelMatrix = glm::mat4(1.f);
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);

	}*/

public:

	Mesh(		
		Vertex* vertexArray, const unsigned& nrOfVertices,
		GLuint* indexArray, const unsigned& nrOfIndices,
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f)
	
	)
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;

		this->initVAO(vertexArray, nrOfVertices, indexArray, nrOfIndices);
		//this->initModelMatrix();
		this->updateModelMatrix();
	}

	Mesh(
		Primitive* primitive,
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f)

	)
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;

		this->initVAO(primitive);
		//this->initModelMatrix();
		this->updateModelMatrix();
	}

	~Mesh()
	{

		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);
	}

	//Accessors

	//MOdifiers
	
	void setPosition(const glm::vec3 position)
	{
		this->position = position;
	}

	void setRotation(const glm::vec3 rotation)
	{
		this->rotation = rotation;
	}

	void setScale(const glm::vec3 setScale)
	{
		this->scale = scale;
	}


	//Functions

	void move(const glm::vec3 position)
	{
		this->position += position;
	}

	void rotate(const glm::vec3 rotation)
	{
		this->rotation += rotation;

	}

	void scaleUp(const glm::vec3 scale)
	{
		this->scale += scale;
	}

	void update()
	{

	}
	

	

	void render(Shader* shader)

	{
		//Update uniforms

		this->updateModelMatrix();
		this->updateUniforms(shader);

		shader->use();

		glBindVertexArray(this->VAO);


		//Draw
		glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);
	}


};

