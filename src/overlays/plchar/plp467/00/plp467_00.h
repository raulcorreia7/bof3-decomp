#ifndef OVERLAY_PLCHAR_PLP467_00_H
#define OVERLAY_PLCHAR_PLP467_00_H

/* The plchar/plp467/00 overlay's local declarations. */

#include "overlays/plchar/plchar.h"
#include "area/spad.h"

/* The cue id multiplier of this image's rare spawn cue. */
#define CHAR_SPAWN_CUE_SCALE    20

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 28

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

extern s32  func_801CF3C0(void);
extern void func_801CF564(void);

#endif
void func_801CF050(s32 kind, s32 x, s32 y, s32 code);
