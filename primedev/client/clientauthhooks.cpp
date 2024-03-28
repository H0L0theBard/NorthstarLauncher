#include "core/convar/convar.h"
#include "client/r2client.h"
#include "core/vanilla.h"

AUTOHOOK_INIT()

ConVar* Cvar_ns_has_agreed_to_send_token;

// mirrored in script
const int NOT_DECIDED_TO_SEND_TOKEN = 0;
const int AGREED_TO_SEND_TOKEN = 1;
const int DISAGREED_TO_SEND_TOKEN = 2;

// clang-format off
AUTOHOOK(AuthWithStryder, engine.dll + 0x1843A0,
void, __fastcall, (void* a1))
// clang-format on
{
	// game will call this forever, until it gets a valid auth key
	// so, we need to manually invalidate our key until we're authed with northstar, then we'll allow game to auth with stryder

	AuthWithStryder(a1);
}

char* p3PToken;

// clang-format off
AUTOHOOK(Auth3PToken, engine.dll + 0x183760,
char*, __fastcall, ())
// clang-format on
{
	return Auth3PToken();
}

ON_DLL_LOAD_CLIENT_RELIESON("engine.dll", ClientAuthHooks, ConVar, (CModule module))
{
	AUTOHOOK_DISPATCH()

	p3PToken = module.Offset(0x13979D80).RCast<char*>();

	// this cvar will save to cfg once initially agreed with
	Cvar_ns_has_agreed_to_send_token = new ConVar(
		"ns_has_agreed_to_send_token",
		"0",
		FCVAR_ARCHIVE_PLAYERPROFILE,
		"whether the user has agreed to send their origin token to the northstar masterserver");
}
