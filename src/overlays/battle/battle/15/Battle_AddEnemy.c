#include "battle_15.h"

/* Copies an encounter entry's work record into an enemy slot, resets the slot's task state and loads the enemy. */
MATCH void Battle_AddEnemy(s32 encounter_index, s32 enemy_slot, s32 enemy_id) {
    volatile u8*  source;
    EnemyBattler* enemy;

    source = Battle_FindActorEntry(encounter_index);
    if (source != NULL) {
        enemy                    = &g_BattleEnemyBattlers[(u8)enemy_slot];
        *(BattleWorkImage*)enemy = *(BattleWorkImage*)source;
        TASK_SET(&g_BattleEnemyBattlers[(u8)enemy_slot]);
        ((EnemyBattler*)g_Task)->header.mode = 0;
        ((EnemyBattler*)g_Task)->header.step = ((EnemyBattler*)g_Task)->unk_03 = ((EnemyBattler*)g_Task)->unk_04 = 0;
        ((EnemyBattler*)g_Task)->unk_29                                                                          = 4;
        ((EnemyBattler*)g_Task)->slot                                                                            = enemy_slot + 3;
        ((EnemyBattler*)g_Task)->unk_18 = ((EnemyBattler*)g_Task)->unk_1C = ((EnemyBattler*)g_Task)->unk_20 = ((EnemyBattler*)g_Task)->unk_0C = ((EnemyBattler*)g_Task)->unk_10 =
            ((EnemyBattler*)g_Task)->unk_14 = ((EnemyBattler*)g_Task)->unk_5D = ((EnemyBattler*)g_Task)->unk_5E = ((EnemyBattler*)g_Task)->unk_5F = 0;
        ((EnemyBattler*)g_Task)->unk_5C                                                                                                           = 0;
        ((EnemyBattler*)g_Task)->unk_06                                                                                                           = 0;
        ((EnemyBattler*)g_Task)->unk_07                                                                                                           = 0;
        ((EnemyBattler*)g_Task)->unk_2B                                                                                                           = 0;
        ((EnemyBattler*)g_Task)->unk_08                                                                                                           = g_Battle.scroll_dir ^ 2;
        ((EnemyBattler*)g_Task)->unk_48                                                                                                           = 0;
        Battle_LoadEnemyBattler(enemy_slot, enemy_id);
        func_800AD0A8((u8)enemy_slot, (u8)enemy_id);
        g_BattleEnemyBattlers[(u8)enemy_slot].unk_7F = 0;
        *source |= 0x40;
        g_Battle.enemy_count++;
    }
}
