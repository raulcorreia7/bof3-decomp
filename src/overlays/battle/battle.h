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
    EMIModuleId id; /* 0x00; 0x142 BATL_END, 0x143 BATL_OVR */
} BattleModule;

ASSERT_SIZE(BattleModule, 4);

/* Camera scroll step per direction: func_8009B488, func_8009B700, func_8009B794
 * and func_800A8678 add one entry to the x/y phase scroll words, indexed by
 * g_BattleScrollDir. */
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
/* D_801462E4 */
extern volatile u8                  g_BattleUIState;
/* D_801462E6 */
extern volatile u8                  g_BattlePanelEntry;
/* D_801462EC */
extern volatile u8                  g_BattleScrollDir;
/* D_801462F3 */
extern u8                           g_BattleLivingEnemyCount;
/* D_80146322 */
extern volatile u8                  g_BattleTurnCursor;
/* D_80146323 */
extern volatile u8                  g_BattleTurnCount;
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
#endif
