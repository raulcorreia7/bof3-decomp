#ifndef OVERLAY_WORLD04_AREA193_13_H
#define OVERLAY_WORLD04_AREA193_13_H

/* The world04/area193/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"

/* D_80143F1D */
extern u8  g_GameRequestKind;
/* The selection pairs at the payload start. */
extern u8  D_801F2C04[];
/* The selection record and the request tables it selects from. */
extern u16 D_801F39FC[];
extern u16 D_801F3A08[];
extern u16 D_801F3A10[];
extern u8  D_801F3A18[];
extern u8  D_801F3A19[];

/* The party item helpers the count-and-add path calls. */
/* func_801650B4 */
bool Item_Add(s32 category, s32 item, s32 amount, s32 unused);
/* func_8016628C */
s32  Item_Count(u8 category, u8 item, u8 mode);

#endif
