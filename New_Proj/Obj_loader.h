#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>

//GLEW
#include<glew.h>

//GLFW
#include <glfw3.h>

#include<glm.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

#include"Vertex.h"


static std::vector<Vertex> loadOBJ(const char* file_name)
{
	//Vertex Portions
	std::vector<glm::fvec3> vertex_positions;
	std::vector<glm::fvec2> vertex_texcoords;
	std::vector<glm::fvec3> vertex_normals;

	//Face vectors
	std::vector<GLint> vertex_position_indices;
	std::vector<GLint> vertex_texcoord_indices;
	std::vector<GLint> vertex_normal_indices;

	std::vector<Vertex> vertices;
	
	std::stringstream ss;
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	GLint temp_glint = 0;


	if (!in_file.is_open())
	{
		throw "ERROR::OBJLOADER::Could not open file.";

	}

	while (std::getline(in_file, line))
	{
		
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#")
		{

		}
		else if (prefix == "o")
		{

		}
		else if (prefix == "use_mtl")
		{

		}
		else if (prefix == "v") // Vertex position
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_positions.push_back(temp_vec3);

		}
		else if (prefix == "vt")
		{
			ss >> temp_vec2.x >> temp_vec2.y;
			vertex_texcoords.push_back(temp_vec2);
		}
		else if (prefix == "vn")
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normals.push_back(temp_vec3);
		}
		else if (prefix == "f")
		{
			
			int counter = 0;
			while (ss >> temp_glint)
			{
				if (counter == 0)
					vertex_position_indices.push_back(temp_glint);
				else if (counter == 1)
					vertex_texcoord_indices.push_back(temp_glint);
				/*else if (counter == 2)
					vertex_normal_indices.push_back(temp_glint);*/

					//Handling characters
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}

				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				
				//Reset the counter
				if (counter > 1)
					counter = 0;

			}

		}
		else
		{

		}

		

		
	}

	//Build final vertex array (mesh)
	vertices.resize(vertex_position_indices.size(), Vertex());

	//Load in all indices
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		vertices[i].position = vertex_positions[vertex_position_indices[i] - 1];
		vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indices[i] - 1];
	//	vertices[i].normal = vertex_normals[vertex_normal_indices[i] - 1];
		vertices[i].color = glm::vec3(1.f, 1.f, 1.f);

	}



	//DEBUG
	//std::cout << line << "\n";
	std::cout << "Nr of Vertices: " << vertices.size() << "\n";


	//Loaded success
	std::cout << "OBJ file loaded!" << "\n";

	return vertices;



}