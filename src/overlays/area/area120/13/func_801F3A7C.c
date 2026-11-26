#include "area120_13.h"

MATCH void func_801F3A7C(void) {
    s16 index;

    index                    = SELF(Actor)->pos.x.part.integer;
    SELF(Actor)->pos.x.fixed = D_801F4404[index * 2] << 16;
    SELF(Actor)->pos.y.fixed = D_801F4405[index * 2] << 16;
    SELF(Actor)->vx          = (s32)(D_801EB748 + index * 0x118);
    SELF(Actor)->timer       = 0;
    SELF(Actor)->unk_0A      = 0;
    SELF(Actor)->header.step += 1;
    func_801F3F5C(0x80, 0x40, 1, 0);
}
