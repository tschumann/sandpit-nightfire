/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/

#include "extdll.h"
#include "util.h"
#include "../plugin/dll.h"

extern int gmsgTextMsg;

#ifdef	DEBUG
edict_t *DBG_EntOfVars( const entvars_t *pev )
{
	if (pev->pContainingEntity != NULL)
		return pev->pContainingEntity;
	ALERT(at_console, "entvars_t pContainingEntity is NULL, calling into engine");
	edict_t* pent = (*g_engfuncs.pfnFindEntityByVars)((entvars_t*)pev);
	if (pent == NULL)
		ALERT(at_console, "DAMN!  Even the engine couldn't FindEntityByVars!");
	((entvars_t *)pev)->pContainingEntity = pent;
	return pent;
}
#endif //DEBUG

void UTIL_MakeVectors( const Vector &vecAngles )
{
	MAKE_VECTORS( vecAngles );
}

void UTIL_TraceLine( const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, IGNORE_GLASS ignoreGlass, edict_t *pentIgnore, TraceResult *ptr )
{
	TRACE_LINE( vecStart, vecEnd, 0, (igmon == ignore_monsters ? TRUE : FALSE) | (ignoreGlass?0x100:0), pentIgnore, ptr );
}

void UTIL_TraceLine( const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, edict_t *pentIgnore, TraceResult *ptr )
{
	TRACE_LINE( vecStart, vecEnd, 0, (igmon == ignore_monsters ? TRUE : FALSE), pentIgnore, ptr );
}

void ClientPrint( entvars_t *client, int msg_dest, const char *msg_name, const char *param1, const char *param2, const char *param3, const char *param4 )
{
	MESSAGE_BEGIN( MSG_ONE, gmsgTextMsg, NULL, client );
		WRITE_BYTE( msg_dest );
		WRITE_STRING( msg_name );

		if ( param1 )
			WRITE_STRING( param1 );
		if ( param2 )
			WRITE_STRING( param2 );
		if ( param3 )
			WRITE_STRING( param3 );
		if ( param4 )
			WRITE_STRING( param4 );

	MESSAGE_END();
}

// custom code

edict_t *FindEntityForward( edict_t *pMe )
{
	TraceResult tr;

	UTIL_MakeVectors(pMe->v.v_angle);
	UTIL_TraceLine(pMe->v.origin + pMe->v.view_ofs, pMe->v.origin + pMe->v.view_ofs + gpGlobals->v_forward * 8192, dont_ignore_monsters, pMe, &tr );

	if ( tr.flFraction != 1.0 && !FNullEnt( tr.pHit ) )
	{
		return tr.pHit;
	}

	return nullptr;
}

edict_t* Create( const char *szName, const Vector &vecOrigin, const Vector &vecAngles, edict_t *pentOwner )
{
	edict_t	*pent;

	pent = CREATE_NAMED_ENTITY( MAKE_STRING( szName ));
	if ( FNullEnt( pent ) )
	{
		ALERT( at_console, "NULL Ent in Create!\n" );
		return NULL;
	}
	pent->v.owner = pentOwner;
	pent->v.origin = vecOrigin;
	pent->v.angles = vecAngles;
	DispatchSpawn( pent );
	return pent;
}