#ifndef BATTLE_FUNCTIONS_H
#define BATTLE_FUNCTIONS_H

#include "types.h"
#include "battle/records.h"

/* The battle overlays' functions that the battle, bmagic and boss images call, in address order. */

void        func_800975D4(void);
u8          func_80097EB8(void);
void        func_800989B4(void);
u8          func_8009AF7C(void);
void        func_800A4458(void);
/* func_800A581C */
void        Battle_StartAbilityPose(void);
u8          func_800A9304(u8 slot);
/* Stages the selection cell for the next battle step. */
/* func_800A9820 */
void        Battle_MarkDamaged(u8 selector);
/* func_800A9BD8 */
void        Battle_RescaleStats(u8 slot);
/* func_800AAA74 */
void        Battle_ApplyFormationStats(void);
/* func_800AAC88 */
void        Battle_QueueAction(s16 amount, u8 battler_index);
void        func_800AAEBC(s16 target_index, u8 battler_index);
/* func_801E29B4 */
/* func_800AC218 */
void        Battle_LoadEnemyBattler(u8 slot, u8 enemy_index);
s32         func_800AC704(s32 entry_id);
s32         func_800AEEC8(s32 arg0, u8 arg1);
void        func_800AEF98(s32 step, s32 payload);
void        func_800AF2B4(BattleRange* target, s32 step);
s32         func_800AF5FC(BattleRange* target, u32 extent);
u32         func_800AF66C(BattleRange* range, u32 extent);
/* func_800AF764 */
void        Battle_ProjectRange(void);
void        func_800AF814(u32 battler_index);
void        func_800AFC98(s32 effect_0, s32 effect_1);
/* func_800AFD9C */
void        Battle_CenterCamera(void);
u8          func_800AFF98(void);
u8          Battle_SlotIsBlocked(u32 slot);
void        func_801DD350(void* work);
s32         func_801DD59C(s32 amount);
u8          func_801DD7AC(s32 selector);
void        func_801E257C(u32 enemy_index, u32 script_index);
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
/* The element argument that takes the attacker's weapon element. */
#define BATTLE_ELEMENT_FROM_WEAPON 0xFFFF

/* One hit's damage, defined by the battle/battle/03 overlay at this address. */
/* func_801DC044 */
s16         Battle_CalcDamage(u8 attacker, u8 target, u16 element);
void        func_801DD14C(u8 battler_index);
void        func_801DD858(u32 effect_index);
void        func_801DDAB4(u32 status);
u8          func_801DDF50(u16 entry_id, u32 table_kind);
void        func_801DDFEC(u32 battler_index);
s16         func_801DE0AC(s32 factor_a, s32 factor_b);
void        Battle_SetSlotPending(u32 slot);
void        func_801DE560(u8 event_kind, u8 event_value, u8 group, u8 timer, u8* payload);
/* func_801E52F0 */
void        Battle_PlayEnemyCue(u16 cue_id);
/* func_801E590C */
u32         Battle_AllocEffect(u32 mode, u32 handler_index);
void        func_801E5988(void);
extern void func_801E5A38(void);

#endif
