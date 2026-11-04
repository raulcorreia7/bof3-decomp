#include "boss008_16.h"

MATCH void func_800C196C(void) {
    g_SpadWork->word_08.byte.unk_09   = 0x40;
    g_SpadWork->word_08.byte.timer_0A = 0x40;
    SND_PlayCue(EMI_CUE_ID(6, 1));
    g_SpadWork->unk_04++;
}
