//
// Sandpit Nightfire
//
// (http://www.teamsandpit.com/)
//

#include "extdll.h"
#include "util.h"

extern enginefuncs_t g_engfuncs;

// ShowMenu isn't implmented in client.dll
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
	if( CVAR_GET_FLOAT("developer") )
	{
		ALERT( at_console, "pfnRegUserMsg: pszName=%s, iSize=%d\n", pszName, iSize );
	}

	int msg = (*g_engfuncs.pfnRegUserMsg)(pszName, iSize);

	if( !strcmp(pszName, "ShowMenu") )
	{
		ALERT( at_console, "Caught ShowMenu message registration\n" );

		gmsgShowMenu = msg;
	}
	else if( !strcmp(pszName, "TextMsg") )
	{
		ALERT( at_console, "Caught TextMsg message registration\n" );

		gmsgTextMsg = msg;
	}

	return msg;
}