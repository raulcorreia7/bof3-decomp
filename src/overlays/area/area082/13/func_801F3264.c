#include "area082_13.h"

MATCH void func_801F3264(void) {
    Pos3 pos;
    s16  x;
    s16  y;
    u16  z;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    pos.x = SELF(Actor)->pos.x.fixed;
    pos.y = SELF(Actor)->pos.y.fixed;
    pos.z = SELF(Actor)->pos.z.fixed;
    x     = SELF(Actor)->angle_x;
    y     = SELF(Actor)->angle_y;
    z     = SELF(Actor)->angle_z;
    func_801F2F50(&pos, x, y, z, 0xC0, 0);
}
