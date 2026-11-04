#ifndef BATTLE_FAMILY_H
#define BATTLE_FAMILY_H

/* Declarations shared by two or more battle images; an image header that
 * reads one includes this file. */

#include "game.h"
#include "sys/cd.h"
#include "work/actor.h"
#include "menu/panel.h"
#include "scenario/effect.h"
#include "sys/exe.h"

/* Reloads g_MenuPanelTaskCurrent on every use, like the panel functions do. */
#define BATTLE_PANEL_TASK ((BattlePanelTask*)g_MenuPanelTaskCurrent)

/* The battle system as the two battle overlays implement it. A battle keeps a
 * 0x140-byte local work row per party member and a 0x118-byte enemy row
 * (PartyBattler, EnemyBattler in records.h); both carry the action block,
 * the HP/AP change cells and the status word the result screens read.
 *
 * Turn order is a ranking pass: func_801DAAE4 scores each active battler from
 * its agility, its action mode and the level-priority multiplier table at
 * 0x801EAF3C (enemy scores also add a random value), then sorts the
 * BattleRank rows at 0x801EB550 high to low. Each battler runs its step
 * handler from D_801EB120 (party) or its row's handler (enemy); actions are
 * queued in the 48 slots at 0x801EC330 and dispatched by Battle_RunEffects
 * (0x801E5824) through the handler table at 0x801D0CC0.
 *
 * One hit is Battle_CalcDamage (0x801DC044): the attacker's element or the
 * weapon's, weapon-vs-enemy-kind doubling, status reactions, the eight random
 * percentages at 0x801D0C7C and a +/-9999 clamp. Battle_ApplyDamage (0x801DBB78)
 * stores the result and the HP/AP change.
 *
 * Readers: emi/battle/battle/03 and emi/battle/battle/15; the game overlay fills
 * the candidate table at 0x801463DC before a wild encounter. Evidence:
 * @source: wiki:data/battle#where-the-records-are. */

/* A battle-effect module's head: the two battle modules BATL_END and BATL_OVR
 * carry the id alone. */
typedef struct BattleModule {
    EmiModuleId id; /* 0x00; 0x142 BATL_END, 0x143 BATL_OVR */
} BattleModule;

ASSERT_SIZE(BattleModule, 4);

/* Camera scroll step per direction: func_8009B488, func_8009B700, func_8009B794
 * and func_800A8678 add one entry to the x/y phase scroll words, indexed by
 * g_BattleScrollDir. */
typedef struct BattleScrollDelta {
    s8 x;
    s8 y;
} BattleScrollDelta;

extern BattleScrollDelta            D_800B44C0[4];
extern u8                           D_800B6510[232];
extern u8*                          D_800B6AB0[];
/* One-field views of the same rows: the local rows (stride 0x140) and the
 * enemy rows (stride 0x118), each anchored at the field the retail symbol
 * names. */
extern u8                           D_801454F5[];
extern u8                           D_801454F6[];
extern u8                           D_80145FA8[];
extern u8                           D_80145FCC[];
/* D_801462E4 */
extern volatile u8                  g_BattleUiState;
/* D_801462E6 */
extern volatile u8                  g_BattlePanelEntry;
/* D_801462EC */
extern volatile u8                  g_BattleScrollDir;
extern u8                           D_801462F3;
extern volatile u8                  D_80146322;
extern volatile u8                  D_80146323;
/* Main-executable battle-selection cell consumed by the countdown arm. */
extern u8                           g_BattleActionType_nv;
extern u8                           D_801463B8[];
extern u8                           D_801463CB;
extern volatile BattleSelectionType D_801CA71C[];
/* D_801EB0B0 */
extern s8                           g_BattlePanelOffsets[];
extern u8*                          D_801EB4D8;
extern u8                           g_BattleEventSlots[];
extern u8                           D_801EB5A8;
extern u8                           D_801EB5B1[];
extern u8*                          D_801EB5B4[];
/* Enemy battler work record (stride 0x118 at D_801EB630, indexed by slot - 3). */
extern EnemyBattler                 D_801EB630[];
extern u8                           D_801EB631[];
extern u8                           D_801EB710[];
extern volatile u16                 D_801EB726[][140];
extern u8                           D_801EB72C[];
/* D_801EBF08 */
extern u8*                          g_BattleMessageSlot;
extern u8                           D_801EC324;
extern u8                           D_801EC328;
/* Queued-slot records at g_BattleEffects (stride 0x78). */
#define BATTLE_EFFECT_COUNT 48
extern BattleEffect                 g_BattleEffects[];
extern u8                           D_801EC339[];
extern u8                           D_801EC3A4[];
extern PanelOwner                   D_801ED9B0[];

void        func_800975D4(void);
u8          func_80097EB8(void);
void        func_800989B4(void);
u8          func_8009AF7C(void);
void        func_800A4458(void);
void        func_800A581C(void);
u8          func_800A9304(u8 slot);
/* Stages the selection cell for the next battle step. */
void        func_800A9820(u8 selector);
void        func_800A9BD8(u8 slot);
void        func_800AAA74(void);
void        func_800AAC88(s16 amount, u8 battler_index);
void        func_800AAEBC(s16 target_index, u8 battler_index);
/* func_801E29B4 */
u8          Battle_PickRandomTarget(u8 excluded_slot);
extern void func_800ACF80(void);
void        func_800AD26C(void);
void        func_800AE014(void);
void        func_800B2218(void);
void        func_800B22AC(void);
void        func_800B23B8(void);
void        func_800B23F8(void);
/* func_80166A10 */
u8          Char_GetAbilityCost(u8 character_index, u8 ability_kind, u8 mode);
extern void func_801D8270(s32 x, s32 y);
void        func_801D9484(void);
void        func_801DAAE4(void);
/* One hit's damage, defined by the battle/battle/03 overlay at this address. */
/* func_801DC044 */
s16         Battle_CalcDamage(u8 attacker, u8 target, u16 element);
void        func_801DD14C(u8 battler_index);
void        func_801DD858(u32 effect_index);
void        func_801DDAB4(u32 arg0);
void        func_801DDFEC(u32 battler_index);
s16         func_801DE0AC(s32 factor_a, s32 factor_b);
void        Battle_SetSlotPending(u32 slot);
void        func_801DE560(u8 event_kind, u8 arg1, u8 arg2, u8 arg3, u8* payload);
void        func_801E52F0(u16 effect_id);
/* func_801E590C */
u32         Battle_AllocEffect(u32 mode, u32 handler_index);
void        func_801E5988(void);
extern void func_801E5A38(void);

extern u8 D_80145FC8;
#endif
