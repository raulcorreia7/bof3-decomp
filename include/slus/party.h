#ifndef SLUS_PARTY_H
#define SLUS_PARTY_H

#include "types.h"
#include "game/character.h"
#include "game/item.h"

/* The executable's character, item and party functions, in address order. */
/* func_8015C100 */
extern void Party_HideBattlers(void);
/* func_80164A44 */
void        Char_RebuildStats(Character* record);
/* func_80164D2C */
void        Char_PreviewEquip(u8 character_id, u8 slot, u8 item_id, u8* flags, u16* values);
/* func_801650B4 */
bool        Item_Add(s32 category, u8 item_id, u8 count, s32 unused);
/* func_801651DC */
s32         Char_AddAbility(s32 ability_id, s32 character_index, s32 to_stock, s32 mode);
/* func_80165280 */
bool        Char_RestoreHP(s32 character_index, s32 amount, s32 use_battle_copy);
/* func_8016534C */
s32         Char_RestoreAP(s32 character_index, s32 amount, s32 use_battle_copy);
/* func_8016546C */
s32         Char_AddCappedStat(u16* value, s32 delta);
/* func_801654B0 */
s32         Char_AddWillpower(u8* value, u16 delta);
/* func_801654F4 */
s16         Char_AddStat(u16* value, s16 delta);
/* func_80165570 */
s16         Char_AddPoints(u16* value, u16 limit, s16 delta);
/* func_80165694 */
u32         Char_AddPercent(u8* value, u8 delta);
/* func_801656EC */
u32         Char_ClearStatus(u8 index, u16 mask, u8 mode);
/* func_80165D48 */
u8*         Item_GetRecord(s32 category, s32 item);
/* func_80165E04 */
s32         Item_GetIcon(ItemCategory category, s32 item_id);
/* func_80165EC0 */
u8          Item_GetEquipability(u8 category, u8 item);
/* func_80165F68 */
u32         Item_GetFlags(u32 category, u32 item);
/* func_801660DC */
s32         Char_GetAbilityElement(s32 ability_id);
/* func_80166140 */
bool        Item_VitalHas(s32 item_id);
/* func_80166180 */
s32         Item_VitalAdd(u8 item_id);
/* func_8016628C */
s32         Item_Count(u8 category, u8 item_id, u8 mode);
/* func_80166438 */
u8          Item_CountHeld(u32 category);
/* func_801664A0 */
u8          Party_CountAbilities(u8 character_index, u8 ability_type, u8 mode);
/* func_801665A0 */
u8          Item_Remove(s32 category, u8 item_id, s32 count, s32 unused);
/* func_8016663C */
bool        Party_SpendZenny(u32 amount, s32 unused);
/* func_8016666C */
s32         Party_AddZenny(s32 amount, s32 skip_earned);
/* func_801666C8 */
s32         Item_GetDescription(s32 category, s32 item_id);
/* func_80166A10 */
u8          Char_GetAbilityCost(u8 character_index, u8 ability_type, u8 mode);
/* func_80166AE4: type table for (source slot, group, table type) */
u8*         Party_GetAbilities(u32 formation_index, u32 ability_type, u32 mode);
/* func_80166B94 */
u8*         Char_GetAbilities(u8 character_index, u8 ability_id, u8 mode);
/* func_80166CEC */
void        Party_ClearBattlerState(s32 character_index);
/* func_80167FDC */
void        Char_AddHP(s32 amount, u8 char_id);
/* func_8016813C */
u16         Char_LoseHP(s32 amount, s32 character_id);
/* func_80168248 */
s32         Char_SpendAP(s32 requested, s32 character_id);

#endif
