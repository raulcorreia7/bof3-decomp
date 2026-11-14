#include "area103_13.h"

MATCH void func_801F2E5C(void) {
    Point3l pos;
    /* FAKE: unused frame, 8 bytes between pos and matrix. */
    FAKE_STACK_PADS(s32, 2);
    MATRIX         matrix;
    AreaEffectRow* row;
    s32            timer;
    u8             i;

    GFX_AddDitheredDrawMode(1, GetTPage(0, 1, 0x380, 0x100));
    pos.x = g_Task->pos.x.fixed;
    pos.y = g_Task->pos.y.fixed;
    pos.z = g_Task->pos.z.fixed;
    func_801F352C(&pos, g_Task->timer << 2, 0x80, 0);
    Area_SetCameraMatrix(&matrix);
    row = (AreaEffectRow*)AREA_WORK;
    for (i = 0; i < 3; i++) {
        func_801F2FB8(row);
        FIELD(u16, row, 0x10) += 0x40;
        FIELD(u16, row, 0x14) -= 8;
        row++;
    }
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (!(timer & 0xFF)) {
        g_Task->header.mode += 1;
    }
}
