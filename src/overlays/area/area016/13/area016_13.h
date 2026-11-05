#ifndef OVERLAY_WORLD00_AREA016_13_H
#define OVERLAY_WORLD00_AREA016_13_H

/* The area016 world overlay's local declarations: its work record, spawn and
 * marker tables, and the handlers its units share. Only this image includes
 * the file. */

#include "overlays/area/world00.h"
#include "work/area_spad.h"
#include <abs.h>

#define AREA_SCENE_RECORD    0xF

/* Signed spawn offsets (func_801F42F8) as u16 words: 0x2000 and -0x2000. */
#define SPAWN_OFFSET_FORWARD 0x2000u
#define SPAWN_OFFSET_BACK    0xE000u

/* The overlay's data block at 0x801F4DA0..0x801F51E0 is one variable per
 * table, in retail address order, in D_801F4DA0_Data.c. */

/* Data, in address order. */
extern SVECTOR       D_1F800014[];
extern s32           D_80145EC4[];
/* The steppers that must reload the cell after every store select the
 * volatile declaration. */
extern WorldMapKey   D_801F4D7C[9];
extern WorldMapPoint D_801F4DA0[137];
/* Key rows: column 0 is matched against g_GameContextSeed; column g_SceneState is
 * the value Fish_LocationMessage passes on. */
extern u16           D_801F4FC4[9][16];
extern u8            D_801F50E4[28];
extern u8            D_801F50E5[]; /* the record-selector byte at +1 */
extern u8            D_801F50F4[]; /* the "Manillo" text at +0x10 */
extern Callback      D_801F5100[5];
extern Callback      D_801F5114[2];
extern Callback      D_801F511C[4];
extern Callback      D_801F512C[4];
extern u8            D_801F513C[88];
#define AREA_HUD_SPRITE_CELLS D_801F513C
extern WorldMapMarker D_801F5194[6];
#define AREA_HUD_MASK_TABLE D_801F5194
extern Callback    D_801F51AC[3];
extern ScreenPoint D_801F51B8[4];
extern u8          D_801F51C8[8];
extern u8          D_801F51C9[]; /* the second byte of each D_801F51C8 pair */
extern Callback    D_801F51D0[2];
extern u8          D_801F51D8[4];
extern u8          D_801F51DC[4];
extern u8          D_801F51E0[2];

/* func_801559AC */
POLY_FT4* Area_FindCellQuad(s32 column, s32 row);
u8        Game_FindAreaHandler(void);
void      func_801F30EC(void);
void      func_801F3224(void);
void      func_801F32A0(void);
/* func_801F3460 */
void      Actor_NextStep(void);
void      func_801F34C8(void);
/* func_801F350C */
void      Actor_SlideScreenLeft(void);
/* func_801F355C */
void      Actor_SlideScreenX(void);
/* func_801F35B8 */
void      Area_Update(void);
void      func_801F3608(void);
void      func_801F368C(void);
/* func_801F36D0 */
void      Actor_SetScreenBottom(void);
void      func_801F3828(void);
void      func_801F3928(void);
/* func_801F3B00 */
/* func_801F39D8 */
void      Area_DrawHudSprite(s32 x, s32 y, u32 sprite_id);
void      Area_DrawHud(s16 x, s16 y);
void      Area_DrawGradientDiamond(s16 x, s16 y);
void      func_801F40C4(s16 x, s16 y);
/* func_801F41BC */
void      Actor_SpawnRandomGroup(void);
void      func_801F42F8(void);
/* func_801F4528 */
void      Actor_MoveByVelocity(void);
void      func_801F4610(void);
void      Area_StepStreamSetDrawMode(void);

/* The value of func 801f2eec table in the shared func_801F2EEC body. */
#define FUNC_801F2EEC_TABLE D_801F5100

/* The value of area update step in the shared Area_Update body. */
#define AREA_UPDATE_STEP    Area_DrawHud

#endif
