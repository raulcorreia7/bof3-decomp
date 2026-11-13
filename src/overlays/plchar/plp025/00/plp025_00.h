#ifndef OVERLAY_PLCHAR_PLP025_00_H
#define OVERLAY_PLCHAR_PLP025_00_H

/* The plchar/plp025/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE    10

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 23

/* The field work row this overlay moves, at scratchpad 0x1F800044. */

extern Callback D_801CFFA8[];
extern Callback D_801CFFB4[];
extern Callback D_801CFFC0[];
extern Callback D_801CFFCC[];
extern Callback D_801CFFD4[];
extern Callback D_801CFFE0[];
extern Callback D_801CFFEC[];
extern Callback D_801CFFF8[];

void Actor_BeginScript(s32 script_index, s32 position);

#endif
