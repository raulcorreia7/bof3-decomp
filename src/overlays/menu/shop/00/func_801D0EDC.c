#include "shop_00.h"

/* Globals the shop target's include chain does not reach; the etc/game/00 overlay
 * owns them (src/engine/game/00/game_00.h). */

MATCH void func_801D0EDC(void) {
    s32        index;
    u8*        pond;
    Character* row;
    u16        flags;
    s32        count;
    u32        have;
    u32        need;

    index = D_8014865C;
    if (index < 0) {
        D_80148650 = D_80148698 + 2;
    } else {
        /* FAKE: retail reads g_Actors as u8[]. */
        pond       = ((u8*)g_Actors) + (index * ACTOR_SIZE);
        D_80148650 = *(s32*)(pond + 0x18) + 2;
        D_80148699 = (u8) * (s32*)(pond + 0x1C);
        g_SpadWork = pond;
    }
    count = 0;

    /* retail walks the records from the status halfword: +0x8 is current_hp, +0x10 is max_hp */
    row = &g_Characters[0];
    do {
        need = (u32)row->max_hp >> 2;
        have = row->current_hp;
        if (have < need) {
            flags = row->status | 0x2000;
        } else {
            flags = row->status & 0xDFFF;
        }
        row->status = flags;
        count++;
        row++;
    } while ((u8)count < PARTY_RECORD_COUNT);

    D_80148651 = 0;
    D_80148652 = 0;
    D_80148654 = 6;
    D_8014865A = 0;
    D_8018E7CC = (u8*)&g_GameShopStock[D_80148699];
}
