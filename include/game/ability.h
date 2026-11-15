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
#define ABILITY_SKILL(difficulty, ability_type)                                                       (((difficulty) << 4) | (ability_type))

#define ABILITY_OBJECT(name, targeting_flags, type, cost, power, element, ability_flags, description) {name, (targeting_flags), (type), (cost), (power), (element), (ability_flags), (description)}

/* Ability flags (record offset 0x11). Together with the element byte they form
 * the 16-bit mask the battle code tests: bit 0 is a ninth element. */
typedef enum AbilityFlags {
    ABILITY_ELEMENT_DEATH = 1 << 0, /* the Death resistance applies to its damage */
    ABILITY_EXAMINABLE    = 1 << 1,
    ABILITY_SILENCEABLE   = 1 << 2, /* Silence blocks it */
    ABILITY_PHYSICAL      = 1 << 3, /* the user plays the attack motion, not the casting one */
    ABILITY_AFFECTS_STATS = 1 << 4,
} AbilityFlags;

/* Ability targeting byte (record offset 0x0C): bit switches the battle selectors
 * (Battle_PickTarget, Battle_PickEnemyTarget) test. Without SELECT or ALL the
 * ability targets its user; OPPONENT is the other side from the user. */
typedef enum AbilityTargetFlags {
    ABILITY_TARGET_FIELD        = 1 << 0, /* usable from the field menu */
    ABILITY_TARGET_BATTLE       = 1 << 1, /* usable in battle */
    ABILITY_TARGET_NO_HIT_REACT = 1 << 2, /* the target skips the generic hit reaction */
    ABILITY_TARGET_UNK_3        = 1 << 3,
    ABILITY_TARGET_ALL          = 1 << 4, /* a whole side */
    ABILITY_TARGET_OPPONENT     = 1 << 5,
    ABILITY_TARGET_SELECT       = 1 << 6, /* the player picks the target */
    ABILITY_TARGET_BOTH_SIDES   = 1 << 7, /* with ALL and no SELECT, both sides; else either side */
} AbilityTargetFlags;

/* clang-format off */
/* Who an ability can be aimed at: the ALL, OPPONENT, SELECT and BOTH_SIDES bits.
 * ENEMY means the cursor starts on the other side. */
typedef enum AbilityAim {
    ABILITY_AIM_USER             = 0,
    ABILITY_AIM_ALL_ALLIES       = ABILITY_TARGET_ALL,
    ABILITY_AIM_ALL_ENEMIES      = ABILITY_TARGET_OPPONENT | ABILITY_TARGET_ALL,
    ABILITY_AIM_ONE_ALLY         = ABILITY_TARGET_SELECT,
    ABILITY_AIM_ONE_ENEMY        = ABILITY_TARGET_SELECT | ABILITY_TARGET_OPPONENT,
    ABILITY_AIM_ENEMIES_SELECT   = ABILITY_TARGET_SELECT | ABILITY_TARGET_OPPONENT | ABILITY_TARGET_ALL,
    ABILITY_AIM_EVERYONE         = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_ALL,
    ABILITY_AIM_EVERYONE_ENEMY   = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_OPPONENT | ABILITY_TARGET_ALL,
    ABILITY_AIM_ONE_EITHER       = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_SELECT,
    ABILITY_AIM_ALL_EITHER       = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_SELECT | ABILITY_TARGET_ALL,
    ABILITY_AIM_ONE_EITHER_ENEMY = ABILITY_TARGET_BOTH_SIDES | ABILITY_TARGET_SELECT | ABILITY_TARGET_OPPONENT,
    ABILITY_AIM_ALL_EITHER_ENEMY = ABILITY_AIM_ONE_EITHER_ENEMY | ABILITY_TARGET_ALL,
} AbilityAim;

/* Where an ability is usable, and the two low bits that change how it plays. */
typedef enum AbilityUse {
    ABILITY_USE_FIELD_UNK_3             = ABILITY_TARGET_FIELD | ABILITY_TARGET_UNK_3,
    ABILITY_USE_BATTLE                  = ABILITY_TARGET_BATTLE,
    ABILITY_USE_BATTLE_NO_REACT         = ABILITY_TARGET_BATTLE | ABILITY_TARGET_NO_HIT_REACT,
    ABILITY_USE_BATTLE_UNK_3            = ABILITY_TARGET_BATTLE | ABILITY_TARGET_UNK_3,
    ABILITY_USE_BATTLE_NO_REACT_UNK_3   = ABILITY_TARGET_BATTLE | ABILITY_TARGET_NO_HIT_REACT | ABILITY_TARGET_UNK_3,
    ABILITY_USE_ANYWHERE_NO_REACT_UNK_3 = ABILITY_TARGET_FIELD | ABILITY_USE_BATTLE_NO_REACT_UNK_3,
} AbilityUse;

/* The targeting bytes of the shipped ability table. */
typedef enum AbilityTarget {
    ABILITY_TARGET_NONE                            = 0,
    ABILITY_TARGET_USER                            = ABILITY_USE_BATTLE,
    ABILITY_TARGET_USER_NO_REACT                   = ABILITY_USE_BATTLE_NO_REACT,
    ABILITY_TARGET_USER_FIELD_UNK_3                = ABILITY_USE_FIELD_UNK_3,
    ABILITY_TARGET_USER_UNK_3                      = ABILITY_USE_BATTLE_UNK_3,
    ABILITY_TARGET_USER_NO_REACT_UNK_3             = ABILITY_USE_BATTLE_NO_REACT_UNK_3,
    ABILITY_TARGET_ALL_ALLIES_NO_REACT_UNK_3       = ABILITY_AIM_ALL_ALLIES | ABILITY_USE_BATTLE_NO_REACT_UNK_3,
    ABILITY_TARGET_ALL_ALLIES_FIELD_NO_REACT_UNK_3 = ABILITY_AIM_ALL_ALLIES | ABILITY_USE_ANYWHERE_NO_REACT_UNK_3,
    ABILITY_TARGET_ALL_ENEMIES                     = ABILITY_AIM_ALL_ENEMIES | ABILITY_USE_BATTLE,
    ABILITY_TARGET_ALL_ENEMIES_UNK_3               = ABILITY_AIM_ALL_ENEMIES | ABILITY_USE_BATTLE_UNK_3,
    ABILITY_TARGET_ALL_ENEMIES_NO_REACT_UNK_3      = ABILITY_AIM_ALL_ENEMIES | ABILITY_USE_BATTLE_NO_REACT_UNK_3,
    ABILITY_TARGET_ONE_ALLY_NO_REACT_UNK_3         = ABILITY_AIM_ONE_ALLY | ABILITY_USE_BATTLE_NO_REACT_UNK_3,
    ABILITY_TARGET_ONE_ENEMY                       = ABILITY_AIM_ONE_ENEMY | ABILITY_USE_BATTLE,
    ABILITY_TARGET_ONE_ENEMY_UNK_3                 = ABILITY_AIM_ONE_ENEMY | ABILITY_USE_BATTLE_UNK_3,
    ABILITY_TARGET_ONE_ENEMY_NO_REACT_UNK_3        = ABILITY_AIM_ONE_ENEMY | ABILITY_USE_BATTLE_NO_REACT_UNK_3,
    ABILITY_TARGET_ENEMIES_SELECT_UNK_3            = ABILITY_AIM_ENEMIES_SELECT | ABILITY_USE_BATTLE_UNK_3,
    ABILITY_TARGET_ENEMIES_SELECT_NO_REACT_UNK_3   = ABILITY_AIM_ENEMIES_SELECT | ABILITY_USE_BATTLE_NO_REACT_UNK_3,
    ABILITY_TARGET_EVERYONE_NO_REACT               = ABILITY_AIM_EVERYONE | ABILITY_USE_BATTLE_NO_REACT,
    ABILITY_TARGET_EVERYONE_NO_REACT_UNK_3         = ABILITY_AIM_EVERYONE | ABILITY_USE_BATTLE_NO_REACT_UNK_3,
    ABILITY_TARGET_EVERYONE_ENEMY_UNK_3            = ABILITY_AIM_EVERYONE_ENEMY | ABILITY_USE_BATTLE_UNK_3,
    ABILITY_TARGET_ONE_EITHER_NO_REACT_UNK_3       = ABILITY_AIM_ONE_EITHER | ABILITY_USE_BATTLE_NO_REACT_UNK_3,
    ABILITY_TARGET_ONE_EITHER_FIELD_NO_REACT_UNK_3 = ABILITY_AIM_ONE_EITHER | ABILITY_USE_ANYWHERE_NO_REACT_UNK_3,
    ABILITY_TARGET_ALL_EITHER_NO_REACT_UNK_3       = ABILITY_AIM_ALL_EITHER | ABILITY_USE_BATTLE_NO_REACT_UNK_3,
    ABILITY_TARGET_ALL_EITHER_FIELD_NO_REACT_UNK_3 = ABILITY_AIM_ALL_EITHER | ABILITY_USE_ANYWHERE_NO_REACT_UNK_3,
    ABILITY_TARGET_ONE_EITHER_ENEMY                = ABILITY_AIM_ONE_EITHER_ENEMY | ABILITY_USE_BATTLE,
    ABILITY_TARGET_ONE_EITHER_ENEMY_UNK_3          = ABILITY_AIM_ONE_EITHER_ENEMY | ABILITY_USE_BATTLE_UNK_3,
    ABILITY_TARGET_ONE_EITHER_ENEMY_NO_REACT_UNK_3 = ABILITY_AIM_ONE_EITHER_ENEMY | ABILITY_USE_BATTLE_NO_REACT_UNK_3,
    ABILITY_TARGET_ALL_EITHER_ENEMY                = ABILITY_AIM_ALL_EITHER_ENEMY | ABILITY_USE_BATTLE,
} AbilityTarget;
/* clang-format on */

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
    u16 description;   /* battle/battle/15 func_8009704C passes this resource ID to Message_GetText */
} Ability;

ASSERT_OFFSET(Ability, description, 0x12);
ASSERT_SIZE(Ability, ABILITY_STRIDE);

/* Ability ids, the record index in the GAME.EMI ability table; the names are the
 * record names. Ids 174-215 repeat the spells of 70-115 as AbilityType SKILL
 * records (the _SKILL suffix); the "Noting" placeholders carry their id.
 * Char_GetExp passes these ids to the character ability list.
 */
typedef enum AbilityId {
    ABILITY_NONE              = 0,
    ABILITY_NUE_STOMP         = 1,
    ABILITY_GAMBIT            = 2,
    ABILITY_SUPER_COMBO       = 3,
    ABILITY_THUNDER_STRIKE    = 4,
    ABILITY_FLAME_STRIKE      = 5,
    ABILITY_MIND_SWORD        = 6,
    ABILITY_MIND_FLAY         = 7,
    ABILITY_BLIND             = 8,
    ABILITY_CHLORINE          = 9,
    ABILITY_UNMOTIVATE        = 10,
    ABILITY_MULTISTRIKE       = 11,
    ABILITY_BLITZ             = 12,
    ABILITY_SNAP              = 13,
    ABILITY_FLYING_KICK       = 14,
    ABILITY_CHARGE            = 15,
    ABILITY_AIR_RAID          = 16,
    ABILITY_ASTRAL_WARP       = 17,
    ABILITY_GIANT_GROWTH      = 18,
    ABILITY_AURA              = 19,
    ABILITY_DISEMBOWEL        = 20,
    ABILITY_BONEBREAK         = 21,
    ABILITY_SPIRIT_BLAST      = 22,
    ABILITY_BAD_BACK          = 23,
    ABILITY_WATCH_ENEMY       = 24,
    ABILITY_NOTING_25         = 25,
    ABILITY_COUNTER           = 26,
    ABILITY_HYPNOTIZE         = 27,
    ABILITY_DEVOUR            = 28,
    ABILITY_WIND_STRIKE       = 29,
    ABILITY_MOLASSES          = 30,
    ABILITY_TARBABY           = 31,
    ABILITY_ABSORB            = 32,
    ABILITY_HEALING_HERB      = 33,
    ABILITY_STEROIDS          = 34,
    ABILITY_MAGIC_BELT        = 35,
    ABILITY_RECALL            = 36,
    ABILITY_MAGIC_SHUFFLE     = 37,
    ABILITY_WAR_SHOUT         = 38,
    ABILITY_FOCUS             = 39,
    ABILITY_ENLIGHTEN         = 40,
    ABILITY_BERSERK           = 41,
    ABILITY_MIND_S_EYE        = 42,
    ABILITY_WARDOFLIGHT       = 43,
    ABILITY_EVIL_EYE          = 44,
    ABILITY_BONE_DART         = 45,
    ABILITY_FIREBREATH        = 46,
    ABILITY_ICEBREATH         = 47,
    ABILITY_DREAM_BREATH      = 48,
    ABILITY_FROST_STRIKE      = 49,
    ABILITY_POLLEN            = 50,
    ABILITY_VENOM_BREATH      = 51,
    ABILITY_OVUM              = 52,
    ABILITY_LAVABURST         = 53,
    ABILITY_HOWLING           = 54,
    ABILITY_EBONFIRE          = 55,
    ABILITY_SACRIFICE         = 56,
    ABILITY_BONE_DANCE        = 57,
    ABILITY_SANCTUARY         = 58,
    ABILITY_TORNADO           = 59,
    ABILITY_IDENTIFY          = 60,
    ABILITY_TARGET            = 61,
    ABILITY_CELERITY          = 62,
    ABILITY_SUDDENDEATH       = 63,
    ABILITY_WERETIGER         = 64,
    ABILITY_PILFER            = 65,
    ABILITY_TSUNAMI           = 66,
    ABILITY_CHILL             = 67,
    ABILITY_FORETELL          = 68,
    ABILITY_INFLUENCE         = 69,
    ABILITY_HEAL              = 70,
    ABILITY_REJUVENATE        = 71,
    ABILITY_RESTORE           = 72,
    ABILITY_VITALIZE          = 73,
    ABILITY_VIGOR             = 74,
    ABILITY_PURIFY            = 75,
    ABILITY_RAISE_DEAD        = 76,
    ABILITY_RESURRECT         = 77,
    ABILITY_LEECH_POWER       = 78,
    ABILITY_DRAIN             = 79,
    ABILITY_NOTING_80         = 80,
    ABILITY_ROTTEN_BREATH     = 81,
    ABILITY_PROTECT           = 82,
    ABILITY_SHIELD            = 83,
    ABILITY_SPEED             = 84,
    ABILITY_MIGHT             = 85,
    ABILITY_BARRIER           = 86,
    ABILITY_SILENCE           = 87,
    ABILITY_SLOW              = 88,
    ABILITY_BLUNT             = 89,
    ABILITY_WEAKEN            = 90,
    ABILITY_FLARE             = 91,
    ABILITY_FIREBLAST         = 92,
    ABILITY_INFERNO           = 93,
    ABILITY_FROST             = 94,
    ABILITY_ICEBLAST          = 95,
    ABILITY_BLIZZARD          = 96,
    ABILITY_JOLT              = 97,
    ABILITY_LIGHTNING         = 98,
    ABILITY_MYOLLNIR          = 99,
    ABILITY_CYCLONE           = 100,
    ABILITY_TYPHOON           = 101,
    ABILITY_QUAKE             = 102,
    ABILITY_SIMOON            = 103,
    ABILITY_SIROCCO           = 104,
    ABILITY_KYRIE             = 105,
    ABILITY_DEATH             = 106,
    ABILITY_SLEEP             = 107,
    ABILITY_CONFUSE           = 108,
    ABILITY_DEPRESS           = 109,
    ABILITY_RAGNAROK          = 110,
    ABILITY_NOTING_111        = 111,
    ABILITY_NOTING_112        = 112,
    ABILITY_NOTING_113        = 113,
    ABILITY_FIRE_WHIP         = 114,
    ABILITY_REMEDY            = 115,
    ABILITY_UTMOST_ATTACK     = 116,
    ABILITY_REST              = 117,
    ABILITY_BURN              = 118,
    ABILITY_DOUBLE_BLOW       = 119,
    ABILITY_WHELP_BREATH      = 120,
    ABILITY_DRAGON_BREATH     = 121,
    ABILITY_FLAME_BREATH      = 122,
    ABILITY_FROST_BREATH      = 123,
    ABILITY_THUNDER_BREATH    = 124,
    ABILITY_DIVINE_BREATH     = 125,
    ABILITY_SHADOW_BREATH     = 126,
    ABILITY_NOTING_127        = 127,
    ABILITY_HEAD_CRACKER      = 128,
    ABILITY_HOLOCAUST         = 129,
    ABILITY_VENOM             = 130,
    ABILITY_KAISER_BREATH     = 131,
    ABILITY_DOOM_BREATH       = 132,
    ABILITY_FLAME_CLAW        = 133,
    ABILITY_FROST_CLAW        = 134,
    ABILITY_THUNDER_CLAW      = 135,
    ABILITY_SHINING_CLAW      = 136,
    ABILITY_CORONA            = 137,
    ABILITY_MAIN_CANNON       = 138,
    ABILITY_PARALYZER         = 139,
    ABILITY_TRUMP             = 140,
    ABILITY_TRIPLE_BLOW       = 141,
    ABILITY_SYPHON            = 142,
    ABILITY_THUNDER_CLAP      = 143,
    ABILITY_WALL_OF_FIRE      = 144,
    ABILITY_NOTING_145        = 145,
    ABILITY_NOTING_146        = 146,
    ABILITY_NOTING_147        = 147,
    ABILITY_NOTING_148        = 148,
    ABILITY_DOUSE             = 149,
    ABILITY_EYE_BEAM          = 150,
    ABILITY_ACCESSION         = 151,
    ABILITY_SNOOZE            = 152,
    ABILITY_RESIST            = 153,
    ABILITY_MIGHTY_CHOP       = 154,
    ABILITY_PYROKINESIS       = 155,
    ABILITY_HOLY_STRIKE       = 156,
    ABILITY_DEMONBANE         = 157,
    ABILITY_CHARM             = 158,
    ABILITY_GLOOM             = 159,
    ABILITY_JUMP              = 160,
    ABILITY_TIMED_BLOW        = 161,
    ABILITY_TRANSFER          = 162,
    ABILITY_MEDITATION        = 163,
    ABILITY_FEIGN_SWING       = 164,
    ABILITY_BACKHAND          = 165,
    ABILITY_MONOPOLIZE        = 166,
    ABILITY_LAST_RESORT       = 167,
    ABILITY_CURE              = 168,
    ABILITY_BENEDICTION       = 169,
    ABILITY_RISKY_BLOW        = 170,
    ABILITY_SHADOWWALK        = 171,
    ABILITY_MAGIC_BALL        = 172,
    ABILITY_INTIMIDATE        = 173,
    ABILITY_HEAL_SKILL        = 174,
    ABILITY_REJUVENATE_SKILL  = 175,
    ABILITY_RESTORE_SKILL     = 176,
    ABILITY_VITALIZE_SKILL    = 177,
    ABILITY_VIGOR_SKILL       = 178,
    ABILITY_PURIFY_SKILL      = 179,
    ABILITY_RAISE_DEAD_SKILL  = 180,
    ABILITY_RESURRECT_SKILL   = 181,
    ABILITY_LEECH_POWER_SKILL = 182,
    ABILITY_DRAIN_SKILL       = 183,
    ABILITY_PROTECT_SKILL     = 184,
    ABILITY_SHIELD_SKILL      = 185,
    ABILITY_SPEED_SKILL       = 186,
    ABILITY_MIGHT_SKILL       = 187,
    ABILITY_BARRIER_SKILL     = 188,
    ABILITY_SILENCE_SKILL     = 189,
    ABILITY_SLOW_SKILL        = 190,
    ABILITY_BLUNT_SKILL       = 191,
    ABILITY_WEAKEN_SKILL      = 192,
    ABILITY_FLARE_SKILL       = 193,
    ABILITY_FIREBLAST_SKILL   = 194,
    ABILITY_INFERNO_SKILL     = 195,
    ABILITY_FROST_SKILL       = 196,
    ABILITY_ICEBLAST_SKILL    = 197,
    ABILITY_BLIZZARD_SKILL    = 198,
    ABILITY_JOLT_SKILL        = 199,
    ABILITY_LIGHTNING_SKILL   = 200,
    ABILITY_MYOLLNIR_SKILL    = 201,
    ABILITY_CYCLONE_SKILL     = 202,
    ABILITY_TYPHOON_SKILL     = 203,
    ABILITY_QUAKE_SKILL       = 204,
    ABILITY_SIMOON_SKILL      = 205,
    ABILITY_SIROCCO_SKILL     = 206,
    ABILITY_KYRIE_SKILL       = 207,
    ABILITY_DEATH_SKILL       = 208,
    ABILITY_SLEEP_SKILL       = 209,
    ABILITY_CONFUSE_SKILL     = 210,
    ABILITY_DEPRESS_SKILL     = 211,
    ABILITY_RAGNAROK_SKILL    = 212,
    ABILITY_NOTING_213        = 213,
    ABILITY_NOTING_214        = 214,
    ABILITY_REMEDY_SKILL      = 215,
    ABILITY_STEAL             = 216,
    ABILITY_RESTORE_FORM      = 217,
    ABILITY_AURA_BREATH       = 218,
    ABILITY_MAGMA_BREATH      = 219,
    ABILITY_GEO_BREATH        = 220,
    ABILITY_GAEAS_BREATH      = 221,
    ABILITY_COMBUSTION        = 222,
    ABILITY_TEMPEST           = 223,
    ABILITY_HURRICANE         = 224,
    ABILITY_TEMPTATION        = 225,
    ABILITY_METEOR_STRIKE     = 226,
    ABILITY_METEOR_STRIKE_2   = 227,
} AbilityId;

/* D_801CA70C */
extern volatile Ability g_Abilities[];

#endif
