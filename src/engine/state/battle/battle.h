#ifndef OVERLAY_STATE_BATTLE_H
#define OVERLAY_STATE_BATTLE_H

#include "types.h"

/* func_801C7A54 */
void Battle_StartScripted(u8 mode_byte);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_STATE_BATTLE_H_LOCAL)
#define OVERLAY_STATE_BATTLE_H_LOCAL

/* func_80197A60 */
void Battle_TurnToEncounter(void);
void Battle_LoadPartySprites(void);
/* func_80197C1C */
void Battle_WalkToEncounter(void);
void Battle_LoadBattleArchive(void);
/* func_80197E54 */
void Battle_BeginEntrance(void);
/* func_801BEDD0 */
void Battle_QueueEncounterTurns(void);
/* func_801BEE5C */
bool Battle_LoadPartyScripts(void);
/* func_801BF11C */
bool Battle_WalkMembersIn(void);
/* func_801BF448 */
void Battle_PlaceMembers(void);
/* func_801BF5A8 */
void Battle_SetEncounterSpot(s32 x, s32 y, s32 party_slot);
/* func_801BF78C */
bool Battle_IsPartyInPlace(void);
/* func_801BF8E0 */
void Battle_ScrollToLeader(void);
/* func_801BFAC4 */
void Battle_RunPartyAnims(void);
/* func_801BFB34 */
void Battle_PlaceFieldMembers(void);

#endif
