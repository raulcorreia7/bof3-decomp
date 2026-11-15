#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8EB0(void) {
    switch (g_SceneState.step_05) {
        case 0:
            SND_PlayBGM(1, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 0x5) {
                g_ScriptVars[0]      = 0x6;
                g_SceneState.step_05 = 2;
            }
            /* fallthrough */
        case 2:
            if (g_ScriptVars[0] == 0x8) {
                g_SceneState.step_05 = 3;
                SYS_SetFlag(g_SceneFlags, 0x10);
                Game_RequestAreaChange(0x2D, TO_COORD(0x3C), TO_COORD(0x2E), 0x83);
                g_GamePrevSelection = 1;
            }
            break;
        case 3:
            Area_StartScrollRoute(3);
            g_SceneState.step_05 = 10;
            break;
        case 10:
            if (g_ScriptVars[0] == 0xC) {
                g_SceneState.step_05 = 0xB;
                g_ScriptVars[0]      = 0x14;
                SYS_SetFlag(g_SceneFlags, 0x11);
                g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
                Game_RequestAreaChange(0x32, TO_COORD(8), TO_COORD(0x26), 0x80);
            }
            break;
        case 11:
            if (g_ScriptVars[0] == 0x1C) {
                Area_StartScrollRoute(0);
                g_SceneState.step_05 = 0xC;
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 0x1D) {
                g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
                SYS_SetFlag(g_SceneFlags, 0x12);
                switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                    case 1:
                        g_ScriptVars[2] = 0;
                        SYS_SetFlag(g_SceneFlags, 0x13);
                        Game_RequestAreaChange(0x4E, TO_COORD(0x24), TO_COORD(0xAD), 0x80);
                        g_GamePrevSelection = 0xFF;
                        break;
                    case 2:
                        g_ScriptVars[2] = 2;
                        SYS_SetFlag(g_SceneFlags, 0x13);
                        func_801C1E3C(3);
                        Game_RequestAreaChange(0x4E, TO_COORD(0x24), TO_COORD(0xAD), 3);
                        g_GamePrevSelection = 0xFF;
                        break;
                    case 6:
                        g_ScriptVars[2] = 3;
                        SYS_SetFlag(g_SceneFlags, 0x13);
                        func_801C1E3C(3);
                        Game_RequestAreaChange(0x4E, TO_COORD(0x24), TO_COORD(0xAD), 3);
                        g_GamePrevSelection = 0xFF;
                        break;
                }
            }
            break;
    }
}
