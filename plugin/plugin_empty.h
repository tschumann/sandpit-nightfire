/***
*
*
****/

#ifndef PLUGIN_EMPTY_H
#define PLUGIN_EMPTY_H

void Plugin_ClientKill( edict_t *pEntity );
void Plugin_ClientPutInServer( edict_t *pEntity );
void Plugin_ClientCommand( edict_t *pEntity, int u1, const char **ppcmd );

#endif // PLUGIN_EMPTY_H