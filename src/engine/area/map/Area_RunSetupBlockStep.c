#include "engine/game/00/game_00.h"

/* func_801A42F0 */
/* Runs the next record or control code of an if block: its end code counts down, its else code sets the flag. */
MATCH u8* Area_RunSetupBlockStep(u8* cursor, s8* in_else, u8* ends_left) {
    u8 value;

    value = *cursor;
    if (value >= AREA_SETUP_CONTROL_IF) {
        if (value < AREA_SETUP_CONTROL_BLOCK_ELSE) {
            cursor = Area_RunSetupBranch(cursor);
        } else if (value == AREA_SETUP_CONTROL_BLOCK_END) {
            *ends_left -= 1;
        } else {
            if (value == AREA_SETUP_CONTROL_BLOCK_ELSE) {
                *in_else = 1;
            }
            cursor += 1;
        }
    } else {
        cursor = Area_RunSetupRecord(cursor);
    }
    return cursor;
}
