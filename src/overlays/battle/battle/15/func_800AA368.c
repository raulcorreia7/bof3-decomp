#include "battle_15.h"

/* The flag bit the picked slot's local work row carries. */
#define BATTLE_SLOT_SELECTED 8
/* The command the picked slot's local work row carries. */
#define BATTLE_SLOT_COMMAND  0xA
/* The local work row stride. */

/* nonmatching 52.1%: tried the first draft (49.08%); g_BattleTargetSelector hoisted into a local (50.92%); callee
 * result in a temporary local (52.15%); active local removed (47.24%); tagged do-while(0) wall around the mask
 * assignment (51.53%); a register pin on mask (49.08%); a search over 7800 source rewrites, best 4650, no better shape.
 * residual is one register: retail keeps the action mask in s2 while the candidate keeps it in s3, and the branch test
 * differs (retail beqz s3, candidate beqz v0). resume: a source shape that raises the mask local's weighted reference
 * count so it wins s2 over the active-count local, or a longer search over source rewrites. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_800AA368(void) {
    u8            candidates[BATTLE_PARTY_CHARACTERS_COUNT];
    u8            count;
    u8            slot;
    u8            pick;
    u8            mask;
    u8            active;
    s32           allowed;
    BattleAction* action;

    action = g_BattleAction;
    mask   = (D_801CA71C[action->unk_02].mask >> 9) & 1;
    active = g_BattleTargetSelector;
    if (active & 0xC0) {
        count = 0;
        for (slot = 0; slot < BATTLE_PARTY_CHARACTERS_COUNT; slot++) {
            if (mask != 0) {
                allowed = func_800AA5F4(slot);
                if (allowed) {
                    candidates[count] = slot;
                    count++;
                }
            } else {
                allowed = func_800AA7A0(slot);
                if (allowed) {
                    candidates[count] = slot;
                    count++;
                }
            }
        }
    } else {
        if (active < BATTLE_PARTY_CHARACTERS_COUNT) {
            slot = active;
            if (mask != 0) {
                allowed = func_800AA5F4(slot);
                if (allowed) {
                    g_Game.members[slot].turn.damage_flags.volatile_value |= BATTLE_SLOT_SELECTED;
                    D_80145E91[slot * BATTLE_PARTY_STRIDE] = BATTLE_SLOT_COMMAND;
                    return 1;
                }
            } else {
                allowed = func_800AA7A0(slot);
                if (allowed) {
                    g_Game.members[slot].turn.damage_flags.volatile_value |= BATTLE_SLOT_SELECTED;
                    D_80145E91[slot * BATTLE_PARTY_STRIDE] = BATTLE_SLOT_COMMAND;
                    return 1;
                }
            }
        }
        count = 0;
        for (slot = 0; slot < BATTLE_PARTY_CHARACTERS_COUNT; slot++) {
            if (mask != 0) {
                allowed = func_800AA5F4(slot);
                if (allowed) {
                    candidates[count] = slot;
                    count++;
                }
            } else {
                allowed = func_800AA7A0(slot);
                if (allowed) {
                    candidates[count] = slot;
                    count++;
                }
            }
        }
    }
    if (count != 0) {
        pick                                   = candidates[RANDOM_MOD(count)];
        D_80145E91[pick * BATTLE_PARTY_STRIDE] = BATTLE_SLOT_COMMAND;
        g_Game.members[pick].turn.damage_flags.volatile_value |= BATTLE_SLOT_SELECTED;
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM(func_800AA368);
#endif
