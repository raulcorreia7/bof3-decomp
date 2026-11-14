#ifndef OVERLAY_BMAGIC_MAGIC102_03_H
#define OVERLAY_BMAGIC_MAGIC102_03_H

/* The bmagic/magic102/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"
#include "slus/exports.h"
#include "slus/functions.h"
#include "slus/part.h"

extern SVECTOR D_1F800014[];
/* D_1F800034 read unsigned: the screen x and y RotTransPers writes. */
extern u16     D_1F800034_U16[2];

s32 func_801F0ADC(s32 x, s32 y);

extern Magic010SharedSteps D_801EEC04;

/* This effect steps the shared tick counter (unk_09) by one per
 * step and advances the magic step at its limit. */
#define EFFECT_TICK_INCREMENT 1
#define EFFECT_TICK_LIMIT     0x10

/* The four field actor rows that follow g_Actors. */
extern Actor D_80147A58[4];


/* The caster's facing, the flag func_801EEC80 raises for encounters 0x1C, 0x23, 0x2F and 0x34, and the
 * target cell the effect starts from. */
extern u8  D_801F0CBC;
extern u8  D_801F0CC0;
extern s16 D_801F0CC4;
extern s16 D_801F0CC8;
/* Per facing (D_801F0CBC >> 1): the divisor of the rise at each step from the target cell. */
extern u8  D_801F0C9C[2][15];
extern s8  D_801F0CCC[17][15];
extern s8  D_801F0DCC[16][15];
/* The height of each party member, enemy, field actor, actor row and actor slot over the ground. */
extern s16 D_801F0ECC[3];
extern s16 D_801F0ED4[30];
extern s16 D_801F0F10[4];
extern s16 D_801F0F18[20];
extern s16 D_801F0F40[8];
extern s16 D_801F0F50[8];

/* The map bundle read through its base address as a number (the retail code loads the constant,
 * not the g_AreaMapBundle symbol): its width, and height byte k of the cell at (row, col). */
#define MAP_BUNDLE_WIDTH             (((AreaMapBundle*)MAP_BUNDLE_BASE)->width)
#define MAP_CELL_CORNER(row, col, k) (((u8*)(MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE))[((col) + (row) * MAP_BUNDLE_WIDTH) * 4 + (k)])

#endif
