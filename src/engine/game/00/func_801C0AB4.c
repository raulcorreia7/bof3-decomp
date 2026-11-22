#include "game_00.h"

MATCH void func_801C0AB4(void) {
    u8*  counter;
    u8*  count;
    u8   count_next;
    s32* pos;
    s32  index;
    u8   flag;

    counter = &D_80146262;
    flag    = 0;
    if (*counter == 0) {
        g_Game.members[0].header.flags &= 0xBF;
        Party_BattlersClearState(CHAR_INDEX_RYU);
        count_next = *counter + 1;
        g_Game.members[0].status.field.flags.unsigned_value &= 0xFD;
        *counter = count_next;
        flag     = 1;
    } else {
        pos = &g_Game.members[0].pos.x.fixed;
        if (abs(*pos - D_80146264) > 0xFFFF || abs(g_Game.members[0].pos.y.fixed - D_80146268) > 0xFFFF) {
            index = 1;
            if (index < g_Game.party_size) {
                count = counter;
                do {
                    if (((g_GameFlags >> *count) & 0x1) == 0) {
                        g_Game.members[index].header.flags &= 0xBF;
                        g_Game.members[index].header.mode = 2;
                        g_Game.members[index].header.step = 2;
                        g_Game.members[index].unk_03      = 0;
                        g_Game.members[index].unk_04      = 0;
                        g_Game.members[index].status.field.flags.unsigned_value &= 0xFD;
                        g_AreaWalkFlags &= ~(BIT(*count));
                    }
                    index += 1;
                    *count += 1;
                } while (index < g_PartySize);
            }
            flag = 1;
        }
    }
    if ((flag != 0) && (D_80146262 == g_Game.party_size)) {
        Area_CellClearPalette(D_80146266, D_8014626A);
        D_80146260 = 0;
        g_Game.walk_flags &= ~AREA_WALK_ACCEPT_LOCK;
    }
}
