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

/* One sprite cell's texture coordinates: u and v of the cell in the effect's texture page. */
typedef UPoint2D Magic064SpriteUv;

extern Magic064SpriteUv D_801F13A4[];

void func_801EF8F4(void);
void func_801F001C(void);
void func_801F04A0(void);
void func_801F05A4(void);

void func_801F03D8(void);
void func_801F0EEC(u32 sprite, s32 blend, s32 color);
void func_801F103C(void);

#endif
