#include "battle_15.h"

MATCH s32 func_800A9A84(void) {
    u32 id;

    id = g_BattleAction->unk_02;
    if (D_801CA718[id * 0x14] & ABILITY_TARGET_ALL) {
        return 0;
    }
    if (Battle_SlotIsBlocked(g_BattleTargetSelector)) {
        if (id == 0x4C) {
            return 0;
        }
        if (id == 0x4D) {
            return 0;
        }
        if (id == 0xB4) {
            return 0;
        }
        return id != 0xB5;
    }
    if (id == 0x4C) {
        return 1;
    }
    if (id == 0x4D) {
        return 1;
    }
    if (id != 0xB4) {
        return id == 0xB5;
    }
    return 1;
}
