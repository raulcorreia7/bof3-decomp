#include "scena09_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8504(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if (D_8014625A & 7) {
                break;
            }
            D_80146258 |= 8;
            func_801C601C(1);
            Scene_SetupParty(5);
            g_SceneState.step_05 = 2;
            break;
        case 2:
            if (*g_ScriptVars != 0x12) {
                break;
            }
            *g_ScriptVars        = 0;
            g_ScriptVars[2]      = 0;
            g_SceneState.step_05 = 3;
            SYS_SetFlag(g_SceneFlags, 2);
            func_8019FA28(0x31, 0x540000, 0x640000, 0x86);
            break;
        case 3:
            if (g_AreaCameraMoving) {
                break;
            }
            *g_ScriptVars        = 1;
            g_SceneState.step_05 = 5;
            break;
        case 5:
            if (*g_ScriptVars != 0x11) {
                break;
            }
            SND_FadeOutSequence(0, 0, 4, 0x1E);
            SND_StartXAStream(3, 1);
            g_SceneState.step_05 = 6;
            break;
        case 6:
            if (SND_IsXAIdle() == 0) {
                break;
            }
            *g_ScriptVars = 0x12;
            SND_PlayBGM(0x10, 0x64, 8);
            g_SceneState.step_05 = 7;
            break;
        case 7:
            if (*g_ScriptVars != 0x12) {
                break;
            }
            D_80146258 ^= 8;
            SYS_SetFlag(g_SceneFlags, 3);
            SYS_ClearFlag(g_SceneFlags, 0x25);
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 10:
            g_SceneState.step_05 = 0xB;
            SYS_SetFlag(g_SceneFlags, 4);
            func_8019FA28(0x31, 0x3F8000, 0x140000, 0x87);
            break;
        case 11:
            if (*g_ScriptVars != 0xB) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 4);
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
    }
}
