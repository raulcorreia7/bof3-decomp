#ifndef OVERLAY_ACTOR_MOTION_H
#define OVERLAY_ACTOR_MOTION_H

#include "types.h"
#include "sys/actor.h"

void Actor_ClearVelocity(void);
/* func_8015C2D4 */
s8   Actor_InitMovement(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, s32 flags);
/* func_8015C540 */
s8   Actor_StepMovement(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags);
/* func_8015C9CC */
void Actor_ApplyVelocity(void);
/* Actor_UpdateMovement */
/* func_801B0DFC */
void Actor_UpdateMovement(void);
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

#endif
