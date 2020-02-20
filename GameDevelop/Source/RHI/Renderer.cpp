#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "../Managers/StateManager.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/GraphicsManager.h"
#include <cstdlib>
#include <iostream>

#include <GLAD/glad.h>

#include <ft2build.h>
#include <freetype/freetype.h>


float vertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};
unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

float texture_vertices[] =
{
	// Pos      // Tex
	   0.0f, 1.0f, 0.0f, 1.0f,
	   1.0f, 0.0f, 1.0f, 0.0f,
	   0.0f, 0.0f, 0.0f, 0.0f,

	   0.0f, 1.0f, 0.0f, 1.0f,
	   1.0f, 1.0f, 1.0f, 1.0f,
	   1.0f, 0.0f, 1.0f, 0.0f
};
unsigned int VBO, VAO, EBO;
unsigned int quadVAO, quadVBO;

void Renderer::Initialize()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
//	Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

//	std::cout << "Previous Matrix: \n" << model << std::endl;

//	Translate(model, Eigen::Vector3f(200.0f, 200.0f, 0.0f));
//	Scale(model, Eigen::Vector3f(200.0f, 200.0f, 1.0f));
	
//	std::cout << "After Matrix: \n" << model << std::endl;
//	InitSpriteRenderer();
}

void Renderer::TestRender()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	
	if (StateManager::Get()->IsGameRuning())
	{
		
		
		ResourceManager::Get()->GetShader("texture_shader").Use();		

		// bind textures on corresponding texture units
		ResourceManager::Get()->GetTexture("dialogbox").Bind();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void Renderer::RenderSprite(Texture2D tex, Eigen::Vector2f pos, Eigen::Vector2f size, float rotate, Eigen::Vector3f color)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (StateManager::Get()->IsGameRuning())
	{
		ResourceManager::Get()->GetShader("sprite_shader").Use();
		Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
		Translate(model, Eigen::Vector3f(200.0f, 200.0f, 0.0f));
		Scale(model, Eigen::Vector3f(200.0f, 200.0f, 1.0f));
		
		ResourceManager::Get()->GetShader("sprite_shader").SetMatrix4f("model", model);
		ResourceManager::Get()->GetShader("sprite_shader").SetVector3f("spriteColor", color);

		glActiveTexture(GL_TEXTURE0);
		// bind textures on corresponding texture units
		tex.Bind();

		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
}

void Renderer::Release()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

int Renderer::InitTextRenderer()
{
	// OpenGL
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	return 0;
}

int Renderer::InitSpriteRenderer()
{
	
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture_vertices), texture_vertices, GL_STATIC_DRAW);

	glBindVertexArray(quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return 0;
}
