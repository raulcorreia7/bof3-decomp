#include "game_00.h"

/* func_801BE0C0 */
MATCH s8 Game_GetPartySize(s32 pos_x, s32 pos_y, s32 range_mode) {
    s16 v;
    s32 a1v;
    /* FAKE: loop bound in the retail register. */
    FAKE_REG(s32, limit, "v0");
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);
    s32 count;
    s32 index;
    s32 off;
    u8* ptr;

    v     = func_801BDCF8(pos_x, pos_y);
    index = 0;
    count = g_Game.party_size;
    if (count > 0) {
        off = 0;
        do {
            ptr = (u8*)g_Game.members + off;
            if (((void*)ptr != (void*)g_Task) && (((u8*)g_Game.members)[off] != 0)) {
                a1v = pos_y;
                if ((func_801BDD58(pos_x, a1v, v, range_mode, (Actor*)ptr) & BYTE_MASK) != 0) {
                    return index;
                }
            }
            limit = g_Game.party_size;
            index += 1;
            off += BATTLE_PARTY_STRIDE;
        } while (index < limit);
    }
    return -1;
}
