#ifndef OVERLAY_ACTOR_MOTION_H
#define OVERLAY_ACTOR_MOTION_H

#include "types.h"
#include "sys/actor.h"

void Actor_ClearVelocity(void);
/* func_8015C2D4 */
s8   Actor_MovementInit(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, s32 flags);
/* func_8015C540 */
s8   Actor_MovementStep(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags);
/* func_8015C9CC */
void Actor_ApplyVelocity(void);
/* Actor_MovementUpdate */
/* func_801B0DFC */
void Actor_MovementUpdate(void);
/* Actor_IsInRange */
/* func_801BDD58 */
u8   Actor_IsInRange(s32 pos_x, s32 pos_y, s16 z, s32 reach, Actor* record);
/* Actor_FindInRange */
/* func_801BDE14 */
s8   Actor_FindInRange(s32 pos_x, s32 pos_y, s32 range_mode);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_ACTOR_MOTION_H_LOCAL)
#define OVERLAY_ACTOR_MOTION_H_LOCAL

/* func_801A4AA8 */
void Actor_ResetMotion(void);
/* func_801B5BDC */
void Actor_RequestRoute(u8 route_index);
/* func_801BB8E8 */
void Actor_SnapFacing(u8 arg_a, u8 arg_b, u8 arg_c);
/* func_801C57B4 */
void Actor_Move(void);

/* func_801A0AE4 */
void Actor_RunWander(Actor* record);
/* func_801A0CFC */
void Actor_RunFlee(Actor* entity);
/* func_801A0F24 */
void Actor_RunChase(Actor* record);
/* func_801A114C */
void Actor_RunWanderHome(Actor* record);
/* func_801A1384 */
void Actor_RunRoute(void* entity);
/* func_801A271C */
void Actor_RunRouteWait(void* record);
/* func_801A1A24 */
void Actor_RunRequestScript(u8* record);
/* func_801A3410 */
void Actor_RunAttach(void* work_index);
/* func_801A3B7C */
void Actor_RunTurn(Actor* entity);
/* func_801A225C */
s32  Actor_PaceFree(s32 unused, s32 divisor, s32 flag_bits);
/* func_801A22CC */
s32  Actor_PaceByPartyStep(Actor* value_a, s32 value_b, u8 flag_bits);
/* func_801A239C */
s32  Actor_PaceByPartyStepDouble(Actor* value_a, s32 value_b, u8 flag_bits);
/* func_801A246C */
s32  Actor_PaceByPartyStepBit1(s32 value_a, s32 value_b, s32 flag_bits);
/* func_801A2788 */
void Actor_RunMode(s32 step_index);
/* func_801A2A04 */
u8   Actor_FindFreeFacing(Actor* entity);
/* func_801A2C94 */
u8   Actor_PickFleeFacing(Actor* actor);
/* func_801A2DB4 */
u8   Actor_PickChaseFacing(Actor* entity);
/* func_801A2ED4 */
u8   Actor_PickFacingByLeaderDistance(Actor* entity, u8 route_step);
/* func_801A1A58 */
bool Actor_IsAheadInHomeBox(Actor* actor);
/* func_801A275C */
void Actor_StartRouteWait(void* unused);
/* func_801A3AC8 */
bool Actor_IsAheadOccupied(Actor* record);
#endif
