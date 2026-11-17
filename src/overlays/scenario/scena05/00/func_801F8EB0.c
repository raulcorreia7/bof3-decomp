#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8EB0(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            SND_PlayBGM(1, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 0x5) {
                g_ScriptVars[0]         = 0x6;
                g_ScenarioState.step_05 = 2;
            }
            /* fallthrough */
        case 2:
            if (g_ScriptVars[0] == 0x8) {
                g_ScenarioState.step_05 = 3;
                SYS_SetFlag(g_SceneFlags, 0x10);
                Game_RequestAreaChange(AREA_ID_WYNDIA_WORLD_MAP, TO_COORD(60), TO_COORD(46), AREA_ENTRY_MAP_LOADING | FACING_RIGHT);
                g_GamePrevSelection = 1;
            }
            break;
        case 3:
            Area_StartScrollRoute(3);
            g_ScenarioState.step_05 = 10;
            break;
        case 10:
            if (g_ScriptVars[0] == 0xC) {
                g_ScenarioState.step_05 = 11;
                g_ScriptVars[0]         = 0x14;
                SYS_SetFlag(g_SceneFlags, 0x11);
                g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
                Game_RequestAreaChange(AREA_ID_GENMEL, TO_COORD(8), TO_COORD(38), AREA_ENTRY_MAP_LOADING | FACING_UP_LEFT);
            }
            break;
        case 11:
            if (g_ScriptVars[0] == 0x1C) {
                Area_StartScrollRoute(0);
                g_ScenarioState.step_05 = 12;
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 0x1D) {
                g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
                SYS_SetFlag(g_SceneFlags, 0x12);
                switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                    case 1:
                        g_ScriptVars[2] = 0;
                        SYS_SetFlag(g_SceneFlags, 0x13);
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(36), TO_COORD(173), AREA_ENTRY_MAP_LOADING | FACING_UP_LEFT);
                        g_GamePrevSelection = GAME_NONE;
                        break;
                    case 2:
                        g_ScriptVars[2] = 2;
                        SYS_SetFlag(g_SceneFlags, 0x13);
                        func_801C1E3C(3);
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(36), TO_COORD(173), FACING_RIGHT);
                        g_GamePrevSelection = GAME_NONE;
                        break;
                    case 6:
                        g_ScriptVars[2] = 3;
                        SYS_SetFlag(g_SceneFlags, 0x13);
                        func_801C1E3C(3);
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(36), TO_COORD(173), FACING_RIGHT);
                        g_GamePrevSelection = GAME_NONE;
                        break;
                }
            }
            break;
    }
}
