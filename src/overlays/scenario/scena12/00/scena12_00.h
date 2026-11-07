#ifndef OVERLAY_SCENARIO_SCENA12_00_H
#define OVERLAY_SCENARIO_SCENA12_00_H

/* The scenario/scena12/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"

extern u8  D_80145F09;
extern u8  D_80146865;
extern u8  D_80146866;
extern u8  D_80146867;
extern u8  D_80146874;
extern u8  D_80146875;
extern u32 D_801F6C00;

extern Callback  D_801FD178[];
extern Callback  D_801FD184[];
extern Callback  D_801FD190[];
extern Callback  D_801FD198[];
extern Callback  D_801FD1B8[];
extern Callback  D_801FD1C4[];
extern SceneFunc D_801FD1EC[];

extern union {
    u8  bytes[4];
    u16 half;
} D_801FD288;

extern u16  g_GameAreaId;
extern char D_801F6C04[];

void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, s32 window_style);
void func_801F75EC(void);

#endif
