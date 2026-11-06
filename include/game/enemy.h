#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

/* The enemy, encounter and treasure-chest records from the world archives,
 * and their resistance and AI blocks. battle/battle/03, battle/battle/15 and etc/game/00 read
 * them; game/records.h owns the counts and strides.
 *
 * Layout: @source: wiki:data/records#area-data (`Encounter` is eight enemy
 * indexes and an appearance rate, 9 bytes). */

#include "types.h"
#include "game/records.h"
#include "psx/mem.h"

/* One byte per resistance slot. */
#define RES_INDEX_COUNT     9

#define ENEMY_AI_BLOCK_SIZE 0x10

typedef enum EnemyId {
    ENEMY_ID_AMMONITE_ALT = 0x96,
} EnemyId;

/* Resistance arrays are nine byte slots; slot 8 has no element-mask bit.
 * Order: @source: wiki:data/records#area-data */
typedef enum ResistanceIndex {
    RES_INDEX_FIRE     = 0,
    RES_INDEX_FROST    = 1,
    RES_INDEX_ELECTRIC = 2,
    RES_INDEX_EARTH    = 3,
    RES_INDEX_WIND     = 4,
    RES_INDEX_HOLY     = 5,
    RES_INDEX_PSIONIC  = 6,
    RES_INDEX_STATUS   = 7,
    RES_INDEX_DEATH    = 8,
} ResistanceIndex;

typedef struct EnemyAIBlock {
    u8 condition;
    u8 parameters[ENEMY_AI_PARAMETER_COUNT];
    u8 skills[ENEMY_SKILL_COUNT];
} EnemyAIBlock;

ASSERT_SIZE(EnemyAIBlock, ENEMY_AI_BLOCK_SIZE);

typedef struct Enemy {
    u8           name[ENEMY_NAME_LENGTH];
    u16          enemy_id;
    u8           choice_ai;
    u8           unk_0B[3];
    u8           target_preference;
    u8           unk_0F;
    u16          zenny;
    u16          exp;
    u8           level;
    u8           unk_15[3];
    u8           initial_skills[ENEMY_SKILL_COUNT];
    u16          hp;
    u16          ap;
    u16          power;
    u16          defense;
    u16          agility;
    u16          intellect;
    u8           first_item_index;
    u8           first_item_type;
    u16          first_item_rate;
    u8           second_item_index;
    u8           second_item_type;
    u16          second_item_rate;
    EnemyAIBlock ai[ENEMY_AI_COUNT];
    u8           unk_74[4];
    u8           resistances[RES_INDEX_COUNT];
    u8           unk_81;
    u8           reach;  /* +0x82: sizes the probe step and the overlap extent of encounter placement */
    u8           height; /* +0x83: the final probe must lie this far plus 8 pixels below the screen top */
    u8           unk_84[4];
} Enemy;

ASSERT_SIZE(Enemy, ENEMY_STRIDE);

/* The enemy records in the encounter block at 0x800E4000, from block +0x48 and indexed by enemy index. */
#define ENCOUNTER_ENEMIES          MEM_PTR(Enemy, 0x800E4048u)
/* The record at a byte offset (index * ENEMY_STRIDE) from the first, for callers that keep the offset in a register. */
#define ENCOUNTER_ENEMY_AT(offset) ((Enemy*)((u8*)ENCOUNTER_ENEMIES + (offset)))

typedef struct Encounter {
    u8 enemy_indexes[ENCOUNTER_ENEMY_COUNT];
    u8 appearance_rate;
} Encounter;

ASSERT_SIZE(Encounter, ENCOUNTER_STRIDE);

#endif
