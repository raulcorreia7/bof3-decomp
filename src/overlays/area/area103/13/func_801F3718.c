#include "area103_13.h"

MATCH void func_801F3718(void) {
    Actor* work = SELF(Actor);
    Actor* work2;
    s32    x = work->pos.x.fixed;
    s32    y = work->pos.y.fixed;
    s32    z = work->pos.z.fixed;

    work->timer            = 60;
    work2                  = SELF(Actor);
    /* FAKE: indexed stores across gravity and active_flags preserve the coordinate load order. */
    MEM_PTR(s16, work)[16] = 0;
    MEM_PTR(s32, work)[9]  = AREA_EFFECT_ACTIVE_WORD;
    setVector(work, x, y, z);
    work->unk_1C = z;
    work2->header.mode++;
    SND_SEPlay(D_801F5934[16] == 0 ? 0x208 : 0x209);
}
