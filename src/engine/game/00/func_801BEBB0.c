#include "game_00.h"

/* The retail passes the roll in $a0 and the callee discards it, so the value
 * is caller context and not part of the shared no-argument prototype. The
 * alias names the same address with the argument spelled out. */

/* Typed view of the party stats table (the 0xA4-byte Character rows). */

MATCH void func_801BEBB0(void) {
    u8* base;
    u8* row;
    s32 slot;
    s32 one;
    s32 offset;
    u8  count;
    u8  random;
    u8  id;

    count = 0;
    base  = &D_80145E9B;
    *base = 0xFF;
    slot  = 0;
    /* FAKE: a local holding 1 places li s4,1 after the slot init; pure-C best 96.32%. */
    FAKE_HOLD(one, 1);
    row    = base + 0x6E;
    offset = 0;
    do {
        while ((random = RANDOM_MASK(0x7F)) >= 101) {
        }
        if (slot < g_Game.party_size) {
            if (g_Characters[g_CharSlot[g_PartyFieldOrder[slot]]].stats.surprise_chance >= random) {
                id = Actor_FindFreeSlot();
                if (id != GAME_NONE) {
                    g_SpawnedActors[id].header.flags = one;
                    g_SpawnedActors[id].type         = 6;
                    g_SpawnedActors[id].unk_06       = one;
                    g_SpawnedActors[id].unk_2E       = *(u16*)(((u8*)&g_Game.members[0].unk_2E) + offset);
                    g_SpawnedActors[id].unk_30       = *(u16*)(((u8*)&g_Game.members[0].unk_2E) + offset + 2);
                    g_SpawnedActors[id].scene_step   = s_BattleStartOffsets[row[0]][0];
                    g_SpawnedActors[id].selection    = s_BattleStartOffsets[row[0]][1];
                    /* FAKE: keeps the selection store ahead of the work-row id store (retail order). */
                    FAKE_BARRIER();
                    D_80145E9B = id;
                }
                count++;
            }
        } else if (random < 51) {
            count++;
        }
        row += BATTLE_PARTY_STRIDE;
        slot++;
        offset += BATTLE_PARTY_STRIDE;
    } while (slot < 5);
    if (count == 5) {
        g_Battle.outcome.surprise = 1;
    } else if (count == 0) {
        g_Battle.outcome.surprise = 2;
    } else {
        g_Battle.outcome.surprise = 0;
    }
}
