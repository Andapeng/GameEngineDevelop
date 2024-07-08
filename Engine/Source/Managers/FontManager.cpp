#include "FontManager.h"
#include "ResourceManager.h"
#include <iostream>
#include <GLAD/glad.h>

#include <SFML/Graphics.hpp>
#include "../RHI/Character.h"

#include <Eigen/Core>

FontManager* FontManager::m_singleFontManager = nullptr;
FontManager::~FontManager()
{
}
int FontManager::Initialize()
{


	FT_Error error = FT_Init_FreeType(&m_library);

	// All functions return a value different than 0 whenever an error occurred
	if (error) 
	{
		// Font Manager Init Failed
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}
	
	return 0;
}

void FontManager::Tick()
{
}

void FontManager::Release()
{
	FT_Done_Face(m_face);
	FT_Done_FreeType(m_library);
	delete m_singleFontManager;
}

FontManager* FontManager::Get()
{
	if (m_singleFontManager == nullptr)
	{
		m_singleFontManager = new FontManager;
	}
	return m_singleFontManager;
}

int FontManager::LoadFont(const char* filepathName)
{
	FT_Error error = FT_New_Face(m_library, filepathName, 0, &m_face);
	
	if (error == FT_Err_Unknown_File_Format)
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		// ... the font file could be openedand read, but it appears
			//... that its font format is unsupported
	}
	else if (error)
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		//... another error code means that the font file could not
			//... be opened or read, or that it is broken...
	}
	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(m_face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned char c = 0; c < 128; c++)
	{
		LoadCharacter(c);
	}
	return 0;
}

int FontManager::LoadCharacter(wchar_t unicode)
{
	if (FT_Load_Char(m_face, unicode, FT_LOAD_RENDER))
	{
		std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
		return -1;
	}
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		m_face->glyph->bitmap.width,
		m_face->glyph->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		m_face->glyph->bitmap.buffer
	);

	// Set texture options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Now store character for later use
	Character character = {
		texture,
		Eigen::Vector2i(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
		Eigen::Vector2i(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
		m_face->glyph->advance.x
	};
	ResourceManager::Get()->LoadCharacter(unicode, character);
	glBindTexture(GL_TEXTURE, 0);
	return 0;
}

FontManager::FontManager()
	: m_library(nullptr)
	, m_face(nullptr)
{
}
