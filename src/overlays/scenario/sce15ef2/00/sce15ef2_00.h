#ifndef OVERLAY_SCENARIO_SCE15EF2_00_H
#define OVERLAY_SCENARIO_SCE15EF2_00_H

/* The scenario/sce15ef2/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"

#define g_ScanBars ((ScanBar*)AREA_WORK)

extern u32      D_801D0C00;
extern Callback D_801D1B1C[];
extern Callback D_801D1B2C[];
extern Callback D_801D1B38[];
extern Callback D_801D1B48[];

/* func_801D15DC */
void Scene_ClaimScanBar(void);
/* func_801D1624 */
u8   Scene_UpdateScanBars(s32 y);

void func_801D1218(WorldPos* pos, s16 y, s32 mode);
void func_801D17A0(s32 x, s32 y, s32 mode);

#endif
