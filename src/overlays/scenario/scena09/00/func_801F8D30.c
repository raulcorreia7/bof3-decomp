#include "scena09_00.h"
#include "menu/gameui.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801F8D30(void) {
    u8 slot;
    u8 counter;

    switch (g_SceneState.step_05) {
        case 0:
            g_SceneState.step_05 = 1;
            SYS_SetFlag(g_SceneFlags, 7);
            func_8019FA28(AREA_ID_PLANT, 0x490000, 0x238000, 0x88);
            break;
        case 1:
            g_SceneState.step_05 = 2;
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            break;
        case 2:
            if (g_ScriptVars[0] == 1) {
                goto clear_script;
            }
            break;
        case 5:
            if (D_80145ECC > ((1 << 27) - 1)) {
                SYS_SetFlag(g_SceneFlags, 0x27);
                if (SYS_TestFlag(g_SceneFlags, 0x26)) {
                    g_ScriptVars[0]      = 5;
                    g_ScriptVars[1]      = 1;
                    g_SceneState.step_05 = 10;
                    break;
                }
            }
            goto clear_script;
        case 6:
            if (D_80145ECC > ((1 << 27) - 1)) {
                SYS_SetFlag(g_SceneFlags, 0x26);
                if (SYS_TestFlag(g_SceneFlags, 0x27)) {
                    g_ScriptVars[0]      = 5;
                    g_ScriptVars[1]      = 2;
                    g_SceneState.step_05 = 10;
                    break;
                }
            }
            goto clear_script;
        case 10:
            Scene_SetupParty(9);
            g_SceneState.step_05 = 11;
            break;
        case 11:
            if (g_ScriptVars[0] == 7) {
                g_ScriptVars[2]      = 1;
                g_SceneState.step_05 = 12;
                func_8019FA28(AREA_ID_PLANT, 0x248000, 0x210000, 0x8A);
            }
            break;
        case 12:
            Area_StartScrollRoute(3);
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x268;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x10E;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 2;
                g_SceneState.step_05                                        = 13;
            }
            break;
        case 13:
            if (!g_UiWindowEffectBusy) {
                g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
                g_SceneState.step_05 = 14;
            }
            break;
        case 14:
            g_AreaCameraRefreshCount = 2;
            counter                  = g_ScriptVars[3] + 1;
            g_AreaCameraOffsetZ      = (u16)(g_AreaCameraOffsetZ - 0x5C);
            g_ScriptVars[3]          = counter;
            if (counter < 0x20) {
                break;
            }
            g_ScriptVars[0]          = 8;
            g_AreaCameraOffsetZ      = 0;
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[3]          = 0;
            g_SceneState.step_05     = 15;
            break;
        case 15:
            if (g_ScriptVars[0] == 9) {
                SYS_SetFlag(g_SceneFlags, 0x3E);
                g_SceneState.step_05 = 16;
            }
            break;
        case 16:
            if (g_ScriptVars[0] == 10) {
                g_ScriptVars[2]      = 0;
                g_SceneState.step_05 = 17;
                SYS_SetFlag(g_SceneFlags, 8);
                switch (g_ScriptVars[1]) {
                    case 1:
                        func_8019FA28(AREA_ID_PLANT, 0x80000, 0x378000, 0x8B);
                        break;
                    case 2:
                        func_8019FA28(AREA_ID_PLANT, 0x1A0000, 0x2F0000, 0x8C);
                        break;
                }
            }
            break;
        case 17:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            g_GameFlags &= ~GAME_FLAG_MENU_LOCK;
            g_ScriptVars[1] = 0;
        clear_script:
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 30:
            Area_SetCellPalette(0xB, 0x54);
            Scene_SetupParty(0xD);
            g_SceneState.step_05 = 31;
            break;
        case 31:
            if (g_ScriptVars[0] == 7) {
                g_SceneState.step_05 = 32;
                g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
                func_8019FA28(AREA_ID_HIDDEN_FACTORY_ENTRANCE, 0x3F0000, 0x58000, 0x80);
            }
            break;
        case 32:
            if (g_ScriptVars[0] == 5) {
                g_SceneState.step_05 = 33;
                g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
                func_8019FA28(AREA_ID_HIDDEN_FACTORY_ENTRANCE, 0xE0000, 0x148000, 0x81);
            }
            break;
        case 33:
            Area_StartScrollRoute(0);
            g_SceneState.step_05 = 34;
            break;
        case 34:
            if (g_ScriptVars[0] == 0x11 && !g_AreaCameraMoving) {
                SYS_SetFlag(g_SceneFlags, 0xB);
                Game_ClearScriptActive();
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
                g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
            }
            break;
    }
}
#else
INCLUDE_ASM(func_801F8D30);
#endif
