#include "battle_15.h"

/* Row field outside this target's include chain: the enemy action id halfword
 * at +0x74 of the 0x118-byte rows indexed by (slot - 3). */

/* Non-volatile alias for the selection-kind byte at 0x80146375. Reading it
 * through the target's volatile g_Battle.action_type makes the compiler materialize
 * the zero-extension of every byte load (`andi rX,rX,0xFF`), which retail does
 * not carry; this distinct, non-volatile symbol keeps the retail `lbu` shape.
 * FAKE: non-volatile alias of g_Battle.action_type (same idiom as Battle_ActionHasElement).
 */

/* Non-volatile alias for the result byte at 0x80146384, used by the slot store
 * only. FAKE: the volatile store keeps retail's `li v0,1` out of the `bnez`
 * delay slot (pure C best 98.10%, scheduling at +0x168); the alias reaches
 * 100%.
 */

/* Enemy row view anchored at the status halfword (+0x82) of the 0x118-byte rows. */

/* answers whether the battler slot may act: with the battle 0x4000
 *           flag set, the slot unblocked and not the current selection, an
 *           enemy slot is checked through its action row and action id. The
 *           result byte g_Battle.target_selector receives the slot, the current selection, or
 *           a 0x40/0x80/0xC0 action code.
 */
MATCH u8 func_800A9304(u8 slot) {
    s32 index;
    u8  action;

    if (!(g_Battle.state & BATTLE_STATE_OVER)) {
        return true;
    }
    if (Battle_SlotIsBlocked(D_801463CB)) {
        return true;
    }
    if (D_801463CB == slot) {
        return true;
    }
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        /* shared exit: the panel copies the current selection */
        goto copy_selection;
    }
    index = slot - BATTLE_PARTY_CHARACTERS_COUNT;
    if (g_BattleEnemyBattlers[index].stats.intellect < 2 || (g_BattleEnemyBattlers[index].status & STATUS_CONFUSED) ||
        (g_BattleEnemyBattlers[index].turn.action_flags.value & COMBATANT_FLAG_CHARGING)) {
        if ((*(u8*)&g_Battle.action_type) == BATTLE_ACTION_ABILITY) {
            action = D_801CA718[ENEMY_COMBATANT(slot).turn.command.id * BATTLE_TYPE_STRIDE];
            if (action & ABILITY_TARGET_ALL) {
                if (!(action & ABILITY_TARGET_BOTH_SIDES)) {
                    if (D_801463CB >= BATTLE_PARTY_CHARACTERS_COUNT) {
                        g_Battle.target_selector = 0x80;
                    } else {
                        g_Battle.target_selector = 0x40;
                    }
                } else {
                    g_Battle.target_selector = 0xC0;
                }
                return true;
            }
            if (!(action & ABILITY_TARGET_SELECT)) {
                (*(u8*)&g_Battle.target_selector) = slot;
                return true;
            }
        }
        /* shared exit: the panel copies the current selection */
        goto copy_selection;
    }
    return true;

copy_selection:
    g_Battle.target_selector = D_801463CB;
    return false;
}
