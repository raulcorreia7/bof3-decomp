#include "battle_03.h"

/* steps the three local battler rows: each active row's countdown
 * is compared with half the party size, then either its action is queued or
 * the countdown is reduced and its state advanced.
 */
/* func_801D62D8 */
MATCH s32 Battle_StepBattlers(void) {
    s32 count;
    u8  index;
    s32 step;
    u32 flags;
    u16 countdown;

    count = 0;
    index = 0;
    do {
        if (!(Battle_GetActionLock(index) & BYTE_MASK)) {
            flags = g_Game.members[index].u.turn.action_flags.volatile_value;
            if (flags & 0x2) {
                if (flags & 0x20) {
                    /* retail shares this clear block */
                    goto clear;
                }
                countdown = g_Game.members[index].chr.ap;
                if ((s32)countdown < ((s32)(*D_801463B8 + 1) >> 1)) {
                    g_Game.members[index].header.mode = 6;
                    g_Game.members[index].header.step = 4;
                    g_Game.members[index].unk_03      = 4;
                    Battle_SetSlotPending(index);
                    count += 1;
                } else {
                    g_Game.members[index].u.turn.hp_change = 0;
                    g_Game.members[index].u.turn.ap_change = 0;
                    g_Game.members[index].chr.ap -= (*D_801463B8 + 1) >> 1;
                    step                                   = (*D_801463B8 + 1) >> 1;
                    g_Game.members[index].u.turn.ap_change = step;
                    if (step != 0) {
                        g_Game.members[index].header.step         = 5;
                        g_Game.members[index].header.mode         = 6;
                        g_Game.members[index].unk_04              = 0;
                        g_Game.members[index].unk_03              = 0;
                        g_Game.members[index].u.turn.target_flags = 2;
                        Battle_SetSlotPending(index);
                        count += 1;
                    }
                }
            } else {
            clear:
                g_Game.members[index].u.turn.action_flags.volatile_value &= ~COMBATANT_FLAG_ACTION_UNK_5;
            }
        }
        index += 1;
    } while ((index & BYTE_MASK) < 3);
    return D_801463C2 != 0;
}
