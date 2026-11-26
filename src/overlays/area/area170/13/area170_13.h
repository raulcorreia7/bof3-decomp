#ifndef OVERLAY_WORLD04_AREA170_13_H
#define OVERLAY_WORLD04_AREA170_13_H

/* The world04/area170/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world04.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0xC0

/* The map bundle's height and grid offset, and the cell table after it. */
extern u8   D_80104001;
extern u16  D_80104002;
extern u8   D_8010402C[];
extern void func_801F3994(void);

/* The scratchpad cell holding this mode's work pointer. */

/* The overlay's flag word. */

/* The game-overlay state bytes the request writes. */

/* The shared game work word the flag mask sets. */

/* The party position in 16.16 fixed point. */
/* The payload includes the per-state handler tables. */
extern u8 D_801F57BC[];

/* The per-cell tile bytes and the cell primitives. */
extern u8  D_801F57CC[2][7][9];
extern u8  D_801F584C[7][9];
extern u32 D_801F58C8[];
extern s8  D_801F58D0[3][7][9];
extern u8  D_801F5990[];

extern u8 D_801F64B8[];

void func_801F2FA0(s16 x, s16 y, s8* glyphs, u8 phase);
void func_801F31DC(s16 x, s16 y);
void func_801F3594(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, s16 x3, s16 y3, u8 r, u8 g, u8 b, u8 semi_trans);
void func_801F3698(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, u8 r, u8 g, u8 b, u8 semi_trans);
void func_801F3774(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b, u8 semi_trans);
void func_801F3838(u16 line_index);
void func_801F388C(s32 x, s32 y, s8 type);
void func_801F4640(s32 sample_height);

/* The row scale bytes the floor quad multiplies by. */
extern u8 D_801F58B8[];

#endif
