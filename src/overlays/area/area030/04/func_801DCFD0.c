#include "area030_04.h"

/* The accessory slot list sits this far past the panel style byte. */
#define FISHING_ACCESSORY_SLOT_OFFSET 0x87A
/* The accessory slot list: one byte per slot, naming the accessory type. */
#define FISHING_ACCESSORY_SLOT_COUNT  128
/* Each accessory row is one icon cell tall. */
#define FISHING_ACCESSORY_ROW_HEIGHT  13
/* One accessory slot of the slot list: the accessory id the row holds. */
#define FISHING_ACCESSORY_SLOT(slot)  (MEM_PTR(u8, (u8*)&g_WindowStyle + FISHING_ACCESSORY_SLOT_OFFSET)[(slot)])

/* The rod and lure equip panels: the pad repeat walks the cursor row, the page
 * keys step the lure page, and the pick button swaps the selected accessory with
 * the equipped one through the item tables. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DCFD0(void) {
    u16* pad_state;
    s32  input;
    s32  item;
    s32  count;
    s32  i;
    u16  old;
    u8   saved;

    pad_state = &g_PadStates[0].pressed;
    input     = INPUT_REPEATED(*pad_state, (PADLup | PADLdown));

    if (*pad_state & g_InputMasks[FISHING_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        D_80144287 &= ~2;
        TASK(FishingState)->flag_04 -= 1;
        return;
    }

    if (!(D_80144287 & 1)) {
        UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, 83));
        if (*pad_state & g_InputMasks[FISHING_INPUT_CAST]) {
            item = FISHING_ACCESSORY_SLOT(D_801442B6);
            if (g_Accessories[item].type == ITEM_TYPE_FISHING_ROD) {
                saved = item;
                Item_Remove(ITEM_CATEGORY_ACCESSORY, item, 1, 0);
                if (g_FishingEquipment.rod_id != 0) {
                    Item_Add(ITEM_CATEGORY_ACCESSORY, g_FishingEquipment.rod_id, 1, 0);
                }
                g_FishingEquipment.rod_id = saved;
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            D_80144287 &= ~2;
            TASK(FishingState)->flag_04 -= 1;
            return;
        }
        if (input & PADLup) {
            if (D_8014428C != 0) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                D_8014428C -= 1;
            }
        } else if (input & PADLdown) {
            if (D_8014428C < D_80144298 - 1) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                D_8014428C += 1;
            }
        }
        item = FISHING_ACCESSORY_SLOT(D_801442B6);
        if (g_Accessories[item].type == ITEM_TYPE_FISHING_ROD) {
            D_801442AC = item + 4;
        } else {
            D_801442AC = 0xFFFF;
        }
        UI_CursorDraw(0xA8, (u16)(D_8014428C * FISHING_ACCESSORY_ROW_HEIGHT + 0x5A), 0);
        return;
    }

    UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, 84));
    if (D_8014428A == 0) {
        if (*pad_state & g_InputMasks[FISHING_INPUT_CAST]) {
            item = FISHING_ACCESSORY_SLOT(D_801442BA);
            if (g_Accessories[item].type == ITEM_TYPE_FISHING_LURE) {
                if (g_FishingEquipment.lure_id != item) {
                    saved = item;
                    Item_Remove(ITEM_CATEGORY_ACCESSORY, item, 1, 0);
                    if (g_FishingEquipment.lure_id != 0) {
                        Item_Add(ITEM_CATEGORY_ACCESSORY, g_FishingEquipment.lure_id, 1, 0);
                    }
                    g_FishingEquipment.lure_id    = saved;
                    g_FishingEquipment.lure_count = 1;
                    count                         = 0;
                    for (i = 0; i < FISHING_ACCESSORY_SLOT_COUNT; i++) {
                        if (g_Accessories[FISHING_ACCESSORY_SLOT(i)].type == ITEM_TYPE_FISHING_LURE) {
                            count++;
                        }
                    }
                    if (D_8014429C >= count) {
                        if (D_801442B8 != 0 && count - 9 < D_801442B8) {
                            D_801442B8 -= 1;
                        }
                    }
                }
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            D_80144287 &= ~2;
            TASK(FishingState)->flag_04 -= 1;
            return;
        }
        if (input & PADLup) {
            if (D_80144290 != 0) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                D_80144290 -= 1;
            } else if (D_801442B8 != 0) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                D_80144288 = 4;
                D_8014428A = 3;
                D_801442B8 -= 1;
            }
        } else if (input & PADLdown) {
            if (D_80144290 == 8) {
                if (D_801442B8 + 8 < D_8014429C) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                    D_80144288 = 0;
                    D_8014428A = 3;
                    D_801442B8 += 1;
                }
            } else if (D_80144290 < D_8014429C) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                D_80144290 += 1;
            }
        } else if (*pad_state & PADL1) {
            old = D_801442B8;
            if (old >= 9) {
                D_801442B8 = old - 9;
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
            } else {
                D_801442B8 = 0;
                if (old != 0) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                } else if (D_80144290 != 0) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                    D_80144290 = 0;
                }
            }
        } else if (*pad_state & PADR1) {
            old = D_801442B8;
            if (D_8014429C < 9) {
                if (D_80144290 < D_8014429C) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                    D_80144290 = D_8014429C;
                }
            } else {
                D_801442B8 = old + 9;
                if (D_801442B8 + 8 < D_8014429C) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                } else {
                    D_801442B8 = D_8014429C - 8;
                    if (D_801442B8 != old) {
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                    } else if (D_80144290 < 8) {
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                        D_80144290 = 8;
                    }
                }
            }
        }
    }

    item = FISHING_ACCESSORY_SLOT(D_801442BA);
    if (g_Accessories[item].type == ITEM_TYPE_FISHING_LURE) {
        D_801442AC = item + 4;
    } else {
        D_801442AC = 0xFFFF;
    }
    UI_CursorDraw(0xA8, (u16)(D_80144290 * FISHING_ACCESSORY_ROW_HEIGHT + 0x5A), 0);
}
#else
INCLUDE_ASM(func_801DCFD0);
#endif
