#include "scena05_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F989C(void) {
}

void func_801FC808(void);

MATCH void func_801F98A4(void) {
    u8* mode;
    s32 lineup;
    s16 message;

    switch (g_ScenarioState.step) {
        case 0:
            if ((g_UiWindowChannel & FRONTEND_FLAG_CONFIRM) == 0) {
                break;
            }
            if (g_ScriptVars[0] == 0x14) {
                g_ScriptVars[0] = 0;
                SCENARIO_MESSAGE_WAIT(MSG_SCENA05_032, 2);
            } else {
                g_ScriptVars[0] = 0;
                SCENARIO_MESSAGE_WAIT(MSG_SCENA05_036, 1);
            }
            break;

        case 1:
            mode = &g_GameStateIndex;
            if (*mode != GAME_REQUEST_MESSAGE) {
                UI_MessageStartArea(MSG_SCENA05_032);
                *mode                = GAME_REQUEST_MESSAGE;
                g_ScenarioState.step = 2;
            }
            break;

        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                if (g_ScriptVars[0] == 0x14) {
                    g_ScenarioState.step = 3;
                } else {
                    g_ScenarioState.step = 4;
                }
            }
            break;

        case 3:
            Game_ClearScriptActive();
            Scene_ClearScriptState(&g_ScenarioState.step);
            break;

        case 4:
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    g_ScenarioState.step = 5;
                    break;
                case 2:
                    g_ScenarioState.step = 6;
                    break;
            }
            break;

        case 5:
            switch (g_PartyBattleOrder[0]) {
                case CHAR_ID_RYU_YOUNG:
                    switch (g_PartyBattleOrder[1]) {
                        case CHAR_ID_NINA_YOUNG:
                            g_ScriptVars[3] = 1;
                            break;
                        case CHAR_ID_MOMO:
                            g_ScriptVars[3] = 2;
                            break;
                        default:
                            return;
                    }
                    break;
                case CHAR_ID_NINA_YOUNG:
                    switch (g_PartyBattleOrder[1]) {
                        case CHAR_ID_RYU_YOUNG:
                            g_ScriptVars[3] = 3;
                            break;
                        case CHAR_ID_MOMO:
                            g_ScriptVars[3] = 4;
                            break;
                        default:
                            return;
                    }
                    break;
                case CHAR_ID_MOMO:
                    switch (g_PartyBattleOrder[1]) {
                        case CHAR_ID_RYU_YOUNG:
                            g_ScriptVars[3] = 5;
                            break;
                        case CHAR_ID_NINA_YOUNG:
                            g_ScriptVars[3] = 6;
                            break;
                        default:
                            return;
                    }
                    break;
                default:
                    return;
            }
            g_ScenarioState.step = 15;
            break;
        case 6:
            switch (g_PartyBattleOrder[0]) {
                case CHAR_ID_RYU_YOUNG:
                    switch (g_PartyBattleOrder[1]) {
                        case CHAR_ID_NINA_YOUNG:
                            g_ScriptVars[3] = 11;
                            break;
                        case CHAR_ID_PECO:
                            g_ScriptVars[3] = 12;
                            break;
                        default:
                            return;
                    }
                    break;
                case CHAR_ID_NINA_YOUNG:
                    switch (g_PartyBattleOrder[1]) {
                        case CHAR_ID_RYU_YOUNG:
                            g_ScriptVars[3] = 13;
                            break;
                        case CHAR_ID_PECO:
                            g_ScriptVars[3] = 14;
                            break;
                        default:
                            return;
                    }
                    break;
                case CHAR_ID_PECO:
                    switch (g_PartyBattleOrder[1]) {
                        case CHAR_ID_RYU_YOUNG:
                            g_ScriptVars[3]      = 15;
                            g_ScenarioState.step = 15;
                            return;
                        case CHAR_ID_NINA_YOUNG:
                            g_ScriptVars[3] = 16;
                            break;
                        default:
                            return;
                    }
                    break;
                default:
                    return;
            }
            g_ScenarioState.step = 15;
            break;
        case 15:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA05_050, 16);
            break;

        case 16:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 10;
                g_ScenarioState.step = 17;
            }
            break;

        case 17:
            if (g_ScriptVars[0] != 11) {
                break;
            }
            g_ScenarioState.step = 18;
            SYS_SetFlag(g_SceneFlags, 0x1D);
            SND_SeqStop(0, 0);
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            func_801FC808();
            if (g_ScriptVars[1] == 1) {
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                switch (g_ScriptVars[3]) {
                    case 1:
                    case 2:
                        Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(7), AREA_ENTRY_MAP_LOADING | FACING_LEFT);
                        break;
                    case 3:
                    case 4:
                        Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(7), 0x88);
                        break;
                    case 5:
                    case 6:
                        Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(7), 0x89);
                        break;
                    default:
                        return;
                }
            } else {
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                switch (g_ScriptVars[3]) {
                    case 11:
                    case 12:
                        Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(7), AREA_ENTRY_MAP_LOADING | FACING_DOWN_RIGHT);
                        break;
                    case 13:
                    case 14:
                        Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(7), AREA_ENTRY_MAP_LOADING | FACING_DOWN);
                        break;
                    case 15:
                    case 16:
                        Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(7), AREA_ENTRY_MAP_LOADING | FACING_DOWN_LEFT);
                        break;
                    default:
                        return;
                }
            }
            break;

        case 18:
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 8));
            switch (g_ScriptVars[3]) {
                case 1:
                case 2:
                case 11:
                case 12:
                    mode = &g_GameStateIndex;
                    if (*mode != GAME_REQUEST_MESSAGE) {
                        UI_MessageStartArea(MSG_SCENA05_051);
                        *mode                = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step = 19;
                    }
                    break;
                case 3:
                case 4:
                case 13:
                case 14:
                    mode = &g_GameStateIndex;
                    if (*mode != GAME_REQUEST_MESSAGE) {
                        UI_MessageStartArea(MSG_SCENA05_052);
                        *mode                = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step = 19;
                    }
                    break;
                case 5:
                case 6:
                    mode = &g_GameStateIndex;
                    if (*mode != GAME_REQUEST_MESSAGE) {
                        UI_MessageStartArea(MSG_SCENA05_053);
                        *mode                = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step = 19;
                    }
                    break;
                case 15:
                case 16:
                    mode = &g_GameStateIndex;
                    if (*mode != GAME_REQUEST_MESSAGE) {
                        UI_MessageStartArea(MSG_SCENA05_054);
                        *mode                = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step = 19;
                    }
                    break;
                default:
                    return;
            }
            break;

        case 19:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 1;
                g_ScenarioState.step = 20;
            }
            break;

        case 20:
            if (g_ScriptVars[0] == 10) {
                g_ScenarioState.step = 21;
                Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(92), TO_COORD(6), 0x8E);
            }
            break;

        case 21:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            g_ScenarioState.step = 22;
            switch (g_ScriptVars[3]) {
                case 1:
                case 2:
                    func_801C1E3C(1);
                    func_801C1E3C(2);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8A);
                    break;
                case 3:
                case 4:
                    func_801C1E3C(2);
                    func_801C1E3C(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8B);
                    break;
                case 5:
                case 6:
                    func_801C1E3C(1);
                    func_801C1E3C(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8C);
                    break;
                case 11:
                case 12:
                    func_801C1E3C(1);
                    func_801C1E3C(3);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8A);
                    break;
                case 13:
                case 14:
                    func_801C1E3C(3);
                    func_801C1E3C(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8B);
                    break;
                case 15:
                case 16:
                    func_801C1E3C(1);
                    func_801C1E3C(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8D);
                    break;
                default:
                    return;
            }
            break;

        case 22:
            if (g_ScriptVars[0] != 0x16) {
                break;
            }
            switch (g_PartyFieldOrder[0]) {
                case CHAR_ID_RYU_YOUNG:
                    message = 62;
                    break;
                case CHAR_ID_NINA_YOUNG:
                    message = 63;
                    break;
                case CHAR_ID_GARR:
                case CHAR_ID_TEEPO:
                case CHAR_ID_REI:
                    return;
                case CHAR_ID_MOMO:
                    message = 64;
                    break;
                case CHAR_ID_PECO:
                    message = 65;
                    break;
                default:
                    return;
            }
            SCENARIO_MESSAGE_WAIT(message, 23);
            break;

        case 23:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 0x17;
                g_ScenarioState.step = 24;
            }
            break;

        case 24:
            if (g_ScriptVars[0] != 0x1B) {
                break;
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 9));
            func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x12);
            Game_BattleStartScripted(0x12);
            g_ScenarioState.step = 25;
            break;

        case 26:
            Scene_SetupParty(0x30);
            Area_ScrollStartRoute(2);
            g_ScenarioState.step = 90;
            break;

        case 27:
            Scene_SetupParty(0x30);
            g_ScriptVars[0]      = 11;
            g_ScenarioState.step = 30;
            SYS_SetFlag(g_SceneFlags, 0x1E);
            Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(90), TO_COORD(2) + COORD_HALF, 0x8E);
            break;

        case 28:
            UI_ModeSet(UI_MODE_SLOW_FADE_OUT);
            g_ScenarioState.step = 70;
            break;

        case 70:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 71;
            }
            break;

        case 71:
            g_ScenarioState.step = 72;
            SYS_SetFlag(g_SceneFlags, 0x23);
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            switch (g_ScriptVars[3]) {
                case 1:
                    Scene_RunScenario(1);
                    Scene_RunScenario(2);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x9A);
                    break;
                case 2:
                    Scene_RunScenario(1);
                    Scene_RunScenario(2);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x9B);
                    break;
                case 3:
                    Scene_RunScenario(2);
                    Scene_RunScenario(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x9C);
                    break;
                case 4:
                    Scene_RunScenario(2);
                    Scene_RunScenario(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x9D);
                    break;
                case 5:
                    Scene_RunScenario(1);
                    Scene_RunScenario(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x9E);
                    break;
                case 6:
                    Scene_RunScenario(1);
                    Scene_RunScenario(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x9F);
                    break;
                case 11:
                    Scene_RunScenario(1);
                    Scene_RunScenario(3);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x94);
                    break;
                case 12:
                    Scene_RunScenario(1);
                    Scene_RunScenario(3);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x95);
                    break;
                case 13:
                    Scene_RunScenario(3);
                    Scene_RunScenario(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x96);
                    break;
                case 14:
                    Scene_RunScenario(3);
                    Scene_RunScenario(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x97);
                    break;
                case 15:
                    Scene_RunScenario(1);
                    Scene_RunScenario(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x98);
                    break;
                case 16:
                    Scene_RunScenario(1);
                    Scene_RunScenario(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x99);
                    break;
                default:
                    return;
            }
            break;

        case 72:
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step = 50;
            break;

        case 30:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            g_ScenarioState.step = 31;
            switch (g_PartyFieldOrder[0]) {
                case CHAR_ID_RYU_YOUNG:
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8A);
                    break;
                case CHAR_ID_NINA_YOUNG:
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8B);
                    break;
                case CHAR_ID_GARR:
                case CHAR_ID_TEEPO:
                case CHAR_ID_REI:
                case CHAR_ID_MOMO:
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8C);
                    break;
                case CHAR_ID_PECO:
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8D);
                    break;
                default:
                    return;
            }
            break;

        case 31:
            if (g_ScriptVars[0] != 0x16) {
                break;
            }
            switch (g_PartyFieldOrder[0]) {
                case CHAR_ID_RYU_YOUNG:
                    message = 73;
                    break;
                case CHAR_ID_NINA_YOUNG:
                    message = 74;
                    break;
                case CHAR_ID_GARR:
                case CHAR_ID_TEEPO:
                case CHAR_ID_REI:
                case CHAR_ID_MOMO:
                    message = 75;
                    break;
                case CHAR_ID_PECO:
                    message = 76;
                    break;
                default:
                    return;
            }
            SCENARIO_MESSAGE_WAIT(message, 32);
            break;

        case 32:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 0x17;
                g_ScenarioState.step = 33;
            }
            break;

        case 33:
            if (g_ScriptVars[0] != 0x1B) {
                break;
            }
            func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x13);
            Game_BattleStartScripted(0x13);
            g_ScenarioState.step = 34;
            break;

        case 35:
            Scene_SetupParty(0x30);
            g_ScriptVars[0]      = 12;
            g_ScenarioState.step = 36;
            SYS_SetFlag(g_SceneFlags, 0x1F);
            Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(90), TO_COORD(8), 0x8E);
            break;

        case 36:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            g_ScenarioState.step = 37;
            switch (g_PartyFieldOrder[0]) {
                case CHAR_ID_RYU_YOUNG:
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8A);
                    break;
                case CHAR_ID_NINA_YOUNG:
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8B);
                    break;
                case CHAR_ID_GARR:
                case CHAR_ID_TEEPO:
                case CHAR_ID_REI:
                case CHAR_ID_MOMO:
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8C);
                    break;
                case CHAR_ID_PECO:
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8D);
                    break;
                default:
                    return;
            }
            break;

        case 37:
            if (g_ScriptVars[0] != 0x16) {
                break;
            }
            switch (g_PartyFieldOrder[0]) {
                case CHAR_ID_RYU_YOUNG:
                    message = 77;
                    break;
                case CHAR_ID_NINA_YOUNG:
                    message = 78;
                    break;
                case CHAR_ID_GARR:
                case CHAR_ID_TEEPO:
                case CHAR_ID_REI:
                case CHAR_ID_MOMO:
                    message = 79;
                    break;
                case CHAR_ID_PECO:
                    message = 80;
                    break;
                default:
                    return;
            }
            SCENARIO_MESSAGE_WAIT(message, 38);
            break;

        case 38:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 0x17;
                g_ScenarioState.step = 39;
            }
            break;

        case 39:
            if (g_ScriptVars[0] != 0x1B) {
                break;
            }
            func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x14);
            Game_BattleStartScripted(0x14);
            g_ScenarioState.step = 40;
            break;

        case 41:
            SYS_SetFlag(g_SceneFlags, 0x20);
            SYS_SetFlag(g_SceneFlags, 0x22);
            g_ScenarioState.step = 26;
            break;

        case 50:
            switch (g_ScriptVars[3]) {
                case 1:
                case 6:
                case 11:
                case 16:
                    mode = &g_GameStateIndex;
                    if (*mode != GAME_REQUEST_MESSAGE) {
                        UI_MessageStartArea(MSG_SCENA05_052);
                        *mode                = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step = 51;
                    }
                    break;
                case 2:
                case 4:
                    mode = &g_GameStateIndex;
                    if (*mode != GAME_REQUEST_MESSAGE) {
                        UI_MessageStartArea(MSG_SCENA05_053);
                        *mode                = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step = 51;
                    }
                    break;
                case 3:
                case 5:
                case 13:
                case 15:
                    mode = &g_GameStateIndex;
                    if (*mode != GAME_REQUEST_MESSAGE) {
                        UI_MessageStartArea(MSG_SCENA05_051);
                        *mode                = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step = 51;
                    }
                    break;
                case 12:
                case 14:
                    mode = &g_GameStateIndex;
                    if (*mode != GAME_REQUEST_MESSAGE) {
                        UI_MessageStartArea(MSG_SCENA05_054);
                        *mode                = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step = 51;
                    }
                    break;
                default:
                    return;
            }
            break;

        case 51:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 1;
                g_ScenarioState.step = 52;
            }
            break;

        case 52:
            if (g_ScriptVars[0] != 10) {
                break;
            }
            g_ScenarioState.step = 53;
            switch (g_ScriptVars[3]) {
                case 1:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(4);
                    func_801C1E3C(2);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8B);
                    break;
                case 2:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(4);
                    func_801C1E3C(1);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8C);
                    break;
                case 3:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(1);
                    func_801C1E3C(2);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8A);
                    break;
                case 4:
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    g_AreaDrawFlags = 0;
                    func_801C1E3C(1);
                    func_801C1E3C(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8C);
                    break;
                case 5:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(2);
                    func_801C1E3C(1);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8A);
                    break;
                case 6:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(2);
                    func_801C1E3C(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8B);
                    break;
                case 11:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(4);
                    func_801C1E3C(3);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8B);
                    break;
                case 12:
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    g_AreaDrawFlags = 0;
                    func_801C1E3C(4);
                    func_801C1E3C(1);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8D);
                    break;
                case 13:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(1);
                    func_801C1E3C(3);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8A);
                    break;
                case 14:
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    g_AreaDrawFlags = 0;
                    func_801C1E3C(1);
                    func_801C1E3C(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8D);
                    break;
                case 15:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(3);
                    func_801C1E3C(1);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8A);
                    break;
                case 16:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(3);
                    func_801C1E3C(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8B);
                    break;
                default:
                    return;
            }
            break;

        case 53:
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step = 54;
            g_ScriptVars[0]      = 0x14;
            break;

        case 54:
            if (g_ScriptVars[0] != 0x16) {
                break;
            }
            if (SYS_TestFlag(g_SceneFlags, 0x1E) != 0) {
                if (SYS_TestFlag(g_SceneFlags, 0x1F) != 0) {
                    switch (g_PartyFieldOrder[0]) {
                        case CHAR_ID_RYU_YOUNG:
                            MESSAGE_START_WAIT(MSG_SCENA05_077);
                            break;
                        case CHAR_ID_NINA_YOUNG:
                            MESSAGE_START_WAIT(MSG_SCENA05_078);
                            break;
                        case CHAR_ID_GARR:
                        case CHAR_ID_TEEPO:
                        case CHAR_ID_REI:
                        case CHAR_ID_MOMO:
                            MESSAGE_START_WAIT(MSG_SCENA05_079);
                            break;
                        case CHAR_ID_PECO:
                            MESSAGE_START_WAIT(MSG_SCENA05_080);
                            break;
                    }
                } else {
                    switch (g_PartyFieldOrder[0]) {
                        case CHAR_ID_RYU_YOUNG:
                            MESSAGE_START_WAIT(MSG_SCENA05_073);
                            break;
                        case CHAR_ID_NINA_YOUNG:
                            MESSAGE_START_WAIT(MSG_SCENA05_074);
                            break;
                        case CHAR_ID_GARR:
                        case CHAR_ID_TEEPO:
                        case CHAR_ID_REI:
                            break;
                        case CHAR_ID_MOMO:
                            MESSAGE_START_WAIT(MSG_SCENA05_075);
                            break;
                        case CHAR_ID_PECO:
                            MESSAGE_START_WAIT(MSG_SCENA05_076);
                            break;
                    }
                }
            } else {
                switch (g_PartyFieldOrder[0]) {
                    case CHAR_ID_RYU_YOUNG:
                        MESSAGE_START_WAIT(MSG_SCENA05_062);
                        break;
                    case CHAR_ID_NINA_YOUNG:
                        MESSAGE_START_WAIT(MSG_SCENA05_063);
                        break;
                    case CHAR_ID_GARR:
                    case CHAR_ID_TEEPO:
                    case CHAR_ID_REI:
                        break;
                    case CHAR_ID_MOMO:
                        MESSAGE_START_WAIT(MSG_SCENA05_064);
                        break;
                    case CHAR_ID_PECO:
                        MESSAGE_START_WAIT(MSG_SCENA05_065);
                        break;
                }
            }
            g_ScenarioState.step = 55;
            break;
        case 55:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 0x17;
                g_ScenarioState.step = 56;
            }
            break;

        case 56:
            if (g_ScriptVars[0] != 0x1B) {
                break;
            }
            if (SYS_TestFlag(g_SceneFlags, 0x1E) != 0) {
                if (SYS_TestFlag(g_SceneFlags, 0x1F) != 0) {
                    func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x14);
                    Game_BattleStartScripted(0x14);
                } else {
                    func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x13);
                    Game_BattleStartScripted(0x13);
                }
            } else {
                func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x12);
                Game_BattleStartScripted(0x12);
            }
            g_ScenarioState.step = 57;
            break;
        case 58:
            UI_ModeSet(UI_MODE_SLOW_FADE_OUT);
            g_ScenarioState.step = 100;
            break;

        case 100:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 101;
            }
            break;

        case 101:
            g_ScenarioState.step = 102;
            SYS_SetFlag(g_SceneFlags, 0x24);
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            switch (g_ScriptVars[3]) {
                case 1:
                    Scene_RunScenario(4);
                    Scene_RunScenario(2);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0xA6);
                    break;
                case 2:
                    Scene_RunScenario(4);
                    Scene_RunScenario(1);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0xA7);
                    break;
                case 3:
                    Scene_RunScenario(1);
                    Scene_RunScenario(2);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0xA8);
                    break;
                case 4:
                    Scene_RunScenario(1);
                    Scene_RunScenario(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0xA9);
                    break;
                case 5:
                    Scene_RunScenario(2);
                    Scene_RunScenario(1);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0xAA);
                    break;
                case 6:
                    Scene_RunScenario(2);
                    Scene_RunScenario(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0xAB);
                    break;
                case 11:
                    Scene_RunScenario(4);
                    Scene_RunScenario(3);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0xA0);
                    break;
                case 12:
                    Scene_RunScenario(4);
                    Scene_RunScenario(1);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0xA1);
                    break;
                case 13:
                    Scene_RunScenario(1);
                    Scene_RunScenario(3);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0xA2);
                    break;
                case 14:
                    Scene_RunScenario(1);
                    Scene_RunScenario(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0xA3);
                    break;
                case 15:
                    Scene_RunScenario(1);
                    Scene_RunScenario(3);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0xA4);
                    break;
                case 16:
                    Scene_RunScenario(3);
                    Scene_RunScenario(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0xA5);
                    break;
                default:
                    return;
            }
            break;

        case 102:
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step = 60;
            break;

        case 60:
            switch (g_ScriptVars[3]) {
                case 1:
                case 3:
                    mode = &g_GameStateIndex;
                    if (*mode != GAME_REQUEST_MESSAGE) {
                        UI_MessageStartArea(MSG_SCENA05_053);
                        *mode                = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step = 61;
                    }
                    break;
                case 2:
                case 5:
                    mode = &g_GameStateIndex;
                    if (*mode != GAME_REQUEST_MESSAGE) {
                        UI_MessageStartArea(MSG_SCENA05_052);
                        *mode                = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step = 61;
                    }
                    break;
                case 11:
                case 13:
                    mode = &g_GameStateIndex;
                    if (*mode != GAME_REQUEST_MESSAGE) {
                        UI_MessageStartArea(MSG_SCENA05_054);
                        *mode                = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step = 61;
                    }
                    break;
                case 12:
                case 15:
                    mode = &g_GameStateIndex;
                    if (*mode != GAME_REQUEST_MESSAGE) {
                        UI_MessageStartArea(MSG_SCENA05_052);
                        *mode                = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step = 61;
                    }
                    break;
                case 4:
                case 6:
                case 14:
                case 16:
                    mode = &g_GameStateIndex;
                    if (*mode != GAME_REQUEST_MESSAGE) {
                        UI_MessageStartArea(MSG_SCENA05_051);
                        *mode                = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step = 61;
                    }
                    break;
                default:
                    return;
            }
            break;

        case 61:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 1;
                g_ScenarioState.step = 62;
            }
            break;

        case 62:
            if (g_ScriptVars[0] != 10) {
                break;
            }
            g_ScenarioState.step = 63;
            switch (g_ScriptVars[3]) {
                case 1:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(4);
                    func_801C1E3C(1);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8C);
                    break;
                case 2:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(4);
                    func_801C1E3C(2);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8B);
                    break;
                case 3:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(1);
                    func_801C1E3C(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8C);
                    break;
                case 4:
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    g_AreaDrawFlags = 0;
                    func_801C1E3C(1);
                    func_801C1E3C(2);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8A);
                    break;
                case 5:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(2);
                    func_801C1E3C(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8B);
                    break;
                case 6:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(2);
                    func_801C1E3C(1);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8A);
                    break;
                case 11:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(4);
                    func_801C1E3C(1);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8D);
                    break;
                case 12:
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    g_AreaDrawFlags = 0;
                    func_801C1E3C(4);
                    func_801C1E3C(3);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8B);
                    break;
                case 13:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(1);
                    func_801C1E3C(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8D);
                    break;
                case 14:
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    g_AreaDrawFlags = 0;
                    func_801C1E3C(1);
                    func_801C1E3C(3);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8A);
                    break;
                case 15:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(3);
                    func_801C1E3C(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8B);
                    break;
                case 16:
                    g_AreaDrawFlags = 0;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C1E3C(3);
                    func_801C1E3C(1);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(195), TO_COORD(14), 0x8A);
                    break;
                default:
                    return;
            }
            break;

        case 63:
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step = 64;
            g_ScriptVars[0]      = 0x14;
            break;

        case 64:
            if (g_ScriptVars[0] != 0x16) {
                break;
            }
            if (SYS_TestFlag(g_SceneFlags, 0x1E) != 0) {
                if (SYS_TestFlag(g_SceneFlags, 0x1F) != 0) {
                    switch (g_PartyFieldOrder[0]) {
                        case CHAR_ID_RYU_YOUNG:
                            MESSAGE_START_WAIT(MSG_SCENA05_077);
                            break;
                        case CHAR_ID_NINA_YOUNG:
                            MESSAGE_START_WAIT(MSG_SCENA05_078);
                            break;
                        case CHAR_ID_GARR:
                        case CHAR_ID_TEEPO:
                        case CHAR_ID_REI:
                        case CHAR_ID_MOMO:
                            MESSAGE_START_WAIT(MSG_SCENA05_079);
                            break;
                        case CHAR_ID_PECO:
                            MESSAGE_START_WAIT(MSG_SCENA05_080);
                            break;
                    }
                } else {
                    switch (g_PartyFieldOrder[0]) {
                        case CHAR_ID_RYU_YOUNG:
                            MESSAGE_START_WAIT(MSG_SCENA05_073);
                            break;
                        case CHAR_ID_NINA_YOUNG:
                            MESSAGE_START_WAIT(MSG_SCENA05_074);
                            break;
                        case CHAR_ID_GARR:
                        case CHAR_ID_TEEPO:
                        case CHAR_ID_REI:
                            break;
                        case CHAR_ID_MOMO:
                            MESSAGE_START_WAIT(MSG_SCENA05_075);
                            break;
                        case CHAR_ID_PECO:
                            MESSAGE_START_WAIT(MSG_SCENA05_076);
                            break;
                    }
                }
            } else {
                switch (g_PartyFieldOrder[0]) {
                    case CHAR_ID_RYU_YOUNG:
                        MESSAGE_START_WAIT(MSG_SCENA05_062);
                        break;
                    case CHAR_ID_NINA_YOUNG:
                        MESSAGE_START_WAIT(MSG_SCENA05_063);
                        break;
                    case CHAR_ID_GARR:
                    case CHAR_ID_TEEPO:
                    case CHAR_ID_REI:
                        break;
                    case CHAR_ID_MOMO:
                        MESSAGE_START_WAIT(MSG_SCENA05_064);
                        break;
                    case CHAR_ID_PECO:
                        MESSAGE_START_WAIT(MSG_SCENA05_065);
                        break;
                }
            }
            g_ScenarioState.step = 65;
            break;
        case 65:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 0x17;
                g_ScenarioState.step = 66;
            }
            break;

        case 66:
            if (g_ScriptVars[0] != 0x1B) {
                break;
            }
            if (SYS_TestFlag(g_SceneFlags, 0x1E) != 0) {
                if (SYS_TestFlag(g_SceneFlags, 0x1F) != 0) {
                    func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x14);
                    Game_BattleStartScripted(0x14);
                } else {
                    func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x13);
                    Game_BattleStartScripted(0x13);
                }
            } else {
                func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x12);
                Game_BattleStartScripted(0x12);
            }
            g_ScenarioState.step = 67;
            break;
        case 68:
            SYS_SetFlag(g_SceneFlags, 0x25);
            break;

        case 90:
            if (g_ScriptVars[0] == 0x1C) {
                g_ScriptVars[0]      = 0;
                g_ScenarioState.step = 91;
            }
            break;

        case 91:
            g_ScenarioState.step = 92;
            SYS_SetFlag(g_SceneFlags, 0x21);
            UI_ModeSet(UI_MODE_LONG_FADE_OUT);
            break;

        case 92:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 93;
            }
            break;

        case 93:
            lineup               = g_ScriptVars[3];
            g_ScenarioState.step = 94;
            g_PartySize          = 0;
            if (lineup == 0) {
                return;
            }
            if (lineup < 7) {
                Scene_RunScenario(1);
                Scene_RunScenario(2);
                Scene_RunScenario(4);
                Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x90);
            } else if (lineup < 17) {
                if (lineup >= 11) {
                    Scene_RunScenario(1);
                    Scene_RunScenario(3);
                    Scene_RunScenario(4);
                    Game_RequestAreaChange(AREA_ID_CONTEST_FIRST_FIGHT, TO_COORD(72), TO_COORD(8), 0x8F);
                }
            }
            break;

        case 94:
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step = 95;
            break;

        case 95:
            if (g_ScriptVars[0] == 9) {
                Game_ClearScriptActive();
                Scene_ClearScriptState(&g_ScenarioState.step);
                SYS_SetFlag(g_SceneFlags, 0x1E);
                SYS_SetFlag(g_SceneFlags, 0x1F);
                SYS_SetFlag(g_SceneFlags, 0x20);
                SYS_SetFlag(g_SceneFlags, 0x22);
                SYS_SetFlag(g_SceneFlags, 0x3B);
                g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
            }
            break;
    }
}

/* The 4-byte zero the retail row places after the jump tables. */
const u8 D_801F6F10[4] = {0, 0, 0, 0};
