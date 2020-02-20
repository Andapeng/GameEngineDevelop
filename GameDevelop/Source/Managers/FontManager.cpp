#include "FontManager.h"

#include <iostream>

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
	FT_Done_FreeType(mLibrary);
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

	for (unsigned char c = 0; c < 128; c++)
	{
		if (FT_Load_Char(mFace, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
	}

	FT_Done_Face(mFace);
	return 0;
}

int FontManager::LoadCharacter()
{
	return 0;
}
