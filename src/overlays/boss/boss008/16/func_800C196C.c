#include "boss008_16.h"

MATCH void func_800C196C(void) {
    g_Task->unk_09 = 0x40;
    g_Task->timer  = 0x40;
    SND_PlayCue(EMI_CUE_ID(6, 1));
    g_Task->unk_04++;
}
