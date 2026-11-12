#ifndef OVERLAY_SCENARIO_SCE15EF3_00_H
#define OVERLAY_SCENARIO_SCE15EF3_00_H

/* The scenario/sce15ef3/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"

#define g_ScanBars ((ScanBar*)(AREA_WORK + 0x18A0))

extern u32      D_801D0C00;
/* D_801D27C0 */
extern Callback g_SceneEntityDispatch[];
extern Callback D_801D27CC[];
extern Callback D_801D27D8[];
extern Callback D_801D27EC[];
extern Callback D_801D2800[];

extern Callback D_801D280C[];

void func_801D16DC(void);
void func_801D18CC(void);
void func_801D1A60(void);
void func_801D1FF8(Point3DL* pos, s16 a, s16 b, u16 c, s32 d, s32 e);
void func_801D230C(void);
/* func_801D23AC */
void Scene_DrawRedFade(u8 red);

void func_801D19A0(void);

void func_801D1D20(WorldPos* pos, s32* step, u8 arg2, u8 arg3);

#endif
