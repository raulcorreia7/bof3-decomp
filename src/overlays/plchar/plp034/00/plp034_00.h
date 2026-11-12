#ifndef OVERLAY_PLCHAR_PLP034_00_H
#define OVERLAY_PLCHAR_PLP034_00_H

/* The plchar/plp034/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The image's map-cell probe, and whether its personal action plays the character's cue. */
#define CHAR_CELL_PROBE              func_801CF940
#define CHAR_PERSONAL_ACTION_HAS_CUE 0

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE         10

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT      28

/* The field work row this overlay moves, at scratchpad 0x1F800044. */

extern Callback D_801D02F4[];
extern Callback D_801D0300[];
extern Callback D_801D030C[];
extern Callback D_801D0318[];
extern Callback D_801D0320[];
extern Callback D_801D0334[];
extern Callback D_801D0340[];
extern Callback D_801D034C[];
extern Callback D_801D0358[];

void func_801CFB4C(s32 kind, s32 x, s32 y, s32 code);

s32 func_801CF940(s16 x, s16 y);

#endif
