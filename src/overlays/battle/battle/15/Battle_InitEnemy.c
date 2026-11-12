#include "battle_15.h"

/* The enemy record the enemy_index id is read from. */
#define BATTLE_ENEMY_RECORD_SIZE 0x88

/* Arms one enemy battler enemy_slot: installs the work pointer in the scratchpad, resets the enemy_slot record, copies
 * the enemy_index id, then queues the enemy_index's script and bit flag. */
/* func_800ABCE0 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_InitEnemy(s32 enemy_slot, u16 enemy_index, s32 x, s32 y) {
    EnemyBattler* enemy;
    u16           unit_id;
    s32           unit_offset;

    enemy = &g_BattleEnemyBattlers[enemy_slot & BYTE_MASK];
    TASK_SET(enemy);
    enemy->header.flags = 1;
    unit_offset         = (enemy_index & HALF_MASK) * BATTLE_ENEMY_RECORD_SIZE;
    unit_id             = FIELD(u16, &D_800E405E, unit_offset);
    if (unit_id == 717 || unit_id == 737) {
        ((EnemyBattler*)g_Task)->header.flags = 0x21;
    }
    ((EnemyBattler*)g_Task)->header.mode = 0;
    enemy                                = (EnemyBattler*)g_Task;
    enemy->unk_04                        = 0;
    enemy->unk_03                        = 0;
    enemy->header.step                   = 0;
    ((EnemyBattler*)g_Task)->unk_29      = 4;
    ((EnemyBattler*)g_Task)->slot        = enemy_slot + 3;
    ((EnemyBattler*)g_Task)->unk_24      = 0;
    enemy                                = (EnemyBattler*)g_Task;
    enemy->unk_5F                        = 0;
    enemy->unk_5E                        = 0;
    enemy->unk_5D                        = 0;
    FIELD(s32, enemy, 0x14u)             = 0;
    FIELD(s32, enemy, 0x10u)             = 0;
    enemy->unk_0C                        = 0;
    enemy->unk_20                        = 0;
    FIELD(s32, enemy, 0x1Cu)             = 0;
    FIELD(s32, enemy, 0x18u)             = 0;
    enemy->unk_32                        = 0;
    enemy->unk_30                        = 0;
    enemy->unk_2E                        = 0;
    ((EnemyBattler*)g_Task)->unk_5C      = 0;
    ((EnemyBattler*)g_Task)->unk_06      = 0;
    ((EnemyBattler*)g_Task)->unk_07      = 0;
    ((EnemyBattler*)g_Task)->unk_08      = g_Battle.scroll_dir ^ 2;
    ((EnemyBattler*)g_Task)->unk_48      = 0;
    ((EnemyBattler*)g_Task)->unk_4B      = 0xFF;
    enemy                                = (EnemyBattler*)g_Task;
    enemy->pos.x.fixed                   = x;
    enemy->pos.y.fixed                   = y;
    enemy                                = (EnemyBattler*)g_Task;
    COORD_INT(enemy->pos.z)              = Area_SampleHeight(enemy->pos.x.fixed, y);
    enemy->unk_2B                        = 0;
    Area_SelectSceneRecord(FIELD(u16, &D_800E405E, unit_offset));
    g_BattleEnemyBattlers[enemy_slot & BYTE_MASK].unk_8A = FIELD(u16, &D_800E405E, unit_offset);
    Battle_LoadEnemyBattler(enemy_slot & BYTE_MASK, enemy_index & BYTE_MASK);
    func_800AD0A8(enemy_slot & BYTE_MASK, enemy_index & HALF_MASK);
    g_BattleEnemyBattlers[enemy_slot & BYTE_MASK].unk_7F = Battle_IsEnemyDefeated(FIELD(u8, &D_800E4050, unit_offset));
    g_Battle.enemy_count += 1;
}
#else
INCLUDE_ASM(Battle_InitEnemy);
#endif
