#ifndef MENU_INVENTORY_H
#define MENU_INVENTORY_H

#include "types.h"

/*
 * Flat inventory arrays and the category-indexed pointer tables that hold
 * their bases. 128 slots per category; the item menu reads the ID and quantity
 * arrays through the pointer tables. See
 * @source: wiki:data/records#gameemi-fixed-tables.
 *
 * The base order and the pointer-table contents come from the shipped image:
 * each table holds the five ID arrays and four quantity arrays in the order
 * below. The code confirms the first four category labels; the fifth ID
 * array's vital-item label is inferred from its position and the category-4
 * vital-item code.
 *
 * Category codes match ITEM_CATEGORY_* in game/item.h.
 */

#define INV_SLOTS_PER_CATEGORY  128
#define INV_ID_PTR_TABLE_COUNT  5
#define INV_QTY_PTR_TABLE_COUNT 4

#define INV_VITAL_ITEM_SLOTS    32

/* One id row and one count row per ITEM_CATEGORY_ITEM..ITEM_CATEGORY_ACCESSORY. */
/* D_8014504C */
extern u8 g_InventoryIds[4][INV_SLOTS_PER_CATEGORY];
/* D_8014524C */
extern u8 g_InventoryCounts[4][INV_SLOTS_PER_CATEGORY];
/* D_8014544C */
extern u8 g_VitalItemIds[INV_VITAL_ITEM_SLOTS];

/* The five list titles the inventory and equip menus draw. */
extern u8* g_MenuInventoryTitles[5];
extern u8* g_MenuEquipTitles[5];

/* The equip choices each item offers: the ids and how many follow. */
extern u8 g_MenuEquipChoiceIds[];
extern u8 g_MenuEquipChoiceCounts[];

/* The inventory and equip panels' sprite and label tables. */
extern char g_MenuNextExpBlank[];
extern u8   g_MenuInventoryTab1OffSprites[];
extern u8   g_MenuInventoryTab1OnSprites[];
extern u8   g_MenuEquipStatLabels[];
extern u8   g_MenuEquipCompareLabels[];
extern u8   g_MenuEquipCompareSprites[];
extern u8   g_MenuEquipSlotIcons[];
extern u8   g_MenuEquipStatSprites[];
extern u8   g_SaveSlotFrameSprites[];

#endif
