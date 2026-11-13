#ifndef OVERLAY_SCENARIO_SCENA05_00_H
#define OVERLAY_SCENARIO_SCENA05_00_H

/* The scenario/scena05/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"

extern u8 D_80146874;

extern u8  D_80146875;
extern u16 D_80146876;

/* The scene starter func_801FD178 and func_801FD208 share: both scene flags 6 set and 9 clear raise
 * an event flag, start the script and arm the timer, else return -1. Every change must keep both
 * members matching. */
#define SCENA05_START_SCENE(event_flag, timer)                                      \
    if (SYS_TestFlag(g_SceneFlags, 6) == 0 || SYS_TestFlag(g_SceneFlags, 9) != 0) { \
        return -1;                                                                  \
    }                                                                               \
    SYS_SetFlag(g_SceneEventFlags, event_flag);                                     \
    Game_SetScriptActive();                                                         \
    D_80146866 = 0;                                                                 \
    D_80146867 = 0;                                                                 \
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));                                      \
    D_80146875 = timer;                                                             \
    D_80146876 = 0;                                                                 \
    return 1

extern u8       D_80146865;
extern u8       D_80146866;
extern u8       D_80146867;
extern u32      D_801F6C00;
/* D_801FD5A8 */
extern Callback g_SceneEntityDispatch[];

extern Callback D_801FD5B4[];

extern Callback  D_801FD5DC[];
extern Callback  D_801FD5E8[];
/* D_801FD644 */
extern SceneFunc g_SceneActorDispatch[];

extern u8 D_801FD668;
extern s8 (*D_801FD674[])(void);

void func_801F7660(s32 x, s32 y, s32 z, u16 angle);

/* Start the scene script at state 13 with its variables and first step cleared. */
#define SCENE_ENTER_STATE_13()  \
    Game_SetScriptActive();     \
    g_ScriptVars[0]       = 0;  \
    g_ScriptVars[1]       = 0;  \
    g_ScriptVars[2]       = 0;  \
    g_ScriptVars[3]       = 0;  \
    g_SceneState.step_05  = 0;  \
    g_SceneState.state_04 = 13;

#endif
