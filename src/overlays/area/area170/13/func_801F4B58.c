#include "area170_13.h"

MATCH void func_801F4B58(void) {
    u8   slot;
    u16* countdown;

    switch (g_SceneEventStep) {
        case 0:
            func_801BE1B0(0);
            g_SceneEventStep = 1;
            break;
        case 1:
            if (D_80146867 == 0x24) {
                SYS_SetFlag(g_SceneEventFlags, 0x55);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_HE_SHELLS, TO_COORD(6), TO_COORD(63), AREA_ENTRY_MAP_LOADING | FACING_UP_RIGHT);
                g_SceneEventStep = 0x1E;
            }
            break;
        case 5:
            func_801BE1B0(1);
            g_SceneEventStep = 6;
            break;
        case 6:
            if (D_80146867 == 0x24) {
                SYS_SetFlag(g_SceneEventFlags, 0x55);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_HE_SHELLS, TO_COORD(4), TO_COORD(117), AREA_ENTRY_MAP_LOADING | FACING_RIGHT);
                g_SceneEventStep = 0x1E;
            }
            break;
        case 10:
            func_801BE1B0(4);
            g_SceneEventStep = 0xB;
            break;
        case 11:
            if (D_80146867 == 0x44) {
                SYS_SetFlag(g_SceneEventFlags, 0x56);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_HE_SHELLS, TO_COORD(16), TO_COORD(93), AREA_ENTRY_MAP_LOADING | FACING_DOWN_LEFT);
                g_SceneEventStep = 0x1E;
            }
            break;
        case 15:
            func_801BE1B0(5);
            g_SceneEventStep = 0x10;
            break;
        case 16:
            if (D_80146867 == 0x44) {
                SYS_SetFlag(g_SceneEventFlags, 0x56);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_HE_SHELLS, TO_COORD(10), TO_COORD(147), AREA_ENTRY_MAP_LOADING | FACING_LEFT);
                g_SceneEventStep = 0x1E;
            }
            break;
        case 20:
            func_801BE1B0(8);
            g_SceneEventStep = 0x15;
            break;
        case 21:
            if (D_80146867 == 0x64) {
                SYS_SetFlag(g_SceneEventFlags, 0x57);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_HE_SHELLS, TO_COORD(23), TO_COORD(93), AREA_ENTRY_MAP_LOADING | 10);
                g_SceneEventStep = 0x1E;
            }
            break;
        case 25:
            func_801BE1B0(9);
            g_SceneEventStep = 0x1A;
            break;
        case 26:
            if (D_80146867 == 0x64) {
                SYS_SetFlag(g_SceneEventFlags, 0x57);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_HE_SHELLS, TO_COORD(17), TO_COORD(147), AREA_ENTRY_MAP_LOADING | 11);
                g_SceneEventStep = 0x1E;
            }
            break;
        case 29:
            if (D_80146867 == 0) {
                g_GameFlags |= 0x1010;
                SYS_ClearFlag(g_SceneEventFlags, 0x57);
                g_SceneEventStep = 0x35;
            }
            break;
        case 30:
            if (D_80146867 == 0) {
                SYS_ClearFlag(g_SceneEventFlags, 0x55);
                SYS_ClearFlag(g_SceneEventFlags, 0x56);
                SYS_ClearFlag(g_SceneEventFlags, 0x57);
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
            }
            break;
        case 40:
            slot = Actor_FindFreeSlot();
            if (slot != GAME_NONE) {
                g_ActorSlots[slot].header.flags = 1;
                g_ActorSlots[slot].type         = 0x7D;
                g_ActorSlots[slot].unk_2E       = 100;
                g_ActorSlots[slot].unk_30       = 100;
                /* FAKE: barrier keeps the message byte load after the slot stores. */
                FAKE_BARRIER();
                g_ActorSlots[slot].unk_06 = LOBU(g_MessageRequest) - 0xB;
            }
            D_801448EE       = 0;
            g_SceneEventStep = 0x29;
            break;
        case 41:
            if (LOHU(D_801448EE) == 1) {
                g_AreaScrollTargetX    = TO_COORD(26);
                g_AreaScrollTargetY    = TO_COORD(145);
                g_AreaCameraStep       = g_RouteSpeedScale[2] << 3;
                D_1F800000.view.raw[0] = Actor_FindFreeSlot();
                if (D_1F800000.view.raw[0] != GAME_NONE) {
                    g_ActorSlots[D_1F800000.view.raw[0]].header.flags   = 1;
                    g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                    g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = 0;
                    g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = 0;
                    g_ActorSlots[D_1F800000.view.raw[0]].layer          = 0x70;
                }
                g_SceneEventStep = 0x2A;
            }
            if (LOHU(D_801448EE) == 0xFF) {
                g_SceneEventStep = 0x2D;
            }
            break;
        case 42:
            if (!g_AreaCameraMoving) {
                D_801448EE       = 0x1E;
                g_SceneEventStep = 0x2B;
            }
            break;
        case 43:
            countdown = &LOHU(D_801448EE);
            if (--*countdown == 0) {
                *countdown       = 0x1E;
                g_SceneEventStep = 0x2C;
            }
            break;
        case 44:
            countdown = &LOHU(D_801448EE);
            if (--*countdown == 0) {
                g_AreaCameraStep       = g_RouteSpeedScale[3] << 3;
                g_AreaScrollTargetX    = g_Game.members[0].pos.x.fixed;
                g_AreaScrollTargetY    = g_Game.members[0].pos.y.fixed;
                D_1F800000.view.raw[0] = Actor_FindFreeSlot();
                if (D_1F800000.view.raw[0] != GAME_NONE) {
                    g_ActorSlots[D_1F800000.view.raw[0]].header.flags   = 1;
                    g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                    g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = -682;
                    g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = 512;
                    g_ActorSlots[D_1F800000.view.raw[0]].layer          = 0x38;
                }
                g_SceneEventStep = 0x2D;
            }
            break;
        case 45:
            if (!g_AreaCameraMoving) {
                Game_ClearScriptActive();
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
            }
            break;
        case 50:
            Message_StartAreaMessage(0xA);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            g_SceneEventStep = 0x33;
            break;
        case 52:
            Game_ClearScriptActive();
            func_801BE1B0(0xC);
            g_SceneEventStep = 0x35;
            break;
        case 53:
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                u16* input;
                u16  held;

                input           = &g_InputHeld;
                held            = *input;
                SP_REF(u16, 0u) = held;
                *input          = held & 0xFFF;
                /* The direction remap table at the payload's +0xCFC. */
                *input |= D_801F57BC[0xCFC + (held >> 12)] << 12;
            }
            break;
        case 55:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_ClearScriptActive();
            g_SceneEventMode = 0;
            g_SceneEventStep = 0;
            break;
        case 60:
            Game_ClearScriptActive();
            g_Game.members[1].u.field.unk_122++;
            g_SceneEventMode = 0;
            g_SceneEventStep = 0;
            /* FAKE: block boundary keeps the second counter below the mode stores. */
            FAKE_ORDER_LOCK_BEGIN
                g_Game.members[2].u.field.unk_122++;
                g_GameFlags &= 0xEFEF;
            FAKE_ORDER_LOCK_END;
            break;
    }
}
