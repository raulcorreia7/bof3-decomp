#include "game_00.h"

/* func_801BDE14 */
MATCH s8 Actor_FindInRange(s32 pos_x, s32 pos_y, s32 range_mode) {
    s16 kind;
    s32 index;
    s32 off;
    u8* slot;

    kind  = func_801BDCF8(pos_x, pos_y);
    index = 0;
    off   = 0;
    do {
        slot = (u8*)g_Actors + off;
        if ((slot != (u8*)g_Task) && (((u8*)g_Actors)[off] != 0) && ((((u8*)g_Actors + 7)[off] & 0x80) == 0)) {
            if (((func_801BDD58(pos_x, pos_y, kind, range_mode, (Actor*)slot)) & BYTE_MASK) != 0) {
                return index;
            }
        }
        index += 1;
        off += ACTOR_SIZE;
    } while (index < 34);
    return -1;
}
