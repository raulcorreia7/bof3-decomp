#ifndef OVERLAY_PLCHAR_PLP247_00_H
#define OVERLAY_PLCHAR_PLP247_00_H

/* The plchar/plp247/00 overlay's local declarations. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE    20

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 20

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801CFAFC[];
extern Callback D_801CFB08[];
extern Callback D_801CFB10[];
extern Callback D_801CFB1C[];
extern Callback D_801CFB28[];
extern Callback D_801CFB34[];
extern Callback D_801CFB40[];

#endif
