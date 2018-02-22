/***
*
*
****/

#include "extdll.h"
#include "util.h"

extern enginefuncs_t g_engfuncs;
extern globalvars_t  *gpGlobals;

DLL_FUNCTIONS gFunctionTable;

void GameDLLInit( void )
{
	(*gFunctionTable.pfnGameInit)();
}

int DispatchSpawn( edict_t *pent )
{
	return (*gFunctionTable.pfnSpawn)(pent);
}

void DispatchThink( edict_t *pent )
{
	(*gFunctionTable.pfnThink)(pent);
}

void DispatchUse( edict_t *pentUsed, edict_t *pentOther )
{
	(*gFunctionTable.pfnUse)(pentUsed, pentOther);
}

void DispatchTouch( edict_t *pentTouched, edict_t *pentOther )
{
	(*gFunctionTable.pfnTouch)(pentTouched, pentOther);
}

void DispatchBlocked( edict_t *pentBlocked, edict_t *pentOther )
{
	(*gFunctionTable.pfnBlocked)(pentBlocked, pentOther);
}

void DispatchKeyValue( edict_t *pentKeyvalue, KeyValueData *pkvd )
{
	(*gFunctionTable.pfnKeyValue)(pentKeyvalue, pkvd);
}

void DispatchSave( edict_t *pent, SAVERESTOREDATA *pSaveData )
{
	(*gFunctionTable.pfnSave)(pent, pSaveData);
}

int DispatchRestore( edict_t *pent, SAVERESTOREDATA *pSaveData, int globalEntity )
{
	return (*gFunctionTable.pfnRestore)(pent, pSaveData, globalEntity);
}

void DispatchObjectCollisionBox( edict_t *pent )
{
	(*gFunctionTable.pfnSetAbsBox)(pent);
}

bool Unknown1( int u1, int u2 )
{
	return (*gFunctionTable.pfnUnknown1)(u1, u2);
}

void SaveWriteFields( SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount )
{
	(*gFunctionTable.pfnSaveWriteFields)(pSaveData, pname, pBaseData, pFields, fieldCount);
}

void SaveReadFields( SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount )
{
	(*gFunctionTable.pfnSaveReadFields)(pSaveData, pname, pBaseData, pFields, fieldCount);
}

void SaveGlobalState( SAVERESTOREDATA *pSaveData )
{
	(*gFunctionTable.pfnSaveGlobalState)(pSaveData);
}

void RestoreGlobalState( SAVERESTOREDATA *pSaveData )
{
	(*gFunctionTable.pfnRestoreGlobalState)(pSaveData);
}

void ResetGlobalState( void )
{
	(*gFunctionTable.pfnResetGlobalState)();
}

BOOL ClientConnect( edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[ 128 ]  )
{
	return (*gFunctionTable.pfnClientConnect)(pEntity, pszName, pszAddress, szRejectReason);
}

void ClientDisconnect( edict_t *pEntity )
{
	(*gFunctionTable.pfnClientDisconnect)(pEntity);
}

void ClientKill( edict_t *pEntity )
{
	ALERT( at_console, "%s was killed\n", pEntity->v.classname );

	(*gFunctionTable.pfnClientKill)(pEntity);
}

void ClientPutInServer( edict_t *pEntity )
{
	// NOTE: classname is an empty string here because it isn't set until the game code
	ALERT( at_console, "Put entity of type %s in server\n", STRING(pEntity->v.classname) );

	(*gFunctionTable.pfnClientPutInServer)(pEntity);
}

void ClientCommand( edict_t *pEntity, int u1, const char **ppcmd )
{
	if( FStrEq(ppcmd[0], "get_player_info") )
	{
		if( pEntity )
		{
			ALERT( at_console, "classname: %s\n", STRING(pEntity->v.classname) );
			ALERT( at_console, "health: %d\n", pEntity->v.health );
		}
		else
		{
			ALERT( at_console, "no entity" );
		}

		return;
	}

	(*gFunctionTable.pfnClientCommand)(pEntity, u1, ppcmd);
}

void ClientUserInfoChanged( edict_t *pEntity, char *infobuffer )
{
	(*gFunctionTable.pfnClientUserInfoChanged)(pEntity, infobuffer);
}

void ServerActivate( edict_t *pEdictList, int edictCount, int clientMax )
{
	(*gFunctionTable.pfnServerActivate)(pEdictList, edictCount, clientMax);
}

void ServerDeactivate( void )
{
	(*gFunctionTable.pfnServerDeactivate)();
}

void PlayerPreThink( edict_t *pEntity )
{
	(*gFunctionTable.pfnPlayerPreThink)(pEntity);
}

void PlayerPostThink( edict_t *pEntity )
{
	(*gFunctionTable.pfnPlayerPostThink)(pEntity);
}

void StartFrame( void )
{
	(*gFunctionTable.pfnStartFrame)();
}

void ParmsNewLevel( void )
{
	(*gFunctionTable.pfnParmsNewLevel)();
}

void ParmsChangeLevel( void )
{
	(*gFunctionTable.pfnParmsChangeLevel)();
}

const char *GetGameDescription( void )
{
	return (*gFunctionTable.pfnGetGameDescription)();
}

void SpectatorConnect( edict_t *pEntity )
{
	(*gFunctionTable.pfnSpectatorConnect)(pEntity);
}

void SpectatorDisconnect( edict_t *pEntity )
{
	(*gFunctionTable.pfnSpectatorDisconnect)(pEntity);
}

void SpectatorThink( edict_t *pEntity )
{
	(*gFunctionTable.pfnSpectatorThink)(pEntity);
}

void Sys_Error( const char *error_string )
{
	(*gFunctionTable.pfnSys_Error)(error_string);
}

void PM_Move( struct playermove_s *ppmove, int server )
{
	(*gFunctionTable.pfnPM_Move)(ppmove, server);
}

void PM_Init( struct playermove_s *ppmove )
{
	(*gFunctionTable.pfnPM_Init)(ppmove);
}

char PM_FindTextureType( char *name )
{
	return (*gFunctionTable.pfnPM_FindTextureType)(name);
}

void SetupVisibility( edict_t *pViewEntity, edict_t *pClient, unsigned char **pvs, unsigned char **pas )
{
	(*gFunctionTable.pfnSetupVisibility)(pViewEntity, pClient, pvs, pas);
}

void UpdateClientData( const struct edict_s *ent, int sendweapons, struct clientdata_s *cd )
{
	(*gFunctionTable.pfnUpdateClientData)(ent, sendweapons, cd);
}

int AddToFullPack( struct entity_state_s *state, int e, edict_t *ent, edict_t *host, int hostflags, int player, unsigned char *pSet )
{
	return (*gFunctionTable.pfnAddToFullPack)(state, e, ent, host, hostflags, player, pSet);
}

void CreateBaseline( int player, int eindex, struct entity_state_s *baseline, struct edict_s *entity, int playermodelindex, vec3_t player_mins, vec3_t player_maxs )
{
	(*gFunctionTable.pfnCreateBaseline)(player, eindex, baseline, entity, playermodelindex, player_mins, player_maxs);
}

void RegisterEncoders( void )
{
	(*gFunctionTable.pfnRegisterEncoders)();
}

int GetWeaponData( struct edict_s *player, struct weapon_data_s *info )
{
	return (*gFunctionTable.pfnGetWeaponData)(player, info);
}

void CmdStart( const edict_t *player, const struct usercmd_s *cmd, unsigned int random_seed )
{
	(*gFunctionTable.pfnCmdStart)(player, cmd, random_seed);
}

void CmdEnd( const edict_t *player )
{
	(*gFunctionTable.pfnCmdEnd)(player);
}

int ConnectionlessPacket( const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size )
{
	return (*gFunctionTable.pfnConnectionlessPacket)(net_from, args, response_buffer, response_buffer_size);
}

int GetHullBounds( int hullnumber, float *mins, float *maxs )
{
	return (*gFunctionTable.pfnGetHullBounds)(hullnumber, mins, maxs);
}

void CreateInstancedBaselines( void )
{
	(*gFunctionTable.pfnCreateInstancedBaselines)();
}

int InconsistentFile( const edict_t *player, const char *filename, char *disconnect_message )
{
	return (*gFunctionTable.pfnInconsistentFile)(player, filename, disconnect_message);
}

int AllowLagCompensation( void )
{
	return (*gFunctionTable.pfnAllowLagCompensation)();
}

void PlayerCustomization( edict_t *pEntity, customization_t *pCust )
{
	return (*gFunctionTable.pfnPlayerCustomization)(pEntity, pCust);
}