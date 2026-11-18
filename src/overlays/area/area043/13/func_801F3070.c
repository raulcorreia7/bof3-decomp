#include "area043_13.h"

MATCH void func_801F3070(void) {
    SYS_SetFlag(g_SceneEventFlags, 127U);
    Area_SetCellPalette(68, 11);
    SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 3));
}
