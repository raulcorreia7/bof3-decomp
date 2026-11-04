#include "game_00.h"

MATCH void Area_RollEncounterThreshold(u32 keep_armed) {
    u8* entry;
    u32 total;
    u8  avail;
    s32 match;
    s32 off;
    u8  cap;
    u32 roll;
    u8  dummy[16];
    s16 limit;
    s32 bound_a;
    s32 bound_b;

    if (g_GameFlags & 0x20) {
        D_80145FB8 = 0;
        return;
    }
    entry = func_801B3C3C(D_80145EC6, D_80145ECA);
    total = s_EncounterStepThresholds[entry[4] * 2];
    if (total == 0) {
        D_80145FB8 = 0;
        return;
    }
    if ((keep_armed & BYTE_MASK) != 0) {
        if (D_80145FB8 == 0)
            keep_armed = 0;
        if ((keep_armed & BYTE_MASK) != 0)
            goto check;
    }
    roll = rand();
    cap  = D_801CD1B9[entry[4] * 2];
    roll &= 0x1F;
    if (cap < roll)
        roll = cap;
    total += roll;
    avail = Party_CountOrder(0);
    limit = avail & BYTE_MASK;
    if (limit > 0) {
        match   = 0;
        bound_a = limit;
        off     = 0;
        do {
            if ((func_801C38F4(D_80145FCC[off], 3, 0x15) & BYTE_MASK) != 0)
                break;
            match++;
            off += BATTLE_PARTY_STRIDE;
        } while (match < bound_a);
        if (match < (avail & BYTE_MASK))
            total *= 2;
    }
    limit = avail & BYTE_MASK;
    if (limit > 0) {
        match   = 0;
        bound_b = limit;
        off     = 0;
        do {
            if ((func_801C38F4(D_80145FCC[off], 3, 0x14) & BYTE_MASK) != 0)
                break;
            match++;
            off += BATTLE_PARTY_STRIDE;
        } while (match < bound_b);
        if (match < (avail & BYTE_MASK))
            total = (total & BYTE_MASK) >> 1;
    }
    goto store;
check:
    if ((u16)D_80145FB8 < (u32)(total & BYTE_MASK))
        return;
store:
    D_80145FB8 = total & BYTE_MASK;
}
