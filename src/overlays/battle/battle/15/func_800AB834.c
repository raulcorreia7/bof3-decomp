#include "battle_15.h"

/* Cue id table: seven cue ids per battle-event flag bit 7. */
/* Player cue index tables. */
/* Enemy cue rows: one 0x118-byte row per enemy slot, cue index at +0. */

/* Queues the current battler's battle cue id from the event flag row.
 */
MATCH void func_800AB834(void) {
    u8 row;
    u8 battler;

    row     = LOBU(g_Battle.state) >> 7;
    battler = LOBU(g_Battle.active_battler);
    if (BATTLER_IS_PLAYER(battler)) {
        SND_PlayCue(D_800B50EC[LOBU(g_Battle.state) >> 7][D_801C90ED[g_Game.members[battler].chr.equip.weapon * 0x18]]);
    } else {
        /* FAKE: the out-of-range all-ones mask is an identity, but its overflow flag
         * stops fold from distributing (battler - 3) * 0x118, so the index is
         * subtracted before the multiply as in retail; found by trying rewrites; pure-C
         * best 94.55% (slot local), plain spelling 67.27%. */
        SND_PlayCue(D_800B50EC[row][ENEMY_COMBATANT(battler).unk_F1]);
    }
}
