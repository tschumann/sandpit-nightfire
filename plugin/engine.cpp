/***
*
*
****/

#include "extdll.h"
#include "util.h"

extern enginefuncs_t g_engfuncs;

int gmsgFade;
int gmsgHudText;
int gmsgSayText;
int gmsgShake;
int gmsgTextMsg;

int gMsgType = 0;

void MessageBegin(int msg_dest, int msg_type, const float *pOrigin, edict_t *ed)
{
	gMsgType = msg_type;

	(*g_engfuncs.pfnMessageBegin)(msg_dest, msg_type, pOrigin, ed);
}
 
void MessageEnd(void)
{
	gMsgType = 0;

	(*g_engfuncs.pfnMessageEnd)();
}

int RegUserMsg(const char *pszName, int iSize)
{
	if( CVAR_GET_FLOAT("developer") )
	{
		ALERT( at_console, "pfnRegUserMsg: pszName=%s, iSize=%d\n", pszName, iSize );
	}

	return (*g_engfuncs.pfnRegUserMsg)(pszName, iSize);
}