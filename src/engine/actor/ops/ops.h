#ifndef OVERLAY_ACTOR_OPS_H
#define OVERLAY_ACTOR_OPS_H

#include "types.h"

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_ACTOR_OPS_H_LOCAL)
#define OVERLAY_ACTOR_OPS_H_LOCAL

/* func_801A8F94 */
u8   Actor_RunFlowOps(ScriptState* state, u8* base, s32 seed);
/* func_801A96E4 */
void Actor_RunSoundOps(ScriptState* state, u8* base);
/* func_801A9944 */
u8   Actor_RunControlOps(void* sub, s32 target, u8 value);
/* func_801A9DE8 */
u8   Actor_RunMotionOps(ScriptState* state, const u8* table, u8 value);
/* func_801AA470 */
u8   Actor_RunWaitOps(void* sub, s32 target, u8 value);
/* func_801AAB00 */
u8   Actor_RunAppearanceOps(void* sub, s32 target, u8 value);
/* func_801AB458 */
u8   Actor_RunStageOps(ScriptState* state, const u8* table, u8 value);
/* func_801AB8B0 */
s32  Actor_RunSpawnOps(ScriptState* state, u8* table, s32 value);
/* func_801ABA24 */
u8   Actor_RunFaceOps(void* sub, s32 target, u8 value);

#endif
