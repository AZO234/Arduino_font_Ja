/* === FONTX2 system === */

#ifndef FONTX2_SYSTEM_H
#define FONTX2_SYSTEM_H

#include "FONTX2.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FONTX2_Font {
	unsigned char ucHeight;
	unsigned int uiStyle;
	FONTX2_Header_ANK_t* ptANK;
	FONTX2_Header_FullSize_t* ptFullSize;	
} FONTX2_Font_t;

typedef struct FONTX2_FontSelect {
	unsigned char ucHeight;
	unsigned int uiStyle;
} FONTX2_FontSelect_t;

typedef struct FONTX2_System {
	unsigned char ucFontCount;
	FONTX2_Font_t* ptFonts;	
} FONTX2_System_t;

extern char FONTX2_System_IsFontExist(const FONTX2_System_t* ptSystem, const FONTX2_FontSelect_t* ptFontSelect);
extern int FONTX2_System_GetFontImage(unsigned char* pucFontImage, const FONTX2_System_t* ptSystem, const FONTX2_FontSelect_t* ptFontSelect, const char* strString);

#ifdef __cplusplus
}
#endif

#endif	/* FONTX2_SYSTEM_H */

