#include "area047_13.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_801F330C(void) {
    AreaRingRow* row;
    s32          alive;
    u8           i;
    u8           timer;

    alive = 0;
    row   = MEM_PTR(AreaRingRow, AREA_WORK);
    i     = 0;
    do {
        if (row->active != 0) {
            alive = 1;
            if (row->stage == 0) {
                row->size       = 0;
                row->size_delta = 0x10;
                row->shade      = 0x20;
                row->timer      = 0x20;
                row->stage += 1;
            } else if (row->stage == 1) {
                row->pos.x.fixed = g_Game.members[0].pos.x.fixed;
                timer            = row->timer - 1;
                row->pos.y.fixed = g_Game.members[0].pos.y.fixed;
                row->pos.z.fixed = g_Game.members[0].pos.z.fixed + 0x800000;
                row->shade -= 1;
                row->timer = timer;
                if (timer == 0) {
                    row->active = 0;
                }
                row->size += 8;
                func_801F2F60(row);
            }
        }
        row += 1;
        i++;
    } while (i < AREA_ROW_COUNT);
    return alive;
}
#else
INCLUDE_ASM(func_801F330C);
#endif
