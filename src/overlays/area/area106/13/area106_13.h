#ifndef OVERLAY_WORLD02_AREA106_13_H
#define OVERLAY_WORLD02_AREA106_13_H

/* The world02/area106/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

#define g_CurrentActor ((u8*)g_CurrentActor)

/* The X and Y cell columns the scene-flag pair selects. */
extern u8 D_801F4850[];
extern u8 D_801F4851[];
extern u8 D_801F3EAC[];

void      func_801F2F38(s32 arg0, s32 arg1);
extern u8 D_801F3E90[];

/* The four corner vectors RotTransPers4 projects; g_ScratchPadVectors forwards. */

/* The quad corner bytes: x, y and the signed depth of each corner. */
extern u8 D_801F3F34[];
extern u8 D_801F3F35[];
extern u8 D_801F3F36[];

/* The quad part word: the tag in the high half, the tile in the low half. */
#define AREA106_QUAD_PART_WORD ((0xBB00u << 16) | 0x9120u)

void func_801F31DC(s32 depth, s32 height);

#endif
