#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include "glew.h"
#include "glfw3.h"

#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <stb_image/stb_image.h>



class Texture
{
private:
	GLuint id;
	

public:
	
	
	Texture(char* fileName, int pic_type) 
	{

		int image_width = 0;
		int image_height = 0;
		int nrofChannels = 0;
		
		
		unsigned char* image = stbi_load(fileName, &image_width, &image_height, &nrofChannels, pic_type);

		
		glGenTextures(1, &this->id);
		glBindTexture(GL_TEXTURE_2D, this->id);


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
		stbi_image_free(image);


	}

	~Texture()
	{

	}


	GLuint getId() { return this->id; }

	void bind( const GLint texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit );
		glBindTexture(GL_TEXTURE_2D, this->id);

	}

	

};