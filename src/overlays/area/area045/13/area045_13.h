#ifndef OVERLAY_WORLD01_AREA045_13_H
#define OVERLAY_WORLD01_AREA045_13_H

/* The world01/area045/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "area/spad.h"

#define AREA_SCENE_RECORD     0x3B

#define AREA_HUD_SPRITE_CELLS ((u8*)D_801F5364 + 0x10)

extern SVECTOR  D_1F800014[];
extern u8       D_801F4D7C[];
/* The spawn step handler table indexed by the record's step byte. */
extern Callback D_801F5338[];
extern u8       D_801F534C[];
extern u8       D_801F5354[];
extern u8       D_801F53E4[];
/* The signed spawn focus offsets, one (x, y) pair per spawn row. */
/* D_801F53F0 */
extern Point2u  g_FlockVelocity[4];
/* The script id and tile-mode byte tables indexed by twice the spawn row. */
/* D_801F5400 */
extern u8       g_FlockScript[4][2];
extern u8       D_801F5408[];

/* The steppers that reload the cell after every store select the volatile
 * declaration. */

/* The value of func 801f2eec table in the shared func_801F2EEC body. */

/* The value of area update step in the shared Area_Update body. */

extern WorldMapMarker D_801F53CC[6];
#define AREA_HUD_MASK_TABLE D_801F53CC

extern u8  D_801F4DA4[548];
extern u16 D_801F51BC[9][16];
extern u8  D_801F531C[28];
extern u8  D_801F531D[]; /* the record-selector byte at +1 */
extern u8  D_801F532C[]; /* the "Manillo" text at +0x10 */

void func_801F40C4(s16 x, s16 y);
void Area_Update(void);

#include "overlays/area/world_cloud.h"

#endif
