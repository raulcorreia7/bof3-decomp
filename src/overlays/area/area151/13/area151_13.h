#ifndef OVERLAY_WORLD03_AREA151_13_H
#define OVERLAY_WORLD03_AREA151_13_H

/* The world03/area151/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "work/area_spad.h"

#define D_801F4D04 (D_801F4CE8 + 0x1Cu)
#define D_801F4D05 (D_801F4CE8 + 0x1Du)
#define D_801F5468 (D_801F4CE8 + 0x780u)
#define AREA_HUD_SPRITE_CELLS D_801F5468

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

extern SVECTOR     D_1F800014[];
/* The world-area state byte tested by the work handlers. */
extern s32         D_80145EC4[];
extern u8          D_801F4CE8[];
/* The request selector and the area request slot. */
extern Callback    D_801F542C[];
/* The state handler tables the dispatchers index. */
extern Callback    D_801F5440[];
extern Callback    D_801F5448[];
extern Callback    D_801F5458[];
extern Callback    D_801F54D8[];
extern ScreenPoint D_801F54E4[];
extern u8          D_801F54F4[];
extern u8          D_801F54F5[];
extern Callback    D_801F54FC[];

/* The work-mode steps the request wrapper runs. */

u8   Game_FindAreaHandler(void);
void func_801F3438(void);
/* The origin pan step the handler enters. */
/* func_801F3528 */
void Area_Update(void);
/* The origin pan step the handler enters. */
/* func_801F3A70 */
void Area_DrawHud(s16 x, s16 y);
/* func_801F4034 */
void Area_DrawHudBanner(s16 x, s16 y);
/* The value of area update step in the shared Area_Update body. */
#define AREA_UPDATE_STEP Area_DrawHud

extern WorldMapMarker D_801F54C0[6];
#define AREA_HUD_MASK_TABLE D_801F54C0
/* func_801F3948 */
void                  Area_DrawHudSprite(s32 x, s32 y, u32 sprite_id);
/* func_801F3E3C */
void                  Area_DrawGradientDiamond(s16 x, s16 y);

#endif
