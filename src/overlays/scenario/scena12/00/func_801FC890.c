#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING s32 func_801FC890(s32 x, s32 y) {
    if (g_GameAreaId == AREA_ID_PLANT) {
        if (SYS_TestFlag(g_SceneFlags, 9) && SYS_TestFlag(g_SceneFlags, 11) == 0 && (x == TO_COORD(77) || x == TO_COORD_HALF(77)) && (u32)(y - TO_COORD(33)) <= TO_COORD_HALF(4)) {
            {
                Game_SetScriptActive();
                g_ScriptVars[0]       = 0;
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 7;
            }
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_DUMP) {
        if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
            if ((u32)(x - TO_COORD(147)) <= TO_COORD_HALF(1) && (y == TO_COORD(6) || y == TO_COORD_HALF(6))) {
                {
                    Game_SetScriptActive();
                    g_ScriptVars[0]       = 0;
                    g_ScriptVars[1]       = 0;
                    g_ScriptVars[2]       = 0;
                    g_ScriptVars[3]       = 0;
                    g_SceneState.step_05  = 0;
                    g_SceneState.state_04 = 4;
                }
                return 1;
            }
        } else if (SYS_TestFlag(g_SceneFlags, 9) == 0 && (u32)(x - TO_COORD(132)) <= TO_COORD_HALF(2) && (y == TO_COORD(12) || y == TO_COORD_HALF(12) || y == TO_COORD(24) || y == TO_COORD_HALF(24))) {
            Game_SetScriptActive();
            g_SceneState.step_05 = 20;
            SCRIPT_VARS_CLEAR_ALL();
            g_SceneState.state_04 = 4;
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_MAEKYSS_GORGE && (y == TO_COORD(52) || y == TO_COORD_HALF(52)) && (u32)(x - TO_COORD(29)) <= TO_COORD_HALF(1)) {
        {
            Game_SetScriptActive();
            g_ScriptVars[0]       = 0;
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 11;
        }
        return 1;
    }
    if (g_GameAreaId == AREA_ID_CAFE) {
        if (SYS_TestFlag(g_SceneFlags, 0) == 0 && (y == TO_COORD(36) || y == TO_COORD_HALF(36)) && (u32)(x - TO_COORD(25)) <= TO_COORD_HALF(6)) {
            {
                Game_SetScriptActive();
                g_ScriptVars[0]       = 0;
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 1;
            }
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_CONTEST_OUTER && SYS_TestFlag(g_SceneFlags, 61)) {
        if (SYS_TestFlag(g_SceneFlags, 50) == 0) {
            if (x == TO_COORD_HALF(40) || x == TO_COORD(41)) {
                if ((u32)(y - TO_COORD(126)) <= TO_COORD_HALF(3)) {
                    {
                        Game_SetScriptActive();
                        g_ScriptVars[0]       = 0;
                        g_ScriptVars[1]       = 0;
                        g_ScriptVars[2]       = 0;
                        g_ScriptVars[3]       = 0;
                        g_SceneState.step_05  = 0;
                        g_SceneState.state_04 = 19;
                    }
                    return 1;
                }
            } else if (x == TO_COORD(31) || x == TO_COORD_HALF(31)) {
                if ((u32)(y - TO_COORD(113)) <= TO_COORD_HALF(1)) {
                    {
                        Game_SetScriptActive();
                        g_ScriptVars[0]       = 0;
                        g_ScriptVars[1]       = 0;
                        g_ScriptVars[2]       = 0;
                        g_ScriptVars[3]       = 0;
                        g_SceneState.step_05  = 0;
                        g_SceneState.state_04 = 20;
                    }
                    return 1;
                }
            }
        } else if ((x == TO_COORD(31) || x == TO_COORD_HALF(31)) && (u32)(y - TO_COORD(113)) <= TO_COORD_HALF(1)) {
            {
                Game_SetScriptActive();
                g_ScriptVars[0]       = 0;
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 22;
            }
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM(func_801FC890);
#endif
