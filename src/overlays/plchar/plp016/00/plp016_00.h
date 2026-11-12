#ifndef OVERLAY_PLCHAR_PLP016_00_H
#define OVERLAY_PLCHAR_PLP016_00_H

/* The plchar/plp016/00 overlay's local declarations. Only this image
 * includes the file. */

/* The two route directions this character program turns between. */
#define CHARACTER_FACING_AWAY FACING_LEFT
#define CHARACTER_FACING_BACK FACING_UP

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The image's map-cell probe, and whether its personal action plays the character's cue. */
#define CHAR_CELL_PROBE              func_801CFD24
#define CHAR_PERSONAL_ACTION_HAS_CUE 1

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE         10

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT      30

/* The field work row this overlay moves, at scratchpad 0x1F800044. */

extern Callback D_801D0630[];
extern Callback D_801D063C[];
extern Callback D_801D0648[];
extern Callback D_801D0654[];
extern Callback D_801D065C[];
extern Callback D_801D0668[];
extern Callback D_801D0670[];
extern Callback D_801D0684[];
extern Callback D_801D0690[];
extern Callback D_801D069C[];

extern s32  func_801D02A0(void);
extern void func_801D0444(void);

s32 func_801CFD24(s16 x, s16 y);

#endif
