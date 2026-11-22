#include "area091_13.h"

MATCH void func_801F2E6C(void) {
    if (g_Game.members[0].u.field.mode.unsigned_value == 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x00));
        TASK(Actor)->unk_0A       = 0;
        TASK(Actor)->param.unk_0B = 0;
        TASK(Actor)->unk_04 += 1;
    }
}
