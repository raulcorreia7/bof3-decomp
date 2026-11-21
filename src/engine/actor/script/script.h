#ifndef OVERLAY_ACTOR_SCRIPT_H
#define OVERLAY_ACTOR_SCRIPT_H

#include "types.h"

/* The executable's actor functions, in address order. */
/* func_8014D54C */
void        Actor_CopyScriptRecord(u32 record_index, u8* staging, u32 size);
/* func_8014D5F0 */
void        Actor_SwitchScript(u8 value, u8* dst, s32 size);
/* func_8014D664 */
void        Actor_StageScript(s32 script_index, s32 position, u8* staging, s32 size);
/* func_8014D6B8 */
void        Actor_SelectScript(u8 script_index);
/* func_8014D6DC */
void        Actor_BeginScript(s32 script_index, s32 position);
/* func_8014D8D4 */
u32         Actor_RequestScript(u8 script_index);
/* func_8014D910 */
void        Actor_SeekScript(u16 position);
/* func_8014D978 */
u8          Actor_StepAnimLoop(void);
/* func_8014DAEC */
u8          Actor_StepAnimOnce(void);
/* func_8015B4F4 */
s8          Actor_FindScriptSlot(s32 code);
/* func_8015BAC4 */
extern void Actor_DispatchSelectorScript(u8 selector);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_ACTOR_SCRIPT_H_LOCAL)
#define OVERLAY_ACTOR_SCRIPT_H_LOCAL
/* func_8014DB98 */
extern void Actor_StageAnimStep(void);

/* func_8015B870 */
s32 Script_ReadValue(u32 type);
/* func_801A8D38 */
u8  Actor_RunScript(void* sub, s32 target);
/* func_801AC8F0 */
u16 Actor_FindScriptLabel(ScriptState* state, u8 wanted_id, u8* base);

#endif
