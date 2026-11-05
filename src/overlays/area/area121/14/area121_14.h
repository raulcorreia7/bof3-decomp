#ifndef OVERLAY_WORLD03_AREA121_14_H
#define OVERLAY_WORLD03_AREA121_14_H

/* The world03/area121/14 overlay: one file per split function
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
extern u8             D_801F64D8[];
extern u8             D_801F64E8[];
extern u8             D_801F64E9[]; /* the y byte of each D_801F64E8 row */
extern Callback       D_801F67C4[];
extern Callback       D_801F67D8[];
extern Callback       D_801F67E0[];
extern Callback       D_801F67F0[];
extern u8             D_801F6800[]; /* one four-byte sprite cell per id: w, h, u0, v0 */
extern WorldMapMarker D_801F6858[6];
#define AREA_HUD_MASK_TABLE D_801F6858
extern Callback       D_801F6870[];
extern AreaSpawnPoint D_801F687C[];
extern u8             D_801F688C[];
extern u8             D_801F688D[]; /* the script-argument byte at +1 */
extern Callback       D_801F6894[];
extern Callback       D_801F689C[];
extern s8             D_80146865;
extern s8             D_80146866;
extern u8             D_80146867;
extern s8             D_80146874;
extern s8             D_80146875;
extern u16            g_GameAreaId;
extern u16            D_80143F22;
extern s8             g_GameRequestKind;

void func_8015A944(void);
u8   Game_FindAreaHandler(void);
/* func_801F35D0 */
void Area_Update(void);
/* func_801F39F0 */
void Area_DrawHudSprite(s32 x, s32 y, u32 sprite_id);
/* func_801F3B18 */
void Area_DrawHud(s16 x, s16 y);
void Area_DrawGradientDiamond(s16 x, s16 y);
/* func_801F40DC */
void Area_DrawHudBanner(s16 x, s16 y);
void func_801F5380(void);
void func_801F5798(void);
void func_801F5B90(void);

/* The value of area update step in the shared Area_Update body. */
#define AREA_UPDATE_STEP Area_DrawHud

s32 func_801F5028(s32, s32, s32);

s32 func_801A79A4(s32, s32);

/* func_801F5ECC */
s32  Area_BeginTurnStep(s32 direction, s32 previous);
void func_801F5C7C(void);
void Area_FinishTurnStep(void);

#define AREA_TURN_SYNC func_801F5C7C

#endif
