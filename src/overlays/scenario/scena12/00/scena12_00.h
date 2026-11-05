#ifndef OVERLAY_SCENARIO_SCENA12_00_H
#define OVERLAY_SCENARIO_SCENA12_00_H

/* The scenario/scena12/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"

extern u32       D_801F6C00;
extern Callback  D_801FD184[];
extern Callback  D_801FD190[];
extern Callback  D_801FD198[];
extern Callback  D_801FD1B8[];
extern Callback  D_801FD1C4[];
extern SceneFunc D_801FD1EC[];

extern Callback D_801FD178[];
extern u8       D_80145F09;
extern u8       D_80146865;
extern u8       D_80146866;
extern u8       D_80146867;
extern u8       D_80146874;
extern u8       D_80146875;

extern union {
    u8  bytes[4];
    u16 half;
} D_801FD288;

extern char D_801F6C04[];
extern u16  g_GameAreaId;

void UI_DrawAsciiString(s16 left, s16 top, s32 flags, u8* text);

#endif
