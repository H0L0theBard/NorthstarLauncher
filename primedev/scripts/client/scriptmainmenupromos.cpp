#include "squirrel/squirrel.h"

// mirror this in script
enum eMainMenuPromoDataProperty
{
	newInfoTitle1,
	newInfoTitle2,
	newInfoTitle3,

	largeButtonTitle,
	largeButtonText,
	largeButtonUrl,
	largeButtonImageIndex,

	smallButton1Title,
	smallButton1Url,
	smallButton1ImageIndex,

	smallButton2Title,
	smallButton2Url,
	smallButton2ImageIndex
};
ADD_SQFUNC("void", NSRequestCustomMainMenuPromos, "", "", ScriptContext::UI)
{
	//g_pMasterServerManager->RequestMainMenuPromos();
	return SQRESULT_NULL;
}

ADD_SQFUNC("bool", NSHasCustomMainMenuPromoData, "", "", ScriptContext::UI)
{
	g_pSquirrel<ScriptContext::UI>->pushbool(sqvm, false);
	return SQRESULT_NOTNULL;
}

ADD_SQFUNC("var", NSGetCustomMainMenuPromoData, "int promoDataKey", "", ScriptContext::UI)
{
	return SQRESULT_NULL;
}
