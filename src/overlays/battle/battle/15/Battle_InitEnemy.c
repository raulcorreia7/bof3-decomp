#define TASK_VOLATILE
#include "battle_15.h"

/* The enemy record the enemy id is read from. */
#define BATTLE_ENEMY_RECORD_SIZE 0x88

/* Arms one enemy battler slot: installs the work pointer in the scratchpad, resets the slot record, copies the
 * enemy id, then queues the enemy's script and bit flag. */
/* func_800ABCE0 */
MATCH void Battle_InitEnemy(u8 enemy_slot, u16 enemy_index, s32 x, s32 y) {
    EnemyBattler* enemy;
    EnemyBattler* first;
    EnemyBattler* motion;
    EnemyBattler* spawn;
    u16           record_id;
    s32           record_offset;

    first = &g_BattleEnemyBattlers[enemy_slot];
    SELF_SET(first);
    first->header.flags = 1;
    record_id           = ENCOUNTER_ENEMIES[enemy_index & HALF_MASK].scene_record_id;
    if (record_id == 717 || record_id == 737) {
        SELF(EnemyBattler)->header.flags = 0x21;
    }
    SELF(EnemyBattler)->header.mode      = 0;
    enemy                                = SELF(EnemyBattler);
    enemy->unk_04                        = 0;
    enemy->unk_03                        = 0;
    enemy->header.step                   = 0;
    SELF(EnemyBattler)->unk_29           = 4;
    SELF(EnemyBattler)->slot             = enemy_slot + 3;
    SELF(EnemyBattler)->unk_24           = 0;
    motion                               = SELF(EnemyBattler);
    motion->unk_5F                       = 0;
    motion->unk_5E                       = 0;
    motion->unk_5D                       = 0;
    motion->unk_14                       = 0;
    motion->unk_10                       = 0;
    motion->unk_0C                       = 0;
    motion->unk_20                       = 0;
    motion->unk_1C                       = 0;
    motion->unk_18                       = 0;
    motion->depth                        = 0;
    motion->screen_y                     = 0;
    motion->screen_x                     = 0;
    SELF(EnemyBattler)->unk_5C           = 0;
    SELF(EnemyBattler)->unk_06           = 0;
    SELF(EnemyBattler)->unk_07           = 0;
    SELF(EnemyBattler)->unk_08           = g_Battle.scroll_dir ^ 2;
    SELF(EnemyBattler)->unk_48           = 0;
    SELF(EnemyBattler)->unk_4B           = 0xFF;
    spawn                                = SELF(EnemyBattler);
    spawn->pos.x.fixed                   = x;
    spawn->pos.y.fixed                   = y;
    COORD_INT(SELF(EnemyBattler)->pos.z) = Area_HeightSample(spawn->pos.x.fixed, y);
    SELF(EnemyBattler)->unk_2B           = 0;
    record_offset                        = (enemy_index & HALF_MASK) * BATTLE_ENEMY_RECORD_SIZE;
    Area_SceneSelectRecord(ENCOUNTER_ENEMY_AT(record_offset)->scene_record_id);
    g_BattleEnemyBattlers[enemy_slot].unk_8A = ENCOUNTER_ENEMY_AT(record_offset)->scene_record_id;
    Battle_LoadEnemyBattler(enemy_slot, enemy_index);
    func_800AD0A8(enemy_slot, enemy_index & HALF_MASK);
    g_BattleEnemyBattlers[enemy_slot].unk_7F = Battle_IsEnemyDefeated(ENCOUNTER_ENEMY_AT(record_offset)->enemy_id.byte.type);
    g_Battle.enemy_count += 1;
}
