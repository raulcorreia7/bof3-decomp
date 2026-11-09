#ifndef OVERLAY_PLCHAR_PLP278_00_H
#define OVERLAY_PLCHAR_PLP278_00_H

/* The plchar/plp278/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE    20

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 22

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801CFCB4[];
extern Callback D_801CFCC0[];
extern Callback D_801CFCC8[];
extern Callback D_801CFCD4[];
extern Callback D_801CFCE0[];
extern Callback D_801CFCEC[];
extern Callback D_801CFCF4[];
extern Callback D_801CFD00[];

#endif

extern u8 D_80143FFC[];
extern u8 D_80144000[];
extern u8 D_80144006[];
