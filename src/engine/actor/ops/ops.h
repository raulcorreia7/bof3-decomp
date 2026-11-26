#ifndef OVERLAY_ACTOR_OPS_H
#define OVERLAY_ACTOR_OPS_H

#include "types.h"

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_ACTOR_OPS_H_LOCAL)
#define OVERLAY_ACTOR_OPS_H_LOCAL

/* func_801A8F94 */
u8   Script_OpsRunFlow(ScriptState* state, u8* base, s32 seed);
/* func_801A96E4 */
void Script_OpsRunSound(ScriptState* state, u8* base);
/* func_801A9944 */
u8   Script_OpsRunControl(void* sub, s32 target, u8 value);
/* func_801A9DE8 */
u8   Script_OpsRunMotion(ScriptState* state, const u8* table, u8 value);
/* func_801AA470 */
u8   Script_OpsRunWait(ScriptState* state, u8* base, u8 value);
/* func_801AAB00 */
u8   Script_OpsRunAppearance(void* sub, s32 target, u8 value);
/* func_801AB458 */
u8   Script_OpsRunStage(ScriptState* state, const u8* table, u8 value);
/* func_801AB8B0 */
s32  Script_OpsRunSpawn(ScriptState* state, u8* table, s32 value);
/* func_801ABA24 */
u8   Script_OpsRunFace(void* sub, s32 target, u8 value);

#endif
