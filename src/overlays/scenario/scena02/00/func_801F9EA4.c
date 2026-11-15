#include "scena02_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9EA4(void) {
    switch (g_SceneState.step_05) {
        case 0: {
            u8* vars;

            vars = g_ScriptVars;
            if (vars[0] == 5) {
                vars[0]         = 0;
                g_ScriptVars[2] = 2;
                UI_SetMode(UI_MODE_LONG_FADE_OUT);
                g_SceneState.step_05 = 1;
            }
            if (vars[0] == 6) {
                vars[0]         = 0;
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        }
        case 1:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_801C16B8();
            g_SceneState.step_05 = 2;
            SND_FadeOutSequence(0, 0, 4, 0x1E);
            break;
        case 2:
            SND_StartXAStream(0, 1);
            g_SceneState.step_05 = 3;
            break;
        case 3:
            if ((SND_IsXAIdle() & BYTE_MASK) == 0) {
                break;
            }
            g_SceneState.step_05 = 4;
            break;
        case 4:
            if (g_Game.party_size == 3) {
                g_SceneState.step_05 = 5;
                Game_RequestAreaChange(0x1B, TO_COORD(0x5E), TO_COORD(0x49), 0x8E);
            } else if (g_PartyFieldOrder[0] == 0) {
                g_SceneState.step_05 = 5;
                Game_RequestAreaChange(0x1B, TO_COORD(0x5E), TO_COORD(0x49), 0x8C);
            } else {
                g_SceneState.step_05 = 5;
                Game_RequestAreaChange(0x1B, TO_COORD(0x5E), TO_COORD(0x49), 0x8D);
            }
            SND_PlayBGM(0x21, 100, 8);
            break;
        case 5:
            if (g_ScriptVars[0] == 1) {
                g_ScriptVars[2] = 0;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 10:
            Game_SetScriptActive();
            g_GameFlags |= 8;
            SYS_SetFlag(g_SceneFlags, 0x18);
            func_801BE1B0(0x11);
            g_SceneState.step_05 = 0xB;
            break;
        case 11:
            if (g_ScriptVars[0] == 1) {
                g_ScriptVars[2]      = 4;
                g_SceneState.step_05 = 0xC;
                Game_RequestAreaChange(0x1B, TO_COORD(0x5C), TO_COORD(0x48), 0x93);
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 5) {
                if ((g_UiWindowChannel & 2) != 0) {
                    SND_FadeOutSequence(0, 0, 4, 0x1E);
                    func_801C16B8();
                    g_SceneState.step_05 = 0;
                    g_GameFlags ^= 8;
                }
            }
            if (g_ScriptVars[0] == 6) {
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
                g_GameFlags ^= 8;
            }
            break;
    }
}
