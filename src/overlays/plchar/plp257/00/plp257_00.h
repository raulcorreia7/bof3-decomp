#ifndef OVERLAY_PLCHAR_PLP257_00_H
#define OVERLAY_PLCHAR_PLP257_00_H

/* The plchar/plp257/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 23

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801CFEDC[];
extern Callback D_801CFEE8[];
extern Callback D_801CFEF0[];
extern Callback D_801CFEFC[];
extern Callback D_801CFF08[];
extern Callback D_801CFF14[];
extern Callback D_801CFF20[];
extern Callback D_801CFF2C[];

#endif
