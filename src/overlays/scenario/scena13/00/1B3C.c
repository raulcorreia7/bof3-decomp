#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801F873C(void) {
    switch (g_SceneState.step_05) {
        case 0:
            Scene_SetupParty(3);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x20);
            g_SceneState.step_05 = 2;
            break;
        default:
            break;
    }
}
#else
INCLUDE_ASM(func_801F873C);
#endif

MATCH void func_801F8C1C(void) {
    SCENE_START_SCRIPT_PAIR(D_801FBF78);
}

MATCH void func_801F8D0C(void) {
    SCENE_START_SCRIPT_PAIR(D_801FBF98);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F8DFC(void) {
    switch (g_SceneState.step_05) {
        case 0:
            Game_ClearScriptActive();
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x21);
            g_SceneState.step_05 = 2;
            break;
        default:
            break;
    }
}
#else
INCLUDE_ASM(func_801F8DFC);
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801F9570(void) {
    switch (g_SceneState.step_05) {
        case 0:
            Game_ClearScriptActive();
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x22);
            g_SceneState.step_05 = 2;
            break;
        default:
            break;
    }
}
#else
INCLUDE_ASM(func_801F9570);
#endif
