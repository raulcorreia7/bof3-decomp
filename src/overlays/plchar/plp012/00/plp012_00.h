#ifndef OVERLAY_PLCHAR_PLP012_00_H
#define OVERLAY_PLCHAR_PLP012_00_H

/* The plchar/plp012/00 overlay's local declarations. Only this image
 * includes the file. */

/* The two route directions this character program turns between. */
#define CHARACTER_FACING_AWAY FACING_LEFT
#define CHARACTER_FACING_BACK FACING_UP

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE    10

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 22

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801CFD80[];
extern Callback D_801CFD8C[];
extern Callback D_801CFD98[];
extern Callback D_801CFDA4[];
extern Callback D_801CFDAC[];
extern Callback D_801CFDB8[];
extern Callback D_801CFDC0[];
extern Callback D_801CFDCC[];

void Actor_BeginScript(s32 script_index, s32 position);

#endif
