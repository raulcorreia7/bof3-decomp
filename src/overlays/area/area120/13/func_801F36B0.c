#include "area120_13.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_801F36B0(void) {
    u8* slot;
    u8* p;
    u8  result;
    u8  timer;
    u16 angle;
    u16 i;
    s32 value;

    u8 scratch[32];

    Area_SetCameraMatrix(scratch);
    result = 0;
    slot   = MEM_PTR(u8, AREA_WORK);
    p      = slot + 1;
    i      = 0;
    do {
        if (slot[0] != 0) {
            if (p[1] < 5) {
                switch (p[1]) {
                    case 0:
                        p[0]                = 32;
                        FIELD(s32, p, 0x0B) = g_Task->pos.x.fixed;
                        FIELD(s32, p, 0x0F) = g_Task->pos.z.fixed + (p[2] != 0 ? TO_COORD_HALF(2) : -TO_COORD_HALF(2));
                        FIELD(s32, p, 0x13) = g_Task->pos.y.fixed + TO_COORD(384);
                        value               = (rand() & 0x1FF) - 0x180;
                        FIELD(s32, p, 0x03) = value / 32;
                        p[1] += 1;
                        break;
                    case 1:
                        FIELD(s32, p, 0x03) -= 0x2C00;
                        FIELD(s32, p, 0x0F) += p[2] != 0 ? -0xC00 : 0xC00;
                        value               = FIELD(s32, p, 0x13) + FIELD(s32, p, 0x03);
                        timer               = --p[0];
                        FIELD(s32, p, 0x13) = value;
                        if (timer == 0) {
                            angle = rand() & 0x1F;
                            if (p[2] != 0) {
                                angle |= 0x0400;
                            } else {
                                angle |= 0xFC00;
                            }
                            FIELD(u16, p, 0x07) = angle;
                            p[0]                = 32;
                            p[1] += g_Task->unk_06;
                        }
                        break;
                    case 2:
                        value               = rcos(FIELD(u16, p, 0x07)) << 4;
                        FIELD(s32, p, 0x0B) = value + g_Task->pos.x.fixed - TO_COORD_HALF(5);
                        value               = rsin(FIELD(u16, p, 0x07)) << 4;
                        FIELD(s32, p, 0x0F) = value + g_Task->pos.z.fixed;
                        FIELD(u16, p, 0x07) = (FIELD(u16, p, 0x07) + (p[2] != 0 ? 128 : -128)) & 0x0FFF;
                        if (g_Task->unk_06 == 2) {
                            FIELD(s32, p, 0x03) = (rand() & 0x7F) + 128;
                            p[0]                = 16;
                        }
                        break;
                    case 3:
                        value               = rcos(FIELD(u16, p, 0x07)) << 4;
                        FIELD(s32, p, 0x0B) = value + g_Task->pos.x.fixed - TO_COORD_HALF(5);
                        value               = rsin(FIELD(u16, p, 0x07)) << 4;
                        FIELD(s32, p, 0x0F) = value + g_Task->pos.z.fixed;
                        FIELD(u16, p, 0x07) = (FIELD(u16, p, 0x07) + (p[2] != 0 ? 128 : -128)) & 0x0FFF;
                        if (g_Task->unk_06 == 2) {
                            FIELD(s32, p, 0x03) = rand() & 0x7F;
                            p[0]                = 16;
                        }
                        break;
                    case 4:
                        value = (FIELD(s32, p, 0x03) * rcos(FIELD(u16, p, 0x07))) >> 4;
                        FIELD(s32, p, 0x0B) += value;
                        value = FIELD(s32, p, 0x03) * rsin(FIELD(u16, p, 0x07));
                        timer = --p[0];
                        FIELD(s32, p, 0x0F) += value >> 4;
                        if (timer == 0) {
                            slot[0] = 0;
                        }
                        break;
                }
            }
            func_801F3468(slot);
            result = 1;
        }
        slot += AREA_ROW_STRIDE;
        p += AREA_ROW_STRIDE;
        i++;
    } while (i < AREA_ROW_COUNT);
    return result;
}
#else
INCLUDE_ASM(func_801F36B0);
#endif
