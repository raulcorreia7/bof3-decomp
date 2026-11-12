#ifndef OVERLAY_WORLD02_AREA104_14_H
#define OVERLAY_WORLD02_AREA104_14_H

/* The world02/area104/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

void func_801F358C(void);

extern SVECTOR  D_1F800014[];
extern u8       D_801F6980[];
extern Callback D_801F6A64[];
extern u8       D_801F6A78[];
extern u8       D_801F6A80[];
extern u8       D_801F6A90[];
/* The map arrow sprite's width, height, u and v per sprite id. */
extern u8       D_801F6AA0[];
#define AREA_HUD_SPRITE_CELLS D_801F6AA0
extern u8 D_801F6B10[];
extern u8 D_801F6B18[];

void func_801F5418(s32 value, s32 flag);
void func_801F555C(s16 x, s16 y, u8 row);

/* func_801F367C */
void Area_Update(void);
/* func_801F3BC4 */
void func_801F4E3C(void);
void func_801F564C(void);
void func_801F5738(void);

#define AREA_TURN_SYNC       func_801F5738
#define AREA_MESSAGE_REQUEST 4 /* the message Message_RunAreaMessage starts */

/* The value of area update step in the shared Area_Update body. */

extern WorldMapMarker D_801F6AF8[6];
#define AREA_HUD_MASK_TABLE D_801F6AF8
extern s8 g_GameRequestKind;

s32 func_801A79A4(s32 handler_x, s32 handler_y);

u8 func_801F4AE4(s32, s32, s32);

void func_801F656C(void);

void func_801F4608(s32 arg0);
void func_801F5BB0(s32 arg0);

#endif
