#include "area170_13.h"

MATCH void func_801F4B58(void) {
    u8   slot;
    u16* countdown;

    switch (g_SceneEventState.step) {
        case 0:
            Scene_SetupParty(0);
            g_SceneEventState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[3] == 0x24) {
                SYS_SetFlag(g_SceneEventFlags, 0x55);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_HE_SHELLS, TO_COORD(6), TO_COORD(63), AREA_ENTRY_MAP_LOADING | FACING_UP_RIGHT);
                g_SceneEventState.step = 0x1E;
            }
            break;
        case 5:
            Scene_SetupParty(1);
            g_SceneEventState.step = 6;
            break;
        case 6:
            if (g_ScriptVars[3] == 0x24) {
                SYS_SetFlag(g_SceneEventFlags, 0x55);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_HE_SHELLS, TO_COORD(4), TO_COORD(117), AREA_ENTRY_MAP_LOADING | FACING_RIGHT);
                g_SceneEventState.step = 0x1E;
            }
            break;
        case 10:
            Scene_SetupParty(4);
            g_SceneEventState.step = 0xB;
            break;
        case 11:
            if (g_ScriptVars[3] == 0x44) {
                SYS_SetFlag(g_SceneEventFlags, 0x56);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_HE_SHELLS, TO_COORD(16), TO_COORD(93), AREA_ENTRY_MAP_LOADING | FACING_DOWN_LEFT);
                g_SceneEventState.step = 0x1E;
            }
            break;
        case 15:
            Scene_SetupParty(5);
            g_SceneEventState.step = 0x10;
            break;
        case 16:
            if (g_ScriptVars[3] == 0x44) {
                SYS_SetFlag(g_SceneEventFlags, 0x56);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_HE_SHELLS, TO_COORD(10), TO_COORD(147), AREA_ENTRY_MAP_LOADING | FACING_LEFT);
                g_SceneEventState.step = 0x1E;
            }
            break;
        case 20:
            Scene_SetupParty(8);
            g_SceneEventState.step = 0x15;
            break;
        case 21:
            if (g_ScriptVars[3] == 0x64) {
                SYS_SetFlag(g_SceneEventFlags, 0x57);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_HE_SHELLS, TO_COORD(23), TO_COORD(93), AREA_ENTRY_MAP_LOADING | 10);
                g_SceneEventState.step = 0x1E;
            }
            break;
        case 25:
            Scene_SetupParty(9);
            g_SceneEventState.step = 0x1A;
            break;
        case 26:
            if (g_ScriptVars[3] == 0x64) {
                SYS_SetFlag(g_SceneEventFlags, 0x57);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_HE_SHELLS, TO_COORD(17), TO_COORD(147), AREA_ENTRY_MAP_LOADING | 11);
                g_SceneEventState.step = 0x1E;
            }
            break;
        case 29:
            if (g_ScriptVars[3] == 0) {
                g_GameFlags |= 0x1010;
                SYS_ClearFlag(g_SceneEventFlags, 0x57);
                g_SceneEventState.step = 0x35;
            }
            break;
        case 30:
            if (g_ScriptVars[3] == 0) {
                SYS_ClearFlag(g_SceneEventFlags, 0x55);
                SYS_ClearFlag(g_SceneEventFlags, 0x56);
                SYS_ClearFlag(g_SceneEventFlags, 0x57);
                g_SceneEventState.mode = 0;
                g_SceneEventState.step = 0;
            }
            break;
        case 40:
            slot = Actor_FindFreeSpawned();
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[slot].type         = 0x7D;
                g_SpawnedActors[slot].screen_x     = 100;
                g_SpawnedActors[slot].screen_y     = 100;
                /* FAKE: barrier keeps the message byte load after the slot stores. */
                FAKE_BARRIER();
                g_SpawnedActors[slot].unk_06 = LOBU(g_UiMessageRequest) - 0xB;
            }
            D_801448EE             = 0;
            g_SceneEventState.step = 0x29;
            break;
        case 41:
            if (LOHU(D_801448EE) == 1) {
                g_AreaScrollTargetX         = TO_COORD(26);
                g_AreaScrollTargetY         = TO_COORD(145);
                g_AreaCameraSpeed           = g_RouteSpeedScale[2] << 3;
                g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
                if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = 0;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x70;
                }
                g_SceneEventState.step = 0x2A;
            }
            if (LOHU(D_801448EE) == 0xFF) {
                g_SceneEventState.step = 0x2D;
            }
            break;
        case 42:
            if (!g_AreaCameraMoving) {
                D_801448EE             = 0x1E;
                g_SceneEventState.step = 0x2B;
            }
            break;
        case 43:
            countdown = &LOHU(D_801448EE);
            if (--*countdown == 0) {
                *countdown             = 0x1E;
                g_SceneEventState.step = 0x2C;
            }
            break;
        case 44:
            countdown = &LOHU(D_801448EE);
            if (--*countdown == 0) {
                g_AreaCameraSpeed           = g_RouteSpeedScale[3] << 3;
                g_AreaScrollTargetX         = g_Game.members[0].pos.x.fixed;
                g_AreaScrollTargetY         = g_Game.members[0].pos.y.fixed;
                g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
                if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -682;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 512;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x38;
                }
                g_SceneEventState.step = 0x2D;
            }
            break;
        case 45:
            if (!g_AreaCameraMoving) {
                Game_ClearScriptActive();
                g_SceneEventState.mode = 0;
                g_SceneEventState.step = 0;
            }
            break;
        case 50:
            MESSAGE_START_WAIT(MSG_AREA170_ASK_ENTER_SPARK_FLOOR);
            g_SceneEventState.step = 0x33;
            break;
        case 52:
            Game_ClearScriptActive();
            Scene_SetupParty(0xC);
            g_SceneEventState.step = 0x35;
            break;
        case 53:
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                u16* input;
                u16  held;

                input           = &g_PadStates[0].held;
                held            = *input;
                SP_REF(u16, 0u) = held;
                *input          = held & 0xFFF;
                *input |= D_801F64B8[held >> 12] << 12;
            }
            break;
        case 55:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_ClearScriptActive();
            g_SceneEventState.mode = 0;
            g_SceneEventState.step = 0;
            break;
        case 60:
            Game_ClearScriptActive();
            g_Game.members[1].u.field.unk_122++;
            g_SceneEventState.mode = 0;
            g_SceneEventState.step = 0;
            /* FAKE: block boundary keeps the second counter below the mode stores. */
            do {
                g_Game.members[2].u.field.unk_122++;
                g_GameFlags &= 0xEFEF;
            } while (0);
            break;
    }
}
