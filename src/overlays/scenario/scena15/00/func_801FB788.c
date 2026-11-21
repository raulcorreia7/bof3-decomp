#include "scena15_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FB788(void) {
    u8* vars;
    s32 i;
    s32 r;

    switch (g_ScenarioState.step_05) {
        case 0:
            EMI_LoadArchive(EMI_SLOT_SCE15EF0);
            Scene_SetupParty(4);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 0xB) {
                if ((u8)Scene_SpawnActor(0x13, -0x32A, g_AreaCameraAngle.vy, 0x80, 0x70, 0)) {
                    g_ScenarioState.step_05 = 2;
                }
            }
            break;
        case 2:
            if (EMI_IsReady()) {
                if (g_ScriptVars[0] == 0xC) {
                    D_801FE748 = Actor_FindFreeSpawned();
                    if (D_801FE748 != GAME_NONE) {
                        g_SpawnedActors[D_801FE748].header.flags = 1;
                        g_SpawnedActors[D_801FE748].type         = 0x9C;
                        g_ScenarioState.timer_06                 = 0xF0;
                        g_ScenarioState.step_05                  = 3;
                    }
                }
            }
            break;
        case 3:
            if (--g_ScenarioState.timer_06 == 0) {
                g_AreaSceneMode         = 2;
                g_ScenarioState.step_05 = 4;
            }
            break;
        case 4:
            if (SYS_TestFlag(g_SceneEventFlags, 0x81)) {
                if ((u8)Scene_SpawnActor(0x13, -0x2AA, g_AreaCameraAngle.vy, 0x200, 0x3C, 0)) {
                    g_ScenarioState.step_05 = 5;
                }
            }
            break;
        case 5:
            if (!(g_SpawnedActors[D_801FE748].header.flags & 1)) {
                i = 5;
                do {
                    r = Scene_SetupParty((u8)i);
                    i++;
                    if ((u8)r == 0) {
                        break;
                    }
                } while ((u8)i < 9);
                g_ScenarioState.step_05 = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0xE) {
                func_801FDC6C(0x2E8000, 0x6D0000, 0, 0x13, 0);
                g_ScenarioState.timer_06 = 0xA;
                g_ScenarioState.step_05  = 7;
            }
            break;
        case 7:
            if (--g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.step_05 = 8;
                g_ScriptVars[0]++;
            }
            break;
        case 8:
            if (g_ScriptVars[0] == 0x13) {
                g_ScenarioState.timer_06 = 0xA;
                g_ScenarioState.step_05  = 9;
            }
            break;
        case 9:
            if (--g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
                g_ScriptVars[0]++;
            }
            break;
        case 15:
            Game_ClearScriptActive();
            g_AreaSceneMode = 2;
            SYS_SetFlag(g_SceneFlags, 1);
            Scene_SetupParty(9);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
        case 20:
            func_801FDC6C(0x440000, 0x20000, 4, 0xFF, 0);
            g_ScriptVars[0] = 1;
            Scene_SetupParty(1);
            g_ScenarioState.step_05 = 0x15;
            break;
        case 21:
            if (g_ScriptVars[0] == 3) {
                UI_SetMode(0);
                g_ScenarioState.step_05 = 0x16;
            }
            break;
        case 22:
            if (!WINDOW_EFFECT_BUSY()) {
                g_AreaDrawFlags = 0;
                SCENARIO_MESSAGE_WAIT(MSG_SCENA15_003, 0x17);
            }
            break;
        case 23:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScenarioState.step_05 = 0x18;
            }
            break;
        case 24:
            SYS_SetFlag(g_SceneFlags, 2);
            func_8019FA28(0x58, 0x3E0000, 0x210000, 0x82);
            g_GameEntryMode         = 0xFF;
            D_80143F1D              = 0xFF;
            g_GamePrevSelection     = 0x8E;
            g_ScenarioState.step_05 = 0x19;
            break;
        case 25:
            if (!WINDOW_EFFECT_BUSY()) {
                g_AreaDrawFlags = 0x1F;
                UI_SetMode(1);
                g_AreaCameraOffsetZ      = 0x5DC;
                g_AreaCameraRefreshCount = 2;
                g_ScenarioState.step_05  = 0x1A;
            }
            break;
        case 26:
            if (g_ScriptVars[0] == 5) {
                func_8019FA28(0xAE, 0x440000, 0x38000, 0x82);
                g_GameEntryMode         = 0;
                g_ScenarioState.step_05 = 0x1B;
            }
            break;
        case 27:
            vars = g_ScriptVars;
            if (*vars == 6) {
                SYS_SetFlag(g_SceneFlags, 3);
                *vars                    = 0;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
        case 30:
            func_801FDC6C(0x520000, 0x2F0000, 5, 2, 0);
            Scene_SetupParty(3);
            g_ScenarioState.step_05 = 0x1F;
            break;
        case 31:
            vars = g_ScriptVars;
            if (*vars == 2) {
                SYS_SetFlag(g_SceneFlags, 4);
                *vars                    = 0;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
        case 40:
            g_ScriptVars[0] = 0xA;
            Scene_SetupParty(4);
            g_ScenarioState.step_05 = 0x29;
            break;
        case 41:
            if (g_ScriptVars[0] == 0xC) {
                SYS_SetFlag(g_SceneFlags, 5);
                func_8019FA28(0x3A, 0x140000, 0x10000, 0x81);
                g_ScenarioState.step_05 = 0x2A;
                g_GamePrevSelection     = g_SndBGMId;
            }
            break;
        case 42:
            if (g_ScriptVars[0] == 0xE) {
                func_8019FA28(0xAE, 0x250000, 0x3A0000, 0x85);
                g_ScenarioState.step_05 = 0x2B;
            }
            break;
        case 43:
            if (g_ScriptVars[0] == 0) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 6);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
        case 50:
            SYS_SetFlag(g_SceneFlags, 7);
            func_8019FA28(2, 0x1A0000, 0x170000, 0x87);
            D_80143F1D              = 0xFF;
            g_GamePrevSelection     = 0x8E;
            g_ScenarioState.step_05 = 0x33;
            break;
        case 51:
            if (g_ScriptVars[0] == 1) {
                g_AreaDrawFlags = 0x1F;
                UI_SetMode(1);
                g_ScenarioState.step_05 = 0x34;
            }
            break;
        case 52:
            if (g_ScriptVars[0] == 2) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 8);
                func_8019FA28(0xAE, 0xA0000, 0x78000, 0x86);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 16:
        case 17:
        case 18:
        case 19:
        case 28:
        case 29:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
            break;
    }
}
#else
INCLUDE_ASM(func_801FB788);
#endif
