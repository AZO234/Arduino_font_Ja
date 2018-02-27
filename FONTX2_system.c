#include <stdio.h>
#if defined(__AVR__)
#include "avr/pgmspace.h"
#elif defined(ESP8266)
#include <pgmspace.h>
#endif
#include <Arduino.h>
#include "FONTX2_system.h"
#include "JaCode.h"

char FONTX2_System_IsFontExist(const FONTX2_System_t* ptSystem, const FONTX2_FontSelect_t* ptFontSelect) {
	unsigned char ucCount;

	if(ptSystem == NULL || ptFontSelect == NULL) {
		return -1;
	}
	if(ptSystem->ucFontCount == 0) {
		return -1;
	}

	for(ucCount = 0; ucCount < ptSystem->ucFontCount; ucCount++) {
		if(ptFontSelect->ucHeight == ptSystem->ptFonts[ucCount].ucHeight && ptFontSelect->uiStyle == ptSystem->ptFonts[ucCount].uiStyle) {
			return ucCount;
		}
	}

	return -1;
}

int FONTX2_System_GetFontImage(unsigned char* pucFontImage, const FONTX2_System_t* ptSystem, const FONTX2_FontSelect_t* ptFontSelect, const char* strString) {
	char cFontNo;
	unsigned char ucBlock, ucData, ucLineSize;
	unsigned short usStartCode, usEndCode, usCode;
	unsigned int uiGlyphCount;
	unsigned char aucCode[2];

	if(pucFontImage == NULL || ptSystem == NULL || ptFontSelect == NULL) {
		return 0;
	}

	cFontNo = FONTX2_System_IsFontExist(ptSystem, ptFontSelect);
	if(cFontNo < 0) {
		return 0;
	}
	if(ptSystem->ptFonts[cFontNo].ptANK == NULL && ptSystem->ptFonts[cFontNo].ptFullSize == NULL) {
		return 0;
	}

	if(ptSystem->ptFonts[cFontNo].ptANK != NULL && ptSystem->ptFonts[cFontNo].ptFullSize == NULL) {
		if(ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontWidth % 8 == 0) {
			ucLineSize = ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontWidth / 8;
		} else {
			ucLineSize = ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontWidth / 8 + 1;
		}
#if defined(__AVR__)
		for(ucData = 0; ucData < ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontHeight * ucLineSize; ucData++) {
			pucFontImage[ucData] = pgm_read_byte_near(ptSystem->ptFonts[cFontNo].ptANK->pucFontImage + (unsigned char)strString[0] * ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontHeight * ucLineSize + ucData);
		}
#elif defined(ESP8266)
		memcpy_P(pucFontImage, &ptSystem->ptFonts[cFontNo].ptANK->pucFontImage[(unsigned char)strString[0] * ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontHeight * ucLineSize], ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontHeight * ucLineSize);
#else
		for(ucData = 0; ucData < ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontHeight * ucLineSize; ucData++) {
			pucFontImage[ucData] = ptSystem->ptFonts[cFontNo].ptANK->pucFontImage[(unsigned char)strString[0] * ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontHeight * ucLineSize + ucData];
		}
#endif
		return 1;
	}

	aucCode[0] = strString[0];
	aucCode[1] = strString[1];
	usCode = 0;
	((unsigned char*)&usCode)[0] = strString[1];
	((unsigned char*)&usCode)[1] = strString[0];
	if(JaCode_DetectType(2, aucCode) == 1) {
		uiGlyphCount = 0;
		if(ptSystem->ptFonts[cFontNo].ptFullSize->tCommon.ucFontWidth % 8 == 0) {
			ucLineSize = ptSystem->ptFonts[cFontNo].ptFullSize->tCommon.ucFontWidth / 8;
		} else {
			ucLineSize = ptSystem->ptFonts[cFontNo].ptFullSize->tCommon.ucFontWidth / 8 + 1;
		}
		for(ucBlock = 0; ucBlock < ptSystem->ptFonts[cFontNo].ptFullSize->ucBlockCount; ucBlock++) {
#if defined(__AVR__)
			usStartCode = pgm_read_word_near(&(ptSystem->ptFonts[cFontNo].ptFullSize->ptCode[ucBlock].usStartCode));
			usEndCode = pgm_read_word_near(&(ptSystem->ptFonts[cFontNo].ptFullSize->ptCode[ucBlock].usEndCode));
#elif defined(ESP8266)
			usStartCode = usEndCode = 0;
			memcpy_P(&usStartCode, &(ptSystem->ptFonts[cFontNo].ptFullSize->ptCode[ucBlock].usStartCode), 2);
			memcpy_P(&usEndCode, &(ptSystem->ptFonts[cFontNo].ptFullSize->ptCode[ucBlock].usEndCode), 2);
#else
			usStartCode = ptSystem->ptFonts[cFontNo].ptFullSize->ptCode[ucBlock].usStartCode;
			usEndCode = ptSystem->ptFonts[cFontNo].ptFullSize->ptCode[ucBlock].usEndCode;
#endif
			if(usCode >= usStartCode && usCode <= usEndCode) {
				uiGlyphCount += usCode - usStartCode;
#if defined(__AVR__)
				for(ucData = 0; ucData < ptSystem->ptFonts[cFontNo].ptFullSize->tCommon.ucFontHeight * ucLineSize; ucData++) {
					pucFontImage[ucData] = pgm_read_byte_near(ptSystem->ptFonts[cFontNo].ptFullSize->pucFontImage + uiGlyphCount * ptSystem->ptFonts[cFontNo].ptFullSize->tCommon.ucFontHeight * ucLineSize + ucData);
				}
#elif defined(ESP8266)
				memcpy_P(pucFontImage, &ptSystem->ptFonts[cFontNo].ptFullSize->pucFontImage[uiGlyphCount * ptSystem->ptFonts[cFontNo].ptFullSize->tCommon.ucFontHeight * ucLineSize], ptSystem->ptFonts[cFontNo].ptFullSize->tCommon.ucFontHeight * ucLineSize);
#else
				for(ucData = 0; ucData < ptSystem->ptFonts[cFontNo].ptFullSize->tCommon.ucFontHeight * ucLineSize; ucData++) {
					pucFontImage[ucData] = ptSystem->ptFonts[cFontNo].ptFullSize->pucFontImage[uiGlyphCount * ptSystem->ptFonts[cFontNo].ptFullSize->tCommon.ucFontHeight * ucLineSize + ucData];
				}
#endif
				return 2;
			}
			uiGlyphCount += usEndCode - usStartCode + 1;
		}
	} else {
		if(ptSystem->ptFonts[cFontNo].ptANK == NULL) {
			return 0;
		}
		if(ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontWidth % 8 == 0) {
			ucLineSize = ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontWidth / 8;
		} else {
			ucLineSize = ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontWidth / 8 + 1;
		}
#if defined(__AVR__)
		for(ucData = 0; ucData < ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontHeight * ucLineSize; ucData++) {
			pucFontImage[ucData] = pgm_read_byte_near(ptSystem->ptFonts[cFontNo].ptANK->pucFontImage + (unsigned char)strString[0] * ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontHeight * ucLineSize + ucData);
		}
#elif defined(ESP8266)
		memcpy_P(pucFontImage, &ptSystem->ptFonts[cFontNo].ptANK->pucFontImage[(unsigned char)strString[0] * ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontHeight * ucLineSize], ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontHeight * ucLineSize);
#else
		for(ucData = 0; ucData < ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontHeight * ucLineSize; ucData++) {
			pucFontImage[ucData] = ptSystem->ptFonts[cFontNo].ptANK->pucFontImage[(unsigned char)strString[0] * ptSystem->ptFonts[cFontNo].ptANK->tCommon.ucFontHeight * ucLineSize + ucData];
		}
#endif
		return 1;
	}

	return 0;
}
