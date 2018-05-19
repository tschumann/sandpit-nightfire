/***
*
*
****/

#ifndef ENGINE_H
#define ENGINE_H

extern int gmsgShowMenu;

void MessageBegin(int msg_dest, int msg_type, const float *pOrigin, edict_t *ed);
void MessageEnd(void);
int RegUserMsg(const char *pszName, int iSize);

#endif // ENGINE_H

