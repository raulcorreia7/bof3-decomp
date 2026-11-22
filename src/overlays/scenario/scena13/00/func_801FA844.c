#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA844(void) {
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (g_ScriptVars[0] != 0xB) {
                break;
            }
            UI_ModeSet(0);
            SND_SeqStop(0, 0);
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SND_BGMPlay(0x6F, 0x64, 0x10);
            g_ScenarioState.timer_06 = 0x96;
            g_ScenarioState.step     = 2;
            break;
        case 2:
            func_801FAFA0(6, 5);
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            g_ScenarioState.step = 3;
            g_ScriptVars[0]++;
            break;
        case 3:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            UI_ModeSet(7);
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_AreaCameraAngle.vx = -0x386;
            g_AreaCameraAngle.vz = 0x3B8;
            g_AreaCameraOffsetZ  = -0xDFC;
            D_801FBFEC           = Actor_FindFreeSpawned();
            if (D_801FBFEC != GAME_NONE) {
                g_SpawnedActors[D_801FBFEC].header.flags   = ACTOR_FLAG_IN_USE;
                g_SpawnedActors[D_801FBFEC].type           = 0x31;
                g_SpawnedActors[D_801FBFEC].camera_angle.x = -0x2EC;
                g_SpawnedActors[D_801FBFEC].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_801FBFEC].camera_angle.z = g_AreaCameraAngle.vz;
                g_SpawnedActors[D_801FBFEC].vx             = 0;
                g_SpawnedActors[D_801FBFEC].layer          = 0x3C;
            }
            g_ScenarioState.timer_06 = 0x96;
            g_ScenarioState.step     = 4;
            break;
        case 4:
            func_801FAFA0(7, 5);
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step     = 5;
            g_ScriptVars[0]++;
            break;
        case 5:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            g_ScenarioState.timer_06 = 0x12C;
            g_ScenarioState.step     = 6;
            break;
        case 6:
            func_801FAFA0(8, 0xA);
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            g_ScenarioState.step = 7;
            break;
        case 7:
            if (g_ScriptVars[0] != 0xE) {
                break;
            }
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step     = 8;
            break;
        case 8:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            g_ScenarioState.timer_06 = 0x96;
            g_ScenarioState.step     = 9;
            UI_ModeSet(6);
            break;
        case 9:
            func_801FAFA0(9, 5);
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
            } else {
                g_AreaCameraAngle.vx = -0x2AA;
                g_AreaCameraAngle.vz = 0x200;
                g_ScriptVars[0]++;
                UI_ModeSet(1);
                g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
                g_ScenarioState.step = 0xA;
            }
            if (!WINDOW_EFFECT_BUSY()) {
                g_AreaDrawFlags = 0;
            }
            break;
        case 10:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x17);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 20:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            SND_StartDecrescendo(0, 0, 0x64, 0x10);
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step     = 0x15;
            break;
        case 21:
            g_AreaCameraOffsetZ += 0x50;
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            SND_SeqStop(0, 0);
            slot = Actor_FindFreeSpawned();
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = ACTOR_FLAG_IN_USE;
                g_SpawnedActors[slot].type         = 0x87;
            }
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step     = 0x16;
            break;
        case 22:
            if (g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_ScenarioState.step = 0x17;
            g_ScriptVars[0]++;
            break;
        case 23:
            if (g_ScriptVars[0] != 0xB) {
                break;
            }
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step     = 0x18;
            break;
        case 24:
            g_AreaCameraOffsetZ -= 0x50;
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_ScriptVars[0]      = 0x32;
            g_ScenarioState.step = 0x19;
            break;
        case 25:
            if (g_ScriptVars[0] != 0x34) {
                break;
            }
            g_AreaScrollTargetX = TO_COORD(36);
            g_AreaScrollTargetY = TO_COORD(28) + COORD_HALF;
            Area_InitMapRenderer();
            Game_BattleStartEncounter(TO_COORD(40) + COORD_HALF, TO_COORD(29) + COORD_HALF, 0x25);
            g_ScenarioState.step = 0x1A;
            g_ScriptVars[0]++;
            break;
        case 26:
            if (g_ScriptVars[0] != 0x37) {
                break;
            }
            Game_BattleStartScripted(0x25);
            g_ScenarioState.step = 0x1B;
            break;
        case 28:
            g_ScriptVars[0]++;
            Scene_SetupParty(7);
            D_801FBFEC = Actor_FindFreeSpawned();
            if (D_801FBFEC != GAME_NONE) {
                g_SpawnedActors[D_801FBFEC].header.flags = ACTOR_FLAG_IN_USE;
                g_SpawnedActors[D_801FBFEC].type         = 0x86;
            }
            g_ScenarioState.step = 0x1D;
            break;
        case 29:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x1A);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
    }
}
