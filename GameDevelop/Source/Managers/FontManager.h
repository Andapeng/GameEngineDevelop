#pragma once
#include "IManager.h"

#include <ft2build.h>
#include <freetype/freetype.h>


class FontManager
	: public IManager
{
public:
	virtual int Initialize() override;
	virtual void Tick() override;
	virtual void Release() override;

	static FontManager* Get();

	int LoadFont(const char* filepathName);
	int LoadCharacter();
private:
	FT_Library  mLibrary;   /* handle to library     */
	FT_Face     mFace;      /* handle to face object */

	static FontManager* mSingleFontManager;
};