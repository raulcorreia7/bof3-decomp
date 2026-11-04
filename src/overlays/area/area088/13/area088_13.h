#ifndef OVERLAY_WORLD02_AREA088_13_H
#define OVERLAY_WORLD02_AREA088_13_H

/* The world02/area088/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "work/area_spad.h"

extern SVECTOR     D_1F800014[];
extern s32         D_80145EC4[];
extern u8          D_801F58DC[];
extern u8          D_801F5900[];
extern u8          D_801F5902[];
extern u8          D_801F591C[];
extern u8          D_801F591D[];
extern Callback    D_801F61A0[];
extern Callback    D_801F61B4[];
extern Callback    D_801F61BC[];
extern Callback    D_801F61CC[];
extern u8          D_801F61DC[];
extern u8          D_801F61DD[];
extern u8          D_801F61DE[];
extern u8          D_801F61DF[];
extern Callback    D_801F624C[];
/* The signed spawn focus offsets, one (x, y) pair per spawn row. */
extern ScreenPoint D_801F6258[];
/* The script id and tile-mode byte tables indexed by twice the spawn row. */
extern u8          D_801F6268[];
extern u8          D_801F6269[];
extern Callback    D_801F6270[];

u8   Game_FindAreaHandler(void);
void func_801F402C(void);
/* func_801F411C */
void Area_Update(void);
void func_801F41F0(void);
/* func_801F4664 */
void Area_DrawHud(s16 x, s16 y);
/* func_801F4C28 */
void Area_DrawHudBanner(s16 x, s16 y);

/* The value of area update step in the shared Area_Update body. */
#define AREA_UPDATE_STEP Area_DrawHud

extern WorldMapMarker D_801F6234[6];
/* func_801F453C */
void                  Area_DrawHudSprite(s32 x, s32 y, u32 sprite_id);
/* func_801F4A30 */
void                  Area_DrawGradientDiamond(s16 x, s16 y);

extern u16 D_801F6090[5][16];
extern u8  D_801F6170[12];
extern u8  D_801F6171[];
extern u8  D_801F6194[]; /* the "Manillo" text at +0x10 */

void func_801F2F28(u8* window);

void func_801F3258(u8* window);

extern u16 D_800E4B3E;

#endif
