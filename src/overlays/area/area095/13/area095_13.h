#ifndef OVERLAY_WORLD02_AREA095_13_H
#define OVERLAY_WORLD02_AREA095_13_H

/* The world02/area095/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world02.h"

extern u8           D_801F3684[];
/* The cell each of the payload's fifteen quads is drawn at. */
extern AreaQuadCell D_801F3694[];

/* The quad part word: the tag in the high half, the tile in the low half. */
#define AREA095_QUAD_PART_WORD  ((0xB600u << 16) | 0xB102u)

/* The payload's fifteen quad cells, three bytes each. */
#define AREA_PAYLOAD_QUAD_COUNT 15

void func_801F2F3C(s32 depth, s32 height);
void func_801F2C48(void);

#endif
