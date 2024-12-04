#include "TextRenderer.h"
#include "../RHI/Shader.h"
#include "../RHI/Texture.h"
#include "../RHI/Character.h"	
#include "../Managers/StateManager.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/GraphicsManager.h"
#include "../Managers/FontManager.h"
#include <cstdlib>
#include <iostream>

#include <GLAD/glad.h>

#include <ft2build.h>
#include <freetype/freetype.h>

int TextRenderer::Initialize()
{
	

	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &textVAO);
	glGenBuffers(1, &textVBO);
	glBindVertexArray(textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return 0;
}

void TextRenderer::RenderText(std::wstring text, float x, float y, float scale, Eigen::Vector3f color)
{
	ResourceManager::Get()->GetShader("text_shader").Use()->SetVector3f("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(textVAO);
	GLfloat max_h = static_cast<GLfloat>(ResourceManager::Get()->GetCharacter('H').GetBearing()(1));
	for (auto c : text)
	{
		auto ch = ResourceManager::Get()->GetCharacter(c);
		if (ch.GetTexture() == 0 && FontManager::Get()->LoadCharacter(c) != -1)
		{
			ch = ResourceManager::Get()->GetCharacter(c);
		}
		GLfloat xpos = x + ch.GetBearing()(0) * scale;
		GLfloat ypos = y + (max_h - ch.GetBearing()(1)) * scale;

		GLfloat w = ch.GetSize()(0) * scale;
		GLfloat h = ch.GetSize()(1) * scale;
		// Update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 1.0 },
			{ xpos + w, ypos	,   1.0, 0.0 },
			{ xpos,     ypos	,   0.0, 0.0 },

			{ xpos	  , ypos + h,   0.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 1.0 },
			{ xpos + w, ypos	,   1.0, 0.0 },
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.GetTexture());
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, textVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.GetAdvance() >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::AddText(std::shared_ptr<Text> Text)
{
	if (Text != nullptr)
	{
		mTexts.push_back(Text);
	}
}

void TextRenderer::OnRender()
{
	for (const auto& text : mTexts)
	{
		RenderText(text->GetText(), text->GetPosX(), text->GetPosY(), text->GetSizeX(), { text->r(), text->g(), text->b() });
	}
}

void TextRenderer::Clear()
{
	mTexts.clear();
}

int TextRenderer::Release()
{
	glDeleteVertexArrays(1,&textVAO);
	glDeleteBuffers(1,&textVBO);
	return 0;
}
