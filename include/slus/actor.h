#ifndef SLUS_ACTOR_H
#define SLUS_ACTOR_H

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
/* func_8014DC08 */
extern void Actor_SelectSprite(u32 record_index);
/* func_8015B4F4 */
s8          Actor_FindScriptSlot(s32 code);
/* func_8015BAC4 */
extern void Actor_DispatchSelectorScript(u8 selector);
/* func_8015C148 */
s32         Actor_GetOwner(void);
/* func_8015C2D4 */
s8          Actor_InitMovement(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, s32 flags);
/* func_8015C540 */
s8          Actor_StepMovement(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags);
/* func_8015C750 */
s8          Actor_StepScroll(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, s32 flags);
/* func_8015C940 */
s32         Actor_RiseToGround(s32 entry, s32 dir_x, s32 dir_y, s32 vz_start, s16 vz_delta);
/* func_8015C9CC */
void        Actor_ApplyVelocity(void);
/* func_8015CA48 */
s32         Actor_FindFreeField(void);
/* func_8015CA9C */
u16         Actor_ReadState(void);

#endif
