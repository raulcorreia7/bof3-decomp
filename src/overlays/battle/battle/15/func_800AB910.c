#include "battle_15.h"

/* Queues a battler action record from the local or enemy work entry and copies its target offsets and stage id. */
MATCH void func_800AB910(void) {
    PartyMember* work;
    PartyMember* current;
    u8           slot;
    u8           target;
    s32          panel_index;

    slot                               = Battle_AllocEffect(0, 3);
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    target                             = g_Battle.active_battler;
    if ((u32)target < 3) {
        if (((BattleTurn*)D_80146390)->damage_flags.value & 2) {
            g_BattleEffects[slot].unk_07 = 7;
        } else {
            g_BattleEffects[slot].unk_07 = g_Weapons[g_Game.members[target].chr.equip.weapon].sound;
        }
    } else {
        if (((BattleTurn*)D_80146390)->damage_flags.value & 2) {
            g_BattleEffects[slot].unk_07 = 7;
        } else {
            g_BattleEffects[slot].unk_07 = ENEMY_COMBATANT(target).unk_F1;
        }
    }
    work = SELF(PartyMember);
    if ((u32)work->slot < 3) {
        current                        = g_Game.current;
        g_BattleEffects[slot].screen_x = work->screen_x.value + (s8)g_BattlePanelOffsets[current->chr.character_id * 8 + work->facing * 2];
        panel_index                    = work->facing * 2 + current->chr.character_id * 8;
        g_BattleEffects[slot].screen_y = work->screen_y.value + (s8)g_BattlePanelOffsets[panel_index + 1];
        g_BattleEffects[slot].depth    = work->depth;
        g_BattleEffects[slot].unk_08   = g_Game.members[work->slot].facing;
    } else {
        g_BattleEffects[slot].screen_x = work->screen_x.value + g_BattleCurrentEnemy->panel_offset_x;
        g_BattleEffects[slot].screen_y = work->screen_y.value + g_BattleCurrentEnemy->panel_offset_y;
        g_BattleEffects[slot].depth    = work->depth;
        g_BattleEffects[slot].unk_08   = ENEMY_COMBATANT(work->slot).unk_08;
    }
}
