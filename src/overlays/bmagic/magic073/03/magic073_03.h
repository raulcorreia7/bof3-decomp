#ifndef OVERLAY_BMAGIC_MAGIC073_03_H
#define OVERLAY_BMAGIC_MAGIC073_03_H

/* The bmagic/magic073/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;
extern BMagicEffectWork* D_801F21F0;

void func_801EED18(void);
void func_801EEF50(void);
void func_801EF724(void);
void func_801F0454(void);

u8 func_801F04A4(void);

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BMagicEffectWork D_801F0670[];
#define BMAGIC_EFFECT_SLOTS D_801F0670
#define BMAGIC_EFFECT_COUNT 160

#define MAGIC073_STEP_COUNT 3

typedef struct Magic073Steps {
    Callback steps[MAGIC073_STEP_COUNT];
} Magic073Steps;

extern Magic073Steps D_801EEC1C;
void                 func_801F00C4(void);
void                 func_801EFE2C(u16 angle, u16 radius);

/* The sparkle record being updated, its launch offset row and the shortest rise per kind. */
#define EFFECT_SPARKLE_TASK    D_801F21F0
#define EFFECT_SPARKLE_OFFSETS D_801F05A4
#define EFFECT_SPARKLE_RISE    D_801F0664
extern Point2D D_801F05A4[];
extern u8      D_801F0664[];

#endif
