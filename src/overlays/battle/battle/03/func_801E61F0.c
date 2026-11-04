#include "battle_03.h"

/* counts the queued slot's step byte down and, on expiry, clears the
 * 0x80 bit of the flag record selected by the slot owner's index before running
 * the queued step.
 */
MATCH void func_801E61F0(void) {
    BattleEffect* work;
    u8            count;
    u8            index;

    work         = D_801EC2E0;
    count        = work->unk_09;
    work->unk_09 = count + 0xFF;
    if (count == 0) {
        index = D_801EC2E0->target.party->slot;
        if (index < 3) {
            g_BattlePartyBattlers[index].flags_124.value &= ~0x80;
        } else {
            ENEMY_COMBATANT(index).flags_100 &= ~0x80;
        }
        func_801E5988();
    }
}
