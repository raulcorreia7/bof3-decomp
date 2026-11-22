#include "area120_13.h"

MATCH void func_801F3A7C(void) {
    s16 index;

    index                    = TASK(Actor)->pos.x.part.integer;
    TASK(Actor)->pos.x.fixed = D_801F4404[index * 2] << 16;
    TASK(Actor)->pos.y.fixed = D_801F4405[index * 2] << 16;
    TASK(Actor)->vx          = (s32)(D_801EB748 + index * 0x118);
    TASK(Actor)->timer       = 0;
    TASK(Actor)->unk_0A      = 0;
    TASK(Actor)->header.step += 1;
    func_801F3F5C(0x80, 0x40, 1, 0);
}
