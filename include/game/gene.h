#ifndef GAME_GENE_H
#define GAME_GENE_H

#include "types.h"
#include "game/enemy.h"

/* Gene slots in the per-gene tables; EMPTY is outside the id range. */
#define GENE_ID_COUNT           18

/* Affinity columns per gene row. */
#define AFFINITY_COUNT          14

/* Runtime dragon state: the selected id, the companion byte copied from D_800B4D4C. */
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

/* Gene ids as the battle tables index them; the patch-gated Flame area record (0x21) has no slot here. */
typedef enum GeneId {
    GENE_FLAME    = 0,
    GENE_FROST    = 1,
    GENE_THUNDER  = 2,
    GENE_SHADOW   = 3,
    GENE_RADIANCE = 4,
    GENE_FORCE    = 5,
    GENE_DEFENDER = 6,
    GENE_ELDRITCH = 7,
    GENE_MIRACLE  = 8,
    GENE_GROSS    = 9,
    GENE_THORN    = 10,
    GENE_REVERSE  = 11,
    GENE_MUTANT   = 12,
    GENE_UNKNOWN  = 13,
    GENE_TRANCE   = 14,
    GENE_FAILURE  = 15,
    GENE_FUSION   = 16,
    GENE_INFINITY = 17,
    GENE_EMPTY    = 0xFF,
} GeneId;

/* Dragon form ids the predetermined gene rows select: D_800B4D58 row + 4. */
typedef enum DragonForm {
    DRAGON_FORM_TRUE_KAISER    = 4,  /* Infinity, Trance, Radiance */
    DRAGON_FORM_TRYGON         = 5,  /* Flame, Frost, Thunder */
    DRAGON_FORM_WILDFIRE       = 6,  /* Miracle, Reverse, Thorn */
    DRAGON_FORM_FAILURE_KAISER = 7,  /* Infinity, Failure */
    DRAGON_FORM_BERSERK_KAISER = 8,  /* Infinity */
    DRAGON_FORM_WHELP          = 9,  /* Failure */
    DRAGON_FORM_HYBRID         = 10, /* Fusion */
    DRAGON_FORM_TIAMAT         = 11, /* Shadow, Trance */
    DRAGON_FORM_MYRMIDON       = 12, /* Force, Trance */
    DRAGON_FORM_MAMMOTH        = 13, /* Miracle, unnamed gene */
    DRAGON_FORM_PYGMY          = 14, /* Mutant, unnamed gene */
} DragonForm;

/* Affinity columns, in the order the dragon-id selection reads them. */
typedef enum GeneAffinity {
    AFFINITY_FLAME        = 0,
    AFFINITY_FROST        = 1,
    AFFINITY_THUNDER      = 2,
    AFFINITY_SHADOW       = 3,
    AFFINITY_RADIANCE     = 4,
    AFFINITY_HP           = 5,
    AFFINITY_POWER        = 6,
    AFFINITY_DEFENSE      = 7,
    AFFINITY_SPEED        = 8,
    AFFINITY_INTELLIGENCE = 9,
    AFFINITY_DRAGON       = 10,
    AFFINITY_WARRIOR      = 11,
    AFFINITY_COUNTER      = 12,
    AFFINITY_BEHEMOTH     = 13,
} GeneAffinity;

typedef struct Gene {
    u8 gene_index;
} Gene;

ASSERT_SIZE(Gene, GENE_OBJECT_SIZE);

typedef struct Chrysm {
    u8 gene_index;
} Chrysm;

ASSERT_SIZE(Chrysm, CHRYSM_OBJECT_SIZE);

/* The ten per-gene pointers. */
typedef struct DragonPointers {
    u32 pointer[10];
} DragonPointers;

ASSERT_SIZE(DragonPointers, DRAGON_POINTERS_SIZE);

/* 0x800B4EE0: per-form multipliers plus nine resistances. */
typedef struct DragonFormStats {
    u8 mult[5];
    u8 resist[RES_INDEX_COUNT];
} DragonFormStats;

ASSERT_SIZE(DragonFormStats, DRAGON_FORM_STATS_SIZE);
ASSERT_OFFSET(DragonFormStats, resist, 0x05);

/* 0x800B4C7C: per-gene AP cost, 8-bit entries. */
extern const u8 D_800B4C7C[GENE_ID_COUNT];
/* 0x800B4D4C / 0x800B4D58: 11 predetermined forms; 0xFF is a wildcard gene and the dragon id is `row + 4`. */
extern const u8 D_800B4D4C[11];
extern const u8 D_800B4D58[11][3];
/* 0x800B4E8C: affinity-level bonus in ten-point steps, indexed by `clamp(affinity_level + 2, 0, 4)`. */
extern const s8 D_800B4E8C[5];
/* 0x800B4EA4: base ability ids for the four non-predetermined forms. */
extern const u8 D_800B4EA4[4][3];
/* 0x800B4EB0: ability ids per affinity combination, 15 rows of three. */
extern const u8 D_800B4EB0[15][3];

#endif
