#ifndef OVERLAY_PLCHAR_PLP349_00_H
#define OVERLAY_PLCHAR_PLP349_00_H

/* The plchar/plp349/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "work/area_spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 22

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801CF5EC[];
extern Callback D_801CF5F8[];
extern Callback D_801CF600[];
extern Callback D_801CF614[];
extern Callback D_801CF620[];
extern Callback D_801CF638[];
extern Callback D_801CF62C[];

#endif
