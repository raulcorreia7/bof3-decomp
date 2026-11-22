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
        TASK(EnemyBattler)->header.mode = 0;
        TASK(EnemyBattler)->header.step = TASK(EnemyBattler)->unk_03 = TASK(EnemyBattler)->unk_04 = 0;
        TASK(EnemyBattler)->unk_29                                                                = 4;
        TASK(EnemyBattler)->slot                                                                  = enemy_slot + 3;
        TASK(EnemyBattler)->unk_18 = TASK(EnemyBattler)->unk_1C = TASK(EnemyBattler)->unk_20 = TASK(EnemyBattler)->unk_0C = TASK(EnemyBattler)->unk_10 = TASK(EnemyBattler)->unk_14 =
            TASK(EnemyBattler)->unk_5D = TASK(EnemyBattler)->unk_5E = TASK(EnemyBattler)->unk_5F = 0;
        TASK(EnemyBattler)->unk_5C                                                               = 0;
        TASK(EnemyBattler)->unk_06                                                               = 0;
        TASK(EnemyBattler)->unk_07                                                               = 0;
        TASK(EnemyBattler)->unk_2B                                                               = 0;
        TASK(EnemyBattler)->unk_08                                                               = g_Battle.scroll_dir ^ 2;
        TASK(EnemyBattler)->unk_48                                                               = 0;
        Battle_LoadEnemyBattler(enemy_slot, enemy_id);
        func_800AD0A8((u8)enemy_slot, (u8)enemy_id);
        g_BattleEnemyBattlers[(u8)enemy_slot].unk_7F = 0;
        *source |= 0x40;
        g_Battle.enemy_count++;
    }
}
