#ifndef OVERLAY_PLCHAR_PLP026_00_H
#define OVERLAY_PLCHAR_PLP026_00_H

/* The plchar/plp026/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/plchar/plchar.h"
#include "work/area_spad.h"

/* The tail callback table's entry count in this image. */
#define PLCHAR_STEP_TABLE_COUNT 30

/* The two route directions this character program turns between. */
#define CHARACTER_FACING_AWAY   5
#define CHARACTER_FACING_BACK   3

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
#define PLCHAR_CHECK_FACING func_801D06C4
#define PLCHAR_PREPARE_TURN func_801D0868

#endif
