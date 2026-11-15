#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9BD0(void) {
    switch (g_SceneState.step_05) {
        case 0:
            func_801BE1B0(g_PartyFieldOrder[0] == 0 ? 8 : 9);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 0x3E) {
                Area_StartScrollRoute(3);
                g_SceneState.step_05 = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0x41) {
                SND_PlayCue(0x204);
                g_SceneState.step_05 = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0x42) {
                SYS_SetFlag(g_SceneFlags, 0x17);
                func_801BFE34(TO_COORD(0x3B), TO_COORD_HALF(0x48), 0xB);
                g_SceneState.step_05 = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0x43) {
                Battle_StartScripted(0xB);
                g_SceneState.step_05 = 5;
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 0x44) {
                func_801BE1B0(g_PartyFieldOrder[0] == 0 ? 0x17 : 0x18);
                g_SceneState.step_05 = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x46) {
                g_ScriptVars[2]      = 1;
                g_SceneState.step_05 = 7;
                if (g_PartyFieldOrder[0] == 0) {
                    Game_RequestAreaChange(0x1B, TO_COORD(0x3B), TO_COORD(0x1A), 0x8A);
                } else {
                    Game_RequestAreaChange(0x1B, TO_COORD(0x3B), TO_COORD(0x1A), 0x8B);
                }
                g_GamePrevSelection = 0x22;
            }
            break;
        case 7:
            Area_StartScrollRoute(4);
            g_SceneState.step_05 = 8;
            break;
        case 8:
            if (g_ScriptVars[0] == 0x4B) {
                SYS_SetFlag(g_SceneFlags, 0x14);
                g_ScriptVars[2]      = 1;
                g_SceneState.step_05 = 10;
                if (g_PartyFieldOrder[0] == 0) {
                    Game_RequestAreaChange(0x1B, TO_COORD(0x3C), TO_COORD(0x48), 0x8A);
                } else {
                    Game_RequestAreaChange(0x1B, TO_COORD(0x3C), TO_COORD(0x48), 0x8B);
                }
            }
            break;
        case 10:
            Game_ClearScriptActive();
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
    }
}
