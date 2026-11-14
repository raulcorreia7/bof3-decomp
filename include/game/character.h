#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

/* The eight playable characters' base stats, their level-growth rows and the
 * master bonus tables, as `GAME.EMI` stores them. `Character` is both
 * the save record and the row the menu copies; `LevelGrowth` is one level of
 * one growth table. The save screen, status menu and both battle overlays read
 * `Character`; the menu copies it into the local work row.
 *
 * Layout: @source: wiki:data/records#character-and-master-data (`Character`
 * is 8 records of 0xA4 bytes). */

#include "types.h"
#include "game/enemy.h"
#include "game/records.h"

#define CHARACTER_BLOCK_RECORDS 0x16

/* The block at its retail address; an image header declares g_WindowStyle. */
#define CHARACTER_BLOCK         ((Char_Block*)&g_WindowStyle)

/* Char_GetExp applies the six stat gains and learns both abilities. */
#define LEVEL_OBJECT(exp, hp, ap, power, defense, agility, intellect, ability, extra_ability)                   \
    {(exp), (hp), (ap), ((power) << 4) | (defense), ((agility) << 4) | (intellect), (ability), (extra_ability)}

/* The character sprites container loaded at 0x8003B800 (PLxxx archives;
 * @source: wiki:formats/character): a table of section offsets relative to the container.
 * Party_LoadMemberSprite stores the selected section's address in the scratchpad work
 * record at +0x4C. A section starts with a count and the offset of its palette
 * table; the table is a list of offsets, each to CHARACTER_PALETTE_COLORS
 * 16-bit colors, which GFX_LoadPalette copies to two VRAM staging rows. */
#define CHARACTER_SPRITES_SECTION_COUNT 3
#define CHARACTER_PALETTE_COLORS        32

/* The ailments the engine cures when a battle ends (the game's own strings
 * call status removal "cure"): Battle_ReloadPartySprites and Battle_LoadEndOverlay pass a
 * battler's status & this mask to func_800A36F0; STATUS_KO, STATUS_POISONED
 * and STATUS_CONFUSED persist. The (u16) keeps the complement a 16-bit
 * immediate (andi) in Battle_ReloadPartySprites's schedule. */
#define STATUS_CURE_MASK                ((u16) ~(STATUS_KO | STATUS_POISONED | STATUS_CONFUSED))

/* Equipment bits: the characters that may use a weapon or armor record
 * (Item.equipability). */
typedef enum EquipFlags {
    EQUIP_RYU   = 1 << 0,
    EQUIP_NINA  = 1 << 1,
    EQUIP_GARR  = 1 << 2,
    EQUIP_TEEPO = 1 << 3,
    EQUIP_REI   = 1 << 4,
    EQUIP_MOMO  = 1 << 5,
    EQUIP_PECO  = 1 << 6,
    EQUIP_WHELP = 1 << 7,
} EquipFlags;

/* Equipment slot: the order of the Character members weapon, shield, helmet,
 * armor and accessories[]. */
typedef enum EquipSlot {
    EQUIP_SLOT_WEAPON      = 0,
    EQUIP_SLOT_SHIELD      = 1,
    EQUIP_SLOT_HELMET      = 2,
    EQUIP_SLOT_ARMOR       = 3,
    EQUIP_SLOT_ACCESSORY_1 = 4,
    EQUIP_SLOT_ACCESSORY_2 = 5,
} EquipSlot;

#define EQUIP_SLOT_COUNT 6

/* The stats Char_PreviewEquip compares, in its order (not the order of Stats). */
typedef enum EquipPreviewStat {
    EQUIP_PREVIEW_POWER     = 0,
    EQUIP_PREVIEW_DEFENSE   = 1,
    EQUIP_PREVIEW_INTELLECT = 2,
    EQUIP_PREVIEW_AGILITY   = 3,
} EquipPreviewStat;

#define EQUIP_PREVIEW_STAT_COUNT 4

/* How a previewed stat compares with the current one; also its text shade. */
typedef enum EquipPreviewChange {
    EQUIP_PREVIEW_SAME   = 0,
    EQUIP_PREVIEW_LOWER  = 2,
    EQUIP_PREVIEW_HIGHER = 3,
} EquipPreviewChange;

/* Which party-order array a call reads: the walking order g_PartyFieldOrder or the
 * battle order g_PartyBattleOrder, three character ids each, 0xFF for an empty
 * position. Party_CountOrder and Party_BuildBattlers take it as their mode. */
typedef enum PartyOrder {
    PARTY_ORDER_FIELD  = 0,
    PARTY_ORDER_BATTLE = 1,
} PartyOrder;

/* Playable-character slot: the record's position in the 8-entry base-stat
 * array. Whelp occupies slot 7 but stores 0x0A in its character index field;
 * slot and stored index are different namespaces (@source: wiki:data/records#masks-and-value-ranges). */
typedef enum CharacterIndex {
    CHAR_INDEX_RYU   = 0,
    CHAR_INDEX_NINA  = 1,
    CHAR_INDEX_GARR  = 2,
    CHAR_INDEX_TEEPO = 3,
    CHAR_INDEX_REI   = 4,
    CHAR_INDEX_MOMO  = 5,
    CHAR_INDEX_PECO  = 6,
    CHAR_INDEX_WHELP = 7,
    CHARACTER_COUNT  = 8,
} CharacterIndex;

/* Stored character id. The party-order arrays hold these values, not record
 * slots; menu/party.h owns the map that resolves one to a record slot.
 * ID 10 appears in the save portrait table and in Whelp's record. */
typedef enum CharacterId {
    CHAR_ID_RYU_YOUNG   = 0,
    CHAR_ID_NINA_YOUNG  = 1,
    CHAR_ID_GARR        = 2,
    CHAR_ID_TEEPO       = 3,
    CHAR_ID_REI         = 4,
    CHAR_ID_MOMO        = 5,
    CHAR_ID_PECO        = 6,
    CHAR_ID_RYU_ADULT   = 7,
    CHAR_ID_NINA_ADULT  = 8,
    CHAR_ID_RYU_PAJAMAS = 9,
    CHAR_ID_WHELP       = 10,
    CHAR_ID_BLANK       = 0xFF,
} CharacterId;

/* Status word bits. The code tests and clears these values. Labels: the
 * ailment strings in the game data name the effects (paralysis, blindness,
 * the Silence skill, confusion, sleep, poison); the 0x20 label is
 * unverified: the code only clears and restores that bit, and a battle/battle/15
 * comment calls it magic-defense. */
typedef enum StatusFlags {
    STATUS_UNK_0     = 1 << 0,
    STATUS_UNK_1     = 1 << 1,
    STATUS_PARALYZED = 1 << 2,
    STATUS_BLIND     = 1 << 3,
    STATUS_SILENCED  = 1 << 4,
    STATUS_CONFUSED  = 1 << 5,
    STATUS_SLEEPING  = 1 << 6,
    STATUS_POISONED  = 1 << 7,
    STATUS_UNK_8     = 1 << 8,
    STATUS_UNK_11    = 1 << 11,
    STATUS_LOW_HP    = 1 << 13,
    STATUS_KO        = 1 << 14,
} StatusFlags;

/* Master ids are array indices into the master name, skill, and stat tables;
 * the records carry no explicit id field (@source: wiki:data/records#character-and-master-data). */
typedef enum MasterId {
    MASTER_BUNYAN    = 0,
    MASTER_MYGAS     = 1,
    MASTER_YGGDRASIL = 2,
    MASTER_DLONZO    = 3,
    MASTER_FAHL      = 4,
    MASTER_DURANDAL  = 5,
    MASTER_GIOTTO    = 6,
    MASTER_HONDARA   = 7,
    MASTER_EMITAI    = 8,
    MASTER_DEIS      = 9,
    MASTER_HACHIO    = 10,
    MASTER_BAIS      = 11,
    MASTER_LANG      = 12,
    MASTER_LEE       = 13,
    MASTER_WYNN      = 14,
    MASTER_LADON     = 15,
    MASTER_MERYLEEP  = 16,
} MasterId;

/* The operations of a master's stat modifier script, one (operation, amount) pair each, applied by
 * Char_ApplyMaster. Operations 0 to 8 add to the resistance of that RES_INDEX_*. */
typedef enum MasterModifier {
    MASTER_MOD_SURPRISE_CHANCE = 9,
    MASTER_MOD_REPRISAL_CHANCE = 10,
    MASTER_MOD_CRITICAL_CHANCE = 11,
    MASTER_MOD_EVASION         = 12,
    MASTER_MOD_ACCURACY        = 13,
    MASTER_MOD_END             = 14,
} MasterModifier;

/* The 0x20-byte stat block: the live copy at +0x1C holds the equipment and
 * buffs a battle reads; the permanent copy at +0x3C is what level-ups raise. */
typedef struct Stats {
    u16 max_hp;
    u16 max_ap;
    u16 power;
    u16 defense;
    u16 agility;
    u16 intellect;
    u16 unk_0C;
    u8  willpower;
    u8  resistances[RES_INDEX_COUNT];
    u8  surprise_chance;
    u8  reprisal_chance;
    u8  critical_chance;
    u8  evasion;
    u8  accuracy;
    u8  pad_1D[3];
} Stats;

ASSERT_SIZE(Stats, 0x20);

/* Equipped item ids, in EquipSlot order. */
typedef struct Equipment {
    u8 weapon;
    u8 shield;
    u8 helmet;
    u8 armor;
    u8 accessories[CHARACTER_ACCESSORY_COUNT];
} Equipment;

ASSERT_SIZE(Equipment, 0x06);

/* The four learned-ability lists, in ability-type order. */
typedef struct AbilitySet {
    u8 healing[CHARACTER_ABILITY_COUNT];
    u8 assist[CHARACTER_ABILITY_COUNT];
    u8 attack[CHARACTER_ABILITY_COUNT];
    u8 skill[CHARACTER_ABILITY_COUNT];
} AbilitySet;

ASSERT_SIZE(AbilitySet, 0x28);

typedef struct Character {
    u8         name[CHARACTER_NAME_LENGTH];
    u8         character_id; /* CharacterId */
    u8         level;
    u8         unk_07; /* party-row flags byte; bit 0 selects the rows func_801E0F78 lists */
    u32        exp;
    u16        status; /* StatusFlags */
    Equipment  equip;
    u16        hp;
    u16        ap;
    u8         willpower;
    u8         inoculations;
    u8         fatigue;
    u8         master_id; /* MasterId */
    Stats      stats;
    Stats      base;
    AbilitySet abilities;
    u8         master_level; /* the level when the current master was assigned */
    u8         level_up_modifiers[CHARACTER_LEVEL_MODIFIER_COUNT];
    u8         unk_8B[0x19];
} Character;

ASSERT_SIZE(Character, PARTY_RECORD_STRIDE);

/* The block from the window-style byte 0x80144952 through the eight character
 * records at 0x80144968. The menu drawers read the style byte and then index a
 * record from the same base address, so the records are byte rows here: the
 * block starts 0x16 bytes before the first record, and a Character
 * member would align to 0x18. Cast a row to Character to read fields.
 *
 * Reader: `emi/etc/shop/00@0x801E1710` loads the style byte through the
 * base register, then adds 0x90 (0x16 plus the skill-ability offset) to it. */
typedef struct Char_Block {
    u8 window_style; /* 0x00: the last argument of UI_DrawWindow */
    u8 pad_01[0x15];
    u8 records[8][PARTY_RECORD_STRIDE]; /* 0x16: the Character rows */
} Char_Block;

ASSERT_OFFSET(Char_Block, records, CHARACTER_BLOCK_RECORDS);
ASSERT_SIZE(Char_Block, CHARACTER_BLOCK_RECORDS + 8 * PARTY_RECORD_STRIDE);

typedef struct MasterSkills {
    u8 skill_levels[MASTER_SKILL_COUNT][2];
} MasterSkills;

ASSERT_SIZE(MasterSkills, MASTER_SKILLS_STRIDE);

typedef struct MasterStats {
    s8 hp_bonus;
    s8 ap_bonus;
    s8 power_bonus;
    s8 defense_bonus;
    s8 agility_bonus;
    s8 intellect_bonus;
} MasterStats;

ASSERT_SIZE(MasterStats, MASTER_STATS_STRIDE);

typedef struct LevelGrowth {
    u16 exp;
    u8  hp;
    u8  ap;
    u8  power_defense;
    u8  agility_intellect;
    u8  ability;
    u8  extra_ability; /* Char_GetExp learns both ability bytes through Char_AddAbility */
} LevelGrowth;

ASSERT_SIZE(LevelGrowth, LEVEL_STRIDE);
ASSERT_OFFSET(LevelGrowth, exp, 0x00);
ASSERT_OFFSET(LevelGrowth, hp, 0x02);
ASSERT_OFFSET(LevelGrowth, ap, 0x03);
ASSERT_OFFSET(LevelGrowth, power_defense, 0x04);
ASSERT_OFFSET(LevelGrowth, agility_intellect, 0x05);
ASSERT_OFFSET(LevelGrowth, ability, 0x06);
ASSERT_OFFSET(LevelGrowth, extra_ability, 0x07);

typedef struct CharacterSprites {
    u32 section_offset[CHARACTER_SPRITES_SECTION_COUNT]; /* 0x00 from the container base */
} CharacterSprites;

typedef struct CharacterSpritesSection {
    u32 unk_00;         /* 0x00 16 in the sampled sections; no reader */
    u32 palette_offset; /* 0x04 section-relative offset of the palette table */
} CharacterSpritesSection;

ASSERT_SIZE(CharacterSprites, 0x0C);
ASSERT_OFFSET(CharacterSpritesSection, palette_offset, 0x04);

/* The party's character records, one per CHAR_INDEX_*. Every field/menu reader
 * indexes it through the g_CharSlot slot of a stored character id. */
/* D_80144968 */
extern Character   g_Characters[CHARACTER_COUNT];
/* D_801CB8DC */
extern LevelGrowth g_LevelGrowth[LEVEL_GROWTH_CHARACTER_COUNT][LEVEL_GROWTH_LEVEL_COUNT];

#endif
