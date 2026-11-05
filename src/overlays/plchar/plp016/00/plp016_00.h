#ifndef OVERLAY_PLCHAR_PLP016_00_H
#define OVERLAY_PLCHAR_PLP016_00_H

/* The plchar/plp016/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "work/area_spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 30

/* The two route directions this character program turns between. */
#define CHARACTER_FACING_AWAY   7
#define CHARACTER_FACING_BACK   1

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
#define PLCHAR_CHECK_FACING func_801D02A0
#define PLCHAR_PREPARE_TURN func_801D0444

#endif
