#include "area082_13.h"

MATCH void func_801F3264(void) {
    Point3l pos;
    s16     x;
    s16     y;
    u16     z;

    GFX_AddDitheredDrawMode(1, GetTPage(0, 1, 0x380, 0x100));
    pos.x = g_Task->pos.x.fixed;
    pos.y = g_Task->pos.y.fixed;
    pos.z = g_Task->pos.z.fixed;
    x     = g_Task->unk_64;
    y     = g_Task->unk_68;
    z     = g_Task->unk_6C;
    func_801F2F50(&pos, x, y, z, 0xC0, 0);
}
