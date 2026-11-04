#include "battle_03.h"

/* D_801EC339, D_801EC364 and D_801EC368 are one-field views of the queued-slot
 * record at g_BattleEffects (stride 0x78): the signed level at +0x09, the position x
 * at +0x34 and the position y at +0x38. Retail addresses each view through its
 * own base symbol, so the three views keep three names. */

/* updates the active battler's animation: runs its state handler, eases the hurt blend bytes and recomputes
 * the sprite vector from the pose tables.
 */
MATCH void func_801DF3F8(void) {
    PartyBattler* actor;
    s32           y_pos;
    s8            offset;
    u8            mode;
    u8            slot;

    {
        PartyBattler* work = g_SpadWork;

        D_801EB154[work->unk_02]();
    }
    {
        PartyBattler* work = g_SpadWork;

        work->unk_5F = 0;
        work->unk_5E = 0;
        work->unk_5D = 0;
    }
    if ((g_BattleMode == 1) && ((u8)g_BattleStep >= 2U)) {
        PartyBattler* work;

        if (g_GameState->stats.character_id != D_80145F09[D_801462EE][0]) {
            offset       = -0x1E;
            work         = g_SpadWork;
            work->unk_5F = offset;
        } else {
            offset       = 0x78;
            work         = g_SpadWork;
            work->unk_5F = offset;
        }
        work->unk_5E = offset;
        work->unk_5D = offset;
    }
    if (g_BattleMode != 5) {
        PartyBattler* battler = g_GameState;

        if (HAS_STATUS(*battler, STATUS_CONFUSED)) {
            if (battler->flags_124.value & 0x800) {
                PartyBattler* work = g_SpadWork;
                s32           slot_offset;
                s8            level;

                slot                        = work->slot;
                slot_offset                 = slot * BATTLE_EFFECT_STRIDE;
                level                       = *(D_801EC339 + slot_offset) + 1;
                *(D_801EC339 + slot_offset) = level;
                if (level < 12) {
                } else {
                    goto block_12; /* shared animation vector join */
                }
            } else {
                PartyBattler* work = g_SpadWork;
                s32           slot_offset;
                s8            level;

                slot                        = work->slot;
                slot_offset                 = slot * BATTLE_EFFECT_STRIDE;
                level                       = *(D_801EC339 + slot_offset) - 1;
                *(D_801EC339 + slot_offset) = level;
                if (level < -11) {
                block_12:
                    g_GameState->flags_124.value ^= 0x800;
                }
            }
            actor = g_SpadWork;
            mode  = actor->word_08.byte.facing_08;
            if ((mode == 1) || (mode == 3)) {
                s32 slot_offset = actor->slot * BATTLE_EFFECT_STRIDE;

                actor->coord_x_34.raw =
                    (s32)(*(s32*)(D_801EC364 + slot_offset) + (*(s8*)(D_801EC339 + slot_offset) << 9));
            } else {
                s32 slot_offset = actor->slot * BATTLE_EFFECT_STRIDE;

                y_pos = *(s32*)(D_801EC368 + slot_offset) + (*(s8*)(D_801EC339 + slot_offset) << 9);
                goto block_21; /* shared animation vector join */
            }
        }
    } else if ((g_BattleState & BATTLE_STATE_RELOAD_PARTY) && (g_GameState->flags_128.value & 2)) {
        PartyBattler* work = g_SpadWork;

        work->coord_x_34.raw = (s32)D_80143F24;
        work->coord_y_38.raw = (s32)D_80143F28;
    } else {
        actor                 = g_SpadWork;
        actor->coord_x_34.raw = (s32) * (s32*)(D_801EC364 + (actor->slot * BATTLE_EFFECT_STRIDE));
        y_pos                 = *(s32*)(D_801EC368 + (actor->slot * BATTLE_EFFECT_STRIDE));
    block_21:
        actor->coord_y_38.raw = y_pos;
    }
    if (!(g_GameState->flags_124.value & COMBATANT_FLAG_SKIP_ACTION_STEP)) {
        func_801DEDE4();
    }
}
