#ifndef OVERLAY_BATTLE_BATTLE_03_H
#define OVERLAY_BATTLE_BATTLE_03_H

/* The battle/battle/03 overlay's local declarations: the command, step and damage
 * dispatch tables, its actor views and the prototypes its units share. The
 * common records are in battle/records.h; only this image includes this file. */

#include "overlays/battle/battle.h"
#include <stdio.h>
#include <memory.h>
#include "menu/draw.h"
#include <strings.h>

/* retail addresses */

/* Battle state machine: the battle mode byte 0x801462E0 selects one of the six
 * handler words at 0x801D0C04, the step byte 0x801462E1 selects one
 * of the mode's step words, and the sub-step byte 0x801462E2 one of the four
 * entrance words at 0x801D0C1C. */
/* The per-frame passes func_801D1014 runs, in its order. */
/* The damage chain. */
/* The queued battle panel slots, and the size a drawn panel gets: its row
 * width g_BattlePanelWidths plus this margin, or this margin alone for an empty row. */
#define BATTLE_PANEL_SLOT_COUNT        5
#define BATTLE_PANEL_SIZE              0x10
#define BATTLE_GLOBAL_BYTE_630C(index) MEM(volatile u8, 0x8014630Cu + (u32)(index))
/* Current enemy-work pointer cell (fixed RAM, not scratchpad). */
#define BATTLE_CURRENT_ENEMY_PTR       (*(volatile EnemyBattler**)&g_BattleCurrentEnemy)
#define BATTLE_LOCAL_BYTE_79(work)     MEM(volatile u8, (u32)(work) + 0x79u)
#define BATTLE_LOCAL_BYTE_119(work)    MEM(volatile u8, (u32)(work) + 0x119u)
#define BATTLE_LOCAL_WORD_124(work)    MEM(volatile u32, (u32)(work) + 0x124u)
#define BATTLE_ENEMY_BYTE_F5(work)     MEM(volatile u8, (u32)(work) + 0xF5u)
#define BATTLE_ENEMY_WORD_100(work)    MEM(volatile u32, (u32)(work) + 0x100u)
/* Panel-task root pointer cell at 0x801485C8 (u8* volatile). */
#define BATTLE_PANEL_ROOT_BASE         D_80150000
/* Base-pointer accessors for fixed RAM regions (preserve lui+offset codegen).
 */
/* FAKE: retail reads D_80140000 as volatile u16[]. */
#define BATTLE_GLOBAL_RAM_U16          ((volatile u16*)D_80140000)
/* Additional fixed-base tables and dispatch helpers. */
#define BATTLE_ENDING_BYTES            ((volatile u8*)&g_BattleMode)
/* Single fixed-address globals (inline; no symbol binding required). */
#define BATTLE_GLOBAL_WORD_598C        (*(u32*)&g_GfxPrimCursor)
#define BATTLE_GLOBAL_BYTE_62F3        (*(u8*)&D_801462F3)
#define g_GameState                    ((PartyBattler* volatile)g_GameState)
#define g_SpadWork                     ((PartyBattler*)g_SpadWork)

/* The fixed panel-task argument table preserves the caller's whole argument
 * block for the selected entry; no lifted caller names those seven words yet,
 * so they keep the panel-task spelling and the selector pointer it also
 * receives. No generic entry carries this contract. */
typedef void (*BattlePanelForwardFunc)(s32 panel_arg0, s32 panel_arg1, s32 panel_arg2, s32 panel_arg3, s32 panel_arg4,
                                       s32 panel_arg5, s32 panel_arg6, u8* selector);

/* The panel task's kind byte (+0x02) selects one of these eight update
 * routines; func_801E9074 copies the table and dispatches. */
typedef struct {
    Callback handlers[8];
} BattlePanelFuncs;

/* The queued slot's kind (+0x05) selects one of these eight handlers in slot
 * mode 3 (`g_BattleEffectStages` row 3); func_801E5C1C copies the
 * table and dispatches. */
typedef struct {
    Callback handlers[8];
} BattleEffectStage3Funcs;

/* The queued slot's kind (+0x05) selects one of these 110 handlers in slot
 * mode 1 (`g_BattleEffectStages` row 1); func_801E5B8C copies the
 * table and dispatches. */
typedef struct {
    Callback handlers[110];
} BattleEffectStage1Funcs;

/* The eight random damage percentages Battle_CalcDamage copies to the stack. */
typedef struct DamageSpread {
    u8 percent[8];
} DamageSpread;

/* One 0xC-byte row of the sprite slot table at D_80145BD4. */
typedef struct BattleSpriteSlot {
    u8 pad_00[2];
    u8 unk_02; /* +0x02 second copy of the shared sprite value */
    u8 unk_03;
    u8 unk_04;
    u8 pad_05[7];
} BattleSpriteSlot;

ASSERT_SIZE(BattleSpriteSlot, 0xC);

/* One 0xC-byte row of the event slot table at g_BattleEventSlots; D_801EB4DC points at the running row. */
typedef struct BattleEventSlot {
    u8  unk_00;
    u8  unk_01;
    u8  pad_02;
    u8  unk_03;
    u8  pad_04[4];
    u16 unk_08;
    u8  pad_0A[2];
} BattleEventSlot;

ASSERT_SIZE(BattleEventSlot, 0xC);

/* One of the two 4-byte drop rows at EnemyBattler+0x98 (func_801E531C). */
typedef struct BattleSpritePrimitive {
    u8  pad_00[4];
    u8  r0;
    u8  g0;
    u8  b0;
    u8  pad_07;
    s16 x0;
    s16 y0;
    s16 unk_0C;
    s16 unk_0E;
} BattleSpritePrimitive;

/* The battle sub-step byte 0x801462E2 selects one of these four entrance
 * handlers, copied to the stack from 0x801D0C1C. */
typedef struct {
    Callback handlers[4];
} BattleEntrances;

/* The queued slot's mode (+0x06, stored by Battle_AllocEffect) selects one
 * of these four stage handlers, copied to the stack from 0x801D0CC0. */
typedef struct {
    Callback handlers[4];
} BattleEffectStages;

/* The 0x20-byte stat block from max_hp on (Character +0x1C, local-work
 * row +0x90), copied with unaligned word pairs. */
typedef struct BattleStatBlock {
    u8 bytes[0x20];
} BattleStatBlock;

/* Drop chance per EnemyBattlerDrop.rate_02, out of 256: 0, 0, 1, 3, 7, 31, 127, 255. */
typedef struct DropChances {
    u8 chance[8];
} DropChances;

/* The battle panel's own 0x24-stride entry table at 0x80148332: the base
 * symbol is the table's first byte, so its fields start at +0. */
typedef struct BattlePanel {
    u8  mode_00;    /* +0x00 panel mode; Battle_ReserveStagePanels writes 5 and 7 */
    u8  unk_01;     /* +0x01 */
    s16 x_02;       /* +0x02 panel x */
    s16 y_04;       /* +0x04 panel y */
    u8  unk_06;     /* +0x06 */
    u8  unk_07;     /* +0x07 */
    u8  battler_08; /* +0x08 the battler the entry belongs to */
    u8  pad_09[0x1B];
} BattlePanel;

ASSERT_SIZE(BattlePanel, 0x24);
ASSERT_OFFSET(BattlePanel, x_02, 0x02);
ASSERT_OFFSET(BattlePanel, y_04, 0x04);
ASSERT_OFFSET(BattlePanel, battler_08, 0x08);

/* The battle mode byte 0x801462E0 selects one of these six handlers, copied to
 * the stack from 0x801D0C04. */
typedef struct {
    Callback handlers[6];
} BattlePhases;

/* Seven-byte palette table copied from the icon CLUT source at 0x801D0C64. */
typedef struct BattleIconColors {
    u8 bytes[7];
} BattleIconColors;

/* 8-byte panel frame record: origin of the frame drawn for one panel id. */
typedef struct BattlePanelFrame {
    s16 unk_00;
    u16 unk_02;
    u8  pad_04[4];
} BattlePanelFrame;

/* Ability category record at 0x801CA719, stride 0x14. */
typedef volatile struct BattleAbilityCategory {
    u8 value;
    u8 pad_001[0x13];
} BattleAbilityCategory;

/* Ranked owner entries at 0x801EB550 (value at +0, battler index at +2). */
typedef struct BattleRank {
    s16 value;
    u16 index;
} BattleRank;

/* The queued slot's kind (+0x05) selects one of these 19 handlers in slot mode
 * 0 (`g_BattleEffectStages` row 0); func_801E5AF4 copies the table
 * and dispatches. */
typedef struct {
    Callback handlers[19];
} BattleEffectStage0Funcs;

/* Fixed five-entry saved-preview/result handler table at 0x801D0F6C. */
typedef struct {
    Callback handlers[5];
} BattleSavedPreviewFuncs;

/* The panel task forwarder func_801EA1E0 calls the routine its selector names
 * with the caller's seven words. */
typedef struct {
    BattlePanelForwardFunc handlers[3];
} BattlePanelTaskForwarders;

/* Overlay data and routines the sources use; names are the retail addresses. */
extern u8               D_1F800002;
extern u16*             D_800B4A64;
extern u16*             D_800B4A68;
extern u8               D_800B51F8[];
extern void*            D_800B6178[];
/* D_800B65F8 */
extern BattleSelection  g_BattleSelections[];
/* D_80143F00 */
extern u16              g_GameAreaId;
extern BattleSpriteSlot D_80145BD4[];
extern s32              D_80145BD6;
extern s32              D_80145ED0;
extern u8               D_80145F09[][BATTLE_PARTY_STRIDE];
extern volatile u8      D_80145F18[];
extern volatile u8      D_80145F1C[];
extern u8               D_80145F20[];
extern u8               D_80145F22[];
/* One-field views of the same rows: the local rows (stride 0x140) and the
 * enemy rows (stride 0x118), each anchored at the field the retail symbol
 * names. */
extern u8               D_80145FB1;
extern u8               D_80145FB2[];
/* FAKE: func_801D4B38 and func_801D64C4 only match with the flags cell as its own volatile word row. */
extern volatile u32     D_80145FB8[][80];
extern u8               D_80145FC6;
extern u8               D_80145FC7;
/* D_801462E3 */
extern u8               g_BattleUiStep;
extern u8               D_80145FC9;
extern u8               D_801462E7;
/* D_801462F0 */
extern u8               g_BattlePartyCount;
extern u8               D_801462F6[];
extern u8               D_80146304; /* oscillation direction latch */
extern u8               D_80146308; /* UI oscillator byte */
extern u8               D_8014630C;
extern u8               D_80146327;
extern u8               D_80146364[];
/* D_80146374 */
extern u8               g_BattleActingBattler;
extern u16              D_80146388;
/* D_80146394 */
extern u8               g_BattleTarget;
/* The active record's 0x118 result cells. */
/* D_801463A0 */
extern s16* volatile g_BattleTargetRecord;
/* Shared step callback: returns a u8 result byte (func_801D656C masks it with
 * 0xFF and compares it with 0xFF). */
/* D_801463AC */
extern u8 (*g_BossBattleEventHook)(u32);
extern volatile u16 D_801463B0;
extern volatile u8  D_801463BA;
extern u32          D_801463D0;
/* D_801463D8 */
extern u16          g_BattlePendingStatus;
extern s16          D_801463DA;
/* The units that must reload the cell after every store read it volatile. */
extern volatile u8  D_80146855;
extern volatile u8  D_80146856;
extern BattlePanel  D_80148332[];
/* UI state byte of the 0x8014837A bundle the entrance sequence writes; the
 * battle/battle/15 and etc/shop/00 targets declare their own. */
extern s32          D_80149298;
extern void         D_801492B8;
extern u8* volatile D_80150000[];
/* Non-const view: a const declaration moves the generated bytes of func_801D7234. */
extern BgmTrack                  D_80181EB8[BGM_TRACK_COUNT];
extern void*                     D_801C893C[];
extern void*                     D_801C8950[];
extern volatile u8               D_801CA718[][20];
extern BattleAbilityCategory     D_801CA719[];
/* D_801D0C04 */
extern BattlePhases              g_BattlePhases;
/* D_801D0C1C */
extern BattleEntrances           g_BattleEntrances;
extern BattleIconColors          D_801D0C64;
/* The overlay head keeps these in .data, so their definitions are non-const. */
extern char                      D_801D0C6C[];
extern char                      D_801D0C70[];
extern char                      D_801D0C74[];
extern s8                        D_801D0C78[];
extern DamageSpread              D_801D0C7C;
/* D_801D0C84 */
extern BattleHandlerTable5       g_BattleEvents;
/* D_801D0C98 */
extern u8                        s_BattleCueIds[];
extern DropChances               g_BattleDropChances;
/* D_801D0CC0 */
extern BattleEffectStages        g_BattleEffectStages;
/* D_801D0CD0 */
extern BattleEffectStage0Funcs   g_BattleEffectStage0Funcs;
/* D_801D0D1C */
extern BattleEffectStage1Funcs   g_BattleEffectStage1Funcs;
/* D_801D0ED4 */
extern BattleEffectStage3Funcs   g_BattleEffectStage3Funcs;
extern BattleHandlerTable5       D_801D0EF4;
extern BattleHandlerTable3       D_801D0F20;
extern BattleHandlerTable3       D_801D0F2C;
extern BattleHandlerTable3       D_801D0F38;
extern BattleHandlerTable5       D_801D0F44;
extern BattleHandlerTable5       D_801D0F58;
extern BattleSavedPreviewFuncs   D_801D0F6C;
/* D_801D0F80 */
extern BattlePanelFuncs          g_BattlePanelFuncs;
extern BattleHandlerTable3       D_801D0FA0;
extern BattleHandlerTable3       D_801D0FAC;
extern BattleHandlerTable3       D_801D0FB8;
extern BattleHandlerTable3       D_801D0FC4;
/* The panel's four state handlers; func_801E960C copies them to the stack
 * before the indexed call. */
extern Callback                  D_801D0FD0[4];
extern BattleHandlerTable3       D_801D0FE0;
/* D_801D0FEC */
extern BattlePanelTaskForwarders g_BattlePanelTaskForwarders;
extern BattleHandlerTable3       D_801D0FF8;
extern BattleResultRings         D_801D1004;
extern Callback                  D_801EABB8[];
extern Callback                  D_801EABD8[];
extern Callback                  D_801EABE4[];
extern Callback                  D_801EAC04[];
extern Callback                  D_801EAC10[];
extern Callback                  D_801EAC24[];
extern Callback                  D_801EAC2C[];
extern Callback                  D_801EAC44[];
extern Callback                  D_801EAC4C[];
/* D_801EAC58 */
extern volatile u8               g_BattleRecallAbilities[];
/* D_801EAC78 */
extern volatile u8               g_BattleMagicShuffleAbilities[];
extern Callback                  D_801EAC98[];
extern Callback                  D_801EACA4[];
extern Callback                  D_801EACB0[];
extern Callback                  D_801EACBC[];
extern Callback                  D_801EACC8[];
extern Callback                  D_801EACD4[];
extern Callback                  D_801EACE8[];
extern Callback                  D_801EACF4[];
extern Callback                  D_801EAD00[];
extern Callback                  D_801EAD0C[];
extern Callback                  D_801EAD20[];
extern s16                       D_801EAD30[]; /* Eight signed vertex offsets per shape, 0x10 bytes a shape. */
extern u16                       D_801EAE50[];
extern u16                       D_801EAE52[];
/* D_801EAE94 */
extern u8                        s_BattlePanelOffsets[][2];
extern s8                        D_801EAEA6;
extern volatile u32              D_801EAEB0[]; /* panel icon blit table */
extern BattlePanelFrame          D_801EAEE8[];
extern u8                        D_801EAF27[];
extern volatile u8               D_801EAF2C[];
extern volatile u8               D_801EAF2D[];
extern volatile u8               D_801EAF2E[];
extern volatile u8               D_801EAF2F[];
extern volatile s8               D_801EAF48[64];
/* D_801EAF94 */
extern u8                        s_BattleDamageBandDivisors[12]; /* nine damage divisor bytes, then three pad bytes */
extern s32                       D_801EAFA0[8];                  /* melee damage multipliers */
extern s16                       D_801EAFC0[8];                  /* offensive-holy multipliers */
extern u16          D_801EAFD0[]; /* Effect id triplets indexed by the local work's pending-effect halfword. */
/* D_801EAFF4 */
extern u8           s_BattleStatusRecoveryPenalties[];
/* D_801EAFFC */
extern u8           s_BattleStatusRecoveryChances[];
/* D_801EB000 */
extern u8           s_BattleActionNames[12][13];
extern const u8     D_801EB00D[];
extern s32          D_801EB04E;
extern u8           D_801EB05B[];
extern u8           D_801EB068[];
extern u8           D_801EB075[];
extern u8           D_801EB082[];
extern s32          D_801EB08F;
extern volatile u16 D_801EB09C[][10]; /* Event-script rows (10 halfwords each) in high RAM. */
/* D_801EB108 */
extern u8           s_BattlePanelYOffsets[];
extern u8           D_801EB109[];
extern Callback     D_801EB120[];
extern void (*D_801EB154[])();
extern Callback         D_801EB15C[]; /* Local-state dispatch tables in high RAM. */
extern Callback         D_801EB188[];
/* D_801EB18C */
extern u8               s_BattleCharacterSprites[];
extern s32              D_801EB198;
/* D_801EB1B4 */
extern Callback         g_BattleTaskFuncs[];
extern Callback         D_801EB1BC[];
extern Callback         D_801EB1D4[];
extern Callback         D_801EB1E0[];
extern Callback         D_801EB1F4[];
extern Callback         D_801EB210[];
extern Callback         D_801EB218[];
extern Callback         D_801EB224[];
/* D_801EB230 */
extern u8               s_BattleCharacterStepIds[];
extern u8               D_801EB23C[];
extern Callback         D_801EB258[];
extern Callback         D_801EB26C[];
extern Callback         D_801EB274[];
extern Callback         D_801EB27C[];
extern Callback         D_801EB294[];
extern Callback         D_801EB298[];
extern u8               D_801EB35C[];
/* Party formation weights: one byte per slot in the formation, two slots per
 * formation in the first table and three in the second (func_801E2E30). */
/* D_801EB394 */
extern u8               s_BattlePartialPartyTargetWeights[3][2];
/* D_801EB39C */
extern u8               s_BattleFullPartyTargetWeights[6][3];
extern Callback         D_801EB3B0[];
extern s32              D_801EB3DC;
extern Callback         D_801EB3E4[];
extern Callback         D_801EB3EC[];
extern Callback         D_801EB3F4[];
extern Callback         D_801EB3FC[];
extern Callback         D_801EB404[];
extern Callback         D_801EB40C[];
extern Callback         D_801EB424[];
extern Callback         D_801EB430[];
extern Callback         D_801EB444[];
extern Callback         D_801EB454[];
extern Callback         D_801EB460[];
extern Callback         D_801EB46C[];
extern Callback         D_801EB478[];
/* D_801EB494 */
extern u8               s_BattleBattlerStepIds[];
/* Effect-type tables: the offset the effect starts at, and the cue byte per
 * type and step (func_801E679C). */
extern u8               D_801EB4A4[];
extern u8               D_801EB4B0[];
extern BattleEventSlot* D_801EB4DC;
extern s8               D_801EB4F2;
extern volatile u8      D_801EB4F3[][12];
extern volatile u16     D_801EB4F8[][6];
extern BattleRank       D_801EB550[];
extern u8               D_801EB5B0[];
extern u8               D_801EB635[][280];
extern u8               D_801EB638[][280];
extern s16              D_801EB65E[][140];
extern u16              D_801EB660[][140];
extern u8               D_801EB6A4[][0x118];
extern volatile u16     D_801EB6B0[][140];
extern u8               D_801EB6BC[];
extern u8               D_801EB6D0[];
extern s8               D_801EB712[];
extern u8               D_801EB730[];
extern volatile u32     D_801EB734[][70];
extern u8               D_801EBF04;
/* D_801EBF20 */
extern u8 s_BattleBattlerTemplates[]; /* Alternate local work entries (stride 0x140) and their paired status words. */
/* D_801EC048 */
extern u8 s_BattleBattlerTemplateTails[];
extern BattleEffect* volatile D_801EC2E0;
extern u8              D_801EC2E4;
extern BattleStatBlock D_801EC2E8;
extern u16             D_801EC2EE;
extern u8              D_801EC303;
extern u16             D_801EC30C;
/* The queued-slot companion tables, one entry per 0x78-byte queued slot: the
 * action kind, the cue byte and the two work-pointer words. The retail
 * addresses them as a base plus the slot's offset, so the declaration stays a
 * scalar base. */
extern u8              D_801EC337;
extern u8              D_801EC357;
extern u8              D_801EC364[];
extern u8              D_801EC368[];
extern u8              D_801EC36C[];
extern volatile u8     D_801F0000[];

void func_80096A74(void);
void func_80096F00(void);
void func_800980A8(void);
void func_8009834C(void);
void func_8009B274(void);
void func_8009BBE8(void);
void func_8009BFC4(void);
void func_8009D198(void);
u16  func_800A2AE0(u8 arg0);
void func_800A31E0(u32 selection_kind, u32 input_mask);
void func_800A36F0(u32 battler_index, u32 flags);
u8   func_800A3DF8(u32 battler_index, u32 selection_kind);
void func_800A4688(void);
void func_800A8540(void);
void func_800A8C60(void);
void func_800A8D80(void);
s32  func_800A8F58(void);
u8   func_800A94A8(void);
u8   func_800A955C(void);
s32  func_800A99AC(void);
s32  func_800A9A84(void);
s32  func_800A9B44(void);
s32  func_800AA368(void);
s32  func_800AA8FC(void);
void func_800AB0B8(u32 arg0, u8 arg1, u8* arg2);
void func_800AB834(void);
void func_800AB910(void);
s32  func_800ABBA4(void);
void func_800AC964(void);
void func_800AD074(u8 bit_index);
void func_800AD69C(void);
void func_800AD9CC(void);
void func_800ADCC4(void);
void func_800ADFBC(void);
s32  func_800AE108(u8 battler_index, s32 work_ptr);
s32  func_800AE260(u16 selection, s32 payload);
void func_800AE2D4(u32 selection);
void func_800AE34C(void);
void func_800AE4D0(void);
void func_800AE788(void);
void func_800C1804(void);
void func_800C1810(void);
void func_800C1814(void);
void func_800C181C(void);
void func_800C1820(void);
void func_800C1838(void);
void func_800C184C(void);
void func_800C1850(void);
void func_800C1860(void);
void func_800C1864(void);
void func_800C18F0(void);
void func_800C18FC(void);
void func_800C190C(void);
void func_800C193C(void);
void func_800C1950(void);
void func_800C19B4(void);
void func_800C19BC(void);
void func_800C19E4(void);
void func_800C19E8(void);
void func_800C1A34(void);
void func_800C1A54(void);
void func_800C1AA8(void);
void func_800C1B40(void);
void func_800C1B6C(void);
void func_800C1B84(void);
void func_800C1BEC(void);
void func_800C1C58(void);
void func_800C1C98(void);
void func_800C1CC4(void);
void func_800C1CD8(void);
void func_800C1D30(void);
void func_800C1D54(void);
void func_800C1D88(void);
void func_800C1DB0(void);
void func_800C1DC4(void);
void func_800C1E2C(void);
void func_800C1EA0(void);
void func_800C1EB0(void);
void func_800C26D4(void);
void func_800C2FF4(void);
void GFX_StagePalette(u8* dst, s32 field);
/* func_8019651C */
s32  GFX_AllocPaletteFade(u8* color_data, s32 palette_base, s32 palette_count, s32 palette_index, s32 flag_value);
/* func_80196718 */
void GFX_FreePaletteFadeTarget(void* target);
void func_801A061C(void);
/* func_801D1014 */
void Battle_Update(void);
/* func_801D112C */
void Battle_DispatchMode(void);
/* func_801D11D8 */
void Battle_DispatchStep(void);
extern void   func_801D1228(void);
/* func_801D17C4 */
void          Battle_DispatchEntrance(void);
/* func_801D1AB4 */
void          Battle_WaitUiMode(void);
/* func_801D1AE8 */
void          Battle_InitPanels(void);
/* func_801D1B94 */
void          Battle_EnterIntro(void);
/* func_801D3844 */
u8            Battle_PickTarget(void);
void          func_801D4850(void);
void          func_801D4D44(void);
u8            func_801D54F8(void);
u8            func_801D5658(void);
u8            func_801D57AC(void);
u8            func_801D590C(void);
u8            func_801D5A60(void);
u8            func_801D5BC0(void);
u8            func_801D5DCC(void);
u8            func_801D64C4(u8 battler_index);
void          func_801D750C(s32 x, s32 y);
void          func_801D7A40(s16 x, s16 y);
void          func_801D7D10(u8 clut_index, u16 x, u16 y, u16 width, u8 height, u8 shade);
void          func_801D7EB0(s32 x, s32 y);
void          func_801D8450(u32 panel_index);
void          func_801D8690(s32 x, s32 y, s32 slot);
void          Battle_DrawEnemyNamePanel(s32 x, s32 y, s32 slot);
void          func_801D8DF8(s32 panel_x, s32 panel_y, u32 index);
void          func_801D9304(u8 arg0);
void          func_801D9388(u8 arg0);
void          func_801D93E4(u8 arg0);
void          func_801D9428(u8 arg0);
void          func_801D94D4(s32 x, u32 y, s32 clut_index, s32 text_value);
/* func_801D9684 */
void          Battle_DrawNumber(s16 x, s16 y, u8 palette, u16 value);
void          func_801D9804(s32 x, s32 y, s32 clut_index, s32 glyph_index);
void          func_801D9900(void);
void          func_801D99AC(s16 x, s16 y, u8 template_index);
void          func_801D9AB4(s16 x, s16 y, s32 shape_index, s32 shade);
void          func_801D9C80(s16 x, s16 y, u8 template_index, u8 shade);
void          func_801D9DBC(s16 x, s16 y, u8 template_index, u16 packed_color, u8 semi_trans);
void          func_801D9E9C(s16 arg0, s16 arg1, u16 arg2, u16 arg3, s8 arg4);
void          func_801DA078(s32 x, s32 y, s32 u_index);
void          func_801DA408(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b);
void          func_801DA4B4(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b);
void          func_801DA5A8(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b);
u8            func_801DA69C(u32 enemy_index);
void          func_801DA7D4(void);
u8            func_801DB058(void);
u8            func_801DB2F8(u32 battler_index);
u8            func_801DB3A0(u32 battler_index, u32 average_threshold, u32 max_threshold);
u8            func_801DB3E4(u32 battler_index, u32 average_threshold, u32 max_threshold);
u32           func_801DB434(u8 compare_value, u32 row_index);
void          func_801DB494(void);
/* func_801DB524 */
u8            Battle_SlotIsBlocked(u32 slot);
u8            func_801DB844(u32 battler_index);
u8            func_801DB9E4(u32 battler_index);
PartyBattler* func_801DBB20(u8 selector);
/* func_801DBB78 */
u32           Battle_ApplyDamage(u8 attacker, u8 target);
u32           func_801DC73C(s16 damage, u32 battler_index, u32 slot_index);
u32           func_801DC894(s16 damage, u8 attacker, u8 target);
u32           Battle_RollBaseDamage(u8 attacker, u8 target, u8 skip_reduction);
u32           func_801DCCB0(void);
u32           func_801DCD50(u32 unused, u8 battler_index, s32 damage_value);
void          func_801DCEF8(u32 battler_index);
void          func_801DD08C(void);
void          func_801DD29C(void);
void          func_801DD350(s32 arg0);
void          func_801DD3CC(s32 arg0);
u8            func_801DD448(void);
extern u8     func_801DD704(u8 battler_index);
extern u8     func_801DD7AC(s32 selector);
void          func_801DD800(void);
void          func_801DD8AC(u32 battler_index);
void          func_801DDAF0(void);
void          func_801DDB7C(void);
u8            func_801DDCB4(u32 battler_index);
u8            func_801DDE7C(u32 slot_index, u32 packed_value);
u8            func_801DDF50(u16 entry_id, u32 table_kind);
void          func_801DE1D4(void);
/* func_801DE43C */
void          Battle_RunEvents(void);
void          func_801DE60C(u32 slot, u8 action_kind, u8 arg2, u8 arg3, u8 arg4, u8* payload);
void          func_801DE690(void);
void          func_801DE7FC(void);
void          func_801DE804(void);
u8            func_801DE858(s8 event_kind);
/* func_801DE8C0 */
void          BattleStageSelectionRingRecord(s8 slot_index, s8 record_kind, u8* text);
u8            func_801DE92C(void);
void          Battle_SetTextPartyName(u32 party_slot);
void          Battle_SetTextEnemyName(u32 enemy_index);
/* func_801DEA64 */
void          BattleStageMessageResource(s32 message_slot);
void          func_801DEAE0(void);
void          func_801DEBC4(u32 script_index, u32 event_index);
/* func_801DECE0 */
void          Battle_RunParty(void);
/* func_801DED54 */
void          Battle_UpdatePartyActors(void);
u8            func_801DEDE4(void);
u8            func_801DEE4C(void);
void          func_801DEEB4(void);
void          func_801DEF0C(void);
void          func_801DEFE4(void);
void          func_801DF34C(void);
void          func_801DF8AC(void);
void          func_801DF914(void);
void          func_801DFC20(void);
void          func_801E019C(void);
void          func_801E046C(void);
void          func_801E0B64(void);
u8            func_801E0E0C(void);
void          func_801E1298(void);
void          func_801E1450(void);
void          func_801E1670(void);
void          func_801E1B2C(void);
void          func_801E1B64(void);
void          func_801E1CD8(void);
void          func_801E1DD4(void);
void          func_801E1E7C(void);
/* func_801E2170 */
void          Battle_RunEnemies(void);
/* func_801E2284 */
void          Battle_UpdateEnemyActors(void);
void          func_801E25E0(u8 arg0);
void          func_801E2948(s8 enemy_index);
u8            Battle_PickEnemyTarget(u8 enemy_index);
u8            func_801E2CA4(void);
/* bytes, caller passes a byte index, no sign extension */
u8            func_801E2D4C(u8 slot_offset);
u8            func_801E2D90(u8 slot_offset);
u8            func_801E2E30(void);
/* bytes, caller passes a byte index, no sign extension */
u8            func_801E30B8(u8 slot_offset);
void          func_801E31C8(void);
u8            func_801E4368(void);
void          func_801E4490(void);
void          func_801E47E0(void);
void          func_801E4928(void);
void          func_801E4F34(void);
void          func_801E531C(void);
/* func_801E5824 */
void          Battle_RunEffects(void);
void          func_801E5AF4(void);
void          Battle_DrawRollingDigits(u8 palette);
void          func_801E679C(void);
void          func_801E68EC(void);
void          func_801E6C84(void);
void          func_801E72A8(void);
void          func_801E72F4(void);
void          func_801E74B8(void);
void          func_801E7818(void);
u8            func_801E7B34(void);
void          func_801E7BA0(void);
void          func_801E862C(void);
extern void   func_801E8684(void);
extern void   func_801E8D04(void);
void          func_801E8DD8(void);
u8            func_801E8FA8(void);
void          func_801E9074(void);
void          func_801E915C(void);
void          func_801E91CC(void);
void          func_801E949C(void);
void          func_801EA174(void);
void          func_801EA1A4(void);
void       func_801EA1E0(s32 panel_arg0, s32 panel_arg1, s32 panel_arg2, s32 panel_arg3, s32 panel_arg4, s32 panel_arg5,
                         s32 panel_arg6, u8* selector);
void       func_801EA650(void);
void       func_801EA7DC(void);
void       func_801EAAB8(void);
u8         func_801EAB38(void);
u8         func_801EAB6C(u8* message);
/* The effect entry points this overlay calls by their fixed address. */
void       func_801EEEC8(void);
void       func_800AE1F8(s32 selection_index); /* defined by the battle/battle/15 chain */
extern s32 D_80145FB4;
extern void func_801D1C54(void);
extern void func_801D1C90(void);
extern void func_801D1D10(void);
extern void func_801D1E8C(void);
extern void func_801D22AC(void);
extern void func_801D22E8(void);
extern void func_801D238C(void);
extern void func_801D2480(void);
extern void func_801D24D4(void);
extern void func_801D251C(void);
extern void func_801D25A0(void);
extern void func_801D2740(void);
extern void func_801D277C(void);
extern void func_801D28E8(void);
extern void func_801D2A24(void);
extern void func_801D2AA8(void);
extern void func_801D2B1C(void);
extern void func_801D2B58(void);
extern void func_801D2FC0(void);
extern void func_801D3014(void);
extern void func_801D3050(void);
extern void func_801D3168(void);
extern void func_801D31C0(void);
extern void func_801D31FC(void);
extern void func_801D3280(void);
extern void func_801D32C8(void);
extern void func_801D3304(void);
extern void func_801D3624(void);
extern void func_801D39BC(void);
extern void func_801D3A28(void);
extern void func_801D3A64(void);
extern void func_801D3BB4(void);
extern void func_801D3C1C(void);
extern void func_801D3C88(void);
extern void func_801D3CC4(void);
extern void func_801D3E80(void);
extern void func_801D3F6C(void);
extern void func_801D3FEC(void);
extern void func_801D4028(void);
extern void func_801D409C(void);
extern void func_801D42B4(void);
extern void func_801D43EC(void);
extern void func_801D4AC0(void);
extern void func_801D4AFC(void);
extern void func_801D4B38(void);
extern void func_801D5008(void);
extern void func_801D5024(void);
extern void func_801D656C(void);
extern void func_801D6774(void);
extern void func_801D67B0(void);
extern void func_801D67EC(void);
extern void func_801D6818(void);
/* func_801D6A14 */
extern void Battle_StreamEndOverlay(void);
extern void func_801D6C84(void);
extern void func_801D6CC0(void);
extern void func_801D6D90(void);
extern void func_801D6DE4(void);
extern void func_801D6E20(void);
extern void func_801D6EAC(void);
extern void func_801D6EEC(void);
extern void func_801D6F28(void);
extern void func_801D7108(void);
extern void func_801D716C(void);
extern void func_801D71A4(void);
extern void func_801D71E0(void);
extern void func_801D7234(void);
/* func_801D7350 */
extern void Battle_WriteBackParty(void);
extern void func_801D74D4(void);
extern void func_801DE698(void);
extern void func_801DE754(void);
extern void func_801DEFDC(void);
extern void func_801DF3B8(void);
extern void func_801DF3F8(void);
extern void func_801DF768(void);
extern void func_801DF7EC(void);
extern void func_801DFA1C(void);
extern void func_801DFA60(void);
extern void func_801DFB64(void);
extern void func_801DFBDC(void);
extern void func_801DFC70(void);
extern void func_801DFCB4(void);
extern void func_801E020C(void);
extern void func_801E04B0(void);
extern void func_801E0554(void);
extern void func_801E05EC(void);
extern void func_801E06EC(void);
extern void func_801E0744(void);
extern void func_801E0788(void);
extern void func_801E0F0C(void);
extern void func_801E1050(void);
extern void func_801E10C8(void);
extern void func_801E12DC(void);
extern void func_801E13B8(void);
extern void func_801E1494(void);
extern void func_801E15CC(void);
extern void func_801E16B4(void);
extern void func_801E1888(void);
extern void func_801E1938(void);
extern void func_801E1990(void);
extern void func_801E19DC(void);
extern void func_801E1A14(void);
extern void func_801E1ADC(void);
extern void func_801E1AE4(void);
extern void func_801E1B04(void);
extern void func_801E1B5C(void);
extern void func_801E1BA8(void);
extern void func_801E1C58(void);
extern void func_801E1C78(void);
extern void func_801E1D1C(void);
extern void func_801E1D88(void);
extern void func_801E1EC0(void);
extern void func_801E2024(void);
extern void func_801E2120(void);
extern void func_801E320C(void);
extern void func_801E32AC(void);
extern void func_801E32F0(void);
extern void func_801E3334(void);
extern void func_801E3398(void);
extern void func_801E3438(void);
extern void func_801E347C(void);
extern void func_801E352C(void);
extern void func_801E35D8(void);
extern void func_801E3638(void);
extern void func_801E383C(void);
extern void func_801E38C0(void);
extern void func_801E3980(void);
extern void func_801E3A00(void);
extern void func_801E3A44(void);
extern void func_801E3B04(void);
extern void func_801E3B68(void);
extern void func_801E3BAC(void);
extern void func_801E3BD0(void);
extern void func_801E3C14(void);
extern void func_801E4104(void);
extern void func_801E414C(void);
extern void func_801E44D4(void);
extern void func_801E4544(void);
extern void func_801E45DC(void);
extern void func_801E46EC(void);
extern void func_801E4760(void);
extern void func_801E47A4(void);
extern void func_801E483C(void);
extern void func_801E48D4(void);
extern void func_801E496C(void);
extern void func_801E4A50(void);
extern void func_801E4AE8(void);
extern void func_801E4B2C(void);
extern void func_801E4C7C(void);
extern void func_801E4D34(void);
extern void func_801E4D8C(void);
extern void func_801E4DD8(void);
extern void func_801E4E10(void);
extern void func_801E4ECC(void);
extern void func_801E4F64(void);
extern void func_801E4FA8(void);
extern void func_801E50C0(void);
extern void func_801E51DC(void);
extern void func_801E5288(void);
extern void func_801E52E8(void);
void        func_801E5768(void);
void        func_801E57C8(void);
extern void func_801E5AEC(void);
extern void func_801E5B8C(void);
extern void func_801E5C1C(void);
extern void func_801E5CA4(void);
extern void func_801E5E2C(void);
extern void func_801E6088(void);
extern void func_801E60DC(void);
extern void func_801E6154(void);
extern void func_801E61F0(void);
extern void func_801E63C0(void);
extern void func_801E6420(void);
extern void func_801E64B4(void);
extern void func_801E65F8(void);
extern void func_801E6724(void);
extern void func_801E6930(void);
extern void func_801E6990(void);
extern void func_801E69C0(void);
extern void func_801E6A54(void);
extern void func_801E6AA0(void);
extern void func_801E6B28(void);
extern void func_801E6BC8(void);
extern void func_801E6C20(void);
extern void func_801E6D28(void);
extern void func_801E6E54(void);
extern void func_801E6FA0(void);
extern void func_801E6FB0(void);
extern void func_801E71EC(void);
extern void func_801E7528(void);
extern void func_801E7558(void);
extern void func_801E75B0(void);
extern void func_801E7634(void);
extern void func_801E7778(void);
extern void func_801E7888(void);
extern void func_801E78F0(void);
extern void func_801E7948(void);
extern void func_801E8558(void);
extern void func_801E90FC(void);
extern void func_801E91FC(void);
extern void func_801E927C(void);
extern void func_801E9390(void);
extern void func_801E943C(void);
extern void func_801E94D0(void);
extern void func_801E9530(void);
extern void func_801E9538(void);
extern void func_801E960C(void);
extern void func_801E97A8(void);
extern void func_801E9910(void);
extern void func_801E99AC(void);
extern void func_801E9B18(void);
extern void func_801E9CA8(void);
extern void func_801E9F18(void);
extern void func_801E9FDC(void);
extern void func_801EA728(void);
extern void func_801EA76C(void);
extern void func_801EA774(void);
extern void func_801EA848(void);
extern void func_801EA894(void);
extern void func_801EA8F4(void);
extern void func_801EA9FC(void);
extern void func_801EAB64(void);
extern s32  D_801EABCC;
extern s32  D_801EB4BF;
/* g_BattlePanelOffsets + 1: func_801D3624 only, the sum changes its bytes */
extern s8   D_801EB0B1[];
extern u16  D_801EB4C8;
extern u16  D_801EB4CC;
extern s32  D_801EB4D0;
extern u32  D_801EB4D4;
extern s32  D_801EB6AF;
extern s32  D_801EBFA0;
extern void Battle_ReserveStagePanels(void);

/* Drain 0x2000 from the battle work counter; at zero set flags_00 bit 6 and
 * advance the spad step. */
static inline void BattleDrainWorkCounter(void) {
    PartyBattler* work;

    work = D_801EB4E0;
    if (work->unk_40 != 0) {
        work->unk_40 -= 0x2000;
    } else {
        work->flags_00 |= PARTY_BATTLER_FLAG_HANDLER_BUSY;
        g_SpadWork->step_01++;
    }
}

/* Advance the work coordinates and run the overlay tail update. */
static inline void BattleAdvanceCoords(u8 (*tail_update)(void)) {
    PartyBattler* work;
    u8            timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A - 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 0) {
        g_SpadWork->word_08.byte.timer_0A = 4;
        g_SpadWork->unk_03 += 1;
    }
    work = g_SpadWork;
    work->coord_x_34.raw += work->unk_0C;
    work->coord_y_38.raw += work->unk_10;
    tail_update();
}

/* Rotate one signed work pair according to the mode byte. */
static inline void BattleRotateWorkPair(PartyBattler* work, s32 offset_a, s32 offset_b) {
    s32 new_a;
    s32 new_b;
    s32 mode;

    mode = work->word_08.byte.unk_08;
    if (mode == 1) {
        goto mode_1; /* swap and negate: (a, b) -> (-b, a) */
    }
    if (mode < 2) {
        return;
    }
    if (mode == 2) {
        goto mode_2; /* negate both: (a, b) -> (-a, -b) */
    }
    if (mode == 3) {
        goto mode_3; /* swap and negate first: (a, b) -> (b, -a) */
    }
    return;

mode_1:
    new_a = -FIELD(s32, work, offset_b);
    new_b = FIELD(s32, work, offset_a);
    goto done; /* shared store of the new pair */

mode_2:
    new_a = -FIELD(s32, work, offset_a);
    new_b = -FIELD(s32, work, offset_b);
    goto done; /* shared store of the new pair */

done:
    FIELD(s32, work, offset_a) = new_a;
    FIELD(s32, work, offset_b) = new_b;
    return;

mode_3:
    {
        s32 old_a;
        s32 old_b;

        old_a                      = FIELD(s32, work, offset_a);
        old_b                      = FIELD(s32, work, offset_b);
        mode                       = old_a;
        FIELD(s32, work, offset_a) = old_b;
        FIELD(s32, work, offset_b) = -mode;
    }
}

/* Seed the battle mode tuple with five and the selected element. */
static inline void BattleSetEnding(u32 value) {
    s32 new_var3;
    u32 new_var2;
    s32 new_var;

    new_var3                      = 2;
    new_var                       = 0;
    BATTLE_ENDING_BYTES[new_var]  = 5u;
    new_var2                      = 1;
    BATTLE_ENDING_BYTES[new_var2] = value;
    BATTLE_ENDING_BYTES[new_var3] = 0u;
}

/* Draw the battle panel frame, its two glyphs and the horizontal rails. */
static inline void BattleDrawPanelFrame(s32 x, s32 y, s32 kind, s32 glyph0, s32 glyph1, s32 width) {
    u16 color;
    u8  r;
    u8  g;
    u8  b;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 0, 960, 0), 0);
    GFX_AddPrim(1, 0xC);
    /* FAKE: retail reads D_80144952 as s8. */
    color = *(u16*)(MEM_PTR(u8, 0x80033A08u) + (((*(s8*)&D_80144952) << 6) | 0x20));
    r     = PSX_COLOR_R(color) << 3;
    g     = PSX_COLOR_G(color) << 3;
    b     = PSX_COLOR_B(color) << 3;
    func_801D9C80((s16)x, (s16)(y + 2), kind, 1);
    func_801D9AB4((s16)x, (s16)y, glyph0, 1);
    func_801D9AB4((s16)x, (s16)(y + 0x11), glyph1, 1);
    func_801DA5A8((s16)(x + 2), (s16)(y + 2), (s16)(x + width), (s16)(y + 2), r, g, b);
    func_801DA5A8((s16)(x + 2), (s16)(y + 3), (s16)(x + 2), (s16)(y + 0x10), r, g, b);
    func_801DA4B4((s16)(x + width), (s16)(y + 2), (s16)(x + width), (s16)(y + 0x10), r, g, b);
    func_801DA4B4((s16)(x + 2), (s16)(y + 0x10), (s16)(x + width), (s16)(y + 0x10), r, g, b);
}
#endif
