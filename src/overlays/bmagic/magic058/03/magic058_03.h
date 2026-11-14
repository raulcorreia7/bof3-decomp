#ifndef OVERLAY_BMAGIC_MAGIC058_03_H
#define OVERLAY_BMAGIC_MAGIC058_03_H

/* The bmagic/magic058/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern u8  D_801EC2E4;
/* The scratchpad base read as a halfword: the radius the range test uses. */
extern s16 D_1F800000_HALF;

#define MAGIC058_STEP_COUNT 3

typedef struct Magic058Steps {
    Callback steps[MAGIC058_STEP_COUNT];
} Magic058Steps;

extern Magic058Steps D_801EEC04;
void                 func_801EF36C(void);
extern Magic058Steps D_801EEC10;
extern Magic058Steps D_801EEC1C;
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect  D_801EFEF4[];
#define BMAGIC_EFFECT_SLOTS D_801EFEF4
#define BMAGIC_EFFECT_COUNT 36

void func_801DE8C0(s32 arg0, s32 arg1, s32 arg2);
void func_801EF74C(void);
void func_801EFA78(void);
s32  func_801EFDD4(void* battler);
u8   func_801DB524(u8 slot);

/* One claim byte per battler slot: set to -1 once the slot has drawn its effects. */
extern s8 D_801F0FD4[];

#endif
