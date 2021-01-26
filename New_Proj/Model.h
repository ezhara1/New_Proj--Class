#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "Obj_loader.h"


class Model
{
private:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	std::vector<Mesh*> meshes;
	glm::vec3 position;

	void updateUniforms()
	{

	}


public:
	Model(glm::vec3 position,
		Material* material,
		Texture* orTexDif,
		Texture* orTexSpec,
		std::vector<Mesh*>& meshes)

	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = orTexDif;
		this->overrideTextureSpecular = orTexSpec;
	
		for (auto* i : meshes)
		{
			this->meshes.push_back(new Mesh(*i));
		}

		for (auto& i : this->meshes)
		{
			i->move(this->position);
			i->setOrigin(this->position);
		}

	}

	//OBJ File loaded model

	Model(
		glm::vec3 position,
		Material* material,
		Texture* orTexDif,
		Texture* orTexSpec,
		const char* objFile
	)

	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = orTexDif;
		this->overrideTextureSpecular = orTexSpec;

		std::vector<Vertex> mesh = loadOBJ(objFile);
		this->meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)));

	

		for (auto& i : this->meshes)
		{
			i->move(this->position);
			i->setOrigin(this->position);
		}

	}

	~Model()
	{
		for (auto*& i : this->meshes)
			delete i;
	}

	//Functions

	void update()
	{


	}

	void render(Shader* shader)
	{
		//Update the uniforms
		this->updateUniforms();

		// Update uniforms
		this->material->sendToShader(*shader);

		//Use a program
		shader->use();

		//Activate texture
		this->overrideTextureDiffuse->bind(0);
		this->overrideTextureSpecular->bind(1);

		//Draw
		for (auto& i : this->meshes)
		{
		
		this->overrideTextureDiffuse->bind(0);
		this->overrideTextureSpecular->bind(1);

		i->render(shader);
	}

		//this->meshes[0]->rotate(glm::vec3(0.00f, 0.05f, 0.00f));

		//this->meshes[MESH_QUAD]->render(this->shaders[SHADER_CORE_PROGRAM]);

	}

	void rotate(const glm::vec3 rotation)
	{
		for (auto& i : this->meshes)
			i->rotate(rotation);
	}

};
