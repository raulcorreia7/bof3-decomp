#ifndef OVERLAY_PLCHAR_PLP026_00_H
#define OVERLAY_PLCHAR_PLP026_00_H

/* The plchar/plp026/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE    10

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 30

/* The field work row this overlay moves, at scratchpad 0x1F800044. */

extern Callback D_801D0A54[];
extern Callback D_801D0A60[];
extern Callback D_801D0A6C[];
extern Callback D_801D0A78[];
extern Callback D_801D0A80[];
extern Callback D_801D0A8C[];
extern Callback D_801D0A94[];
extern Callback D_801D0AA8[];
extern Callback D_801D0AB4[];
extern Callback D_801D0AC0[];

extern s32  func_801D06C4(void);
extern void func_801D0868(void);

void Actor_BeginScript(s32 raw_selector, s32 raw_code);

#endif
void func_801D0354(s32 kind, s32 x, s32 y, s32 code);
