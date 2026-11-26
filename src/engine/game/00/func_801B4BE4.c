#include "game_00.h"

MATCH u8 func_801B4BE4(u8 mode, u8 code) {
    s16* cells;
    /* FAKE: allocator pin puts the loop counter in s0, as retail. */
    FAKE_REG(s32, count, "s0");
    s32 index;
    s32 want;
    s8  delta;

    delta                         = D_80181B00[mode][0];
    /* FAKE: the scratchpad cell is stored through a volatile halfword view, as retail. */
    *(volatile s16*)&g_ScratchPad = (TASK(Actor)->pos.x.part.integer + ((delta == 1) ? 2 : delta));

    delta      = D_80181B00[mode][1];
    D_1F800002 = (TASK(Actor)->pos.y.part.integer + ((delta == 1) ? 2 : delta));

    index = mode;
    if ((index == 1) || (index == 5)) {
        count = 0;
        cells = (s16*)g_ScratchPad.cells.bytes;
        want  = code;
        do {
            if ((Area_CellGetCode(cells[0], cells[1]) & BYTE_MASK) == want) {
                TASK(Actor)->direction = mode;
                return true;
            }
            ((u16*)cells)[0] = ((u16*)cells)[0] + 1;
            count += 1;
        } while (count < 2);
        return false;
    }
    if ((index == 3) | (index == 7)) {
        count = 0;
        cells = (s16*)g_ScratchPad.cells.bytes;
        want  = code;
        do {
            if ((Area_CellGetCode(cells[0], cells[1]) & BYTE_MASK) == want) {
                TASK(Actor)->direction = mode;
                return true;
            }
            ((u16*)cells)[1] = ((u16*)cells)[1] + 1;
            count += 1;
        } while (count < 2);
    }
    return false;
}
