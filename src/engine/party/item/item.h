#ifndef OVERLAY_PARTY_ITEM_H
#define OVERLAY_PARTY_ITEM_H

#include "types.h"
#include "game/item.h"

bool Item_PassesTest(u8 test, u8 character_id, u8 category, u8 item_id);
/* func_801650B4 */
bool Item_Add(s32 category, u8 item_id, u8 count, s32 unused);
/* func_80165D48 */
u8*  Item_GetRecord(s32 category, s32 item);
/* func_80165E04 */
s32  Item_GetIcon(ItemCategory category, s32 item_id);
/* func_80165EC0 */
u8   Item_GetEquipability(u8 category, u8 item);
/* func_80165F68 */
u32  Item_GetFlags(u32 category, u32 item);
/* func_80166140 */
bool Item_VitalHas(s32 item_id);
/* func_80166180 */
s32  Item_VitalAdd(u8 item_id);
/* func_8016628C */
s32  Item_Count(u8 category, u8 item_id, u8 mode);
/* func_80166438 */
u8   Item_CountHeld(u32 category);
/* func_801665A0 */
u8   Item_Remove(s32 category, u8 item_id, s32 count, s32 unused);
/* func_801666C8 */
s32  Item_GetDescription(s32 category, s32 item_id);

#endif
