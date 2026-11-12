#include "area043_13.h"

MATCH void func_801F3070(void) {
    SYS_SetFlag(g_SceneEventFlags, 127U);
    Area_SetCellPalette(68, 11);
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
}
