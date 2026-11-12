#ifndef OVERLAY_PLCHAR_PLP678_00_H
#define OVERLAY_PLCHAR_PLP678_00_H

/* The plchar/plp678/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The image's map-cell probe, and whether its personal action plays the character's cue. */
#define CHAR_CELL_PROBE              func_801CEC28
#define CHAR_PERSONAL_ACTION_HAS_CUE 1

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE         20

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT      30

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801D0564[];
extern Callback D_801D0570[];
extern Callback D_801D0578[];
extern Callback D_801D058C[];
extern Callback D_801D0598[];
extern Callback D_801D05A4[];
extern Callback D_801D05B0[];
extern Callback D_801D05BC[];
extern Callback D_801D05C4[];
extern Callback D_801D05D0[];

s32  func_801CF1A4(void);
void func_801CF348(void);

s32 func_801CEC28(s16 x, s16 y);

#endif
