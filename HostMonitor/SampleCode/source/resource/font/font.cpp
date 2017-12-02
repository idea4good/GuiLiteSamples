#include "core_include/api.h"
#include "core_include/resource_type.h"

extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_8_11;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_9B_12;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_10B_13;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_12_16;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_13B_17;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_15B_20;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_17B_23;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_26B_35;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_40B_53;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_64B_85;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_104B_139;


const GUI_FONT *font_select(const GUI_FONT *font_gbk,const GUI_FONT *font_turkish)
{
	LANGUAGE_TYPE language = ENGLISH;
	const GUI_FONT *font = NULL;

	switch(language){
	case ENGLISH:
	case CHINESE:
	//case SPANISH:
		font = font_gbk;
		break;
	//case TURKISH:
		font = font_turkish;
		break;
	default:
		break;
	}
	return font;
}

const GUI_FONT *font_language_s()
{
	return font_select(&GUI_FontHZ_Arial_Narrow_8_11,NULL);
}

const GUI_FONT * font_language_sb()
{
	return font_select(&GUI_FontHZ_Arial_Narrow_9B_12,NULL);
}

const GUI_FONT * font_language_sbm()
{
	return font_select(&GUI_FontHZ_Arial_Narrow_10B_13,NULL);
}

const GUI_FONT * font_language_smb()
{
	return font_select(&GUI_FontHZ_Arial_Narrow_12_16,NULL);
}

const GUI_FONT * font_language_smb_aa()
{
	return font_select(&GUI_FontHZ_Arial_Narrow_13B_17,NULL);
}

const GUI_FONT * font_language_mb_aa()
{
	return font_select(&GUI_FontHZ_Arial_Narrow_15B_20,NULL);
}

const GUI_FONT * font_language_mmb_aa()
{
	return font_select(&GUI_FontHZ_Arial_Narrow_17B_23,NULL);
}

const GUI_FONT * font_language_mb()
{
	return font_select(&GUI_FontHZ_Arial_Narrow_26B_35,NULL);
}

const GUI_FONT * font_language_llb()
{
	return font_select(&GUI_FontHZ_Arial_Narrow_40B_53,NULL);
}

const GUI_FONT * font_language_lllb()
{
	return font_select(&GUI_FontHZ_Arial_Narrow_64B_85,NULL);
}

const GUI_FONT * font_language_llllb()
{
	return font_select(&GUI_FontHZ_Arial_Narrow_104B_139,NULL);
}
