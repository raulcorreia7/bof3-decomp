#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9DF4(void) {
    PartyMember member;
    u8          i;
    u8          j;

    switch (g_SceneState.step_05) {
        case 0:
            func_801C16B8();
            func_801C601C(1);
            for (i = 0; i < PARTY_SLOT_COUNT - 1; i++) {
                for (j = i + 1; j < PARTY_SLOT_COUNT; j++) {
                    if (g_Game.members[i].chr.character_id > g_Game.members[j].chr.character_id) {
                        member            = g_Game.members[i];
                        g_Game.members[i] = g_Game.members[j];
                        g_Game.members[j] = member;
                    }
                }
            }
            for (i = 0; i < g_PartySize; i++) {
                D_801FE4EC[i] = g_PartyBattleOrder[i];
            }
            D_801FE4E4            = g_PartySize;
            g_PartyBattleOrder[1] = FORMATION_SLOT_EMPTY;
            g_PartyBattleOrder[2] = FORMATION_SLOT_EMPTY;
            g_PartyBattleOrder[0] = 0;
            g_Game.party_size     = 1;
            g_SceneState.step_05  = 1;
            break;
        case 1:
            func_801BFE34(TO_COORD(25), TO_COORD(65), 25);
            g_SceneState.step_05 = 2;
            break;
        case 2:
            Battle_StartScripted(25);
            g_SceneState.step_05 = 3;
            break;
        case 4:
            func_801C16B8();
            g_ScriptVars[2]      = 2;
            g_SceneState.step_05 = 5;
            Game_RequestAreaChange(AREA_ID_BEYD_TRAINING, TO_COORD(25), TO_COORD(60), AREA_ENTRY_MAP_LOADING | FACING_DOWN);
            break;
        case 5:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            Game_ClearScriptActive();
            Scene_ClearScriptState(&g_SceneState.step_05);
            break;
        case 10:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            func_801BE1B0(6);
            func_801C601C(2);
            g_SceneState.step_05 = 11;
            break;
        case 11:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            func_801BFE34(TO_COORD(25), TO_COORD(65), 26);
            g_SceneState.step_05 = 12;
            break;
        case 12:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            Battle_StartScripted(26);
            g_SceneState.step_05 = 13;
            break;
        case 13:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            g_ScriptVars[2]      = 2;
            g_SceneState.step_05 = 14;
            Game_RequestAreaChange(AREA_ID_BEYD_TRAINING, TO_COORD(25), TO_COORD(60), AREA_ENTRY_MAP_LOADING | FACING_LEFT);
            break;
        case 14:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            g_GameStateIndex     = GAME_REQUEST_ABILITY_MENU;
            D_8018E244           = 1;
            g_SceneState.step_05 = 15;
            break;
        case 15:
            if (g_GameStateIndex != GAME_REQUEST_IDLE) {
                break;
            }
            g_SceneState.step_05 = 16;
            break;
        case 16:
            Message_StartAreaMessage(0x23);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 17;
            break;
        case 17:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_SceneState.step_05 = 18;
            func_801C16B8();
            g_SceneState.flags_01 ^= 0x01;
            SYS_SetFlag(g_SceneFlags, 28);
            Game_RequestAreaChange(AREA_ID_RHAPALA_WORLD_MAP, TO_COORD(49), TO_COORD(45), FACING_DOWN_RIGHT);
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
            /* FAKE: retail reads the request byte through a register. */
            u8* state;

            state = &g_GameStateIndex;
            if (*state == GAME_REQUEST_MESSAGE) {
                break;
            }
            *state               = GAME_REQUEST_SHOP;
            g_SceneState.step_05 = 21;
            break;
        }
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_IDLE) {
                break;
            }
            g_SceneState.step_05 = 22;
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
            /* FAKE: retail reads the request byte through a register. */
            u8* state;

            state = &g_GameStateIndex;
            if (*state == GAME_REQUEST_MESSAGE) {
                break;
            }
            *state               = GAME_REQUEST_ABILITY_MENU;
            D_8018E244           = 0;
            g_SceneState.step_05 = 31;
            break;
        }
        case 31:
            if (g_GameStateIndex != GAME_REQUEST_IDLE) {
                break;
            }
            g_SceneState.step_05 = 32;
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
            g_SceneState.step_05 = 41;
            func_801C16B8();
            g_SceneState.flags_01 ^= 0x01;
            Game_RequestAreaChange(AREA_ID_RHAPALA_WORLD_MAP, TO_COORD(49), TO_COORD(45), FACING_DOWN_RIGHT);
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
