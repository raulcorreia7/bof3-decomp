#ifndef OVERLAY_PLCHAR_PLP267_00_H
#define OVERLAY_PLCHAR_PLP267_00_H

/* The plchar/plp267/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "work/area_spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 30

/* The two route directions this character program turns between. */
#define CHARACTER_FACING_AWAY   5
#define CHARACTER_FACING_BACK   3

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

s32 func_801B2D00(s32 selector);

extern s32  func_801CF99C(void);
extern void func_801CFB40(void);
#define PLCHAR_CHECK_FACING func_801CF99C
#define PLCHAR_PREPARE_TURN func_801CFB40

#endif
