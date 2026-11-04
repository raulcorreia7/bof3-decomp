#ifndef OVERLAY_SCENARIO_SCE15EF3_00_H
#define OVERLAY_SCENARIO_SCE15EF3_00_H

/* The scenario/sce15ef3/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "work/area_spad.h"

/* The 16 six-byte effect slots. */
#define SCENE_SLOT_BASE (AREA_WORK_WINDOW + 0x18A0)

extern u32      D_80145EC4;
extern u32      D_801D0C00;
extern Callback D_801D27CC[];
extern Callback D_801D27D8[];
extern Callback D_801D27EC[];
extern Callback D_801D2800[];
extern Callback D_801D280C[];

extern Callback D_801D27C0[];

extern void func_801D23AC(u8 arg);
void        func_801D230C(void);
void        func_801D18CC(void);
void        func_801D1A60(void);

#endif
