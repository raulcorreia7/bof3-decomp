#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC380(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            func_801FC8A0(0x91);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            g_ScenarioState.step_05 = 2;
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(37), TO_COORD(174), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_UP_RIGHT);
                    break;
                case 2:
                    Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(37), TO_COORD(174), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_UP);
                    break;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0x1) {
                g_ScenarioState.step_05 = 3;
                SYS_SetFlag(g_SceneFlags, 0x30);
                g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
                switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                    case 1:
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(39), TO_COORD(173), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_DOWN_RIGHT);
                        break;
                    case 2:
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(39), TO_COORD(173), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_RIGHT);
                        break;
                }
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0xA) {
                g_ScenarioState.step_05 = 4;
                SYS_SetFlag(g_SceneFlags, 0x31);
                g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
                switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                    case 1:
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(34), TO_COORD(114), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_DOWN_LEFT);
                        break;
                    case 2:
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(34), TO_COORD(114), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_DOWN);
                        break;
                }
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0x4) {
                g_ScenarioState.step_05 = 5;
                g_Characters[CHAR_INDEX_NINA].party_flags |= PARTY_FLAG_JOINED;
                g_Characters[CHAR_INDEX_MOMO].party_flags |= PARTY_FLAG_JOINED;
                g_Characters[CHAR_INDEX_PECO].party_flags |= PARTY_FLAG_JOINED;
                switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                    case 1:
                        Scene_RunScenario(3);
                        break;
                    case 2:
                        Scene_RunScenario(2);
                        break;
                }
            }
            break;
        case 5:
            if (g_GameStateIndex == 0) {
                g_ScriptVars[0]         = 0x5;
                g_ScenarioState.step_05 = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x5) {
                SYS_SetFlag(g_SceneFlags, 0x32);
                Game_ClearScriptActive();
                Scene_ClearScriptState(&g_ScenarioState.step_05);
            }
            break;
    }
}
