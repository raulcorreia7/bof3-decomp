#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8A04(void) {
    u8   row;
    u16  column;
    u16* line;
    u16  value;
    u32  gray;
    u8*  state;
    u32  alpha;

    switch (g_ScenarioState.step_05) {
        case 0:
            g_ScriptVars[0]         = 0;
            g_ScriptVars[2]         = 0;
            g_ScenarioState.step_05 = 1;
            Game_RequestAreaChange(0x85, TO_COORD(5), TO_COORD(93), 0x80);
            break;
        case 1:
            Area_ScrollStartRoute(0);
            g_ScenarioState.step_05 = 2;
            break;
        case 2:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_GameFlags |= 0x16;
            SYS_SetFlag(g_SceneFlags, 0x16);
            SYS_SetFlag(g_SceneFlags, 0);
            Game_ClearScriptActive();
            SCRIPT_VARS_CLEAR_ALL();
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 10:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA12_011, 11);
            break;
        case 11:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_ClearScriptActive();
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 20:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[0] = 1;
            func_801BE1B0(1);
            g_ScenarioState.step_05 = 21;
            break;
        case 21:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            g_ScriptVars[2]         = 2;
            g_ScriptVars[0]         = 0;
            g_ScenarioState.step_05 = 22;
            SYS_SetFlag(g_SceneFlags, 0x17);
            Game_RequestAreaChange(0x65, TO_COORD(68), TO_COORD_HALF(8), 0x82);
            g_GamePrevSelection = 0xFF;
            break;
        case 22:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            SCENARIO_MESSAGE_WAIT(MSG_SCENA12_017, 23);
            break;
        case 23:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            for (row = 0; row < 32; row++) {
                column = 0;
                line   = MEM_PTR(u16, AREA_PALETTE_WORK) + row * 256;
                for (; column < 256; column++) {
                    value        = line[column];
                    alpha        = value & 0x8000;
                    gray         = (u32)((value & 0x1F) + ((value >> 5) & 0x1F) + ((value >> 10) & 0x1F)) / 3;
                    line[column] = gray | (alpha | (gray << 10) | (gray << 5));
                }
            }
            g_GfxPalettePending     = 1;
            g_AreaDrawFlags         = AREA_DRAW_ALL_FLAGS;
            g_ScriptVars[0]         = 1;
            g_ScriptVars[2]         = 0;
            g_ScenarioState.step_05 = 24;
            break;
        case 24:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            g_ScriptVars[2]         = 0;
            g_ScriptVars[0]         = 0;
            g_ScenarioState.step_05 = 25;
            SYS_SetFlag(g_SceneFlags, 0x18);
            Game_RequestAreaChange(0x85, TO_COORD(30), TO_COORD(93), 0x82);
            SND_BGMPlay(0x8F, 100, 8);
            break;
        case 25:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            UI_ModeSet(4);
            g_ScenarioState.step_05 = 26;
            break;
        case 26:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScriptVars[0] = 0;
            g_AreaDrawFlags = 0;
            g_GameFlags ^= 0x16;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA12_017, 27);
            break;
        case 27:
            state = &g_GameStateIndex;
            if (*state == GAME_REQUEST_MESSAGE) {
                break;
            }
            *state                  = GAME_REQUEST_SHOP;
            g_ScenarioState.step_05 = 28;
            break;
        case 28:
            if (g_GameStateIndex != 0) {
                break;
            }
            g_ScenarioState.step_05 = 29;
            SYS_SetFlag(g_SceneFlags, 0x19);
            Char_RebuildPartyStats();
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 7:
                    SYS_SetFlag(g_SceneFlags, 0x1A);
                    break;
                case 8:
                    SYS_SetFlag(g_SceneFlags, 0x1B);
                    break;
                case 9:
                    SYS_SetFlag(g_SceneFlags, 0x1C);
                    break;
                case 10:
                    SYS_SetFlag(g_SceneFlags, 0x1D);
                    break;
                case 13:
                    SYS_SetFlag(g_SceneFlags, 0x1E);
                    break;
                case 14:
                    SYS_SetFlag(g_SceneFlags, 0x1F);
                    break;
                case 15:
                    SYS_SetFlag(g_SceneFlags, 0x20);
                    break;
                case 16:
                    SYS_SetFlag(g_SceneFlags, 0x21);
                    break;
                case 17:
                    SYS_SetFlag(g_SceneFlags, 0x22);
                    break;
                case 18:
                    SYS_SetFlag(g_SceneFlags, 0x23);
                    break;
            }
            Game_RequestAreaChange(0x85, TO_COORD(61), TO_COORD_HALF(43), 0x83);
            break;
        case 30:
            if (g_GameStateIndex != 0) {
                break;
            }
            if (D_8014865F != 1) {
                break;
            }
            g_ScenarioState.step_05 = 39;
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 7:
                    SYS_SetFlag(g_SceneFlags, 0x1A);
                    SYS_ClearFlag(g_SceneFlags, 0x1B);
                    SYS_ClearFlag(g_SceneFlags, 0x1C);
                    SYS_ClearFlag(g_SceneFlags, 0x1D);
                    SYS_ClearFlag(g_SceneFlags, 0x1E);
                    SYS_ClearFlag(g_SceneFlags, 0x1F);
                    SYS_ClearFlag(g_SceneFlags, 0x20);
                    SYS_ClearFlag(g_SceneFlags, 0x21);
                    SYS_ClearFlag(g_SceneFlags, 0x22);
                    SYS_ClearFlag(g_SceneFlags, 0x23);
                    break;
                case 8:
                    SYS_SetFlag(g_SceneFlags, 0x1B);
                    SYS_ClearFlag(g_SceneFlags, 0x1A);
                    SYS_ClearFlag(g_SceneFlags, 0x1C);
                    SYS_ClearFlag(g_SceneFlags, 0x1D);
                    SYS_ClearFlag(g_SceneFlags, 0x1E);
                    SYS_ClearFlag(g_SceneFlags, 0x1F);
                    SYS_ClearFlag(g_SceneFlags, 0x20);
                    SYS_ClearFlag(g_SceneFlags, 0x21);
                    SYS_ClearFlag(g_SceneFlags, 0x22);
                    SYS_ClearFlag(g_SceneFlags, 0x23);
                    break;
                case 9:
                    SYS_SetFlag(g_SceneFlags, 0x1C);
                    SYS_ClearFlag(g_SceneFlags, 0x1A);
                    SYS_ClearFlag(g_SceneFlags, 0x1B);
                    SYS_ClearFlag(g_SceneFlags, 0x1D);
                    SYS_ClearFlag(g_SceneFlags, 0x1E);
                    SYS_ClearFlag(g_SceneFlags, 0x1F);
                    SYS_ClearFlag(g_SceneFlags, 0x20);
                    SYS_ClearFlag(g_SceneFlags, 0x21);
                    SYS_ClearFlag(g_SceneFlags, 0x22);
                    SYS_ClearFlag(g_SceneFlags, 0x23);
                    break;
                case 10:
                    SYS_SetFlag(g_SceneFlags, 0x1D);
                    SYS_ClearFlag(g_SceneFlags, 0x1A);
                    SYS_ClearFlag(g_SceneFlags, 0x1B);
                    SYS_ClearFlag(g_SceneFlags, 0x1C);
                    SYS_ClearFlag(g_SceneFlags, 0x1E);
                    SYS_ClearFlag(g_SceneFlags, 0x1F);
                    SYS_ClearFlag(g_SceneFlags, 0x20);
                    SYS_ClearFlag(g_SceneFlags, 0x21);
                    SYS_ClearFlag(g_SceneFlags, 0x22);
                    SYS_ClearFlag(g_SceneFlags, 0x23);
                    break;
                case 13:
                    SYS_SetFlag(g_SceneFlags, 0x1E);
                    SYS_ClearFlag(g_SceneFlags, 0x1A);
                    SYS_ClearFlag(g_SceneFlags, 0x1B);
                    SYS_ClearFlag(g_SceneFlags, 0x1C);
                    SYS_ClearFlag(g_SceneFlags, 0x1D);
                    SYS_ClearFlag(g_SceneFlags, 0x1F);
                    SYS_ClearFlag(g_SceneFlags, 0x20);
                    SYS_ClearFlag(g_SceneFlags, 0x21);
                    SYS_ClearFlag(g_SceneFlags, 0x22);
                    SYS_ClearFlag(g_SceneFlags, 0x23);
                    break;
                case 14:
                    SYS_SetFlag(g_SceneFlags, 0x1F);
                    SYS_ClearFlag(g_SceneFlags, 0x1A);
                    SYS_ClearFlag(g_SceneFlags, 0x1B);
                    SYS_ClearFlag(g_SceneFlags, 0x1C);
                    SYS_ClearFlag(g_SceneFlags, 0x1D);
                    SYS_ClearFlag(g_SceneFlags, 0x1E);
                    SYS_ClearFlag(g_SceneFlags, 0x20);
                    SYS_ClearFlag(g_SceneFlags, 0x21);
                    SYS_ClearFlag(g_SceneFlags, 0x22);
                    SYS_ClearFlag(g_SceneFlags, 0x23);
                    break;
                case 15:
                    SYS_SetFlag(g_SceneFlags, 0x20);
                    SYS_ClearFlag(g_SceneFlags, 0x1A);
                    SYS_ClearFlag(g_SceneFlags, 0x1B);
                    SYS_ClearFlag(g_SceneFlags, 0x1C);
                    SYS_ClearFlag(g_SceneFlags, 0x1D);
                    SYS_ClearFlag(g_SceneFlags, 0x1E);
                    SYS_ClearFlag(g_SceneFlags, 0x1F);
                    SYS_ClearFlag(g_SceneFlags, 0x21);
                    SYS_ClearFlag(g_SceneFlags, 0x22);
                    SYS_ClearFlag(g_SceneFlags, 0x23);
                    break;
                case 16:
                    SYS_SetFlag(g_SceneFlags, 0x21);
                    SYS_ClearFlag(g_SceneFlags, 0x1A);
                    SYS_ClearFlag(g_SceneFlags, 0x1B);
                    SYS_ClearFlag(g_SceneFlags, 0x1C);
                    SYS_ClearFlag(g_SceneFlags, 0x1D);
                    SYS_ClearFlag(g_SceneFlags, 0x1E);
                    SYS_ClearFlag(g_SceneFlags, 0x1F);
                    SYS_ClearFlag(g_SceneFlags, 0x20);
                    SYS_ClearFlag(g_SceneFlags, 0x22);
                    SYS_ClearFlag(g_SceneFlags, 0x23);
                    break;
                case 17:
                    SYS_SetFlag(g_SceneFlags, 0x22);
                    SYS_ClearFlag(g_SceneFlags, 0x1A);
                    SYS_ClearFlag(g_SceneFlags, 0x1B);
                    SYS_ClearFlag(g_SceneFlags, 0x1C);
                    SYS_ClearFlag(g_SceneFlags, 0x1D);
                    SYS_ClearFlag(g_SceneFlags, 0x1E);
                    SYS_ClearFlag(g_SceneFlags, 0x1F);
                    SYS_ClearFlag(g_SceneFlags, 0x20);
                    SYS_ClearFlag(g_SceneFlags, 0x21);
                    SYS_ClearFlag(g_SceneFlags, 0x23);
                    break;
                case 18:
                    SYS_SetFlag(g_SceneFlags, 0x23);
                    SYS_ClearFlag(g_SceneFlags, 0x1A);
                    SYS_ClearFlag(g_SceneFlags, 0x1B);
                    SYS_ClearFlag(g_SceneFlags, 0x1C);
                    SYS_ClearFlag(g_SceneFlags, 0x1D);
                    SYS_ClearFlag(g_SceneFlags, 0x1E);
                    SYS_ClearFlag(g_SceneFlags, 0x1F);
                    SYS_ClearFlag(g_SceneFlags, 0x20);
                    SYS_ClearFlag(g_SceneFlags, 0x21);
                    SYS_ClearFlag(g_SceneFlags, 0x22);
                    break;
            }
            Game_RequestAreaChange(0x85, TO_COORD(61), TO_COORD_HALF(43), 0x83);
            break;
        case 29:
        case 39:
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            Game_ClearScriptActive();
            SCRIPT_VARS_CLEAR_ALL();
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
    }
}
