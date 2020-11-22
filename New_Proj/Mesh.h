#pragma once

#include<iostream>
#include<vector>
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"


class Mesh
{

private:

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;

	void initVertexData(Vertex* vertexArray, const unsigned& nrOfVertices, 
		GLuint* indexArray, const unsigned& nrOfIndices)
	{
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertices.push_back(vertexArray[i]);
		}

		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indices.push_back(indexArray[i]);
		}
	}

	void initVAO()
	{
		
		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA
		
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		//GEN EBO AND BIND AND SEND DATA
		
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);


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

public:

	Mesh(Vertex* vertexArray, const unsigned& nrOfVertices,
		GLuint* indexArray, const unsigned& nrOfIndices)
	{
		this->initVertexData(vertexArray, nrOfVertices, indexArray, nrOfIndices);
		this->initVAO();
		this->initModelMatrix();
	}

	~Mesh()
	{

		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);
	}

	void update()
	{

	}
	
	void render(Shader* shader)

	{
		
		this->updateUniforms(shader);

		shader->use();

		glBindVertexArray(this->VAO);


		//Draw
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	}


};

