#ifndef OVERLAY_PARTY_CHARACTER_H
#define OVERLAY_PARTY_CHARACTER_H

#include "types.h"
#include "game/character.h"

void Char_ApplyLevelUps(s32 char_id);
void Char_RebuildPartyStats(void);
/* func_80164A44 */
void Char_RebuildStats(Character* record);
/* func_80164D2C */
void Char_PreviewEquip(u8 character_id, u8 slot, u8 item_id, u8* flags, u16* values);
/* func_801651DC */
s32  Char_AbilityAdd(s32 ability_id, s32 character_index, s32 to_stock, s32 mode);
/* func_80165280 */
bool Char_HPRestore(s32 character_index, s32 amount, s32 use_battle_copy);
/* func_8016534C */
s32  Char_APRestore(s32 character_index, s32 amount, s32 use_battle_copy);
/* func_8016546C */
s32  Char_AddCappedStat(u16* value, s32 delta);
/* func_801654B0 */
s32  Char_AddWillpower(u8* value, u16 delta);
/* func_801654F4 */
s16  Char_AddStat(u16* value, s16 delta);
/* func_80165570 */
s16  Char_AddPoints(u16* value, u16 limit, s16 delta);
/* func_80165694 */
u32  Char_AddPercent(u8* value, u8 delta);
/* func_801656EC */
u32  Char_ClearStatus(u8 index, u16 mask, u8 mode);
/* func_801660DC */
s32  Char_AbilityGetElement(s32 ability_id);
/* func_80166A10 */
u8   Char_AbilityGetCost(u8 character_index, u8 ability_type, u8 mode);
/* func_80166B94 */
u8*  Char_GetAbilities(u8 character_index, u8 ability_id, u8 mode);
/* func_80167FDC */
void Char_HPAdd(s32 amount, u8 char_id);
/* func_8016813C */
u16  Char_HPLose(s32 amount, s32 character_id);
/* func_80168248 */
s32  Char_APSpend(s32 requested, s32 character_id);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_PARTY_CHARACTER_H_LOCAL)
#define OVERLAY_PARTY_CHARACTER_H_LOCAL

void Char_ApplyMaster(Character* character);
/* Retail calls this executable makes into its own units and the overlays. */
void Char_ApplyWeapon(Character* character);
void Char_ApplyArmor(Character* character);
void Char_ApplyAccessories(Character* character);
s32  Char_AddResistance(u8* counter, s32 delta);
/* func_801C38F4 */
s32  Char_CountEquipped(s32 character_index, s32 equip_group, s32 item_id);

#endif
