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
            Scene_SetupParty(g_PartyFieldOrder[0] == 0 ? 8 : 9);
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
                SND_PlaySE(EMI_CUE_ID(SND_BANK_AREA, 4));
                g_SceneState.step_05 = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0x42) {
                SYS_SetFlag(g_SceneFlags, 0x17);
                func_801BFE34(TO_COORD(59), TO_COORD_HALF(72), 0xB);
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
                Scene_SetupParty(g_PartyFieldOrder[0] == 0 ? 23 : 24);
                g_SceneState.step_05 = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x46) {
                g_ScriptVars[2]      = 1;
                g_SceneState.step_05 = 7;
                if (g_PartyFieldOrder[0] == 0) {
                    Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR, TO_COORD(59), TO_COORD(26), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_UP_RIGHT);
                } else {
                    Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR, TO_COORD(59), TO_COORD(26), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_RIGHT);
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
                    Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR, TO_COORD(60), TO_COORD(72), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_UP_RIGHT);
                } else {
                    Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR, TO_COORD(60), TO_COORD(72), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_RIGHT);
                }
            }
            break;
        case 10:
            Game_ClearScriptActive();
            Scene_ClearScriptState(&g_SceneState.step_05);
            break;
    }
}
