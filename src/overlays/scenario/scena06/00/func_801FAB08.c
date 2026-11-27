#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Runs the scene script one step per frame, keyed on g_ScenarioState.step. */
MATCH void func_801FAB08(void) {
    switch (g_ScenarioState.step) {
        case 0:
            func_801FCB80(0x91);
            g_ScenarioState.step = 1;
            break;
        case 1:
            func_801BE1B0(0);
            func_801C601C(0);
            g_ScenarioState.step = 2;
            break;
        case 2:
            if (g_ScriptVars[0] == 1) {
                SND_SeqStop(0, 0);
                SND_BGMPlay(0x45, 100, 8);
                g_ScenarioState.step = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 3) {
                func_801BFE34(TO_COORD(0x1D), TO_COORD(0x1D), 0x17);
                g_ScenarioState.step = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 5) {
                func_801C7A54(0x17);
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 10) {
                func_801BE1B0(1);
                g_ScenarioState.step = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x1D) {
                UI_ModeSet(4);
                g_ScenarioState.step = 7;
            }
            break;
        case 7:
            if (g_SysThreads[2].state == 0) {
                g_AreaDrawFlags = 0;
                g_ScriptVars[0] = 0x1F;
                SND_SeqStop(0, 1);
                SND_SeqPlay(0, 2, 100, 100);
                SCENARIO_MESSAGE_WAIT(MSG_SCENA06_013, 8);
            }
            break;
        case 8:
            if (g_UIWindowChannel & 2) {
                Party_MemberAdd(2);
                g_GameStateIndex     = 6;
                D_8014865F           = 0;
                g_ScenarioState.step = 10;
            }
            break;
        case 10:
            if (D_8014865F != 0) {
                g_ScenarioState.step = 11;
            }
            break;
        case 11:
            g_Characters[g_CharSlot[CHAR_ID_GARR]].party_flags &= ~0x02;
            g_GameStateIndex     = 1;
            D_80148660           = 1;
            g_ScenarioState.step = 12;
            break;
        case 12:
            if (D_80148660 == 0) {
                g_AreaDrawFlags = 0x1F;
                func_801BFE34(TO_COORD(0x1D), TO_COORD(0x1D), 0x18);
                SND_BGMPlay(0x45, 100, 8);
                g_ScenarioState.step = 13;
            }
        case 13:
            if (g_GameStateIndex == 0) {
                g_ScriptVars[0]      = 0x28;
                g_ScenarioState.step = 14;
            }
            break;
        case 14:
            if (g_ScriptVars[0] == 0x3C) {
                func_801C7A54(0x18);
                g_ScenarioState.step = 15;
            }
            break;
        case 15:
            if (g_ScriptVars[0] == 5) {
                func_801BE1B0(3);
                SYS_SetFlag(g_SceneFlags, 0);
                g_ScenarioState.step = 16;
                UI_ModeSet(13);
            }
            break;
        case 16:
            if (g_SysThreads[2].state == 0) {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 17;
            }
            break;
        case 17:
            g_ScenarioState.step = 18;
            SYS_SetFlag(g_SceneFlags, 1);
            switch (g_EmiLoadedCharacterIndex & 0x7F) {
                case 0:
                    g_ScriptVars[2] = 0;
                    func_8019FA28(0x43, TO_COORD(0x1D), TO_COORD(0x1C), 0x82);
                    break;
                case 3:
                    g_ScriptVars[2] = 0;
                    func_801C1E3C(6);
                    func_801C1DF0(6);
                    func_8019FA28(0x43, TO_COORD(0x1D), TO_COORD(0x1C), 0x82);
                    break;
                case 4:
                    g_ScriptVars[2] = 0;
                    func_801C1E3C(4);
                    func_801C1DF0(6);
                    func_8019FA28(0x43, TO_COORD(0x1D), TO_COORD(0x1C), 0x82);
                    break;
            }
            break;
        case 18:
            g_AreaDrawFlags      = 0x1F;
            g_ScenarioState.step = 19;
            break;
        case 19:
            if (g_ScriptVars[0] == 0x14) {
                SND_BGMPlay(0x44, 100, 8);
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                g_ScriptVars[3] = 0;
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
    }
}
