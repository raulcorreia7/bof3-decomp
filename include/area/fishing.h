#ifndef AREA_FISHING_H
#define AREA_FISHING_H

/* The fishing tables:
 *
 * | Table | Address | Record | Rows | Reader |
 * | --- | --- | ---: | ---: | --- |
 * | rod table | `0x801E2748` | 10 bytes | — | `emi/world00/area030/04@0x801DDE2C` |
 * | lure table | `0x801E2720` | 20 bytes | — | `emi/world00/area030/04@0x801DDE2C` |
 * | pond rows | `0x80146888` | 0x98 bytes | 30 | `emi/world00/area030/04@0x801DBBAC`, `@0x801E026C`, `@0x801DE5EC` |
 * | caught-fish bytes | `0x80144FE4` | 1 byte | — | `emi/world00/area030/04@0x801D5048`, `@0x801D4884`, `@0x801DB554` |
 *
 * A pond is an entity-table record (`include/sys/actor.h`, 30 records at `0x80146888`); the fishing code reads the
 * stamina, facing and fish bytes of each. "Pond" is a community name, not a retail string.
 */

#include "types.h"

/*
 * Fishing state. The code addresses `lure_table + lure * 20` and `rod_table + rod * 10`
 * (func_801DDE2C). Other references give the same record strides at RAM addresses
 * 0x801E2914 and 0x801E2950; these are unverified. Record fields:
 * @source: wiki:data/field#fairy-village-and-fishing.
 */

/* The equipped lure, how many of it are held, and the equipped rod. */
typedef struct FishingEquipment {
    /* 0x00 */ u8 lure_id;    /* accessory id; its row is the FISHING_LURE_STRIDE entry of the lure table */
    /* 0x01 */ u8 lure_count; /* lures held; Item_Count adds it to the lure's item count */
    /* 0x02 */ u8 rod_id;     /* accessory id; its row is the FISHING_ROD_STRIDE entry of the rod table */
} FishingEquipment;

ASSERT_OFFSET(FishingEquipment, lure_id, 0x00);
ASSERT_OFFSET(FishingEquipment, lure_count, 0x01);
ASSERT_OFFSET(FishingEquipment, rod_id, 0x02);
ASSERT_SIZE(FishingEquipment, 0x03);

/* D_80145026 */
extern FishingEquipment g_FishingEquipment;

#define FISHING_ROD_TABLE                  0x801E2748u
#define FISHING_LURE_TABLE                 0x801E2720u

/* One byte per fish, index order shared with the count table. */
#define FISHING_CATCH_SAVE_OFFSET          0x90Cu

#define FISHING_RECORD_COUNT               32 /* func_801E0B6C walks all 32 bytes */
/* [inferred] the six rod accessories, ids 46 to 51; no code bounds the rod selector. */
#define FISHING_ROD_COUNT                  6
#define FISHING_ROD_STRIDE                 0x0a
#define FISHING_LURE_STRIDE                0x14
#define FISHING_POND_STRIDE                0x98 /* size of one entity-table record */
#define FISHING_POND_ROWS                  30   /* entity-table record count */

/* Lure rows are 20 bytes. The notes span the three float-rate groups as
 * `+1..3`, `+4..7`, and `+8..11` while calling each a 16-bit value, so the
 * groups keep their byte spans and their widths stay unresolved. */
#define FISHING_LURE_IDLE_FLOAT_OFFSET     0x01u
#define FISHING_LURE_REELING_FLOAT_OFFSET  0x04u
#define FISHING_LURE_SIDEWAYS_FLOAT_OFFSET 0x08u

/* Rod table row; every field is one byte (@source: wiki:data/field#fairy-village-and-fishing). */
typedef struct FishingRod {
    u8 cast_power_speed;
    u8 cast_sweep_direction; /* 0 linear bidirectional, 1 linear
                                   unidirectional, 2 quadratic bidirectional */
    u8 max_distance;         /* half the value in metres */
    u8 reel_cursor_size;
    s8 cursor_return_speed;
    s8 cursor_left_speed;
    s8 cursor_right_speed;
    s8 unk_07;
    u8 snap_left_tension;
    u8 snap_right_tension;
} FishingRod;

ASSERT_SIZE(FishingRod, FISHING_ROD_STRIDE);

typedef struct FishingLure {
    u8 unk_00;
    u8 idle_float[3];
    u8 reeling_float[4];
    u8 sideways_float[4];
    u8 unk_0C[8];
} FishingLure;

ASSERT_SIZE(FishingLure, FISHING_LURE_STRIDE);
ASSERT_OFFSET(FishingLure, idle_float, FISHING_LURE_IDLE_FLOAT_OFFSET);
ASSERT_OFFSET(FishingLure, reeling_float, FISHING_LURE_REELING_FLOAT_OFFSET);
ASSERT_OFFSET(FishingLure, sideways_float, FISHING_LURE_SIDEWAYS_FLOAT_OFFSET);

/* D_80144FE4 */
extern u8 g_FishingBestCatch[FISHING_RECORD_COUNT];

#endif
