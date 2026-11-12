#include "game_00.h"

/* The etc/game/00 units each declare the shared row base locally; no header owns it yet. */

MATCH void func_801C0AB4(void) {
    u8*  counter;
    u8*  count;
    u8   count_next;
    s32* pos;
    s32  off;
    s32  index;
    u8   flag;

    counter = &D_80146262;
    flag    = 0;
    if (*counter == 0) {
        ((u8*)g_Game.members)[0] &= 0xBF;
        Party_ClearBattlerState(CHAR_INDEX_RYU);
        /* Retail reads the counter before the flag update and stores it after (*counter += 1: 93.48%). */
        count_next = *counter + 1;
        g_Game.members[0].status.field.flags_12C.u8_value &= 0xFD;
        *counter = count_next;
        flag     = 1;
    } else {
        pos = (s32*)&((u8*)g_Game.members)[0x34];
        if (abs(*pos - D_80146264) > 0xFFFF || abs(g_Game.members[0].pos.y.fixed - D_80146268) > 0xFFFF) {
            index = 1;
            if (index < g_Game.party_size) {
                off   = BATTLE_PARTY_STRIDE;
                /* The loop works through its own copy of the counter pointer (direct use: 81.88%). */
                count = counter;
                do {
                    if (((g_GameFlags >> *count) & 0x1) == 0) {
                        ((u8*)g_Game.members)[off] &= 0xBF;
                        D_80145E91[off] = 2;
                        D_80145E92[off] = 2;
                        D_80145E93[off] = 0;
                        D_80145E94[off] = 0;
                        ((u8*)g_Game.members)[off + 0x12C] &= 0xFD;
                        g_AreaWalkFlags &= ~(BIT(*count));
                    }
                    off += BATTLE_PARTY_STRIDE;
                    index += 1;
                    *count += 1;
                } while (index < g_PartySize);
            }
            flag = 1;
        }
    }
    if ((flag != 0) && (D_80146262 == g_Game.party_size)) {
        Area_ClearCellPalette(D_80146266, D_8014626A);
        D_80146260 = 0;
        g_Game.walk_flags &= ~AREA_WALK_ACCEPT_LOCK;
    }
}
