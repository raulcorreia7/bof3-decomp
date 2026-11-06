#ifndef GAME_SPELL_H
#define GAME_SPELL_H

/* The 228 ability records from `GAME.EMI`: name, flags, targeting byte, stat
 * effects and the fields the battle code reads. battle/battle/03 and battle/battle/15 read
 * the table; game/records.h owns the count and stride.
 *
 * Layout: @source: wiki:data/records#gameemi-fixed-tables (228 records of 0x14
 * bytes). */

#include "types.h"
#include "game/records.h"

/* Difficulty is the high nibble; the low two bits are the AbilityType. */
#define ABILITY_SKILL(difficulty, ability_type) (((difficulty) << 4) | (ability_type))

#define ABILITY_OBJECT(name, targeting_flags, type, cost, power, element, ability_flags, description) \
    {name, (targeting_flags), (type), (cost), (power), (element), (ability_flags), (description)}

/* Ability flags: what the ability does when the battle code reads it. */
typedef enum AbilityFlags {
    ABILITY_UNKNOWN_0           = 1 << 0,
    ABILITY_EXAMINABLE          = 1 << 1,
    ABILITY_TARGET_ALLY_DEFAULT = 1 << 2,
    ABILITY_UNKNOWN_3           = 1 << 3,
    ABILITY_AFFECTS_STATS       = 1 << 4,
} AbilityFlags;

/* Ability targeting byte (record offset 0x0C): bit switches the battle selectors
 * (Battle_PickTarget, Battle_PickEnemyTarget) test. Without SELECT or ALL the
 * ability targets its user; OPPONENT is the other side from the user. */
typedef enum AbilityTargetFlags {
    ABILITY_TARGET_FIELD      = 1 << 0, /* usable in the field */
    ABILITY_TARGET_UNK_1      = 1 << 1,
    ABILITY_TARGET_UNK_2      = 1 << 2,
    ABILITY_TARGET_UNK_3      = 1 << 3,
    ABILITY_TARGET_ALL        = 1 << 4, /* a whole side */
    ABILITY_TARGET_OPPONENT   = 1 << 5,
    ABILITY_TARGET_SELECT     = 1 << 6, /* the player picks the target */
    ABILITY_TARGET_BOTH_SIDES = 1 << 7, /* with ALL and no SELECT, both sides; else either side */
} AbilityTargetFlags;

/* The targeting bytes of the shipped ability table. */
typedef enum AbilityTarget {
    ABILITY_TARGET_SELF_02       = ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_SELF_0E       = ABILITY_TARGET_UNK_3 | ABILITY_TARGET_UNK_2 | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_ALL_PLAYER_1E = ABILITY_TARGET_ALL | ABILITY_TARGET_UNK_3 | ABILITY_TARGET_UNK_2 |
        ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_ALL_PLAYER_1F = ABILITY_TARGET_ALL | ABILITY_TARGET_UNK_3 | ABILITY_TARGET_UNK_2 |
        ABILITY_TARGET_UNK_1 | ABILITY_TARGET_FIELD,
    ABILITY_TARGET_ALL_ENEMY_32 = ABILITY_TARGET_OPPONENT | ABILITY_TARGET_ALL | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_ALL_ENEMY_3A = ABILITY_TARGET_OPPONENT | ABILITY_TARGET_ALL | ABILITY_TARGET_UNK_3 |
        ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_ALL_ENEMY_3E = ABILITY_TARGET_OPPONENT | ABILITY_TARGET_ALL | ABILITY_TARGET_UNK_3 |
        ABILITY_TARGET_UNK_2 | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_SINGLE_PLAYER_4E = ABILITY_TARGET_SELECT | ABILITY_TARGET_UNK_3 | ABILITY_TARGET_UNK_2 |
        ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_SINGLE_ENEMY_62 = ABILITY_TARGET_SELECT | ABILITY_TARGET_OPPONENT | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_SINGLE_ENEMY_6A = ABILITY_TARGET_SELECT | ABILITY_TARGET_OPPONENT | ABILITY_TARGET_UNK_3 |
        ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_SINGLE_ENEMY_6E = ABILITY_TARGET_SELECT | ABILITY_TARGET_OPPONENT | ABILITY_TARGET_UNK_3 |
        ABILITY_TARGET_UNK_2 | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_ALL_ENEMY_7A = ABILITY_TARGET_SELECT | ABILITY_TARGET_OPPONENT | ABILITY_TARGET_ALL |
        ABILITY_TARGET_UNK_3 | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_ALL_ENEMY_7E = ABILITY_TARGET_SELECT | ABILITY_TARGET_OPPONENT | ABILITY_TARGET_ALL |
        ABILITY_TARGET_UNK_3 | ABILITY_TARGET_UNK_2 | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_ALL_BOTH_96 = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_ALL | ABILITY_TARGET_UNK_2 |
        ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_ALL_BOTH_RANDOM_9E = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_ALL | ABILITY_TARGET_UNK_3 |
        ABILITY_TARGET_UNK_2 | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_SINGLE_BOTH_RANDOM_BA = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_OPPONENT | ABILITY_TARGET_ALL |
        ABILITY_TARGET_UNK_3 | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_SINGLE_EITHER_CE = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_SELECT | ABILITY_TARGET_UNK_3 |
        ABILITY_TARGET_UNK_2 | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_SINGLE_EITHER_CF = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_SELECT | ABILITY_TARGET_UNK_3 |
        ABILITY_TARGET_UNK_2 | ABILITY_TARGET_UNK_1 | ABILITY_TARGET_FIELD,
    ABILITY_TARGET_ALL_EITHER_DE = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_SELECT | ABILITY_TARGET_ALL |
        ABILITY_TARGET_UNK_3 | ABILITY_TARGET_UNK_2 | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_ALL_EITHER_DF = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_SELECT | ABILITY_TARGET_ALL |
        ABILITY_TARGET_UNK_3 | ABILITY_TARGET_UNK_2 | ABILITY_TARGET_UNK_1 | ABILITY_TARGET_FIELD,
    ABILITY_TARGET_SINGLE_EITHER_ENEMY_FIRST_E2 = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_SELECT |
        ABILITY_TARGET_OPPONENT | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_SINGLE_EITHER_ENEMY_FIRST_EA = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_SELECT |
        ABILITY_TARGET_OPPONENT | ABILITY_TARGET_UNK_3 | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_SINGLE_EITHER_ENEMY_FIRST_EE = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_SELECT |
        ABILITY_TARGET_OPPONENT | ABILITY_TARGET_UNK_3 | ABILITY_TARGET_UNK_2 | ABILITY_TARGET_UNK_1,
    ABILITY_TARGET_ALL_EITHER_ENEMY_FIRST_F2 = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_SELECT |
        ABILITY_TARGET_OPPONENT | ABILITY_TARGET_ALL | ABILITY_TARGET_UNK_1,
} AbilityTarget;

/* The low two bits of ABILITY_SKILL select the ability type. */
typedef enum AbilityType {
    ABILITY_TYPE_HEAL   = 0,
    ABILITY_TYPE_ASSIST = 1,
    ABILITY_TYPE_ATTACK = 2,
    ABILITY_TYPE_SKILL  = 3,
} AbilityType;

/* 0x14-byte record, 228 entries at 0x801CA70C.
 * Offsets 0x10-0x11 are element/ability_flags (menu/effect code) or a
 * 16-bit selection_mask (battle selector). See @source: wiki:data/records#masks-and-value-ranges. */
typedef struct Ability {
    u8  name[ABILITY_NAME_LENGTH];
    u8  targeting_flags; /* AbilityTargetFlags */
    u8  type;
    u8  cost;
    u8  power;
    u8  element;       /* ElementFlags */
    u8  ability_flags; /* AbilityFlags */
    u16 description;   /* battle/battle/15 func_8009704C passes this resource ID to Resource_GetText */
} Ability;

ASSERT_OFFSET(Ability, description, 0x12);
ASSERT_SIZE(Ability, ABILITY_STRIDE);

/* Learned ability IDs: names from the GAME.EMI Ability table;
 * func_801ADDD4 passes these IDs to the character ability list.
 * Sorted by numeric table index; gaps are intentional.
 */
typedef enum AbilityId {
    ABILITY_NONE         = 0,
    ABILITY_GAMBIT       = 2,
    ABILITY_SUPER_COMBO  = 3,
    ABILITY_FLAME_STRIKE = 5,
    ABILITY_MIND_SWORD   = 6,
    ABILITY_UNMOTIVATE   = 10,
    ABILITY_CHARGE       = 15,
    ABILITY_AURA         = 19,
    ABILITY_DISEMBOWEL   = 20,
    ABILITY_BONEBREAK    = 21,
    ABILITY_COUNTER      = 26,
    ABILITY_RECALL       = 36,
    ABILITY_WAR_SHOUT    = 38,
    ABILITY_FOCUS        = 39,
    ABILITY_ENLIGHTEN    = 40,
    ABILITY_BERSERK      = 41,
    ABILITY_MIND_S_EYE   = 42,
    ABILITY_WARDOFLIGHT  = 43,
    ABILITY_FIREBREATH   = 46,
    ABILITY_ICEBREATH    = 47,
    ABILITY_DREAM_BREATH = 48,
    ABILITY_VENOM_BREATH = 51,
    ABILITY_SANCTUARY    = 58,
    ABILITY_IDENTIFY     = 60,
    ABILITY_CELERITY     = 62,
    ABILITY_SUDDENDEATH  = 63,
    ABILITY_PILFER       = 65,
    ABILITY_FORETELL     = 68,
    ABILITY_HEAL         = 70,
    ABILITY_REJUVENATE   = 71,
    ABILITY_RESTORE      = 72,
    ABILITY_VITALIZE     = 73,
    ABILITY_VIGOR        = 74,
    ABILITY_PURIFY       = 75,
    ABILITY_RAISE_DEAD   = 76,
    ABILITY_RESURRECT    = 77,
    ABILITY_LEECH_POWER  = 78,
    ABILITY_DRAIN        = 79,
    ABILITY_PROTECT      = 82,
    ABILITY_SHIELD       = 83,
    ABILITY_SPEED        = 84,
    ABILITY_MIGHT        = 85,
    ABILITY_BARRIER      = 86,
    ABILITY_SILENCE      = 87,
    ABILITY_SLOW         = 88,
    ABILITY_BLUNT        = 89,
    ABILITY_WEAKEN       = 90,
    ABILITY_FLARE        = 91,
    ABILITY_FIREBLAST    = 92,
    ABILITY_INFERNO      = 93,
    ABILITY_FROST        = 94,
    ABILITY_ICEBLAST     = 95,
    ABILITY_BLIZZARD     = 96,
    ABILITY_JOLT         = 97,
    ABILITY_LIGHTNING    = 98,
    ABILITY_MYOLLNIR     = 99,
    ABILITY_CYCLONE      = 100,
    ABILITY_TYPHOON      = 101,
    ABILITY_QUAKE        = 102,
    ABILITY_SIMOON       = 103,
    ABILITY_SIROCCO      = 104,
    ABILITY_KYRIE        = 105,
    ABILITY_DEATH        = 106,
    ABILITY_SLEEP        = 107,
    ABILITY_CONFUSE      = 108,
    ABILITY_RAGNAROK     = 110,
    ABILITY_REMEDY       = 115,
    ABILITY_TRUMP        = 140,
    ABILITY_ACCESSION    = 151,
    ABILITY_RESIST       = 153,
    ABILITY_MIGHTY_CHOP  = 154,
    ABILITY_HOLY_STRIKE  = 156,
    ABILITY_DEMONBANE    = 157,
    ABILITY_CHARM        = 158,
    ABILITY_MEDITATION   = 163,
    ABILITY_FEIGN_SWING  = 164,
    ABILITY_BACKHAND     = 165,
    ABILITY_MONOPOLIZE   = 166,
    ABILITY_CURE         = 168,
    ABILITY_BENEDICTION  = 169,
    ABILITY_RISKY_BLOW   = 170,
    ABILITY_SHADOWWALK   = 171,
    ABILITY_MAGIC_BALL   = 172,
    ABILITY_INTIMIDATE   = 173,
    ABILITY_STEAL        = 216,
} AbilityId;

/* D_801CA70C */
extern volatile Ability g_Abilities[];

#endif
