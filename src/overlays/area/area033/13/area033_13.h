#ifndef OVERLAY_WORLD00_AREA033_13_H
#define OVERLAY_WORLD00_AREA033_13_H

/* The world00/area033/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world00.h"
#include "sys/scene.h"
#include "gfx/prim.h"
#include "work/area_spad.h"

/* The scratchpad quad vertices the map arrow draws through. */
extern SVECTOR D_1F800014[];
/* The map step: 9 runs the area entry instead of the reset. */
extern u8      D_8014496D;
/* The party focus point: the camera-scroll targets, x then y, in 16.16. */
extern s32     D_80145EC4[];
/* The tile map scan: four byte records per work row, the map offset and code. */
extern u8      D_801F4CB0[];
/* The work-step handler table indexed by the record's step byte. */
/* Handler tables the step bytes select. */
extern void (*D_801F4F78[])(void);
extern void (*D_801F4F80[])(void);
extern void (*D_801F4F90[])(void);
/* The map arrow sprite's width, height, u and v per sprite id. */
extern u8 D_801F4FA0[];
#define AREA_HUD_SPRITE_CELLS D_801F4FA0
extern u8 D_801F4FA1[];
extern u8 D_801F4FA2[];
extern u8 D_801F4FA3[];
extern void (*D_801F5010[])(void);
extern ScreenPoint D_801F501C[];
/* The script id and tile-mode byte tables indexed by twice the spawn row. */
extern u8          D_801F502C[];
extern u8          D_801F502D[];
extern void (*D_801F5034[])(void);
/* The world map marker rows the step handler selects by a controller mask. */
extern WorldMapMarker D_801F4FF8[6];
#define AREA_HUD_MASK_TABLE D_801F4FF8
/* func_801F3E00 */
void                  Area_DrawGradientDiamond(s16 x, s16 y);

u8   Game_FindAreaHandler(void);
void func_801F33FC(void);
/* func_801F34EC */
void Area_Update(void);
void func_801F35C0(void);
/* The value of area update step in the shared Area_Update body. */
#define AREA_UPDATE_STEP Area_DrawHud

/* func_801F390C */
void Area_DrawHudSprite(s32 x, s32 y, u32 sprite_id);

void func_801F3FF8(s16 x, s16 y);

#endif
