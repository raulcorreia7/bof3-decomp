#include "game_00.h"

MATCH u8* func_801A4640(u8* cursor) {
    u8 keep_going;
    u8 value;

    keep_going = 1;
    while (keep_going) {
        value = *cursor;
        if (value >= 0xF0) {
            switch (value - 0xF0) {
                case 0x0:
                case 0x1:
                case 0x4:
                case 0x9:
                case 0xA:
                    cursor = Area_RunSetupBranch(cursor);
                    break;
                case 0x6:
                    cursor += 2;
                    break;
                case 0x8:
                    keep_going = 0;
                    cursor += 1;
                    break;
                case 0x7:
                    cursor += 1;
                    break;
            }
        } else {
            cursor = Area_RunSetupRecord(cursor);
        }
    }
    return cursor;
}
