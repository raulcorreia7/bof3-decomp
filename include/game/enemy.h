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

/* The family byte of an enemy id: the slayer weapons double damage to their
 * family (Dragon Blade, Dragon Spear and Dragonfang to dragons; Demonsbane,
 * Holy Avenger and Aries Spear to demons). The disc records hold only these three
 * values: 146 enemies with none, 11 dragons, 12 demons. */
typedef enum EnemyFamily {
    ENEMY_FAMILY_NONE   = 0,
    ENEMY_FAMILY_DRAGON = 1,
    ENEMY_FAMILY_DEMON  = 4,
} EnemyFamily;

/* An enemy id: the family in the high byte, the enemy number in the low byte. */
#define ENEMY_ID(family, number) (((family) << 8) | (number))

typedef enum EnemyId {
    ENEMY_ID_BARB_BULB          = 0x01,
    ENEMY_ID_RIPPER             = 0x02,
    ENEMY_ID_BOMBER             = 0x03,
    ENEMY_ID_MAN_TRAP           = 0x05,
    ENEMY_ID_TRICKER            = 0x06,
    ENEMY_ID_NUT_MAGE           = 0x07,
    ENEMY_ID_CURR               = 0x09,
    ENEMY_ID_GONGHEAD           = 0x0A,
    ENEMY_ID_GOBLIN             = 0x0B,
    ENEMY_ID_WORKER             = 0x0C,
    ENEMY_ID_NUE_MOUNT_GLAUS    = 0x0D,
    ENEMY_ID_NUE_CAVE           = 0x0E,
    ENEMY_ID_RANK_WEED          = 0x0F,
    ENEMY_ID_FLY_MAN            = 0x10,
    ENEMY_ID_VOLT               = 0x11,
    ENEMY_ID_NUT_ARCHER         = 0x12,
    ENEMY_ID_NUT_TROOP          = 0x13,
    ENEMY_ID_GUARD              = 0x15,
    ENEMY_ID_EYE_GOO            = 0x17,
    ENEMY_ID_MAGE_GOO           = 0x18,
    ENEMY_ID_MINER              = 0x19,
    ENEMY_ID_ENGINEER           = 0x1A,
    ENEMY_ID_FOREMAN            = 0x1B,
    ENEMY_ID_OPERATOR           = 0x1C,
    ENEMY_ID_GARY               = 0x1D,
    ENEMY_ID_MOGU               = 0x1E,
    ENEMY_ID_ZOMBIE             = 0x1F,
    ENEMY_ID_FOUL_WEED          = 0x20,
    ENEMY_ID_PROTO_BOT          = 0x21,
    ENEMY_ID_ARMOR_BOT          = 0x22,
    ENEMY_ID_MULTI_BOT          = 0x23,
    ENEMY_ID_DEATH_BOT          = 0x24,
    ENEMY_ID_TORAST             = 0x25,
    ENEMY_ID_KASSEN             = 0x26,
    ENEMY_ID_GALTEL             = 0x27,
    ENEMY_ID_DOKSEN             = 0x28,
    ENEMY_ID_AMALGAM            = 0x29,
    ENEMY_ID_BALIO              = 0x2A,
    ENEMY_ID_SUNDER             = 0x2B,
    ENEMY_ID_ORC                = 0x2C,
    ENEMY_ID_CODGER             = 0x2D,
    ENEMY_ID_GOO_KING           = 0x2E,
    ENEMY_ID_PUFF_GOO           = 0x2F,
    ENEMY_ID_GOOEY              = 0x30,
    ENEMY_ID_GOO_TITAN          = 0x31,
    ENEMY_ID_BOSS_GOBLIN        = 0x32,
    ENEMY_ID_BAT                = 0x33,
    ENEMY_ID_VAGABOND           = 0x34,
    ENEMY_ID_ROACH              = 0x35,
    ENEMY_ID_THRASHER           = 0x36,
    ENEMY_ID_GIANT_CRAB         = 0x37,
    ENEMY_ID_TAR_MAN            = 0x38,
    ENEMY_ID_EYE_BULB           = 0x39,
    ENEMY_ID_SLEEPY             = 0x3A,
    ENEMY_ID_THANOTOS           = 0x3B,
    ENEMY_ID_TOXIC_FLY          = 0x3C,
    ENEMY_ID_ROCKY              = 0x3D,
    ENEMY_ID_POOCH              = 0x3E,
    ENEMY_ID_BLOOD_BAT          = 0x3F,
    ENEMY_ID_NINA               = 0x40,
    ENEMY_ID_MUTANT             = 0x41,
    ENEMY_ID_ARMOR              = 0x46,
    ENEMY_ID_STALLION           = 0x47,
    ENEMY_ID_CLAW               = 0x48,
    ENEMY_ID_CAWER              = 0x49,
    ENEMY_ID_PATRIO             = 0x4A,
    ENEMY_ID_EMITAI             = 0x4B,
    ENEMY_ID_GOLEM              = 0x4C,
    ENEMY_ID_GOLEM_ALT          = 0x4D,
    ENEMY_ID_DODAI_1            = 0x4E,
    ENEMY_ID_DODAI_2            = 0x4F,
    ENEMY_ID_GHOUL              = 0x50,
    ENEMY_ID_THUNDER            = 0x51,
    ENEMY_ID_GONGER             = 0x52,
    ENEMY_ID_MAD_GONG           = 0x53,
    ENEMY_ID_BULLY_1            = 0x55,
    ENEMY_ID_BULLY_2            = 0x56,
    ENEMY_ID_BULLY_3            = 0x57,
    ENEMY_ID_BEYD               = 0x58,
    ENEMY_ID_BEYD_ALT           = 0x59,
    ENEMY_ID_ZIG                = 0x5A,
    ENEMY_ID_GAZER              = 0x5B,
    ENEMY_ID_HYPER_BOT          = 0x5C,
    ENEMY_ID_LAVA_MAN           = 0x5D,
    ENEMY_ID_GHOST              = 0x5E,
    ENEMY_ID_SPIKER             = 0x60,
    ENEMY_ID_DOLPHIN            = 0x61,
    ENEMY_ID_GISSHAN            = 0x64,
    ENEMY_ID_PAIN_WEED          = 0x68,
    ENEMY_ID_WERETIGER          = 0x69,
    ENEMY_ID_BLUE_GOBLIN        = 0x6B,
    ENEMY_ID_HOBGOBLIN          = 0x6C,
    ENEMY_ID_SLASHER            = 0x6D,
    ENEMY_ID_ZOMBIE_DRAGON      = 0x6E,
    ENEMY_ID_GIANT_ROACH        = 0x6F,
    ENEMY_ID_AUDREY             = 0x70,
    ENEMY_ID_EGG_GANG           = 0x71,
    ENEMY_ID_ICE_TOAD           = 0x72,
    ENEMY_ID_BOMB_SEED          = 0x73,
    ENEMY_ID_BIG_BULB           = 0x74,
    ENEMY_ID_TORCH              = 0x76,
    ENEMY_ID_ANGLER             = 0x77,
    ENEMY_ID_HOPPER             = 0x78,
    ENEMY_ID_ADEPT              = 0x7B,
    ENEMY_ID_ARCH_MAGE          = 0x7C,
    ENEMY_ID_TOXIC_MAN          = 0x7F,
    ENEMY_ID_PIPE_BOMB          = 0x80,
    ENEMY_ID_BOLT               = 0x81,
    ENEMY_ID_BOLT_MAGE          = 0x82,
    ENEMY_ID_BOLT_LORD          = 0x83,
    ENEMY_ID_BOLT_ARCHER        = 0x84,
    ENEMY_ID_KING_TOAD          = 0x85,
    ENEMY_ID_VILE_WEED          = 0x86,
    ENEMY_ID_SCORPION           = 0x87,
    ENEMY_ID_GIANT_ORC          = 0x8B,
    ENEMY_ID_INSECTOR           = 0x8C,
    ENEMY_ID_ASSASSIN           = 0x8D,
    ENEMY_ID_MIST_MAN           = 0x8F,
    ENEMY_ID_DRAGONFLY          = 0x90,
    ENEMY_ID_PLANT_42           = 0x91,
    ENEMY_ID_GOLD_EGG           = 0x92,
    ENEMY_ID_TANK_BOT           = 0x93,
    ENEMY_ID_ELDER              = 0x94,
    ENEMY_ID_AMMONITE           = 0x95,
    ENEMY_ID_AMMONITE_ALT       = 0x96,
    ENEMY_ID_SAMPLE_1           = 0x97,
    ENEMY_ID_SAMPLE_2           = 0x98,
    ENEMY_ID_SAMPLE_4           = 0x9A,
    ENEMY_ID_SAMPLE_5           = 0x9B,
    ENEMY_ID_SAMPLE_6           = 0x9C,
    ENEMY_ID_SAMPLE_7           = 0x9D,
    ENEMY_ID_SAMPLE_8           = 0x9E,
    ENEMY_ID_SAMPLE_10          = 0xA0,
    ENEMY_ID_SAMPLE_11          = 0xA1,
    ENEMY_ID_SAMPLE_12          = 0xA2,
    ENEMY_ID_VULCAN             = 0xA3,
    ENEMY_ID_SLUG               = 0xA4,
    ENEMY_ID_SPECTRE            = 0xA5,
    ENEMY_ID_MANMO              = 0xA6,
    ENEMY_ID_CHIMERA            = 0xA7,
    ENEMY_ID_WRAITH             = 0xAA,
    ENEMY_ID_FIRE_SLUG          = 0xAB,
    ENEMY_ID_NIGHT_BAT          = 0xAC,
    ENEMY_ID_MAGMAITE           = 0xAD,
    ENEMY_ID_TOXIC_MAN_WEAK     = 0xAE,
    ENEMY_ID_TOXIC_MAN_LEVEL_20 = 0xAF,
    ENEMY_ID_HUGE_SLUG          = 0xB0,
    ENEMY_ID_SHROOM             = 0xB1,
    ENEMY_ID_CACTI              = 0xB2,
    ENEMY_ID_BERSERKER          = 0xB4,
    ENEMY_ID_MYRIA              = 0xB5,
    ENEMY_ID_LIZARDMAN          = ENEMY_ID(ENEMY_FAMILY_DRAGON, 0x08),
    ENEMY_ID_LIZARD             = ENEMY_ID(ENEMY_FAMILY_DRAGON, 0x14),
    ENEMY_ID_SCYLLA             = ENEMY_ID(ENEMY_FAMILY_DRAGON, 0x62),
    ENEMY_ID_CHARYBDIS          = ENEMY_ID(ENEMY_FAMILY_DRAGON, 0x63),
    ENEMY_ID_D_ZOMBIE           = ENEMY_ID(ENEMY_FAMILY_DRAGON, 0x66),
    ENEMY_ID_RED_DRAKE          = ENEMY_ID(ENEMY_FAMILY_DRAGON, 0x88),
    ENEMY_ID_ICE_DRAKE          = ENEMY_ID(ENEMY_FAMILY_DRAGON, 0x89),
    ENEMY_ID_CLONE              = ENEMY_ID(ENEMY_FAMILY_DRAGON, 0x8A),
    ENEMY_ID_NEWT               = ENEMY_ID(ENEMY_FAMILY_DRAGON, 0x8E),
    ENEMY_ID_D_LORD             = ENEMY_ID(ENEMY_FAMILY_DRAGON, 0xA9),
    ENEMY_ID_DRAK               = ENEMY_ID(ENEMY_FAMILY_DRAGON, 0xB3),
    ENEMY_ID_PHANTOM            = ENEMY_ID(ENEMY_FAMILY_DEMON, 0x44),
    ENEMY_ID_NITEMARE           = ENEMY_ID(ENEMY_FAMILY_DEMON, 0x45),
    ENEMY_ID_GARR_CONTEST       = ENEMY_ID(ENEMY_FAMILY_DEMON, 0x54),
    ENEMY_ID_GARR_ANGEL_TOWER   = ENEMY_ID(ENEMY_FAMILY_DEMON, 0x65),
    ENEMY_ID_CEREBUS            = ENEMY_ID(ENEMY_FAMILY_DEMON, 0x67),
    ENEMY_ID_MIKBA              = ENEMY_ID(ENEMY_FAMILY_DEMON, 0x6A),
    ENEMY_ID_GAIST              = ENEMY_ID(ENEMY_FAMILY_DEMON, 0x75),
    ENEMY_ID_VAMPIRE            = ENEMY_ID(ENEMY_FAMILY_DEMON, 0x79),
    ENEMY_ID_REAPER             = ENEMY_ID(ENEMY_FAMILY_DEMON, 0x7D),
    ENEMY_ID_REVENANT           = ENEMY_ID(ENEMY_FAMILY_DEMON, 0x7E),
    ENEMY_ID_SAMPLE_3           = ENEMY_ID(ENEMY_FAMILY_DEMON, 0x99),
    ENEMY_ID_SAMPLE_9           = ENEMY_ID(ENEMY_FAMILY_DEMON, 0x9F),
    ENEMY_ID_ARWAN              = ENEMY_ID(ENEMY_FAMILY_DEMON, 0xA8),
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

/* The enemy id as the records store it, read as two bytes: the low byte tells
 * enemies apart (func_801DA69C, func_8009CFEC, Battle_DefeatEnemy) and the high byte is the
 * family the slayer weapons test (Battle_CalcDamage, func_800A2598). */
typedef union EnemyIdCode {
    u16 value;

    struct {
        u8 kind;
        u8 family;
    } byte;
} EnemyIdCode;

/* One drop of an enemy: the item id (index, then type, as Battle_RollEnemyDrops
 * compares it) and the index into the 8-byte drop chance table at 0x801D0CB8. */
typedef struct EnemyDrop {
    u16 item;
    u8  rate;
    u8  flags; /* battle only: bit 0 is set once an ability has raised the rate */
} EnemyDrop;

ASSERT_SIZE(EnemyDrop, 0x4);

typedef struct Enemy {
    u8           name[ENEMY_NAME_LENGTH];
    EnemyIdCode  enemy_id;
    u8           choice_ai;
    u8           unk_0B[3];
    u16          event_flags; /* +0x0E: the low byte is the target preference */
    u16          zenny;
    u16          exp;
    u16          level;
    u8           unk_16[2];
    u8           initial_skills[ENEMY_SKILL_COUNT];
    u16          hp;
    u16          ap;
    u16          power;
    u16          defense;
    u16          agility;
    u16          intellect;
    EnemyDrop    drops[2];
    EnemyAIBlock ai[ENEMY_AI_COUNT];
    u8           unk_74[4];
    u8           resistances[RES_INDEX_COUNT];
    u8           status; /* +0x81: the StatusFlags the enemy enters battle with */
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
