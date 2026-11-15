#include "battle_15.h"

/* Queues a battler action record from the local or enemy work entry and copies its target offsets and stage id. */
#ifdef NON_MATCHING
NON_MATCHING void func_800AB910(void) {
    PartyMember* work;
    u8*          current;
    u8           slot;
    u8           target;

    slot                               = Battle_AllocEffect(0, 3);
    g_BattleEffects[slot].target.party = BATTLE_WORK;
    target                             = g_Battle.active_battler;
    if ((u32)target < 3) {
        if (FIELD(u32, D_80146390, 0xCu) & 2) {
            g_BattleEffects[slot].unk_07 = 7;
        } else {
            g_BattleEffects[slot].unk_07 = g_Weapons[g_Game.members[target].chr.equip.weapon].sound;
        }
    } else {
        if (FIELD(u32, D_80146390, 0xCu) & 2) {
            g_BattleEffects[slot].unk_07 = 7;
        } else {
            g_BattleEffects[slot].unk_07 = ENEMY_COMBATANT(target).unk_F1;
        }
    }
    work = BATTLE_WORK;
    if ((u32)work->slot < 3) {
        current = g_Game.current;
        g_BattleEffects[slot].unk_2E =
            work->unk_2E.half + (s8)g_BattlePanelOffsets[work->facing * 2 + FIELD(u8, current, 0x79u) * 8];
        g_BattleEffects[slot].unk_30 =
            work->unk_30.half + (s8)(g_BattlePanelOffsets + 1)[work->facing * 2 + FIELD(u8, current, 0x79u) * 8];
        g_BattleEffects[slot].unk_32 = work->depth;
        g_BattleEffects[slot].unk_08 = g_Game.members[work->slot].facing;
    } else {
        g_BattleEffects[slot].unk_2E = work->unk_2E.half + g_BattleCurrentEnemy->panel_offset_x;
        g_BattleEffects[slot].unk_30 = work->unk_30.half + g_BattleCurrentEnemy->panel_offset_y;
        g_BattleEffects[slot].unk_32 = work->depth;
        g_BattleEffects[slot].unk_08 = ENEMY_COMBATANT(work->slot).unk_08;
    }
}
#else
INCLUDE_ASM(func_800AB910);
#endif
