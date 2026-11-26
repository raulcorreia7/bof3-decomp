#ifndef OVERLAY_BMAGIC_MAGIC065_00_H
#define OVERLAY_BMAGIC_MAGIC065_00_H

/* The bmagic/magic065/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The enemy row's steal cells: the first drop's item and rate and the live agility, one
 * 0x118-byte row per enemy. */
typedef struct EnemyStealRow {
    u16 item;
    u8  rate;
    u8  pad_03;
    u8  pad_04[0x0C];
    u16 agility;
    u8  pad_12[0x106];
} EnemyStealRow;

ASSERT_SIZE(EnemyStealRow, 0x118);

extern EnemyStealRow D_801EB6C8[];
extern u8            D_801EC2E4;
extern BattleEffect  D_801EC330[];
extern Magic065Steps D_801EEC04;
/* The drop chance of each rate index. */
extern s8            D_801EF508[];

#define MAGIC065_TASK_STEP_COUNT 4

typedef struct Magic065TaskSteps {
    Callback steps[MAGIC065_TASK_STEP_COUNT];
} Magic065TaskSteps;

extern Magic065TaskSteps D_801EEC14;

void func_801DE8C0(s32 arg0, s32 arg1, s32 arg2);
u32  func_801E590C(u32 mode, u32 effect_type);
void BMagic_SetTextItemName(u8 item_id, u8 category);

#endif
