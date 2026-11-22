#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Scene 12 area entry: picks the join message by cell and character, and sets the party flag. */
MATCH void func_801FAE04(void) {
    switch (g_ScenarioState.step) {
        case 0:
            if (g_GameStateIndex == 2) {
                break;
            }
            switch (g_GameCellType) {
                case 2:
                    switch (g_Game.members[0].chr.character_id) {
                        case CHAR_ID_GARR:
                        case CHAR_ID_REI:
                        case CHAR_ID_PECO:
                        case CHAR_ID_RYU_ADULT:
                            UI_MessageStartArea(0x19);
                            g_GameStateIndex     = 2;
                            g_ScenarioState.step = 1;
                            break;
                        case CHAR_ID_TEEPO:
                            break;
                        case CHAR_ID_MOMO:
                        case CHAR_ID_NINA_ADULT:
                            UI_MessageStartArea(0x1A);
                            g_GameStateIndex     = 2;
                            g_ScenarioState.step = 0xA;
                            break;
                    }
                    break;
                case 3:
                    switch (g_Game.members[0].chr.character_id) {
                        case CHAR_ID_GARR:
                        case CHAR_ID_REI:
                        case CHAR_ID_PECO:
                        case CHAR_ID_RYU_ADULT:
                            UI_MessageStartArea(0x18);
                            g_GameStateIndex     = 2;
                            g_ScenarioState.step = 0xA;
                            break;
                        case CHAR_ID_TEEPO:
                            break;
                        case CHAR_ID_MOMO:
                        case CHAR_ID_NINA_ADULT:
                            UI_MessageStartArea(0x19);
                            g_GameStateIndex     = 2;
                            g_ScenarioState.step = 1;
                            break;
                    }
                    break;
            }
            break;
        case 1:
            if (g_GameStateIndex == 2) {
                break;
            }
            if (g_ScriptVars[0] == 0xA) {
                g_ScriptVars[0]      = 0;
                g_ScenarioState.step = 2;
                UI_ModeSet(0xD);
                func_801C16B8();
                SND_SeqFadeOut(0, 1, 4, 0x1E);
                break;
            }
            if (g_ScriptVars[0] != 5) {
                break;
            }
            Game_ClearScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 2:
            SND_XAStartStream(0, 1);
            g_ScenarioState.step = 3;
            break;
        case 3:
            if (!WINDOW_EFFECT_BUSY()) {
                g_AreaDrawFlags = 0;
                if (SND_XAIsIdle() & 0xFF) {
                    g_ScenarioState.step = 4;
                }
            }
            break;
        case 4:
            UI_ModeSet(0xE);
            g_AreaDrawFlags      = 0x1F;
            g_ScenarioState.step = 5;
            break;
        case 5:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            SND_BGMPlay(0x8B, 100, 8);
            Game_ClearScriptActive();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 10:
            if (g_GameStateIndex == 2) {
                break;
            }
            Game_ClearScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 20:
            if (g_GameStateIndex != 0) {
                break;
            }
            g_AreaDrawFlags = 0;
            if (D_8014865F != 1) {
                break;
            }
            g_ScenarioState.step = 0x15;
            switch (g_EmiLoadedCharacterIndex & 0x7F) {
                case 7:
                    SYS_SetFlag(g_SceneFlags, 0x32);
                    SYS_ClearFlag(g_SceneFlags, 0x33);
                    SYS_ClearFlag(g_SceneFlags, 0x34);
                    SYS_ClearFlag(g_SceneFlags, 0x35);
                    SYS_ClearFlag(g_SceneFlags, 0x36);
                    SYS_ClearFlag(g_SceneFlags, 0x37);
                    SYS_ClearFlag(g_SceneFlags, 0x38);
                    SYS_ClearFlag(g_SceneFlags, 0x39);
                    SYS_ClearFlag(g_SceneFlags, 0x3A);
                    SYS_ClearFlag(g_SceneFlags, 0x3B);
                    break;
                case 8:
                    SYS_SetFlag(g_SceneFlags, 0x33);
                    SYS_ClearFlag(g_SceneFlags, 0x32);
                    SYS_ClearFlag(g_SceneFlags, 0x34);
                    SYS_ClearFlag(g_SceneFlags, 0x35);
                    SYS_ClearFlag(g_SceneFlags, 0x36);
                    SYS_ClearFlag(g_SceneFlags, 0x37);
                    SYS_ClearFlag(g_SceneFlags, 0x38);
                    SYS_ClearFlag(g_SceneFlags, 0x39);
                    SYS_ClearFlag(g_SceneFlags, 0x3A);
                    SYS_ClearFlag(g_SceneFlags, 0x3B);
                    break;
                case 9:
                    SYS_SetFlag(g_SceneFlags, 0x34);
                    SYS_ClearFlag(g_SceneFlags, 0x32);
                    SYS_ClearFlag(g_SceneFlags, 0x33);
                    SYS_ClearFlag(g_SceneFlags, 0x35);
                    SYS_ClearFlag(g_SceneFlags, 0x36);
                    SYS_ClearFlag(g_SceneFlags, 0x37);
                    SYS_ClearFlag(g_SceneFlags, 0x38);
                    SYS_ClearFlag(g_SceneFlags, 0x39);
                    SYS_ClearFlag(g_SceneFlags, 0x3A);
                    SYS_ClearFlag(g_SceneFlags, 0x3B);
                    break;
                case 10:
                    SYS_SetFlag(g_SceneFlags, 0x35);
                    SYS_ClearFlag(g_SceneFlags, 0x32);
                    SYS_ClearFlag(g_SceneFlags, 0x33);
                    SYS_ClearFlag(g_SceneFlags, 0x34);
                    SYS_ClearFlag(g_SceneFlags, 0x36);
                    SYS_ClearFlag(g_SceneFlags, 0x37);
                    SYS_ClearFlag(g_SceneFlags, 0x38);
                    SYS_ClearFlag(g_SceneFlags, 0x39);
                    SYS_ClearFlag(g_SceneFlags, 0x3A);
                    SYS_ClearFlag(g_SceneFlags, 0x3B);
                    break;
                case 11:
                case 12:
                    break;
                case 13:
                    SYS_SetFlag(g_SceneFlags, 0x36);
                    SYS_ClearFlag(g_SceneFlags, 0x32);
                    SYS_ClearFlag(g_SceneFlags, 0x33);
                    SYS_ClearFlag(g_SceneFlags, 0x34);
                    SYS_ClearFlag(g_SceneFlags, 0x35);
                    SYS_ClearFlag(g_SceneFlags, 0x37);
                    SYS_ClearFlag(g_SceneFlags, 0x38);
                    SYS_ClearFlag(g_SceneFlags, 0x39);
                    SYS_ClearFlag(g_SceneFlags, 0x3A);
                    SYS_ClearFlag(g_SceneFlags, 0x3B);
                    break;
                case 14:
                    SYS_SetFlag(g_SceneFlags, 0x37);
                    SYS_ClearFlag(g_SceneFlags, 0x32);
                    SYS_ClearFlag(g_SceneFlags, 0x33);
                    SYS_ClearFlag(g_SceneFlags, 0x34);
                    SYS_ClearFlag(g_SceneFlags, 0x35);
                    SYS_ClearFlag(g_SceneFlags, 0x36);
                    SYS_ClearFlag(g_SceneFlags, 0x38);
                    SYS_ClearFlag(g_SceneFlags, 0x39);
                    SYS_ClearFlag(g_SceneFlags, 0x3A);
                    SYS_ClearFlag(g_SceneFlags, 0x3B);
                    break;
                case 15:
                    SYS_SetFlag(g_SceneFlags, 0x38);
                    SYS_ClearFlag(g_SceneFlags, 0x32);
                    SYS_ClearFlag(g_SceneFlags, 0x33);
                    SYS_ClearFlag(g_SceneFlags, 0x34);
                    SYS_ClearFlag(g_SceneFlags, 0x35);
                    SYS_ClearFlag(g_SceneFlags, 0x36);
                    SYS_ClearFlag(g_SceneFlags, 0x37);
                    SYS_ClearFlag(g_SceneFlags, 0x39);
                    SYS_ClearFlag(g_SceneFlags, 0x3A);
                    SYS_ClearFlag(g_SceneFlags, 0x3B);
                    break;
                case 16:
                    SYS_SetFlag(g_SceneFlags, 0x39);
                    SYS_ClearFlag(g_SceneFlags, 0x32);
                    SYS_ClearFlag(g_SceneFlags, 0x33);
                    SYS_ClearFlag(g_SceneFlags, 0x34);
                    SYS_ClearFlag(g_SceneFlags, 0x35);
                    SYS_ClearFlag(g_SceneFlags, 0x36);
                    SYS_ClearFlag(g_SceneFlags, 0x37);
                    SYS_ClearFlag(g_SceneFlags, 0x38);
                    SYS_ClearFlag(g_SceneFlags, 0x3A);
                    SYS_ClearFlag(g_SceneFlags, 0x3B);
                    break;
                case 17:
                    SYS_SetFlag(g_SceneFlags, 0x3A);
                    SYS_ClearFlag(g_SceneFlags, 0x32);
                    SYS_ClearFlag(g_SceneFlags, 0x33);
                    SYS_ClearFlag(g_SceneFlags, 0x34);
                    SYS_ClearFlag(g_SceneFlags, 0x35);
                    SYS_ClearFlag(g_SceneFlags, 0x36);
                    SYS_ClearFlag(g_SceneFlags, 0x37);
                    SYS_ClearFlag(g_SceneFlags, 0x38);
                    SYS_ClearFlag(g_SceneFlags, 0x39);
                    SYS_ClearFlag(g_SceneFlags, 0x3B);
                    break;
                case 18:
                    SYS_SetFlag(g_SceneFlags, 0x3B);
                    SYS_ClearFlag(g_SceneFlags, 0x32);
                    SYS_ClearFlag(g_SceneFlags, 0x33);
                    SYS_ClearFlag(g_SceneFlags, 0x34);
                    SYS_ClearFlag(g_SceneFlags, 0x35);
                    SYS_ClearFlag(g_SceneFlags, 0x36);
                    SYS_ClearFlag(g_SceneFlags, 0x37);
                    SYS_ClearFlag(g_SceneFlags, 0x38);
                    SYS_ClearFlag(g_SceneFlags, 0x39);
                    SYS_ClearFlag(g_SceneFlags, 0x3A);
                    break;
            }
            func_8019FA28(0xBC, 0xC8000, 0xA8000, 0x95);
            break;
        case 21:
            g_AreaDrawFlags = 0x1F;
            Game_ClearScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 30: {
            u8* state = &g_GameStateIndex;

            if (*state != 0) {
                break;
            }
            g_ScriptVars[0] = 1;
            UI_MessageStartArea(0x20);
            *state               = 2;
            g_ScenarioState.step = 0x1F;
            break;
        }
        case 31:
            if (g_GameStateIndex != 0) {
                break;
            }
            g_ScriptVars[0]      = 2;
            g_ScenarioState.step = 0x20;
            break;
        case 32: {
            u8* vars = g_ScriptVars;

            if (vars[0] != 3) {
                break;
            }
            Game_ClearScriptActive();
            vars[0]                  = 0;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0;
            break;
        }
    }
}
