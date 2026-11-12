#include "area188_13.h"

MATCH void func_801F3484(void) {
    u8  timer;
    s32 spin;
    s32 i;

    g_Task->unk_6C += 0xC0000;
    g_Task->screen_x -= 6;
    func_801F38E0(&g_Task->unk_64, (s16)g_Task->screen_x, 6);
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if ((timer & BYTE_MASK) == 0) {
        g_Task->timer  = 0x20;
        g_Task->unk_06 = 0;
        g_Task->header.mode += 1;
        Area_ClearWorkColumn();
        g_Task->pos.x.fixed = g_Task->unk_64;
        g_Task->pos.y.fixed = g_Task->unk_68;
        g_Task->pos.z.fixed = g_Task->unk_6C;
        spin                = AREA_WORK + 0xC0;
        i                   = 0;
        do {
            Area_InitSpin(spin);
            i += 1;
            spin += 0x2C;
        } while ((i & BYTE_MASK) < 0x10U);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x15));
    }
}
