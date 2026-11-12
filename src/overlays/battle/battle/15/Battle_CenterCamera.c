#include "battle_15.h"

/* Averages the x, y and vertical span of the living battlers (the enemies in
 * the 0x40 mode, otherwise the three party slots) into the camera work
 * record. */
/* func_800AFD9C */
MATCH void Battle_CenterCamera(void) {
    s32          i;
    s32          count;
    s32          sum_x;
    s32          sum_y;
    s32          sum_span;
    u8           flags;
    PartyMember* work;

    count    = 0;
    sum_span = 0;
    sum_y    = 0;
    sum_x    = 0;
    flags    = g_Battle.target_selector;
    if ((flags & 0xC0) != 0xC0) {
        if (flags & 0x40) {
            for (i = 0; i < ENCOUNTER_ENEMY_COUNT; i++) {
                if (Battle_SlotIsBlocked((i + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK) == 0) {
                    count++;
                    sum_x += g_BattleEnemyBattlers[i].pos.x.fixed >> 9;
                    sum_y += g_BattleEnemyBattlers[i].pos.y.fixed >> 9;
                    sum_span += COORD_INT(g_BattleEnemyBattlers[i].pos.z);
                }
            }
        } else {
            for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
                if (Battle_SlotIsBlocked(i & BYTE_MASK) == 0) {
                    count++;
                    sum_x += g_Game.members[i].pos.x.fixed >> 9;
                    sum_y += g_Game.members[i].pos.y.fixed >> 9;
                    sum_span += COORD_INT(g_Game.members[i].pos.z);
                }
            }
        }
        work                   = BATTLE_WORK;
        work->pos.x.fixed      = (sum_x / count) << 9;
        work->pos.y.fixed      = (sum_y / count) << 9;
        COORD_INT(work->pos.z) = sum_span / count;
    }
}
