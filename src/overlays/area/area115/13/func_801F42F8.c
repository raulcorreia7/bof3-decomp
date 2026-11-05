#include "area115_13.h"

MATCH void func_801F42F8(void) {
    u8** slots;
    u8*  scratch;
    u8*  cell;
    u16  value;
    u16  y;

    Area_FindSceneRecord(0x46);

    slots             = SP_PTR(u8*, 0u);
    slots[0x11][0x48] = 0;
    slots             = SP_PTR(u8*, 0u);
    slots[0x11][0x24] = 0;
    slots             = SP_PTR(u8*, 0u);
    slots[0x11][0x29] = 5;

    slots                     = SP_PTR(u8*, 0u);
    scratch                   = slots[0x11];
    FIELD(s32, scratch, 0x0C) = (s16)D_801F5000[FIELD(u8, scratch, 8)].x;
    FIELD(s32, scratch, 0x10) = (s16)D_801F5000[FIELD(u8, scratch, 8)].y;
    FIELD(s32, scratch, 0x34) = D_80145EC4[0];
    FIELD(s32, scratch, 0x38) = D_80145EC8;

    if (FIELD(u8, scratch, 0x06) != 0) {
        FIELD(s16, scratch, 0x36) -= (D_801F5000[FIELD(u8, scratch, 8)].x << 16) >> 29;
        value = FIELD(s16, scratch, 0x3A) - ((D_801F5000[FIELD(u8, scratch, 8)].y << 16) >> 29);
        FIELD(s16, scratch, 0x3A) = value;
        if (FIELD(u8, scratch, 0x06) == 1) {
            if (FIELD(s32, scratch, 0x0C) == 0) {
                FIELD(s16, scratch, 0x36) += 2;
            } else {
                FIELD(s16, scratch, 0x3A) = value + 2;
            }
        } else {
            if (FIELD(s32, scratch, 0x0C) == 0) {
                FIELD(s16, scratch, 0x36) -= 2;
            } else {
                FIELD(s16, scratch, 0x3A) = value - 2;
            }
        }
    }

    slots   = SP_PTR(u8*, 0u);
    scratch = slots[0x11];
    FIELD(s16, scratch, 0x36) -= (D_801F5000[FIELD(u8, scratch, 8)].x << 16) >> 25;
    y                         = FIELD(s16, scratch, 0x3A) - ((D_801F5000[FIELD(u8, scratch, 8)].y << 16) >> 25);
    FIELD(u8, scratch, 0x0B)  = 0;
    slots                     = SP_PTR(u8*, 0u);
    cell                      = slots[0x11];
    FIELD(s16, scratch, 0x3A) = y;
    cell[1] += 1;

    slots = SP_PTR(u8*, 0u);
    Actor_SelectScript(D_801F5010[slots[0x11][8] * 2]);

    slots             = SP_PTR(u8*, 0u);
    slots[0x11][0x2A] = D_801F5011[slots[0x11][8] * 2];
    func_8014D290();
}
