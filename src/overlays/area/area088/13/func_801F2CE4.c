#include "area088_13.h"

MATCH void func_801F2CE4(void) {
    u8  tick;
    s32 x;

    tick               = g_SpadWork->unk_09;
    g_SpadWork->unk_09 = tick + 1;
    if (tick == 0) {
        SND_PlayCue(0x200);
    }
    func_801F2F28((u8*)AREA_WORK);
    func_801F3258((u8*)AREA_WORK);
    x                   = g_SpadWork->x.fixed + 0x10000;
    g_SpadWork->x.fixed = x;
    if (x == 0x170000) {
        g_SpadWork->unk_09 = 0x20;
        g_SpadWork->unk_01++;
    }
}
