#include "area052_13.h"

/* func_801F31C0 */
MATCH s32 Area_UpdateEffectRows(void) {
    MATRIX         camera;
    AreaEffectRow* row;
    s32            active;
    u8             i;
    u8             life;

    active = 0;
    Area_SetCameraMatrix(&camera);
    row = MEM_PTR(AreaEffectRow, AREA_WORK);
    for (i = 0; i < 16; i++) {
        if (row->active != 0) {
            func_801F2EC8(row);
            life = row->unk_16 - 1;
            row->pos.z.fixed += 0x3000;
            row->unk_14 -= 0x18;
            row->unk_16 = life;
            if (life == 0) {
                row->active = 0;
            }
            active = 1;
        }
        row++;
    }
    return active;
}
