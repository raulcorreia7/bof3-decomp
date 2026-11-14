#ifndef OVERLAY_BMAGIC_MAGIC096_03_H
#define OVERLAY_BMAGIC_MAGIC096_03_H

/* The bmagic/magic096/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern SVECTOR D_1F800014[];

/* The scratch words func_801F0164 sums the screen x, y and height of the living targets into, and their count; the
 * effect view names only halfwords there, so the words go through the scratch math word view. */
#define MAGIC096_SUM_X     D_1F800000.view.scenario.math_00
#define MAGIC096_SUM_Y     D_1F800000.view.scenario.math_04
#define MAGIC096_SUM_Z     D_1F800000.view.scenario.math_08
#define MAGIC096_SUM_COUNT D_1F800000.view.scenario.math_0C
void BMagic_DrawGlowRing(void);
void func_801F0164(void);

#define MAGIC096_STEP_COUNT 5

typedef struct Magic096Steps {
    Callback steps[MAGIC096_STEP_COUNT];
} Magic096Steps;

extern Magic096Steps D_801EEC10;
extern u8            D_801F0488[];

/* The x and y offset from the battler each spawned effect starts at, one row per effect index (byte 0x04). */
extern Point2l D_801F0408[];
/* One byte per spawned effect. */
extern u8      D_801F0498[];

#endif
