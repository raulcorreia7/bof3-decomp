#ifndef OVERLAY_PLCHAR_PLP567_00_H
#define OVERLAY_PLCHAR_PLP567_00_H

/* The plchar/plp567/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The image's map-cell probe, and whether its personal action plays the character's cue. */
#define CHAR_CELL_PROBE              func_801CF224
#define CHAR_PERSONAL_ACTION_HAS_CUE 1

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE         20

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT      31

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

extern s32  func_801CF7A0(void);
extern void func_801CF944(void);

s32 func_801CF224(s16 x, s16 y);

#endif
