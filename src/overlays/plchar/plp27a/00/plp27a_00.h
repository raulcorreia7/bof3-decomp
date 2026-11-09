#ifndef OVERLAY_PLCHAR_PLP27A_00_H
#define OVERLAY_PLCHAR_PLP27A_00_H

/* The plchar/plp27a/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE    20

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 17

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801CF914[];
extern Callback D_801CF920[];
extern Callback D_801CF92C[];
extern Callback D_801CF938[];

#endif

extern u8 D_80143FFC[];
extern u8 D_80144000[];
extern u8 D_80144006[];

