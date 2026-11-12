#include "game_00.h"

MATCH s32 func_801BA278(u8 cell0, u8 cell1, u8 cell2, u8 cell3, u8 cell4) {
    u8  cells[5];
    s32 count;
    u8* pos;
    u8* end;
    s32 index;
    s32 inner;

    cells[0] = cell0;
    cells[1] = cell1;
    cells[2] = cell2;
    cells[3] = cell3;
    cells[4] = cell4;

    count = 0;
    pos   = cells;
    end   = cells + 5;
loop:
    if (*pos == 0) /* a zero cell ends the scan */
        goto done;
    pos++;
    count++;
    if ((s32)pos < (s32)end) /* still inside the five cells */
        goto loop;
done:

    for (index = 0; index < (count & BYTE_MASK); index++)
        cells[index] = ((u8*)&D_1F800000)[cells[index]];

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

    if ((count & BYTE_MASK) == 2) {
        if (cells[0] == 0xA0)
            return 0x10;
        if (cells[1] == 0xA0)
            return 0x10;
        if (cells[0] == 0xA2 || cells[1] == 0xA2) {
            if ((g_Task->direction_08 & 0x1) == 0)
                return 0x10;
        }
        if (cells[0] == 0xA3) {
            if (cells[1] == cells[0])
                return 0xA3;
            return 0x10;
        }
        if ((cells[0] & 0xF0) == 0xA0 || (cells[1] & 0xF0) == 0xA0) {
            if (cells[0] == cells[1])
                return cells[0];
            return 0x10;
        }
    } else if ((count & BYTE_MASK) == 3) {
        if (cells[0] == 0xA3 || cells[1] == 0xA3 || cells[2] == 0xA3)
            return 0x10;
        if (cells[0] == 0xA2 || cells[1] == 0xA2 || cells[2] == 0xA2) {
            if ((g_Task->direction_08 & 0x1) == 0)
                return 0x10;
        }
        if ((cells[0] & 0xF0) == 0xA0 || (cells[1] & 0xF0) == 0xA0 || (cells[2] & 0xF0) == 0xA0) {
            if (cells[0] == 0xA0)
                cells[0] = 0xA1;
            if (cells[2] == 0xA0)
                cells[2] = 0xA1;
            if (cells[0] == cells[1] && cells[0] == cells[2])
                return cells[0];
            return 0x10;
        }
    } else {
        for (index = 0; index < (count & BYTE_MASK); index++) {
            if ((cells[index] & 0xF0) == 0xA0)
                return 0x10;
        }
    }

    for (index = 0; index < (count & BYTE_MASK); index++) {
        if ((cells[index] & 0xF0) == 0x20) {
            inner = index + 1;
            if (inner >= (count & BYTE_MASK))
                return 0;
            for (; inner < (count & BYTE_MASK); inner++) {
                if ((cells[inner] & 0xF0) == 0x20 && cells[index] != cells[inner])
                    return 0x20;
            }
            return 0;
        }
    }
    return 0;
}
