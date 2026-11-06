#ifndef OVERLAY_PLCHAR_PLP678_00_H
#define OVERLAY_PLCHAR_PLP678_00_H

/* The plchar/plp678/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "work/area_spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 30

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

void func_801CF348(void);

#endif
