#include "game_00.h"

/* func_801AF20C */
MATCH s32 Game_ReadCommand(u8* command_stream) {
    s32 command;
    s32 count;
    s32 index;
    s32 extended_command;
    u8* cursor;
    s32 value;

    cursor           = command_stream;
    count            = 0;
    index            = 0;
    extended_command = 0x15;
loop:
    value   = *cursor;
    command = value & BYTE_MASK;
    if (command != 0) {
        count++;
        if (((value - 0x12) < 2U) || (command == extended_command)) {
            cursor += 2;
            index++;
        } else {
            cursor += 1;
        }
        index++;
        if ((index & BYTE_MASK) < 0xCU) {
            goto loop; /* read the next command */
        }
    }
    return count & BYTE_MASK;
}
