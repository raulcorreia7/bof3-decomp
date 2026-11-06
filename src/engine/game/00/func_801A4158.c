#include "game_00.h"

MATCH void func_801A4158(u8* cursor) {
    u8 flag;
    u8 count;

    count = 0;
    flag  = 0;
    if (!((*(ScriptFunc*)(&D_8018217C + ((*cursor++ & 0x1F) * 4)))(&cursor) & 0xFF)) {
        count++;
        cursor++;
        if ((count & 0xFF) != 0 || cursor[0] != 0xFE) {
        loop_forward:
            if (flag == 0) {
                cursor = func_801A42F0(cursor, (s8*)&flag, &count);
            } else {
                cursor = func_801A4374(cursor, (s8*)&flag, &count);
            }
            if (count != 0) {
                goto loop_forward; /* the stepper reported more steps */
            }
            if (cursor[0] != 0xFE) {
                goto loop_forward; /* the stream did not reach its terminator */
            }
        }
    } else {
        count++;
        cursor++;
        if ((count & 0xFF) != 0 || cursor[0] != 0xFE) {
        loop_backward:
            if (flag != 0) {
                cursor = func_801A42F0(cursor, (s8*)&flag, &count);
            } else {
                cursor = func_801A4374(cursor, (s8*)&flag, &count);
            }
            if (count != 0) {
                goto loop_backward; /* the stepper reported more steps */
            }
            if (cursor[0] != 0xFE) {
                goto loop_backward; /* the stream did not reach its terminator */
            }
        }
    }
    cursor++;
}
