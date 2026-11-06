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
 * "Pond" is the community word for the array (bof3-notes), not a retail string. The pond rows are the actor rows: the
 * table at `0x80146888` is the 30-row entity table (`include/work/actor.h`), and the fishing code reads the stamina,
 * facing and fish bytes of its rows.
 */

#include "types.h"

/*
 * Fishing state. The selector bytes and both table bases are proven in the
 * matched world00/area030/04 code: `lure_table + lure * 20` and `rod_table + rod * 10`
 * (func_801DDE2C). The reference notes give the same record strides at
 * different RAM addresses (0x801E2914 / 0x801E2950); those stay unverified
 * here. Record fields come from @source: wiki:data/field#fairy-village-and-fishing.
 */

#define FISHING_LURE                       0x80145026u
#define FISHING_LURE_QTY                   0x80145027u /* lures held; func_8016628C adds it to the lure's item count */
#define FISHING_ROD                        0x80145028u

#define FISHING_ROD_TABLE                  0x801E2748u
#define FISHING_LURE_TABLE                 0x801E2720u

/* One byte per fish, index order shared with the count table. */
#define FISHING_CATCH_SAVE_OFFSET          0x90Cu

#define FISHING_RECORD_COUNT               32 /* func_801E0B6C walks all 32 bytes */
/* [inferred] the six rod accessories, ids 46 to 51; no code bounds the rod selector. */
#define FISHING_ROD_COUNT                  6
#define FISHING_ROD_STRIDE                 0x0a
#define FISHING_LURE_STRIDE                0x14
#define FISHING_POND_STRIDE                0x98 /* the field work row size */
#define FISHING_POND_ROWS                  30   /* the field work table's row count */

/* Lure rows are 20 bytes. The notes span the three float-rate groups as
 * `+1..3`, `+4..7`, and `+8..11` while calling each a 16-bit value, so the
 * groups keep their byte spans and their widths stay unresolved. */
#define FISHING_LURE_IDLE_FLOAT_OFFSET     0x01u
#define FISHING_LURE_REELING_FLOAT_OFFSET  0x04u
#define FISHING_LURE_SIDEWAYS_FLOAT_OFFSET 0x08u

/* D_80144FE4 */
extern u8 g_FishBestCatch[FISHING_RECORD_COUNT];

#endif
