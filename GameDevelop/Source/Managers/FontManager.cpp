#include "FontManager.h"
#include "ResourceManager.h"
#include <iostream>
#include <GLAD/glad.h>

#include <SFML/Graphics.hpp>
#include "../RHI/Character.h"

#include <Eigen/Core>

FontManager* FontManager::mSingleFontManager = nullptr;
int FontManager::Initialize()
{


	FT_Error error = FT_Init_FreeType(&mLibrary);

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
	FT_Done_Face(mFace);
	FT_Done_FreeType(mLibrary);
	delete mSingleFontManager;
}

FontManager* FontManager::Get()
{
	if (mSingleFontManager == nullptr)
	{
		mSingleFontManager = new FontManager;
	}
	return mSingleFontManager;
}

int FontManager::LoadFont(const char* filepathName)
{
	FT_Error error = FT_New_Face(mLibrary, filepathName, 0, &mFace);
	
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
	FT_Set_Pixel_Sizes(mFace, 0, 48);

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
	if (FT_Load_Char(mFace, unicode, FT_LOAD_RENDER))
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
		mFace->glyph->bitmap.width,
		mFace->glyph->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		mFace->glyph->bitmap.buffer
	);

	// Set texture options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Now store character for later use
	Character character = {
		texture,
		Eigen::Vector2i(mFace->glyph->bitmap.width, mFace->glyph->bitmap.rows),
		Eigen::Vector2i(mFace->glyph->bitmap_left, mFace->glyph->bitmap_top),
		mFace->glyph->advance.x
	};
	ResourceManager::Get()->LoadCharacter(unicode, character);
	glBindTexture(GL_TEXTURE, 0);
	return 0;
}
