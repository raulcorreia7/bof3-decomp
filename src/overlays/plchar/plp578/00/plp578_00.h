#ifndef OVERLAY_PLCHAR_PLP578_00_H
#define OVERLAY_PLCHAR_PLP578_00_H

/* The plchar/plp578/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "work/area_spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 23

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801CFAB8[];
extern Callback D_801CFAC4[];
extern Callback D_801CFAD0[];
extern Callback D_801CFADC[];
extern Callback D_801CFAE8[];
extern Callback D_801CFAF4[];
extern Callback D_801CFAFC[];
extern Callback D_801CFB08[];

#endif
