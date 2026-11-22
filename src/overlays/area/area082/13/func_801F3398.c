#include "area082_13.h"

MATCH void func_801F3398(void) {
    s16 t;

    TASK(Actor)->screen_y += 0x80;
    t                   = TASK(Actor)->unk_32 - 1;
    TASK(Actor)->unk_32 = t;
    if (t == 0) {
        Area_ClearWorkColumn();
        TASK(Actor)->unk_32 = 300;
        TASK(Actor)->header.mode++;
        SND_SEPlay(0x209);
    }
}
