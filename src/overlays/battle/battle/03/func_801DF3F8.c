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
        PartyBattler* work = g_Task;

        D_801EB154[work->header.step]();
    }
    {
        PartyBattler* work = g_Task;

        work->unk_5F = 0;
        work->unk_5E = 0;
        work->unk_5D = 0;
    }
    if ((g_BattleMode == 1) && (g_BattleStep >= 2U)) {
        PartyBattler* work;

        if (g_GameState->chr.character_id != g_BattlePartyBattlers[D_801462EE].chr.character_id) {
            offset       = -0x1E;
            work         = g_Task;
            work->unk_5F = offset;
        } else {
            offset       = 0x78;
            work         = g_Task;
            work->unk_5F = offset;
        }
        work->unk_5E = offset;
        work->unk_5D = offset;
    }
    if (g_BattleMode != 5) {
        PartyBattler* battler = g_GameState;

        if (HAS_STATUS(*battler, STATUS_CONFUSED)) {
            if (battler->turn.damage_flags.value & COMBATANT_FLAG_UNK_11) {
                PartyBattler* work = g_Task;
                s32           slot_offset;
                s8            level;

                slot                        = work->slot;
                slot_offset                 = slot * BATTLE_EFFECT_STRIDE;
                level                       = *(D_801EC339 + slot_offset) + 1;
                *(D_801EC339 + slot_offset) = level;
                if (level < 12) {
                } else {
                    goto confuse_flip;
                }
            } else {
                PartyBattler* work = g_Task;
                s32           slot_offset;
                s8            level;

                slot                        = work->slot;
                slot_offset                 = slot * BATTLE_EFFECT_STRIDE;
                level                       = *(D_801EC339 + slot_offset) - 1;
                *(D_801EC339 + slot_offset) = level;
                if (level < -11) {
                confuse_flip:
                    g_GameState->turn.damage_flags.value ^= 0x800;
                }
            }
            actor = g_Task;
            mode  = actor->facing;
            if ((mode == 1) || (mode == 3)) {
                s32 slot_offset = actor->slot * BATTLE_EFFECT_STRIDE;

                actor->pos.x.fixed = (*(s32*)(D_801EC364 + slot_offset) + (*(s8*)(D_801EC339 + slot_offset) << 9));
            } else {
                s32 slot_offset = actor->slot * BATTLE_EFFECT_STRIDE;

                y_pos = *(s32*)(D_801EC368 + slot_offset) + (*(s8*)(D_801EC339 + slot_offset) << 9);
                goto store_coord_y;
            }
        }
    } else if ((g_BattleState & BATTLE_STATE_RELOAD_PARTY) &&
               (g_GameState->turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM)) {
        PartyBattler* work = g_Task;

        s32 x = g_EncounterOriginX;
        s32 y = g_EncounterOriginY;

        work->pos.x.fixed = x;
        work->pos.y.fixed = y;
    } else {
        actor              = g_Task;
        actor->pos.x.fixed = *(s32*)(D_801EC364 + (actor->slot * BATTLE_EFFECT_STRIDE));
        y_pos              = *(s32*)(D_801EC368 + (actor->slot * BATTLE_EFFECT_STRIDE));
    store_coord_y:
        actor->pos.y.fixed = y_pos;
    }
    if (!(g_GameState->turn.damage_flags.value & COMBATANT_FLAG_SKIP_ACTION_STEP)) {
        func_801DEDE4();
    }
}
