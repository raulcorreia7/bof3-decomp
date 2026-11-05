#ifndef OVERLAY_WORLD02_AREA104_14_H
#define OVERLAY_WORLD02_AREA104_14_H

/* The world02/area104/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "work/area_spad.h"

extern SVECTOR  D_1F800014[];
extern s32      D_80145EC4;
extern u8       D_801F6980[];
extern Callback D_801F6A64[];
extern u8       D_801F6A78[];
extern u8       D_801F6A80[];
extern u8       D_801F6A90[];
/* The map arrow sprite's width, height, u and v per sprite id. */
extern u8       D_801F6AA0[];
extern u8       D_801F6B10[];
extern u8       D_801F6B18[];

/* func_801F367C */
void Area_Update(void);
/* func_801F3BC4 */
void Area_DrawHud(s16 x, s16 y);
/* func_801F4188 */
void Area_DrawHudBanner(s16 x, s16 y);
void func_801F4E3C(void);
void func_801F5254(void);
void func_801F564C(void);
void func_801F5738(void);
/* func_801F5988 */
s32  Area_BeginTurnStep(s32 direction, s32 previous);
void Area_FinishTurnStep(void);

#define AREA_TURN_SYNC   func_801F5738

/* The value of area update step in the shared Area_Update body. */
#define AREA_UPDATE_STEP Area_DrawHud

extern WorldMapMarker D_801F6AF8[6];
#define AREA_HUD_MASK_TABLE D_801F6AF8
extern u16            g_GameAreaId;
extern u16            D_80143F22;
extern s8             g_GameRequestKind;
/* func_801F3A9C */
void                  Area_DrawHudSprite(s32 x, s32 y, u32 sprite_id);
/* func_801F3F90 */
void                  Area_DrawGradientDiamond(s16 x, s16 y);

void func_8015A944(void);

void func_801F656C(void);

s32 func_801F4AE4(s32, s32, s32);

s32 func_801A79A4(s32 handler_x, s32 handler_y);

#endif
