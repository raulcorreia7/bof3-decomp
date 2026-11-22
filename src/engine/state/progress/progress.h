#ifndef OVERLAY_STATE_PROGRESS_H
#define OVERLAY_STATE_PROGRESS_H

#include "types.h"

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_STATE_PROGRESS_H_LOCAL)
#define OVERLAY_STATE_PROGRESS_H_LOCAL

/* func_801C39D8 */
u8  Game_TestMapCells(s32 pos_x, s32 pos_y, s32 flag, s32 wanted_code, u8 mask_cells);
/* func_801C3E40 */
s32 Game_TestPlacement(s32 pos_x, s32 pos_y, s32 probe_flag, s16 probe_range);
s32 Game_IsScenarioEqual(u8** cursor);
s32 Game_IsAreaEqual(u8** cursor);
s32 Game_TestSceneFlag(u8** cursor);
/* func_8015B6A8 */
s32 Game_IsScenarioStateEqual(u8** cursor);
/* func_8015B6D0 */
s32 Game_IsCellTypeEqual(u8** cursor);
/* func_8015B6F8 */
s32 Game_TestScenarioFlag(u8** cursor);
/* func_8015B73C */
s32 Game_IsLeaderEqual(u8** cursor);
s32 Game_TestEventFlag(u8** cursor);
s32 Game_IsScenarioAtMost(u8** cursor);
s32 Game_IsScriptVar0Equal(u8** cursor);
s32 Game_IsScriptVar1Equal(u8** cursor);
s32 Game_IsScriptVar2Equal(u8** cursor);
s32 Game_IsScriptVar3Equal(u8** cursor);
s32 Game_ScriptVarSet(u8* operand);
s32 Game_ScriptVarIsEqual(u8* operand);
s32 Game_ScriptVarInc(u8* operand);
/* func_8015BABC */
s32 Game_TestNever(void);

#endif
