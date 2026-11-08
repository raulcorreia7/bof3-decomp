#include "area091_13.h"

MATCH void func_801F2E6C(void) {
    if (g_Game.members[0].u.field.mode_12B.u8_value == 0) {
        SND_PlayCue(0x200);
        g_Task->unk_0A       = 0;
        g_Task->param.unk_0B = 0;
        g_Task->unk_04 += 1;
    }
}
