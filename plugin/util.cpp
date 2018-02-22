
#include "extdll.h"
#include "util.h"

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