#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Starts the scene script for the trigger cell at (x, y) in the current area; returns 1 when one starts. */
MATCH s32 func_801FC890(s32 x, s32 y) {
    if (g_GameAreaId == AREA_ID_BLACK_SHIP_AMMONITE) {
        if (!SYS_TestFlag(g_SceneFlags, 1)) {
            if ((u32)(x - TO_COORD_HALF(31)) <= TO_COORD(1) && (u32)(y - TO_COORD_HALF(36)) <= TO_COORD_HALF(2)) {
                Game_SetScriptActive();
                g_ScenarioState.step_05  = 0xA;
                g_ScriptVars[0]          = 0;
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.state_04 = 9;
                Area_CellSetCode(0x2D, 0x29, 0x70);
                Area_CellSetCode(0x2D, 0x2A, 0x70);
                Area_CellSetCode(0x2E, 0x29, 0x70);
                Area_CellSetCode(0x2E, 0x2A, 0x70);
                SYS_SetFlag(g_SceneFlags, 1);
                return 1;
            }
        } else if (g_Game.members[0].pos.z.fixed <= TO_COORD(0x200) && (u32)(x - TO_COORD(46)) <= TO_COORD_HALF(1) && (u32)(y - TO_COORD(41)) <= TO_COORD(1)) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 0x21;
            g_ScriptVars[0]          = 0;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.state_04 = 9;
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_BOAT_AFTER_BLACK_SHIP) {
        if (!SYS_TestFlag(g_SceneFlags, 0x19) && (u32)(x - TO_COORD(51)) <= TO_COORD_HALF(1) && (u32)(y - TO_COORD(41)) <= COORD_HALF) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 0xA;
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 4;
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_BLACK_SHIP_BOOST_COUNTER && SYS_TestFlag(g_SceneFlags, 0x25) && !SYS_TestFlag(g_SceneFlags, 0x26) && x > TO_COORD(27) && (u32)((y >> 16) - 7) < 5) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 5;
        g_ScenarioState.step_05  = 0x1B;
        return 1;
    }
    if (g_GameAreaId == AREA_ID_BLACK_SHIP && !SYS_TestFlag(g_SceneFlags, 0x2B)) {
        if ((u32)(x - TO_COORD(28)) <= TO_COORD_HALF(1) && (u32)(y - TO_COORD_HALF(3)) <= TO_COORD(1)) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 5;
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 7;
            return 1;
        }
        if ((u32)(x - TO_COORD(57)) <= TO_COORD_HALF(1) && (u32)(y - TO_COORD(71)) <= TO_COORD_HALF(1)) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 5;
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 7;
            return 1;
        }
        if ((u32)(x - TO_COORD_HALF(54)) <= COORD_HALF && (u32)(y - TO_COORD(63)) <= COORD_HALF) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 0xA;
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 7;
            return 1;
        }
    }
    return 0;
}
