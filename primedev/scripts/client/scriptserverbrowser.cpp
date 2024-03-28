#include "squirrel/squirrel.h"
#include "server/auth/serverauthentication.h"
#include "engine/r2engine.h"
#include "client/r2client.h"

// functions for viewing server browser

ADD_SQFUNC("void", NSRequestServerList, "", "", ScriptContext::UI)
{
	return SQRESULT_NULL;
}

ADD_SQFUNC("bool", NSIsRequestingServerList, "", "", ScriptContext::UI)
{
	g_pSquirrel<context>->pushbool(sqvm, false);
	return SQRESULT_NOTNULL;
}

ADD_SQFUNC("bool", NSMasterServerConnectionSuccessful, "", "", ScriptContext::UI)
{
	g_pSquirrel<context>->pushbool(sqvm, false);
	return SQRESULT_NOTNULL;
}

ADD_SQFUNC("int", NSGetServerCount, "", "", ScriptContext::UI)
{
	g_pSquirrel<context>->pushinteger(sqvm, 0);
	return SQRESULT_NOTNULL;
}

ADD_SQFUNC("void", NSClearRecievedServerList, "", "", ScriptContext::UI)
{
	return SQRESULT_NULL;
}

// functions for authenticating with servers

ADD_SQFUNC("void", NSTryAuthWithServer, "int serverIndex, string password = ''", "", ScriptContext::UI)
{
	return SQRESULT_NULL;
}

ADD_SQFUNC("bool", NSIsAuthenticatingWithServer, "", "", ScriptContext::UI)
{
	g_pSquirrel<context>->pushbool(sqvm, false);
	return SQRESULT_NOTNULL;
}

ADD_SQFUNC("bool", NSWasAuthSuccessful, "", "", ScriptContext::UI)
{
	g_pSquirrel<context>->pushbool(sqvm, false);
	return SQRESULT_NOTNULL;
}

ADD_SQFUNC("void", NSConnectToAuthedServer, "", "", ScriptContext::UI)
{
	return SQRESULT_NULL;
}

ADD_SQFUNC("void", NSTryAuthWithLocalServer, "", "", ScriptContext::UI)
{
	// do auth request
	//g_pMasterServerManager->AuthenticateWithOwnServer(g_pLocalPlayerUserID, g_pMasterServerManager->m_sOwnClientAuthToken);

	return SQRESULT_NULL;
}

ADD_SQFUNC("void", NSCompleteAuthWithLocalServer, "", "", ScriptContext::UI)
{

	return SQRESULT_NULL;
}

ADD_SQFUNC("string", NSGetAuthFailReason, "", "", ScriptContext::UI)
{
	g_pSquirrel<context>->pushstring(sqvm, "This is ronin, dipshit. No MS auth", -1);
	return SQRESULT_NOTNULL;
}

ADD_SQFUNC("array<ServerInfo>", NSGetGameServers, "", "", ScriptContext::UI)
{
	g_pSquirrel<context>->newarray(sqvm, 0);
	return SQRESULT_NOTNULL;
}
