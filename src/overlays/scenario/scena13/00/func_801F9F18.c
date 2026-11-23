#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Step script: camera-actor cuts, area changes and scene flags 0x11 to 0x16. */
MATCH void func_801F9F18(void) {
    switch (g_ScenarioState.step) {
        case 0:
            func_8019FA28(0x8F, 0x3A8000, 0x1F8000, 0x82);
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 7) {
                D_801FBFEC = func_8019601C();
                if (D_801FBFEC != 0xFF) {
                    g_SpawnedActors[D_801FBFEC].header.flags   = 1;
                    g_SpawnedActors[D_801FBFEC].type           = 0x13;
                    g_SpawnedActors[D_801FBFEC].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[D_801FBFEC].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FBFEC].camera_angle.z = 0x200;
                    g_SpawnedActors[D_801FBFEC].layer          = 0x20;
                    g_ScenarioState.step                       = 2;
                }
            }
            break;
        case 2:
            if (!(g_SpawnedActors[D_801FBFEC].header.flags & 1)) {
                g_ScenarioState.step = 3;
                g_ScriptVars[0]++;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0xE) {
                SYS_SetFlag(g_SceneFlags, 0x20);
                func_8019FA28(0x8F, 0x98000, 0x518000, 0x28);
                g_ScenarioState.step = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0xD) {
                SYS_SetFlag(g_SceneFlags, 0x11);
                SYS_SetFlag(g_SceneFlags, 0x21);
                func_8019FA28(0x8F, 0x350000, 0x330000, 0x84);
                g_GameRequestType    = 0xFF;
                g_GamePrevSelection  = 0xFF;
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            if (g_SysThreads[2].state == 0) {
                SYS_ClearFlag(g_SceneFlags, 0x20);
                g_ScenarioState.timer_06 = 0x3C;
                g_ScenarioState.step     = 6;
            }
            break;
        case 6:
            if (--g_ScenarioState.timer_06 == 0) {
                UI_ModeSet(1);
                g_AreaDrawFlags      = 0x1F;
                g_AreaCameraAngle.vx = -0x1CE;
                g_AreaCameraOffsetZ  = -0x780;
                D_801FBFEC           = func_8019601C();
                if (D_801FBFEC != 0xFF) {
                    g_SpawnedActors[D_801FBFEC].header.flags   = 1;
                    g_SpawnedActors[D_801FBFEC].type           = 0x31;
                    g_SpawnedActors[D_801FBFEC].camera_angle.x = -0x2AA;
                    g_SpawnedActors[D_801FBFEC].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FBFEC].camera_angle.z = g_AreaCameraAngle.vz;
                    g_SpawnedActors[D_801FBFEC].vx             = 0;
                    g_SpawnedActors[D_801FBFEC].layer          = 0x3C;
                }
                g_ScenarioState.step = 7;
            }
            break;
        case 7:
            if (!(g_SpawnedActors[D_801FBFEC].header.flags & 1)) {
                g_ScenarioState.step = 8;
                g_ScriptVars[0]++;
            }
            break;
        case 8:
            if (g_ScriptVars[0] == 0xB) {
                D_801FBFEC = func_8019601C();
                if (D_801FBFEC != 0xFF) {
                    g_SpawnedActors[D_801FBFEC].header.flags = 1;
                    g_SpawnedActors[D_801FBFEC].type         = 0x81;
                }
                g_ScenarioState.step = 9;
            }
            break;
        case 9:
            if (g_ScriptVars[0] == 0xC) {
                UI_ModeSet(0);
                g_ScenarioState.step = 10;
            }
            break;
        case 10:
            if (g_SysThreads[2].state == 0) {
                g_ScenarioState.timer_06 = 0x3C;
                g_AreaDrawFlags          = 0;
                g_ScenarioState.step     = 11;
            }
            break;
        case 11:
            if (--g_ScenarioState.timer_06 == 0) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 5));
                SCENARIO_MESSAGE_WAIT(MSG_SCENA13_020, 12);
            }
            break;
        case 12:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SYS_SetFlag(g_SceneFlags, 0x22);
                SYS_ClearFlag(g_SceneFlags, 0x21);
                func_8019FA28(0x8F, 0x90000, 0x4C0000, 0x85);
                g_GameEntryMode      = 0xFF;
                g_GameRequestType    = 0xFF;
                g_ScenarioState.step = 13;
            }
            break;
        case 13:
            if (g_SysThreads[2].state == 0) {
                UI_ModeSet(1);
                g_AreaDrawFlags      = 0x1F;
                g_ScenarioState.step = 14;
            }
            break;
        case 14:
            if (g_SysThreads[2].state == 0) {
                g_ScenarioState.step = 15;
                g_ScriptVars[0]++;
            }
            break;
        case 15:
            if (g_ScriptVars[0] == 0) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0x12);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
                D_80146258 |= 0x10;
            }
            break;
        case 20:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA13_038, 21);
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
        case 25:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801C1DF0(7);
                func_801BE1B0(7);
                g_Game.members[2].pos.x.fixed        = g_ScriptWorkRecord->pos.x.fixed;
                g_Game.members[2].pos.y.fixed        = g_ScriptWorkRecord->pos.y.fixed;
                g_Game.members[2].pos.z.part.integer = Area_HeightSample(g_Game.members[2].pos.x.fixed, g_Game.members[2].pos.y.fixed);
                g_ScriptWorkRecord->header.flags     = 0;
                g_ScenarioState.step                 = 26;
            }
            break;
        case 26:
            if (g_ScriptVars[0] == 2) {
                SYS_SetFlag(g_SceneFlags, 0x14);
                SYS_ClearFlag(g_SceneFlags, 0x22);
                func_8019FA28(0x8F, 0x78000, 0x508000, 0x88);
                g_GameEntryMode      = 0xFF;
                g_GameRequestType    = 0xFF;
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 27;
            }
            break;
        case 27:
            if (g_SysThreads[2].state == 0) {
                g_AreaDrawFlags = 0x1F;
                SCENARIO_MESSAGE_WAIT(MSG_SCENA13_042, 28);
            }
            break;
        case 28:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SYS_SetFlag(g_SceneFlags, 0x15);
                func_8019FA28(0x8F, 0xC8000, 0x218000, 0x89);
                g_ScenarioState.step = 29;
            }
            break;
        case 29:
            if (g_ScriptVars[0] == 0xA) {
                g_ScenarioState.step = 30;
            }
            break;
        case 30:
            if (g_ScriptVars[0] == 0) {
                Game_ClearScriptActive();
                D_80146258 &= ~0x10;
                SYS_SetFlag(g_SceneFlags, 0x16);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
    }
}
