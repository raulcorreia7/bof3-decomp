#include "battle_15.h"

typedef struct {
    u32 words[4];
} WorkCopyBlock;

#ifdef NON_MATCHING
NON_MATCHING void Battle_AddEnemy(s32 entry_index, s32 enemy_index, s32 entry_value) {
    volatile u8* source;
    u32*         words_in;
    u32*         words_out;
    u32*         words_end;

    source = func_800AC754(entry_index & BYTE_MASK);
    if (source != NULL) {
        words_out = (u32*)&D_801EB630[enemy_index & BYTE_MASK];
        words_in  = (u32*)source;
        words_end = (u32*)(source + 0x70);
        do {
            *(WorkCopyBlock*)words_out = *(const WorkCopyBlock*)words_in;
            words_in += 4;
            words_out += 4;
        } while (words_in != words_end);
        *words_out = *words_in;
        TASK_SET(&D_801EB630[enemy_index & BYTE_MASK]);
        ((EnemyBattler*)g_Task)->mode              = 0;
        ((EnemyBattler*)g_Task)->unk_04            = 0;
        ((EnemyBattler*)g_Task)->unk_03            = 0;
        ((EnemyBattler*)g_Task)->step              = 0;
        ((EnemyBattler*)g_Task)->unk_29            = 4;
        ((EnemyBattler*)g_Task)->slot              = enemy_index + 3;
        ((EnemyBattler*)g_Task)->unk_5F            = 0;
        ((EnemyBattler*)g_Task)->unk_5E            = 0;
        ((EnemyBattler*)g_Task)->unk_5D            = 0;
        ((EnemyBattler*)g_Task)->unk_14            = 0;
        ((EnemyBattler*)g_Task)->unk_10            = 0;
        ((EnemyBattler*)g_Task)->unk_0C            = 0;
        ((EnemyBattler*)g_Task)->unk_20            = 0;
        ((EnemyBattler*)g_Task)->unk_1C            = 0;
        ((EnemyBattler*)g_Task)->unk_18            = 0;
        ((EnemyBattler*)g_Task)->unk_5C            = 0;
        ((EnemyBattler*)g_Task)->unk_06            = 0;
        ((EnemyBattler*)g_Task)->unk_07            = 0;
        ((EnemyBattler*)g_Task)->unk_2B            = 0;
        ((EnemyBattler*)g_Task)->unk_08            = g_BattleScrollDir ^ 2;
        ((EnemyBattler*)g_Task)->base_stats.unk_0C = 0;
        func_800AC218(enemy_index & BYTE_MASK, entry_value & BYTE_MASK);
        func_800AD0A8(enemy_index & BYTE_MASK, entry_value & BYTE_MASK);
        FIELD(u8, &D_801EB6AF, (enemy_index & BYTE_MASK) * 0x118) = 0;
        *source |= 0x40;
        g_BattleEnemyCount += 1;
    }
}
#else
INCLUDE_ASM(Battle_AddEnemy);
#endif
