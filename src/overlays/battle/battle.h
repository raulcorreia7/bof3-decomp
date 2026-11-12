#ifndef BATTLE_FAMILY_H
#define BATTLE_FAMILY_H

#include "game.h"
#include "sys/cd.h"
#include "sys/actor.h"
#include "menu/panel.h"
#include "scenario/effect.h"
#include "sys/exe.h"
#include "battle/functions.h"

/* Reloads g_MenuCurrentPanel on every use, like the panel functions do. */
#define BATTLE_PANEL_TASK ((BattlePanelTask*)g_MenuCurrentPanel)

/* The battle system as the two battle overlays implement it. A battle keeps a
 * 0x140-byte local work row per party member and a 0x118-byte enemy row
 * (PartyMember, EnemyBattler in records.h); both carry the action block,
 * the HP/AP change cells and the status word the result screens read.
 *
 * Turn order is a ranking pass: func_801DAAE4 scores each active battler from
 * its agility, its action mode and the level-priority multiplier table at
 * 0x801EAF3C (enemy scores also add a random value), then sorts the
 * BattleRank rows at 0x801EB550 high to low. Each battler runs its step
 * handler from D_801EB120 (party) or its row's handler (enemy); actions are
 * queued in the 48 slots at 0x801EC330 and dispatched by Battle_UpdateEffects
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
    EMIModuleId id; /* 0x00; 0x142 BATL_END, 0x143 BATL_OVR */
} BattleModule;

ASSERT_SIZE(BattleModule, 4);

/* Camera scroll step per direction: func_8009B488, func_8009B700, func_8009B794
 * and func_800A8678 add one entry to the x/y phase scroll words, indexed by
 * g_Battle.scroll_dir. */
typedef struct BattleScrollDelta {
    s8 x;
    s8 y;
} BattleScrollDelta;

ASSERT_SIZE(BattleScrollDelta, 0x02);

extern BattleScrollDelta            D_800B44C0[4];
/* D_800B6510 */
extern u8                           g_BattleActionSelection[232];
extern u8*                          D_800B6AB0[];
/* One-field views of the same rows: the local rows (stride 0x140) and the
 * enemy rows (stride 0x118), each anchored at the field the retail symbol
 * names. */
extern u8                           D_801454F5[];
extern u8                           D_801454F6[];
extern u8                           D_80145FA8[];
/* FAKE: g_Battle.ui_state as a global of its own; the sites that use it match only with a separate symbol. */
extern volatile u8                  g_BattleUIState;
/* Main-executable battle-selection cell consumed by the countdown arm. */
extern u8                           g_BattleActionType_nv;
extern u8                           D_801463B8[];
extern u8                           D_801463CB;
extern volatile BattleSelectionType D_801CA71C[];
/* D_801EB0B0 */
extern s8                           g_BattlePanelOffsets[];
extern BattleTurn*                  g_BattleActorTurn;
extern u8                           g_BattleEventSlots[];
extern u8                           D_801EB5A8;
extern u8                           D_801EB5B1[];
extern u8*                          D_801EB5B4[];
/* D_801EBF08 */
extern u8*                          g_BattleMessageSlot;
extern u8                           D_801EC324;
extern u8                           D_801EC328;
/* Queued-slot records at g_BattleEffects (stride 0x78). */
#define BATTLE_EFFECT_COUNT 48
extern u8           D_80145FC8;
extern BattleEffect g_BattleEffects[];

extern PanelOwner D_801ED9B0[];
/* Prototypes the images of this group share. */
void              func_80096A74();
void              func_80096F00();
void              func_800980A8();
void              func_8009834C();
void              func_8009B274();
void              Battle_TriggerEnemyEvents();
void              func_800A4688();
void              func_800A8540();
void              func_800A8C60();
void              func_800A8D80();
u8                func_800A94A8();
u8                func_800A955C();
s32               func_800A99AC();
s32               func_800A9A84();
s32               func_800A9B44();
s32               func_800AA8FC();
void              func_800AB834();
void              func_800AD69C();
void              func_800AD9CC();
void              func_800ADCC4();
void              func_800ADFBC();
void              Battle_LoadSelectionEffect(s32);
void              Battle_AllocActionEffect(u16, u32);
void              func_800AE2D4(u32);
void              func_800AE34C();
void              func_800AE4D0();
void              func_800AE788();
void              func_800C1814();
void              func_800C1820();
void              func_800C1838();
void              func_800C184C();
void              func_800C1850();
void              func_800C1860();
void              func_800C1864();
void              func_800C18F0();
void              func_800C190C();
void              func_800C193C();
void              func_800C1950();
void              func_800C19E4();
void              func_800C19E8();
u8                Battle_TargetPrev(u8);
void              Battle_SetTextActionName(u32, s8);

#endif
