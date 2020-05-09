//
// Sandpit Nightfire
//
// (http://www.teamsandpit.com/)
//

#include "extdll.h"
#include "util.h"

extern enginefuncs_t g_engfuncs;

// ShowMenu isn't implmented on the client-side
int gmsgShowMenu = 0;
int gmsgTextMsg = 0;

void MessageBegin(int msg_dest, int msg_type, const float *pOrigin, edict_t *ed)
{
	(*g_engfuncs.pfnMessageBegin)(msg_dest, msg_type, pOrigin, ed);
}
 
void MessageEnd(void)
{
	(*g_engfuncs.pfnMessageEnd)();
}

int RegUserMsg(const char *pszName, int iSize)
{
#if DEBUG
	if( CVAR_GET_FLOAT("developer") )
	{
		ALERT( at_console, "pfnRegUserMsg: pszName=%s, iSize=%d\n", pszName, iSize );
	}
#endif

	int msg = (*g_engfuncs.pfnRegUserMsg)(pszName, iSize);

	if( !strcmp(pszName, "ShowMenu") )
	{
#if DEBUG
		ALERT( at_console, "Caught ShowMenu\n" );
#endif
		gmsgShowMenu = msg;
	}
	else if( !strcmp(pszName, "TextMsg") )
	{
#if DEBUG
		ALERT( at_console, "Caught TextMsg\n" );
#endif
		gmsgTextMsg = msg;
	}

	return msg;
}