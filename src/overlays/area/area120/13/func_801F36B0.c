#include "area120_13.h"

MATCH u8 func_801F36B0(void) {
    AreaRow* row;
    u8       scratch[32];
    u16      i;
    u8       handled;

    Camera_SetMatrix(scratch);

    handled = 0;
    row     = MEM_PTR(AreaRow, AREA_WORK);
    i       = 0;
    do {
        if (row->active != 0) {
            switch (row->state) {
                case 0:
                    row->timer = 0x20;
                    row->x     = g_Task->pos.x.fixed;
                    row->z     = g_Task->pos.y.fixed + (row->side != 0 ? TO_COORD_HALF(2) : -TO_COORD_HALF(2));
                    row->y     = g_Task->pos.z.fixed + TO_COORD(384);
                    row->speed = (((rand() & 0x1FF) - 0x180) << 16) / 32;
                    row->state += 1;
                    break;
                case 1:
                    row->x -= 0x2C00;
                    row->z += row->side != 0 ? -0xC00 : 0xC00;
                    row->y += row->speed;
                    if (--row->timer == 0) {
                        row->angle = (rand() & 0x1F) | (row->side != 0 ? ANGLE_90 : -ANGLE_90);
                        row->state += g_Task->unk_06 + 1;
                        row->timer = 0x20;
                    }
                    break;
                case 2:
                    row->x     = (rcos(row->angle) << 4) + g_Task->pos.x.fixed - TO_COORD_HALF(5);
                    row->z     = (rsin(row->angle) << 4) + g_Task->pos.y.fixed;
                    row->angle = (row->angle + (row->side != 0 ? 128 : -128)) & ANGLE_MASK;
                    if (--row->timer == 0) {
                        row->active = 0;
                    }
                    break;
                case 3:
                    row->x     = (rcos(row->angle) << 4) + g_Task->pos.x.fixed - TO_COORD_HALF(5);
                    row->z     = (rsin(row->angle) << 4) + g_Task->pos.y.fixed;
                    row->angle = (row->angle + (row->side != 0 ? 128 : -128)) & ANGLE_MASK;
                    if (g_Task->unk_06 == 2) {
                        row->speed = (rand() & 0x7F) + 128;
                        row->timer = 16;
                        row->state += 1;
                    }
                    break;
                case 4:
                    row->x += (row->speed * rcos(row->angle)) >> 4;
                    row->z += (row->speed * rsin(row->angle)) >> 4;
                    if (--row->timer == 0) {
                        row->active = 0;
                    }
                    break;
            }
            func_801F3468(row);
            handled = 1;
        }
        row++;
        i++;
    } while (i < AREA_ROW_COUNT);
    return handled;
}
