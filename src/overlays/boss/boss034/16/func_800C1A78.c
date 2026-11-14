#include "boss034_16.h"

MATCH void func_800C1A78(void) {
    Actor_StepAnimOnce();
    GFX_ClearRect(832, 256, 192, 256);
    g_Task->unk_18             = g_Task->unk_2E.signed_half;
    g_Task->unk_1C             = g_Task->unk_30.signed_half;
    g_Task->unk_0C             = 190;
    g_Task->unk_10             = 104;
    g_Task->unk_2E.signed_half = 100;
    g_Task->unk_20             = 0;
    g_Task->unk_30.signed_half = 80;
    g_Task->timer              = 1;
    g_Task->unk_24 |= 0x88;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_ENEMY, 2));
    func_800C23D4(g_Task->unk_09);
    g_Task->unk_03++;
}
