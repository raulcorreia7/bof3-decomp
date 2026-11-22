#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F873C(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            func_8019FA28(0xC2, TO_COORD(19), TO_COORD(25), 1);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 3) {
                D_801FBFEC = func_8019601C();
                if (D_801FBFEC != 0xFF) {
                    g_SpawnedActors[D_801FBFEC].header.flags = 1;
                    g_SpawnedActors[D_801FBFEC].type         = 0x75;
                }
                SND_BGMFadeOut(0x71, 100, 8);
                g_ScenarioState.step_05 = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0) {
                SYS_SetFlag(g_SceneFlags, 2);
                func_8019FA28(0xC2, TO_COORD(60) + COORD_HALF, TO_COORD(11), 0x81);
                g_GameEntryMode         = 0xFF;
                g_GamePrevSelection     = 0xFF;
                g_ScenarioState.step_05 = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 2) {
                D_801FBFEC = func_8019601C();
                if (D_801FBFEC != 0xFF) {
                    g_SpawnedActors[D_801FBFEC].header.flags = 1;
                    g_SpawnedActors[D_801FBFEC].type         = 0x75;
                }
                g_ScenarioState.step_05 = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0) {
                SYS_SetFlag(g_SceneFlags, 3);
                func_8019FA28(0xC2, TO_COORD(19), TO_COORD(19), 3);
                g_ScenarioState.step_05 = 5;
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 5) {
                D_801FBFEC = func_8019601C();
                if (D_801FBFEC != 0xFF) {
                    g_SpawnedActors[D_801FBFEC].header.flags = 1;
                    g_SpawnedActors[D_801FBFEC].type         = 0x75;
                }
                SND_BGMFadeOut(0x71, 100, 8);
                g_ScenarioState.step_05 = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0) {
                SYS_SetFlag(g_SceneFlags, 4);
                func_8019FA28(0xC2, TO_COORD(60) + COORD_HALF, TO_COORD(11), 0x83);
                g_GamePrevSelection     = 0xFF;
                g_ScenarioState.step_05 = 7;
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 1) {
                UI_ModeSet(0);
                g_ScriptVars[0]         = 0;
                g_ScenarioState.step_05 = 8;
            }
            break;
        case 8:
            if (g_UiWindowEffectBusy == 0) {
                g_ScenarioState.timer_06 = 120;
                g_AreaDrawFlags          = 0;
                g_ScenarioState.step_05  = 9;
            }
            break;
        case 9:
            if (--g_ScenarioState.timer_06 == 0) {
                func_801C1DF0(3);
                SND_XAStartStream(0, 1);
                SYS_SetFlag(g_SceneFlags, 5);
                g_ScenarioState.step_05 = 10;
            }
            break;
        case 10:
            if ((u8)SND_XAIsIdle() != 0) {
                func_801C16B8();
                func_8019FA28(0x97, TO_COORD(51), TO_COORD(55), 1);
                g_GameRequestType       = 0xFF;
                g_GameEntryMode         = 0xFF;
                g_ScenarioState.step_05 = 11;
            }
            break;
        case 11:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0x1F;
                UI_ModeSet(0xB);
                g_GameFlags &= 0xFFF7;
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
    }
}
