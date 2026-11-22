#ifndef OVERLAY_SCENARIO_SCENA05_00_H
#define OVERLAY_SCENARIO_SCENA05_00_H

/* The scenario/scena05/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "sys/exe.h"
#include "area/spad.h"

/* The scene starter func_801FD178 and func_801FD208 share: both scene flags 6 set and 9 clear raise
 * an event flag, start the script and arm the timer, else return -1. Every change must keep both
 * members matching. */
#define SCENA05_START_SCENE(event_flag, timer)                                      \
    if (SYS_TestFlag(g_SceneFlags, 6) == 0 || SYS_TestFlag(g_SceneFlags, 9) != 0) { \
        return -1;                                                                  \
    }                                                                               \
    SYS_SetFlag(g_SceneEventFlags, event_flag);                                     \
    Game_SetScriptActive();                                                         \
    g_ScriptVars[2] = 0;                                                            \
    g_ScriptVars[3] = 0;                                                            \
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));                                        \
    g_ScenarioState.step_05  = timer;                                               \
    g_ScenarioState.timer_06 = 0;                                                   \
    return 1

extern u32 D_801F6C00;
/* D_801FD5A8 */

extern Callback D_801FD5B4[];
extern u8       D_801FD5C0[];

extern Callback D_801FD5DC[];
extern Callback D_801FD5E8[];
/* D_801FD644 */

extern u8 D_801FD668;
extern s8 (*D_801FD674[])(void);
extern Callback jtbl_801F6DCC[5];

void func_801F7660(s32 x, s32 y, s32 z, u16 angle);

/* Start the scene script at state 13 with its variables and first step cleared. */
#define SCENE_ENTER_STATE_13()     \
    Game_SetScriptActive();        \
    g_ScriptVars[0]          = 0;  \
    g_ScriptVars[1]          = 0;  \
    g_ScriptVars[2]          = 0;  \
    g_ScriptVars[3]          = 0;  \
    g_ScenarioState.step_05  = 0;  \
    g_ScenarioState.state_04 = 13;

#endif
