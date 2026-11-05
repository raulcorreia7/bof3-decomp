#ifndef OVERLAY_PLCHAR_PLP278_00_H
#define OVERLAY_PLCHAR_PLP278_00_H

/* The plchar/plp278/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "work/area_spad.h"

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
