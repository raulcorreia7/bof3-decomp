#ifndef OVERLAY_PARTY_PARTY_H
#define OVERLAY_PARTY_PARTY_H

#include "types.h"

/* func_801BDB7C */
u8          Party_CountOrder(u8 order);
u8          Party_CountOrder(u8 mode);
/* The executable's character, item and party functions, in address order. */
/* func_8015C100 */
extern void Party_BattlersHide(void);
/* func_801664A0 */
u8          Party_CountAbilities(u8 character_index, u8 ability_type, u8 mode);
/* func_8016663C */
bool        Party_SpendZenny(u32 amount, s32 unused);
/* func_8016666C */
s32         Party_AddZenny(s32 amount, s32 skip_earned);
/* func_801C1254 */
void        Party_MemberLoadSprite(s32 character_id, s32 party_slot);
/* func_801C1400 */
void        Party_BattlersBuild(u32 order);
/* Party_LoadPalettes */
/* func_801C1630 */
void        Party_LoadPalettes(void);
/* func_801C187C */
s32         Party_MemberJoin(s32 char_id);
/* Party_MemberRemove */
/* func_801C1ABC */
void        Party_MemberRemove(s32 character_id);
/* Party_TickConfusion */
/* func_801C3598 */
void        Party_TickConfusion(void);
/* func_80166AE4: type table for (source slot, group, table type) */
u8*         Party_GetAbilities(u32 formation_index, u32 ability_type, u32 mode);
/* func_80166CEC */
void        Party_BattlersClearState(s32 character_index);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_PARTY_PARTY_H_LOCAL)
#define OVERLAY_PARTY_PARTY_H_LOCAL

void Party_BattlersShow(void);
void Party_BattlersReset(void);
void Party_BattlersClearActive(void);
/* func_801B55C0 */
bool Party_CanSwitchLeader(void);
void Party_MemberSwap(u32 slot_a, u32 slot_b, u32 skip_state);
void Party_BattlersSwapRows(s32 slot_a, s32 slot_b, s32 skip_state);
/* func_801B00F8 */
void Party_RunLeader(void);
/* func_801B69C0 */
void Party_RunMoveStep(void);
/* func_801B6A04 */
void Party_ScriptWalkRun(void);
/* func_801B6AB0 */
void Party_ScriptWalkAlign(void);
/* func_801B6BC8 */
void Party_ScriptWalkRead(void);
/* func_801B6F1C */
void Party_ScriptWalkMove(void);
/* func_801B6FDC */
void Party_ScriptWalkWaitMessage(void);
/* func_801B7024 */
void Party_ScriptWalkFadeOut(void);
/* func_801B707C */
void Party_ScriptWalkFadeIn(void);
/* func_801B70D4 */
void Party_AttachRun(void);
/* func_801B726C */
void Party_FadeInRun(void);
/* func_801B72B0 */
void Party_FadeInStart(void);
/* func_801B7344 */
void Party_FadeInWait(void);
/* func_801B73B0 */
void Party_JumpRun(void);
/* func_801B73F4 */
void Party_JumpStart(void);
/* func_801B744C */
void Party_JumpLaunch(void);
/* func_801B7658 */
void Party_JumpTravel(void);
/* func_801B76F4 */
void Party_JumpFall(void);
/* func_801B781C */
void Party_JumpLand(void);
/* func_801B78B4 */
void Party_LadderTransitRun(void);
/* func_801B790C */
void Party_LadderUpRun(void);
/* func_801B7950 */
void Party_LadderUpGrab(void);
/* func_801B7988 */
void Party_LadderUpLeave(void);
/* func_801B79F8 */
void Party_LadderUpEnter(void);
/* func_801B7B54 */
void Party_LadderUpClimb(void);
/* func_801B7C10 */
void Party_LadderUpDismount(void);
/* func_801B7C58 */
void Party_LadderUpExitBegin(void);
/* func_801B7CA0 */
void Party_LadderUpExit(void);
/* func_801B7D00 */
void Party_LadderDownRun(void);
/* func_801B7D44 */
void Party_LadderDownApproachBegin(void);
/* func_801B7D84 */
void Party_LadderDownApproach(void);
/* func_801B7DC0 */
void Party_LadderDownTurn(void);
/* func_801B7DFC */
void Party_LadderDownTurnWait(void);
/* func_801B7E38 */
void Party_LadderDownLower(void);
/* func_801B7E74 */
void Party_LadderDownLeave(void);
/* func_801B7EF0 */
void Party_LadderDownEnter(void);
/* func_801B7FE0 */
void Party_LadderDownDescend(void);
/* func_801B80B4 */
void Party_LadderDownDismount(void);
/* func_801B81EC */
void Party_LadderWaitFadeIn(void);
/* func_801B8234 */
void Party_WalkTransitRun(void);
/* func_801B828C */
void Party_WalkExitBegin(void);
/* func_801B830C */
void Party_WalkExit(void);
/* func_801B8394 */
void Party_WalkEnterBegin(void);
/* func_801B8578 */
void Party_WalkEnterFadeWait(void);
/* func_801B85C0 */
void Party_WalkEnter(void);
/* func_801B870C */
void Party_CellWalkRun(void);
/* func_801B876C */
void Party_CellWalkStart(void);
/* func_801B87B8 */
void Party_CellWalkMove(void);
/* func_801B8A0C */
void Party_CellWalkEnd(void);
/* func_801B9048 */
void Party_FallThroughRun(void);
/* func_801B90A0 */
void Party_FallThroughStart(void);
/* func_801B9100 */
void Party_FallThroughSpin(void);
/* func_801B91CC */
void Party_FloorDamageRun(void);
/* func_801B9210 */
void Party_FloorDamageStart(void);
/* func_801B9478 */
void Party_FloorDamageBlink(void);
/* func_801BBE48 */
void Party_RunFollower(void);
/* func_801C2AAC */
s32  Party_StartCellWalk(void);
/* func_801C2B4C */
s32  Party_StartFallThrough(void);
/* func_801C2E34 */
void Party_FloorDamageApply(u8 damage_index);
/* func_801C308C */
void Party_FlashDamage(s32 color_index);
/* func_801C364C */
s32  Party_StartFloorDamage(s32 wanted_code, s32 damage_index, s32 find_facing);
#endif
