#include "battle_15.h"

typedef struct {
    u32 words[4];
} WorkCopyBlock;

#ifdef NON_MATCHING
NON_MATCHING void Battle_AddEnemy(s32 encounter_index, s32 enemy_slot, s32 enemy_id) {
    volatile u8* source;
    u32*         words_in;
    u32*         words_out;
    u32*         words_end;

    source = func_800AC754(encounter_index & BYTE_MASK);
    if (source != NULL) {
        words_out = (u32*)&g_BattleEnemyBattlers[enemy_slot & BYTE_MASK];
        words_in  = (u32*)source;
        words_end = (u32*)(source + 0x70);
        do {
            *(WorkCopyBlock*)words_out = *(const WorkCopyBlock*)words_in;
            words_in += 4;
            words_out += 4;
        } while (words_in != words_end);
        *words_out = *words_in;
        TASK_SET(&g_BattleEnemyBattlers[enemy_slot & BYTE_MASK]);
        ((EnemyBattler*)g_Task)->header.mode = 0;
        ((EnemyBattler*)g_Task)->unk_04      = 0;
        ((EnemyBattler*)g_Task)->unk_03      = 0;
        ((EnemyBattler*)g_Task)->header.step = 0;
        ((EnemyBattler*)g_Task)->unk_29      = 4;
        ((EnemyBattler*)g_Task)->slot        = enemy_slot + 3;
        ((EnemyBattler*)g_Task)->unk_5F      = 0;
        ((EnemyBattler*)g_Task)->unk_5E      = 0;
        ((EnemyBattler*)g_Task)->unk_5D      = 0;
        ((EnemyBattler*)g_Task)->unk_14      = 0;
        ((EnemyBattler*)g_Task)->unk_10      = 0;
        ((EnemyBattler*)g_Task)->unk_0C      = 0;
        ((EnemyBattler*)g_Task)->unk_20      = 0;
        ((EnemyBattler*)g_Task)->unk_1C      = 0;
        ((EnemyBattler*)g_Task)->unk_18      = 0;
        ((EnemyBattler*)g_Task)->unk_5C      = 0;
        ((EnemyBattler*)g_Task)->unk_06      = 0;
        ((EnemyBattler*)g_Task)->unk_07      = 0;
        ((EnemyBattler*)g_Task)->unk_2B      = 0;
        ((EnemyBattler*)g_Task)->unk_08      = g_Battle.scroll_dir ^ 2;
        ((EnemyBattler*)g_Task)->base.unk_0C = 0;
        Battle_LoadEnemyBattler(enemy_slot & BYTE_MASK, enemy_id & BYTE_MASK);
        func_800AD0A8(enemy_slot & BYTE_MASK, enemy_id & BYTE_MASK);
        g_BattleEnemyBattlers[enemy_slot & BYTE_MASK].unk_7F = 0;
        *source |= 0x40;
        g_Battle.enemy_count += 1;
    }
}
#else
INCLUDE_ASM(Battle_AddEnemy);
#endif
