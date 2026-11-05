#ifndef OVERLAY_PLCHAR_PLP27A_00_H
#define OVERLAY_PLCHAR_PLP27A_00_H

/* The plchar/plp27a/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "work/area_spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 17

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801CF914[];
extern Callback D_801CF920[];
extern Callback D_801CF92C[];
extern Callback D_801CF938[];

#endif
