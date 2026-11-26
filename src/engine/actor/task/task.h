#ifndef OVERLAY_ACTOR_TASK_H
#define OVERLAY_ACTOR_TASK_H

#include "types.h"
/* func_8014DC08 */
extern void Actor_SelectSprite(u32 record_index);
/* func_8015A944 */
void        Actor_ProjectForDraw(void);
/* func_8015B410 */
void        Actor_BuildTransformMatrix(void* matrix);
/* func_8015C148 */
s32         Actor_GetOwner(void);
/* func_8015C750 */
s8          Actor_StepScroll(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, s32 flags);
/* func_8015C940 */
s32         Actor_RiseToGround(s32 entry, s32 dir_x, s32 dir_y, s32 vz_start, s16 vz_delta);
/* func_8015CA48 */
s32         Actor_FindFreeField(void);
/* func_8015CA9C */
u16         Actor_ReadState(void);
/* func_8015CB18 */
s32         Actor_ClaimSlot();
/* func_8015CC00 */
s32         Actor_SpawnHelper(u8 id, s32 vx, s32 selection, s32 x, s32 y, s32 z);

/* func_8019601C */
u8   Actor_FindFreeSpawned(void);
/* func_80196070 */
void Actor_Clear(void);
/* func_801960C0 */
void Actor_Free(u8 record_index);
/* func_8019611C */
void Actor_ClearAll(void);
/* func_8019615C */
void Actor_Create(u8* request);
/* func_8019A0E4 */
void Actor_DispatchAll(void);
/* Actor_SpawnFromRecord */
/* func_801A4D54 */
void Actor_SpawnFromRecord(u8* script);
/* func_801A65A0 */
void Actor_SpawnPartyFromRecord(u8* script);
/* func_801B2D00 */
s32  Actor_GetTurnStep(s32 target_facing);
/* Actor_SetSemiTransparent */
/* func_801C2438 */
void Actor_SetSemiTransparent(void);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_ACTOR_TASK_H_LOCAL)
#define OVERLAY_ACTOR_TASK_H_LOCAL

s8   Actor_Run(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 landing_flags);
/* func_8015D820 */
void Actor_PlayCueByDistance(u16 cue_id, u16 index);
/* func_801A06D8 */
u32  Actor_RunInteractions(void);
/* func_801A2C10 */
u8   Actor_TurnRandom(void* record);
/* func_801A4990 */
void Actor_SetOptionFlags(u8* script);
void Actor_SpawnSceneActor(s8 actor_slot);
void Actor_ReadValue(void);
/* func_8019ADA4 */
void Actor_TossRun(void);
/* func_8019ADE8 */
void Actor_TossStart(void);
/* func_8019AF1C */
void Actor_TossLaunch(void);
/* func_8019B024 */
void Actor_TossFall(void);
/* func_8019B0EC */
void Actor_ClearSelf(void);
/* func_8019F5B8 */
void Actor_DrawValueDigits(s16 x, s16 y, u8 unused, u8 palette);
/* func_801A4914 */
void Actor_StartFacingScript(void);
/* func_801A4B80 */
void Actor_TurnRampClear(s32 index);
/* func_801A50C0 */
void Actor_SpawnNoRoute(u8* script);
/* func_801A5400 */
void Actor_SpawnBlocker(u8* script);
/* func_801A57F0 */
void Actor_SpawnAttached(u8* script);
/* func_801A5B78 */
void Actor_SpawnVoiced(u8* script);
/* func_801A5EFC */
void Actor_SpawnWithAction(u8* script);
/* func_801A623C */
void Actor_SpawnBattleEntry(u8* script);
/* func_801A68C0 */
void Actor_SpawnFromDefRow(u8* script);
/* func_801A6F58 */
void Actor_SpawnAttachedFixedFlags(u8* script);
/* func_801ADCF4 */
void Actor_SpawnToss(u8 source_slot);

/* func_8019B364 */
void Actor_RockRun(void);
/* func_8019B3A8 */
void Actor_RockStart(void);
/* func_8019B4A0 */
void Actor_RockWait(void);
/* func_8019BBA4 */
void Actor_RockSettle(void);
/* func_8019BE28 */
void Actor_RockEnd(void);
/* func_8019BEFC */
void Actor_RockRest(void);
/* func_8019BF78 */
void Actor_RockClaimCell(void);
/* func_8019BFD4 */
void Actor_RockReleaseCamera(void);
/* func_8019C028 */
bool Actor_RockHit(void);
/* func_8019C124 */
void Actor_RockSetTarget(s32 step_byte);
/* func_8019C1E4 */
s32  Actor_RockIsBlockedAhead(void);
/* func_8019C244 */
s32  Actor_RockIsBlockedAtEdge(void);
/* func_8019C344 */
s32  Actor_RockIsPointBlocked(s32 x, s32 y);
/* func_8019C4F0 */
s32  Actor_RockIsCellBlocked();
/* One of the 24 shards of a broken model, at 0x800E4800 + n * 0x38: a centre, a random rotation and four corner offsets that
 * Actor_ShatterWriteShard rotates and writes out as vertices. */
typedef struct ShatterShard {
    Pos3s   pos;
    u8      unk_06[0x0A];
    SVECTOR rotation; /* 0x10 */
    SVECTOR corners[4];
} ShatterShard;

ASSERT_OFFSET(ShatterShard, rotation, 0x10);
ASSERT_OFFSET(ShatterShard, corners, 0x18);
ASSERT_SIZE(ShatterShard, 0x38);

/* func_8019CB94 */
void Actor_BlockRun(void);
/* func_8019CBD8 */
void Actor_BlockStart(void);
/* func_8019CCB8 */
void Actor_BlockWait(void);
/* func_8019CEDC */
void Actor_BlockSlide(void);
/* func_8019CFCC */
void Actor_BlockShatter(void);
/* func_8019D054 */
bool Actor_BlockIsPathBlocked(s32 point_x, s32 point_y);
/* func_8019D20C */
s32  Actor_BlockIsCellSolid(s16 map_x, s16 map_y);
/* func_8019D270 */
void Actor_BlockClaimCells(void);
/* func_8019D4BC */
void Actor_BlockReleaseCells(void);
/* func_8019D648 */
void Actor_ShatterBuildShards(void);
/* func_8019D800 */
void Actor_ShatterSpinShards(void);
/* func_8019D8C0 */
void Actor_ShatterWriteShard(ShatterShard* quad, s16* out);
/* func_8019D9C0 */
void Actor_ShatterStartDust(void);
/* func_8019DAA0 */
s32  Actor_ShatterDrawPuff(s32* puff, s16 quad_size, u8 brightness);
/* func_8019DC6C */
void Actor_ShatterRunDust(void);
#endif
