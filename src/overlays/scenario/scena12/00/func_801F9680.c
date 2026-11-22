#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The step sequence of one scena12 scenario state: messages, party setups, area changes and the
 * closing scroll. */
MATCH void func_801F9680(void) {
    u8* state;
    u8  slot;

    switch (g_ScenarioState.step) {
        case 0:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA12_002, 1);
            break;
        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            SCRIPT_VARS_CLEAR_ALL();
            Game_ClearScriptActive();
            SCENARIO_RETURN_TO_START();
            break;
        case 2:
            state = &g_GameStateIndex;
            if (*state != GAME_REQUEST_MESSAGE) {
                slot = Actor_FindFreeSpawned();
                if (slot != 0xFF) {
                    SpawnedActor* actor = &g_SpawnedActors[slot];
                    actor->header.flags = 1;
                    actor->type         = 0x77;
                    actor->header.mode  = 2;
                }
                UI_MessageStartArea(MSG_SCENA12_013);
                *state = GAME_REQUEST_MESSAGE;
            }
            g_ScenarioState.step = 3;
            break;
        case 3:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x14);
            g_ScriptVars[0] = 10;
            g_ScriptVars[1] = 0;
            g_ScriptVars[2] = 10;
            g_ScriptVars[3] = 0;
            Game_ClearScriptActive();
            SCENARIO_RETURN_TO_START();
            break;
        case 5:
            g_GameFlags |= 0x20;
            Scene_SetupParty(3);
            g_ScenarioState.step = 6;
            break;
        case 6:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            g_ScenarioState.step = 7;
            g_ScriptVars[2]      = 2;
            Game_RequestAreaChange(AREA_ID_BLACK_SHIP_BOOST_COUNTER, TO_COORD(4), TO_COORD(1), 0x84);
            break;
        case 7:
            Area_ScrollStartRoute(0);
            g_ScenarioState.step = 8;
            break;
        case 8:
            if (g_ScriptVars[0] != 10) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_ScriptVars[2]      = 1;
            g_ScenarioState.step = 9;
            SYS_SetFlag(g_SceneFlags, 0x24);
            Game_RequestAreaChange(AREA_ID_BLACK_SHIP_BOOST_COUNTER, TO_COORD(12), TO_COORD(89), 0x85);
            break;
        case 9:
            if (g_ScriptVars[0] != 10) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x25);
            g_ScriptVars[1] = 0;
            g_ScriptVars[2] = 10;
            g_ScriptVars[3] = 0;
            Game_ClearScriptActive();
            SCENARIO_RETURN_TO_START();
            slot = Actor_FindFreeSpawned();
            if (slot != 0xFF) {
                SpawnedActor* actor = &g_SpawnedActors[slot];
                actor->header.flags = 1;
                actor->type         = 0x77;
                actor->header.mode  = 0;
            }
            break;
        case 20:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[0] = 1;
            if (D_801FD288.bytes[0] >= 0x62 && D_801FD288.bytes[0] < 0x67) {
                Scene_SetupParty(9);
                SYS_SetFlag(g_SceneFlags, 0x16);
                g_ScenarioState.step = 40;
            } else {
                Scene_SetupParty(6);
                g_ScenarioState.step = 21;
            }
            break;
        case 21:
            if (g_ScriptVars[0] != 0x23) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_ScriptVars[1]      = 1;
            g_ScenarioState.step = 22;
            Game_RequestAreaChange(AREA_ID_BLACK_SHIP_BOOST_COUNTER, TO_COORD(12), TO_COORD(89), 0x87);
            break;
        case 22:
            if (g_ScriptVars[0] != 10) {
                break;
            }
            g_ScriptVars[1] = 0;
            g_ScriptVars[2] = 10;
            g_ScriptVars[3] = 0;
            Game_ClearScriptActive();
            SCENARIO_RETURN_TO_START();
            SYS_SetFlag(g_SceneEventFlags, 0x29);
            SYS_ClearFlag(g_SceneFlags, 0x14);
            slot = Actor_FindFreeSpawned();
            if (slot != 0xFF) {
                SpawnedActor* actor = &g_SpawnedActors[slot];
                actor->header.flags = 1;
                actor->type         = 0x77;
                actor->header.mode  = 0;
            }
            break;
        case 25:
            g_ScenarioState.step = 26;
            switch (g_GameAreaId) {
                case AREA_ID_BOAT_AFTER_BLACK_SHIP:
                    Scene_SetupParty(4);
                    break;
                case AREA_ID_BLACK_SHIP_EARLY:
                    Scene_SetupParty(2);
                    break;
                case AREA_ID_BLACK_SHIP_BOOST_COUNTER:
                    Scene_SetupParty(8);
                    break;
            }
            break;
        case 26:
            if (g_ScriptVars[0] != 0x28) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_ScriptVars[1]      = 1;
            g_ScriptVars[2]      = 0;
            g_ScenarioState.step = 22;
            Game_RequestAreaChange(AREA_ID_BLACK_SHIP_BOOST_COUNTER, TO_COORD(12), TO_COORD(89), 0x87);
            break;
        case 27:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA12_019, 28);
            break;
        case 28:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_ClearScriptActive();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 40:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_ScriptVars[2]      = 3;
            g_ScenarioState.step = 41;
            SYS_SetFlag(g_SceneFlags, 0x26);
            switch (g_EmiLoadedCharacterIndex & 0x7F) {
                case 17:
                    g_ScriptVars[1] = 0;
                    Game_RequestAreaChange(AREA_ID_BOAT_AFTER_BLACK_SHIP, TO_COORD(6), TO_COORD(92), 0x85);
                    break;
                case 8:
                    g_ScriptVars[1] = 0;
                    Game_RequestAreaChange(AREA_ID_BOAT_AFTER_BLACK_SHIP, TO_COORD(6), TO_COORD(92), 0x86);
                    break;
                case 13:
                    g_ScriptVars[1] = 1;
                    Game_RequestAreaChange(AREA_ID_BOAT_AFTER_BLACK_SHIP, TO_COORD(6), TO_COORD(92), 0x86);
                    break;
                case 16:
                    g_ScriptVars[1] = 2;
                    Game_RequestAreaChange(AREA_ID_BOAT_AFTER_BLACK_SHIP, TO_COORD(6), TO_COORD(92), 0x86);
                    break;
            }
            break;
        case 41:
            if (g_ScriptVars[0] != 10) {
                break;
            }
            g_ScenarioState.step = 42;
            g_ScriptVars[0]      = 0;
            g_ScriptVars[2]      = 0;
            SYS_SetFlag(g_SceneFlags, 0x27);
            switch (g_EmiLoadedCharacterIndex & 0x7F) {
                case 8:
                    Game_RequestAreaChange(AREA_ID_BOAT_AFTER_BLACK_SHIP, TO_COORD_HALF(49), TO_COORD_HALF(38), 0x87);
                    break;
                case 17:
                    Game_RequestAreaChange(AREA_ID_BOAT_AFTER_BLACK_SHIP, TO_COORD_HALF(49), TO_COORD_HALF(38), 0x88);
                    break;
            }
            break;
        case 42:
            g_ScriptVars[1] = 0;
            Area_ScrollStartRoute(1);
            g_ScenarioState.step = 43;
            break;
        case 43:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            UI_ModeSet(4);
            g_ScenarioState.step = 44;
            break;
        case 44:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScenarioState.step = 45;
            g_ScriptVars[0]      = 0;
            g_AreaDrawFlags      = 0;
            g_GameFlags ^= 0xE;
            switch (g_EmiLoadedCharacterIndex & 0x7F) {
                case 7:
                    func_801C1E3C(1);
                    func_801C1E3C(0);
                    func_801C1DF0(6);
                    break;
                case 8:
                    func_801C1E3C(1);
                    func_801C1DF0(7);
                    break;
                case 9:
                    func_801C1E3C(1);
                    func_801C1DF0(6);
                    break;
                case 10:
                    func_801C1E3C(1);
                    func_801C1E3C(4);
                    func_801C1DF0(6);
                    break;
                case 13:
                    func_801C1E3C(0);
                    func_801C1DF0(7);
                    break;
                case 14:
                    func_801C1E3C(0);
                    func_801C1DF0(6);
                    break;
                case 15:
                    func_801C1E3C(0);
                    func_801C1E3C(4);
                    func_801C1DF0(6);
                    break;
                case 17:
                    func_801C1E3C(4);
                    func_801C1DF0(7);
                    break;
                case 18:
                    func_801C1E3C(4);
                    func_801C1DF0(6);
                    break;
            }
            break;
        case 45:
            SCRIPT_VARS_CLEAR_ALL();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 6;
            break;
    }
}
