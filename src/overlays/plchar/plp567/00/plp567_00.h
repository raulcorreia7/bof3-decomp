#ifndef OVERLAY_PLCHAR_PLP567_00_H
#define OVERLAY_PLCHAR_PLP567_00_H

/* The plchar/plp567/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "work/area_spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 31

/* The two route directions this character program turns between. */
#define CHARACTER_FACING_AWAY   5
#define CHARACTER_FACING_BACK   3

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801D078C[];
extern Callback D_801D0798[];
extern Callback D_801D07A4[];
extern Callback D_801D07B0[];
extern Callback D_801D07B8[];
extern Callback D_801D07CC[];
extern Callback D_801D07D8[];
extern Callback D_801D07E4[];
extern Callback D_801D07F0[];
extern Callback D_801D07FC[];

s32 func_801B2D00(s32 selector);

#endif
