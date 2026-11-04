#ifndef BATTLE_RECORDS_H
#define BATTLE_RECORDS_H

/* The battle records that the two battle overlays (emi/battle/battle/03
 * and emi/battle/battle/15) declare alike: one definition per record, here,
 * so the two overlays read the same bytes through the same members.
 *
 * Both overlays declare these globals with these types, so the same objects
 * are read through the same members and not through two look-alikes.
 *
 *   g_BattleAction   BattleAction *        battle family header (src/overlays/battle/battle.h)
 *   D_801463DC   EncounterEnemy[]   battle/battle/15 image header, etc/game/00 image header
 *   D_801ED9B0   PanelOwner[]  battle family header (src/overlays/battle/battle.h)
 *   D_801CA71C   BattleSelectionType[]    battle family header (src/overlays/battle/battle.h)
 *
 * Where the two overlays name one member differently, the retail access
 * decides: the comment on each member records which unit reads it. */

#include "common/handler.h"
#include "game/character.h"
#include "game/records.h"
#include "types.h"

#define BATTLE_PANEL_BYTE_CELLS_SIZE 0x1E

/* The enemy battler work record (stride 0x118 at 0x801EB630).
 *
 * Both battle overlays declare D_801EB630 as EnemyBattler and read the same
 * table, so this is one record: the union of both overlays' halves.
 *
 * The cells from +0x06 to +0x5F are the ones the slot setup (func_800ABCE0
 * and Battle_AddEnemy) clears when it arms an enemy slot; their widths follow
 * those accesses. No reader names them yet, so they keep the address names. */
#define ENEMY_COMBATANT_PAD_F1_SIZE  4 /* the pad between the +0xF0 byte and +0xF5 */

/* Ask whether the battler's status word carries the flag, a STATUS_* value or a
 * mask. Pass the row itself or, for a pointer, its dereference. */
#define HAS_STATUS(battler, flag)    (((battler).stats.status & (flag)) != 0)

/* The acting battler's row. Each battle overlay declares the acting-battler
 * byte itself, so the macro expands where it is used. */
#define BATTLE_ACTING_PARTY          (g_BattlePartyBattlers[g_BattleActingBattler])

/* One drop of an enemy: the item id the battle spoils gain when the roll
 * passes, and the index into the 8-byte drop chance table at 0x801D0CB8. */
typedef struct EnemyBattlerDrop {
    u16 item_00;
    u8  rate_02;
    u8  pad_03;
} EnemyBattlerDrop;

/* Two drops fill 0x98..0xA0 of an EnemyBattler: cell_A0 follows drops_98[2]. */
ASSERT_SIZE(EnemyBattlerDrop, 0x4);

/* The mode handler an enemy record points at. */
typedef ModeFunc EnemyBattlerEventFunc;

/* Half of a 0x20-byte battler stat block. The retail copies each half with an
 * unaligned word pair, so the two halves stay one 16-byte type. */
typedef struct BattleStatBlockPart {
    u8 bytes[0x10];
} BattleStatBlockPart;

ASSERT_SIZE(BattleStatBlockPart, 0x10);

/* Record behind the g_BattleAction cell; +0x02 is the action id. */
typedef struct BattleAction {
    u8  pad_00[2];
    u16 unk_02;
    u8  pad_04[4];
    u8  unk_08; /* +0x08 step byte: func_8009E248 sets 1, func_8009E500 sets 2 */
} BattleAction;

ASSERT_OFFSET(BattleAction, unk_02, 0x02);
ASSERT_OFFSET(BattleAction, unk_08, 0x08);

/* One entry of the candidate table at 0x801463DC: eight rows of 0x0C bytes
 * that the game overlay fills before a wild encounter and the battle overlay
 * walks to place the enemy.
 *
 *   emi/etc/game/00 func_801C6AEC   writes the id at +0x01 and the live flag
 *                                    at +0x00
 *   emi/etc/game/00 func_801C6BB4   writes the encounter position at +0x04
 *                                    and +0x08
 *   emi/battle/battle/15 func_800ABC30 reads all three and hands the id, the
 *                                    x and the y to func_800ABCE0
 *
 * The id is the index of one 0x88-byte enemy record (func_800ABCE0 reads
 * &D_800E405E + id * 0x88), so +0x01 is that index and 0xFF means none. */
typedef struct EncounterEnemy {
    u8  active; /* 0x00 - set by the game overlay, cleared when the candidate is out of reach */
    u8  id;     /* 0x01 - the enemy-record index; 0xFF means none */
    u8  pad_02[2];
    s32 x; /* 0x04 - the encounter x, 16.16 */
    s32 y; /* 0x08 - the encounter y, 16.16 */
} EncounterEnemy;

ASSERT_SIZE(EncounterEnemy, 0x0C);
ASSERT_OFFSET(EncounterEnemy, id, 0x01);
ASSERT_OFFSET(EncounterEnemy, x, 0x04);
ASSERT_OFFSET(EncounterEnemy, y, 0x08);

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

/* 32-bit position cell whose two halfwords are also read on their own. */
typedef union BattleFix32 {
    s32 raw;

    struct {
        u16 lo;
        s16 hi;
    } half;
} BattleFix32;

/* The word at +0x60 of a queued slot. battle/battle/15 stores the action's target
 * index there (func_800AAEBC) and battle/battle/03 reads the low halfword of it to
 * draw the capture count (func_801E5CA4 loads it with `lhu` and hands it to
 * func_801D9684), so the cell carries both widths. */
typedef union BattleTargetIndex {
    s32 target_index;  /* the action's target index, as battle/battle/15 stores it */
    u16 capture_count; /* the low halfword, as battle/battle/03 draws it */
} BattleTargetIndex;

/* The word at +0x3C of a local work record. It is copied whole by
 * func_801E72F4 and func_801DDAF0, and its high halfword is the vertical span
 * written by func_801DEF0C and func_801E352C. The two overlays read that
 * halfword with opposite signs. */
typedef union BattleWorkWord3C {
    u32 word;

    struct {
        u8  pad_00[2];
        s16 span_3E; /* the vertical span; func_800AF764 projects it negated */
    } half;
} BattleWorkWord3C;

/* What a queued effect acts on: a party or enemy battler, another effect, or a payload address. */
typedef union BattleEffectTarget {
    struct PartyBattler* party;
    struct EnemyBattler* enemy;
    struct BattleEffect* effect;
    u8*                  bytes;
    u32                  address;
} BattleEffectTarget;

/* One queued action slot of the table at 0x801EC330 (stride 0x78).
 *
 * Both overlays declare g_BattleEffects as BattleEffect and read the same
 * table, so this is one record. The two overlays name different halves of it:
 * battle/battle/03 names the head fields, battle/battle/15 the tail, and the merged record
 * names the union of both. */
typedef struct BattleEffect {
    u8                 unk_00;
    u8                 unk_01;
    u8                 unk_02;
    u8                 unk_03;
    u8                 unk_04;
    u8                 handler_index; /* +0x05 indexes a mode's handler table; Battle_AllocEffect stores it */
    u8                 unk_06;
    u8                 unk_07;
    u8                 unk_08;
    u8                 unk_09;
    u8                 unk_0A;
    u8                 unk_0B;
    s32                unk_0C;
    s32                unk_10;
    u8                 pad_14[4];
    s32                unk_18;
    s32                unk_1C;
    u8                 pad_20[7];
    u8                 unk_27;
    u8                 unk_28;
    u8                 unk_29; /* +0x29 func_801DE1D4 stores an action step here */
    u8                 pad_2A[4];
    s16                unk_2E;
    s16                unk_30;
    u16                unk_32;
    BattleFix32        unk_34;
    BattleFix32        unk_38;
    BattleWorkWord3C   word_3C; /* +0x3C the work record's word; bmagic stores its span halfword (+0x3E) */
    u8                 pad_40[8];
    u8                 unk_48;
    u8                 pad_49[2];
    u8                 unk_4B; /* +0x4B the panel cell index battle/battle/15 stores */
    u8                 pad_4C[0x10];
    u8                 unk_5C; /* +0x5C func_801DE1D4 clears it with the byte row below */
    u8                 unk_5D;
    u8                 unk_5E;
    u8                 unk_5F;
    BattleTargetIndex  word_60; /* +0x60 the target index: a word, a low halfword */
    u8                 pad_64[0x10];
    BattleEffectTarget target; /* +0x74 the battler the effect acts on */
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
ASSERT_OFFSET(BattleEffect, unk_5C, 0x5C);
ASSERT_OFFSET(BattleEffect, word_60, 0x60);
ASSERT_OFFSET(BattleEffect, target, 0x74);

/* A flag word of a battle work record. The overlays test and set bits through
 * `value`; the ones that race the other overlay's tasks read `volatile_value`. */
typedef union BattlerFlags {
    u32          value;
    volatile u32 volatile_value;
} BattlerFlags;

/* A screen coordinate cell: battle/battle/03 and the field overlays read it
 * unsigned, battle/battle/15 reads it signed because the panels slide to
 * negative screen positions (Actor names +0x2E/+0x30 screen_x and
 * screen_y). */
typedef union BattleScreenCoord {
    u16 half;
    s16 signed_half;
} BattleScreenCoord;

/* The cell at +0x90 of a local work record: battle/battle/03 reads the halfword, and
 * battle/battle/15 reads the low byte of it. */
typedef union BattleWorkHalfOrByte90 {
    u16 half;
    u8  value;
} BattleWorkHalfOrByte90;

/* The cell at +0xA0 of an enemy work record. battle/battle/03 reads the halfword as
 * the enemy's capture cap (func_801E496C) and battle/battle/15 reads the low byte
 * (func_800AFC98), so the cell carries both widths. */
typedef union BattleEnemyCellA0 {
    u16 max_hp;
    u8  value;
} BattleEnemyCellA0;

/* The cell at +0x0A of a battle panel task. battle/battle/03 reads it as the
 * selected battler slot (the row index is slot - 3) and battle/battle/15 reads it
 * as the panel's slide mode (0 moves the panel right), so the cell carries
 * both readings. */
typedef union BattlePanelCell0A {
    u8 slot;
    u8 mode;
} BattlePanelCell0A;

/* The byte view of a battle panel task's +0x12 and +0x14 cells. battle/battle/15
 * reads those cells as bytes (func_800B1728, func_800B0F9C) and as
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

/* The battle panel task at 0x80148648 (g_MenuPanelTaskCurrent).
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
    BattleScreenCoord x;         /* +0x04 the panel x; battle/battle/15 reads it signed */
    BattleScreenCoord y;         /* +0x06 the panel y; battle/battle/15 reads it signed */
    u8                unk_08;
    u8                unk_09;
    BattlePanelCell0A cell_0A; /* +0x0A the selected battler slot, or the slide mode */
    u8                ratio;   /* +0x0B enemy value * 0x37 / divisor, floored at 1 */
    u8                unk_0C;
    u8                cursor;    /* +0x0D cleared on panel entry */
    u8                pad_0E[4]; /* +0x0E .. +0x11 */
    u16               row_base;  /* +0x12 the panel list's first row (func_800B1728) */
    u16               hp;        /* +0x14 copied from EnemyBattler.hp_94; the HP bar's numerator */
    u8                pad_16[6]; /* +0x16 .. +0x1B */
    u16               max_hp;    /* +0x1C copied from EnemyBattler.cell_A0.max_hp; the HP bar's divisor */
} BattlePanelTask;

ASSERT_SIZE(BattlePanelTask, 0x1E);
ASSERT_OFFSET(BattlePanelTask, state, 0x03);
ASSERT_OFFSET(BattlePanelTask, x, 0x04);
ASSERT_OFFSET(BattlePanelTask, y, 0x06);
ASSERT_OFFSET(BattlePanelTask, cell_0A, 0x0A);
ASSERT_OFFSET(BattlePanelTask, row_base, 0x12);
ASSERT_OFFSET(BattlePanelTask, hp, 0x14);
ASSERT_OFFSET(BattlePanelTask, max_hp, 0x1C);

/* The word at +0x3C of an enemy work record.  The slot setup writes its high
 * halfword with the vertical span at the enemy's position (Area_SampleHeight of
 * the enemy's x and y) and the whole word is copied into the local work
 * record's word_3C (func_800AE82C). */
typedef union BattleEnemyWord3C {
    s32 word;

    struct {
        u8  pad_00[2];
        s16 span_3E; /* the vertical span at the enemy's position */
    } half;
} BattleEnemyWord3C;

typedef struct EnemyBattler {
    u8                           unk_00;
    u8                           step_01;
    u8                           unk_02;
    u8                           unk_03;
    u8                           unk_04;
    u8                           slot;   /* +0x05 battler slot; func_800ABCE0 stores slot + 3 here */
    u8                           unk_06; /* +0x06 cleared when the slot is armed */
    u8                           unk_07; /* +0x07 cleared when the slot is armed */
    u8                           unk_08; /* +0x08 the battle index with its low bit flipped */
    u8                           pad_09[0x3];
    s32                          unk_0C; /* +0x0C cleared when the slot is armed */
    s32                          unk_10; /* +0x10 cleared when the slot is armed */
    s32                          unk_14; /* +0x14 cleared when the slot is armed */
    s32                          unk_18; /* +0x18 cleared when the slot is armed */
    s32                          unk_1C; /* +0x1C cleared when the slot is armed */
    s32                          unk_20; /* +0x20 cleared when the slot is armed */
    u8                           unk_24; /* +0x24 cleared when the slot is armed */
    u8                           pad_25[0x4];
    u8                           unk_29; /* +0x29 set to 4 when the slot is armed */
    u8                           pad_2A[0x1];
    u8                           unk_2B; /* +0x2B cleared when the slot is armed */
    u8                           pad_2C[0x2];
    s16                          unk_2E;     /* +0x2E cleared when the slot is armed */
    s16                          unk_30;     /* +0x30 cleared when the slot is armed */
    s16                          unk_32;     /* +0x32 cleared when the slot is armed */
    s32                          coord_x_34; /* +0x34 the enemy's x */
    s32                          coord_y_38; /* +0x38 the enemy's y */
    /* 0x3C */ BattleEnemyWord3C word_3C;    /* +0x3C the enemy's frame counter */
    u8                           pad_40[0x8];
    u8                           unk_48; /* +0x48 cleared when the slot is armed */
    u8                           pad_49[0x2];
    u8                           unk_4B; /* +0x4B set to 0xFF when the slot is armed */
    u8                           pad_4C[0xC];
    u16                          unk_58; /* +0x58 the halfword the boss end-of-battle setup copies to the spad record */
    u16                          unk_5A; /* +0x5A the halfword the boss end-of-battle setup copies to the spad record */
    u8                           unk_5C; /* +0x5C cleared when the slot is armed */
    u8                           unk_5D; /* +0x5D cleared when the slot is armed */
    u8                           unk_5E; /* +0x5E cleared when the slot is armed */
    u8                           unk_5F; /* +0x5F cleared when the slot is armed */
    u8                           pad_60[0x14];
    u8                    name[8]; /* +0x74 the 8-character enemy name, drawn as text by Battle_DrawEnemyNamePanel */
    u8                    kind_id;
    u8                    unk_7D;      /* +0x7D battle/battle/15's cell; battle/battle/03 leaves it padded */
    u8                    unk_7E;      /* +0x7E battle/battle/03's cell; func_801E25E0 reads it as a byte */
    u8                    unk_7F;      /* +0x7F battle/battle/03's cell; battle/battle/15 leaves it padded */
    u16                   event_flags; /* +0x80 battle/battle/03's cell; battle/battle/15 leaves it padded */
    u16                   status_82;   /* +0x82 StatusFlags; bit 0x4000 marks the slot blocked */
    u16                   unk_84;      /* +0x84 damage; func_801E54EC clears it */
    u16                   unk_86;      /* +0x86 damage; func_801E54EC banks it in D_8014632C */
    u16                   power;       /* +0x88 read by the turn-order ranking */
    u8                    pad_8A[2];
    u8                    techniques[8]; /* +0x8C the bytes func_8009C994 copies the event packet's tail into */
    u16                   hp_94;
    u16                   ap; /* +0x96 battle/battle/03's cell; battle/battle/15 leaves it padded */
    EnemyBattlerDrop      drops_98[2];
    BattleEnemyCellA0     cell_A0; /* +0xA0 the cell both overlays read at their own width */
    u8                    pad_A2[0x2];
    u16                   attack;  /* +0xA4 battle/battle/15's cell; battle/battle/03 leaves it padded */
    u16                   unk_A6;  /* +0xA6 battle/battle/15's cell; battle/battle/03 leaves it padded */
    u16                   agility; /* +0xA8 battle/battle/03's cell; battle/battle/15 leaves it padded */
    u16                   unk_AA;  /* +0xAA battle/battle/15's cell; battle/battle/03 leaves it padded */
    u8                    pad_AC[0x3];
    u8                    resistances[RES_SLOT_COUNT]; /* +0xAF per-element resistance levels, as in Character */
    u8                    pad_B8[0x28];
    u8                    kind;
    u8                    unk_E1;
    u8                    unk_E2; /* +0xE2 battle/battle/15's cell; battle/battle/03 leaves it padded */
    u8                    unk_E3; /* +0xE3 battle/battle/15's cell; battle/battle/03 leaves it padded */
    EnemyBattlerEventFunc unk_E4;
    u16*                  unk_E8;
    u8*                   script;
    u8                    unk_F0;
    u8                    pad_F1[ENEMY_COMBATANT_PAD_F1_SIZE];
    u8                    unk_F5;
    u16                   technique;
    s16                   damage_F8; /* +0xF8 damage dealt this hit; negative heals (func_801E496C) */
    u16                   unk_FA;
    u8                    target_flags_FC; /* +0xFC battle/battle/15 calls it target_flags */
    u8                    unk_FD;
    u8                    pad_FE[0x2];
    u32                   flags_100; /* BattleBattlerDamageFlags */
    u32                   flags_104; /* BattleBattlerActionFlags */
    u8                    pad_108[0xA];
    u8                    unk_112;
    u8                    pad_113[0x1];
    u8                    unk_114;
    u8                    unk_115;
    u8                    pad_116[0x2];
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
ASSERT_OFFSET(EnemyBattler, word_3C, 0x3C);
ASSERT_OFFSET(EnemyBattler, unk_48, 0x48);
ASSERT_OFFSET(EnemyBattler, unk_4B, 0x4B);
ASSERT_OFFSET(EnemyBattler, unk_58, 0x58);
ASSERT_OFFSET(EnemyBattler, unk_5A, 0x5A);
ASSERT_OFFSET(EnemyBattler, unk_5C, 0x5C);
ASSERT_OFFSET(EnemyBattler, unk_5F, 0x5F);
ASSERT_OFFSET(EnemyBattler, status_82, 0x82);
ASSERT_OFFSET(EnemyBattler, techniques, 0x8C);
ASSERT_OFFSET(EnemyBattler, hp_94, 0x94);
ASSERT_OFFSET(EnemyBattler, cell_A0, 0xA0);
ASSERT_OFFSET(EnemyBattler, kind, 0xE0);
ASSERT_OFFSET(EnemyBattler, unk_E8, 0xE8);
ASSERT_OFFSET(EnemyBattler, target_flags_FC, 0xFC);
ASSERT_OFFSET(EnemyBattler, flags_100, 0x100);
ASSERT_OFFSET(EnemyBattler, flags_104, 0x104);

/* The kind walk: `D_8014833A[i]` is the owner table's record `i` seen at +0x07
 * (0x8014833A = 0x80148333 + 7, stride 0x24). Kept as its own name because the
 * units index it as an array; battle/battle/03 (func_801DA69C) names both walks. */
typedef struct BattleOwnerKind {
    u8 kind_00;      /* 0x00 - record +0x07 of the owner table */
    u8 pad_01[0x23]; /* 0x01-0x23 */
} BattleOwnerKind;

ASSERT_SIZE(BattleOwnerKind, 0x24);

/* The word at +0x08 of a work record: its four bytes, which the overlays read one at a time, and the
 * whole word they mask and test at once. */
typedef union BattleWorkWord08 {
    u32 word;

    struct {
        u8 facing_08;
        u8 unk_09;
        u8 timer_0A;
        u8 unk_0B;
    } byte;
} BattleWorkWord08;

typedef enum PartyBattlerFlags {
    PARTY_BATTLER_FLAG_OCCUPIED     = 1 << 0,
    PARTY_BATTLER_FLAG_HANDLER_BUSY = 1 << 6,
} PartyBattlerFlags;

/* Local battler work table (stride 0x140 at 0x80145E90), shared by the battle overlays. */
typedef struct PartyBattler {
    u8                flags_00;
    u8                step_01;
    u8                unk_02;
    u8                unk_03;
    u8                unk_04;
    u8                slot; /* +0x05 battler slot; func_801DC044 passes it to func_800A36F0 */
    u8                pad_06;
    u8                unk_07;
    BattleWorkWord08  word_08;
    s32               unk_0C;
    s32               unk_10;
    s32               unk_14; /* +0x14 the 32-bit cell both overlays read */
    s32               unk_18;
    s32               unk_1C; /* +0x1C battle/battle/03's cell; battle/battle/15 leaves it padded */
    s32               unk_20; /* +0x20 the 32-bit cell both overlays read */
    u8                unk_24;
    u8                unk_25;
    u8                unk_26;
    u8                unk_27;
    u8                unk_28;
    s8                unk_29; /* +0x29 the byte both overlays read */
    s8                unk_2A; /* +0x2A the byte both overlays read */
    s8                unk_2B; /* +0x2B the byte both overlays read */
    BattleScreenCoord unk_2C; /* +0x2C the halfword both overlays read */
    BattleScreenCoord unk_2E; /* +0x2E the field overlays read it signed */
    BattleScreenCoord unk_30; /* +0x30 the field overlays read it signed */
    u16               z;      /* +0x32 depth halfword; func_800AB910 calls it off_z */
    BattleFix32       coord_x_34;
    BattleFix32       coord_y_38;
    BattleWorkWord3C  word_3C;
    u32               unk_40; /* +0x40 battle/battle/03's cell; battle/battle/15 leaves it padded */
    s32               unk_44; /* +0x44 battle/battle/03's cell; battle/battle/15 leaves it padded */
    u8                unk_48; /* +0x48 battle/battle/03's cell; battle/battle/15 leaves it padded */
    u8                unk_49;
    u8                unk_4A;
    u8                unk_4B;
    s32               unk_4C; /* +0x4C battle/battle/03's cell; battle/battle/15 leaves it padded */
    s32               unk_50;
    s32               unk_54;
    u16               unk_58;
    u16               unk_5A;
    u8                unk_5C;
    u8                unk_5D;
    u8                unk_5E;
    u8                unk_5F;
    s32          unk_60; /* +0x60 the cell func_8014D290 stores the rotation in; bmagic effects read its low halfword */
    s32          unk_64; /* +0x64 the offset magic109 sweeps between -0x7F and 0x80 in steps of 8 */
    u8           pad_68[8];
    u8           unk_70;
    u8           pad_71[3];
    /* +0x74..+0x117 is a Character copy: func_801DD08C copies a
     * 0xA4-byte character record to this offset. */
    Character    stats;
    u8           unk_118;
    u8           mode_119;
    u16          command;
    u16          hp_change; /* +0x11C signed HP delta shown on the hit; func_801D527C seeds it from stats.current_hp,
                               func_801DFCB4 tests its sign (ram-map: hp_change) */
    u16          ap_change; /* +0x11E signed AP delta, as hp_change (ram-map: ap_change) */
    u8           unk_120;
    u8           counter_121;
    u8           unk_122;
    u8           unk_123;
    BattlerFlags flags_124; /* BattleBattlerDamageFlags */
    BattlerFlags flags_128; /* BattleBattlerActionFlags */
    u8           unk_12C[8];
    u16          unk_134;
    u8           counter_136;
    u8           counter_137;
    u8           charge;
    u8           unk_139;
    u8           unk_13A[6];
} PartyBattler;

ASSERT_SIZE(PartyBattler, 0x140);
ASSERT_OFFSET(PartyBattler, slot, 0x05);
ASSERT_OFFSET(PartyBattler, word_08, 0x08);
ASSERT_OFFSET(PartyBattler, unk_14, 0x14);
ASSERT_OFFSET(PartyBattler, unk_20, 0x20);
ASSERT_OFFSET(PartyBattler, unk_60, 0x60);
ASSERT_OFFSET(PartyBattler, unk_70, 0x70);
ASSERT_OFFSET(PartyBattler, unk_29, 0x29);
ASSERT_OFFSET(PartyBattler, unk_2C, 0x2C);
ASSERT_OFFSET(PartyBattler, z, 0x32);
ASSERT_OFFSET(PartyBattler, stats, 0x74);
ASSERT_OFFSET(PartyBattler, hp_change, 0x11C);
ASSERT_OFFSET(PartyBattler, ap_change, 0x11E);
ASSERT_OFFSET(PartyBattler, unk_120, 0x120);
ASSERT_OFFSET(PartyBattler, flags_124, 0x124);
ASSERT_OFFSET(PartyBattler, flags_128, 0x128);
ASSERT_OFFSET(PartyBattler, unk_12C, 0x12C);
ASSERT_OFFSET(PartyBattler, unk_13A, 0x13A);

/* The damage/status word: `flags_100` of the enemy row, `flags_124` of the
 * player row. Bit 6 marks a marked damage target; bit 7 runs the popup digits
 * and countdown; bit 8 makes the hit lethal and queues the reaction cue; bit 9
 * marks a damage row present; bit 12 skips the action gate; bit 15 counters;
 * bit 16 zeroes damage and the HP-bar numerator. */
typedef enum BattleBattlerDamageFlags {
    COMBATANT_FLAG_DAMAGED            = 1 << 6,
    COMBATANT_FLAG_DAMAGE_NUMBER      = 1 << 7,
    COMBATANT_FLAG_HURT_REACTION      = 1 << 8,
    COMBATANT_FLAG_DAMAGE_ROW_PRESENT = 1 << 9,
    COMBATANT_FLAG_SKIP_ACTION_STEP   = 1 << 12,
    COMBATANT_FLAG_REPRISAL           = 1 << 15,
    COMBATANT_FLAG_DAMAGE_IMMUNE      = 1 << 16,
} BattleBattlerDamageFlags;

/* The action/pending word: `flags_104` of the enemy row, `flags_128` of the
 * player row. Bit 3 marks a mode handler action installed; bit 4 keeps the row
 * available during the suppression countdown; bit 6 applies the queued power
 * boost; bit 9 halves the damage; bits 11 and 13 zero the holy and fire
 * resistance; bit 14 charges the action; bit 15 marks a preemptive turn. */
typedef enum BattleBattlerActionFlags {
    COMBATANT_FLAG_MODE_HANDLER_ACTION = 1 << 3,
    COMBATANT_FLAG_SUPPRESSION_EXEMPT  = 1 << 4,
    COMBATANT_FLAG_POWER_BOOST         = 1 << 6,
    COMBATANT_FLAG_DAMAGE_HALVED       = 1 << 9,
    COMBATANT_FLAG_HOLY_RESIST_ZERO    = 1 << 11,
    COMBATANT_FLAG_SELECTION_BONUS     = 1 << 12,
    COMBATANT_FLAG_FIRE_RESIST_ZERO    = 1 << 13,
    COMBATANT_FLAG_CHARGING            = 1 << 14,
    COMBATANT_FLAG_PREEMPTIVE_TURN     = 1 << 15,
} BattleBattlerActionFlags;

/* The three mode work records; g_GameState points at the current one. */
/* D_80145E90 */
extern PartyBattler    g_BattlePartyBattlers[3];
/* The mode byte of each 0x24-byte owner record; the kind byte sits at +0x07. */
extern u8              D_80148333[];
extern BattleOwnerKind D_8014833A[];
#endif
