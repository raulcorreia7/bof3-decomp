#include "engine/game/00/game_00.h"

/* func_801A3FC0 */
/* Runs a 0xF0 block when the area test holds. */
MATCH void Area_RunSetupIf(u8* cursor) {
    u8 flag;
    u8 count;

    count = 0;
    flag  = 0;
    if ((*(ScriptOpCallback*)(&g_AreaScriptTests + ((*cursor++ & 0x1F) * 4)))(&cursor) & BYTE_MASK) {
        count++;
        cursor++;
        if ((count & BYTE_MASK) != 0 || cursor[0] != 0xFE) {
        loop_forward:
            if (flag == 0) {
                cursor = Area_RunSetupBlockStep(cursor, (s8*)&flag, &count);
            } else {
                cursor = Area_SkipSetupBlockStep(cursor, (s8*)&flag, &count);
            }
            if (count != 0) {
                goto loop_forward;
            }
            if (cursor[0] != 0xFE) {
                goto loop_forward;
            }
        }
    } else {
        count++;
        cursor++;
        if ((count & BYTE_MASK) != 0 || cursor[0] != 0xFE) {
        loop_backward:
            if (flag != 0) {
                cursor = Area_RunSetupBlockStep(cursor, (s8*)&flag, &count);
            } else {
                cursor = Area_SkipSetupBlockStep(cursor, (s8*)&flag, &count);
            }
            if (count != 0) {
                goto loop_backward;
            }
            if (cursor[0] != 0xFE) {
                goto loop_backward;
            }
        }
    }
    cursor++;
}
