#ifndef OVERLAY_BMAGIC_MAGIC151_03_H
#define OVERLAY_BMAGIC_MAGIC151_03_H

/* The bmagic/magic151/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern SVECTOR D_1F800014[];

/* Column views of g_BattleEffects: func_801EFC68 stores through them because the
 * record form reuses the target store's g_Task load for the ticker bump. */
extern u8 D_801EC331[];
extern u8 D_801EC3A4[];

#define MAGIC151_STEP_COUNT 5

typedef struct Magic151Steps {
    Callback steps[MAGIC151_STEP_COUNT];
} Magic151Steps;

extern Magic151Steps D_801EEC10;
extern Magic151Steps D_801EEC24;

extern BMagicEffectFuncs D_801EEC38;
void                     func_801F026C(void);
void                     func_801F0648(void);

extern Callback D_801F24B8[];
extern Callback D_801F250C[];
void            func_801F1DC0(void);
void            BMagic_DrawGlowRingInner(void);
void            BMagic_DrawGlowRingOuter(void);

#endif
