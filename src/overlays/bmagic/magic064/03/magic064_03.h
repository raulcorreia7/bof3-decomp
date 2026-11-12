#ifndef OVERLAY_BMAGIC_MAGIC064_03_H
#define OVERLAY_BMAGIC_MAGIC064_03_H

/* The bmagic/magic064/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The twelve step callbacks at D_801EEC10, copied to the stack and indexed by the work state byte. */
#define BMAGIC064_STEP_COUNT 12

typedef struct BMagic064Steps {
    Callback handlers[BMAGIC064_STEP_COUNT];
} BMagic064Steps;

extern BMagic064Steps D_801EEC10;

#define MAGIC064_STEP_COUNT 4

typedef struct Magic064Steps {
    Callback steps[MAGIC064_STEP_COUNT];
} Magic064Steps;

#define MAGIC064_SECOND_STEP_COUNT 3

typedef struct Magic064SecondSteps {
    Callback steps[MAGIC064_SECOND_STEP_COUNT];
} Magic064SecondSteps;

extern Magic064Steps       D_801EEC40;
extern Magic064SecondSteps D_801EEC50;
extern Magic064SecondSteps D_801EEC70;
extern void*               D_801F28B4;
extern u8                  D_801F13B4[];

/* The texture coordinates of one cell of the effect sprite's two-by-two atlas: u is 0 or 0x58,
 * v is 0 or 0x50. */
typedef struct BMagic064Cell {
    u16 u;
    u16 v;
} BMagic064Cell;

ASSERT_SIZE(BMagic064Cell, 0x04);
ASSERT_OFFSET(BMagic064Cell, v, 0x02);

extern BMagic064Cell D_801F13A4[];

void func_801EF8F4(void);
void func_801F001C(void);
void func_801F04A0(void);
void func_801F05A4(void);

void func_801F03D8(void);
void func_801F0EEC(s32 variant, s32 abr, s32 color);
void func_801F103C(void);

#endif
