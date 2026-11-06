#ifndef GAME_GENE_H
#define GAME_GENE_H

#include "types.h"
#include "game/enemy.h"

/* Gene slots in the per-gene tables; EMPTY is outside the id range. */
#define GENE_TYPE_COUNT         18

/* Affinity columns per gene row. */
#define AFF_COUNT               14

/* Runtime dragon state: the selected id, the companion byte copied from
 * D_800B4D4C, and the signed affinity accumulator over AFF_* columns. */
#define BATTLE_DRAGON_ID        0x800B6F58u
#define BATTLE_DRAGON_COMPANION 0x800B6F5Cu
#define BATTLE_GENE_AFFINITY    0x800B6F60u

#define GENE_OBJECT_SIZE        0x01

#define CHRYSM_OBJECT_SIZE      0x01

#define DRAGON_POINTERS_SIZE    0x28

#define DRAGON_FORM_STATS_SIZE  0x0E

/*
 * Dragon-gene and dragon-form tables that ship in BATTLE.EMI entry 15 and are
 * byte-identical in the boss overlays. Load-time RAM addresses; the archive
 * offset is `ram - 0x80096800 + 0x8A000`.
 *
 * See @source: wiki:data/records#area-data for the affinity
 * values and the two rows the accumulation loop never reads.
 */

/* Gene ids as the battle tables index them; the patch-gated Flame area record
 * (0x21) has no slot here. */
typedef enum GeneType {
    GENE_FLAME    = 0x00,
    GENE_FROST    = 0x01,
    GENE_THUNDER  = 0x02,
    GENE_SHADOW   = 0x03,
    GENE_RADIANCE = 0x04,
    GENE_FORCE    = 0x05,
    GENE_DEFENDER = 0x06,
    GENE_ELDRITCH = 0x07,
    GENE_MIRACLE  = 0x08,
    GENE_GROSS    = 0x09,
    GENE_THORN    = 0x0A,
    GENE_REVERSE  = 0x0B,
    GENE_MUTANT   = 0x0C,
    GENE_UNKNOWN  = 0x0D,
    GENE_TRANCE   = 0x0E,
    GENE_FAILURE  = 0x0F,
    GENE_FUSION   = 0x10,
    GENE_INFINITY = 0x11,
    GENE_EMPTY    = 0xFF,
} GeneType;

/* Affinity columns, in the order the dragon-id selection reads them: five
 * elements, then five stats, then the four form affinities. */
typedef enum GeneAffinity {
    AFF_FLAME        = 0x00,
    AFF_FROST        = 0x01,
    AFF_THUNDER      = 0x02,
    AFF_SHADOW       = 0x03,
    AFF_RADIANCE     = 0x04,
    AFF_HP           = 0x05,
    AFF_POWER        = 0x06,
    AFF_DEFENSE      = 0x07,
    AFF_SPEED        = 0x08,
    AFF_INTELLIGENCE = 0x09,
    AFF_DRAGON       = 0x0A,
    AFF_WARRIOR      = 0x0B,
    AFF_COUNTER      = 0x0C,
    AFF_BEHEMOTH     = 0x0D,
} GeneAffinity;

typedef struct Gene {
    u8 gene_index;
} Gene;

ASSERT_SIZE(Gene, GENE_OBJECT_SIZE);

typedef struct Chrysm {
    u8 gene_index;
} Chrysm;

ASSERT_SIZE(Chrysm, CHRYSM_OBJECT_SIZE);

/* 0x800B4C7C: per-gene AP cost, 8-bit entries. */
extern const u8 D_800B4C7C[GENE_TYPE_COUNT];
/* 0x800B4D4C / 0x800B4D58: 11 predetermined forms; 0xFF is a wildcard gene and
 * the dragon id is `row + 4`. D_800B4D58 is read as [selection id][slot]. */
extern const u8 D_800B4D4C[11];
extern const u8 D_800B4D58[11][3];
/* 0x800B4E8C: affinity-level bonus in ten-point steps, indexed by
 * `clamp(affinity_level + 2, 0, 4)`. */
extern const s8 D_800B4E8C[5];
/* 0x800B4EA4: base ability ids for the four non-predetermined forms. */
extern const u8 D_800B4EA4[4][3];
/* 0x800B4EB0: ability ids per affinity combination, 15 rows of three. */
extern const u8 D_800B4EB0[15][3];

#endif
