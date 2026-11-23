#ifndef OVERLAY_BATTLE_BATTLE_15_H
#define OVERLAY_BATTLE_BATTLE_15_H

/* The battle/battle/15 overlay's local declarations: the command, step and damage dispatch tables, the actor views it shares with battle/battle/03 and the prototypes its units use. The common records are in battle/records. */

#include "overlays/battle/battle.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sys/exe.h"
#include "menu/draw.h"
#include "menu/clock.h"

/* FAKE: the callers pass the counter as volatile and the delta as s32, which the real prototype (u16*, s16) lacks. */
#define Char_AddStat                   ((s16 (*)(volatile u16*, s32))Char_AddStat)

/* retail addresses */

#define BATTLE_SELECTION_SLOT_MASK     0x7F

/* Engine helpers this target calls. The implementing bodies live in the
 * battle/battle/03 overlay; the call sites in this target fix the parameter roles
 * named in the prototypes below. */

/* The actor's target slot, signed, moved by one step before the wrap helper clamps it. */
#define ACTOR_TARGET_STEP(delta)       ((s8)g_BattleActorTurn->command.target + (delta))
#define BATTLE_ACTIVE_MESSAGE_SLOT_PTR (*(volatile void**)&g_BattleMessageSlot)
#define BATTLE_ACTIVE_MEMBER           ((PartyMember*)g_BattleMessageSlot)
/* Fixed-address bases, tables, and rodata pointers. The raw literals live only
 * here; function bodies reference these named accessors. */
#define BATTLE_LOCK_RAM_BASE           D_80150000

/* Entry table at D_8014688E with its parallel id byte table at D_8014691A:
 * thirty records of stride 0x98, type 7 marks a live entry
 * (Battle_FindActorEntry, func_800AC7D0). */
#define BATTLE_ENTRY_STRIDE            0x98
#define BATTLE_ENTRY_COUNT             30
/* The type byte of a live entry; the other types are unproven. */
#define BATTLE_ENTRY_TYPE              7

/* The hit-chance formula's quantities, in percentage points: the threshold is
 * the seeded roll's fifth over the base, capped at the max; the rate is the
 * base over the seeded roll's fifth, floored at the min. */
#define BATTLE_HIT_THRESHOLD_BASE      50
#define BATTLE_HIT_THRESHOLD_MAX       100
#define BATTLE_HIT_RATE_BASE           125
#define BATTLE_HIT_RATE_MIN            50
#define g_AreaScrollTargetY            (*(u32*)&g_AreaScrollTargetY)

/* Pick the battler's step rule entry from the flagged, player and enemy tables.
 * Kept: as an inline the enemy table pointer loads into $a0 before the branch
 * (first instruction differs in both members). */
#define BATTLE_BATTLER_STEP_RULE(flagged, player, enemy)                                                  \
    do {                                                                                                  \
        u32 slot;                                                                                         \
        u8  battler;                                                                                      \
        u8  result;                                                                                       \
        battler = g_Battle.active_battler;                                                                \
        if (battler < 3u) {                                                                               \
            if ((g_Game.members[battler].u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM) != 0u) { \
                result = flagged[g_Battle.dragon_form];                                                   \
            } else {                                                                                      \
                result = player[g_Game.members[battler].chr.character_id];                                \
            }                                                                                             \
        } else {                                                                                          \
            slot   = (u32)battler - 3u;                                                                   \
            result = enemy[(u32)g_BattleEnemyBattlers[slot].type * 0x88u];                                \
        }                                                                                                 \
        return result;                                                                                    \
    } while (0)

/* The party formation g_PartyFormation: Battle_ApplyFormationStats applies its stat changes. */
typedef enum PartyFormation {
    PARTY_FORMATION_NORMAL  = 0x00,
    PARTY_FORMATION_ATTACK  = 0x01,
    PARTY_FORMATION_DEFENSE = 0x02,
    PARTY_FORMATION_CHAIN   = 0x03,
    PARTY_FORMATION_MAGIC   = 0x04,
    PARTY_FORMATION_REFUGE  = 0x05, /* battle/battle/03 Battle_ApplyTurnDamage tests g_PartyFormation == 5 */
} PartyFormation;

/* The selection byte g_Battle.selection: bit 7 marks an active selection, the low
 * seven bits are its slot. */
typedef enum BattleSelectionFlags {
    BATTLE_SELECTION_ACTIVE = 1 << 7,
} BattleSelectionFlags;

/* Record behind the g_Battle.action cell; +0x02 is the action id. */
typedef struct BattleSelectionAction {
    Callback handler;
    u32      unk_04;
} BattleSelectionAction;

/* Player flag record of the selection table: stride 0x140, flag word at the
 * record's +0x128 (the table's base symbol D_80145FB8). */
typedef volatile struct BattleSelectionPlayer {
    volatile u32 flags; /* +0x128 */
    u8           pad_04[0x13C];
} BattleSelectionPlayer;

typedef struct BattleStatDisplayTemplate {
    s16 max_hp;         /* 0x00 */
    s16 power;          /* 0x02 */
    s16 defense;        /* 0x04 */
    s16 agility;        /* 0x06 */
    s16 intelligence;   /* 0x08 */
    u8  resistances[9]; /* 0x0A */
    u8  pad_13[5];      /* 0x13 */
} BattleStatDisplayTemplate;

ASSERT_SIZE(BattleStatDisplayTemplate, 0x18);

/* Battle-local work record (stride 0x140 at g_Game.members). Offsets 0x24..0x4B
 * are the g_Task stores in func_800ADD44 (retail asm byte/half/word
 * widths, matching its exact twin func_800ADA4C). +0x120/+0x124/+0x128 alias
 * D_80145FB0 (u8), D_80145FB4[i].flags (u32) and D_80145FB8[i].flags
 * (u32); 0x9F..0xA3 is the element-slot byte run Battle_GetFireResistance reads. */
typedef struct BattlePlayerDamageStatus {
    volatile u32 flags;
    volatile u32 flags_04;
    u8           pad_08[0x138];
} BattlePlayerDamageStatus;

ASSERT_SIZE(BattlePlayerDamageStatus, 0x140);

typedef struct BattleLocalOffsets {
    s16 values[4][2];
} BattleLocalOffsets;

/* Declarations and record types this target owns; the units below carried
 * the same text in their own file-local copies.
 * Evidence: tasks/types-all/decl-census.tsv, tasks/types-all/inventory.tsv. */
typedef struct BattleSlot {
    u8 slot_00;
    u8 slot_01;
    u8 slot_02;
    u8 gate_03;
} BattleSlot;

typedef struct BattleTargetSelection {
    u8   sel;
    u8   unk_01[0x0B];
    s16* record;
} BattleTargetSelection;

typedef struct BattleTaskModes {
    Callback modes[4];
} BattleTaskModes;

/* One battle event packet (0x10 bytes) of the event table at 0x800E407C: the
 * table holds four packets per enemy type record, at the type record's +0x34.
 *
 * Evidence: the retail reads the packet's +0x00 with `lbu` and switches on it
 * (Battle_TriggerEnemyEvents), its +0x01 with `lbu` and switches on it (Battle_ApplyEnemyEvent),
 * its +0x02 and +0x03 with `lbu`, its +0x04 with `lbu`, its +0x06 with `lh`
 * and its +0x08..+0x0F with `lbu` (Battle_ApplyEnemyEvent). */
typedef struct BattleEventPacket {
    u8  type;        /* +0x00 the type Battle_TriggerEnemyEvents switches on to pick the trigger test */
    u8  effect_type; /* +0x01 the type Battle_ApplyEnemyEvent switches on to pick the record update */
    u8  selector;    /* +0x02 the bits that select the cells the packet updates */
    u8  value;       /* +0x03 the value the selected cells take */
    u8  choice_ai;   /* +0x04 the byte copied to the work record's +0x7E */
    u8  pad_05;
    s16 panel_id;  /* +0x06 the panel id; Battle_ApplyEnemyEvent stores it in the panel-owner table */
    u8  unk_08[8]; /* +0x08 the eight bytes copied to the work record's +0x8C */
} BattleEventPacket;

ASSERT_OFFSET(BattleEventPacket, type, 0x00);
ASSERT_OFFSET(BattleEventPacket, effect_type, 0x01);
ASSERT_OFFSET(BattleEventPacket, selector, 0x02);
ASSERT_OFFSET(BattleEventPacket, value, 0x03);
ASSERT_OFFSET(BattleEventPacket, choice_ai, 0x04);
ASSERT_OFFSET(BattleEventPacket, panel_id, 0x06);
ASSERT_OFFSET(BattleEventPacket, unk_08, 0x08);
ASSERT_SIZE(BattleEventPacket, 0x10);

/* What makes an event packet trigger (BattleEventPacket.type). The once-only types trigger at most once per
 * battle; the REPEAT types trigger at every hit. */
typedef enum BattleEventTrigger {
    BATTLE_EVENT_HIT_FIRE             = 0,
    BATTLE_EVENT_HIT_FROST            = 1,
    BATTLE_EVENT_HIT_ELECTRIC         = 2,
    BATTLE_EVENT_HIT_EARTH            = 3,
    BATTLE_EVENT_HIT_WIND             = 4,
    BATTLE_EVENT_HIT_HOLY             = 5,
    BATTLE_EVENT_HIT_PSIONIC          = 6,
    BATTLE_EVENT_HIT_DEATH            = 7,
    BATTLE_EVENT_HIT_STATUS           = 8,
    BATTLE_EVENT_HIT_BY_ABILITY       = 9,
    BATTLE_EVENT_HIT_BY_ATTACK        = 10,
    BATTLE_EVENT_BLINDED              = 22,
    BATTLE_EVENT_POISONED             = 23,
    BATTLE_EVENT_NO_DROP              = 24,
    BATTLE_EVENT_REPEAT_HIT_FIRE      = 33,
    BATTLE_EVENT_REPEAT_HIT_FROST     = 34,
    BATTLE_EVENT_REPEAT_HIT_ELECTRIC  = 35,
    BATTLE_EVENT_REPEAT_HIT_BY_ATTACK = 36,
    BATTLE_EVENT_LETHAL_HIT           = 37,
} BattleEventTrigger;

/* The enemy record of the encounter block from its event packets (+0x34) on: ENEMY_AI_COUNT packets, then the rest of
 * the Enemy record. The address view of the cell that Enemy.ai covers; retail addresses it as a constant. */
typedef struct BattleEnemyEvents {
    BattleEventPacket packets[ENEMY_AI_COUNT];
    u8                unk_40[ENEMY_STRIDE - ENEMY_AI_COUNT * sizeof(BattleEventPacket)];
} BattleEnemyEvents;

ASSERT_SIZE(BattleEnemyEvents, ENEMY_STRIDE);

#define BATTLE_ENEMY_EVENTS MEM_PTR(BattleEnemyEvents, 0x800E407Cu)

typedef struct BattleSelectionState {
    volatile u8 active_count; /* +0x00 */
    volatile u8 unk_01[0xA3];
    volatile u8 selection_index; /* +0xA4 */
} BattleSelectionState;

/* Shared battle-template stats, one row (stride 0x78) per battler slot. The
 * magic-defense path copies three defense values out of this table. */
typedef struct BattleTemplateStats {
    u32 defense[3]; /* 0x00 */
    u8  pad_0C[0x6C];
} BattleTemplateStats;

/* The same cell read without the reload is g_BattleWorkCell: Battle_CureStatus's
 * save/restore keeps the plain word. A second name is the only form that keeps
 * the retail `lui`/`sw` pairs; the address is an `alias:true` row of the image's table in config/symbols/<image>.toml. */
extern u32 g_BattleWorkCell;

#define BATTLE_EFFECT_STEP_COUNT 3

typedef struct BattleEffectSteps {
    Callback steps[BATTLE_EFFECT_STEP_COUNT];
} BattleEffectSteps;

#define BATTLE_MENU_PANEL_MODE_COUNT 5

typedef struct BattleMenuPanelModes {
    Callback modes[BATTLE_MENU_PANEL_MODE_COUNT];
} BattleMenuPanelModes;

#define BATTLE_MENU_PANEL0_STATE_COUNT 3

typedef struct BattleMenuPanel0Steps {
    Callback steps[BATTLE_MENU_PANEL0_STATE_COUNT];
} BattleMenuPanel0Steps;

#define BATTLE_MENU_PANEL1_STATE_COUNT 3

typedef struct BattleMenuPanel1Steps {
    Callback steps[BATTLE_MENU_PANEL1_STATE_COUNT];
} BattleMenuPanel1Steps;

#define BATTLE_MENU_PANEL2_STATE_COUNT 5

typedef struct BattleMenuPanel2Steps {
    Callback steps[BATTLE_MENU_PANEL2_STATE_COUNT];
} BattleMenuPanel2Steps;

#define BATTLE_MENU_PANEL3_STATE_COUNT 3

typedef struct BattleMenuPanel3Steps {
    Callback steps[BATTLE_MENU_PANEL3_STATE_COUNT];
} BattleMenuPanel3Steps;

#define BATTLE_MENU_PANEL4_STATE_COUNT 3

typedef struct BattleMenuPanel4Steps {
    Callback steps[BATTLE_MENU_PANEL4_STATE_COUNT];
} BattleMenuPanel4Steps;

extern BattleEffectSteps     D_80096994;
extern BattleEffectSteps     D_800969A0;
extern BattleEffectSteps     D_800969AC;
extern BattleEffectSteps     D_800969B8;
extern BattleMenuPanelModes  D_800969E4;
extern BattleMenuPanel0Steps D_800969F8;
extern volatile u8           D_80096A04[4];
extern BattleMenuPanel1Steps D_80096A08;
extern BattleMenuPanel2Steps D_80096A14;
/* Main-executable battle state consumed by target-local lifts. */
extern char                  D_80096A28[];
extern char                  D_80096A2C[];
extern BattleMenuPanel3Steps D_80096A34;
extern BattleMenuPanel4Steps D_80096A40;
extern char                  D_80096A54[];
extern Callback              func_800B43B8[];
extern Callback              D_800B43D4[17];
extern Callback              g_BattleExamineSteps[4];
extern Callback              D_800B4428[12];
extern Callback              D_800B4458[5];
extern Callback              D_800B446C[4];
extern Callback              D_800B447C[4];
extern Callback              D_800B448C[5];
extern Callback              D_800B44A0[];
extern u8                    D_800B44B0[];
extern u8                    D_800B44B8[];
extern Callback              D_800B44C8[3];
extern Callback              D_800B44D4[4];
extern Callback              D_800B44E4[];
/* D_800B45E0 */
extern u8                    g_BattleItemEffectIds[96];
/* D_800B4640 */
extern u8                    g_BattleWeaponEffectIds[92];
/* D_800B469C */
extern u8                    g_BattleArmorEffectIds[72];
/* D_800B46E4 */
extern u8                    g_BattleAccessoryEffectIds[40];
extern u8*                   D_800B470C[4];
/* D_800B471C */
extern Callback              g_BattleItemEffects[130];
extern u8                    g_BattleEscapeThresholds[];
extern s8                    D_800B4924[];
extern u16                   D_800B492C[16];
/* Overlay data and routines the sources use; names are the retail addresses. */
extern s16                   D_800B494C[8];
extern s16                   D_800B495C[8];
extern s16                   D_800B496C[8];
extern s16                   D_800B497C[8];
extern s16                   D_800B498C[400];
extern u8                    D_800B4C90[];
extern Callback              D_800B4CAC[7];
extern Callback              D_800B4CC8[2];
extern Callback              D_800B4CD0[5];
extern Callback              D_800B4CE4[7];
extern Callback              D_800B4D00[5];
extern Callback              D_800B4D14[7];
extern Callback              D_800B4D30[];
extern u8                    D_800B4D7C[18][14];
extern u8                    D_800B4E78[5][5];
/* D_800B4E94 */
extern u8                    s_BattleAffinityLevelBonus[5];
extern u8                    D_800B4E99[5];
extern u8                    D_800B4E9E[5];
extern u8                    D_800B4EE0[21][14];
extern u8                    D_800B5008[21][8];
extern u16                   D_800B51E8[4][2];
extern u8                    D_800B70AC[];
extern PartyMember           s_BattleBattlerTemplates[BATTLE_PARTY_CHARACTERS_COUNT];
extern Callback              D_800B50B0[7];
extern Callback              D_800B50CC[2];
extern Callback              D_800B50D4[];
extern u8                    D_800B50DC[];
extern u8                    D_800B50E4[];
extern u16                   D_800B50EC[][7];
extern Callback              D_800B5108[];
/* D_800B65F8 */
extern BattleSelection       g_BattleSelections[];
extern BattleSelectionAction D_800B65FC[];
extern u8                    D_800B6BF0[4];
extern Callback              D_800B6BF4[];
/* D_800B6C04 */
extern u8                    g_BattlePanelUV[];
/* D_800B6C28 */
extern u8                    s_BattleCellRowCount[8];
/* D_800B6C30 */
extern u8                    s_BattleCellRowDivisor[8];
/* D_800B6C38 */
extern u8                    s_BattleCellRowScale[8];
extern u8                    D_800B6C40[12];
extern u8                    D_800B6C4C[28];
extern u8                    D_800B6C68[12];
extern u8                    D_800B6C74[28];
extern BattleLocalOffsets    D_800B6C90[7];
extern u8                    D_800B6D00[28];
extern volatile u32          D_800B6D1C[1];
extern volatile u16          D_800B6D20[4];
extern volatile u16          D_800B6D28[4];
extern volatile u16          D_800B6D30[28];
/* The two glyph runs UI_SpriteDrawRun stamps at the frame's top-left corner;
 * they lie inside the D_800B6D30 word table, so their length is unproven. */
extern u8                    D_800B6D44[];
extern u8                    D_800B6D50[];
/* D_800B6D5C */
extern u8                    s_BattleFrameTitles[2][5];
/* D_800B6D68 */
extern u8                    s_BattleAbilityIcon[25];
/* D_800B6D84 */
extern u8                    s_BattleAbilityLine1Run[12];
/* D_800B6D90 */
extern u8                    s_BattleAbilityLine2Run[12];
/* D_800B6D9C */
extern u8                    s_BattleAbilityLine1FlagRun[12];
/* D_800B6DA8 */
extern u8                    s_BattleAbilityLine2FlagRun[12];
/* The panel slots' palette and sprite blocks; func_800B4220 hands their
 * addresses to func_8014F800 and UI_SpriteDrawRun. */
/* D_800B6DCC */
extern u8                    s_BattlePanelSelectedMarker[6];
/* D_800B6DD4 */
extern u8                    s_BattlePanelUnselectedMarker[6];
/* D_800B6DDC */
extern u8                    s_BattlePanelValueRun[42];
extern Callback              D_800B6E08[6];
extern Callback              D_800B6E20[5];
extern Callback              D_800B6E34[3];
extern Callback              D_800B6E40[4];
extern Callback              D_800B6E50[];
extern s32                   D_800B6EC4;
extern s32                   D_800B6ED4;

/* The stat labels, slot icons and slot categories inside the panel data block, then the
 * second label block. */
typedef struct BattlePanelEquipTables {
    u8 stat_labels[4][6];
    u8 slot_icons[8];
    u8 slot_categories[6];
    u8 pad_26[2];
    u8 rest[0x3C];
} BattlePanelEquipTables;

extern BattlePanelEquipTables            s_BattlePanelEquipTables;
/* D_800B6F3C */
extern char                              s_BattlePanelUseLabel[4];
/* D_800B6F40 */
extern char                              s_BattlePanelEquipLabel[5];
/* D_800B6F50 */
extern u8                                s_BattleEquipment[6];
extern u8                                D_800B6F58;
extern u8                                D_800B6F5C;
extern s8                                D_800B6F60;
extern s8                                D_800B6F61;
extern s8                                D_800B6F62;
extern s8                                D_800B6F63;
extern s8                                D_800B6F64;
extern s8                                D_800B6F65;
extern s8                                D_800B6F66;
extern s8                                D_800B6F67;
extern s8                                D_800B6F68;
extern s8                                D_800B6F69;
extern s8                                D_800B6F6A;
extern s8                                D_800B6F6B;
extern s8                                D_800B6F6C;
extern s8                                D_800B6F6D;
extern u8                                D_800B7070[][6]; /* Flag bytes read back by the panel: one u8 per table entry. */
extern u8                                D_800B7088[][2]; /* Flag bytes cleared at a two-byte stride. */
extern u8                                D_800B70B8[];
extern u8                                D_800E4050;
extern u16                               D_800E405E;
extern u16                               D_800E4068;
/* Playable-character records are byte-addressed; each typed record is 0xA4 bytes. */
extern volatile u32                      D_80144F60[];
extern u8                                D_801454FD; /* plain: Battle_SelectItem stores it outside the volatile order */
extern volatile u8                       D_801454FE;
extern volatile u8                       D_801454FF;
/* D_80145500 */
extern BattleSlot                        g_BattleTargetRows[];
extern BattleSlot                        D_80145518[];
extern u8                                D_8014551B;
/* Battler base halfwords, one u16 per 0x140-byte player record. */
extern u16                               D_80145FAA[];
extern u8                                D_80145FB2;
extern volatile BattlePlayerDamageStatus D_80145FB4[];
/* Selection row table: player rows for slots 0-2, indexed by battler slot. */
extern BattleSelectionPlayer             D_80145FB8[];
extern s8                                D_80145FBD;
extern s8                                D_80145FBE;
extern s8                                D_80145FBF;
extern s8                                D_80145FC0;
extern s8                                D_80145FC1;
extern s8                                D_80145FC2;
extern s8                                D_80145FC3;
extern u16                               D_801460EA;
extern u8                                D_801460F2;
/* FAKE: g_Battle.ui_step as a global of its own; the sites that use it match only with a separate symbol. */
extern volatile u8                       g_BattleUIStep;

extern BattleSelectionState      D_801462F0_state;
/* FAKE: g_Battle.active_battler as a global of its own; the sites that use it match only with a separate symbol. */
extern volatile u8               g_BattleActiveBattler;
/* Per-access views of a symbol at the same address, named by an `alias = true` row in config/symbols/<image>.toml (this image's
 * table or battle/battle/03's). Units that need retail's separate %hi/%lo pair for one cell use them; a cast of the
 * canonical symbol merges the pair and changes the bytes. */
extern u8                        g_BattleActiveBattler_nv;
/* FAKE: g_Battle.target as a global of its own; the sites that use it match only with a separate symbol. */
extern volatile u8               g_BattleTarget;
extern u8                        g_BattleTarget_nv;
extern u16                       D_801463B4;
/* D_801463D8 */
/* D_80148570 */
extern volatile u8               g_BattleChoicePanel[];
/* First byte of g_BattleChoicePanel (0x80148570). The original stores it
 * through a scalar symbol, which emits the direct %lo store form; indexing the
 * array symbol would materialize its address in a register instead. */
/* First byte of g_BattleChoicePanel (0x80148570); a scalar symbol emits the
 * direct %lo store form. */
extern volatile u8               g_BattleSelectionHead;
extern u8                        D_80148571;
extern u8                        D_80148572;
extern u16                       D_80148576;
extern s16                       D_80148582;
extern u8                        D_80148594;
extern u8                        D_80148595;
extern u8                        D_80148596;
extern u16                       D_80148598;
extern u16                       D_8014859A;
extern u8                        D_8014859D;
extern u8                        D_801485A1;
extern volatile u8               D_801485B8;
extern s8                        D_801485B9;
extern s8                        D_801485BA;
extern s16                       D_801485BC;
extern s16                       D_801485BE;
extern s8                        D_801485C5;
extern s16                       D_801485CA;
extern u8*                       D_801485D8;
extern volatile u8               D_801485DD;
extern volatile u8               D_801485DE;
extern volatile u8               D_801485DF;
extern volatile u16              D_801485EC;
extern s16                       D_801485EE;
extern volatile s16              D_80148628;
extern volatile u16              D_8014862A;
extern volatile u8               D_8014862F;
extern volatile u8               D_80148654;
extern u8                        D_80148656;
/* Proven game-RAM base for battle state (0x80140000). func_800A4458 already
 * references it through a local extern of this exact type. */
/* Handle ring slot array: one u32 per 8-byte record (func_800A60DC writes
 * g_BattleMessages[(D_801EC328 - 1) & 0xF].text). */
extern volatile u8               D_80150000[];
extern u8*                       g_ItemCategoryIds[];
extern u8*                       g_ItemCategoryCounts[];
extern char                      g_MenuInventoryCountFormat[];
extern u8                        D_801C90ED[];
extern u8                        D_801CAF13;
extern u8                        D_801CD78E[];
extern u32                       D_801EB082;
extern u8                        D_801EB3DC[];
extern BattleStatDisplayTemplate D_801EBEF0;
/* Battler base halfwords, one u16 per 0x118-byte enemy record. */
extern u8                        D_801EBEFA; /* Nine-slot affinity mirror in the high battle block. */
extern u8                        D_801EBEFB;
extern u8                        D_801EBEFC;
extern u8                        D_801EBEFD;
extern u8                        D_801EBEFE;
extern u8                        D_801EBEFF;
extern u8                        D_801EBF00;
extern u8                        D_801EBF01;
extern u8                        D_801EBF02;
/* Alternate local work entries (stride 0x140) and their paired status words. */
extern u8                        D_801EC2E8[];
extern volatile s16              D_801EC2EE;
extern volatile u16              D_801EC2F2;
extern volatile u16              D_801EC30C;
extern volatile u16              D_801EC310;
extern volatile u16              D_801EC312;
/* D_801EC364 */
extern BattleTemplateStats       g_BattleTemplateStats[]; /* 0x801EC364 */

/* The battle program's handler tables call these functions. */
void        func_80096F3C(void);
void        func_80096F78(void);
void        Battle_SetCommandType(void);
void        Battle_ChooseAbility(void);
/* func_8009761C */
void        Battle_RouteAbilityTarget(void);
void        func_8009773C(void);
void        Battle_SetCommandId(void);
/* func_80097844 */
void        Battle_SelectAbilityEnemyTarget(void);
/* func_800979E4 */
void        Battle_SelectAbilityPartyTarget(void);
void        Battle_ResetSelectionLatch(void);
void        Battle_SetPhaseStep(void);
void        func_80097D1C(void);
/* func_80097D58 */
void        Battle_SetAbilityTargetSide(void);
/* func_80097DC0 */
void        Battle_ToggleAbilityTargetSide(void);
void        func_80097FE8(void);
/* func_800980E4 */
void        Battle_StartExamineTarget(void);
/* func_80098144 */
void        Battle_SelectExamineEnemyTarget(void);
/* func_80098254 */
void        Battle_ConfirmExamine(void);
/* func_800982E4 */
void        Battle_CancelExamine(void);
void        Battle_GrantAlwaysHits(void);
void        Battle_GrantDamageImmunity(void);
void        Battle_GrantReprisal(void);
void        func_80098388(void);
void        func_800983C4(void);
/* func_80098408 */
void        Battle_StartItemCommand(void);
/* func_80098450 */
void        Battle_SelectItem(void);
/* func_800989FC */
void        Battle_RouteItemTarget(void);
void        func_80098B08(void);
/* func_80098B44 */
void        Battle_StartItemTarget(void);
/* func_80098C18 */
void        Battle_SelectItemEnemyTarget(void);
/* func_80098DC4 */
void        Battle_SelectItemPartyTarget(void);
/* func_80098FD4 */
void        Battle_ConfirmItem(void);
/* func_80099114 */
void        Battle_CancelItem(void);
void        func_80099178(void);
/* func_800991B4 */
void        Battle_SetItemTargetSide(void);
/* func_80099248 */
void        Battle_ToggleItemTargetSide(void);
void        func_80099328(void);
/* func_80099364 */
void        Battle_ChooseEquipAction(void);
/* func_80099568 */
void        Battle_SelectEquipSlot(void);
/* func_80099830 */
void        Battle_SelectEquipChoice(void);
/* func_80099B74 */
void        Battle_SelectEquipItem(void);
/* func_80099E80 */
void        Battle_RouteEquipItem(void);
void        func_80099F90(void);
/* func_80099FCC */
void        Battle_SetEquipTarget(void);
void        func_8009A0A4(void);
void        func_8009A254(void);
/* func_8009A468 */
void        Battle_ConfirmEquipItem(void);
/* func_8009A518 */
void        Battle_CancelEquipItem(void);
void        func_8009A590(void);
/* func_8009AF84 */
void        Battle_InitItemPanel(void);
/* func_8009B20C */
void        Battle_ClearMenuPanels(void);
/* func_8009B2B0 */
void        Battle_TryEscape(void);
void        func_8009B44C(void);
/* func_8009B488 */
void        Battle_StartEscapeScroll(void);
/* func_8009B700 */
void        Battle_ScrollEscapeOut(void);
/* func_8009B794 */
void        Battle_ScrollEscapeBack(void);
/* func_8009B828 */
void        Battle_FailEscape(void);
void        func_8009B964(void);
/* func_8009BACC */
u8          Battle_CalcEscapeChance(s32 diff);
bool        func_8009C794(s32 skip_slot, s32 enemy_slot);
/* func_8009C8AC */
u8          Battle_ActionHasElement(u16 required_mask);
/* func_8009CCBC */
void        Battle_ScaleEnemyStat(void* battler, s32 rate_type, s32 rate_percent);
void        func_8009CF80(u8* record, s32 index, s32 new_value);
/* func_8009CFEC */
void        Battle_MergeEnemyPanels(void);
/* func_8009DA94 */
void        Battle_DealNoDamage(void);
void        func_8009DAB4(void);
void        func_8009DBA4(void);
void        func_8009DC6C(void);
/* func_8009DD20 */
void        Battle_CurePoison(void);
void        func_8009DD50(void);
/* func_8009DE18 */
extern void Battle_ApplyHeal(void);
/* func_8009DE50 */
void        Battle_Heal20Hp(void);
/* func_8009DE64 */
void        Battle_Heal40Hp(void);
/* func_8009DE78 */
void        Battle_Heal100Hp(void);
/* func_8009DE8C */
void        Battle_HealFullHp(void);
/* func_8009DF70 */
void        Battle_CureStatusChance(void);
void        func_8009DFBC(void);
/* func_8009DFEC */
void        Battle_CureBlindness(void);
/* func_8009E01C */
void        Battle_CurePetrification(void);
/* func_8009E04C */
void        Battle_CureAilments(void);
/* func_8009E07C */
void        Battle_ReviveOneHp(void);
void        func_8009E184(void);
void        func_8009E1E0(void);
/* func_8009E200 */
void        Battle_Heal20Ap(void);
/* func_8009E224 */
void        Battle_Heal100Ap(void);
/* func_8009E248 */
void        Battle_DrainHp(void);
/* func_8009E500 */
extern void Battle_DrainAp(void);
void        func_8009E7C4(void);
void        func_8009E7E4(void);
/* func_8009E804 */
void        Battle_InflictSleep(void);
/* func_8009E824 */
void        Battle_InflictConfusion(void);
/* func_8009E844 */
void        Battle_ReviveQuarterHp(void);
/* func_8009E98C */
void        Battle_ReviveFullHp(void);
void        func_8009EA30(void);
void        func_8009EA8C(void);
void        func_8009EACC(void);
void        func_8009EB28(void);
void        func_8009EC48(void);
void        func_8009EDB4(void);
void        func_8009EECC(void);
void        func_8009EF08(void);
void        func_8009EF28(void);
void        func_8009EFB8(void);
void        func_8009F010(void);
void        func_8009F0A4(void);
void        func_8009F1BC(void);
/* func_8009F258 */
void        Battle_InflictSilence(void);
/* func_8009F278 */
void        Battle_CastQuake(void);
/* func_8009F2B0 */
void        Battle_CastTyphoon(void);
/* func_8009F2E8 */
void        Battle_CastLightning(void);
/* func_8009F320 */
void        Battle_HalveDamage(void);
/* func_8009F3DC */
void        Battle_CastMight(void);
/* func_8009F414 */
void        Battle_CastInferno(void);
/* func_8009F44C */
void        Battle_CastBlizzard(void);
/* func_8009F484 */
void        Battle_CastSirocco(void);
/* func_8009F4BC */
void        Battle_CastFlare(void);
/* func_8009F4F4 */
void        Battle_CastProtect(void);
/* func_8009F52C */
void        Battle_CastWeaken(void);
/* func_8009F564 */
void        Battle_CastFireblast(void);
/* func_8009F59C */
void        Battle_CastCyclone(void);
/* func_8009F5D4 */
void        Battle_CastSilence(void);
/* func_8009F60C */
void        Battle_CastJolt(void);
void        func_8009F644(void);
/* func_8009F67C */
void        Battle_CastSimoon(void);
/* func_8009F6B4 */
void        Battle_CastBarrier(void);
void        func_8009F6EC(void);
void        func_8009F758(void);
/* func_8009F7EC */
void        Battle_ThirdHpDamage(void);
/* func_8009F814 */
void        Battle_FullHpDamage(void);
/* func_8009F83C */
void        Battle_HalfHpDamage(void);
/* func_8009F864 */
void        Battle_InflictParalysis(void);
void        func_8009F884(void);
/* func_8009F978 */
void        Battle_InflictBlindness(void);
/* func_8009F998 */
void        Battle_InflictPoison(void);
void        func_8009F9B8(void);
void        func_8009F9E0(void);
void        func_8009FA20(void);
void        func_8009FAE4(void);
void        func_8009FB38(void);
void        func_8009FE10(void);
/* func_8009FE70 */
void        Battle_Heal1Hp(void);
/* func_8009FE84 */
void        Battle_Heal80Hp(void);
/* func_8009FE98 */
void        Battle_Heal240Hp(void);
/* func_8009FEAC */
void        Battle_Heal5Ap(void);
void        func_8009FED0(void);
void        func_8009FEF4(void);
/* func_8009FF7C */
void        Battle_CastMyollnir(void);
/* func_8009FFB4 */
void        Battle_FullRestore(void);
/* func_8009FFE4 */
void        Battle_Heal5Hp(void);
void        func_8009FFF8(void);
void        func_800A0000(void);
void        func_800A0188(void);
void        func_800A0244(void);
void        func_800A02E8(void);
extern void func_800A0378(void);
void        func_800A042C(void);
void        func_800A0564(void);
void        func_800A0660(void);
/* func_800A07D0 */
void        Battle_DoubleRewards(void);
void        func_800A0898(void);
/* func_800A0920 */
void        Battle_StopTurns(void);
void        func_800A0A04(void);
void        func_800A0A40(void);
void        func_800A0B2C(void);
void        func_800A0BF4(void);
void        func_800A0C44(void);
void        func_800A0C68(void);
void        func_800A0D64(void);
void        func_800A0E68(void);
void        func_800A0EC4(void);
void        func_800A14B4(void);
void        func_800A15DC(void);
void        func_800A17A4(void);
void        func_800A1978(void);
void        func_800A1AD0(void);
void        func_800A1B38(void);
void        func_800A1BE4(void);
void        func_800A1CB4(void);
void        func_800A1D84(void);
void        func_800A2120(void);
void        func_800A21D0(void);
void        func_800A22CC(void);
void        func_800A23CC(void);
/* func_800A2404 */
void        Battle_CastDeath(void);
void        Battle_ApplyAbilityDamage(void);
void        func_800A243C(void);
void        func_800A250C(void);
void        func_800A2560(void);
void        func_800A2598(void);
void        func_800A2668(void);
void        func_800A26F0(void);
s16         Battle_RollActionDamage(u8 unused, u8 battler_index, u16 base_value, u8 element_flag);
s16         Battle_GetFireResistance(u8 battler_index, u16 element_mask);
s16         func_800A2EF0(u8 battler_index, u16 element_mask);
/* func_800A30E8 */
s32         Battle_CalcHeal(u8 unused, u8 battler_index);
/* func_800A31E0 */
void        Battle_AddStatus(u8 battler_index, u16 status_mask);
bool        func_800A3638(s32 battler_index, s32 compare_value);
u8          func_800A36BC(s32 battler_index, s32 compare_value);
/* func_800A36F0 */
u16         Battle_CureStatus(u8 battler_index, u16 status_mask);
extern void Battle_AddStatClamped(s16 delta, u8 battler_index);
u8          Battle_PickAbility(u8 battler_index, u8 selection_type);
u8          func_800A3C9C(u8 battler_index, u8 selection_type);
void        Battle_MarkDamageApplied(void);
u8          func_800A403C(u8 battler_index);
/* func_800A41D8 */
u8          Battle_InflictStatus(s32 status_mask);
u8          func_800A4238(s32 input_mask);
/* func_800A4294 */
s16         Battle_RollHpDamage(s32 divisor);
void        func_800A46C4(void);
/* func_800A4700 */
void        Battle_LoadDraArchive(void);
/* func_800A4744 */
void        Battle_EndDraLoad(void);
/* func_800A47AC */
void        Battle_OpenMenu(void);
void        func_800A4900(void);
void        func_800A493C(void);
void        func_800A4AD0(void);
void        func_800A4B08(void);
/* func_800A4B2C */
void        Battle_LoadRe2Archive(void);
/* func_800A4BB4 */
void        Battle_EndRe2Load(void);
void        func_800A4C08(void);
void        func_800A4C44(void);
void        func_800A4C70(void);
void        func_800A4D3C(void);
void        func_800A50B8(void);
void        func_800A5120(void);
void        func_800A5164(void);
void        func_800A5244(void);
void        func_800A52C4(void);
void        func_800A5300(void);
void        func_800A5330(void);
void        func_800A5874(void);
void        func_800A58F4(void);
void        func_800A59AC(void);
void        func_800A59E8(void);
void        func_800A5A18(void);
void        func_800A5AE4(void);
void        func_800A5DE0(void);
void        func_800A5E54(void);
void        func_800A5E98(void);
void        func_800A5F80(void);
void        func_800A5FF0(void);
bool        func_800A6CF8(u8 selection_id, u8 column_index);
u8          func_800A6D84(void);
void        func_800A6E14(u8 value);
void        func_800A7C14(u8 slot);
extern u8   func_800A805C(void);
extern bool func_800A82A0(u8 selection_id);
extern void Battle_SetGeneCount(void);
void        func_800A83F8(void);
void        func_800A8450(void);
void        func_800A84FC(void);
void        func_800A85A8(void);
void        func_800A8610(void);
void        func_800A8678(void);
void        func_800A87D4(void);
void        func_800A8A28(void);
void        func_800A8B40(void);
void        func_800A8BD0(void);
void        func_800A8CC8(void);
void        func_800A8D3C(void);
extern u32  func_800AA874(u32 bit_index);
bool        func_800AA8A4(s32 battler_index);
bool        func_800AB470(u8 battler_index);
bool        func_800AB4BC(s32 type_index);
void        func_800AB570(s32 battler_index);
u8          func_800AB68C(u8 excluded_slot);
/* func_800ABBE0 */
extern void Battle_LoadScriptedEncounter(void);
extern void func_800ABC30(void);
extern void Battle_LoadEncounterEnemies(void);
void        func_800AD0A8(s32 enemy_index, s32 unit_index);
void        func_800AD2EC(void);
void        func_800AD434(void);
extern void func_800AD4D4(void);
extern void func_800AD5C8(void);
void        func_800AD67C(void);
void        func_800AD71C(void);
void        func_800AD808(void);
extern void func_800AD8D8(void);
extern void func_800AD930(void);
void        func_800AD9AC(void);
void        func_800ADA4C(void);
void        func_800ADB74(void);
void        func_800ADCA4(void);
void        func_800ADD44(void);
void        func_800ADE6C(void);
void        func_800ADF9C(void);
void        func_800AE06C(void);
void        func_800AE09C(void);
void        func_800AE9C4(u8 texture_index);
void        func_800B01F0(void);
void        func_800B0250(void);
void        func_800B0398(void);
void        func_800B0410(void);
void        func_800B0498(void);
void        func_800B06F4(s16 x, s16 y, u8 width, u8 height);
void        func_800B09CC(void);
void        func_800B0A2C(void);
void        func_800B0A54(void);
void        func_800B0AB0(void);
void        func_800B0B0C(s16 base_x, s16 base_y);
void        func_800B0CE4(void);
void        func_800B0D54(void);
void        func_800B0E24(void);
void        func_800B0E6C(void);
void        func_800B0EC4(void);
void        func_800B0F30(void);
extern void func_800B0F9C(void);
void        func_800B138C(void);
void        func_800B13EC(void);
void        func_800B14BC(void);
void        func_800B1504(void);
void        func_800B155C(void);
void        func_800B15BC(void);
void        func_800B1664(void);
void        func_800B16D0(void);
/* func_800B1728 */
extern void Battle_DrawCommandList(void);
/* func_800B1A74 */
extern void Battle_DrawTitledFrame(s16 x, s16 y, s32 unused_a, s32 unused_b, u8 title_index);
void        func_800B20CC(void);
/* func_800B2104 */
void        Battle_DrawInventoryPanel(void);
void        func_800B2158(void);
void        func_800B2198(void);
void        func_800B21D8(void);
void        func_800B2258(void);
void        func_800B22EC(void);
void        func_800B232C(void);
void        func_800B2438(void);
void        func_800B2478(void);
void        func_800B250C(void);
void        func_800B258C(void);
/* func_800B25C0 */
void        Menu_DrawInventoryWindow(MenuPanelTask* task);
void        func_800B2C90(MenuPanelTask* task);
void        func_800B3324(u8 index, s32 x, s32 y, s32 patch, u8 hide_changes, MenuPanelTask* task);
/* func_800B3AE8 */
void        Menu_DrawEquipChoiceWindow(MenuPanelTask* task);
void        func_800B4220(s16 x, s16 y, u8 selected);
/* func_801AF494 */
/* func_801AF930 */
void        UI_ListDrawAbilityRow(s32 x, s32 y, u8 shade, u8 element, u8* name, u8 cost, u8 flags);
/* func_801DB5CC */
u8          Battle_TargetNext(s32 start_slot);
/* func_801DB6F4 */
s32         func_801DD7D8(s32 low_bound, s32 high_bound, s32 current);
/* func_801DD978 */
void        func_801DD978(void);
/* The panel scale helper lives in battle/battle/03 (src/overlays/battle/battle/03/
 * func_801DE0AC.c). Its retail body multiplies $a0 by $a1 and reads no other
 * argument, and every call site in this target passes two words, so the
 * helper takes two parameters. */
/* Multiplies a permanent stat by its dragon form percentage. */
s16         func_801DE0F8(s32 base, s32 percent);
/* Multiplies its inputs and divides by 100. */
s16         func_801DE144(s32 amount, s32 percent);
/* func_801DE8C0 */
void        Battle_AddMessage(u32 index, u32 record_type, u8* text);
/* PsyQ SDK primitive setup helpers called by this target.
 * SetSprt8 / SetSemiTrans are declared by <libgpu.h> (via common.h);
 * GFX_AddPrim is a game primitive-append helper declared by gfx/prim.h. */
/* func_801DE94C */
/* func_801DEA64 */
void        Battle_ShowMessage(void* message_slot);
s32         func_801DEE4C();
void        func_801E24F8(u32 enemy_index, u32 script_index);
#if defined(MATCHING)
/* A second name for Script_Select that also passes the payload the retail call leaves in $a1. */
void Actor_SelectScript_keep_a1(u32 selector, u32 payload);
#else
#define Actor_SelectScript_keep_a1(selector, payload) Script_Select(selector)
#endif
/* func_80097574 */
bool        Battle_IsAbilityLocked(void);
/* func_80097EC0 */
void        Battle_InitAbilityPanel(void);
/* func_8009A744 */
void        Battle_ApplyEquipment(void);
/* func_8009AAE8 */
extern void Battle_PreviewEquipment(void);
/* func_8009B03C */
void        Battle_InitEquipChangePanel(void);
/* func_8009B160 */
void        Battle_InitEquipUsePanel(void);
/* func_8009C994 */
extern void Battle_ApplyEnemyEvent(EnemyBattler* work_arg, BattleEventPacket* event);
extern u8   Battle_EnemyEventTriggered(volatile EnemyBattler* enemy, s32 bit_index);
extern void Battle_SetEnemyEventTriggered(EnemyBattler* enemy, s32 bit, u8 set);
extern u8   func_800A3B6C(u8 battler_index, u8 selection_type, u16 input_mask);
bool        func_800A4FD8(void);
bool        func_800A5D00(void);
u8          func_800A6C2C(void);
s32         Battle_AppendComboIds(u8 combination, u8 count);
/* func_800A9FC4 */
void        Battle_RescalePanel(Character* rec, s32 slot);
bool        func_800AA5F4(s32 slot);
bool        func_800AA7A0(u8 slot);
/* func_800AD044 */
extern u32  Battle_IsEnemyDefeated(u32 bit_index);
extern void func_800B1DAC(s16 x, s16 y, u8 sprite_arg);
u8          func_801DDE7C(u32 counter_index, u32 packed_value);
extern u8   g_BattleUIStep_nv;
extern u8   D_80145F20[];

/* Store half the calculated damage and queue its animation. */
static inline void BattleApplyHalfDamage(s32 anim) {
    s32 half;

    half                              = Battle_CalcDamage(g_Battle.active_battler, g_Battle.target, BATTLE_ELEMENT_FROM_WEAPON) / 2;
    g_Battle.target_record->hp_change = half;
    if (half != 0) {
        func_800A4238(anim);
    }
}

/* Fill the 3x3 slot grid from the queued-slot allocator, then raise the panel.
 * The trailing values differ per member, so each member writes them; the loop
 * is the shared helper. */
static inline void BattleFillEffectGrid(s32 type) {
    s32 offset;
    s32 slot;
    s32 row;

    for (row = 0; (u32)(row & BYTE_MASK) < 3U; row++) {
        for (slot = 0; (u32)(slot & BYTE_MASK) < 3U; slot++) {
            offset                             = Battle_AllocEffect(0, type) & BYTE_MASK;
            g_BattleEffects[offset].unk_0A     = slot;
            g_BattleEffects[offset].arg.unk_09 = row;
        }
    }
}

/* Report whether the status byte at offset differs from the masked compare
 * value, for the first three battlers. */
static inline s32 BattleCompareStatusByte(s32 battler_index, s32 compare_value, s32 offset) {
    volatile u8* entry;
    s32          result;

    result = 1;
    if ((u32)(battler_index & BYTE_MASK) < 3U) {
        entry  = (u8*)(g_Game.current);
        result = (*(entry + offset)) != (compare_value & BYTE_MASK);
    }
    return result;
}

/* Run the handler the spad step byte selects out of the caller's table. */
static inline void Battle_DispatchEffect(BattleEffectSteps* table) {
    BattleEffectSteps handlers;
    PartyMember*      work;

    handlers  = *table;
    work      = TASK(PartyMember);
    g_Scripts = BATTLE_SCRIPT_TABLE;
    ((Callback*)&handlers)[work->header.mode]();
    g_Scripts = AREA_SCRIPT_TABLE;
}

/* Reset the three selection bytes once the lock at -0x7A8D is clear, then run
 * the selection update. */
static inline void BattleResetSelectionState(void) {
    volatile u8* battle_selection_state;
    volatile u8* battle_selection_lock;

    battle_selection_state = (u8*)(PARTY_STATE_PTR);
    battle_selection_lock  = BATTLE_LOCK_RAM_BASE;
    if (battle_selection_lock[-0x7A8D] != 0u) {
        return;
    }

    battle_selection_state[0x62E1u] = 1u;
    battle_selection_state[0x62E2u] = 0u;
    battle_selection_state[0x62E3u] = 0u;
    Battle_ClearMenuPanels();
}

/* Roll a hit against the seeded threshold and the caller's rate table.
 *
 * NOTE: the halves are read through a plain (non-volatile) MEM view: a volatile
 * u16 load widened to the signed /5 dividend emits a redundant `andi 0xFFFF`
 * zero-extend the original bytes do not have.
 */
static inline u8 BattleRollHitChance(u8 selection_type, s16 (*hit_rate)(s32, s32)) {
    s32 rate;
    s32 threshold;
    s32 rollSeed;
    s16 temp;
    u8  ret;

    rollSeed  = *(u16*)&D_801EC312;
    threshold = (rollSeed / 5) + BATTLE_HIT_THRESHOLD_BASE;
    if (threshold >= BATTLE_HIT_THRESHOLD_MAX + 1) {
        threshold = BATTLE_HIT_THRESHOLD_MAX;
    }
    rate = *(u16*)&D_801EC2F2;
    rate = BATTLE_HIT_RATE_BASE - (rate / 5);
    CLAMP_MIN(rate, BATTLE_HIT_RATE_MIN);
    temp = hit_rate((s32)(selection_type & BYTE_MASK), (s32)(D_801CA71C[g_Battle.action_id].mask & ELEM_ALL));
    if (temp == -1) {
        ret = 0;
    } else {
        ret = (RANDOM_PERCENT()) >= ((threshold * rate * temp) / 10000);
    }
    return ret;
}

/* Write the selected battler's action result from the selection value that the
 * mode selects, clamped at zero. */
static inline void BattleSelectionDelta(s32 mode) {
    /* FAKE: retail keeps the cell address in $s0 across both selection calls;
     * without the pin GCC rematerialises it after each call and the function
     * measured 0xC short. */
    FAKE_REG(BattleTargetSelection*, ctx, "s0");
    BattleTurn* result;
    u16         value;

    ctx = (BattleTargetSelection*)&g_Battle.target;
    if (ctx->sel < 3u) {
        value                                                        = Battle_RollHpDamage(mode);
        (*(volatile BattleTurn**)&g_Battle.target_record)->hp_change = (s16)(value - g_Game.members[ctx->sel].chr.stats.defense);
    } else {
        value                                                        = Battle_RollHpDamage(mode);
        (*(volatile BattleTurn**)&g_Battle.target_record)->hp_change = (s16)(value - ENEMY_COMBATANT(ctx->sel).stats.defense);
    }

    result = g_Battle.target_record;
    if (result->hp_change < 0) {
        result->hp_change = 0;
    }
}

/* Set the selection flag on the chosen battler or mark the pending record,
 * then run the panel update. */
static inline void BattleSetSelectionFlag(u32 flag) {
    u32         mode;
    BattleTurn* record;
    u8          one;

    if (Battle_PickAbility(g_Battle.active_battler, g_Battle.target) == 0) {
        mode = g_Battle.target;
        if (mode < 3u) {
            g_Game.members[mode].u.turn.action_flags.value |= flag;
        } else {
            ENEMY_COMBATANT(mode).turn.action_flags.value |= flag;
        }
        Battle_RescaleStats(g_Battle.target);
    } else {
        record               = *(BattleTurn**)&g_Battle.target_record;
        /* FAKE: volatile-drop cell read keeps the constant load ahead of
         * the pointer load, so the branch delay slot takes it. */
        one                  = 1;
        record->target_flags = one;
        Battle_QueueAction(0, g_Battle.target);
    }
    Battle_MarkDamageApplied();
}

/* Run the handler quad at offset with the spad step. */
static inline void BattleRunHandlerQuad(s32 offset) {
    BattleTaskModes handlers;
    PartyMember*    work;

    handlers = *(BattleTaskModes*)((Callback*)&D_800969B8 + offset);
    handlers.modes[TASK(PartyMember)->header.mode]();
    work = TASK(PartyMember);
    if ((work->header.flags != 0u) && (work->header.mode != 0u)) {
        func_800AE9C4(work->unk_04);
    }
}

/* Seed the panel task after the queued slot grid is filled. */
static inline void Battle_SeedQueuedSlotPanel(u8 unk14, u8 unk08) {
    g_UiPanelCurrent->u.addr.unk_14 = unk14;
    g_UiPanelCurrent->unk_08        = unk08;
    g_UiPanelCurrent->unk_09        = 0x11;
    g_UiPanelCurrent->state         = (u8)(g_UiPanelCurrent->state + 1);
}

u8 func_800A40D0(u8 battler_index);

/* func_800AED5C */
u8 Battle_CanTarget(s32 selector, u32 battler_index);

volatile u8* Battle_FindActorEntry(u8 entry_id);
void         Battle_MoveRangeToward(BattleRange* target, s32 step);
u8           Battle_SelectStepRule(void);

/* Add the queued text message and advance the battle UI state. The member declares temp. */
#define BATTLE_ADD_MESSAGE_AND_STEP() \
    temp = UI_MessageGetText(0x4000); \
    Battle_AddMessage(2, 0xFF, temp); \
    g_Battle.ui_mode += 1;

#endif
