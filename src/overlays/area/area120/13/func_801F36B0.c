#include "area120_13.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_801F36B0(void) {
    AreaRow* row;
    u8       result;
    u8       timer;
    u16      angle;
    u16      i;
    s32      value;

    u8 scratch[32];

    Area_SetCameraMatrix(scratch);
    result = 0;
    row    = MEM_PTR(AreaRow, AREA_WORK);
    i      = 0;
    do {
        if (row->active != 0) {
            if (row->state < 5) {
                switch (row->state) {
                    case 0:
                        row->timer = 32;
                        row->x     = g_Task->pos.x.fixed;
                        row->z     = g_Task->pos.z.fixed + (row->side != 0 ? TO_COORD_HALF(2) : -TO_COORD_HALF(2));
                        row->y     = g_Task->pos.y.fixed + TO_COORD(384);
                        value      = (rand() & 0x1FF) - 0x180;
                        row->speed = value / 32;
                        row->state += 1;
                        break;
                    case 1:
                        row->speed -= 0x2C00;
                        row->z += row->side != 0 ? -0xC00 : 0xC00;
                        value  = row->y + row->speed;
                        timer  = --row->timer;
                        row->y = value;
                        if (timer == 0) {
                            angle = rand() & 0x1F;
                            if (row->side != 0) {
                                angle |= ANGLE_90;
                            } else {
                                angle |= (u16)-ANGLE_90;
                            }
                            row->angle = angle;
                            row->timer = 32;
                            row->state += g_Task->unk_06;
                        }
                        break;
                    case 2:
                        value      = rcos(row->angle) << 4;
                        row->x     = value + g_Task->pos.x.fixed - TO_COORD_HALF(5);
                        value      = rsin(row->angle) << 4;
                        row->z     = value + g_Task->pos.z.fixed;
                        row->angle = (row->angle + (row->side != 0 ? 128 : -128)) & ANGLE_MASK;
                        if (g_Task->unk_06 == 2) {
                            row->speed = (rand() & 0x7F) + 128;
                            row->timer = 16;
                        }
                        break;
                    case 3:
                        value      = rcos(row->angle) << 4;
                        row->x     = value + g_Task->pos.x.fixed - TO_COORD_HALF(5);
                        value      = rsin(row->angle) << 4;
                        row->z     = value + g_Task->pos.z.fixed;
                        row->angle = (row->angle + (row->side != 0 ? 128 : -128)) & ANGLE_MASK;
                        if (g_Task->unk_06 == 2) {
                            row->speed = rand() & 0x7F;
                            row->timer = 16;
                        }
                        break;
                    case 4:
                        value = (row->speed * rcos(row->angle)) >> 4;
                        row->x += value;
                        value = row->speed * rsin(row->angle);
                        timer = --row->timer;
                        row->z += value >> 4;
                        if (timer == 0) {
                            row->active = 0;
                        }
                        break;
                }
            }
            func_801F3468(row);
            result = 1;
        }
        row++;
        i++;
    } while (i < AREA_ROW_COUNT);
    return result;
}
#else
INCLUDE_ASM(func_801F36B0);
#endif
