#include "area103_13.h"

MATCH void func_801F2CB0(void) {
    Pos3            pos;
    MATRIX          matrix;
    AreaSpinEffect* row;
    u8              i;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    pos.x = TASK(Actor)->pos.x.fixed;
    pos.y = TASK(Actor)->pos.y.fixed;
    pos.z = TASK(Actor)->pos.z.fixed;
    func_801F352C(&pos, TASK(Actor)->unk_0A << 2, 0x80, 0);
    Camera_SetMatrix(&matrix);
    row = (AreaSpinEffect*)AREA_WORK;
    for (i = 0; i < 3; i++) {
        func_801F2FB8(row);
        row->unk_14 += 4;
        TASK(Actor)->unk_0A++;
        if (TASK(Actor)->unk_0A > 32) {
            TASK(Actor)->unk_0A = 32;
            row->unk_14         = 0x80;
        }
        row->pos.z -= 0x70000;
        row->angle += 64;
        row->scale -= 0x18;
        row++;
    }
    if (!(--TASK(Actor)->timer & 0xFF)) {
        TASK(Actor)->timer = 32;
        TASK(Actor)->header.mode += 1;
    }
}
