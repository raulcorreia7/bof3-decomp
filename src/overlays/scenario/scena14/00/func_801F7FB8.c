#include "scena14_00.h"
#include "menu/save_data.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7FB8(void) {
    u8* char_slots;
    u8* flags;
    u8* exit_flags;
    u8  bits;
    u8  slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            g_Game.members[2].unk_48 = 1;
            g_Game.members[1].unk_48 = 1;
            g_Game.members[0].unk_48 = 1;
            g_ScenarioState.timer_06 = 0xF0;
            g_ScenarioState.step     = 1;
            break;
        case 1:
            if (--g_ScenarioState.timer_06 != 0) {
                g_AreaCameraOffsetZ = (0xF0 - g_ScenarioState.timer_06) * 0x76C / 0xF0;
            } else {
                g_AreaCameraOffsetZ = 0x76C;
                func_801BFE34(TO_COORD_HALF(36), TO_COORD_HALF(22), 0x25);
                g_Game.members[2].unk_48 = 1;
                g_Game.members[1].unk_48 = 1;
                g_Game.members[0].unk_48 = 1;
                g_ScenarioState.step     = 2;
            }
            g_AreaCameraRefreshCount = 2;
            break;
        case 2:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            g_AreaSceneMode = 1;
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step     = 3;
            break;
        case 3:
            if (g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.step = 4;
                g_ScriptVars[0]++;
            } else {
                g_ScenarioState.timer_06--;
                func_801F8800(4);
            }
            break;
        case 4:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step     = 5;
            break;
        case 5:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                func_801F8800(4);
            } else {
                g_AreaSceneMode      = 2;
                g_ScenarioState.step = 6;
                g_ScriptVars[0]++;
            }
            break;
        case 6:
            if (g_ScriptVars[0] != 8) {
                break;
            }
            g_AreaSceneMode = 3;
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
            g_ScenarioState.timer_06 = 0xD2;
            g_ScenarioState.step     = 7;
            break;
        case 7:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                func_801F8800(4);
                if (g_ScenarioState.timer_06 != 0xB4 && g_ScenarioState.timer_06 < 0xB4) {
                    g_AreaCameraOffsetZ = g_ScenarioState.timer_06 * 0x76C / 0xB4;
                }
            } else {
                g_AreaCameraOffsetZ  = 0;
                g_ScenarioState.step = 8;
                g_ScriptVars[0]++;
            }
            g_AreaCameraRefreshCount = 2;
            break;
        case 8:
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
            func_801BFE34(TO_COORD_HALF(24), TO_COORD_HALF(22), 0x31);
            Game_BattleStartScripted(0x31);
            g_ScenarioState.step = 9;
            break;
        case 10:
            Game_RequestAreaChange(AREA_ID_DESERT_CAMP_FIRST, TO_COORD_HALF(30), TO_COORD_HALF(34), FACING_UP);
            SYS_SetFlag(g_SceneFlags, 4);
            SYS_SetFlag(g_SceneFlags, 5);
            g_ScenarioState.step = 11;
            break;
        case 11:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScenarioState.step = 12;
            break;
        case 12:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            UI_ModeSet(0);
            g_ScenarioState.step = 13;
            break;
        case 13:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA14_112, 14);
            break;
        case 14:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScenarioState.step = 15;
            break;
        case 15:
            Game_RequestAreaChange(AREA_ID_DESERT_CAMP_FIRST, TO_COORD(73), TO_COORD(13), AREA_ENTRY_MAP_LOADING | FACING_UP);
            g_GameEntryMode      = 0xFF;
            g_GameRequestType    = 0xFF;
            g_ScenarioState.step = 16;
            break;
        case 16:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            UI_ModeSet(1);
            g_ScenarioState.step = 17;
            break;
        case 17:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            /* FAKE: retail reads the const g_CharSlot row through a pointer. */
            char_slots                        = (u8*)&g_CharSlot[CHAR_ID_NINA_ADULT];
            g_Characters[*char_slots].fatigue = 9;
            g_Characters[*char_slots].hp      = 1;
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 6);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 20:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA14_125, 21);
            break;
        case 21:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_ClearScriptActive();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 25:
            if ((u8)g_Game.members[0].u.field.mode.value != 0) {
                break;
            }
            Game_ClearScriptActive();
            Scene_SetupParty(3);
            SYS_SetFlag(g_SceneFlags, 8);
            Item_Add(0, 0x5A, 1, 0);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 29:
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 9);
            Scene_SetupParty(4);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 30:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            slot       = Actor_FindFreeSpawned();
            D_801FC4C0 = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[D_801FC4C0].type   = 0x91;
            }
            g_ScenarioState.step = 31;
            break;
        case 32:
            Game_RequestAreaChange(AREA_ID_DESERT_OF_DEATH_MAP, TO_COORD(0x1800), TO_COORD(0xC00), FACING_UP_RIGHT);
            flags                          = &g_ScenarioState.flags_01;
            g_SaveData.return_point.facing = 2;
            g_SaveData.desert.clock        = 0;
            *flags |= 1;
            g_ScenarioState.step = 33;
            break;
        case 33:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScenarioState.step = 34;
            break;
        case 34:
            if (TIMER_EXPIRED(g_ScenarioState.timer_06)) {
                SCENARIO_MESSAGE_WAIT(MSG_SCENA14_004, 35);
            }
            g_Game.members[0].unk_09++;
            break;
        case 35:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScenarioState.step = 36;
            }
            g_Game.members[0].unk_09++;
            break;
        case 36:
            Game_RequestAreaChange(AREA_ID_OASIS, TO_COORD_HALF(28), TO_COORD_HALF(20), FACING_DOWN);
            exit_flags               = &g_ScenarioState.flags_01;
            g_GameEntryMode          = 0;
            bits                     = *exit_flags;
            g_ScenarioState.state_04 = 3;
            g_ScenarioState.step     = 0;
            *exit_flags              = bits & ~1;
            break;
    }
}
