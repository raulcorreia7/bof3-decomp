#include "area040_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3A00(void) {
    u8  i;
    u8  j;
    u8  value;
    u8* flags;

    flags = &D_80144EA9;
    if (D_80143F03 != 1) {
        *flags &= 0xF0;
        for (i = 0; i < 7; i++) {
            func_801A4BC0(0x41, i + 3, 0xA4);
            func_801A4BC0(0x42, i + 3, 0xA4);
            func_801A4BC0(0x43, i + 3, 0xA4);
            func_801A4BC0(0x44, i + 3, 0xA4);
        }
    }
    if (D_80143F03 == 6 && SYS_TestFlag(g_SceneEventFlags, 0x27) == 0) {
        func_801A4BC0(0x92, 0x1D, 0);
        func_801A4BC0(0x93, 0x1D, 0);
        func_801A4BC0(0x92, 0x1C, 0x50);
        func_801A4BC0(0x93, 0x1C, 0x50);
    }
    if (D_80143F06 == 6 && D_80143F03 == 2) {
        g_GameFlags &= ~0x1000;
        SYS_ClearFlag(g_SceneEventFlags, 0x27);
        g_ScriptVars[0] = 0;
    }
    if (D_80143F06 == 4) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                value = D_801F4960[i][j];
                if (value != 0) {
                    Area_SetCellPalette(0x94 + j, (s16)(i + 0x20));
                }
            }
        }
    }
}
#else
INCLUDE_ASM(func_801F3A00);
#endif
