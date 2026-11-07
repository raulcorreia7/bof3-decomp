#include "battle_03.h"

/* steps the three local battler rows: each active row's countdown
 * is compared with half the party size, then either its action is queued or
 * the countdown is reduced and its state advanced.
 */
MATCH s32 func_801D62D8(void) {
    s32 count;
    u8  index;
    s32 step;
    u32 flags;
    u16 countdown;

    count = 0;
    index = 0;
    do {
        if (!(func_801D64C4(index) & BYTE_MASK)) {
            flags = g_BattlePartyBattlers[index].turn.action_flags.volatile_value;
            if (flags & 2) {
                if (flags & 0x20) {
                    /* retail shares this clear block */
                    goto clear;
                }
                countdown = g_BattlePartyBattlers[index].chr.ap;
                if ((s32)countdown < ((s32)(*D_801463B8 + 1) >> 1)) {
                    g_BattlePartyBattlers[index].header.mode = 6;
                    g_BattlePartyBattlers[index].header.step = 4;
                    g_BattlePartyBattlers[index].unk_03      = 4;
                    Battle_SetSlotPending(index);
                    count += 1;
                } else {
                    g_BattlePartyBattlers[index].turn.hp_change = 0;
                    g_BattlePartyBattlers[index].turn.ap_change = 0;
                    g_BattlePartyBattlers[index].chr.ap -= (*D_801463B8 + 1) >> 1;
                    step                                        = (*D_801463B8 + 1) >> 1;
                    g_BattlePartyBattlers[index].turn.ap_change = step;
                    if (step != 0) {
                        g_BattlePartyBattlers[index].header.step       = 5;
                        g_BattlePartyBattlers[index].header.mode       = 6;
                        g_BattlePartyBattlers[index].unk_04            = 0;
                        g_BattlePartyBattlers[index].unk_03            = 0;
                        g_BattlePartyBattlers[index].turn.target_flags = 2;
                        Battle_SetSlotPending(index);
                        count += 1;
                    }
                }
            } else {
            clear:
                g_BattlePartyBattlers[index].turn.action_flags.volatile_value &= ~COMBATANT_FLAG_ACTION_UNK_5;
            }
        }
        index += 1;
    } while ((index & BYTE_MASK) < 3);
    return D_801463C2 != 0;
}
