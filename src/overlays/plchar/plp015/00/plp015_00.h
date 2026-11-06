#ifndef OVERLAY_PLCHAR_PLP015_00_H
#define OVERLAY_PLCHAR_PLP015_00_H

/* The plchar/plp015/00 overlay's local declarations. Only this image
 * includes the file. */

/* The two route directions this character program turns between. */
#define CHARACTER_FACING_BACK 1
#define CHARACTER_FACING_AWAY 7

#include "overlays/plchar/plchar.h"
#include "work/area_spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 23

/* The field work row this overlay moves, at scratchpad 0x1F800044. */

extern Callback D_801CFB84[];
extern Callback D_801CFB90[];
extern Callback D_801CFB9C[];
extern Callback D_801CFBA8[];
extern Callback D_801CFBB0[];
extern Callback D_801CFBBC[];
extern Callback D_801CFBC8[];
extern Callback D_801CFBD4[];

#endif
