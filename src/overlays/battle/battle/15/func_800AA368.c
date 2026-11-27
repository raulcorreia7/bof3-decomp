#include "battle_15.h"

/* The header mode byte the picked slot's work record carries. */
#define BATTLE_PICKED_SLOT_MODE 0xA

MATCH s32 func_800AA368(void) {
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
    /* FAKE: keeps the count clear at the head of the branch (it fills the branch delay slot, not the load delay). */
    FAKE_BARRIER();
    count = 0;
    if (active & 0xC0) {
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
                goto collect_fallback;
            }
            if ((u8)func_800AA7A0(active) == 0) {
                goto collect_fallback;
            }
        direct_selected:
            g_Game.members[g_Battle.target_selector].u.turn.damage_flags.volatile_value |= BATTLER_DAMAGE_UNK_3;
            g_Game.members[g_Battle.target_selector].header.mode = BATTLE_PICKED_SLOT_MODE;
            return 1;
        }
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
    if (count == 0) {
        return 0;
    }
    pick                             = candidates[RANDOM_MOD(count)];
    g_Game.members[pick].header.mode = BATTLE_PICKED_SLOT_MODE;
    g_Game.members[pick].u.turn.damage_flags.volatile_value |= BATTLER_DAMAGE_UNK_3;
    return 1;
}
