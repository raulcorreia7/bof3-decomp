#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC900(void) {
    u16* timer;

    switch (D_80146875) {
        case 0:
            Message_StartAreaMessage(2);
            g_GameStateIndex = 2;
            D_80146875       = 1;
            break;

        case 1:
            if (g_GameStateIndex != 2 && g_InputHeld != 0) {
                Scene_SetupParty(0);
                D_80146876 = 0x1E;
                D_80146875 = 2;
                D_801FE9DC = 1;
            }
            break;

        case 2:
            func_801FC220();
            timer = &D_80146876;
            if (--*timer == 0) {
                SYS_ClearFlag(g_SceneEventFlags, 0x4F);
                HIH(g_AreaScrollTargetY) += 7;
                g_AreaSceneMode  = 1;
                g_AreaCameraStep = D_80181BD7 << 3;
                SCENA10_SPAWN_ANGLED_ACTOR(-0x3B4, 0x2A6);
                D_801FE9DC = 0;
                D_80146875 = 3;
            }
            break;

        case 3:
            if (g_AreaCameraMoving == 0) {
                g_AreaSceneMode = 2;
                D_80146876      = 0x1E;
                D_80146875      = 4;
            }
            break;

        case 4:
            timer = &D_80146876;
            if (--*timer == 0) {
                HIH(g_AreaScrollTargetY) -= 7;
                g_AreaCameraStep = D_80181BD7 << 3;
                SCENA10_SPAWN_ANGLED_ACTOR(-0x2AA, 0x200);
                D_80146875 = 5;
            }
            break;

        case 5:
            if (g_AreaCameraMoving == 0) {
                g_AreaSceneMode = 0;
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0x35);
                D_80146874 = 0;
                D_80146875 = 0;
            }
            break;
    }
}
