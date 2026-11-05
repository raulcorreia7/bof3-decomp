#ifndef OVERLAY_WORLD01_AREA065_13_H
#define OVERLAY_WORLD01_AREA065_13_H

/* The world01/area065/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "work/area_spad.h"

void Area_SetCellCode(s16 column, s16 row, u8 code);

extern SVECTOR D_1F800014[];
extern s32     D_80145EC4[];
extern u8      D_801F4DB4[];
#define AREA_HUD_SPRITE_CELLS ((u8*)D_801F4DB4 + 0x4FC)
/* The spawn step handler table indexed by the record's step byte. */
extern Callback    D_801F5274[];
extern u8          D_801F5288[];
extern u8          D_801F5290[];
extern u8          D_801F52A0[];
extern u8          D_801F5320[];
/* The signed spawn focus offsets, one (x, y) pair per spawn row. */
extern ScreenPoint D_801F532C[];
/* The script id and tile-mode byte tables indexed by twice the spawn row. */
extern u8          D_801F533C[];
extern u8          D_801F533D[];
extern u8          D_801F5344[];

/* func_801F3A10 */
void        Area_DrawHudSprite(s32 x, s32 y, u32 sprite_id);
extern void Area_DrawHud(s16 x, s16 y);

/* The value of area update step in the shared Area_Update body. */
#define AREA_UPDATE_STEP Area_DrawHud

extern WorldMapMarker D_801F5308[6];
#define AREA_HUD_MASK_TABLE D_801F5308
/* func_801F3F04 */
void Area_DrawGradientDiamond(s16 x, s16 y);

extern WorldMapPoint D_801F4DE0[];
extern u16           D_801F50FC[5][16];
extern u8            D_801F525C[12];
extern u8            D_801F525D[];
extern u8            D_801F5268[]; /* the "Manillo" text at +0x10 */

void func_801F40FC(s16 x, s16 y);
void Area_Update(void);

#endif
