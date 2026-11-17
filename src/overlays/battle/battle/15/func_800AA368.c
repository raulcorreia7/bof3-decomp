#include "battle_15.h"

/* The flag bit the picked slot's local work row carries. */
#define BATTLE_SLOT_SELECTED 8
/* The command the picked slot's local work row carries. */
#define BATTLE_SLOT_COMMAND  0xA

#ifdef NON_MATCHING
NON_MATCHING s32 func_800AA368(void) {
    u8            candidates[BATTLE_PARTY_CHARACTERS_COUNT];
    u8            count;
    u8            slot;
    u8            pick;
    u8            mask;
    u8            active;
    BattleAction* action;

    action = g_Battle.action;
    mask   = (u8)((D_801CA71C[action->unk_02].mask >> 9) & 1);
    active = g_Battle.target_selector;
    if (active & 0xC0) {
        count = 0;
        for (slot = 0; slot < BATTLE_PARTY_CHARACTERS_COUNT; slot++) {
            if (mask != 0) {
                if ((u8)func_800AA5F4(slot) != 0) {
                    goto accept_multi_candidate;
                }
                goto next_multi_candidate;
            } else {
                if ((u8)func_800AA7A0(slot) == 0) {
                    goto next_multi_candidate;
                }
            }
        accept_multi_candidate:
            candidates[count] = slot;
            count++;
        next_multi_candidate:;
        }
    } else {
        if (active < BATTLE_PARTY_CHARACTERS_COUNT) {
            if (mask != 0) {
                if ((u8)func_800AA5F4(active) != 0) {
                    goto direct_selected;
                }
                count = 0;
                goto collect_fallback;
            }
            if ((u8)func_800AA7A0(active) == 0) {
                count = 0;
                goto collect_fallback;
            }
        direct_selected:
            g_Game.members[g_Battle.target_selector].u.turn.damage_flags.volatile_value |= BATTLE_SLOT_SELECTED;
            D_80145E91[g_Battle.target_selector * BATTLE_PARTY_STRIDE] = BATTLE_SLOT_COMMAND;
            return 1;
        }
        count = 0;
    collect_fallback:
        for (slot = 0; slot < BATTLE_PARTY_CHARACTERS_COUNT; slot++) {
            if (mask != 0) {
                if ((u8)func_800AA5F4(slot) != 0) {
                    goto accept_fallback_candidate;
                }
                goto next_fallback_candidate;
            } else {
                if ((u8)func_800AA7A0(slot) == 0) {
                    goto next_fallback_candidate;
                }
            }
        accept_fallback_candidate:
            candidates[count] = slot;
            count++;
        next_fallback_candidate:;
        }
    }
    if (count != 0) {
        pick                                   = candidates[RANDOM_MOD(count)];
        D_80145E91[pick * BATTLE_PARTY_STRIDE] = BATTLE_SLOT_COMMAND;
        g_Game.members[pick].u.turn.damage_flags.volatile_value |= BATTLE_SLOT_SELECTED;
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM(func_800AA368);
#endif
