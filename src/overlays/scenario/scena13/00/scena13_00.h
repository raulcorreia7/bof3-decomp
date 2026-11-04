#ifndef OVERLAY_SCENARIO_SCENA13_00_H
#define OVERLAY_SCENARIO_SCENA13_00_H

/* The scenario/scena13/00 overlay's local declarations. Only this image
 * includes the file. */

#define GRAPHICS_PALETTE_PENDING_VOLATILE
#define GAME_SCRATCH_BASE_SCALAR
#include "overlays/scenario/scenario.h"
#include "engine/game/00/game_00.h"

extern u32       D_801F6C00;
extern u8        D_801468E4[];
extern u8        D_801FBF20[];
extern Callback  D_801FBEFC[];
extern Callback  D_801FBF10[];
extern Callback  D_801FBF48[];
extern Callback  D_801FBF54[];
extern SceneFunc D_801FBFB8[];

void func_801F6FF8(void);
void func_801F70DC(void);
void func_801F7568(void);

extern Callback D_801FBEF0[];

extern u8 D_80144908[];
extern u8 D_8014490B[];

#endif
