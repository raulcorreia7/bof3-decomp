#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9DF4(void) {
    PartyMember temp;
    u8          i;
    u8          j;

    switch (g_SceneState.step_05) {
        case 0:
            func_801C16B8();
            func_801C601C(1);
            for (i = 0; i < 2; i++) {
                for (j = i + 1; j < 3; j++) {
                    if (g_Game.members[i].chr.character_id > g_Game.members[j].chr.character_id) {
                        temp              = g_Game.members[i];
                        g_Game.members[i] = g_Game.members[j];
                        g_Game.members[j] = temp;
                    }
                }
            }
            for (i = 0; i < g_PartySize; i++) {
                D_801FE4EC[i] = g_PartyBattleOrder[i];
            }
            D_801FE4E4            = g_PartySize;
            g_PartyBattleOrder[1] = 0xFF;
            g_PartyBattleOrder[2] = 0xFF;
            g_PartyBattleOrder[0] = 0;
            g_Game.party_size     = 1;
            g_SceneState.step_05  = 1;
            break;
        case 1:
            func_801BFE34(0x190000, 0x410000, 0x19);
            g_SceneState.step_05 = 2;
            break;
        case 2:
            Battle_StartScripted(0x19);
            g_SceneState.step_05 = 3;
            break;
        case 4:
            func_801C16B8();
            g_ScriptVars[2]      = 2;
            g_SceneState.step_05 = 5;
            func_8019FA28(0x5C, 0x190000, 0x3C0000, 0x85);
            break;
        case 5:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            Game_ClearScriptActive();
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 10:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            func_801BE1B0(6);
            func_801C601C(2);
            g_SceneState.step_05 = 0xB;
            break;
        case 11:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            func_801BFE34(0x190000, 0x410000, 0x1A);
            g_SceneState.step_05 = 0xC;
            break;
        case 12:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            Battle_StartScripted(0x1A);
            g_SceneState.step_05 = 0xD;
            break;
        case 13:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            g_ScriptVars[2]      = 2;
            g_SceneState.step_05 = 0xE;
            func_8019FA28(0x5C, 0x190000, 0x3C0000, 0x87);
            break;
        case 14:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            g_GameStateIndex     = GAME_REQUEST_ABILITY_MENU;
            D_8018E244           = 1;
            g_SceneState.step_05 = 0xF;
            break;
        case 15:
            if (g_GameStateIndex != GAME_REQUEST_IDLE) {
                break;
            }
            g_SceneState.step_05 = 0x10;
            break;
        case 16:
            Message_StartAreaMessage(0x23);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 0x11;
            break;
        case 17:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_SceneState.step_05 = 0x12;
            func_801C16B8();
            g_SceneState.flags_01 ^= 1;
            SYS_SetFlag(g_SceneFlags, 0x1C);
            func_8019FA28(0x57, 0x310000, 0x2D0000, 4);
            break;
        case 18:
            Game_ClearScriptActive();
            g_ScriptVars[0]       = 0;
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 20: {
            u8* state;

            state = &g_GameStateIndex;
            if (*state == GAME_REQUEST_MESSAGE) {
                break;
            }
            *state               = GAME_REQUEST_SHOP;
            g_SceneState.step_05 = 0x15;
            break;
        }
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_IDLE) {
                break;
            }
            g_SceneState.step_05 = 0x16;
            break;
        case 22:
            Game_ClearScriptActive();
            g_ScriptVars[0]       = 0;
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 30: {
            u8* state;

            state = &g_GameStateIndex;
            if (*state == GAME_REQUEST_MESSAGE) {
                break;
            }
            *state               = GAME_REQUEST_ABILITY_MENU;
            D_8018E244           = 0;
            g_SceneState.step_05 = 0x1F;
            break;
        }
        case 31:
            if (g_GameStateIndex != GAME_REQUEST_IDLE) {
                break;
            }
            g_SceneState.step_05 = 0x20;
            break;
        case 32:
            Game_ClearScriptActive();
            g_ScriptVars[0]       = 0;
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 40:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_SceneState.step_05 = 0x29;
            func_801C16B8();
            g_SceneState.flags_01 ^= 1;
            func_8019FA28(0x57, 0x310000, 0x2D0000, 4);
            break;
        case 41:
            Game_ClearScriptActive();
            g_ScriptVars[0]       = 0;
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
    }
}
