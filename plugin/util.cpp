/***
*
*
****/

#include "extdll.h"
#include "util.h"
#include "dll.h"

// from Half-Life's util.cpp
void UTIL_MakeVectors( const Vector &vecAngles )
{
	MAKE_VECTORS( vecAngles );
}

// from Half-Life's util.cpp
void UTIL_TraceLine( const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, IGNORE_GLASS ignoreGlass, edict_t *pentIgnore, TraceResult *ptr )
{
	TRACE_LINE( vecStart, vecEnd, 0, (igmon == ignore_monsters ? TRUE : FALSE) | (ignoreGlass?0x100:0), pentIgnore, ptr );
}

// from Half-Life's util.cpp
void UTIL_TraceLine( const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, edict_t *pentIgnore, TraceResult *ptr )
{
	TRACE_LINE( vecStart, vecEnd, 0, (igmon == ignore_monsters ? TRUE : FALSE), pentIgnore, ptr );
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
		ALERT ( at_console, "NULL Ent in Create!\n" );
		return NULL;
	}
	pent->v.owner = pentOwner;
	pent->v.origin = vecOrigin;
	pent->v.angles = vecAngles;
	DispatchSpawn( pent );
	return pent;
}