#include "battle_03.h"

/* updates the active battler's animation: runs its state handler, eases the hurt blend bytes and recomputes
 * the sprite vector from the pose tables.
 */
MATCH void func_801DF3F8(void) {
    PartyMember* actor;
    s32          y_pos;
    s8           offset;
    u8           mode;
    u8           slot;

    {
        PartyMember* work = SELF(PartyMember);

        D_801EB154[work->header.step]();
    }
    {
        PartyMember* work = SELF(PartyMember);

        work->unk_5F = 0;
        work->unk_5E = 0;
        work->unk_5D = 0;
    }
    if ((g_Battle.phase.mode == BATTLE_MODE_COMMANDS) && (g_Battle.phase.step >= 2U)) {
        PartyMember* work;

        if (g_Game.current->chr.character_id != g_Game.members[g_Battle.unk_0E].chr.character_id) {
            offset       = -0x1E;
            work         = SELF(PartyMember);
            work->unk_5F = offset;
        } else {
            offset       = 0x78;
            work         = SELF(PartyMember);
            work->unk_5F = offset;
        }
        work->unk_5E = offset;
        work->unk_5D = offset;
    }
    if (g_Battle.phase.mode != BATTLE_MODE_RESULT) {
        PartyMember* battler = g_Game.current;

        if (HAS_STATUS(*battler, STATUS_CONFUSED)) {
            if (battler->u.turn.damage_flags.value & BATTLER_DAMAGE_UNK_11) {
                PartyMember* work = SELF(PartyMember);
                s8           level;

                slot                           = work->slot;
                level                          = g_BattleEffects[slot].arg.sway + 1;
                g_BattleEffects[slot].arg.sway = level;
                if (level < 12) {
                } else {
                    goto confuse_flip;
                }
            } else {
                PartyMember* work = SELF(PartyMember);
                s8           level;

                slot                           = work->slot;
                level                          = g_BattleEffects[slot].arg.sway - 1;
                g_BattleEffects[slot].arg.sway = level;
                if (level < -11) {
                confuse_flip:
                    g_Game.current->u.turn.damage_flags.value ^= 0x800;
                }
            }
            actor = SELF(PartyMember);
            mode  = actor->facing;
            if ((mode == 1) || (mode == 3)) {
                actor->pos.x.fixed = g_BattleEffects[actor->slot].pos.x.fixed + (g_BattleEffects[actor->slot].arg.sway << 9);
            } else {
                y_pos = g_BattleEffects[actor->slot].pos.y.fixed + (g_BattleEffects[actor->slot].arg.sway << 9);
                goto store_coord_y;
            }
        }
    } else if ((g_Battle.flags & BATTLE_STATE_RELOAD_PARTY) && (g_Game.current->u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM)) {
        PartyMember* work = SELF(PartyMember);

        s32 x = g_AreaEncounterPlacement.origin.x.fixed;
        s32 y = g_AreaEncounterPlacement.origin.y.fixed;

        work->pos.x.fixed = x;
        work->pos.y.fixed = y;
    } else {
        actor              = SELF(PartyMember);
        actor->pos.x.fixed = g_BattleEffects[actor->slot].pos.x.fixed;
        y_pos              = g_BattleEffects[actor->slot].pos.y.fixed;
    store_coord_y:
        actor->pos.y.fixed = y_pos;
    }
    if (!(g_Game.current->u.turn.damage_flags.value & BATTLER_DAMAGE_SKIP_ACTION_STEP)) {
        func_801DEDE4();
    }
}
