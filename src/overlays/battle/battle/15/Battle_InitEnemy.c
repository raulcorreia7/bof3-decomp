#define TASK_VOLATILE
#include "battle_15.h"

/* The enemy record the enemy id is read from. */
#define BATTLE_ENEMY_RECORD_SIZE 0x88

/* Arms one enemy battler slot: installs the work pointer in the scratchpad, resets the slot record, copies the
 * enemy id, then queues the enemy's script and bit flag. */
/* func_800ABCE0 */
#ifdef NON_MATCHING
// clang-format off
NON_MATCHING void Battle_InitEnemy(enemy_slot, enemy_index, x, y)
u8 enemy_slot;
u16 enemy_index;
s32 x;
s32 y;
// clang-format on
{
    EnemyBattler* enemy;
    EnemyBattler* first;
    u16           unit_id;
    s32           unit_offset;

    first = &g_BattleEnemyBattlers[enemy_slot];
    TASK_SET(first);
    first->header.flags = 1;
    unit_id             = FIELD(u16, &D_800E405E, (enemy_index & HALF_MASK) * BATTLE_ENEMY_RECORD_SIZE);
    if (unit_id == 717 || unit_id == 737) {
        TASK(EnemyBattler)->header.flags = 0x21;
    }
    TASK(EnemyBattler)->header.mode      = 0;
    enemy                                = TASK(EnemyBattler);
    enemy->unk_04                        = 0;
    enemy->unk_03                        = 0;
    enemy->header.step                   = 0;
    TASK(EnemyBattler)->unk_29           = 4;
    TASK(EnemyBattler)->slot             = enemy_slot + 3;
    TASK(EnemyBattler)->unk_24           = 0;
    enemy                                = TASK(EnemyBattler);
    enemy->unk_5F                        = 0;
    enemy->unk_5E                        = 0;
    enemy->unk_5D                        = 0;
    enemy->unk_14                        = 0;
    enemy->unk_10                        = 0;
    enemy->unk_0C                        = 0;
    enemy->unk_20                        = 0;
    enemy->unk_1C                        = 0;
    enemy->unk_18                        = 0;
    enemy->depth                         = 0;
    enemy->screen_y                      = 0;
    enemy->screen_x                      = 0;
    TASK(EnemyBattler)->unk_5C           = 0;
    TASK(EnemyBattler)->unk_06           = 0;
    TASK(EnemyBattler)->unk_07           = 0;
    TASK(EnemyBattler)->unk_08           = g_Battle.scroll_dir ^ 2;
    TASK(EnemyBattler)->unk_48           = 0;
    TASK(EnemyBattler)->unk_4B           = 0xFF;
    enemy                                = TASK(EnemyBattler);
    enemy->pos.x.fixed                   = x;
    enemy->pos.y.fixed                   = y;
    COORD_INT(TASK(EnemyBattler)->pos.z) = Area_HeightSample(enemy->pos.x.fixed, y);
    TASK(EnemyBattler)->unk_2B           = 0;
    unit_offset                          = (enemy_index & HALF_MASK) * BATTLE_ENEMY_RECORD_SIZE;
    Area_SceneSelectRecord(FIELD(u16, &D_800E405E, unit_offset));
    g_BattleEnemyBattlers[enemy_slot].unk_8A = FIELD(u16, &D_800E405E, unit_offset);
    Battle_LoadEnemyBattler(enemy_slot, enemy_index);
    func_800AD0A8(enemy_slot, enemy_index & HALF_MASK);
    g_BattleEnemyBattlers[enemy_slot].unk_7F = Battle_IsEnemyDefeated(FIELD(u8, &D_800E4050, unit_offset));
    g_Battle.enemy_count += 1;
}
#else
INCLUDE_ASM(Battle_InitEnemy);
#endif
