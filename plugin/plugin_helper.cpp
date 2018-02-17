/***
*
*
****/

#include "extdll.h"
#include "util.h"

edict_t *FindEntityForward( edict_t *pMe )
{
	TraceResult tr;

	UTIL_MakeVectors(pMe->v.v_angle);
	UTIL_TraceLine(pMe->v.origin + pMe->v.view_ofs,pMe->v.origin + pMe->v.view_ofs + gpGlobals->v_forward * 8192,dont_ignore_monsters, pMe, &tr );
	if ( tr.flFraction != 1.0 && !FNullEnt( tr.pHit) )
	{
		return tr.pHit;
	}
	return NULL;
}