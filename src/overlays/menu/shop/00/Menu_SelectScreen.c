#include "shop_00.h"

/* Globals the shop target's include chain does not reach; the etc/game/00 overlay
 * owns them (src/engine/game/00/game_00.h). */

/* func_801D0EDC */
MATCH void Menu_SelectScreen(void) {
    s32        index;
    u8*        pond;
    Character* character;
    u16        flags;
    s32        count;
    u32        have;
    u32        need;

    index = D_8014865C;
    if (index < 0) {
        g_MenuStep.step = D_80148698 + 2;
    } else {
        /* FAKE: retail reads g_Actors as u8[]. */
        pond            = ((u8*)g_Actors) + (index * ACTOR_SIZE);
        g_MenuStep.step = *(s32*)(pond + 0x18) + 2;
        D_80148699      = *(s32*)(pond + 0x1C);
        SELF_SET(pond);
    }
    count = 0;

    /* retail walks the records from the status halfword: +0x8 is current_hp, +0x10 is max_hp */
    character = &g_Characters[0];
    do {
        need = character->stats.max_hp >> 2;
        have = character->hp;
        if (have < need) {
            flags = character->status | STATUS_LOW_HP;
        } else {
            flags = character->status & ~STATUS_LOW_HP;
        }
        character->status = flags;
        count++;
        character++;
    } while ((u8)count < CHAR_INDEX_COUNT);

    g_MenuStep.sub_step = 0;
    g_MenuStep.state    = 0;
    D_80148654          = 6;
    D_8014865A          = 0;
    D_8018E7CC          = (u8*)&g_GameShopStock[D_80148699];
}
