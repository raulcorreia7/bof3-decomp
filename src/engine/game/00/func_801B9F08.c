#include "game_00.h"

MATCH u8 func_801B9F08(u8 cell0, u8 cell1, s8 cell2) {
    u8  cells[3];
    s32 count;
    u8* pos;
    u8* end;
    s32 index;
    s32 inner;

    cells[0] = cell0;
    cells[1] = cell1;
    cells[2] = cell2;

    count = 0;
    pos   = cells;
    end   = cells + 3;
loop:
    if (*pos == 0) /* a zero cell ends the scan */
        goto done;
    pos++;
    count++;
    if ((s32)pos < (s32)end) /* still inside the three cells */
        goto loop;
done:

    for (index = 0; index < (count & BYTE_MASK); index++)
        cells[index] = g_ScratchPad.cells.bytes[cells[index]];

    if ((count & BYTE_MASK) == 2 && cells[0] == 0x70 && cells[1] == cells[0])
        return 0x70;

    for (index = 0; index < (count & BYTE_MASK); index++) {
        if (cells[index] == 0x70)
            cells[index] = 0xFF;
    }

    for (index = 0; index < (count & BYTE_MASK); index++) {
        if (cells[index] == GAME_NONE)
            return 0x10;
    }

    for (index = 0; index < (count & BYTE_MASK); index++) {
        if (cells[index] != 0xB0)
            break;
    }
    if (index == (count & BYTE_MASK))
        return 0xB0;

    if ((count & 1) != 0) {
        for (index = 0; index < (count & BYTE_MASK); index++) {
            if ((SELF(Actor)->direction & 1) == 0 && cells[index] == 0xA2)
                return 0x10;
            if (cells[index] == 0xA3 || cells[index] == 0xA0)
                return 0x10;
        }
        if ((count & BYTE_MASK) == 1 && (cells[0] & 0xF0) == 0xA0)
            return cells[0];
    } else {
        if ((cells[0] & 0xF0) == 0xA0 || (cells[1] & 0xF0) == 0xA0) {
            if ((cells[0] & BYTE_MASK) == 0xA2 && cells[1] == cells[0]) {
                if ((SELF(Actor)->direction & 1) == 0)
                    return 0x10;
                return 0xA2;
            }
            if (cells[0] == 0xA3 && cells[1] == cells[0])
                return 0xA3;
            if ((cells[0] & 0xF0) == 0xA0 && (cells[1] & 0xF0) == 0xA0)
                return 0xA1;
            return 0x10;
        }
    }

    if ((count & BYTE_MASK) >= 2U) {
        for (index = 0; index < (count & BYTE_MASK) - 1; index++) {
            if ((cells[index] & 0xF0) == 0x20) {
                for (inner = 0; inner < (count & BYTE_MASK); inner++) {
                    if ((cells[inner] & 0xF0) == 0x20 && cells[index] != cells[inner])
                        return 0x20;
                }
                index = (count & BYTE_MASK);
            }
        }
    }
    return 0;
}
