#ifndef OVERLAY_WORLD01_AREA065_13_H
#define OVERLAY_WORLD01_AREA065_13_H

/* The world01/area065/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "area/spad.h"

extern SVECTOR D_1F800014[];
extern u8      D_801F4DB4[];
#define AREA_HUD_SPRITE_CELLS ((u8*)D_801F4DB4 + 0x4FC)
/* The spawn step handler table indexed by the record's step byte. */
extern Callback D_801F5274[];
extern u8       D_801F5288[];
extern u8       D_801F5290[];
extern u8       D_801F52A0[];
extern u8       D_801F5320[];
/* The signed spawn focus offsets, one (x, y) pair per spawn row. */
/* D_801F532C */
extern Point2u  g_FlockVelocity[4];
/* The script id and tile-mode byte tables indexed by twice the spawn row. */
/* D_801F533C */
extern u8       g_FlockScript[4][2];
extern u8       D_801F5344[];

/* The value of area update step in the shared Area_Update body. */

extern WorldMapMarker D_801F5308[6];
#define AREA_HUD_MASK_TABLE D_801F5308

extern WorldMapPoint D_801F4DE0[];
extern u16           D_801F50FC[5][16];
extern u8            D_801F525C[12];
extern u8            D_801F525D[];
extern u8            D_801F5268[]; /* the "Manillo" text at +0x10 */

void func_801F40FC(s16 x, s16 y);
void Area_Update(void);

#include "overlays/area/world_cloud.h"

#endif
