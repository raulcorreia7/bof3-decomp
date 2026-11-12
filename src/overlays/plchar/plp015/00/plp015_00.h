#ifndef OVERLAY_PLCHAR_PLP015_00_H
#define OVERLAY_PLCHAR_PLP015_00_H

/* The plchar/plp015/00 overlay's local declarations. Only this image
 * includes the file. */

/* The two route directions this character program turns between. */
#define CHARACTER_FACING_AWAY FACING_LEFT
#define CHARACTER_FACING_BACK FACING_UP

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE    10

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

void Actor_BeginScript(s32 script_index, s32 position);

#endif
