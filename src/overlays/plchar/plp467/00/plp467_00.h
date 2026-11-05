#ifndef OVERLAY_PLCHAR_PLP467_00_H
#define OVERLAY_PLCHAR_PLP467_00_H

/* The plchar/plp467/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "work/area_spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 28

/* The two route directions this character program turns between. */
#define CHARACTER_FACING_AWAY   5
#define CHARACTER_FACING_BACK   3

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801D03AC[];
extern Callback D_801D03B8[];
extern Callback D_801D03C4[];
extern Callback D_801D03CC[];
extern Callback D_801D03E0[];
extern Callback D_801D03EC[];
extern Callback D_801D03F8[];
extern Callback D_801D0404[];
extern Callback D_801D0410[];

s32 func_801B2D00(s32 selector);

#endif
