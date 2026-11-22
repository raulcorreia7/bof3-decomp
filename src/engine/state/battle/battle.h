#ifndef OVERLAY_STATE_BATTLE_H
#define OVERLAY_STATE_BATTLE_H

#include "types.h"

/* func_801C7A54 */
void Game_BattleStartScripted(u8 mode_byte);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_STATE_BATTLE_H_LOCAL)
#define OVERLAY_STATE_BATTLE_H_LOCAL

/* func_80197A60 */
void Game_BattleTurnToEncounter(void);
void Game_BattleLoadPartySprites(void);
/* func_80197C1C */
void Game_BattleWalkToEncounter(void);
void Game_BattleLoadArchive(void);
/* func_80197E54 */
void Game_BattleBeginEntrance(void);
/* func_801BEDD0 */
void Game_BattleQueueEncounterTurns(void);
/* func_801BEE5C */
bool Game_BattleLoadPartyScripts(void);
/* func_801BF11C */
bool Game_BattleWalkMembersIn(void);
/* func_801BF448 */
void Game_BattlePlaceMembers(void);
/* func_801BF5A8 */
void Game_BattleSetEncounterSpot(s32 x, s32 y, s32 party_slot);
/* func_801BF78C */
bool Game_BattleIsPartyInPlace(void);
/* func_801BF8E0 */
void Game_BattleScrollToLeader(void);
/* func_801BFAC4 */
void Game_BattleRunPartyAnims(void);
/* func_801BFB34 */
void Game_BattlePlaceFieldMembers(void);

#endif
