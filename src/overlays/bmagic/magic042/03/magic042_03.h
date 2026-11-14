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
extern Point2s       D_801EFB74[][2];
extern Point2s       D_801EFBCC[][2];
extern u8            D_801EFC24[];
void                 func_801EF920(void);
void                 func_801EF380(u8 start, u16 radius);
void                 func_801EF71C(u8 start, u16 radius);

#endif
