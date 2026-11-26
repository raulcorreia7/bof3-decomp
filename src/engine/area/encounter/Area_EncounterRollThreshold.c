#include "engine/game/00/game_00.h"

MATCH void Area_EncounterRollThreshold(u32 keep_armed) {
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

    if (g_Game.flags & 0x20) {
        D_80145FB8 = 0;
        return;
    }
    entry = Area_EncounterFindZone(g_Game.members[0].pos.x.part.integer, g_Game.members[0].pos.y.part.integer);
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
    avail = Party_CountOrder(PARTY_ORDER_FIELD);
    limit = avail & BYTE_MASK;
    if (limit > 0) {
        match   = 0;
        bound_a = limit;
        off     = 0;
        do {
            if ((Char_CountEquipped((&g_Game.members[0].character_index)[off], EQUIP_GROUP_ACCESSORY, 0x15) & BYTE_MASK) != 0)
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
            if ((Char_CountEquipped((&g_Game.members[0].character_index)[off], EQUIP_GROUP_ACCESSORY, 0x14) & BYTE_MASK) != 0)
                break;
            match++;
            off += BATTLE_PARTY_STRIDE;
        } while (match < bound_b);
        if (match < (avail & BYTE_MASK))
            total = (total & BYTE_MASK) >> 1;
    }
    goto store;
check:
    if (D_80145FB8 < (total & BYTE_MASK))
        return;
store:
    D_80145FB8 = total & BYTE_MASK;
}
