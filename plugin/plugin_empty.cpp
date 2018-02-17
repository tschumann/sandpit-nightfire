/***
*
*
****/

#include "extdll.h"
#include "util.h"
#include "enginecallback.h"

#include "plugin.h"
#include "plugin_empty.h"
#include "plugin_helper.h"

//---------------------------------------------------------------------------------
// engine functions
//---------------------------------------------------------------------------------


//---------------------------------------------------------------------------------
// engine callbacks
//---------------------------------------------------------------------------------

void Plugin_ClientKill( edict_t *pEntity )
{
	ALERT( at_console, "%s was killed\n", pEntity->v.classname );
}

void Plugin_ClientPutInServer( edict_t *pEntity )
{
	// NOTE: classname is an empty string here because it isn't set until the game code
	ALERT( at_console, "Put entity of type %s in server\n", STRING(pEntity->v.classname) );
}

void Plugin_ClientCommand( edict_t *pEntity, int u1, const char **ppcmd )
{
	// Is the client spawned yet?
	if ( !pEntity->pvPrivateData )
		return;

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
	}
}
