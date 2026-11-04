#ifndef OVERLAY_SCENARIO_SCENA04_00_H
#define OVERLAY_SCENARIO_SCENA04_00_H

/* The scenario/scena04/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "work/area_spad.h"

#define SCRATCH_ROW_STRIDE 0x28
#define SCRATCH_ROW_OFFSET 0x25

extern u16       g_GameAreaId;
extern s8        D_80144EA8;
extern u32       D_801F6C00;
extern Callback  D_801FA198[];
extern Callback  D_801FA1E4[];
extern s8        D_801FA220[];
extern Callback  D_801FA204[];
extern Callback  D_801FA210[];
extern SceneFunc D_801FA224[];

extern Callback D_801FA180[];

void func_801F7FCC(void);
void func_801F7084(s32* step);
s8   func_801F9DF4();

extern u8 D_80144F5A;
extern u8 D_80144F5B;
extern u8 D_80144F5C;
extern u8 D_80144F5E;
extern u8 D_80144F5F;

#endif
