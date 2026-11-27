#ifndef BATTLE_FAMILY_H
#define BATTLE_FAMILY_H

#include "game.h"
#include "sys/cd.h"
#include "sys/actor.h"
#include "menu/panel.h"
#include "scenario/effect.h"
#include "sys/exe.h"
#include "battle/functions.h"

/* Reloads g_UIPanelCurrent on every use, like the panel functions do. */
#define BATTLE_PANEL_TASK ((BattlePanelTask*)g_UIPanelCurrent)

/* The battle system as the two battle overlays implement it. A battle keeps a
 * 0x140-byte work record per party member and a 0x118-byte enemy record
 * (PartyMember, EnemyBattler in records.h); both carry the action block,
 * the HP/AP change cells and the status word the result screens read.
 *
 * Turn order is a ranking pass: func_801DAAE4 scores each active battler from
 * its agility, its action mode and the level-priority multiplier table at
 * 0x801EAF3C (enemy scores also add a random value), then sorts the
 * BattleRank rows at 0x801EB550 high to low. Each battler runs its step
 * handler from D_801EB120 (party) or its record's handler (enemy); actions are
 * queued in the 48 slots at 0x801EC330 and dispatched by Battle_UpdateEffects
 * (0x801E5824) through the handler table at 0x801D0CC0.
 *
 * One hit is Battle_CalcDamage (0x801DC044): the attacker's element or the
 * weapon's, weapon-vs-enemy-type doubling, status reactions, the eight random
 * percentages at 0x801D0C7C and a +/-9999 clamp. Battle_ApplyDamage (0x801DBB78)
 * stores the result and the HP/AP change.
 *
 * Readers: emi/battle/battle/03 and emi/battle/battle/15; the game overlay fills
 * the candidate table at 0x801463DC before a wild encounter. Evidence:
 * @source: wiki:data/battle#where-the-records-are. */

/* Camera scroll step per direction: func_8009B488, func_8009B700, func_8009B794
 * and func_800A8678 add one entry to the x/y phase scroll words, indexed by
 * g_Battle.scroll_dir. */
typedef Step2 BattleScrollDelta;

ASSERT_SIZE(BattleScrollDelta, 0x02);

extern BattleScrollDelta g_BattleScrollDeltas[4];
/* D_800B6510 */
extern u8                g_BattleActionSelection[232];
extern u8*               D_800B6AB0[];
/* One-field views of the same records: the party records (stride 0x140) and the
 * enemy records (stride 0x118), each anchored at the field the retail symbol
 * names. */
extern u8                D_801454F5[];
extern u8                D_801454F6[];
extern u8                D_80145FA8[];

/* One 8-byte message of the 16-message ring at g_BattleMessages; D_801EC328 is the next message to fill. */
typedef struct BattleMessageSlot {
    u8  flags;       /* 0x00 bit 0 waits for a button, bit 1 counts record_type down */
    u8  record_type; /* 0x01 the record type, or the wait countdown while bit 1 of flags is set */
    u8  pad_02[2];   /* 0x02 */
    u8* text;        /* 0x04 the message text */
} BattleMessageSlot;

ASSERT_OFFSET(BattleMessageSlot, flags, 0x00);
ASSERT_OFFSET(BattleMessageSlot, record_type, 0x01);
ASSERT_OFFSET(BattleMessageSlot, text, 0x04);
ASSERT_SIZE(BattleMessageSlot, 0x08);

extern BattleMessageSlot g_BattleMessages[16];

/* One 0xC-byte record of the event slot table at g_BattleEventSlots; D_801EB4DC points at the running event. */
typedef struct BattleEventSlot {
    u8  active;     /* 0x00 set while the event runs */
    u8  event_type; /* 0x01 indexes g_BattleEvents.steps and its flag bit */
    u8  value;      /* 0x02 the event's value byte */
    u8  group;      /* 0x03 event pass: group 0 before group 1 */
    u8* payload;    /* 0x04 the event's data pointer */
    u16 timer;      /* 0x08 counts down; 0xFF means no countdown */
    u8  text_style; /* 0x0A text style argument UI_TextDraw draws the payload with */
    u8  pad_0B;     /* 0x0B */
} BattleEventSlot;

ASSERT_OFFSET(BattleEventSlot, active, 0x00);
ASSERT_OFFSET(BattleEventSlot, event_type, 0x01);
ASSERT_OFFSET(BattleEventSlot, value, 0x02);
ASSERT_OFFSET(BattleEventSlot, group, 0x03);
ASSERT_OFFSET(BattleEventSlot, payload, 0x04);
ASSERT_OFFSET(BattleEventSlot, timer, 0x08);
ASSERT_OFFSET(BattleEventSlot, text_style, 0x0A);
ASSERT_SIZE(BattleEventSlot, 0xC);

/* FAKE: g_Battle.ui_mode as a global of its own; the sites that use it match only with a separate symbol. */
extern volatile u8                  g_BattleUIState;
/* Main-executable battle-selection cell consumed by the countdown arm. */
extern u8                           g_BattleActionType_nv;
extern u8                           D_801463B8[];
extern volatile BattleSelectionType D_801CA71C[];
/* D_801EB0B0 */
extern s8                           g_BattlePanelOffsets[];
extern BattleTurn*                  g_BattleActorTurn;
extern BattleEventSlot              g_BattleEventSlots[8];
/* A byte view of g_BattleEventSlots: func_801DE60C reaches every field by byte offset. */
extern u8                           g_BattleEventSlotBytes[];
extern u8                           D_801EB5A8;
/* D_801EBF08 */
extern u8*                          g_BattleMessageSlot;
extern u8                           D_801EC328;
/* Queued-slot records at g_BattleEffects (stride 0x78). */
#define BATTLE_EFFECT_COUNT 48

extern PanelOwner D_801ED9B0[];
/* Prototypes the images of this group share. */
/* func_80096A74 */
void              Battle_RunAttackCommand(void);
/* func_80096F00 */
void              Battle_RunAbilityCommand(void);
void              Battle_RunExamineCommand(void);
/* func_8009834C */
void              Battle_RunItemCommand(void);
/* func_8009B274 */
void              Battle_RunEscapeCommand(void);
void              Battle_TriggerEnemyEvents(void);
void              func_800A4688(void);
void              func_800A8540(void);
void              func_800A8C60(void);
void              func_800A8D80(void);
u8                func_800A94A8(void);
u8                func_800A955C(void);
s32               func_800A99AC(void);
s32               func_800A9A84(void);
s32               func_800A9B44(void);
s32               func_800AA8FC(void);
void              func_800AB834(void);
void              func_800AD69C(void);
void              func_800AD9CC(void);
void              func_800ADCC4(void);
void              func_800ADFBC(void);
void              Battle_LoadSelectionEffect(s32);
void              Battle_AllocActionEffect(u16, u32);
void              func_800AE2D4(u32);
void              func_800AE34C(void);
void              func_800AE4D0(void);
void              func_800AE788(void);
void              func_800C1814(void);
void              func_800C1820(void);
void              func_800C1838(void);
void              func_800C184C(void);
void              func_800C1850(void);
void              func_800C1860(void);
void              func_800C1864(void);
void              func_800C18F0(void);
void              func_800C190C(void);
void              func_800C193C(void);
void              func_800C1950(void);
void              func_800C19E4(void);
void              func_800C19E8(void);
u8                Battle_TargetPrev(u8);
void              Battle_SetTextActionName(u32, s8);

#endif
