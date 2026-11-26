#include "area060_13.h"

MATCH void func_801F2C48(void) {
    g_AreaCameraAngle.vx = -0x340;
    SetGeomOffset(0xA0, 0x90);
    SELF(Actor)->header.step += 1;
}
