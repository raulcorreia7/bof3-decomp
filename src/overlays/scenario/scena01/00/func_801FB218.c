#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/Area_DrawDimQuad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB218(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_ScriptVars[0] = 0xA;
            Message_StartAreaMessage(0x18);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_SceneState.step_05 = 2;
            break;
        case 2: {
            u8* vars;

            vars = g_ScriptVars;
            if (vars[0] == 0x14) {
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0x1B;
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_SceneState.state_04 = 9;
            } else {
                g_SceneState.step_05 = 3;
                SYS_ClearFlag(g_SceneFlags, 0x10);
                vars[0] = 0xB;
            }
            break;
        }
        case 3:
            Scene_SetupParty(8);
            g_SceneState.step_05 = 4;
            break;
        case 4:
            g_SceneState.step_05 = 0xB;
            break;
        case 11:
            if (g_ScriptVars[0] == 0x14) {
                g_SceneState.step_05 = 0xC;
                SND_PlayCue(0x205);
                SND_PlayCue(0x206);
                g_ScriptVars[2] = 5;
                if (SYS_TestFlag(g_SceneFlags, 0x12) == 0) {
                    g_SceneState.step_05 = 0xC;
                    g_ScriptVars[2]      = 6;
                    Game_RequestAreaChange(AREA_ID_MOUNT_GLAUS, TO_COORD(0xF), TO_COORD(0x28), 0x84);
                } else if (SYS_TestFlag(g_SceneFlags, 0x14) == 0) {
                    g_ScriptVars[2]      = 6;
                    g_SceneState.step_05 = 0x1E;
                    Game_RequestAreaChange(AREA_ID_MOUNT_GLAUS, TO_COORD(0xF), TO_COORD(0x28), 0x84);
                } else {
                    g_ScriptVars[2]      = 6;
                    g_SceneState.step_05 = 0x14;
                    Game_RequestAreaChange(AREA_ID_MOUNT_GLAUS, TO_COORD(0xF), TO_COORD(0x28), 0x85);
                }
            }
            break;
        case 12:
            func_801C601C(3);
            g_SceneState.step_05 = 0xD;
            break;
        case 13:
            if (g_ScriptVars[0] == 0xA) {
                Game_ClearScriptActive();
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 20:
            func_801C601C(6);
            g_SceneState.step_05 = 0x15;
            break;
        case 21:
            if (g_ScriptVars[0] == 8) {
                func_801C601C(4);
                g_SceneState.step_05 = 0x19;
            }
            break;
        case 25:
            if (g_ScriptVars[0] == 0xD) {
                g_GameFlags ^= 0x80;
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
                Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE, TO_COORD(0x30), TO_COORD(1), 0);
                g_GamePrevSelection = 0xFF;
            }
            break;
        case 30:
            func_801C601C(3);
            g_SceneState.step_05 = 0x1F;
            break;
        case 31:
            if (g_ScriptVars[0] == 0xA) {
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
                Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE, TO_COORD(0x30), TO_COORD(1), 0);
                g_GamePrevSelection = 0xFF;
            }
            break;
    }
}
