#ifndef OVERLAY_BMAGIC_MAGIC063_03_H
#define OVERLAY_BMAGIC_MAGIC063_03_H

/* The bmagic/magic063/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC063_STEP_COUNT 5

typedef struct Magic063Steps {
    Callback steps[MAGIC063_STEP_COUNT];
} Magic063Steps;

extern Magic063Steps D_801EEC04;
extern Callback      D_801F040C[];

extern Callback      D_801F0440[];
extern u8            D_801F0454[];
extern u8            D_801F0470[];
extern PartyBattler* D_801F1054;
void                 func_801EECF8(void);
void                 func_801EF340(void);
void                 func_801EF994(void);
void                 func_801EFA5C(void);

#endif
