#include "area111_13.h"

/* Walks the cell grid from the actor along its facing while the cells are empty and sets the script step count from the cells crossed. */
MATCH void func_801F3460(void) {
    s16 x;
    s16 y;
    s8  offset;
    s32 facing;
    u8  value;

    offset = 0;
    x      = (TASK(Actor)->pos.x.part.integer - 11) >> 1;
    y      = (TASK(Actor)->pos.y.part.integer - 177) >> 1;
    func_801F4604(x, y, 0x10);
    facing = TASK(Actor)->direction & 7;
    for (;;) {
        if ((u16)(x += D_80181B00[facing][0]) >= 7) {
            goto done;
        }
        if ((u16)(y += D_80181B00[facing][1]) >= 7) {
            goto done;
        }
        if (x & 1) {
            value = D_801F5C18[y][x / 2] & 0xF;
        } else {
            value = D_801F5C18[y][x / 2] >> 4;
        }
        if (value != 0) {
            goto done;
        }
        offset += 4;
    }
done:
    if (offset != 0) {
        g_ScriptState->steps = offset + 1;
    }
    TASK(Actor)->vz = 0;
    func_801F4604(x, y, 0);
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
}
