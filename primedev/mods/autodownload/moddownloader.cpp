#include "moddownloader.h"
#include "util/utils.h"
#include "squirrel/squirrel.h"
#include "mods/modmanager.h"

ADD_SQFUNC(
	"bool", NSIsModDownloadable, "string name, string version", "", ScriptContext::SERVER | ScriptContext::CLIENT | ScriptContext::UI)
{
	g_pSquirrel<context>->newarray(sqvm, 0);

	g_pSquirrel<context>->pushbool(sqvm, false);

	return SQRESULT_NOTNULL;
}

ADD_SQFUNC("void", NSDownloadMod, "string name, string version", "", ScriptContext::SERVER | ScriptContext::CLIENT | ScriptContext::UI)
{
	const SQChar* modName = g_pSquirrel<context>->getstring(sqvm, 1);
	const SQChar* modVersion = g_pSquirrel<context>->getstring(sqvm, 2);

	return SQRESULT_NULL;
}

// should never be read as we dont even have a server browser lmao
ADD_SQFUNC("ModInstallState", NSGetModInstallState, "", "", ScriptContext::SERVER | ScriptContext::CLIENT | ScriptContext::UI)
{
	g_pSquirrel<context>->pushnewstructinstance(sqvm, 4);

	// state
	g_pSquirrel<context>->pushinteger(sqvm, -1);
	g_pSquirrel<context>->sealstructslot(sqvm, 0);

	// progress
	g_pSquirrel<context>->pushinteger(sqvm, 1);
	g_pSquirrel<context>->sealstructslot(sqvm, 1);

	// total
	g_pSquirrel<context>->pushinteger(sqvm, 1);
	g_pSquirrel<context>->sealstructslot(sqvm, 2);

	// ratio
	g_pSquirrel<context>->pushfloat(sqvm, 1.0f);
	g_pSquirrel<context>->sealstructslot(sqvm, 3);

	return SQRESULT_NOTNULL;
}
