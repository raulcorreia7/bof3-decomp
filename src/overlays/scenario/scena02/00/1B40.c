#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
/* Runs the scene script one step per frame, keyed on g_ScenarioState.step_05. */
NON_MATCHING void func_801F8740(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            if (g_ScriptVars[0] == 3) {
                func_801C601C(4);
                g_ScenarioState.step_05 = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 8) {
                func_801BFE34(TO_COORD(7), TO_COORD(0xE), 0xE);
                g_ScenarioState.step_05 = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0xB) {
                func_801C7A54(0xE);
                g_ScenarioState.step_05 = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0xC) {
                g_ScriptVars[2] = 1;
                func_801BE1B0(0x12);
                g_ScenarioState.step_05 = 4;
                SYS_SetFlag(g_SceneFlags, 7);
                SYS_SetFlag(g_SceneFlags, 0x3E);
                func_8019FA28(0x1A, TO_COORD(0x34), TO_COORD(8), 0x84);
                g_GamePrevSelection = 0x1F;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0x31) {
                SYS_SetFlag(g_SceneFlags, 0xC);
                SYS_ClearFlag(g_SceneFlags, 0x2C);
                SYS_ClearFlag(g_SceneFlags, 0x2B);
                Game_ClearScriptActive();
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                g_ScriptVars[3] = 0;
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 1) {
                Game_ClearScriptActive();
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.step_05  = 8;
                g_ScenarioState.state_04 = 8;
            }
            break;
        case 6:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA02_154, 7);
            break;
        case 7:
            if (g_GameStateIndex != 2) {
                Game_ClearScriptActive();
                g_ScenarioState.step_05  = 8;
                g_ScenarioState.state_04 = 8;
            }
            break;
        case 8:
            if (g_PartyFieldOrder[0] == 0) {
                if (!SYS_TestFlag(g_SceneFlags, 9) && (u32)((u16)g_Game.members[0].pos.x.part.integer - 4) < 2 && g_Game.members[0].pos.y.part.integer < 5 && g_Game.members[0].unk_4B == 0x42 &&
                    g_Game.members[0].facing == 1) {
                    Game_SetScriptActive();
                    g_ScriptVars[3] = 1;
                    SYS_SetFlag(g_SceneFlags, 9);
                    g_ScenarioState.step_05 = 9;
                }
                if (!SYS_TestFlag(g_SceneFlags, 0xA) && (u32)((u16)g_Game.members[0].pos.x.part.integer - 8) < 2 && g_Game.members[0].pos.y.part.integer < 9 && g_Game.members[0].unk_4B == 0x42 &&
                    g_Game.members[0].facing == 1) {
                    Game_SetScriptActive();
                    g_ScriptVars[3] = 5;
                    SYS_SetFlag(g_SceneFlags, 0xA);
                    g_ScenarioState.step_05 = 10;
                }
                if (!SYS_TestFlag(g_SceneFlags, 0xB) && (u32)((u16)g_Game.members[0].pos.x.part.integer - 0xC) < 2 && g_Game.members[0].pos.y.part.integer < 5 && g_Game.members[0].unk_4B == 0x42 &&
                    g_Game.members[0].facing == 1) {
                    Game_SetScriptActive();
                    g_ScriptVars[3] = 10;
                    SYS_SetFlag(g_SceneFlags, 0xB);
                    g_ScenarioState.step_05 = 11;
                }
            }
            if (g_ScriptVars[2] == 3) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0x35);
                SYS_SetFlag(g_SceneFlags, 0x3E);
                SYS_ClearFlag(g_SceneFlags, 0x34);
                SYS_ClearFlag(g_SceneFlags, 0x2B);
                SYS_ClearFlag(g_SceneFlags, 0x2C);
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                g_ScriptVars[3] = 0;
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 9:
            if (g_ScriptVars[3] == 2) {
                func_801FBF24();
            }
            break;
        case 10:
            if (g_ScriptVars[3] == 6) {
                func_801FBF24();
            }
            break;
        case 11:
            if (g_ScriptVars[3] == 0xB) {
                func_801FBF24();
            }
            break;
    }
}
#else
INCLUDE_ASM(func_801F8740);
#endif
