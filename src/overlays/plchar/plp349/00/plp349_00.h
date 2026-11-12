#ifndef OVERLAY_PLCHAR_PLP349_00_H
#define OVERLAY_PLCHAR_PLP349_00_H

/* The plchar/plp349/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The image's map-cell probe, and whether its personal action plays the character's cue. */
#define CHAR_CELL_PROBE              func_801CEC18
#define CHAR_PERSONAL_ACTION_HAS_CUE 0

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT      22

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801CF5EC[];
extern Callback D_801CF5F8[];
extern Callback D_801CF600[];
extern Callback D_801CF614[];
extern Callback D_801CF620[];
extern Callback D_801CF62C[];
extern Callback D_801CF638[];

s32 func_801CEC18(s16 x, s16 y);

#endif
