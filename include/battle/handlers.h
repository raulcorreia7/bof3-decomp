#ifndef BATTLE_HANDLERS_H
#define BATTLE_HANDLERS_H

#include "common/handler.h"

/* func_801D656C treats 0xFF as pending; battle/battle/03 passes modes 0-6. */
typedef u8 (*BossBattleEventFunc)(u32 mode);

/* The step routines of a battle effect, run by the effect's header.mode or
 * header.step. Retail copies the whole list to the stack before the indexed
 * call, so each length is its own type. */
typedef struct EffectStepFuncs3 {
    Callback handlers[3];
} EffectStepFuncs3;

typedef struct EffectStepFuncs4 {
    Callback handlers[4];
} EffectStepFuncs4;

typedef struct EffectStepFuncs5 {
    Callback handlers[5];
} EffectStepFuncs5;

typedef struct EffectStepFuncs8 {
    Callback handlers[8];
} EffectStepFuncs8;

/* The state routines of a battle menu panel, selected by the panel's state. */
typedef struct BattlePanelStateFuncs3 {
    Callback handlers[3];
} BattlePanelStateFuncs3;

typedef struct BattlePanelStateFuncs4 {
    Callback handlers[4];
} BattlePanelStateFuncs4;

typedef struct BattlePanelStateFuncs5 {
    Callback handlers[5];
} BattlePanelStateFuncs5;

/* The mode routines of a battle menu panel, selected by the panel's mode. */
typedef struct BattlePanelModeFuncs5 {
    Callback handlers[5];
} BattlePanelModeFuncs5;

typedef struct BattlePanelModeFuncs6 {
    Callback handlers[6];
} BattlePanelModeFuncs6;

/* The routines of the battle event kinds Battle_RunEvents dispatches. */
typedef struct BattleEventFuncs {
    Callback handlers[5];
} BattleEventFuncs;

ASSERT_SIZE(EffectStepFuncs3, 3 * sizeof(Callback));
ASSERT_SIZE(EffectStepFuncs4, 4 * sizeof(Callback));
ASSERT_SIZE(EffectStepFuncs5, 5 * sizeof(Callback));
ASSERT_SIZE(EffectStepFuncs8, 8 * sizeof(Callback));
ASSERT_SIZE(BattlePanelStateFuncs3, 3 * sizeof(Callback));
ASSERT_SIZE(BattlePanelStateFuncs4, 4 * sizeof(Callback));
ASSERT_SIZE(BattlePanelStateFuncs5, 5 * sizeof(Callback));
ASSERT_SIZE(BattlePanelModeFuncs5, 5 * sizeof(Callback));
ASSERT_SIZE(BattlePanelModeFuncs6, 6 * sizeof(Callback));
ASSERT_SIZE(BattleEventFuncs, 5 * sizeof(Callback));

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
void        Battle_DefeatEnemy(void);
void        func_801E567C(void);
void        func_801E5704(void);
extern void func_801EF318(void);
#endif
