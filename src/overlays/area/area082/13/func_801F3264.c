#include "area082_13.h"

MATCH void func_801F3264(void) {
    Pos3 pos;
    s16  x;
    s16  y;
    u16  z;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    pos.x = TASK(Actor)->pos.x.fixed;
    pos.y = TASK(Actor)->pos.y.fixed;
    pos.z = TASK(Actor)->pos.z.fixed;
    x     = TASK(Actor)->angle_x;
    y     = TASK(Actor)->angle_y;
    z     = TASK(Actor)->angle_z;
    func_801F2F50(&pos, x, y, z, 0xC0, 0);
}
