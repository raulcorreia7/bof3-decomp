#ifndef OVERLAY_PLCHAR_PLP457_00_H
#define OVERLAY_PLCHAR_PLP457_00_H

/* The plchar/plp457/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "work/area_spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 21

/* The two route directions this character program turns between. */
#define CHARACTER_FACING_AWAY   5
#define CHARACTER_FACING_BACK   3

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801CF918[];
extern Callback D_801CF924[];
extern Callback D_801CF930[];
extern Callback D_801CF93C[];
extern Callback D_801CF948[];

s32 func_801B2D00(s32 selector);

#endif
