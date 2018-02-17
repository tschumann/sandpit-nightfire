/***
*
*
****/

#include "extdll.h"
#include "enginecallback.h"
#include "util.h"
#include "studio.h"

#include "engine.h"
#include "dll.h"

#include <io.h>

HINSTANCE h_Library = NULL;

enginefuncs_t g_engfuncs;
globalvars_t  *gpGlobals;

#undef DLLEXPORT
#ifdef _WIN32
#define DLLEXPORT __stdcall
#else
#define DLLEXPORT __attribute__ ((visibility("default")))
#endif

extern DLL_FUNCTIONS gFunctionTable;

typedef int (FAR *GETENTITYAPI)(DLL_FUNCTIONS *, int *);
typedef int (FAR *GETNEWDLLFUNCTIONS)(NEW_DLL_FUNCTIONS *, int *);
typedef void (DLLEXPORT *GIVEFNPTRSTODLL)(enginefuncs_t *, globalvars_t *);

// required DLL entry point
BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
	if( fdwReason == DLL_PROCESS_DETACH )
	{
		if( h_Library )
		{
			FreeLibrary(h_Library);
		}
	}

	static_assert(offsetof(edict_t, v) == 288, "edict_t.v must be at offset 288");

	return TRUE;
}

void DLLEXPORT GiveFnptrsToDll( enginefuncs_t* pengfuncsFromEngine, globalvars_t *pGlobals )
{
	// keep a local copy of the engine functions
	memcpy(&g_engfuncs, pengfuncsFromEngine, sizeof(enginefuncs_t));
	// get the globals from the engine
	gpGlobals = pGlobals;

	h_Library = LoadLibrary( "bond/dlls/game.dll" ); // and load the library

	if( h_Library == NULL )
	{
		ALERT( at_error, "Library not found!" );
	}

	// possibly override engine functions - these should probably call
	// the actual engine function as part of their implementation
	pengfuncsFromEngine->pfnMessageBegin = MessageBegin;
	pengfuncsFromEngine->pfnMessageEnd = MessageEnd;
	pengfuncsFromEngine->pfnRegUserMsg = RegUserMsg;

	// pass the possibly overriden engine functions to the game .dll
	(*(GIVEFNPTRSTODLL)GetProcAddress(h_Library, "GiveFnptrsToDll"))(pengfuncsFromEngine, pGlobals);

	return; // finished, interfacing from gamedll to engine complete
}


extern "C" _declspec( dllexport ) int GetEntityAPI( DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion )
{
	// check if engine's pointer is valid and version is correct...
	if( (pFunctionTable == NULL) || (*interfaceVersion != INTERFACE_VERSION) )
	{
		return FALSE;
	}

	// completely populate the function table - each of these calls the game
	// .dll's corresponding function which is obtained from gFunctionTable
	pFunctionTable->pfnGameInit = GameDLLInit;
	pFunctionTable->pfnSpawn = DispatchSpawn;
	pFunctionTable->pfnThink = DispatchThink;
	pFunctionTable->pfnUse = DispatchUse;
	pFunctionTable->pfnTouch = DispatchTouch;
	pFunctionTable->pfnBlocked = DispatchBlocked;
	pFunctionTable->pfnKeyValue = DispatchKeyValue;
	pFunctionTable->pfnSave = DispatchSave;
	pFunctionTable->pfnRestore = DispatchRestore;
	pFunctionTable->pfnSetAbsBox = DispatchObjectCollisionBox;
	pFunctionTable->pfnUnknown1 = Unknown1;
	pFunctionTable->pfnSaveWriteFields = SaveWriteFields;
	pFunctionTable->pfnSaveReadFields = SaveReadFields;
	pFunctionTable->pfnSaveGlobalState = SaveGlobalState;
	pFunctionTable->pfnRestoreGlobalState = RestoreGlobalState;
	pFunctionTable->pfnResetGlobalState = ResetGlobalState;
	pFunctionTable->pfnClientConnect = ClientConnect;
	pFunctionTable->pfnClientDisconnect = ClientDisconnect;
	pFunctionTable->pfnClientKill = ClientKill;
	pFunctionTable->pfnClientPutInServer = ClientPutInServer;
	pFunctionTable->pfnClientCommand = ClientCommand;
	pFunctionTable->pfnClientUserInfoChanged = ClientUserInfoChanged;
	pFunctionTable->pfnServerActivate = ServerActivate;
	pFunctionTable->pfnServerDeactivate = ServerDeactivate;
	pFunctionTable->pfnPlayerPreThink = PlayerPreThink;
	pFunctionTable->pfnPlayerPostThink = PlayerPostThink;
	pFunctionTable->pfnStartFrame = StartFrame;
	pFunctionTable->pfnParmsNewLevel = ParmsNewLevel;
	pFunctionTable->pfnParmsChangeLevel = ParmsChangeLevel;
	pFunctionTable->pfnGetGameDescription = GetGameDescription;
	pFunctionTable->pfnSpectatorConnect = SpectatorConnect;
	pFunctionTable->pfnSpectatorDisconnect = SpectatorDisconnect;
	pFunctionTable->pfnSpectatorThink = SpectatorThink;
	pFunctionTable->pfnSys_Error = Sys_Error;
	pFunctionTable->pfnPM_Move = PM_Move;
	pFunctionTable->pfnPM_Init = PM_Init;
	pFunctionTable->pfnPM_FindTextureType = PM_FindTextureType;
	pFunctionTable->pfnSetupVisibility = SetupVisibility;
	pFunctionTable->pfnUpdateClientData = UpdateClientData;
	pFunctionTable->pfnAddToFullPack = AddToFullPack;
	pFunctionTable->pfnCreateBaseline = CreateBaseline;
	pFunctionTable->pfnRegisterEncoders = RegisterEncoders;
	pFunctionTable->pfnGetWeaponData = GetWeaponData;
	pFunctionTable->pfnCmdStart = CmdStart;
	pFunctionTable->pfnCmdEnd = CmdEnd;
	pFunctionTable->pfnConnectionlessPacket = ConnectionlessPacket;
	pFunctionTable->pfnGetHullBounds = GetHullBounds;
	pFunctionTable->pfnCreateInstancedBaselines = CreateInstancedBaselines;
	pFunctionTable->pfnInconsistentFile = InconsistentFile;
	pFunctionTable->pfnAllowLagCompensation = AllowLagCompensation;
	pFunctionTable->pfnPlayerCustomization = PlayerCustomization;

	// try to get the game .dll's function table and put it into gFunctionTable
	if( !(*(GETENTITYAPI)GetProcAddress(h_Library, "GetEntityAPI"))(&gFunctionTable, interfaceVersion) )
	{
		return FALSE;  // error initializing function table!!!
	}

	return TRUE; // finished, interfacing from engine to gamedll complete
}

extern "C" _declspec( dllexport ) int GetNewDLLFunctions( NEW_DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion )
{
	static GETNEWDLLFUNCTIONS other_GetNewDLLFunctions = NULL;
	static bool missing = FALSE;

	// if the new DLL functions interface has been formerly reported as missing, give up
	if (missing)
		return FALSE;

	// do we NOT know if the new DLL functions interface is provided ? if so, look for its address
	if (other_GetNewDLLFunctions == NULL)
		other_GetNewDLLFunctions = (GETNEWDLLFUNCTIONS)GetProcAddress(h_Library, "GetNewDLLFunctions");

	// have we NOT found it ?
	if (other_GetNewDLLFunctions == NULL)
	{
		missing = TRUE; // then mark it as missing, no use to look for it again in the future
		return FALSE; // and give up
	}

	// else call the function that provides the new DLL functions interface on request
	return (!(*other_GetNewDLLFunctions) (pFunctionTable, interfaceVersion));
}


