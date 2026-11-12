#ifndef OVERLAY_BMAGIC_MAGIC151_03_H
#define OVERLAY_BMAGIC_MAGIC151_03_H

/* The bmagic/magic151/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern SVECTOR D_1F800014[];

#define MAGIC151_STEP_COUNT 5

typedef struct Magic151Steps {
    Callback steps[MAGIC151_STEP_COUNT];
} Magic151Steps;

extern Magic151Steps D_801EEC10;
extern Magic151Steps D_801EEC24;

extern BMagicEffectFuncs D_801EEC38;
void                     func_801F026C(void);
void                     func_801F0648(void);
void                     func_801F0D0C(u8 angle0, u8 angle1);

extern Callback D_801F24B8[];
/* The draw step's handler table and its two-byte row per effect slot. */
extern u8       D_801F24D0[][2];
extern Callback D_801F24F0[];
extern Callback D_801F24FC[];
extern Callback D_801F250C[];
void            Effect_SetActorMatrixQuarterRoll(void);
void            func_801F1DC0(void);
void            BMagic_DrawGlowRingInner(void);
void            BMagic_DrawGlowRingOuter(void);

#endif
