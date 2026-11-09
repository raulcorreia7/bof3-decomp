#include "area082_13.h"

MATCH void func_801F3398(void) {
    s16 t;

    g_Task->screen_y += 0x80;
    t              = g_Task->unk_32 - 1;
    g_Task->unk_32 = t;
    if (t == 0) {
        Area_ClearWorkColumn();
        g_Task->unk_32 = 300;
        g_Task->header.mode++;
        SND_PlayCue(0x209);
    }
}
