#include "scena12_00.h"
#include "area/map.h"
#include "sys/exe.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The party's walk to the Wyndia balcony, the bridge scene and the world-map return. */
MATCH void func_801FB864(void) {
    u8 slot;
    u8 i;

    switch (g_ScenarioState.step) {
        case 0:
            if (D_8014623B != 3) {
                func_801BE1B0(0);
                g_ScenarioState.step = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 1) {
                SYS_SetFlag(g_SceneFlags, 0x30);
                Game_ClearScriptActive();
                g_ScriptVars[0] = 0;
                goto step_zero;
            }
            break;
        case 2:
            Game_ClearScriptActive();
            g_ScriptVars[0] = 0;
            goto reset_state;
            break;
        case 10:
            SND_SeqStop(0, 0);
            SND_BGMPlay(0xA4, 0x64, 8);
            func_801BE1B0(1);
            func_801C601C(0);
            g_ScenarioState.step = 0xB;
            break;
        case 11:
            if (g_ScriptVars[0] == 2) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                          = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x32E;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x8A;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x28;
                    g_ScenarioState.step                                        = 0xC;
                }
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 6) {
                func_801BE1B0(2);
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                          = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x28;
                    g_ScenarioState.step                                        = 0xD;
                    D_80146867                                                  = g_ScratchPad.cells.bytes[0];
                }
            }
            break;
        case 13:
            if (g_SpawnedActors[D_80146867].header.flags == 0 && g_AreaCameraMoving == 0) {
                g_ScriptVars[0]      = 7;
                g_ScenarioState.step = 0xE;
            }
            break;
        case 14:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 2) {
                    UI_MessageStartArea(5);
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 8) {
                    UI_MessageStartArea(4);
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 5) {
                    UI_MessageStartArea(3);
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 4) {
                    UI_MessageStartArea(2);
                }
            }
            g_GameStateIndex     = 2;
            g_ScenarioState.step = 0xF;
            break;
        case 15:
            if (g_GameStateIndex == 0) {
                g_ScriptVars[0]      = 0xA;
                g_ScenarioState.step = 0x10;
            }
            break;
        case 16:
            g_ScenarioState.step = 0x11;
            D_80146258 |= 8;
            break;
        case 17:
            if (g_ScriptVars[0] == 0xE && g_AreaCameraMoving == 0) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x82;
                }
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x83;
                }
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x84;
                }
                g_ScenarioState.step = 0x12;
            }
            break;
        case 18:
            if (D_80146865 != 0xFF) {
                if (g_PadStates[0].held == 0x3000 || g_PadStates[0].held == 0x6000 || g_PadStates[0].held == 0x2000) {
                    if (g_AreaCameraMoving == 0) {
                        func_801BE1B0(7);
                        func_801C601C(3);
                        g_ScenarioState.step = 0x12;
                    }
                } else if (D_80146866 != 0x80) {
                    D_80146866           = 0;
                    g_ScenarioState.step = 0x12;
                } else {
                    g_ScenarioState.step = 0x13;
                }
            }
            break;
        case 20:
            if (g_AreaCameraMoving == 0) {
                func_801BE1B0(4);
                func_801C601C(4);
                g_ScenarioState.step = 0x15;
            }
            break;
        case 21:
            if (g_ScriptVars[0] == 0x18) {
                g_ScenarioState.step = 0x16;
                SYS_SetFlag(g_SceneFlags, 2);
                func_801BFE34(0x348000, 0x258000, 0x26);
            }
            break;
        case 22:
            if (g_ScriptVars[0] == 0x19) {
                g_ScenarioState.step = 0x17;
                func_801C7A54(0x26);
            }
            break;
        case 30:
            if (g_AreaCameraMoving == 0) {
                func_801BE1B0(3);
                g_ScenarioState.step = 0x1F;
            }
            break;
        case 31:
            if (g_ScriptVars[0] == 1) {
                func_801BFE34(D_80146144 + 0x30000, 0x258000, 0x26);
                func_801C7A54(0x26);
                g_ScenarioState.step = 0x20;
            }
            break;
        case 32:
            if (g_ScriptVars[0] == 5) {
                SYS_SetFlag(g_SceneFlags, 0x2D);
                D_80146258 ^= 8;
                Game_ClearScriptActive();
                goto reset_state;
            }
            break;
        reset_state:
            D_80146865 = 0;
            D_80146866 = 0;
            D_80146867 = 0;
        step_zero:
            g_ScenarioState.step = 0;
            D_80146874           = 0;
            break;
        case 33:
            g_ScriptVars[0] = 0;
            func_801C601C(2);
            SYS_SetFlag(g_SceneFlags, 0x2D);
            g_ScenarioState.step = 0x22;
            break;
        case 34:
            if (g_ScriptVars[0] == 1) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                          = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x35A;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x14;
                    g_ScenarioState.step                                        = 0x2B;
                }
            }
            break;
        case 43:
            if (g_ScriptVars[0] == 2) {
                UI_ModeSet(0xD);
                g_ScenarioState.step = 0x2C;
            }
            break;
        case 44:
            if (g_ScriptVars[0] == 3) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                          = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x2B0;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x14;
                    g_ScenarioState.step                                        = 0x2D;
                }
            }
            break;
        case 45:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 0x2E;
            }
            break;
        case 46:
            UI_MessageStartArea(0xB);
            g_GameStateIndex     = 2;
            g_ScenarioState.step = 0x2F;
            break;
        case 47:
            if (g_GameStateIndex == 0) {
                D_80146866           = 0;
                g_ScenarioState.step = 0;
                D_80146874           = 0;
                SYS_SetFlag(g_SceneFlags, 0x3F);
                func_801A78F8();
                func_8019FA28(0x7E, 0x500000, 0x1E0000, 4);
            }
            break;
    }
}
