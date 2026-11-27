#ifndef OVERLAY_BATTLE_BATTLE_03_H
#define OVERLAY_BATTLE_BATTLE_03_H

/* The battle/battle/03 overlay's local declarations: the command, step and damage dispatch tables, its actor views and the prototypes its units share. The common records are in battle/records. */

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
/* The queued battle panel slots, and the size a drawn panel gets: its panel
 * width g_Battle.panel_widths plus this margin, or this margin alone for an empty panel. */
#define BATTLE_PANEL_SLOT_COUNT  5
#define BATTLE_PANEL_SIZE        0x10
/* Current enemy-work pointer cell (fixed RAM, not scratchpad). */
#define BATTLE_CURRENT_ENEMY_PTR (*(volatile EnemyBattler**)&g_BattleCurrentEnemy)
/* Panel-task root pointer cell at 0x801485C8 (u8* volatile). */
#define BATTLE_PANEL_ROOT_BASE   D_80150000
/* Base-pointer accessors for fixed RAM regions (preserve lui+offset codegen).
 */
/* FAKE: retail reads D_80140000 as volatile u16[]. */
#define BATTLE_GLOBAL_RAM_U16    ((volatile u16*)D_80140000)
/* Additional fixed-base tables and dispatch helpers. */
#define BATTLE_ENDING_BYTES      ((volatile u8*)&g_Battle.phase)
/* Single fixed-address globals (inline; no symbol binding required). */
#define BATTLE_GLOBAL_WORD_598C  (*(u32*)&g_GfxPrimCursor)
/* D_80033A08 as a fixed address: retail indexes the window colour words as a literal (addu at,index,at). */
#define BATTLE_GLOBAL_BYTES_3A08 MEM_PTR(u8, 0x80033A08u)
/* The same window color words read a halfword at a time: 32 per window style. */
#define BATTLE_WINDOW_COLORS     ((u16*)BATTLE_GLOBAL_BYTES_3A08)
/* Party slot the entrance pass is on, and the entrance sub-step byte 0x801462E2. */
#define BATTLE_PARTY_CURSOR      (((u8*)&D_80140000)[0x62E5])
#define BATTLE_ENTRANCE_STEP     (((u8*)&D_80140000)[0x62E2])

/* The fixed panel-task argument table preserves the caller's whole argument
 * block for the selected entry; no lifted caller names those seven words yet,
 * so they keep the panel-task spelling and the selector pointer it also
 * receives. No generic entry carries this contract. */
typedef void (*BattlePanelTaskCallback)(s32 panel_arg0, s32 panel_arg1, s32 panel_arg2, s32 panel_arg3, s32 panel_arg4, s32 panel_arg5, s32 panel_arg6, u8* selector);

/* The panel task's type byte (+0x02) selects one of these eight update
 * routines; Battle_UpdatePanel copies the table and dispatches. */
typedef struct {
    Callback modes[8];
} BattlePanelModes;

/* The queued slot's effect_type (+0x05) selects one of these eight handlers in slot
 * mode 3 (`g_BattleEffectModes` row 3); Battle_RunBossEffect copies the
 * table and dispatches. */
typedef struct {
    Callback steps[8];
} BattleBossEffectSteps;

/* The queued slot's effect_type (+0x05) selects one of these 110 handlers in slot
 * mode 1 (`g_BattleEffectModes` row 1); Battle_RunMagicEffect copies the
 * table and dispatches. */
typedef struct {
    Callback steps[110];
} BattleMagicEffectSteps;

/* The eight random damage percentages Battle_CalcDamage copies to the stack. */
typedef struct DamageSpread {
    u8 percent[8];
} DamageSpread;

/* The battle sub-step byte 0x801462E2 selects one of these four entrance
 * handlers, copied to the stack from 0x801D0C1C. */
typedef struct {
    Callback steps[4];
} BattleEntranceSteps;

/* The queued slot's mode (+0x06, stored by Battle_AllocEffect) selects one
 * of these four effect handlers, copied to the stack from 0x801D0CC0. */
typedef struct {
    Callback modes[4];
} BattleEffectModes;

/* Drop chance per EnemyDrop.rate, out of 256: 0, 0, 1, 3, 7, 31, 127, 255. */
typedef struct DropChances {
    u8 chance[8];
} DropChances;

/* The battle panel entries; BattlePanel is in battle/records.h. */
/* The battle mode byte 0x801462E0 selects one of these six handlers, copied to
 * the stack from 0x801D0C04. */
typedef struct {
    Callback modes[6];
} BattleModes;

/* Seven-byte palette table copied from the icon CLUT source at 0x801D0C64. */
typedef struct BattleIconPalette {
    u8 bytes[7];
} BattleIconPalette;

/* 8-byte panel frame record: origin of the frame drawn for one panel id. */
typedef struct BattlePanelFrame {
    s16 unk_00;
    u16 unk_02;
    u8  pad_04[4];
} BattlePanelFrame;

/* Ranked owner entries at 0x801EB550 (value at +0, battler index at +2). */
typedef struct BattleRank {
    s16 value;
    u16 index;
} BattleRank;

/* The queued slot's effect_type (+0x05) selects one of these 19 handlers in slot mode
 * 0 (`g_BattleEffectModes` row 0); Battle_RunBattlerEffect copies the table
 * and dispatches. */
typedef struct {
    Callback steps[19];
} BattleBattlerEffectSteps;

/* The form change effect's five step routines, at 0x801D0F6C. */
typedef struct {
    Callback modes[5];
} BattleFormChangeSteps;

/* The panel task forwarder func_801EA1E0 calls the routine its selector names
 * with the caller's seven words. */
typedef struct {
    BattlePanelTaskCallback steps[3];
} BattlePanelTaskSteps;

/* Overlay data and routines the sources use; names are the retail addresses. */
extern u8              D_1F800002;
extern u16*            D_800B4A64;
extern u16*            D_800B4A68;
extern u8              D_800B51F8[];
extern void*           D_800B6178[];
/* D_800B65F8 */
extern BattleSelection g_BattleSelections[];
/* D_80143F00 */
extern volatile u8     D_80145F18[];
extern u8              D_80145F20[];
extern u8              D_80145F22[];
/* One-field views of the same records: the party records (stride 0x140) and the
 * enemy records (stride 0x118), each anchored at the field the retail symbol
 * names. */
extern u8              D_80145FB1;
extern u8              D_80145FB2[];
/* FAKE: func_801D4B38 and Battle_GetActionLock only match with the flags cell as its own volatile word. */
extern volatile u32    D_80145FB8[][80];
extern u8              D_80145FC6;
extern u8              D_80145FC7;
extern u8              D_80145FC9;
extern u8              D_80145FCC[];
extern u8              D_801462F6[];
extern u8              D_80146308; /* UI oscillator byte */
extern u8              D_80146364[];
extern u16             D_80146388;
/* The active record's 0x118 result cells. */
extern volatile u16    D_801463B0;
extern volatile u8     D_801463BA;
extern u32             D_801463D0;
/* D_801463D8 */
extern s16             D_801463DA;
/* The units that must reload the cell after every store read it volatile. */
extern volatile u8     D_80146855;
extern volatile u8     D_80146856;
extern BattlePanel     D_80148332[];
/* UI state byte of the 0x8014837A bundle the entrance sequence writes; the
 * battle/battle/15 and etc/shop/00 targets declare their own. */
extern s32             D_80149298;
extern void            D_801492B8;
extern u8* volatile D_80150000[];
/* Non-const view: a const declaration moves the generated bytes of Battle_ReloadMusicBank. */
extern BGMTrack            g_BGMTracks[BGM_TRACK_COUNT];
extern u8*                 g_ItemCategoryIds[];
extern u8*                 g_ItemCategoryCounts[];
/* D_801D0C04 */
extern BattleModes         g_BattlePhases;
/* D_801D0C1C */
extern BattleEntranceSteps g_BattleEntrances;
/* g_BattleIconPalette */
extern BattleIconPalette   g_BattleIconPalette;
/* The overlay head keeps these in .data, so their definitions are non-const. */
extern char                D_801D0C6C[];
extern char                D_801D0C70[];
extern char                D_801D0C74[];
extern s8                  D_801D0C78[];
/* g_BattleDamageSpread */
extern DamageSpread        g_BattleDamageSpread;

/* D_801D0C84 */
#define BATTLE_EVENT_STEP_COUNT 5

typedef struct BattleEventSteps {
    Callback steps[BATTLE_EVENT_STEP_COUNT];
} BattleEventSteps;

#define BATTLE_DAMAGE_NUMBER_STEP_COUNT 5

typedef struct BattleDamageNumberSteps {
    Callback steps[BATTLE_DAMAGE_NUMBER_STEP_COUNT];
} BattleDamageNumberSteps;

#define BATTLE_SCREEN_FLASH_STEP_COUNT 3

typedef struct BattleScreenFlashSteps {
    Callback steps[BATTLE_SCREEN_FLASH_STEP_COUNT];
} BattleScreenFlashSteps;

#define BATTLE_SCREEN_FADE_STEP_COUNT 3

typedef struct BattleScreenFadeSteps {
    Callback steps[BATTLE_SCREEN_FADE_STEP_COUNT];
} BattleScreenFadeSteps;

#define BATTLE_EFFECT2_STEP_COUNT 3

typedef struct BattleEffect2Steps {
    Callback steps[BATTLE_EFFECT2_STEP_COUNT];
} BattleEffect2Steps;

#define BATTLE_AILMENT_ACTOR_STEP_COUNT 5

typedef struct BattleAilmentActorSteps {
    Callback steps[BATTLE_AILMENT_ACTOR_STEP_COUNT];
} BattleAilmentActorSteps;

#define BATTLE_EFFECT4_STEP_COUNT 5

typedef struct BattleEffect4Steps {
    Callback steps[BATTLE_EFFECT4_STEP_COUNT];
} BattleEffect4Steps;

#define BATTLE_PARTY_PANEL_STATE_COUNT 3

typedef struct BattlePartyPanelSteps {
    Callback steps[BATTLE_PARTY_PANEL_STATE_COUNT];
} BattlePartyPanelSteps;

#define BATTLE_MENU_ROWS_PANEL_STATE_COUNT 3

typedef struct BattleMenuRowsPanelSteps {
    Callback steps[BATTLE_MENU_ROWS_PANEL_STATE_COUNT];
} BattleMenuRowsPanelSteps;

#define BATTLE_PANEL2_STATE_COUNT 3

typedef struct BattlePanel2Steps {
    Callback steps[BATTLE_PANEL2_STATE_COUNT];
} BattlePanel2Steps;

#define BATTLE_PANEL3_STATE_COUNT 3

typedef struct BattlePanel3Steps {
    Callback steps[BATTLE_PANEL3_STATE_COUNT];
} BattlePanel3Steps;

#define BATTLE_MEMBER_PANEL_STATE_COUNT 3

typedef struct BattleMemberPanelSteps {
    Callback steps[BATTLE_MEMBER_PANEL_STATE_COUNT];
} BattleMemberPanelSteps;

#define BATTLE_EVENT_PANEL_STATE_COUNT 3

typedef struct BattleEventPanelSteps {
    Callback steps[BATTLE_EVENT_PANEL_STATE_COUNT];
} BattleEventPanelSteps;

#define BATTLE_MESSAGE_PANEL_STATE_COUNT 4

typedef struct BattleMessagePanelSteps {
    Callback steps[BATTLE_MESSAGE_PANEL_STATE_COUNT];
} BattleMessagePanelSteps;

extern BattleEventSteps         g_BattleEvents;
/* D_801D0C98 */
extern u8                       s_BattleSeIds[];
extern DropChances              g_BattleDropChances;
/* D_801D0CC0 */
extern BattleEffectModes        g_BattleEffectModes;
/* D_801D0CD0 */
extern BattleBattlerEffectSteps g_BattleBattlerEffectSteps;
/* D_801D0D1C */
extern BattleMagicEffectSteps   g_BattleMagicEffectSteps;
/* D_801D0ED4 */
extern BattleBossEffectSteps    g_BattleBossEffectSteps;
/* D_801D0EF4 */
extern BattleDamageNumberSteps  g_BattleDamageNumberSteps;
/* D_801D0F20 */
extern BattleScreenFlashSteps   g_BattleScreenFlashSteps;
/* D_801D0F2C */
extern BattleScreenFadeSteps    g_BattleScreenFadeSteps;
extern BattleEffect2Steps       D_801D0F38;
/* D_801D0F44 */
extern BattleAilmentActorSteps  g_BattleAilmentActorSteps;
extern BattleEffect4Steps       D_801D0F58;
/* D_801D0F6C */
extern BattleFormChangeSteps    g_BattleFormChangeSteps;
/* D_801D0F80 */
extern BattlePanelModes         g_BattlePanelModes;
/* D_801D0FA0 */
extern BattlePartyPanelSteps    g_BattlePartyPanelSteps;
/* D_801D0FAC */
extern BattleMenuRowsPanelSteps g_BattleMenuRowsPanelSteps;
extern BattlePanel2Steps        D_801D0FB8;
extern BattlePanel3Steps        D_801D0FC4;
/* The panel's four state handlers; Battle_UpdateEnemyPanel copies them to the stack
 * before the indexed call. */
/* D_801D0FD0 */
extern Callback                 g_BattleEnemyPanelSteps[4];
/* D_801D0FE0 */
extern BattleMemberPanelSteps   g_BattleMemberPanelSteps;
/* D_801D0FEC */
extern BattlePanelTaskSteps     g_BattlePanelTaskForwarders;
/* D_801D0FF8 */
extern BattleEventPanelSteps    g_BattleEventPanelSteps;
/* D_801D1004 */
extern BattleMessagePanelSteps  g_BattleMessagePanelSteps;
/* D_801EABB8 */
extern Callback                 g_BattleCommandSteps[];
extern u16                      D_801EABCC[];
/* D_801EABD8 */
extern Callback                 g_BattleCommandPanelSteps[];
/* D_801EABE4 */
extern Callback                 g_BattleRunCommandSteps[];
extern Callback                 D_801EAC04[];
extern Callback                 D_801EAC10[];
extern Callback                 D_801EAC24[];
extern Callback                 D_801EAC2C[];
extern Callback                 D_801EAC44[];
extern Callback                 D_801EAC4C[];
/* D_801EAC58 */
extern volatile u8              g_BattleRecallAbilities[];
/* D_801EAC78 */
extern volatile u8              g_BattleMagicShuffleAbilities[];
extern Callback                 D_801EAC98[];
extern Callback                 D_801EACA4[];
extern Callback                 D_801EACB0[];
extern Callback                 D_801EACBC[];
extern Callback                 D_801EACC8[];
extern Callback                 D_801EACD4[];
extern Callback                 D_801EACE8[];
extern Callback                 D_801EACF4[];
extern Callback                 D_801EAD00[];
extern Callback                 D_801EAD0C[];
extern Callback                 D_801EAD20[];
extern s16                      D_801EAD30[]; /* Eight signed vertex offsets per shape, 0x10 bytes a shape. */
extern u16                      D_801EAE50[];
extern u16                      D_801EAE52[];
/* D_801EAE94 */
extern u8                       s_BattlePanelOffsets[][2];
extern s8                       D_801EAEA4[]; /* panel x offsets: [0] for types 0 and 3, [2] otherwise */
extern volatile u32             D_801EAEB0[]; /* panel icon blit table */
extern BattlePanelFrame         D_801EAEE8[];
extern u8                       D_801EAF27[];
extern volatile u8              D_801EAF2C[];
extern volatile u8              D_801EAF2D[];
extern volatile u8              D_801EAF2E[];
extern volatile u8              D_801EAF2F[];
extern volatile s8              D_801EAF48[4][16]; /* the enemy turn-order agility roll per level rank */
/* D_801EAF94 */
extern u8                       s_BattleDamageBandDivisors[12]; /* nine damage divisor bytes, then three pad bytes */
extern s32                      D_801EAFA0[8];                  /* melee damage multipliers */
extern s16                      D_801EAFC0[8];                  /* offensive-holy multipliers */
extern u16                      D_801EAFD0[];                   /* Effect id triplets indexed by the local work's pending-effect halfword. */
/* D_801EAFF4 */
extern u8                       s_BattleStatusRecoveryPenalties[];
/* D_801EAFFC */
extern u8                       s_BattleStatusRecoveryChances[];
/* D_801EB000 */
extern u8                       s_BattleActionNames[12][13];
extern const u8                 D_801EB00D[];
extern s32                      D_801EB04E;
extern u8                       D_801EB05B[];
extern u8                       D_801EB068[];
extern u8                       D_801EB075[];
extern u8                       D_801EB082[];
extern volatile u16             D_801EB09C[][10]; /* Event-script records (10 halfwords each) in high RAM. */
/* D_801EB108 */
extern u8                       s_BattlePanelYOffsets[];
extern s32                      D_801EB08F;
/* g_BattlePanelOffsets + 1: func_801D3624 only, the sum changes its bytes */
extern s8                       D_801EB0B1[];
extern u8                       D_801EB109[];
extern Callback                 D_801EB120[];
extern void (*D_801EB154[])();
extern Callback         D_801EB15C[]; /* Local-state dispatch tables in high RAM. */
extern Callback         D_801EB188[];
/* D_801EB18C */
extern u8               s_BattleCharacterSprites[];
extern s32              D_801EB198;
/* D_801EB1B4 */
extern Callback         g_BattleTaskSteps[];
extern Callback         D_801EB1BC[];
extern Callback         D_801EB1D4[];
extern Callback         D_801EB1E0[];
extern Callback         D_801EB1F4[];
extern Callback         D_801EB210[];
extern Callback         D_801EB218[];
extern Callback         D_801EB224[];
/* D_801EB230 */
extern u8               g_BattleCharacterStepIds[0x28];
extern u8               D_801EB23C[];
extern Callback         D_801EB258[];
extern Callback         D_801EB26C[];
extern Callback         D_801EB274[];
extern Callback         D_801EB27C[];
extern Callback         D_801EB294[];
extern Callback         D_801EB298[];
extern u8               D_801EB35C[];
/* Party formation weights: one byte per slot in the formation, two slots per
 * formation in the first table and three in the second (Battle_PickFormationTarget). */
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
 * type and step (Battle_StartPoseActor). */
extern u8               D_801EB4A4[];
extern u8               D_801EB4B0[];
extern s32              D_801EB4BF;
extern u16              D_801EB4C8;
extern u16              D_801EB4CC;
extern s32              D_801EB4D0;
extern u32              D_801EB4D4;
extern BattleEventSlot* D_801EB4DC;
extern BattleRank       D_801EB550[];
/* D_801EBF20 */
extern PartyMember      s_BattleBattlerTemplates[BATTLE_PARTY_CHARACTERS_COUNT]; /* Alternate local work entries. */
extern u8               D_801EB6D0[];
extern u8               D_801EBF04;
extern s32              D_801EBFA0;
extern BattleEffect* volatile D_801EC2E0;
extern u8  D_801EC2E4;
/* kept: the overlays disagree on the sign of the defense word here, and func_801DFCB4's evasion update moves its code through the typed member. */
extern u16 D_801EC2EE;
extern u8  D_801EC303;

/* func_8009BBE8 */
/* func_8009BFC4 */
void               Battle_RunEnemyEvents(void);
void               func_8009D198(void);
u16                func_800A2AE0(u8 arg0);
/* func_800A31E0 */
void               Battle_AddStatus(u32 battler_index, u32 status_mask);
/* func_800A36F0 */
void               Battle_CureStatus(u32 battler_index, u32 status_mask);
u8                 func_800A3DF8(u32 battler_index, u32 selection_type);
s32                func_800A8F58(void);
s32                func_800AA368(void);
void               func_800AB910(void);
s32                func_800ABBA4(void);
void               func_800AC964(void);
void               func_800AD074(u8 bit_index);
s32                func_800AE108(u8 battler_index, s32 work_ptr);
/* func_800AE1F8 */
/* defined by the battle/battle/15 chain */
extern s32         D_80145FB4;
/* func_800AE260 */
void               func_800C1804(void);
void               func_800C1810(void);
void               func_800C181C(void);
void               func_800C18FC(void);
void               func_800C19B4(void);
void               func_800C19BC(void);
void               func_800C1A34(void);
void               func_800C1A54(void);
void               func_800C1AA8(void);
void               func_800C1B40(void);
void               func_800C1B6C(void);
void               func_800C1B84(void);
void               func_800C1BEC(void);
void               func_800C1C58(void);
void               func_800C1C98(void);
void               func_800C1CC4(void);
void               func_800C1CD8(void);
void               func_800C1D30(void);
void               func_800C1D54(void);
void               func_800C1D88(void);
void               func_800C1DB0(void);
void               func_800C1DC4(void);
void               func_800C1E2C(void);
void               func_800C1EA0(void);
void               func_800C1EB0(void);
void               func_800C26D4(void);
void               func_800C2FF4(void);
/* func_801D1014 */
void               Battle_Update(void);
/* func_801D112C */
void               Battle_DispatchMode(void);
/* func_801D11D8 */
void               Battle_DispatchStep(void);
/* func_801D1228 */
extern void        Battle_Reset(void);
/* func_801D17C4 */
void               Battle_DispatchEntrance(void);
extern void        Battle_OpenPanels(void);
/* func_801D1AB4 */
void               Battle_WaitForUI(void);
/* func_801D1AE8 */
void               Battle_InitPanels(void);
/* func_801D1B94 */
void               Battle_EnterIntro(void);
/* func_801D1C54 */
extern void        Battle_UpdateCommands(void);
/* func_801D1C90 */
extern void        Battle_StartCommands(void);
/* func_801D1D10 */
extern void        Battle_NextCommandMember(void);
/* func_801D1E8C */
extern void        Battle_ReadCommandMenu(void);
/* func_801D22AC */
extern void        Battle_UpdateCommandPanel(void);
/* func_801D22E8 */
extern void        Battle_ShrinkCommandPanel(void);
/* func_801D238C */
extern void        Battle_DrawEntrances(void);
/* func_801D2480 */
extern void        Battle_GrowCommandPanel(void);
/* func_801D24D4 */
extern void        Battle_RunCommand(void);
/* func_801D251C */
extern void        Battle_StartDefend(void);
/* func_801D25A0 */
extern void        Battle_ArmCommands(void);
/* func_801D2740 */
extern void        Battle_UpdateTurnSetup(void);
extern void        func_801D277C(void);
extern void        func_801D28E8(void);
extern void        func_801D2A24(void);
/* func_801D2AA8 */
extern void        Battle_UpdateTurns(void);
extern void        func_801D2B1C(void);
extern void        func_801D2B58(void);
extern void        func_801D2FC0(void);
extern void        func_801D3014(void);
extern void        func_801D3050(void);
extern void        func_801D3168(void);
extern void        func_801D31C0(void);
extern void        func_801D31FC(void);
extern void        func_801D3280(void);
extern void        func_801D32C8(void);
/* func_801D3304 */
extern void        Battle_SelectAbility(void);
extern void        func_801D3624(void);
/* func_801D3844 */
u8                 Battle_PickTarget(void);
extern void        func_801D39BC(void);
extern void        func_801D3A28(void);
extern void        func_801D3A64(void);
extern void        func_801D3BB4(void);
extern void        func_801D3C1C(void);
extern void        func_801D3C88(void);
extern void        func_801D3CC4(void);
extern void        func_801D3E80(void);
/* func_801D3F6C */
extern void        Battle_EndEffectLoad(void);
extern void        func_801D3FEC(void);
extern void        func_801D4028(void);
extern void        func_801D409C(void);
extern void        func_801D42B4(void);
extern void        func_801D43EC(void);
void               func_801D4850(void);
/* func_801D4AC0 */
extern void        Battle_UpdateRoundEnd(void);
extern void        func_801D4AFC(void);
extern void        func_801D4B38(void);
/* func_801D4D44 */
void               Battle_TickCountdowns(void);
extern void        func_801D5008(void);
extern void        func_801D5024(void);
u8                 func_801D54F8(void);
u8                 func_801D5658(void);
u8                 func_801D57AC(void);
u8                 func_801D590C(void);
u8                 func_801D5A60(void);
u8                 func_801D5BC0(void);
/* func_801D5DCC */
u8                 Battle_ApplyTurnDamage(void);
u8                 Battle_GetActionLock(u8 battler_index);
/* func_801D656C */
extern void        Battle_WaitVoiceSlots(void);
/* func_801D6774 */
extern void        Battle_UpdateResult(void);
extern void        func_801D67B0(void);
extern void        func_801D67EC(void);
extern void        func_801D6818(void);
/* func_801D6A14 */
extern void        Battle_LoadEndOverlay(void);
extern void        func_801D6C84(void);
extern void        func_801D6CC0(void);
extern void        func_801D6D90(void);
extern void        func_801D6DE4(void);
extern void        func_801D6E20(void);
extern void        func_801D6EAC(void);
extern void        func_801D6EEC(void);
extern void        Battle_ReloadPartySprites(void);
extern void        Battle_ReloadAreaAudio(void);
/* func_801D716C */
extern void        Battle_WaitAreaReload(void);
extern void        func_801D71A4(void);
extern void        Battle_ReloadFieldText(void);
extern void        Battle_ReloadMusicBank(void);
/* func_801D7350 */
extern void        Battle_WriteBackParty(void);
extern void        func_801D74D4(void);
void               Battle_DrawPartyPanel(s16 x, s16 y);
/* func_801D7A40 */
void               Battle_DrawPanels(s16 x, s16 y);
void               func_801D7D10(u8 clut_index, u16 x, u16 y, u16 width, u8 height, u8 shade);
void               func_801D7EB0(s32 x, s32 y);
void               func_801D8450(u32 panel_index);
/* func_801D8690 */
void               Battle_DrawEnemyPanel(s16 x, s16 y, s32 slot);
void               Battle_DrawEnemyNamePanel(s32 x, s32 y, s32 slot);
void               func_801D8DF8(s16 x, s16 y, u8 index);
/* func_801D9304 */
void               Battle_OpenPartyPanel(u8 index);
void               func_801D9388(u8 index);
void               func_801D93E4(u8 mode);
void               func_801D9428(u8 index);
void               func_801D94D4(s32 x, u32 y, s32 clut_index, s32 text_value);
/* func_801D9684 */
void               Battle_DrawNumber(s16 x, s16 y, u8 palette, u16 value);
void               func_801D9804(s32 x, s32 y, s32 clut_index, s32 glyph_index);
/* func_801D9900 */
void               Battle_DrawDimOverlay(void);
void               func_801D99AC(s16 x, s16 y, u8 template_index);
void               Battle_DrawPanelShape(s16 x, s16 y, s32 shape_index, s32 shade);
void               Battle_DrawWindowTile(s16 x, s16 y, u8 template_index, u8 shade);
bool               Battle_EndRound(void);
s32                Battle_StepBattlers(void);
void               func_801EA59C(u8* counter, s16* budget_max, u32 unused_a, u32 unused_b, s16* share, u8* budget, s16* step, u8* clear_flag);
void               func_801D9DBC(s16 x, s16 y, u8 template_index, u16 packed_color, u8 semi_trans);
void               func_801D9E9C(s32 x, s32 y, s32 width, s32 second_width, u8 second);
void               func_801DA078(s32 x, s32 y, s32 u_index);
/* func_801DA408 */
void               Battle_DrawLine(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b);
void               func_801DA4B4(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b);
void               Battle_DrawPanelLine(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b);
u8                 func_801DA69C(u32 enemy_index);
void               func_801DA7D4(void);
u8                 func_801DB058(void);
u8                 func_801DB2F8(u32 battler_index);
u8                 func_801DB3A0(u32 battler_index, u32 average_threshold, u32 max_threshold);
u8                 func_801DB3E4(u32 battler_index, u32 average_threshold, u32 max_threshold);
u32                func_801DB434(u8 compare_value, u32 side);
void               func_801DB494(void);
u8                 func_801DB844(u32 battler_index);
u8                 func_801DB9E4(u32 battler_index);
PartyMember*       func_801DBB20(u8 selector);
/* func_801DBB78 */
u32                Battle_ApplyDamage(u8 attacker_slot, u8 target_slot);
/* func_801DC73C */
u32                Battle_RollHitOnParty(s16 damage, u32 battler_index, u32 target_index);
/* func_801DC894 */
u32                Battle_RollHitOnEnemy(s16 damage, u8 attacker, u8 target);
u32                Battle_RollBaseDamage(u8 attacker_slot, u8 target_slot, u8 skip_reduction);
/* func_801DCCB0 */
u32                Battle_CalcPartyDefense(void);
/* func_801DCD50 */
u32                Battle_ScaleDamage(u32 unused, u8 battler_index, s32 damage_value);
void               func_801DCEF8(u32 battler_index);
void               func_801DD08C(void);
void               func_801DD29C(void);
void               func_801DD3CC(void* work);
u8                 func_801DD448(void);
extern u8          func_801DD704(u8 battler_index);
void               func_801DD800(void);
void               func_801DD8AC(u32 battler_index);
void               func_801DDAF0(void);
void               func_801DDB7C(void);
u8                 func_801DDCB4(u32 battler_index);
u8                 func_801DDE7C(u32 counter_index, u32 packed_value);
void               func_801DE1D4(void);
/* func_801DE43C */
void               Battle_UpdateEvents(void);
void               func_801DE60C(u32 slot, u8 event_type, u8 event_value, u8 group, u8 timer, u8* payload);
void               func_801DE690(void);
extern void        func_801DE698(void);
extern void        func_801DE754(void);
void               func_801DE7FC(void);
void               func_801DE804(void);
u8                 func_801DE858(s8 event_type);
/* func_801DE8C0 */
void               Battle_AddMessage(s8 index, s8 record_type, u8* text);
u8                 func_801DE92C(void);
void               Battle_SetTextPartyName(u32 party_slot);
void               Battle_SetTextEnemyName(u32 enemy_index);
/* func_801DEA64 */
void               Battle_ShowMessage(s32 message_slot);
void               func_801DEAE0(void);
void               func_801DEBC4(u32 script_index, u32 event_index);
/* func_801DECE0 */
void               Battle_UpdateParty(void);
/* func_801DED54 */
void               Battle_UpdatePartyActors(void);
u8                 func_801DEDE4(void);
u8                 Battle_IsPartyMemberBlocked(void);
u8                 Battle_IsEnemyBlocked(void);
u8                 Battle_IsEnemyBlockedOnce(void);
void               Battle_OpenPanel(void);
void               Battle_GetTurnCursor(u32 battler_index);
void               Battle_QueueEvent(u8 event_type, u8 event_value, u8 group, u8 timer, u8* payload);
void               func_801DEEB4(void);
void               func_801DEF0C(void);
extern void        func_801DEFDC(void);
void               func_801DEFE4(void);
void               func_801DF34C(void);
extern void        func_801DF3B8(void);
extern void        func_801DF3F8(void);
extern void        func_801DF768(void);
extern void        func_801DF7EC(void);
void               func_801DF8AC(void);
void               func_801DF914(void);
extern void        func_801DFA1C(void);
extern void        func_801DFA60(void);
extern void        func_801DFB64(void);
extern void        func_801DFBDC(void);
void               func_801DFC20(void);
extern void        func_801DFC70(void);
extern void        func_801DFCB4(void);
void               func_801E019C(void);
extern void        func_801E020C(void);
void               func_801E046C(void);
extern void        func_801E04B0(void);
extern void        func_801E0554(void);
extern void        func_801E05EC(void);
extern void        func_801E06EC(void);
extern void        func_801E0744(void);
extern void        func_801E0788(void);
void               func_801E0B64(void);
u8                 func_801E0E0C(void);
extern void        func_801E0F0C(void);
extern void        func_801E1050(void);
extern void        func_801E10C8(void);
void               func_801E1298(void);
extern void        func_801E12DC(void);
extern void        func_801E13B8(void);
void               func_801E1450(void);
extern void        func_801E1494(void);
extern void        func_801E15CC(void);
void               func_801E1670(void);
extern void        func_801E16B4(void);
extern void        func_801E1888(void);
extern void        func_801E1938(void);
extern void        func_801E1990(void);
extern void        func_801E19DC(void);
extern void        func_801E1A14(void);
extern void        func_801E1ADC(void);
extern void        func_801E1AE4(void);
extern void        func_801E1B04(void);
void               func_801E1B2C(void);
extern void        func_801E1B5C(void);
void               func_801E1B64(void);
extern void        func_801E1BA8(void);
extern void        func_801E1C58(void);
extern void        func_801E1C78(void);
void               func_801E1CD8(void);
extern void        func_801E1D1C(void);
extern void        func_801E1D88(void);
void               func_801E1DD4(void);
void               func_801E1E7C(void);
extern void        func_801E1EC0(void);
extern void        func_801E2024(void);
extern void        func_801E2120(void);
/* func_801E2170 */
void               Battle_UpdateEnemies(void);
/* func_801E2284 */
void               Battle_UpdateEnemyActors(void);
void               func_801E25E0(u8 battler);
void               func_801E2948(s8 enemy_index);
u8                 Battle_PickEnemyTarget(u8 enemy_index);
/* func_801E2CA4 */
u8                 Battle_PickLowestHpTarget(void);
/* bytes, caller passes a byte index, no sign extension */
u8                 func_801E2D4C(u8 slot_offset);
u8                 func_801E2D90(u8 slot_offset);
/* func_801E2E30 */
u8                 Battle_PickFormationTarget(void);
/* bytes, caller passes a byte index, no sign extension */
u8                 func_801E30B8(u8 slot_offset);
void               func_801E31C8(void);
extern void        func_801E320C(void);
extern void        func_801E32AC(void);
extern void        func_801E32F0(void);
extern void        func_801E3334(void);
extern void        func_801E3398(void);
extern void        func_801E3438(void);
extern void        func_801E347C(void);
extern void        func_801E352C(void);
extern void        func_801E383C(void);
extern void        func_801E38C0(void);
extern void        func_801E3A44(void);
extern void        func_801E3B04(void);
extern void        func_801E3C14(void);
extern void        func_801E4104(void);
extern void        func_801E414C(void);
u8                 func_801E4368(void);
extern void        func_801E44D4(void);
extern void        func_801E4544(void);
extern void        func_801E45DC(void);
extern void        func_801E46EC(void);
extern void        func_801E4760(void);
extern void        func_801E47A4(void);
void               func_801E47E0(void);
extern void        func_801E483C(void);
extern void        func_801E48D4(void);
void               func_801E4928(void);
extern void        func_801E496C(void);
extern void        func_801E4A50(void);
extern void        func_801E4B2C(void);
extern void        func_801E4C7C(void);
extern void        func_801E4D34(void);
extern void        func_801E4DD8(void);
extern void        func_801E4E10(void);
extern void        func_801E4ECC(void);
void               func_801E4F34(void);
extern void        func_801E4FA8(void);
extern void        func_801E50C0(void);
extern void        func_801E51DC(void);
/* func_801E531C */
void               Battle_RollEnemyDrops(void);
/* func_801E5768 */
void               Battle_RunDesertDefeat(void);
void               func_801E57C8(void);
/* func_801E5824 */
void               Battle_UpdateEffects(void);
extern void        func_801E5AEC(void);
/* Battle_RunBattlerEffect */
void               Battle_RunBattlerEffect(void);
/* Battle_RunMagicEffect */
extern void        Battle_RunMagicEffect(void);
/* Battle_RunBossEffect */
extern void        Battle_RunBossEffect(void);
/* func_801E5CA4 */
extern void        Battle_UpdateDamageNumber(void);
/* func_801E5E2C */
extern void        Battle_StartDamageNumber(void);
/* func_801E6088 */
extern void        Battle_HoldDamageNumber(void);
/* func_801E60DC */
extern void        Battle_RiseDamageNumber(void);
/* func_801E6154 */
extern void        Battle_BounceDamageNumber(void);
/* func_801E61F0 */
extern void        Battle_EndDamageNumber(void);
void               Battle_DrawRollingDigits(u8 palette);
/* func_801E63C0 */
extern void        Battle_UpdateScreenFlash(void);
/* func_801E6420 */
extern void        Battle_StartScreenFlash(void);
/* func_801E64B4 */
extern void        Battle_RaiseScreenFlash(void);
/* func_801E65F8 */
extern void        Battle_LowerScreenFlash(void);
/* Battle_UpdatePoseActor */
extern void        Battle_UpdatePoseActor(void);
/* Battle_StartPoseActor */
void               Battle_StartPoseActor(void);
/* Battle_PlayPoseActor */
void               Battle_PlayPoseActor(void);
/* func_801E6930 */
extern void        Battle_UpdateScreenFade(void);
/* func_801E6990 */
extern void        Battle_StartScreenFade(void);
/* func_801E69C0 */
extern void        Battle_RaiseScreenFade(void);
/* func_801E6A54 */
extern void        Battle_HoldScreenFade(void);
extern void        func_801E6AA0(void);
extern void        func_801E6B28(void);
extern void        func_801E6BC8(void);
extern void        func_801E6C20(void);
/* func_801E6C84 */
void               Battle_UpdateAilmentActor(void);
/* func_801E6D28 */
extern void        Battle_WaitAilment(void);
/* func_801E6E54 */
extern void        Battle_StartAilmentActor(void);
/* func_801E6FA0 */
extern void        Battle_RestartAilmentActor(void);
/* func_801E6FB0 */
extern void        Battle_RunAilmentActor(void);
/* func_801E71EC */
extern void        Battle_WaitAilmentEffect(void);
/* Battle_UpdateBattlerGhost */
void               Battle_UpdateBattlerGhost(void);
/* Battle_CopyBattlerGhost */
void               Battle_CopyBattlerGhost(void);
void               func_801E74B8(void);
extern void        func_801E7528(void);
extern void        func_801E7558(void);
extern void        func_801E75B0(void);
extern void        func_801E7634(void);
extern void        func_801E7778(void);
/* func_801E7818 */
void               Battle_UpdateFormChange(void);
/* func_801E7888 */
extern void        Battle_StartFormChange(void);
/* func_801E78F0 */
extern void        Battle_WaitFormChange(void);
/* func_801E7948 */
extern void        Battle_StartCharacterLoad(void);
u8                 func_801E7B34(void);
/* func_801E7BA0 */
void               Battle_RebuildFormBattler(void);
/* func_801E8558 */
extern void        Battle_EndFormChange(void);
/* func_801E862C */
void               Battle_UpdateFormRestore(void);
/* func_801E8684 */
extern void        Battle_StartFormRestore(void);
/* func_801E8D04 */
extern void        Battle_EndFormRestore(void);
void               func_801E8DD8(void);
u8                 func_801E8FA8(void);
/* func_801E9074 */
void               Battle_UpdatePanel(void);
/* func_801E90FC */
extern void        Battle_UpdatePartyPanel(void);
/* func_801E915C */
void               Battle_SlideInPartyPanel(void);
/* func_801E91CC */
void               Battle_HoldPartyPanel(void);
/* func_801E91FC */
extern void        Battle_UpdateMenuRowsPanel(void);
/* func_801E927C */
extern void        Battle_DrawMenuPanels(void);
/* func_801E9390 */
extern void        Battle_AnimatePanels(void);
extern void        func_801E943C(void);
void               func_801E949C(void);
extern void        func_801E94D0(void);
extern void        func_801E9530(void);
extern void        func_801E9538(void);
/* func_801E960C */
extern void        Battle_UpdateEnemyPanel(void);
/* func_801E97A8 */
extern void        Battle_StartEnemyPanel(void);
/* func_801E9910 */
extern void        Battle_ShowEnemyPanel(void);
/* func_801E99AC */
extern void        Battle_PlaceEnemyPanel(void);
/* func_801E9B18 */
extern void        Battle_UpdateMemberPanel(void);
/* func_801E9CA8 */
extern void        Battle_SetPanelGauges(void);
/* func_801E9F18 */
extern void        Battle_ShowMemberPanel(void);
/* func_801E9FDC */
extern void        Battle_MovePanel(void);
/* func_801EA174 */
void               Battle_LightPanel(void);
/* func_801EA1A4 */
void               Battle_DimPanel(void);
void               func_801EA1E0(s32 panel_arg0, s32 panel_arg1, s32 panel_arg2, s32 panel_arg3, s32 panel_arg4, s32 panel_arg5, s32 panel_arg6, u8* selector);
/* func_801EA650 */
void               Battle_UpdateEventPanel(void);
/* func_801EA728 */
extern void        Battle_SlideInEventPanel(void);
extern void        func_801EA76C(void);
/* func_801EA774 */
extern void        Battle_SlideOutEventPanel(void);
/* func_801EA7DC */
void               Battle_UpdateMessagePanel(void);
/* func_801EA848 */
extern void        Battle_WaitMessage(void);
/* func_801EA894 */
extern void        Battle_SlideInMessagePanel(void);
/* func_801EA8F4 */
extern void        Battle_HoldMessagePanel(void);
/* func_801EA9FC */
extern void        Battle_SlideOutMessagePanel(void);
/* func_801EAAB8 */
void               Battle_DrawMessagePanel(void);
/* func_801EAB38 */
u8                 Battle_AdvanceMessage(void);
extern void        func_801EAB64(void);
/* func_801EAB6C */
u8                 Battle_CountMessageChars(u8* message);
extern volatile u8 D_801F0000[];
/* The effect entry points this overlay calls by their fixed address. */
void               func_801EEEC8(void);

/* Drain 0x2000 from the battle work counter; at zero set flags bit 6 and
 * advance the spad step. */
static inline void BattleDrainWorkCounter(void) {
    PartyMember* work;

    work = g_BattleEffectBattler;
    if (work->scale.x != 0) {
        work->scale.x -= 0x2000;
    } else {
        work->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
        SELF(PartyMember)->header.mode++;
    }
}

/* Advance the work coordinates and run the overlay tail update. */
static inline void BattleAdvanceCoords(u8 (*tail_update)(void)) {
    PartyMember* work;
    u8           timer;

    timer                    = SELF(PartyMember)->timer - 1;
    SELF(PartyMember)->timer = timer;
    if (timer == 0) {
        SELF(PartyMember)->timer = 4;
        SELF(PartyMember)->unk_03 += 1;
    }
    work = SELF(PartyMember);
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    tail_update();
}

/* Rotate one signed work pair according to the mode byte. */
static inline void BattleRotateWorkPair(PartyMember* work, s32 offset_a, s32 offset_b) {
    s32 new_a;
    s32 new_b;
    s32 mode;

    mode = work->facing;
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
static inline void BattleDrawPanelFrame(s32 x, s32 y, s32 type, s32 glyph0, s32 glyph1, s32 width) {
    u16 color;
    u8  r;
    u8  g;
    u8  b;

    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
    /* FAKE: retail reads g_WindowStyle as s8. */
    color = *(u16*)(BATTLE_GLOBAL_BYTES_3A08 + (((*(s8*)&g_WindowStyle) << 6) | 0x20));
    r     = PSX_COLOR_R(color) << 3;
    g     = PSX_COLOR_G(color) << 3;
    b     = PSX_COLOR_B(color) << 3;
    Battle_DrawWindowTile((s16)x, (s16)(y + 2), type, 1);
    Battle_DrawPanelShape((s16)x, (s16)y, glyph0, 1);
    Battle_DrawPanelShape((s16)x, (s16)(y + 0x11), glyph1, 1);
    Battle_DrawPanelLine((s16)(x + 2), (s16)(y + 2), (s16)(x + width), (s16)(y + 2), r, g, b);
    Battle_DrawPanelLine((s16)(x + 2), (s16)(y + 3), (s16)(x + 2), (s16)(y + 0x10), r, g, b);
    func_801DA4B4((s16)(x + width), (s16)(y + 2), (s16)(x + width), (s16)(y + 0x10), r, g, b);
    func_801DA4B4((s16)(x + 2), (s16)(y + 0x10), (s16)(x + width), (s16)(y + 0x10), r, g, b);
}

#endif
