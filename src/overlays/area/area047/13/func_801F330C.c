#include "area047_13.h"

MATCH u8 func_801F330C(void) {
    AreaRingRow* row;
    s32*         pos;
    u8           alive;
    u8           timer;
    u8           shade;
    u8           i;

    alive = 0;
    row   = MEM_PTR(AreaRingRow, AREA_WORK);
    i     = 0;
    shade = 0x20;
    pos   = &D_80145EC4;
    for (; i < AREA_ROW_COUNT; i++) {
        if (row->active != 0) {
            alive = 1;
            switch (row->stage) {
                case 0:
                    row->size       = 0;
                    row->size_delta = 0x10;
                    row->shade      = shade;
                    row->timer      = shade;
                    row->stage += 1;
                    break;
                case 1:
                    row->pos.x.fixed = pos[0];
                    row->pos.y.fixed = pos[1];
                    row->pos.z.fixed = pos[2] + TO_COORD(0x80);
                    row->size += 8;
                    timer      = row->timer - 1;
                    row->timer = timer;
                    row->shade -= 1;
                    if (timer == 0) {
                        row->active = 0;
                    }
                    func_801F2F60(row);
                    break;
            }
        }
        row += 1;
    }
    return alive;
}
