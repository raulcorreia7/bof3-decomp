#include "engine/game/00/game_00.h"

/* func_801A4640 */
/* Runs the records of one if-chain branch up to its end code and returns the cursor after it. */
MATCH u8* Area_RunSetupChainBody(u8* cursor) {
    u8 keep_going;
    u8 value;

    keep_going = 1;
    while (keep_going) {
        value = *cursor;
        if (value >= AREA_SETUP_CONTROL_IF) {
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
