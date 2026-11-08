#include "area041_13.h"

MATCH void func_801F4288(u8* actor) {
    SYS_SetFlag(g_SceneEventFlags, D_801F5651[actor[0x7A]]);
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x01));
}
