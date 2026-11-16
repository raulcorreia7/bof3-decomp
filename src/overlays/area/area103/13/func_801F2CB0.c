#include "area103_13.h"

MATCH void func_801F2CB0(void) {
    Pos3         pos;
    MATRIX          matrix;
    AreaSpinEffect* row;
    u8              i;

    GFX_AddDitheredDrawMode(1, GetTPage(0, 1, 0x380, 0x100));
    pos.x = g_Task->pos.x.fixed;
    pos.y = g_Task->pos.y.fixed;
    pos.z = g_Task->pos.z.fixed;
    func_801F352C(&pos, g_Task->unk_0A << 2, 0x80, 0);
    Area_SetCameraMatrix(&matrix);
    row = (AreaSpinEffect*)AREA_WORK;
    for (i = 0; i < 3; i++) {
        func_801F2FB8(row);
        row->unk_14 += 4;
        g_Task->unk_0A++;
        if (g_Task->unk_0A > 32) {
            g_Task->unk_0A = 32;
            row->unk_14    = 0x80;
        }
        row->pos.z -= 0x70000;
        row->angle += 64;
        row->scale -= 0x18;
        row++;
    }
    if (!(--g_Task->timer & 0xFF)) {
        g_Task->timer = 32;
        g_Task->header.mode += 1;
    }
}
