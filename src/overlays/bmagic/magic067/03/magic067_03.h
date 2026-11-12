#ifndef OVERLAY_BMAGIC_MAGIC067_03_H
#define OVERLAY_BMAGIC_MAGIC067_03_H

/* The bmagic/magic067/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC067_STEP_COUNT 5

typedef struct Magic067Steps {
    Callback steps[MAGIC067_STEP_COUNT];
} Magic067Steps;

#define MAGIC067_SECOND_STEP_COUNT 3

typedef struct Magic067SecondSteps {
    Callback steps[MAGIC067_SECOND_STEP_COUNT];
} Magic067SecondSteps;

extern Magic067Steps       D_801EEC04;
extern Magic067SecondSteps D_801EEC18;
extern Callback            D_801F04C8[];
extern Callback            D_801F04D8[];

void func_801EF79C(void);
void func_801F00C4(void);

#endif
