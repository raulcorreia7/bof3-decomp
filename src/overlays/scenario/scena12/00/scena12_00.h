#ifndef OVERLAY_SCENARIO_SCENA12_00_H
#define OVERLAY_SCENARIO_SCENA12_00_H

/* The scenario/scena12/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"

extern u8  D_80146865;
extern u8  D_80146866;
extern u8  D_80146867;
extern u8  D_80146874;
extern u8  D_80146875;
extern u32 D_801F6C00;

/* D_801FD178 */
extern Callback  g_SceneEntityDispatch[];
extern Callback  D_801FD184[];
extern Callback  D_801FD190[];
extern Callback  D_801FD198[];
extern Callback  D_801FD1B8[];
extern Callback  D_801FD1C4[];
/* D_801FD1EC */
extern SceneFunc g_SceneActorDispatch[];

extern union {
    u8  bytes[4];
    u16 half;
} D_801FD288;

extern char D_801F6C04[];

void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, s32 window_style);
void func_801F75EC(void);

#endif
