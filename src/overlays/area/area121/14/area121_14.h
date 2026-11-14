#ifndef OVERLAY_WORLD03_AREA121_14_H
#define OVERLAY_WORLD03_AREA121_14_H

/* The world03/area121/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "common/vector.h"
#include "sys/actor.h"
#include "overlays/area/world03.h"
#include "area/spad.h"
#include <rand.h>

extern SVECTOR  D_1F800014[];
extern u8       D_801F64D8[];
extern u8       D_801F64E8[];
extern u8       D_801F64E9[]; /* the y byte of each D_801F64E8 row */
/* The area ids the message step looks the current area up in. */
extern u16      D_801F67BC[4];
extern Callback D_801F67C4[];
extern Callback D_801F67D8[];
extern Callback D_801F67E0[];
extern Callback D_801F67F0[];
extern u8       D_801F6800[]; /* one four-byte sprite cell per id: w, h, u0, v0 */
#define AREA_HUD_SPRITE_CELLS D_801F6800
extern WorldMapMarker D_801F6858[6];
#define AREA_HUD_MASK_TABLE D_801F6858
extern s8       g_GameRequestKind;
extern s8       D_80146865;
extern s8       D_80146866;
extern s8       D_80146874;
extern s8       D_80146875;
extern Callback D_801F6870[];
extern Point2u  g_FlockVelocity[4];
extern u8       g_FlockScript[4][2];
extern Callback D_801F6894[];
extern Callback D_801F689C[];

/* func_801F35D0 */
void Area_Update(void);
void func_801F5380(void);
void func_801F595C(s32 value, s32 flag);
void func_801F5B90(void);

s32 func_801A79A4(s32, s32);

u8 func_801F5028(s32 x, s32 y, u8 dir);

void func_801F5C7C(void);

#define AREA_TURN_SYNC func_801F5C7C

void func_801F4B4C(s32 arg0);
void func_801F60F4(void* arg0);

extern u8 D_801F68B8[];

#endif
