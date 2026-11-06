#ifndef BATTLE_HANDLERS_H
#define BATTLE_HANDLERS_H

#include "common/handler.h"

/* The copy sizes are data reads, not model arithmetic: func_801E6AA0 takes
 * three words out of D_801D0F38 (`lw 0x0/0x4/0x8` then three `sw`), and the run
 * at D_801D0C84 holds five pointers before `+0x14` turns into 0x03020100 data.
 * D_801D0F38 itself is a longer table (twelve pointers measured before it
 * stops), so that extern types a copy, not the whole table. */
#define BATTLE_HANDLER_TABLE3_SIZE 0x0c
#define BATTLE_HANDLER_TABLE5_SIZE 0x14

#define BATTLE_RESULT_RING_SIZE    0x10

/* func_801D656C treats 0xFF as pending; battle/battle/03 passes modes 0-6. */
typedef u8 (*BossBattleEventFunc)(u32 mode);

/* Callback-table views the battle code copies and indexes: three or five
 * Callback slots. */
typedef struct BattleHandlerTable3 {
    Callback handlers[3];
} BattleHandlerTable3;

typedef struct BattleHandlerTable5 {
    Callback handlers[5];
} BattleHandlerTable5;

ASSERT_SIZE(BattleHandlerTable3, BATTLE_HANDLER_TABLE3_SIZE);
ASSERT_SIZE(BattleHandlerTable5, BATTLE_HANDLER_TABLE5_SIZE);

/* Fixed four-entry result-ring icon table at 0x801D1004; the battle effects read
 * the same shape from their own module head. */
typedef struct BattleResultRings {
    Callback handlers[4];
} BattleResultRings;

ASSERT_SIZE(BattleResultRings, BATTLE_RESULT_RING_SIZE);

void        func_800AC844(u8 entry_id);
void        func_800AC934(u8 entry_id);
s32         func_800ACFF4(void);
void        func_801DDED8(void);
void        func_801DDF00(void);
void        func_801DDF28(void);
void        Battle_ClearSlotPending(u32 slot);
void        func_801E2314(u32 script_index);
u8          func_801E30F8(void);
u8          func_801E3160(void);
/* func_801E54EC */
void        Battle_CollectEnemySpoils(void);
void        func_801E567C(void);
void        func_801E5704(void);
extern void func_801EF318(void);
#endif
