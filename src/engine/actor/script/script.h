#ifndef OVERLAY_ACTOR_SCRIPT_H
#define OVERLAY_ACTOR_SCRIPT_H

#include "types.h"

/* The executable's actor functions, in address order. */
/* func_8014D54C */
void        Script_CopyRecord(u32 record_index, u8* staging, u32 size);
/* func_8014D5F0 */
void        Script_Switch(u8 value, u8* dst, s32 size);
/* func_8014D664 */
void        Script_Stage(s32 script_index, s32 position, u8* staging, s32 size);
/* func_8014D6B8 */
void        Script_Select(u8 script_index);
/* func_8014D6DC */
void        Script_Begin(s32 script_index, s32 position);
/* func_8014D8D4 */
u32         Script_Request(u8 script_index);
/* func_8014D910 */
void        Script_Seek(u16 position);
/* func_8014D978 */
u8          Script_AnimStepLoop(void);
/* func_8014DAEC */
u8          Script_AnimStepOnce(void);
/* func_8015B4F4 */
s8          Script_FindSlot(s32 code);
/* func_8015BAC4 */
extern void Script_DispatchSelector(u8 selector);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_ACTOR_SCRIPT_H_LOCAL)
#define OVERLAY_ACTOR_SCRIPT_H_LOCAL
/* func_8014DB98 */
extern void Script_AnimStageStep(void);

/* func_8015B870 */
s32 Script_ReadValue(u32 type);
/* func_801A8D38 */
u8  Script_Run(void* sub, s32 target);
/* func_801AC8F0 */
u16 Script_FindLabel(ScriptState* state, u8 wanted_id, u8* base);

#endif
