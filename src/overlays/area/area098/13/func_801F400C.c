#include "area098_13.h"

MATCH void func_801F400C(void) {
    u16 level;
    s32 fade;

    level              = g_SpadWork->unk_30;
    g_SpadWork->unk_30 = level + 1;
    if ((s16)(level + 1) >= 0x5B) {
        fade = (level - 0x59) * 4;
        if ((s16)fade >= 0x100) {
            fade = 0xFF;
        }
        func_801F5050(fade);
    }
    g_SpadWork->unk_2E -= 1;
    if ((s16)g_SpadWork->unk_2E == 0) {
        func_80196070();
    }
}
