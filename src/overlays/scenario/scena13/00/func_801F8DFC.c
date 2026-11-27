/* FAKE: retail re-reads each scroll target right after storing it. */
#define FAKE_DECL_AREA_SCROLL_TARGET_VOLATILE
#define FAKE_DECL_AREA_SCROLL_TARGET_Y_VOLATILE
#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8DFC(void) {
    u8* state;
    u8  slot;
    s32 x;
    s32 y;

    switch (g_ScenarioState.step) {
        case 0:
            if (g_ScriptVars[0] == 2) {
                D_801FBFEC = func_8019601C();
                if (D_801FBFEC != 0xFF) {
                    g_SpawnedActors[D_801FBFEC].header.flags   = 1;
                    g_SpawnedActors[D_801FBFEC].type           = 0x13;
                    g_SpawnedActors[D_801FBFEC].camera_angle.x = -0x370;
                    g_SpawnedActors[D_801FBFEC].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FBFEC].camera_angle.z = 0x299;
                    g_SpawnedActors[D_801FBFEC].layer          = 0xFF;
                    g_AreaTileRemainderY -= 0x800;
                    g_ScenarioState.timer_06 = 0x80;
                    g_ScenarioState.step     = 1;
                }
            }
            break;
        case 1:
            if (--g_ScenarioState.timer_06 == 0) {
                g_AreaSceneMode      = 1;
                g_ScenarioState.step = 2;
                g_AreaTileRemainderY -= 0x800;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 3) {
                D_801FBFEC = func_8019601C();
                if (D_801FBFEC != 0xFF) {
                    g_SpawnedActors[D_801FBFEC].header.flags   = 1;
                    g_SpawnedActors[D_801FBFEC].type           = 0x13;
                    g_SpawnedActors[D_801FBFEC].camera_angle.x = -0x2AA;
                    g_SpawnedActors[D_801FBFEC].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FBFEC].camera_angle.z = 0x200;
                    g_SpawnedActors[D_801FBFEC].layer          = 0x40;
                    g_ScenarioState.timer_06                   = 0x20;
                    g_ScenarioState.step                       = 3;
                }
            }
            break;
        case 3:
            if (--g_ScenarioState.timer_06 == 0) {
                g_AreaSceneMode      = 0;
                g_ScenarioState.step = 4;
                g_AreaTileRemainderY += 0x800;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0) {
                g_AreaTileRemainderY += 0x800;
                SYS_SetFlag(g_SceneFlags, 7);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
        case 5:
            Game_ClearScriptActive();
            func_801BE1B0(7);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 10:
            Item_VitalRemove(0xB);
            func_801C601C(2);
            g_ScenarioState.step = 11;
            break;
        case 11:
            if (g_ScriptVars[0] == 0x12) {
                g_AreaDrawFlags = 0;
                SCENARIO_MESSAGE_WAIT(MSG_SCENA13_024, 12);
            }
            break;
        case 12:
            state = &g_GameStateIndex;
            if (*state != GAME_REQUEST_MESSAGE) {
                g_AreaScrollTargetX       = TO_COORD(10);
                x                         = g_AreaScrollTargetX;
                g_AreaScrollTargetY       = TO_COORD(98);
                y                         = g_AreaScrollTargetY;
                g_PartyPos.x.fixed        = TO_COORD(10);
                g_PartyPos.y.fixed        = TO_COORD(98);
                g_PartyPos.z.part.integer = Area_HeightSample(x, y);
                Area_InitMapRenderer();
                UI_MessageStartArea(MSG_SCENA13_025);
                *state = GAME_REQUEST_MESSAGE;
                UI_ModeSet(1);
                g_AreaDrawFlags      = 0x1F;
                g_AreaCameraAngle.vx = -0x344;
                g_AreaCameraAngle.vz = 0x3A2;
                D_801FBFEC           = func_8019601C();
                if (D_801FBFEC != 0xFF) {
                    g_SpawnedActors[D_801FBFEC].header.flags   = 1;
                    g_SpawnedActors[D_801FBFEC].type           = 0x13;
                    g_SpawnedActors[D_801FBFEC].camera_angle.x = -0x2AA;
                    g_SpawnedActors[D_801FBFEC].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FBFEC].camera_angle.z = 0x200;
                    g_SpawnedActors[D_801FBFEC].layer          = 0x64;
                    g_ScenarioState.step                       = 13;
                }
            }
            break;
        case 13:
            if (!(g_SpawnedActors[D_801FBFEC].header.flags & 1) && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SYS_SetFlag(g_SceneFlags, 9);
                func_8019FA28(0x91, TO_COORD_HALF(63), TO_COORD(94), 0x88);
                g_SndBGMId               = 0x5C;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
        case 20:
            if (g_ScriptVars[0] == 1) {
                Game_SetScriptActive();
                func_8019FA28(0x58, TO_COORD(19), TO_COORD(37), 0x80);
                g_GameRequestType    = 1;
                g_ScenarioState.step = 21;
            }
            break;
        case 21:
            if (g_UIWindowEffectBusy == 0) {
                g_ScenarioState.timer_06 = 0x3C;
                g_ScenarioState.step     = 22;
            }
            break;
        case 22:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
            } else {
                slot = func_8019601C();
                if (slot != 0xFF) {
                    g_SpawnedActors[slot].header.flags = 1;
                    g_SpawnedActors[slot].type         = 0x80;
                }
                g_ScenarioState.timer_06 = 0x46;
                g_ScenarioState.step     = 23;
            }
            break;
        case 23:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
            } else {
                func_8019FA28(0x70, TO_COORD_HALF(12), TO_COORD(88), 0x81);
                g_GameEntryMode      = 0;
                g_ScenarioState.step = 24;
            }
            break;
        case 24:
            if (g_UIWindowEffectBusy == 0) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0xB);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
    }
}
