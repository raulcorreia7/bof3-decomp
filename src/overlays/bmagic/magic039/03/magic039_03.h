#ifndef OVERLAY_BMAGIC_MAGIC039_03_H
#define OVERLAY_BMAGIC_MAGIC039_03_H

/* The bmagic/magic039/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC039_STEP_COUNT 3

typedef struct Magic039Steps {
    Callback steps[MAGIC039_STEP_COUNT];
} Magic039Steps;

extern Magic039Steps     D_801EEC28;
extern BMagicEffectFuncs D_801EEC10;

void func_801EF758(void);

/* The start phase each of the eight pieces adds to 9, indexed by piece. */
extern u8 D_801F041C[];

/* The red, green and blue of each colour row, indexed by the effect byte 0x04: the disc rows,
 * the box rows and the flame rows. */
extern u8 D_801F0404[][3];
extern u8 D_801F040C[][3];
extern u8 D_801F0414[][3];

#endif
