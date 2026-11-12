#ifndef OVERLAY_PLCHAR_PLP267_00_H
#define OVERLAY_PLCHAR_PLP267_00_H

/* The plchar/plp267/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The image's map-cell probe, and whether its personal action plays the character's cue. */
#define CHAR_CELL_PROBE              func_801CF420
#define CHAR_PERSONAL_ACTION_HAS_CUE 1

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE         20

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT      30

/* The field work row this overlay moves, at scratchpad 0x1F800044. */
extern Callback D_801D0988[];
extern Callback D_801D0994[];
extern Callback D_801D099C[];
extern Callback D_801D09A8[];
extern Callback D_801D09B0[];
extern Callback D_801D09C4[];
extern Callback D_801D09D0[];
extern Callback D_801D09DC[];
extern Callback D_801D09E8[];
extern Callback D_801D09F4[];

extern s32  func_801CF99C(void);
extern void func_801CFB40(void);

s32 func_801CF420(s16 x, s16 y);

#endif
