#ifndef OVERLAY_WORLD03_AREA115_13_H
#define OVERLAY_WORLD03_AREA115_13_H

/* The world03/area115/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "common/vector.h"
#include "work/actor.h"
#include "overlays/area/world03.h"
#include "work/area_spad.h"
#include <rand.h>

/* One spawn point in the area's spawn table: x then y, four bytes. */
typedef Vec2us AreaSpawnPoint;

ASSERT_SIZE(AreaSpawnPoint, 4);

extern SVECTOR        D_1F800014[];
extern s32            D_80145EC4[];
extern u8             D_801F4D7C[]; /* key rows: u16 key + byte mode, stride 4 */
extern WorldMapPoint  D_801F4D90[];
extern u16            D_801F4E90[5][16];
extern u8             D_801F4F30[12];
extern u8             D_801F4F31[];
extern u8             D_801F4F3C[]; /* the "Manillo" text at +0x10 */
extern Callback       D_801F4F48[];
extern Callback       D_801F4F5C[];
extern Callback       D_801F4F74[];
extern u8             D_801F4F84[]; /* one four-byte sprite cell per id: w, h, u0, v0 */
#define AREA_HUD_SPRITE_CELLS D_801F4F84
extern WorldMapMarker D_801F4FDC[6];
#define AREA_HUD_MASK_TABLE D_801F4FDC
extern Callback       D_801F4FF4[];
extern AreaSpawnPoint D_801F5000[];
extern u8             D_801F5010[];
extern u8             D_801F5011[]; /* the script-argument byte at +1 */
extern Callback       D_801F5018[];

u8   Game_FindAreaHandler(void);
void func_801F34CC(void);
/* func_801F35BC */
void Area_Update(void);
/* func_801F39DC */
void Area_DrawHudSprite(s32 x, s32 y, u32 sprite_id);
/* func_801F3B04 */
void Area_DrawHud(s16 x, s16 y);
void Area_DrawGradientDiamond(s16 x, s16 y);
/* func_801F40C8 */
void Area_DrawHudBanner(s16 x, s16 y);

/* The value of area update step in the shared Area_Update body. */
#define AREA_UPDATE_STEP Area_DrawHud

#endif
