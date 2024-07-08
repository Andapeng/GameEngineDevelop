#pragma once
#include "IManager.h"

#include <ft2build.h>
#include <freetype/freetype.h>


class FontManager
	: public IManager
{
public:
	virtual ~FontManager();

	virtual int Initialize() override;
	virtual void Tick() override;
	virtual void Release() override;

	static FontManager* Get();

	int LoadFont(const char* filepathName);
	int LoadCharacter(wchar_t unicode);
private:
	FontManager();
	FT_Library  m_library;   /* handle to library     */
	FT_Face     m_face;      /* handle to face object */

	static FontManager* m_singleFontManager;
};

extern FontManager* g_pFontManager;