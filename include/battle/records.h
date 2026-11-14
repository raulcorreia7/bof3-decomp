#ifndef BATTLE_RECORDS_H
#define BATTLE_RECORDS_H

/* The battle records that the two battle overlays (emi/battle/battle/03
 * and emi/battle/battle/15) declare alike: one definition per record, here,
 * so the two overlays read the same bytes through the same members.
 *
 * Both overlays declare these globals with these types, so the same objects
 * are read through the same members and not through two look-alikes.
 *
 *   g_Battle.action   BattleAction *        battle family header (src/overlays/battle/battle.h)
 *   D_801463DC   EncounterEnemy[]   battle/battle/15 image header, etc/game/00 image header
 *   D_801ED9B0   PanelOwner[]  battle family header (src/overlays/battle/battle.h)
 *   D_801CA71C   BattleSelectionType[]    battle family header (src/overlays/battle/battle.h)
 *
 * Where the two overlays name one member differently, the retail access
 * decides: the comment on each member records which unit reads it. */

#include "battle/handlers.h"
#include "common/handler.h"
#include "common/fixed.h"
#include "common/vector.h"
#include "game/character.h"
#include "game/enemy.h"
#include "game/records.h"
#include "psx/mem.h"
#include "slus/facing.h"
#include "types.h"
#include "sys/task.h"

#define BATTLE_PANEL_BYTE_CELLS_SIZE 0x1E

/* The signed stat modifier bytes an enemy battler carries from +0x108. */
#define ENEMY_STAT_MULTIPLIER_COUNT  8

/* The enemy battler work record (stride 0x118 at 0x801EB630).
 *
 * Both battle overlays declare g_BattleEnemyBattlers as EnemyBattler and read the same
 * table, so this is one record: the union of both overlays' halves.
 *
 * The cells from +0x06 to +0x5F are the ones the slot setup (Battle_InitEnemy
 * and Battle_AddEnemy) clears when it arms an enemy slot; their widths follow
 * those accesses. No reader names them yet, so they keep the address names. */

/* Ask whether the battler's status word carries the flag, a STATUS_* value or a
 * mask. Pass the row itself or, for a pointer, its dereference. */
#define HAS_STATUS(battler, flag)    (((battler).chr.status & (flag)) != 0)

/* The active battler's row. Each battle overlay declares the active-battler
 * byte itself, so the macro expands where it is used. */
#define BATTLE_ACTIVE_PARTY          (g_Game.members[g_Battle.active_battler])

/* The action a battler has queued: whom it targets, what kind it is (examine 0, attack 1, defend 2, ability 4, item 5)
 * and the ability or item id. */
typedef enum BattleCommandType {
    BATTLE_COMMAND_EXAMINE = 0,
    BATTLE_COMMAND_ATTACK  = 1,
    BATTLE_COMMAND_DEFEND  = 2,
    BATTLE_COMMAND_ESCAPE  = 3,
    BATTLE_COMMAND_ABILITY = 4,
    BATTLE_COMMAND_ITEM    = 5,
} BattleCommandType;

typedef struct BattleCommandSlot {
    u8  target;
    u8  type;
    u16 id;
} BattleCommandSlot;

ASSERT_SIZE(BattleCommandSlot, 0x04);

/* Half of a 0x20-byte battler stat block. The retail copies each half with an
 * unaligned word pair, so the two halves stay one 16-byte type. */
typedef struct BattleStatBlockPart {
    u8 bytes[0x10];
} BattleStatBlockPart;

ASSERT_SIZE(BattleStatBlockPart, 0x10);

/* Record behind the g_Battle.action cell; +0x01 is the action kind and +0x02 the action id. */
typedef struct BattleAction {
    u8  pad_00[1];
    u8  type; /* +0x01 mirrors g_Battle.action_type */
    u16 unk_02;
    u8  pad_04[4];
    u8  unk_08; /* +0x08 step byte: func_8009E248 sets 1, func_8009E500 sets 2 */
} BattleAction;

ASSERT_SIZE(BattleAction, 0x0A);

ASSERT_OFFSET(BattleAction, type, 0x01);
ASSERT_OFFSET(BattleAction, unk_02, 0x02);
ASSERT_OFFSET(BattleAction, unk_08, 0x08);

/* One entry of the candidate table at 0x801463DC: eight rows of 0x0C bytes
 * that the game overlay fills before a wild encounter and the battle overlay
 * walks to place the enemy.
 *
 *   emi/etc/game/00 Area_RollEncounterEnemies   writes the id at +0x01 and the live flag
 *                                    at +0x00
 *   emi/etc/game/00 Area_PlaceEncounterEnemies   writes the encounter position at +0x04
 *                                    and +0x08
 *   emi/battle/battle/15 func_800ABC30 reads all three and hands the id, the
 *                                    x and the y to Battle_InitEnemy
 *
 * The id is the index of one 0x88-byte enemy record (Battle_InitEnemy reads
 * &D_800E405E + id * 0x88), so +0x01 is that index and 0xFF means none. */
typedef struct EncounterEnemy {
    u8      active; /* 0x00 - set by the game overlay, cleared when the candidate is out of reach */
    u8      id;     /* 0x01 - the enemy-record index; 0xFF means none */
    u8      pad_02[2];
    Point2l pos; /* 0x04 encounter position, 16.16 */
} EncounterEnemy;

ASSERT_SIZE(EncounterEnemy, 0x0C);
ASSERT_OFFSET(EncounterEnemy, id, 0x01);
ASSERT_OFFSET(EncounterEnemy, pos, 0x04);

/* One entry of the panel-owner table at 0x801ED9B0: the owner index, a second
 * byte, and the panel id. */
typedef struct PanelOwner {
    u8  owner_index;
    u8  unk_01;
    u16 panel_id;
} PanelOwner;

ASSERT_SIZE(PanelOwner, 0x04);
ASSERT_OFFSET(PanelOwner, owner_index, 0x00);
ASSERT_OFFSET(PanelOwner, panel_id, 0x02);

/* One entry of the selection table g_BattleSelections: the id battle/battle/03 tests
 * against 0xFFFF and battle/battle/15 reads, and the handler. 8 bytes. */
typedef struct BattleSelection {
    u16      id;
    u16      unk_02;
    Callback handler;
} BattleSelection;

ASSERT_SIZE(BattleSelection, 0x08);
ASSERT_OFFSET(BattleSelection, id, 0x00);
ASSERT_OFFSET(BattleSelection, handler, 0x04);

/* One entry of the selection-type table at 0x801CA71C: a mask halfword and the
 * rest of the 0x14-byte row, which battle/battle/15 reads byte by byte. */
typedef struct BattleSelectionType {
    u16 mask;
    u8  unk_02[0x12];
} BattleSelectionType;

ASSERT_SIZE(BattleSelectionType, 0x14);
ASSERT_OFFSET(BattleSelectionType, mask, 0x00);

/* The word at +0x60 of a queued slot. battle/battle/15 stores the action's target
 * index there (func_800AAEBC) and battle/battle/03 reads the low halfword of it to
 * draw the capture count (func_801E5CA4 loads it with `lhu` and hands it to
 * func_801D9684), so the cell carries both widths. */
typedef union BattleTargetIndex {
    s32 target_index;  /* the action's target index, as battle/battle/15 stores it */
    u16 capture_count; /* the low halfword, as battle/battle/03 draws it */
} BattleTargetIndex;

/* What a queued effect acts on: a party or enemy battler, another effect, or a payload address. */
typedef union BattleEffectTarget {
    struct PartyMember*  party;
    struct EnemyBattler* enemy;
    struct BattleEffect* effect;
    u8*                  bytes;
    u32                  address;
} BattleEffectTarget;

/* The byte a spawner sets for its effect (a start count, a grid row); on a
 * battler's home row it is the signed sway of a confused battler, -11 to 12. */
typedef union BattleEffectArg {
    u8 unk_09;
    s8 sway;
} BattleEffectArg;

ASSERT_SIZE(BattleEffectArg, 1);

/* One queued action slot of the table at 0x801EC330 (stride 0x78).
 *
 * Both overlays declare g_BattleEffects as BattleEffect and read the same
 * table, so this is one record. The two overlays name different halves of it:
 * battle/battle/03 names the head fields, battle/battle/15 the tail, and the merged record
 * names the union of both. */
typedef struct BattleEffect {
    TaskHeader          header; /* 0x00 */
    u8                  unk_03;
    u8                  unk_04;
    u8                  handler_index; /* +0x05 indexes a mode's handler table; Battle_AllocEffect stores it */
    u8                  unk_06;
    u8                  unk_07;
    u8                  unk_08;
    BattleEffectArg     arg;
    u8                  unk_0A;
    u8                  unk_0B;
    s32                 unk_0C;
    s32                 unk_10;
    u8                  pad_14[4];
    s32                 unk_18;
    s32                 unk_1C;
    u8                  pad_20[7];
    u8                  unk_27;
    u8                  unk_28;
    u8                  unk_29; /* +0x29 func_801DE1D4 stores an action step here */
    u8                  pad_2A[4];
    s16                 unk_2E;
    s16                 unk_30;
    u16                 unk_32;
    WorldPos            pos; /* +0x34 x, y and z; bmagic stores the z span halfword (+0x3E) */
    u8                  pad_40[8];
    u8                  unk_48;
    u8                  pad_49[2];
    u8                  unk_4B; /* +0x4B the panel cell index battle/battle/15 stores */
    struct PartyMember* unk_4C; /* +0x4C a linked battle task; magic078 hands its phase to it through param */
    u8                  pad_50[0xC];
    u8                  unk_5C; /* +0x5C func_801DE1D4 clears it with the byte row below */
    u8                  unk_5D;
    u8                  unk_5E;
    u8                  unk_5F;
    BattleTargetIndex   word_60; /* +0x60 the target index: a word, a low halfword */
    u8                  pad_64[0x10];
    BattleEffectTarget  target; /* +0x74 the battler the effect acts on */
} BattleEffect;

ASSERT_SIZE(BattleEffect, 0x78);
ASSERT_OFFSET(BattleEffect, unk_07, 0x07);
ASSERT_OFFSET(BattleEffect, unk_08, 0x08);
ASSERT_OFFSET(BattleEffect, unk_2E, 0x2E);
ASSERT_OFFSET(BattleEffect, unk_30, 0x30);
ASSERT_OFFSET(BattleEffect, unk_32, 0x32);
ASSERT_OFFSET(BattleEffect, handler_index, 0x05);
ASSERT_OFFSET(BattleEffect, unk_27, 0x27);
ASSERT_OFFSET(BattleEffect, unk_29, 0x29);
ASSERT_OFFSET(BattleEffect, unk_4B, 0x4B);
ASSERT_OFFSET(BattleEffect, unk_4C, 0x4C);
ASSERT_OFFSET(BattleEffect, unk_5C, 0x5C);
ASSERT_OFFSET(BattleEffect, word_60, 0x60);
ASSERT_OFFSET(BattleEffect, target, 0x74);

/* A flag word of a battle work record. The overlays test and set bits through
 * `value`; the ones that race the other overlay's tasks read `volatile_value`. */
typedef union BattlerFlags {
    u32          value;
    volatile u32 volatile_value;
} BattlerFlags;

/* One battler's turn: the command it queued, the HP and AP the hit deals, the
 * target state bits and counter, and the damage and action flag words. Both
 * battler records embed it as `turn`; g_BattleActorTurn and g_Battle.target_record
 * point at it. */
typedef struct BattleTurn {
    BattleCommandSlot command;
    s16               hp_change; /* signed HP delta shown on the hit; negative heals */
    s16               ap_change; /* signed AP delta, as hp_change */
    u8                target_flags;
    u8                counter;
    u8                choice; /* the menu choice stored with the command */
    u8                unk_0B;
    BattlerFlags      damage_flags; /* BattleBattlerDamageFlags */
    BattlerFlags      action_flags; /* BattleBattlerActionFlags */
} BattleTurn;

ASSERT_SIZE(BattleTurn, 0x14);
ASSERT_OFFSET(BattleTurn, hp_change, 0x04);
ASSERT_OFFSET(BattleTurn, target_flags, 0x08);
ASSERT_OFFSET(BattleTurn, damage_flags, 0x0C);
ASSERT_OFFSET(BattleTurn, action_flags, 0x10);

/* A screen coordinate cell: battle/battle/03 and the field overlays read it
 * unsigned, battle/battle/15 reads it signed because the panels slide to
 * negative screen positions (Actor names +0x2E/+0x30 screen_x and
 * screen_y). */
typedef union ScreenCoord {
    u16 half;
    s16 signed_half;
} ScreenCoord;

/* The cell at +0x90 of a local work record: battle/battle/03 reads the halfword, and
 * battle/battle/15 reads the low byte of it. */
typedef union BattleWorkHalfOrByte90 {
    u16 half;
    u8  value;
} BattleWorkHalfOrByte90;

/* The cell at +0x0A of a battle panel task. battle/battle/03 reads it as the
 * selected battler slot (the row index is slot - 3) and battle/battle/15 reads it
 * as the panel's slide mode (0 moves the panel right), so the cell carries
 * both readings. */
typedef union BattlePanelCell0A {
    u8 slot;
    u8 mode;
} BattlePanelCell0A;

/* The byte view of a battle panel task's +0x12 and +0x14 cells. battle/battle/15
 * reads those cells as bytes (Battle_DrawCommandList, func_800B0F9C) and as
 * halfwords, so the cells keep two views. This view starts at the panel
 * task's base, so a unit that holds the panel pointer reads the bytes
 * through it. */
typedef struct BattlePanelByteCells {
    u8 pad_00[0x12];
    u8 scale; /* +0x12 the box drawer's scale */
    u8 pad_13[1];
    u8 rows; /* +0x14 the rows the drawer draws */
    u8 pad_15[0x09];
} BattlePanelByteCells;

ASSERT_SIZE(BattlePanelByteCells, BATTLE_PANEL_BYTE_CELLS_SIZE);
ASSERT_OFFSET(BattlePanelByteCells, scale, 0x12);
ASSERT_OFFSET(BattlePanelByteCells, rows, 0x14);

/* The battle panel task at 0x80148648 (g_MenuCurrentPanel).
 *
 * Both battle overlays read that one root through their own BattlePanelTask
 * declaration, and the shared MenuPanelTask in include/menu/panel.h holds the
 * same record. The battle reading names the cells the battle panel code uses;
 * the other overlays read the same bytes through MenuPanelTask.
 *
 * battle/battle/15 reads the first 0x0C bytes only, and reads the x and y cells
 * signed, because the panel slides to negative screen positions. */
typedef struct BattlePanelTask {
    u8                unk_00[3]; /* +0x00 */
    u8                state;     /* +0x03 short-menu state word */
    ScreenCoord       x;         /* +0x04 the panel x; battle/battle/15 reads it signed */
    ScreenCoord       y;         /* +0x06 the panel y; battle/battle/15 reads it signed */
    u8                unk_08;
    u8                unk_09;
    BattlePanelCell0A cell_0A; /* +0x0A the selected battler slot, or the slide mode */
    u8                ratio;   /* +0x0B enemy value * 0x37 / divisor, floored at 1 */
    u8                unk_0C;
    u8                cursor;    /* +0x0D cleared on panel entry */
    u8                pad_0E[4]; /* +0x0E .. +0x11 */
    u16               row_base;  /* +0x12 the panel list's first row (Battle_DrawCommandList) */
    u16               hp;        /* +0x14 copied from EnemyBattler.hp; the HP bar's numerator */
    u8                pad_16[6]; /* +0x16 .. +0x1B */
    u16               max_hp;    /* +0x1C copied from EnemyBattler.stats.max_hp; the HP bar's divisor */
} BattlePanelTask;

ASSERT_SIZE(BattlePanelTask, 0x1E);
ASSERT_OFFSET(BattlePanelTask, state, 0x03);
ASSERT_OFFSET(BattlePanelTask, x, 0x04);
ASSERT_OFFSET(BattlePanelTask, y, 0x06);
ASSERT_OFFSET(BattlePanelTask, cell_0A, 0x0A);
ASSERT_OFFSET(BattlePanelTask, row_base, 0x12);
ASSERT_OFFSET(BattlePanelTask, hp, 0x14);
ASSERT_OFFSET(BattlePanelTask, max_hp, 0x1C);

typedef struct EnemyBattler {
    TaskHeader  header; /* 0x00 */
    u8          unk_03;
    u8          unk_04;
    u8          slot;   /* +0x05 battler slot; Battle_InitEnemy stores slot + 3 here */
    u8          unk_06; /* +0x06 cleared when the slot is armed */
    u8          unk_07; /* +0x07 cleared when the slot is armed */
    u8          unk_08; /* +0x08 the battle index with its low bit flipped */
    u8          pad_09[0x3];
    s32         unk_0C; /* +0x0C cleared when the slot is armed */
    s32         unk_10; /* +0x10 cleared when the slot is armed */
    s32         unk_14; /* +0x14 cleared when the slot is armed */
    s32         unk_18; /* +0x18 cleared when the slot is armed */
    s32         unk_1C; /* +0x1C cleared when the slot is armed */
    s32         unk_20; /* +0x20 cleared when the slot is armed */
    u8          unk_24; /* +0x24 cleared when the slot is armed */
    u8          pad_25[0x4];
    u8          unk_29; /* +0x29 set to 4 when the slot is armed */
    u8          pad_2A[0x1];
    u8          unk_2B; /* +0x2B cleared when the slot is armed */
    u8          pad_2C[0x2];
    s16         unk_2E; /* +0x2E cleared when the slot is armed */
    s16         unk_30; /* +0x30 cleared when the slot is armed */
    s16         unk_32; /* +0x32 cleared when the slot is armed */
    WorldPos    pos;    /* +0x34 the enemy's x, y and z; the slot setup stores the vertical span in z */
    u8          pad_40[0x8];
    u8          unk_48; /* +0x48 cleared when the slot is armed */
    u8          pad_49[0x2];
    u8          unk_4B; /* +0x4B set to 0xFF when the slot is armed */
    u8          pad_4C[0xC];
    u16         unk_58; /* +0x58 the halfword the boss end-of-battle setup copies to the spad record */
    u16         unk_5A; /* +0x5A the halfword the boss end-of-battle setup copies to the spad record */
    u8          unk_5C; /* +0x5C cleared when the slot is armed */
    u8          unk_5D; /* +0x5D cleared when the slot is armed */
    u8          unk_5E; /* +0x5E cleared when the slot is armed */
    u8          unk_5F; /* +0x5F cleared when the slot is armed */
    u8          pad_60[0x14];
    u8          name[8]; /* +0x74 the 8-character enemy name, drawn as text by Battle_DrawEnemyNamePanel */
    EnemyIdCode enemy_id;
    u8          choice_ai;
    u8          unk_7F;                    /* +0x7F battle/battle/03's cell; battle/battle/15 leaves it padded */
    u16         event_flags;               /* +0x80 battle/battle/03's cell; battle/battle/15 leaves it padded */
    u16         status;                    /* +0x82 StatusFlags; Battle_DefeatEnemy sets STATUS_KO when the enemy leaves the field */
    u16         zenny;                     /* +0x84 added to the battle reward by Battle_DefeatEnemy */
    u16         exp;                       /* +0x86 added to the battle reward by Battle_DefeatEnemy */
    u16         level;                     /* +0x88 the turn-order ranking and the base damage read it */
    u16         unk_8A;                    /* +0x8A set from the area scene record when the slot is armed */
    u8          skills[ENEMY_SKILL_COUNT]; /* +0x8C the bytes func_8009C994 copies the event packet's tail into */
    u16         hp;
    u16         ap; /* +0x96 battle/battle/03's cell; battle/battle/15 leaves it padded */
    EnemyDrop   drops[2];
    Stats       stats; /* +0xA0 the live stats; the capture cap and the hit math read it */
    Stats       base;  /* +0xC0 the stats before buffs */
    u8          kind;
    u8          triggered_events; /* +0xE1 one bit per event packet already applied */
    s8          panel_offset_x;   /* +0xE2 added to the panel's screen x, as the party's g_BattlePanelOffsets entry */
    s8          panel_offset_y;   /* +0xE3 added to the panel's screen y */
    ModeFunc    unk_E4;
    u16*        unk_E8;
    u8*         script;
    u8          unk_F0;
    u8          unk_F1;
    u8          pad_F2[2];
    BattleTurn  turn;                                          /* +0xF4 the action the enemy has queued and its outcome */
    s8          stat_multipliers[ENEMY_STAT_MULTIPLIER_COUNT]; /* +0x108 the first four modify power, defense, agility and intellect */
    u8          pad_110[2];
    u8          unk_112;
    u8          unk_113;
    u8          unk_114;
    u8          unk_115;
    u8          pad_116[0x2];
} EnemyBattler;

ASSERT_SIZE(EnemyBattler, 0x118);
ASSERT_OFFSET(EnemyBattler, slot, 0x05);
ASSERT_OFFSET(EnemyBattler, unk_06, 0x06);
ASSERT_OFFSET(EnemyBattler, unk_08, 0x08);
ASSERT_OFFSET(EnemyBattler, unk_0C, 0x0C);
ASSERT_OFFSET(EnemyBattler, unk_20, 0x20);
ASSERT_OFFSET(EnemyBattler, unk_24, 0x24);
ASSERT_OFFSET(EnemyBattler, unk_29, 0x29);
ASSERT_OFFSET(EnemyBattler, unk_2B, 0x2B);
ASSERT_OFFSET(EnemyBattler, unk_2E, 0x2E);
ASSERT_OFFSET(EnemyBattler, unk_30, 0x30);
ASSERT_OFFSET(EnemyBattler, unk_32, 0x32);
ASSERT_OFFSET(EnemyBattler, pos, 0x34);
ASSERT_OFFSET(EnemyBattler, unk_48, 0x48);
ASSERT_OFFSET(EnemyBattler, unk_4B, 0x4B);
ASSERT_OFFSET(EnemyBattler, unk_58, 0x58);
ASSERT_OFFSET(EnemyBattler, unk_5A, 0x5A);
ASSERT_OFFSET(EnemyBattler, unk_5C, 0x5C);
ASSERT_OFFSET(EnemyBattler, unk_5F, 0x5F);
ASSERT_OFFSET(EnemyBattler, status, 0x82);
ASSERT_OFFSET(EnemyBattler, unk_8A, 0x8A);
ASSERT_OFFSET(EnemyBattler, skills, 0x8C);
ASSERT_OFFSET(EnemyBattler, hp, 0x94);
ASSERT_OFFSET(EnemyBattler, enemy_id, 0x7C);
ASSERT_OFFSET(EnemyBattler, choice_ai, 0x7E);
ASSERT_OFFSET(EnemyBattler, zenny, 0x84);
ASSERT_OFFSET(EnemyBattler, exp, 0x86);
ASSERT_OFFSET(EnemyBattler, stats, 0xA0);
ASSERT_OFFSET(EnemyBattler, base, 0xC0);
ASSERT_OFFSET(EnemyBattler, kind, 0xE0);
ASSERT_OFFSET(EnemyBattler, turn, 0xF4);
ASSERT_OFFSET(EnemyBattler, unk_E8, 0xE8);

/* Point a boss enemy at its script, event handler and step table. */
static inline void EnemyBattler_SetScript(EnemyBattler* enemy, u8* script, ModeFunc handler, u16* steps) {
    enemy->script = script;
    enemy->unk_E4 = handler;
    enemy->unk_E8 = steps;
}

/* The kind walk: `D_8014833A[i]` is the owner table's record `i` seen at +0x07
 * (0x8014833A = 0x80148333 + 7, stride 0x24). Kept as its own name because the
 * units index it as an array; battle/battle/03 (func_801DA69C) names both walks. */
typedef struct BattleOwner {
    u8 kind_00;      /* 0x00 - record +0x07 of the owner table */
    u8 pad_01[0x23]; /* 0x01-0x23 */
} BattleOwner;

ASSERT_SIZE(BattleOwner, 0x24);

/* Ability category records at 0x801CA719 have a 0x14-byte stride: the ability byte at
 * +0x00, the rest unnamed. Char_GetAbilities reads the low two bits. */
typedef volatile struct BattleAbilityCategory {
    u8 value;
    u8 pad_001[0x13];
} BattleAbilityCategory;

ASSERT_SIZE(BattleAbilityCategory, 0x14);

typedef enum PartyMemberFlags {
    PARTY_MEMBER_FLAG_OCCUPIED     = 1 << 0,
    PARTY_MEMBER_FLAG_HANDLER_BUSY = 1 << 6,
} PartyMemberFlags;

typedef union BattlerParam {
    u8 unk_0B;
    u8 phase;
} BattlerParam;

ASSERT_SIZE(BattlerParam, 1);

/* A one-byte counter that field code reads signed or unsigned. */
typedef union PanelCounter {
    s8 s8_value;
    u8 u8_value;
} PanelCounter;

/* The field's view of the 0x14 bytes where a battle row keeps its queued turn: the menu and scene code reuse them
 * as panel and mode counters while no battle runs. */
typedef struct FieldMode {
    u8           flags_118;     /* 0x00 bit 0x80 restores the saved word */
    u8           countdown_119; /* 0x01 frame countdown, reloaded with 0x28 or 0x0A */
    u8           pad_02[2];
    PanelCounter counter_11C; /* 0x04 panel step counter */
    u8           pad_05;
    u8           kind_11E;  /* 0x06 record kind */
    u8           wait_11F;  /* 0x07 shared wait countdown */
    u16          value_120; /* 0x08 copied into the record's 0x7C */
    u16          unk_122;   /* 0x0A lowered by 2 per step; @source: write:func_801F3B9C@0x801F3B9C */
    u32          index_124; /* 0x0C slot index passed to the selector */
    u8           pad_10[2];
    PanelCounter step_12A; /* 0x12 */
    PanelCounter mode_12B; /* 0x13 panel mode */
} FieldMode;

ASSERT_SIZE(FieldMode, 0x14);
ASSERT_OFFSET(FieldMode, counter_11C, 0x04);
ASSERT_OFFSET(FieldMode, value_120, 0x08);
ASSERT_OFFSET(FieldMode, index_124, 0x0C);
ASSERT_OFFSET(FieldMode, mode_12B, 0x13);

/* The field's view of the eight cells after the turn: the flags that gate the entry check and the entity slot. */
typedef struct FieldEntry {
    PanelCounter flags_12C; /* 0x00 bit 0x01/0x08 gate the entry check */
    u8           slot_12D;  /* 0x01 entity slot index */
    u8           pad_02[6];
} FieldEntry;

ASSERT_SIZE(FieldEntry, 0x08);

/* One party member's live work record: the task header, a copy of the member's Character and the state the field and
 * the battle keep in it. */
typedef struct PartyMember {
    TaskHeader          header; /* 0x00 */
    u8                  unk_03;
    u8                  unk_04;
    u8                  slot; /* +0x05 battler slot; func_801DC044 passes it to func_800A36F0 */
    u8                  pad_06;
    u8                  unk_07;
    u8                  facing; /* +0x08 the direction the battler faces */
    u8                  unk_09;
    u8                  timer; /* +0x0A frame counter */
    BattlerParam        param;
    s32                 unk_0C;
    s32                 unk_10;
    s32                 unk_14; /* +0x14 the 32-bit cell both overlays read */
    s32                 unk_18;
    s32                 unk_1C; /* +0x1C battle/battle/03's cell; battle/battle/15 leaves it padded */
    s32                 unk_20; /* +0x20 the 32-bit cell both overlays read */
    u8                  unk_24;
    u8                  unk_25;
    u8                  unk_26;
    u8                  unk_27;
    u8                  unk_28;
    s8                  unk_29; /* +0x29 the byte both overlays read */
    s8                  unk_2A; /* +0x2A the byte both overlays read */
    s8                  unk_2B; /* +0x2B the byte both overlays read */
    ScreenCoord         unk_2C; /* +0x2C the halfword both overlays read */
    ScreenCoord         unk_2E; /* +0x2E the field overlays read it signed */
    ScreenCoord         unk_30; /* +0x30 the field overlays read it signed */
    u16                 depth;  /* +0x32 depth halfword; func_800AB910 calls it off_z */
    WorldPos            pos;
    SpriteScale         scale;  /* +0x40 16.16, 0x10000 at setup */
    u8                  unk_48; /* +0x48 battle/battle/03's cell; battle/battle/15 leaves it padded */
    u8                  unk_49;
    u8                  unk_4A;
    u8                  unk_4B;
    struct PartyMember* unk_4C; /* +0x4C a linked battle task; magic078 hands its phase to it through param */
    s32                 unk_50;
    s32                 unk_54;
    u16                 unk_58;
    u16                 unk_5A;
    u8                  unk_5C;
    u8                  unk_5D;
    u8                  unk_5E;
    u8                  unk_5F;
    s32                 unk_60; /* +0x60 the cell func_8014D290 stores the rotation in; bmagic effects read its low halfword */
    s32                 unk_64; /* +0x64 the offset magic109 sweeps between -0x7F and 0x80 in steps of 8 */
    u8                  pad_68[8];
    u8                  unk_70;
    u8                  pad_71[3];
    /* +0x74..+0x117 is a Character copy: func_801DD08C copies a
     * 0xA4-byte character record to this offset. */
    Character           chr;

    /* +0x118 battle keeps the action the player has queued and its outcome; the field reuses the bytes as counters */
    union {
        BattleTurn turn;
        FieldMode  field;
    } u;

    /* +0x12C battle clears all eight cells when the battler falls; the field names two of them */
    union {
        u8         unk_12C[8];
        FieldEntry field;
    } status;

    u16 unk_134;
    u8  counter_136;
    u8  counter_137;
    u8  focus_counter; /* +0x138 the Focus counter, 0..2; Battle_CalcDamage spends it as a power bonus */
    u8  unk_139;
    u8  unk_13A[2];
    u8  character_index; /* +0x13C the Character slot this battler was built from */
    u8  unk_13D;         /* the palette fade index; @source: write:func_801AAB00@0x801AAB00 */
    u8  pad_13E[2];
} PartyMember;

ASSERT_SIZE(PartyMember, 0x140);
ASSERT_OFFSET(PartyMember, slot, 0x05);
ASSERT_OFFSET(PartyMember, u, 0x118);
/* The four bytes at +0x08 as one word; the bmagic tests mask it. */
#define PARTY_MEMBER_WORD_08(battler) (*(u32*)&(battler)->facing)

ASSERT_OFFSET(PartyMember, facing, 0x08);
ASSERT_OFFSET(PartyMember, unk_09, 0x09);
ASSERT_OFFSET(PartyMember, timer, 0x0A);
ASSERT_OFFSET(PartyMember, param, 0x0B);
ASSERT_OFFSET(PartyMember, unk_14, 0x14);
ASSERT_OFFSET(PartyMember, unk_20, 0x20);
ASSERT_OFFSET(PartyMember, unk_60, 0x60);
ASSERT_OFFSET(PartyMember, unk_70, 0x70);
ASSERT_OFFSET(PartyMember, unk_29, 0x29);
ASSERT_OFFSET(PartyMember, unk_2C, 0x2C);
ASSERT_OFFSET(PartyMember, depth, 0x32);
ASSERT_OFFSET(PartyMember, pos, 0x34);
ASSERT_OFFSET(PartyMember, chr, 0x74);
ASSERT_OFFSET(PartyMember, status, 0x12C);
ASSERT_OFFSET(PartyMember, unk_13A, 0x13A);
ASSERT_OFFSET(PartyMember, focus_counter, 0x138);
ASSERT_OFFSET(PartyMember, character_index, 0x13C);

/* The damage/status word: `damage_flags` of the enemy row, `damage_flags` of the
 * player row. Bit 6 marks a marked damage target; bit 7 runs the popup digits
 * and countdown; bit 8 makes the hit lethal and queues the reaction cue; bit 9
 * marks a damage row present; bit 12 skips the action gate; bit 15 counters;
 * bit 16 zeroes damage and the HP-bar numerator. */
typedef enum BattleBattlerDamageFlags {
    COMBATANT_FLAG_COMMAND_ENTERED     = 1 << 0,
    COMBATANT_FLAG_DEFENDING           = 1 << 1,
    COMBATANT_FLAG_WILLPOWER_SURVIVED  = 1 << 2,
    COMBATANT_FLAG_UNK_3               = 1 << 3,
    COMBATANT_FLAG_UNK_4               = 1 << 4,
    COMBATANT_FLAG_UNK_5               = 1 << 5,
    COMBATANT_FLAG_DAMAGED             = 1 << 6,
    COMBATANT_FLAG_DAMAGE_NUMBER       = 1 << 7,
    COMBATANT_FLAG_HURT_REACTION       = 1 << 8,
    COMBATANT_FLAG_DAMAGE_ROW_PRESENT  = 1 << 9,
    COMBATANT_FLAG_UNK_11              = 1 << 11,
    COMBATANT_FLAG_SKIP_ACTION_STEP    = 1 << 12,
    COMBATANT_FLAG_FORM_EFFECT_PLAYING = 1 << 13,
    COMBATANT_FLAG_UNK_14              = 1 << 14,
    COMBATANT_FLAG_REPRISAL            = 1 << 15,
    COMBATANT_FLAG_DAMAGE_IMMUNE       = 1 << 16,
} BattleBattlerDamageFlags;

/* The action/pending word: `action_flags` of the enemy row, `action_flags` of the
 * player row. Bit 3 marks a mode handler action installed; bit 4 keeps the row
 * available during the suppression countdown; bit 6 applies the queued power
 * boost; bit 9 halves the damage; bits 11 and 13 zero the holy and fire
 * resistance; bit 14 charges the action; bit 15 marks a preemptive turn; bit 16
 * marks the berserk Kaiser form; bit 17 lets the player steer a Kaiser form,
 * otherwise the command cursor stays locked. */
typedef enum BattleBattlerActionFlags {
    COMBATANT_FLAG_DRAGON_FORM_QUEUED     = 1 << 0,
    COMBATANT_FLAG_DRAGON_FORM            = 1 << 1,
    COMBATANT_FLAG_ABILITY_ALT_POSE       = 1 << 2,
    COMBATANT_FLAG_MODE_HANDLER_ACTION    = 1 << 3,
    COMBATANT_FLAG_SUPPRESSION_EXEMPT     = 1 << 4,
    COMBATANT_FLAG_ACTION_UNK_5           = 1 << 5,
    COMBATANT_FLAG_POWER_BOOST            = 1 << 6,
    COMBATANT_FLAG_MEDITATION             = 1 << 7,
    COMBATANT_FLAG_ALWAYS_HITS            = 1 << 8,
    COMBATANT_FLAG_SELECT_EXCLUDED        = 1 << 10,
    COMBATANT_FLAG_DAMAGE_HALVED          = 1 << 9,
    COMBATANT_FLAG_HOLY_RESIST_ZERO       = 1 << 11,
    COMBATANT_FLAG_SELECTION_BONUS        = 1 << 12,
    COMBATANT_FLAG_FIRE_RESIST_ZERO       = 1 << 13,
    COMBATANT_FLAG_CHARGING               = 1 << 14,
    COMBATANT_FLAG_PREEMPTIVE_TURN        = 1 << 15,
    COMBATANT_FLAG_DRAGON_FORM_BERSERK    = 1 << 16,
    COMBATANT_FLAG_DRAGON_FORM_CONTROLLED = 1 << 17,
    COMBATANT_FLAG_SELECTED               = 1 << 18,
} BattleBattlerActionFlags;

/* BattleTurn.target_flags: what a hit did to its target. The HP bits (0, 2, 4) and the AP bits (1, 3, 5)
 * mirror each other: a hit starts with HIT_HP and HIT_HP_LANDED set, the miss rolls clear the LANDED bit, and a heal that
 * stops at the maximum sets the MAX bit. */
typedef enum BattleHitFlags {
    BATTLE_HIT_HP        = 1 << 0,
    BATTLE_HIT_AP        = 1 << 1,
    BATTLE_HIT_HP_MAX    = 1 << 2,
    BATTLE_HIT_AP_MAX    = 1 << 3,
    BATTLE_HIT_HP_LANDED = 1 << 4,
    BATTLE_HIT_AP_LANDED = 1 << 5,
} BattleHitFlags;

/* The game's party state at 0x80145E90: the three party members, the one the running mode points at, the party
 * size and order, and the game and walk flags. */
typedef struct GameState {
    /* 0x000 */ PartyMember  members[3];
    /* 0x3C0 */ PartyMember* current; /* field and battle code point it at one of members */
    /* 0x3C4 */ u8           party_size;
    /* 0x3C5 */ u8           battle_order; /* party order command list applied when play resumes */
    /* 0x3C6 */ u8           unk_3C6[2];
    /* 0x3C8 */ u16          flags;
    /* 0x3CA */ u16          walk_flags;
    /* 0x3CC */ u16          input; /* field pad state: g_InputHeld, directions swapped while the lead is confused */
    /* 0x3CE */ u8           unk_3CE[0x4E];
} GameState;

ASSERT_SIZE(GameState, 0x41C);
ASSERT_OFFSET(GameState, current, 0x3C0);
ASSERT_OFFSET(GameState, party_size, 0x3C4);
ASSERT_OFFSET(GameState, battle_order, 0x3C5);
ASSERT_OFFSET(GameState, unk_3C6, 0x3C6);
ASSERT_OFFSET(GameState, flags, 0x3C8);
ASSERT_OFFSET(GameState, walk_flags, 0x3CA);
ASSERT_OFFSET(GameState, input, 0x3CC);
ASSERT_OFFSET(GameState, unk_3CE, 0x3CE);

/* D_80145E90 */
extern GameState g_Game;

/* FAKE: the members of g_Game as globals of their own. A function that touches one of them beside other globals
 * matches only when the compiler sees a separate symbol for it, and some sites read it through another width. */
extern PartyMember* g_GameState;
extern PartyMember  g_BattlePartyBattlers[3];
extern u8           g_PartySize;
extern u16          g_GameFlags;
extern u16          g_AreaWalkFlags;
/* The mode byte of each 0x24-byte owner record; the kind byte sits at +0x07. */
extern u8           D_80148333[];
extern BattleOwner  D_8014833A[];

typedef struct BattleRange {
    u8  unk_00[0x34];
    u32 range_axis_34;
    u32 range_axis_38;
    u8  pad_3C[2]; /* 0x3C */
    u16 unk3E;     /* 0x3E */
} BattleRange;

ASSERT_OFFSET(BattleRange, unk3E, 0x3E);
ASSERT_SIZE(BattleRange, 0x40);

/* Shared battle RAM layout: work-record bases and strides, call tables, ring and kind records
 * (@source: wiki:data/battle#where-the-records-are) */

/* retail addresses */

/*
 * Common to battle/battle/03 and battle/battle/15. Per-image headers keep
 * their own target-specific accessors; these names describe addresses common
 * to both targets. Strides are struct sizes (hex). Addresses are fixed RAM
 * (hex).
 */

#define BATTLE_OUTCOME_SIZE 0x40

/* Raise a bit in the battle state word. A bare statement macro: the member
 * declares `flags` and runs the follow-up the bit starts. Kept: as an inline
 * the member loses its 24-byte frame (first instruction differs in 17 members);
 * the do/while form moves bytes. */
#define BATTLE_RAISE_STATE(flag) \
    flags = &g_Battle.state;     \
    *flags |= (flag)

/* The party rows 0-2 and enemy rows 3-10 share one battler index space. */
#define COMBATANT_COUNT                   11
/* The drop list cap Battle_RollEnemyDrops walks. */
#define BATTLE_DROP_COUNT_MAX             15

/* func_801DB434 reads six threshold bytes per row. */
#define BATTLE_LEVEL_THRESHOLD_COUNT      6u

#define BATTLE_PARTY_CHARACTERS_COUNT     3 /* player slots 0-2; enemy slots start at 3 */
#define BATTLE_PARTY_STRIDE               0x140
#define BATTLE_ENEMY_STRIDE               0x118
#define BATTLE_EFFECT_STRIDE              0x78
#define BATTLE_RING_STRIDE                0x08
#define BATTLE_TYPE_STRIDE                0x14

#define ENEMY_COMBATANT_BASE              0x801EB630u
#define BATTLE_EFFECT_BASE                0x801EC330u

/* Parent base of the enemy records: ENEMY_COMBATANT_BASE - 3 * enemy stride, so
 * player slots 0-2 and enemy slots 3-10 share one battler index space. */
#define ENEMY_COMBATANT_PARENT_BASE       0x801EB2E8u

/*
 * Data tables every overlay loaded at 0x80096800 carries its own copy of
 * (battle/battle/15 and the boss archives). Each is indexed directly by the record id
 * and holds one byte per entry, so a table read is `table[id]`.
 */
#define BATTLE_ABILITY_CALL_TABLE         0x800B44F8u
#define BATTLE_ITEM_CALL_TABLE            0x800B45E0u
#define BATTLE_ITEM_ANIM_TABLE            0x800B6AC0u
/* Six u8 escape thresholds: 32, 36, 40, 44, 48, 52. */
#define BATTLE_ESCAPE_THRESHOLD_TABLE     0x800B44F0u
/* Eight u8 difficulty thresholds: 1, 2, 4, 8, 12, 16, 24, 48; indexed by the
 * ability record's high nibble at offset 0x0D. */
#define BATTLE_LEARNING_DIFFICULTY_TABLE  0x800B50DCu
/* Four-byte function pointers, indexed by accessory id - 1 (bound 0x17). */
#define BATTLE_ACCESSORY_CALL_TABLE       0x80149EC8u
/* The 0x40-stride action blocks GFX_LoadPalette copies an action step into, one
 * per battler slot (index << 6). */
#define BATTLE_ACTION_BLOCK_TABLE         0x80035600u
/* The encounter block: formations and 0x88-stride enemy records from +0x48 (ENCOUNTER_ENEMIES in game/enemy.h). Block
 * +0xCA and +0xCB are the reach and height of enemy record +0x82 and +0x83. */
#define BATTLE_ENCOUNTER_TABLE            0x800E4000u

/* The enemy battler row for a battler slot: enemy slots begin after the party
 * slots, so slot 3 is the first enemy row. An lvalue, so reads, writes and
 * member access all use it. */
#define ENEMY_COMBATANT(slot)             (g_BattleEnemyBattlers[(slot) - BATTLE_PARTY_CHARACTERS_COUNT])
/* A battler slot on the player side: slots 0-2 are the party rows. */
#define BATTLER_IS_PLAYER(slot)           ((slot) < BATTLE_PARTY_CHARACTERS_COUNT)

/* A random battle has encounter 0; a scripted battle holds its s_BattleModeRecords index. */
#define BATTLE_IS_RANDOM()                (g_Battle.encounter == 0)
#define BATTLE_IS_SCRIPTED()              (g_Battle.encounter != 0)

/* The battle ended with the party's victory: the result bit the ending step
 * sets when no enemy is left. */
#define BATTLE_IS_VICTORY()               (g_Battle.outcome.result & BATTLE_RESULT_VICTORY)

#define BATTLE_SELECTION_RECORD_HANDLE(i) MEM(u8* volatile, 0x801EB5B4u + (u32)(i) * BATTLE_RING_STRIDE)

#define BATTLE_ACTIVE_WORK                ((PartyMember*)g_BattleEffectBattler)

/* A hit's target answers with a reprisal when its reprisal roll passes
 * (Character.stats.reprisal_chance, or the enemy's event_flags bit 2): the hit's
 * ending step sets REPRISAL_PENDING, the turn's closing step hands the action
 * to that battler, and the answer's own ending step sets REPRISAL_DONE so the
 * answer is not itself answered (func_801E020C, func_801E414C, func_801D43EC).
 * EFFECT_LOADING is held from the action's effect stream request
 * (EMI_LoadArchive) until the loader is ready (Battle_FinishEffectLoad). */

/* The items a battle drops: ids and how many of each. Battle_RollEnemyDrops fills it. */
typedef struct BattleDrops {
    u16 items[16];       /* 0x00 dropped item ids */
    u8  item_counts[16]; /* 0x20 drops of each id */
} BattleDrops;

ASSERT_SIZE(BattleDrops, 0x30);
ASSERT_OFFSET(BattleDrops, item_counts, 0x20);

/* How the battle went at 0x80146324: the surprise and option flags it started with, the escape attempts, the
 * result and event flags, and the experience, zenny and drops it pays out. */
typedef struct BattleOutcome {
    u8          surprise;    /* 0x00 */
    u8          options;     /* 0x01 battle option flags */
    u8          attempts;    /* 0x02 escape attempts; battle/battle/15 reads this byte */
    u8          drop_count;  /* 0x03 listed drops, capped at BATTLE_DROP_COUNT_MAX */
    u8          result;      /* 0x04 battle result flags */
    u8          event_flags; /* 0x05 flags of the battle events that fired */
    u8          pad_06[2];
    u32         reward_exp;   /* 0x08 */
    s32         reward_zenny; /* 0x0C */
    BattleDrops drops;        /* 0x10 */
} BattleOutcome;

ASSERT_SIZE(BattleOutcome, BATTLE_OUTCOME_SIZE);
ASSERT_OFFSET(BattleOutcome, drop_count, 0x03);
ASSERT_OFFSET(BattleOutcome, reward_exp, 0x08);
ASSERT_OFFSET(BattleOutcome, drops, 0x10);

/* The battle modes, the rows of g_BattlePhases: set-up and entrance once, then rounds of commands, turn order,
 * actions and round end, then the result. */
typedef enum BattleMode {
    BATTLE_MODE_ENTRANCE   = 0,
    BATTLE_MODE_COMMANDS   = 1,
    BATTLE_MODE_TURN_SETUP = 2,
    BATTLE_MODE_TURNS      = 3,
    BATTLE_MODE_ROUND_END  = 4,
    BATTLE_MODE_RESULT     = 5,
} BattleMode;

/* The battle's phase tuple at 0x801462E0: the mode selects the g_BattlePhases handler, the step runs inside it and
 * the sub-step inside the step. BattleSetEnding writes the three bytes together; the intro and panel code reset
 * step and sub-step together and advance the mode through one base. */
typedef struct BattlePhase {
    u8 mode;     /* 0x00 BattleMode */
    u8 step;     /* 0x01 */
    u8 sub_step; /* 0x02 */
} BattlePhase;

ASSERT_SIZE(BattlePhase, 3);
ASSERT_OFFSET(BattlePhase, step, 0x01);
ASSERT_OFFSET(BattlePhase, sub_step, 0x02);

/* The battle state word g_Battle.state, read and written by both battle overlays
 * and the boss/bmagic handlers. Bit 3 (0x0008) is set by func_801D277C and
 * func_8009B828 and cleared by Battle_WaitVoiceSlots; no reader is known, so
 * it has no member. */
typedef enum BattleStateFlags {
    BATTLE_STATE_WINDOW_BUSY      = 1 << 1,
    BATTLE_STATE_EFFECT_PLAYING   = 1 << 2,
    BATTLE_STATE_COMMAND_ARMED    = 1 << 4,
    BATTLE_STATE_UNK_5            = 1 << 5,
    BATTLE_STATE_REPRISAL_PENDING = 1 << 6,
    BATTLE_STATE_CRITICAL         = 1 << 7,
    BATTLE_STATE_EFFECT_LOADING   = 1 << 10,
    BATTLE_STATE_AP_PAID          = 1 << 11,
    BATTLE_STATE_REPRISAL_DONE    = 1 << 12,
    BATTLE_STATE_DAMAGE_APPLIED   = 1 << 13,
    BATTLE_STATE_OVER             = 1 << 14,
    BATTLE_STATE_RELOAD_PARTY     = 1 << 15,
} BattleStateFlags;

/* The side mask Battle_MarkDamaged writes into D_80146384; the low values are one
 * battler slot (0-10). */
typedef enum BattleTargetFlags {
    BATTLE_TARGET_ENEMY_SIDE = 1 << 6,
    BATTLE_TARGET_PARTY_SIDE = 1 << 7,
    BATTLE_TARGET_BOTH_SIDES = BATTLE_TARGET_ENEMY_SIDE | BATTLE_TARGET_PARTY_SIDE,
} BattleTargetFlags;

/* The battle result byte D_80146328. */
typedef enum BattleResultFlags {
    BATTLE_RESULT_DEFEAT  = 1 << 0,
    BATTLE_RESULT_VICTORY = 1 << 1,
    BATTLE_RESULT_NO_BGM  = 1 << 3,
} BattleResultFlags;

extern s32          D_801459E8;
/* Pointer to the active animation-stream bank (area, battle or battle magic). */
/* D_801459F0 */
extern volatile u32 g_Scripts;
extern u8           D_80145A00;
extern s32          D_80145A04;
extern u8           D_80146229;
extern u16          D_8014622A;
extern u8           D_80146232;
extern s16          D_801462AA;
/* FAKE: g_Battle.row_cursor as a global of its own; the sites that use it match only with a separate symbol. */
extern u8           g_BattleRowCursor;
extern u8           D_801462EE;
/* FAKE: g_Battle.boss_flags as a global of its own; the sites that set a bit in it match only with a separate symbol. */
extern u8           g_BattleBossFlags;
/* FAKE: g_Battle.party_count as a global of its own; the sites that use it match only with a separate symbol. */
extern u8           g_BattlePartyCount;
/* FAKE: g_Battle.living_party_count as a global of its own; the sites that use it match only with a separate symbol. */
extern u8           g_BattleLivingPartyCount;

/* The Accession gene picker's cursor: row (-1 on the confirm line) and column. */
typedef struct GeneCursor {
    s8 row;
    u8 column;
} GeneCursor;

ASSERT_SIZE(GeneCursor, 2);

/* The battle's state at 0x801462E0, from the phase tuple to the pending status. */
typedef struct BattleState {
    /* 0x00 */ BattlePhase phase;
    /* 0x03 */ u8          ui_step;  /* step of the battle UI */
    /* 0x04 */ u8          ui_state; /* index of the battle UI state handler */
    /* 0x05 */ u8          row_cursor;
    /* 0x06 */ union {
        u8         panel_entry; /* the selected entry of the battle panel */
        GeneCursor gene;        /* the gene picker's cursor in Accession */
    } cursor;

    /* 0x08 */ u16           state; /* BattleStateFlags */
    /* 0x0A */ u8            encounter;
    /* 0x0B */ u8            unk_0B;
    /* 0x0C */ u8            scroll_dir;
    /* 0x0D */ u8            boss_flags;
    /* 0x0E */ u8            unk_0E;
    /* 0x0F */ u8            selection_latch;
    /* 0x10 */ u8            party_count;
    /* 0x11 */ u8            living_party_count;
    /* 0x12 */ u8            enemy_count;
    /* 0x13 */ u8            living_enemy_count;
    /* 0x14 */ u8            panel_slot;
    /* 0x15 */ u8            unk_15[7];
    /* 0x1C */ u8            panel_widths[7];
    /* 0x23 */ u8            command_count;
    /* 0x24 */ u8            unk_24[8];
    /* 0x2C */ u8            turn_order[11];
    /* 0x37 */ u8            unk_37[11];
    /* 0x42 */ u8            turn_cursor;
    /* 0x43 */ u8            turn_count;
    /* 0x44 */ BattleOutcome outcome;
    /* 0x84 */ u8            unk_84[16];
    /* 0x94 */ u8            active_battler;
    /* 0x95 */ u8            action_type;
    /* 0x96 */ u8            unk_96[10];
    /* 0xA0 */ BattleAction* action;
    /* 0xA4 */ u8            target_selector;
    /* 0xA5 */ u8            unk_A5[7];
    /* 0xAC */ PartyMember*  selected_actor;
    /* 0xB0 */ u8            unk_B0[4];
    /* 0xB4 */ u8            target;
    /* 0xB5 */ u8            unk_B5[11];
    /* 0xC0 */ BattleTurn*   target_record;
    /* 0xC4 */ Callback      choose_ending_hook;
    /* 0xC8 */ Callback      end_hook;
    /* 0xCC */ BossEventFunc boss_event_hook;
    /* 0xD0 */ u8            unk_D0[16];
    /* 0xE0 */ u16           action_id;
    /* 0xE2 */ u8            unk_E2[2];
    /* 0xE4 */ u8            genes[3];
    /* 0xE7 */ u8            gene_count;
    /* 0xE8 */ u8            unk_E8;
    /* 0xE9 */ u8            dragon_form;
    /* 0xEA */ u8            unk_EA[4];
    /* 0xEE */ u8            action_lock;
    /* 0xEF */ u8            unk_EF[9];
    /* 0xF8 */ u16           pending_status;
    /* 0xFA */ u8            unk_FA[6];
} BattleState;

ASSERT_SIZE(BattleState, 0x100);
ASSERT_OFFSET(BattleState, phase, 0x00);
ASSERT_OFFSET(BattleState, ui_step, 0x03);
ASSERT_OFFSET(BattleState, cursor, 0x06);
ASSERT_OFFSET(BattleState, state, 0x08);
ASSERT_OFFSET(BattleState, encounter, 0x0A);
ASSERT_OFFSET(BattleState, party_count, 0x10);
ASSERT_OFFSET(BattleState, panel_slot, 0x14);
ASSERT_OFFSET(BattleState, panel_widths, 0x1C);
ASSERT_OFFSET(BattleState, command_count, 0x23);
ASSERT_OFFSET(BattleState, turn_order, 0x2C);
ASSERT_OFFSET(BattleState, turn_cursor, 0x42);
ASSERT_OFFSET(BattleState, outcome, 0x44);
ASSERT_OFFSET(BattleState, active_battler, 0x94);
ASSERT_OFFSET(BattleState, action, 0xA0);
ASSERT_OFFSET(BattleState, target_selector, 0xA4);
ASSERT_OFFSET(BattleState, selected_actor, 0xAC);
ASSERT_OFFSET(BattleState, target, 0xB4);
ASSERT_OFFSET(BattleState, target_record, 0xC0);
ASSERT_OFFSET(BattleState, choose_ending_hook, 0xC4);
ASSERT_OFFSET(BattleState, boss_event_hook, 0xCC);
ASSERT_OFFSET(BattleState, action_id, 0xE0);
ASSERT_OFFSET(BattleState, genes, 0xE4);
ASSERT_OFFSET(BattleState, gene_count, 0xE7);
ASSERT_OFFSET(BattleState, dragon_form, 0xE9);
ASSERT_OFFSET(BattleState, action_lock, 0xEE);
ASSERT_OFFSET(BattleState, pending_status, 0xF8);

/* D_801462E0 */
extern BattleState g_Battle;

/* FAKE: the phase and the outcome of g_Battle as globals of their own; the functions that take the address of one
 * of their bytes match only with a separate symbol. */
extern BattleOutcome g_BattleOutcome;

/* FAKE: g_Battle.outcome.result as a plain byte; the functions that set a bit in it (boss endings, func_801E51DC) match only with this base. */
extern u8 g_BattleResult;

/* The kind of command the active battler runs; 2 and 3 are enemy AI states with no name yet. */
enum {
    BATTLE_ACTION_NONE    = 0,
    BATTLE_ACTION_ATTACK  = 1, /* a plain attack: Battle_ApplyDamage */
    BATTLE_ACTION_ABILITY = 4, /* g_Battle.action_id indexes the ability table D_801CA71C */
    BATTLE_ACTION_ITEM    = 5, /* g_Battle.action_id is category << 8 | item id */
};

extern u16           D_80146386;
extern u16           D_8014638A;
/* The selected battler's row (D_8014638C), stored by func_801D3624. */
/* FAKE: g_Battle.selected_actor as a global of its own; the sites that use it match only with a separate symbol. */
extern PartyMember*  g_BattleSelectedActor;
extern void*         D_80146390;
extern s32           D_8014639C;
extern u16           D_801463B2;
extern u8            D_801463B9;
/* FAKE: g_Battle.action_id as a global of its own; the sites that use it match only with a separate symbol. */
extern volatile u16  g_BattleActionId;
extern u16           D_801463C2;
extern u8            D_801463C8;
/* The slot that owns the pending panel: battle/battle/15 latches the selected slot
 * into it (func_8009FAE4), battle/battle/03 clears the 0x4000 event bit when the
 * active row's slot matches it (Battle_DefeatEnemy). */
extern u8            D_801463CA;
extern u8            D_801463CD;
extern u8            D_801463CF;
extern u8            D_801463D4;
extern u8            D_801463D5;
extern u8            D_801463D7;
extern u8            D_80148450;
extern u8            D_8014845A;
extern u8            D_80148474;
extern u8            D_80148498;
extern u8            D_801484BC;
extern u8            D_801484E0;
extern u16           D_801485A4;
extern s16           D_801485D6;
extern volatile u16  g_BattleTurnPriorityMultipliers[6];
/* D_801EAF88 */
extern volatile u8   g_BattleLevelThresholds[12];
/* Enemy battler record base for both battle overlays. */
/* D_801EB2E8 */
extern u8            g_BattleEnemies[];
/* The battler the running effect acts on: the pointer battle/battle/03 and the bmagic
 * overlays advance through the effect steps. It is a non-volatile view on
 * purpose: some retail stores rely on the plain form, for example the counter
 * store in the return-jump delay slot of func_801E8D04. */
extern PartyMember*  g_BattleEffectBattler;
/* The current battler's enemy work row (the row at ENEMY_COMBATANT_BASE that
 * the battle mode is running). battle/battle/03 stores it when it arms a slot
 * (func_801E2170) and battle/battle/15 reads its cells (Battle_TriggerEnemyEvents). */
/* D_801EB4E8 */
extern EnemyBattler* g_BattleCurrentEnemy;
extern u8            D_801EB6B2[];
/* Enemy battler work record (stride 0x118, indexed by slot - 3). */
extern EnemyBattler  g_BattleEnemyBattlers[];
/* The last battle's stat gains, which the bate stat screen adds to its character. */
extern u32           D_801FE4E8;
extern u8            D_801FE4EF;
extern u32           D_801FE4F0;

#endif
