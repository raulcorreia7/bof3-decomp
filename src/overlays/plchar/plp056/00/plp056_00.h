#ifndef OVERLAY_PLCHAR_PLP056_00_H
#define OVERLAY_PLCHAR_PLP056_00_H

/* The plchar/plp056/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The image's map-cell probe, and whether its personal action plays the character's cue. */
#define CHAR_CELL_PROBE              func_801CFF4C
#define CHAR_PERSONAL_ACTION_HAS_CUE 1

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE         10

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT      31

/* The field work row this overlay moves, at scratchpad 0x1F800044. */

extern Callback D_801D0858[];
extern Callback D_801D0864[];
extern Callback D_801D0870[];
extern Callback D_801D087C[];
extern Callback D_801D0888[];
extern Callback D_801D0894[];
extern Callback D_801D089C[];
extern Callback D_801D08B0[];
extern Callback D_801D08BC[];
extern Callback D_801D08C8[];

extern s32  func_801D04C8(void);
extern void func_801D066C(void);

void func_801D0158(s32 kind, s32 x, s32 y, s32 code);

s32 func_801CFF4C(s16 x, s16 y);

#endif
