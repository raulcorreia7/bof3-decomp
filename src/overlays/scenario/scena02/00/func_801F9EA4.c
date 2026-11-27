#include "scena02_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9EA4(void) {
    switch (g_ScenarioState.step) {
        case 0: {
            u8* vars;

            vars = g_ScriptVars;
            if (vars[0] == 5) {
                vars[0]         = 0;
                g_ScriptVars[2] = 2;
                UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                g_ScenarioState.step = 1;
            }
            if (vars[0] == 6) {
                vars[0]         = 0;
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
        }
        case 1:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_801C16B8();
            g_ScenarioState.step = 2;
            SND_SeqFadeOut(0, 0, 4, 0x1E);
            break;
        case 2:
            SND_XAStartStream(0, 1);
            g_ScenarioState.step = 3;
            break;
        case 3:
            if ((SND_XAIsIdle() & BYTE_MASK) == 0) {
                break;
            }
            g_ScenarioState.step = 4;
            break;
        case 4:
            if (g_Game.party_size == 3) {
                g_ScenarioState.step = 5;
                Game_RequestAreaChange(0x1B, TO_COORD(0x5E), TO_COORD(0x49), 0x8E);
            } else if (g_PartyFieldOrder[0] == 0) {
                g_ScenarioState.step = 5;
                Game_RequestAreaChange(0x1B, TO_COORD(0x5E), TO_COORD(0x49), 0x8C);
            } else {
                g_ScenarioState.step = 5;
                Game_RequestAreaChange(0x1B, TO_COORD(0x5E), TO_COORD(0x49), 0x8D);
            }
            SND_BGMPlay(0x21, 100, 8);
            break;
        case 5:
            if (g_ScriptVars[0] == 1) {
                g_ScriptVars[2] = 0;
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 10:
            Game_SetScriptActive();
            g_GameFlags |= 8;
            SYS_SetFlag(g_SceneFlags, 0x18);
            Scene_SetupParty(0x11);
            g_ScenarioState.step = 0xB;
            break;
        case 11:
            if (g_ScriptVars[0] == 1) {
                g_ScriptVars[2]      = 4;
                g_ScenarioState.step = 0xC;
                Game_RequestAreaChange(0x1B, TO_COORD(0x5C), TO_COORD(0x48), 0x93);
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 5) {
                if ((g_UIWindowChannel & 2) != 0) {
                    SND_SeqFadeOut(0, 0, 4, 0x1E);
                    func_801C16B8();
                    g_ScenarioState.step = 0;
                    g_GameFlags ^= 8;
                }
            }
            if (g_ScriptVars[0] == 6) {
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
                g_GameFlags ^= 8;
            }
            break;
    }
}
