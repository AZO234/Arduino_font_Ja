#include <string.h>
#include <FONTX2_system.h>

extern FONTX2_Header_ANK_t tNaga10K;
extern FONTX2_Header_FullSize_t tElisa;
extern FONTX2_Header_ANK_t tILGH16XB;
extern FONTX2_Header_FullSize_t tILGZ16XB;
extern FONTX2_Header_ANK_t tILMH16XB;
extern FONTX2_Header_FullSize_t tILMZ16XB;

const FONTX2_Font_t atFonts[] = {
	{ 8, 0, &tNaga10K,  &tElisa   },
	{16, 0, &tILGH16XB, &tILGZ16XB},
	{16, 1, &tILMH16XB, &tILMZ16XB},
};

const FONTX2_System_t tFontSystem = {sizeof(atFonts) / sizeof(FONTX2_Font_t), (FONTX2_Font_t*)atFonts};

void FontImageSerialWrite(const FONTX2_FontSelect_t* ptFont, const char* strString) {
  unsigned int uiLength = strlen(strString);
  unsigned int uiLocate = 0;
  unsigned int uiRes;
  int i, j, k;
  unsigned char aucFontImage[32];
  unsigned char ucLineSize;

  while(uiLocate < uiLength) {
    uiRes = FONTX2_System_GetFontImage(aucFontImage, &tFontSystem, ptFont, &strString[uiLocate]);
    if(((ptFont->ucHeight / 2) * uiRes) % 8 == 0) {
      ucLineSize = ((ptFont->ucHeight / 2) * uiRes) / 8;
    } else {
      ucLineSize = ((ptFont->ucHeight / 2) * uiRes) / 8 + 1;
    }
    for(j = 0; j < ptFont->ucHeight; j++) {
      for(i = 0; i < (ptFont->ucHeight / 2) * uiRes; i++) {
        if(((aucFontImage[j * ucLineSize + i / 8] >> (7 - (i % 8))) & 0x1) == 0) {
          Serial.write("  ");
        } else {
          Serial.write("@@");
        }
      }
      Serial.write("\n");
    }
    Serial.write("\n");
    uiLocate += uiRes;
  }
}

void setup() {
  // put your setup code here, to run once:
  unsigned int uiLocate;
  char strString[] = "\x8C\xE1\x94\x79\x82\xCD\x94\x4C\x82\xC5\x82\xA0\x82\xE9";
  FONTX2_FontSelect tFont = {8, 0};
  
  Serial.begin(115200);
  delay(10);

  FontImageSerialWrite(&tFont, strString);
}

void loop() {
  // put your main code here, to run repeatedly:

}
