#include <chrono>

#include "squirrel/squirrel.h"
#include "modtimer.h"

AUTOHOOK_INIT()

AUTOHOOK(ChangeLevel, server.dll + 0x2772b0, SQRESULT, __fastcall, (HSquirrelVM* sqvm))
{
	std::string targetLevel = g_pSquirrel<ScriptContext::SERVER>->getstring(sqvm, 1);
	spdlog::info(targetLevel);
	std::chrono::time_point point = std::chrono::steady_clock::now();
	// this is only a call since we need it synced.
	// we prefer asynccall because it is more stable.
	SQRESULT result = g_pSquirrel<ScriptContext::UI>->Call("CodeCallback_ShouldChangeLevel", targetLevel);
	spdlog::info((std::chrono::steady_clock::now() - point).count() / 1000 + "ms");
	if (shouldChangeLevel || result == SQRESULT_ERROR)
	{
		shouldChangeLevel = false;
		return ChangeLevel(sqvm);
	}
	return SQRESULT_NULL;
}

AUTOHOOK(LoadSavedGame, engine.dll + 0x166130, void, __fastcall, (CCommand & command))
{
	g_pSquirrel<ScriptContext::UI>->Call("CodeCallback_SetLoadedSaveFile", command.ArgS());
	LoadSavedGame(command);
}

CMemoryAddress inLoadingScreen;
CMemoryAddress tickCount;
CMemoryAddress inCutscene;

ADD_SQFUNC("void", StartClockTime, "", "", ScriptContext::UI)
{
	point = std::chrono::system_clock::now();

	return SQRESULT_NULL;
}
// this is very dumb
ADD_SQFUNC("int", GetCurrentClockTime, "", "", ScriptContext::UI)
{
	std::chrono::time_point point2 = std::chrono::system_clock::now();
	std::chrono::nanoseconds time = point2 - point;
	point = point2;

	int ns = time.count(); // me no trust sqvm to fuckin handle this
	g_pSquirrel<context>->pushinteger(sqvm, ns);
	return SQRESULT_NOTNULL;
}

// fuck you fzzy actualyl please do not touch titanfall 2 ever again
ADD_SQFUNC("bool", FzzyIsInCutscene, "", "", ScriptContext::CLIENT)
{
	if (!inCutscene)
		g_pSquirrel<context>->pushbool(sqvm, false);
	else
	{
		g_pSquirrel<context>->pushbool(sqvm, *inCutscene.RCast<bool*>());
	}
	return SQRESULT_NOTNULL;
}

// fuck you fzzysplitter!!!!1!
ADD_SQFUNC("bool", FzzyInLoadingScreen, "", "", ScriptContext::UI)
{
	if (!inLoadingScreen || !tickCount)
		g_pSquirrel<context>->pushbool(sqvm, false);
	else
	{
		g_pSquirrel<context>->pushbool(sqvm, *inLoadingScreen.RCast<bool*>() || (*tickCount.RCast<int*>() <= 23));
	}
	return SQRESULT_NOTNULL;
}

ADD_SQFUNC("bool", InLoadingScreen, "", "", ScriptContext::UI)
{
	if (!inLoadingScreen || !tickCount)
		g_pSquirrel<context>->pushbool(sqvm, false);
	else
	{
		g_pSquirrel<context>->pushbool(sqvm, *inLoadingScreen.RCast<bool*>());
	}
	return SQRESULT_NOTNULL;
}

ADD_SQFUNC("int", GetEngineTick, "", "", ScriptContext::UI)
{
	if (!inLoadingScreen || !tickCount)
		g_pSquirrel<context>->pushbool(sqvm, false);
	else
	{
		g_pSquirrel<context>->pushbool(sqvm, *tickCount.RCast<bool*>());
	}
	return SQRESULT_NOTNULL;
}

ADD_SQFUNC("void", SetShouldChangeLevel, "", "", ScriptContext::UI)
{
	shouldChangeLevel = true;
	return SQRESULT_NULL;
}	

ON_DLL_LOAD_CLIENT("client.dll", InLoadingScreenAddress, (CModule module))
{
	inLoadingScreen = module.Offset(0xB38C5C); // god help us.
}

ON_DLL_LOAD_CLIENT("engine.dll", TickCountAddress, (CModule module))
{
	tickCount = module.Offset(0x765A24);
	inCutscene = module.Offset(0x111E1B58);
	AUTOHOOK_DISPATCH_MODULE(engine.dll);
}

ON_DLL_LOAD("server.dll", HookChangeLevel, (CModule module))
{
	AUTOHOOK_DISPATCH_MODULE(server.dll);
}
