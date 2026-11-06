#include "area043_13.h"

MATCH void func_801F3070(void) {
    SYS_SetFlag(g_SaveData.scene_event_flags, 0x7FU);
    Area_SetCellPalette(0x44, 0xB);
    SND_PlayCue(EMI_CUE_ID(1, 3));
}
