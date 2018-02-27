#ifndef FONTX2_H
#define FONTX2_H

/* FONTX2 struct by AZO */

/* FONTX2 Header common */
typedef struct FONTX2_Header_Common {
	char acSignature[6];
	char acFontName[8];
	unsigned char ucFontWidth;
	unsigned char ucFontHeight;
	unsigned char ucCodeType;
} FONTX2_Header_Common_t;

typedef struct FONTX2_Code {
	unsigned short usStartCode;
	unsigned short usEndCode;
} FONTX2_Code_t;

/* FONTX2 Header ANK */
typedef struct FONTX2_Header_ANK {
	FONTX2_Header_Common_t tCommon;
	const unsigned char* pucFontImage;
} FONTX2_Header_ANK_t;

/* FONTX2 Header FullSize */
typedef struct FONTX2_Header_FullSize {
	FONTX2_Header_Common_t tCommon;
	unsigned char ucBlockCount;
	FONTX2_Code_t* ptCode;
	const unsigned char* pucFontImage;
} FONTX2_Header_FullSize_t;

#endif	/* FONTX2_H */
