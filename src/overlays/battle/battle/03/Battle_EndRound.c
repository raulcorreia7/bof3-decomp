#include "battle_03.h"

/* Ends the round for every sprite slot whose 0x4000 flag is set and whose state reached 3: clears the slot
 * flags, arms the 0x11/6/5 action bytes and opens the round-result overlay. */
/* func_801D527C */
MATCH bool Battle_EndRound(void) {
    s32 count;
    u8  slot;

    count = 0;
    for (slot = 0; slot < BATTLE_PARTY_CHARACTERS_COUNT; slot++) {
        if (Battle_GetActionLock(slot) == 0) {
            if ((g_Game.members[slot].u.turn.action_flags.value & COMBATANT_FLAG_CHARGING) && (g_Game.members[slot].counter_136 == 3)) {
                count++;
                g_Game.members[slot].header.mode         = 6;
                g_Game.members[slot].header.step         = 5;
                g_Game.members[slot].u.turn.target_flags = 0x11;
                g_Game.members[slot].counter_136         = 0;
                g_Game.members[slot].unk_04              = 0;
                g_Game.members[slot].unk_03              = 0;
                g_Game.members[slot].u.turn.action_flags.value &= ~COMBATANT_FLAG_CHARGING;
                g_Game.members[slot].u.turn.hp_change = g_Game.members[slot].chr.hp;
                Battle_SetSlotPending(slot);
            }
        }
    }
    for (slot = 3; slot < 11; slot++) {
        if (Battle_GetActionLock(slot) == 0) {
            if ((ENEMY_COMBATANT(slot).turn.action_flags.value & COMBATANT_FLAG_CHARGING) && (g_Game.members[slot].counter_136 == 3)) {
                count++;
                ENEMY_COMBATANT(slot).header.mode       = 6;
                ENEMY_COMBATANT(slot).header.step       = 5;
                ENEMY_COMBATANT(slot).turn.target_flags = 0x11;
                ENEMY_COMBATANT(slot).unk_112           = 0;
                ENEMY_COMBATANT(slot).unk_04            = 0;
                ENEMY_COMBATANT(slot).unk_03            = 0;
                ENEMY_COMBATANT(slot).turn.action_flags.value &= ~COMBATANT_FLAG_CHARGING;
                ENEMY_COMBATANT(slot).turn.hp_change = ENEMY_COMBATANT(slot).hp;
                Battle_SetSlotPending(slot);
            }
        }
    }
    if (count & BYTE_MASK) {
        Battle_OpenPanel();
        Battle_QueueEvent(2, 0, 0, 45, Message_GetText(0x2D));
        return true;
    }
    return false;
}
