#include "area060_13.h"
#include "area/spad.h"

MATCH void func_801F2C48(void) {
    g_AreaCameraAngle.vx = -0x340;
    SetGeomOffset(0xA0, 0x90);
    g_Task->header.step += 1;
}
