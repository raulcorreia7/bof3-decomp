#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FAB08(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if ((g_UiWindowChannel & 2) == 0) {
                break;
            }
            if (g_ScriptVars[0] == 1) {
                g_SceneState.step_05 = 1;
            } else {
                Game_ClearScriptActive();
                g_ScriptVars[0] = 0;
                Scene_ClearScriptState(&g_SceneState.step_05);
            }
            break;
        case 1:
            g_ScriptVars[0]      = 2;
            g_SceneState.step_05 = 2;
            break;
        case 2:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_SceneState.step_05 = 3;
            SYS_SetFlag(g_SceneFlags, 0x2D);
            Game_RequestAreaChange(0x50, TO_COORD(32), TO_COORD(10), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_DOWN_LEFT);
            g_GamePrevSelection = 0x4F;
            break;
        case 3:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            g_SceneState.step_05 = 4;
            SYS_SetFlag(g_SceneFlags, 0x2E);
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            SND_PlayCue(0x208);
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(0x50, TO_COORD(129), TO_COORD(7), 0x85);
                    g_GamePrevSelection = 0xFF;
                    break;
                case 2:
                    Game_RequestAreaChange(0x50, TO_COORD(129), TO_COORD(7), 0x84);
                    g_GamePrevSelection = 0xFF;
                    break;
            }
            break;
        case 4:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            UI_SetMode(0xD);
            g_SceneState.step_05 = 5;
            break;
        case 5:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_AreaDrawFlags      = 0;
            g_SceneState.step_05 = 6;
            break;
        case 6:
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    func_801C1E3C(0);
                    break;
                case 2:
                    func_801C1E3C(1);
                    func_801C1E3C(3);
                    break;
            }
            g_ScriptVars[2]      = 1;
            g_SceneState.step_05 = 7;
            Game_RequestAreaChange(0x50, TO_COORD(198), TO_COORD(15) + COORD_HALF, 0x82);
            g_GamePrevSelection = 0xFF;
            break;
        case 7:
            g_AreaDrawFlags      = 0x1F;
            g_SceneState.step_05 = 8;
            break;
        case 8:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            Area_StartScrollRoute(0);
            g_SceneState.step_05 = 9;
            break;
        case 9:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            SND_PlayCue(0x209);
            SND_PlayBGM(0x66, 0x64, 8);
            g_SceneState.step_05 = 10;
            break;
        case 10:
            if (g_ScriptVars[0] != 0xB) {
                break;
            }
            func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x16);
            Battle_StartScripted(0x16);
            g_SceneState.step_05 = 11;
            break;
        case 11:
            if (g_ScriptVars[0] != 0xC) {
                break;
            }
            Scene_SetupParty(3);
            SND_PlayBGM(0x6A, 0x64, 0x10);
            g_SceneState.step_05 = 12;
            break;
        case 12:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            g_SceneState.step_05 = 13;
            SYS_SetFlag(g_SceneFlags, 0x2F);
            UI_SetMode(0xD);
            break;
        case 13:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_AreaDrawFlags      = 0;
            g_SceneState.step_05 = 14;
            break;
        case 14:
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    g_SceneState.step_05 = 15;
                    Scene_RunScenario(1);
                    Scene_RunScenario(2);
                    Game_RequestAreaChange(0x50, TO_COORD(129), TO_COORD(11), 0x81);
                    break;
                case 2:
                    g_SceneState.step_05 = 15;
                    Scene_RunScenario(1);
                    Scene_RunScenario(3);
                    Game_RequestAreaChange(0x50, TO_COORD(129), TO_COORD(11), 0x80);
                    break;
            }
            break;
        case 15:
            g_AreaDrawFlags      = 0x1F;
            g_SceneState.step_05 = 16;
            break;
        case 16:
            if (g_ScriptVars[0] != 8) {
                break;
            }
            func_801C16B8();
            g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
            SYS_SetFlag(g_SceneFlags, 0x3D);
            Game_ClearScriptActive();
            Scene_ClearScriptState(&g_SceneState.step_05);
            break;
    }
}
#else
INCLUDE_ASM(func_801FAB08);
#endif
