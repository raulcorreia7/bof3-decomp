#ifndef OVERLAY_BMAGIC_MAGIC042_03_H
#define OVERLAY_BMAGIC_MAGIC042_03_H

/* The bmagic/magic042/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

void func_801EEC70(void);
void func_801EED44(void);

#define MAGIC042_STEP_COUNT 5

typedef struct Magic042Steps {
    Callback steps[MAGIC042_STEP_COUNT];
} Magic042Steps;

extern Magic042Steps D_801EEC04;
void                 func_801EF920(void);
void                 func_801EF380(u8 arg0, u8 arg1);
void                 func_801EF71C(u8 arg0, u8 arg1);

#endif
