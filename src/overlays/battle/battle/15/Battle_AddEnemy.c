#include "battle_15.h"

/* Copies an encounter entry's work record into an enemy slot, resets the slot's task state and loads the enemy. */
MATCH void Battle_AddEnemy(s32 encounter_index, s32 enemy_slot, s32 enemy_id) {
    volatile u8*  source;
    EnemyBattler* enemy;

    source = Battle_FindActorEntry(encounter_index);
    if (source != NULL) {
        enemy                    = &g_BattleEnemyBattlers[(u8)enemy_slot];
        *(BattleWorkImage*)enemy = *(BattleWorkImage*)source;
        SELF_SET(&g_BattleEnemyBattlers[(u8)enemy_slot]);
        SELF(EnemyBattler)->header.mode = 0;
        SELF(EnemyBattler)->header.step = SELF(EnemyBattler)->unk_03 = SELF(EnemyBattler)->unk_04 = 0;
        SELF(EnemyBattler)->unk_29                                                                = 4;
        SELF(EnemyBattler)->slot                                                                  = enemy_slot + 3;
        SELF(EnemyBattler)->unk_18 = SELF(EnemyBattler)->unk_1C = SELF(EnemyBattler)->unk_20 = SELF(EnemyBattler)->unk_0C = SELF(EnemyBattler)->unk_10 = SELF(EnemyBattler)->unk_14 =
            SELF(EnemyBattler)->unk_5D = SELF(EnemyBattler)->unk_5E = SELF(EnemyBattler)->unk_5F = 0;
        SELF(EnemyBattler)->unk_5C                                                               = 0;
        SELF(EnemyBattler)->unk_06                                                               = 0;
        SELF(EnemyBattler)->unk_07                                                               = 0;
        SELF(EnemyBattler)->unk_2B                                                               = 0;
        SELF(EnemyBattler)->unk_08                                                               = g_Battle.scroll_dir ^ 2;
        SELF(EnemyBattler)->unk_48                                                               = 0;
        Battle_LoadEnemyBattler(enemy_slot, enemy_id);
        func_800AD0A8((u8)enemy_slot, (u8)enemy_id);
        g_BattleEnemyBattlers[(u8)enemy_slot].unk_7F = 0;
        *source |= 0x40;
        g_Battle.enemy_count++;
    }
}
