#ifndef OVERLAY_PLCHAR_PLP034_00_H
#define OVERLAY_PLCHAR_PLP034_00_H

/* The plchar/plp034/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "work/area_spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 28

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

#endif
