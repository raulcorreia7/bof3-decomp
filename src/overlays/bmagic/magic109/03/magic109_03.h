#ifndef OVERLAY_BMAGIC_MAGIC109_03_H
#define OVERLAY_BMAGIC_MAGIC109_03_H

/* The bmagic/magic109/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Magic010SharedSteps D_801EEC04;

void func_801EF0F8(s32 offset);

/* The screen point the effect starts from, by g_Battle.scroll_dir. */
extern Point2l D_801EF9D8[];

/* The outer rim the quads draw from: sixteen vertices, a pair of s32
 * coordinates each. */
extern u8 D_801EF9F8[];
/* The y of each rim vertex; D_801EF9F8 holds the x. */
extern u8 D_801EF9FC[];
/* The spiral the rings twist: sixteen vertices, a pair of s32 coordinates
 * each, turned by the ring's angle. */
extern u8 D_801EFA78[];
/* The y of each spiral vertex; D_801EFA78 holds the x. */
extern u8 D_801EFA7C[];
/* The radial mesh the effect builds each frame: nine rings of sixteen
 * vertices, a pair of s32 coordinates each; the ring sets the radius. */
extern u8 D_801EFAF8[];
/* The y of each mesh vertex; D_801EFAF8 holds the x. */
extern u8 D_801EFAFC[];

#endif
