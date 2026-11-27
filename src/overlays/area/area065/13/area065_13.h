#ifndef OVERLAY_WORLD01_AREA065_13_H
#define OVERLAY_WORLD01_AREA065_13_H

/* The world01/area065/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world01.h"

/* The world-map entry keys WORLD_MAP_SELECT_KEY_SCRIPT scans. */
extern WorldMapKey D_801F4DB4[11];
#define AREA_HUD_SPRITE_CELLS (D_801F5268 + 0x48)
/* The spawn step handler table indexed by the record's step byte. */
extern Callback       D_801F5274[];
extern u8             D_801F5288[];
extern u8             D_801F5290[];
extern u8             D_801F52A0[];
extern WorldMapMarker D_801F5308[6];
extern u8             D_801F5320[];

/* The value of area update step in the shared Area_Update body. */

/* The signed spawn focus offsets, one (x, y) pair per spawn row. */
/* D_801F532C */
/* The script id and tile-mode byte tables indexed by twice the spawn row. */
/* D_801F533C */
extern u8 D_801F5344[];
#define AREA_HUD_MASK_TABLE D_801F5308

extern WorldMapPoint      D_801F4DE0[];
extern u16                D_801F50FC[11][16];
extern FishingLocationRow D_801F525C[2];
extern u8                 D_801F5268[]; /* the "Manillo" text at +0x10 */

void func_801F40FC(s16 x, s16 y);
void Area_Update(void);

#include "overlays/area/shared/world_cloud.h"

#endif
