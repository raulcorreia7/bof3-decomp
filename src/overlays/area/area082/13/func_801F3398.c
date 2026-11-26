#include "area082_13.h"

MATCH void func_801F3398(void) {
    s16 t;

    SELF(Actor)->screen_y += 0x80;
    t                   = SELF(Actor)->unk_32 - 1;
    SELF(Actor)->unk_32 = t;
    if (t == 0) {
        Area_ClearWorkColumn();
        SELF(Actor)->unk_32 = 300;
        SELF(Actor)->header.mode++;
        SND_SEPlay(0x209);
    }
}
