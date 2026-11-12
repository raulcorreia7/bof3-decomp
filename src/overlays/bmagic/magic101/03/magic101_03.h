#ifndef OVERLAY_BMAGIC_MAGIC101_03_H
#define OVERLAY_BMAGIC_MAGIC101_03_H

/* The bmagic/magic101/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern SVECTOR D_1F800014[];

#define MAGIC101_STEP_COUNT 5

typedef struct Magic101Steps {
    Callback steps[MAGIC101_STEP_COUNT];
} Magic101Steps;

extern Magic101Steps D_801EEC04;

extern u16      D_801EFCC0[];
extern u16      D_801EFCE0[];
extern Callback D_801EFCE8[];
void            func_801EF88C(void);

void func_801EF07C(void);

#endif
