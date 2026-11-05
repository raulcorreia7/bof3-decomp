#include "battle_03.h"

extern volatile s32 D_8014632C;

/* Enemy work tail: pending-damage words at +0x82..0x86 and the state word at
 * +0x100 (no header members yet). */
typedef struct BattleEnemyStep {
    u8  pad_00[0x7C];
    u8  cue; /* +0x7C */
    u8  pad_7D[5];
    u16 pending;   /* +0x82 */
    u16 damage;    /* +0x84 */
    u16 damage_hi; /* +0x86 */
    u8  pad_88[0x78];
    u32 state; /* +0x100 */
} BattleEnemyStep;

ASSERT_SIZE(BattleEnemyStep, 0x104);

#define ENEMY_STEP ((BattleEnemyStep*)g_BattleCurrentEnemy)

MATCH void func_801E54EC(void) {
    u8            count;
    int           new_var;
    volatile s32* acc;

    g_Task->flags = g_Task->flags | ACTOR_FLAG_HIDDEN;
    acc           = &D_8014632C;
    *acc += ENEMY_STEP->damage_hi;
    do {
        D_80146330 += ENEMY_STEP->damage;
        ENEMY_STEP->pending = ENEMY_STEP->pending | 0x4000;
        ENEMY_STEP->damage  = 0;
        func_801DD14C(g_Task->slot);
        func_801E531C();
        count      = D_801462F3 - 1;
        D_801462F3 = count;
        new_var    = count == 0;
        if (new_var) {
            g_BattleResult |= BATTLE_RESULT_VICTORY;
        }
        if (((g_BattleState & BATTLE_STATE_OVER) != 0) && (D_801463CA == g_Task->slot)) {
            g_BattleState &= ~BATTLE_STATE_OVER;
        }
        func_800AD074(ENEMY_STEP->cue);
        GFX_FreePaletteFadeTarget(g_Task);
        ENEMY_STEP->state = ENEMY_STEP->state & (~0x70);
        Battle_ClearSlotPending(g_Task->slot);
        g_Task->mode = 2;
        g_Task->step = 0;
    } while (0);
    g_Task->unk_03 = 0;
}
