#ifndef OVERLAY_BMAGIC_MAGIC006_03_H
#define OVERLAY_BMAGIC_MAGIC006_03_H

/* The bmagic/magic006/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;

/* The amount Effect_CountDownTimer adds to the effect work byte 9. */
#define EFFECT_TIMER_STEP 8

extern s16 D_1F800008;

typedef struct Magic006Steps801EEC1C {
    Callback steps[3];
} Magic006Steps801EEC1C;

typedef struct Magic006Steps801EEC28 {
    Callback steps[4];
} Magic006Steps801EEC28;

extern Magic006Steps801EEC1C D_801EEC1C;

extern Magic006Steps801EEC28 D_801EEC28;

void func_801EEC90(void);

void func_801F0308(void);
void func_801F0790(void);

#endif
