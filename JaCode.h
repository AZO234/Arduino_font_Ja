#ifndef JACODE_H
#define JACODE_H

#define JACODE_BOM_UTF8		"\xEF\xBB\xBF"
#define JACODE_BOM_UTF16_LE	"\xFF\xFE"

/* Return: -1:failed / 0:ASCII / 1:SJIS / 2:UTF-8 / 3:UTF-16 / 4:EUC-JP */
extern int JaCode_DetectType(const unsigned int uiLength, const unsigned char* pucBinary);

/* CodeType: 1:SJIS / 2:UTF-8 / 3:UTF-16 / 4:EUC-JP */
/* Return: Code size */
extern unsigned int JaCode_SearchCode(const unsigned char ucCodeType, const unsigned char* pucCode);

/* OutCode buffer size must be over 6. */
/* CodeType: 1:SJIS / 2:UTF-8 / 3:UTF-16 / 4:EUC-JP */
/* Return: 0:failed / 1:Converted input code size */
extern unsigned int JaCode_ConvertCode(unsigned int* puiOutCodeSize, unsigned char* pucOutCode, const unsigned char ucInCodeType, const unsigned char* pucInCode, const unsigned char ucOutCodeType);

/* CodeType: 1:SJIS / 2:UTF-8 / 3:UTF-16 / 4:EUC-JP */
/* Return: 0:failed / 1:String size */
extern unsigned int JaCode_GetStringSize(const unsigned char ucStringType, const unsigned char* pucString);

/* CodeType: 1:SJIS / 2:UTF-8 / 3:UTF-16 / 4:EUC-JP */
/* Return: 0:failed / 1:Character count */
extern unsigned int JaCode_GetCharCount(const unsigned char ucStringType, const unsigned char* pucString);

/* CodeType: 1:SJIS / 2:UTF-8 / 3:UTF-16 / 4:EUC-JP */
/* Return: 0:failed / 1:Will be converted output string size */
extern unsigned int JaCode_GetConvertStringSize(unsigned int* puiOutStringSize, const unsigned char ucInStringType, const unsigned char* pucInString, const unsigned char ucOutStringType);

/* CodeType: 1:SJIS / 2:UTF-8 / 3:UTF-16 / 4:EUC-JP */
/* Return: 0:failed / 1:Converted input string size */
extern unsigned int JaCode_ConvertString(unsigned int* puiOutStringSize, unsigned char* pucOutString, const unsigned char ucInStringType, const unsigned char* pucInString, const unsigned char ucOutStringType);

/* CodeType: 2:UTF-8 / 3:UTF-16 */
/* Return: 0:failed / 1:Output string size */
extern unsigned int JaCode_AddBOMToString(unsigned char* pucOutString, const unsigned char ucInStringType, const unsigned char* pucInString);

#endif	/* JACODE_H */
