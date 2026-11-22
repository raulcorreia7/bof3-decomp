#include "area103_13.h"

MATCH void func_801F2E5C(void) {
    Pos3 pos;
    /* FAKE: unused frame, 8 bytes between pos and matrix. */
    FAKE_STACK_PADS(s32, 2);
    MATRIX          matrix;
    AreaSpinEffect* row;
    s32             timer;
    u8              i;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    pos.x = g_Task->pos.x.fixed;
    pos.y = g_Task->pos.y.fixed;
    pos.z = g_Task->pos.z.fixed;
    func_801F352C(&pos, g_Task->timer << 2, 0x80, 0);
    Camera_SetMatrix(&matrix);
    row = (AreaSpinEffect*)AREA_WORK;
    for (i = 0; i < 3; i++) {
        func_801F2FB8(row);
        FIELD(u16, row, 0x10) += 0x40;
        FIELD(u16, row, 0x14) -= 8;
        row++;
    }
    ACTOR_COUNT_DOWN(TASK(Actor), timer, timer);
    if (!(timer & 0xFF)) {
        g_Task->header.mode += 1;
    }
}
