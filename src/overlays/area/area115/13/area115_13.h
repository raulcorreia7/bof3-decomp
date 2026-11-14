#ifndef OVERLAY_WORLD03_AREA115_13_H
#define OVERLAY_WORLD03_AREA115_13_H

/* The world03/area115/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "common/vector.h"
#include "sys/actor.h"
#include "overlays/area/world03.h"
#include "area/spad.h"
#include <rand.h>

extern SVECTOR       D_1F800014[];
extern u8            D_801F4D7C[]; /* key rows: u16 key + byte mode, stride 4 */
extern WorldMapPoint D_801F4D90[];
extern u16           D_801F4E90[5][16];
extern u8            D_801F4F30[12];
extern u8            D_801F4F31[];
extern u8            D_801F4F3C[]; /* the "Manillo" text at +0x10 */
extern Callback      D_801F4F48[];
extern Callback      D_801F4F5C[];
extern Callback      D_801F4F74[];
extern u8            D_801F4F84[]; /* one four-byte sprite cell per id: w, h, u0, v0 */
#define AREA_HUD_SPRITE_CELLS D_801F4F84
extern WorldMapMarker D_801F4FDC[6];
#define AREA_HUD_MASK_TABLE D_801F4FDC
extern Callback D_801F4FF4[];
extern Point2u  g_FlockVelocity[4];
extern u8       g_FlockScript[4][2];
extern Callback D_801F5018[];

void func_801F34CC(void);
/* func_801F35BC */
void Area_Update(void);

/* The value of area update step in the shared Area_Update body. */

#include "overlays/area/world_cloud.h"

#endif
