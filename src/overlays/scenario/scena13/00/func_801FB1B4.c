#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB1B4(void) {
    u8* progress;

    switch (D_80146875) {
        case 0:
            if (D_801460FB != 0) {
                break;
            }
            if (D_8014623B != 0) {
                break;
            }
            func_801BE1B0(0xA);
            SYS_SetFlag(g_SceneFlags, 0x1D);
            D_80146874 = 0;
            D_80146875 = 0;
            break;
        case 4:
            Message_StartAreaMessage(1);
            g_GameStateIndex = 2;
            D_80146875       = 6;
            break;
        case 5:
            Message_StartAreaMessage(0x4E);
            g_GameStateIndex = 2;
            D_80146875       = 6;
            break;
        case 6:
            if (g_GameStateIndex != 2) {
                Game_ClearScriptActive();
                D_80146874 = 0;
                D_80146875 = 0;
            }
            break;
        case 8:
            progress = &g_ScriptVars[0];
            if (*progress == 0x28) {
                *progress  = 0;
                D_80146875 = 0xA;
            }
            break;
        case 10:
            if (g_GameStateIndex != 2) {
                Game_RequestAreaChange(0x97, 0x360000, 0x1D0000, 3);
                D_80146875 = 0xB;
            }
            break;
        case 11:
            if (g_GameStateIndex == 0) {
                SYS_SetFlag(g_SceneFlags, 0x1E);
                Game_ClearScriptActive();
                D_80146874 = 0;
                D_80146875 = 0;
                Scene_RequestChapterAdvance();
            }
            break;
    }
}
