#ifndef OVERLAY_WORLD02_AREA096_13_H
#define OVERLAY_WORLD02_AREA096_13_H

/* The world02/area096/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

extern u8 D_801F3614[];

/* The cell each of the payload's fifteen quads is drawn at: x, y and a signed z. */
typedef struct AreaQuadCell {
    u8 x;
    u8 y;
    s8 z;
} AreaQuadCell;

ASSERT_SIZE(AreaQuadCell, 3);

extern AreaQuadCell D_801F3624[];

/* The payload's fifteen quad cells, three bytes each. */
#define AREA_PAYLOAD_QUAD_COUNT 15

/* The packed part word the payload quads are queued with: the tag in the high half, the first
 * tile of the bundle's tile table in the low half. */
#define AREA_QUAD_PART_TAG      (0xB600u << 16)
#define AREA_QUAD_PART_TILE     0xB102u
#define AREA_QUAD_PART_WORD     (AREA_QUAD_PART_TAG | AREA_QUAD_PART_TILE)

extern SVECTOR D_1F800014[];

void func_801F2ECC(s32 depth, s32 height);

#endif
