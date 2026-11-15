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

extern Callback D_801F0440[];
extern u8       D_801F0454[];
extern u8       D_801F0470[];

/* The four sparkle wedges of func_801EFA5C: the radius and angle of their two outer corners. */
extern s16 D_801F041C[];
extern s16 D_801F0424[];
extern s16 D_801F042C[];
extern s16 D_801F0434[];
/* The phase each wedge adds to the effect tick. */
extern u8  D_801F043C[];
void       func_801EECF8(void);
void       func_801EF340(void);
void       func_801EF994(void);
void       func_801EFA5C(void);
void       func_801F03B0(void);

#endif
