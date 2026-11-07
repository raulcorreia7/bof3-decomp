#ifndef SLUS_PART_H
#define SLUS_PART_H

#include "types.h"

/* The z/y/x vertex view of one part word: the part functions double the signed
 * byte offsets x and y around the projected origin and take the depth word
 * through `raw` (func_80156000, func_80156228, func_8015707C). */
typedef struct {
    s16 z;
    s8  y;
    s8  x;
} PartCell;

/* One word of a scene part list: a packed cell, the record header (id and
 * run count), the four colour bytes of a part, or a run's frame pick. */
typedef union ScenePart {
    u32      raw;
    PartCell vertex;

    struct {
        s16 id;
        u8  count;
        u8  unk_03;
    } head;

    struct {
        u8 b;
        u8 g;
        u8 r;
        u8 tpage;
    } color;

    struct {
        u8 table;
        u8 extra;
        u8 limit[2];
    } pick;
} ScenePart;

#endif
