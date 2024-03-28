#include "squirrel/squirrel.h"
#include "engine/r2engine.h"
#include "client/r2client.h"

ADD_SQFUNC("bool", NSIsMasterServerAuthenticated, "", "", ScriptContext::UI)
{
	g_pSquirrel<context>->pushbool(sqvm, false);
	return SQRESULT_NOTNULL;
}

/*
global struct MasterServerAuthResult
{
	bool success
	string errorCode
	string errorMessage
}
*/

ADD_SQFUNC("MasterServerAuthResult", NSGetMasterServerAuthResult, "", "", ScriptContext::UI)
{
	g_pSquirrel<context>->pushnewstructinstance(sqvm, 3);

	g_pSquirrel<context>->pushbool(sqvm, false);
	g_pSquirrel<context>->sealstructslot(sqvm, 0);

	g_pSquirrel<context>->pushstring(sqvm, "500", -1);
	g_pSquirrel<context>->sealstructslot(sqvm, 1);

	g_pSquirrel<context>->pushstring(sqvm, "This is ronin, dipshit. No MS authentication.", -1);
	g_pSquirrel<context>->sealstructslot(sqvm, 2);

	return SQRESULT_NOTNULL;
}
