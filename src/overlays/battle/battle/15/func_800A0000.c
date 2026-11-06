#include "battle_15.h"

MATCH void func_800A0000(void) {
    s32 index;
    s32 offset;
    s32 last;
    u8  flags;

    func_800A3F28();
    index  = g_BattleTarget - 3;
    offset = (index & 0xFF) * BATTLE_ENEMY_STRIDE;
    if (D_801EB6CA[offset] != 0) {
        flags = D_801EB6CA[offset + 1];
        if (!(flags & 1)) {
            D_801EB6CA[offset + 1] = flags | 1;
            D_801EB6CA[offset] += 2;
        }
    }
    offset = (index & 0xFF) * BATTLE_ENEMY_STRIDE;
    if (D_801EB6CE[offset] != 0) {
        flags = D_801EB6CE[offset + 1];
        if (!(flags & 1)) {
            D_801EB6CE[offset + 1] = flags | 1;
            D_801EB6CE[offset] += 1;
        }
    }
    /* FAKE: statement boundary keeps the retail register order and schedule. */
    ORDER_LOCK(last = (index & 0xFF) * BATTLE_ENEMY_STRIDE);
    if (D_801EB6CA[last] >= 8U) {
        D_801EB6CA[last] = 7;
    }
    if (D_801EB6CE[last] >= 8U) {
        D_801EB6CE[last] = 7;
    }
}
