#include "battle_15.h"

/* The enemy record the unit id is read from. */
#define BATTLE_ENEMY_RECORD_SIZE 0x88

/* Arms one enemy battler slot: installs the work pointer in the scratchpad, resets the slot record, copies
 * the unit id, then queues the unit's script and bit flag. */
/* nonmatching 61.0%: tried the first draft (59.75%); u16 unit parameter (61.01%); u8/u16/s32/u32 parameter-type sweep
 * (best 61.01%); caching the unit offset in a local (56.10%); moving the y store after the call (58.39%); a register
 * pin on slot and unit (61.01%, no change: gcc 2.7.2 ignores the constraint). the work record's byte cells are read
 * through the shared record's members now; the word cells at +0x0C..+0x20 and the halfwords at +0x2E..+0x32 keep the
 * byte-pointer form, because the member form lets gcc 2.7.2 fold the zero stores and drops an instruction (60.38
 * percent, 628 bytes against the retail's 636). residual is the callee-saved set: retail saves s2,s0,ra,s3,s1 with
 * slot in s2 and unit in s0; the candidate saves s1,s0,s3,ra,s2. resume: a source shape that homes slot in s2 and unit
 * in s0, or a register pin that this compiler honours on a parameter. */
#ifdef NON_MATCHING
NON_MATCHING void func_800ABCE0(s32 slot, u16 unit, s32 x, s32 y) {
    EnemyBattler* enemy;
    u16           unit_id;
    s32           unit_offset;
    s32           enemy_offset;

    enemy = &D_801EB630[slot & BYTE_MASK];
    TASK_SET(enemy);
    enemy->flags = 1;
    unit_offset  = (unit & HALF_MASK) * BATTLE_ENEMY_RECORD_SIZE;
    unit_id      = FIELD(u16, &D_800E405E, unit_offset);
    if (unit_id == 717 || unit_id == 737) {
        ((EnemyBattler*)g_Task)->flags = 0x21;
    }
    ((EnemyBattler*)g_Task)->mode   = 0;
    enemy                           = (EnemyBattler*)g_Task;
    enemy->unk_04                   = 0;
    enemy->unk_03                   = 0;
    enemy->step                     = 0;
    ((EnemyBattler*)g_Task)->unk_29 = 4;
    ((EnemyBattler*)g_Task)->slot   = slot + 3;
    ((EnemyBattler*)g_Task)->unk_24 = 0;
    enemy                           = (EnemyBattler*)g_Task;
    enemy->unk_5F                   = 0;
    enemy->unk_5E                   = 0;
    enemy->unk_5D                   = 0;
    FIELD(s32, enemy, 0x14u)        = 0;
    FIELD(s32, enemy, 0x10u)        = 0;
    enemy->unk_0C                   = 0;
    enemy->unk_20                   = 0;
    FIELD(s32, enemy, 0x1Cu)        = 0;
    FIELD(s32, enemy, 0x18u)        = 0;
    enemy->unk_32                   = 0;
    enemy->unk_30                   = 0;
    enemy->unk_2E                   = 0;
    ((EnemyBattler*)g_Task)->unk_5C = 0;
    ((EnemyBattler*)g_Task)->unk_06 = 0;
    ((EnemyBattler*)g_Task)->unk_07 = 0;
    ((EnemyBattler*)g_Task)->unk_08 = g_BattleScrollDir ^ 2;
    ((EnemyBattler*)g_Task)->unk_48 = 0;
    ((EnemyBattler*)g_Task)->unk_4B = 0xFF;
    enemy                           = (EnemyBattler*)g_Task;
    enemy->pos.x.raw                = x;
    enemy->pos.y.raw                = y;
    enemy                           = (EnemyBattler*)g_Task;
    COORD_INT(enemy->pos.z)         = Area_SampleHeight(enemy->pos, y);
    enemy->unk_2B                   = 0;
    Area_FindSceneRecord(FIELD(u16, &D_800E405E, unit_offset));
    enemy_offset                          = (slot & BYTE_MASK) * BATTLE_ENEMY_STRIDE;
    FIELD(u16, &D_801EB6BA, enemy_offset) = FIELD(u16, &D_800E405E, unit_offset);
    func_800AC218(slot & BYTE_MASK, unit & BYTE_MASK);
    func_800AD0A8(slot & BYTE_MASK, unit & HALF_MASK);
    FIELD(u8, &D_801EB6AF, enemy_offset) = func_800AD044(FIELD(u8, &D_800E4050, unit_offset));
    g_BattleEnemyCount += 1;
}
#else
INCLUDE_ASM(func_800ABCE0);
#endif
