#include "battle_03.h"

/* counts the queued slot's step byte down and, on expiry, clears the
 * 0x80 bit of the flag record selected by the slot owner's index before running
 * the queued step.
 */
MATCH void func_801E61F0(void) {
    BattleEffect* work;
    u8            count;
    u8            index;

    work             = D_801EC2E0;
    count            = work->arg.unk_09;
    work->arg.unk_09 = count + 0xFF;
    if (count == 0) {
        index = D_801EC2E0->target.party->slot;
        if (index < 3) {
            g_Game.members[index].u.turn.damage_flags.value &= ~COMBATANT_FLAG_DAMAGE_NUMBER;
        } else {
            ENEMY_COMBATANT(index).turn.damage_flags.value &= ~COMBATANT_FLAG_DAMAGE_NUMBER;
        }
        Effect_Reset();
    }
}
