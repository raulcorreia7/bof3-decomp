#ifndef OVERLAY_WORLD02_AREA106_13_H
#define OVERLAY_WORLD02_AREA106_13_H

/* The world02/area106/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world02.h"

#define g_CurrentActor ((u8*)g_CurrentActor)
extern u8 D_801F3EAC[];

/* The cell the scene-flag pair selects. */
extern Cell2 D_801F4850[];

void      func_801F2F38(s32 index, s32 height);
extern u8 D_801F3E90[];

/* The four corner vectors RotTransPers4 projects; g_ScratchPadVectors forwards. */

/* The corner x, y and signed depth bytes of the four tiles a quad call draws, the
 * tile ids it walks, and the part word and depth scale of each tile. */
extern u8  D_801F3EE8[];
extern u8  D_801F3F18[];
extern u32 D_801F3F20[];
extern s8  D_801F3F30[];

/* The quad corner bytes: x, y and the signed depth of each corner. */
extern u8 D_801F3F34[];
extern u8 D_801F3F35[];
extern u8 D_801F3F36[];

/* The quad part word: the tag in the high half, the tile in the low half. */
#define AREA106_QUAD_PART_WORD ((0xBB00u << 16) | 0x9120u)

/* The bits of a tile word a depth-scaled offset may change. */
#define AREA106_TILE_WORD_MASK (0xFFF8u << 16)

void func_801F31DC(s32 depth, s32 height);

#endif
