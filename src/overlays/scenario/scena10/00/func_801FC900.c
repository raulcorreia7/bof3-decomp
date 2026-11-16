#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC900(void) {
    u16* timer;

    switch (g_SceneState.step_05) {
        case 0:
            Message_StartAreaMessage(2);
            g_GameStateIndex     = 2;
            g_SceneState.step_05 = 1;
            break;

        case 1:
            if (g_GameStateIndex != 2 && g_InputHeld != 0) {
                Scene_SetupParty(0);
                g_SceneState.timer_06 = 0x1E;
                g_SceneState.step_05  = 2;
                D_801FE9DC            = 1;
            }
            break;

        case 2:
            func_801FC220();
            timer = &g_SceneState.timer_06;
            if (--*timer == 0) {
                SYS_ClearFlag(g_SceneEventFlags, 0x4F);
                HIH(g_AreaScrollTargetY) += 7;
                g_AreaSceneMode  = 1;
                g_AreaCameraStep = D_80181BD7 << 3;
                SCENA10_SPAWN_ANGLED_ACTOR(-0x3B4, 0x2A6);
                D_801FE9DC           = 0;
                g_SceneState.step_05 = 3;
            }
            break;

        case 3:
            if (g_AreaCameraMoving == 0) {
                g_AreaSceneMode       = 2;
                g_SceneState.timer_06 = 0x1E;
                g_SceneState.step_05  = 4;
            }
            break;

        case 4:
            timer = &g_SceneState.timer_06;
            if (--*timer == 0) {
                HIH(g_AreaScrollTargetY) -= 7;
                g_AreaCameraStep = D_80181BD7 << 3;
                SCENA10_SPAWN_ANGLED_ACTOR(-0x2AA, 0x200);
                g_SceneState.step_05 = 5;
            }
            break;

        case 5:
            if (g_AreaCameraMoving == 0) {
                g_AreaSceneMode = 0;
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0x35);
                g_SceneState.state_04 = 0;
                g_SceneState.step_05  = 0;
            }
            break;
    }
}
