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
MATCH void func_801DCFD0(void) {
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
        g_SpawnedActors[6].unk_07 &= ~2;
        SELF(FishingState)->flag_04 -= 1;
        return;
    }

    if (!(g_SpawnedActors[6].unk_07 & 1)) {
        UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, 83));
        if (*pad_state & g_InputMasks[FISHING_INPUT_CAST]) {
            item = FISHING_ACCESSORY_SLOT(g_SpawnedActors[6].pos.x.part.integer);
            if (g_Accessories[(u8)item].type == ITEM_TYPE_FISHING_ROD) {
                saved = item;
                Item_Remove(ITEM_CATEGORY_ACCESSORY, item, 1, 0);
                if (g_FishingEquipment.rod_id != 0) {
                    Item_Add(ITEM_CATEGORY_ACCESSORY, g_FishingEquipment.rod_id, 1, 0);
                }
                g_FishingEquipment.rod_id = saved;
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            g_SpawnedActors[6].unk_07 &= ~2;
            SELF(FishingState)->flag_04 -= 1;
            return;
        }
        if (input & PADLup) {
            if (g_SpawnedActors[6].vx != 0) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                g_SpawnedActors[6].vx -= 1;
            }
        } else if (input & PADLdown) {
            if (g_SpawnedActors[6].vx < g_SpawnedActors[6].counter_18 - 1) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                g_SpawnedActors[6].vx += 1;
            }
        }
        item = FISHING_ACCESSORY_SLOT(g_SpawnedActors[6].pos.x.part.integer);
        if (g_Accessories[(u8)item].type == ITEM_TYPE_FISHING_ROD) {
            g_SpawnedActors[6].unk_2C = item + 4;
        } else {
            g_SpawnedActors[6].unk_2C = 0xFFFF;
        }
        UI_CursorDraw(0xA8, (u16)(g_SpawnedActors[6].vx * FISHING_ACCESSORY_ROW_HEIGHT + 0x5A), 0);
        return;
    }

    UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, 84));
    if (g_SpawnedActors[6].unk_0A == 0) {
        if (*pad_state & g_InputMasks[FISHING_INPUT_CAST]) {
            item = FISHING_ACCESSORY_SLOT(g_SpawnedActors[6].pos.y.part.integer);
            if (g_Accessories[(u8)item].type == ITEM_TYPE_FISHING_LURE) {
                if (g_FishingEquipment.lure_id != (u8)item) {
                    saved = item;
                    Item_Remove(ITEM_CATEGORY_ACCESSORY, item, 1, 0);
                    if (g_FishingEquipment.lure_id != 0) {
                        Item_Add(ITEM_CATEGORY_ACCESSORY, g_FishingEquipment.lure_id, 1, 0);
                    }
                    g_FishingEquipment.lure_id    = saved;
                    g_FishingEquipment.lure_count = 1;
                    for (i = 0, count = 0; i < FISHING_ACCESSORY_SLOT_COUNT; i++) {
                        if (g_Accessories[FISHING_ACCESSORY_SLOT(i)].type == ITEM_TYPE_FISHING_LURE) {
                            count++;
                        }
                    }
                    if (g_SpawnedActors[6].counter_1C >= count) {
                        if (g_SpawnedActors[6].pos.y.part.fraction != 0 && count - 9 < g_SpawnedActors[6].pos.y.part.fraction) {
                            g_SpawnedActors[6].pos.y.part.fraction -= 1;
                        }
                    }
                }
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            g_SpawnedActors[6].unk_07 &= ~2;
            SELF(FishingState)->flag_04 -= 1;
            return;
        }
        if (input & PADLup) {
            if (g_SpawnedActors[6].selection == 0) {
                if (g_SpawnedActors[6].pos.y.part.fraction != 0) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                    g_SpawnedActors[6].unk_08 = 4;
                    g_SpawnedActors[6].unk_0A = 3;
                    g_SpawnedActors[6].pos.y.part.fraction -= 1;
                }
            } else {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                g_SpawnedActors[6].selection -= 1;
            }
        } else if (input & PADLdown) {
            if (g_SpawnedActors[6].selection == 8) {
                if (g_SpawnedActors[6].pos.y.part.fraction + 8 < g_SpawnedActors[6].counter_1C) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                    g_SpawnedActors[6].unk_08 = 0;
                    g_SpawnedActors[6].unk_0A = 3;
                    g_SpawnedActors[6].pos.y.part.fraction += 1;
                }
            } else if (g_SpawnedActors[6].selection < g_SpawnedActors[6].counter_1C) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                g_SpawnedActors[6].selection += 1;
            }
        } else if (*pad_state & PADL1) {
            old                                    = g_SpawnedActors[6].pos.y.part.fraction;
            g_SpawnedActors[6].pos.y.part.fraction = old - 9;
            if ((s16)g_SpawnedActors[6].pos.y.part.fraction >= 0) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
            } else {
                g_SpawnedActors[6].pos.y.part.fraction = 0;
                if (old != 0) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                } else if (g_SpawnedActors[6].selection != 0) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                    g_SpawnedActors[6].selection = 0;
                }
            }
        } else if (*pad_state & PADR1) {
            if (g_SpawnedActors[6].counter_1C >= 9) {
                old                                    = g_SpawnedActors[6].pos.y.part.fraction;
                g_SpawnedActors[6].pos.y.part.fraction = old + 9;
                if (g_SpawnedActors[6].pos.y.part.fraction + 8 < g_SpawnedActors[6].counter_1C) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                } else {
                    g_SpawnedActors[6].pos.y.part.fraction = g_SpawnedActors[6].counter_1C - 8;
                    if (g_SpawnedActors[6].pos.y.part.fraction == old) {
                        if (g_SpawnedActors[6].selection < 8) {
                            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                            g_SpawnedActors[6].selection = 8;
                        }
                    } else {
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                    }
                }
            } else if (g_SpawnedActors[6].selection < g_SpawnedActors[6].counter_1C) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
                g_SpawnedActors[6].selection = g_SpawnedActors[6].counter_1C;
            }
        }
    }

    item = FISHING_ACCESSORY_SLOT(g_SpawnedActors[6].pos.y.part.integer);
    if (g_Accessories[(u8)item].type == ITEM_TYPE_FISHING_LURE) {
        g_SpawnedActors[6].unk_2C = item + 4;
    } else {
        g_SpawnedActors[6].unk_2C = 0xFFFF;
    }
    UI_CursorDraw(0xA8, (u16)(g_SpawnedActors[6].selection * FISHING_ACCESSORY_ROW_HEIGHT + 0x5A), 0);
}
