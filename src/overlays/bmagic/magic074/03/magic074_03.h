#ifndef OVERLAY_BMAGIC_MAGIC074_03_H
#define OVERLAY_BMAGIC_MAGIC074_03_H

/* The bmagic/magic074/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;
extern BMagicEffectWork* D_801F20DC;

void func_801EED18(void);
void func_801EF710(void);
void func_801F0440(void);

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BMagicEffectWork D_801F055C[];
#define BMAGIC_EFFECT_SLOTS D_801F055C
#define BMAGIC_EFFECT_COUNT 160

#define MAGIC074_STEP_COUNT 3

typedef struct Magic074Steps {
    Callback steps[MAGIC074_STEP_COUNT];
} Magic074Steps;

extern Magic074Steps D_801EEC1C;
void                 func_801F00B0(void);

/* The sparkle record being updated, its launch offset row and the shortest rise per kind. */
#define EFFECT_SPARKLE_TASK    D_801F20DC
#define EFFECT_SPARKLE_OFFSETS D_801F0490
#define EFFECT_SPARKLE_RISE    D_801F0550
extern Point2D D_801F0490[];
extern u8      D_801F0550[];

#endif
