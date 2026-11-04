#ifndef OVERLAY_SCENARIO_SCENA08_00_H
#define OVERLAY_SCENARIO_SCENA08_00_H

/* The scenario/scena08/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "work/area_spad.h"
#define SCRATCH_ROW_STRIDE 0x28
#define SCRATCH_ROW_OFFSET 0x00

extern u32       D_801F6C00;
extern Callback  D_801FE8A0[];
extern Callback  D_801FE8D0[];
extern Callback  D_801FE8D8[];
extern Callback  D_801FE908[];
extern Callback  D_801FE910[];
extern Callback  D_801FE938[];
extern Callback  D_801FE964[];
extern Callback  D_801FE970[];
extern SceneFunc D_801FE9C0[];

s32  func_801F7E14(void);
s32  func_801F8BF8(void);
void func_801F8AE8(void);
void func_801FE800(void);

extern Callback D_801FE894[];

void func_801F7DE8(void);

extern u8  D_80146874;
extern u16 D_80146876;
extern u8  D_80146875;

extern u16 D_800E4C1E;

#endif
