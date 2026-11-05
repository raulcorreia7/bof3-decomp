#include "area108_14.h"

MATCH void func_801F36E8(void) {
    Actor* work;

    g_SpadWork->x.fixed          = 0x240000;
    g_SpadWork->y.fixed          = 0x418000;
    g_SpadWork->z.part.integer   = Area_SampleHeight(g_SpadWork->x.fixed, 0x418000);
    g_SpadWork->unk_18           = 0;
    g_SpadWork->tint.bytes.flags = 0x3D;
    g_SpadWork->unk_01           = 1;
    work                         = g_SpadWork;
    work->tint.bytes.unk_5F      = 0;
    work->tint.bytes.unk_5E      = 0;
    work->tint.bytes.unk_5D      = 0;
}
