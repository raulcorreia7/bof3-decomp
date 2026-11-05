#include "shop_00.h"

MATCH void func_801D163C(void) {
    u8*            entry;
    u8*            pick;
    s32            input;
    s32            held;
    u8             old;
    u8             i;
    u8             choice;
    MenuPanelTask* panel;
    MenuPanelTask* panels;

    entry                      = D_8018E7CC + g_ShopStockIndex * 2;
    g_ShopItemCategory         = entry[1];
    i                          = 0;
    choice                     = entry[2];
    g_MenuPanelTasks[8].unk_0A = 0;
    g_ShopItemId               = choice;
    panels                     = &g_MenuPanelTasks[3];
    for (; i < (u8)Party_CountOrder(0); i++) {
        panel         = (MenuPanelTask*)(i * sizeof(MenuPanelTask) + (u32)panels);
        panel->unk_0B = Item_GetKind(g_ShopItemCategory, g_ShopItemId);
        panel->unk_0C = g_ShopItemId;
    }
    g_MenuPanelTasks[0].unk_10 = Item_GetDescription(g_ShopItemCategory, g_ShopItemId);
    D_80148474                 = 0;
    if (D_80148453 == 0) {
        /* FAKE: block boundary keeps the panel-task stores base-relative off one la. */
        ORDER_LOCK((void)0);
        g_MenuPanelTasks[21].unk_00[0] = 1;
        D_80148628                     = (u16)D_80148454 + 4;
        D_8014862A                     = (u16)D_80148456 + g_ShopStockIndex * 0xD + 0xA;
        D_80148644                     = D_8018E7CC;
    }
    input = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown));
    old   = g_ShopStockIndex;
    if (input & PADLup) {
        if ((g_ShopStockIndex = old - 1) < 0) {
            g_ShopStockIndex = *D_8018E7CC - 1;
        }
    } else if (input & PADLdown) {
        if ((g_ShopStockIndex = old + 1) > (s8)*D_8018E7CC - 1) {
            g_ShopStockIndex = 0;
        }
    }
    if ((s8)old != g_ShopStockIndex) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    D_8014845C = g_ShopStockIndex;
    if (g_InputPressed & D_80145AC2) {
        pick               = D_8018E7CC + g_ShopStockIndex * 2;
        g_ShopItemCategory = pick[1];
        g_ShopItemId       = pick[2];
        g_ShopItemCount    = 1;
        g_ShopItemPrice    = Shop_ApplyPercent(Item_GetPrice(g_ShopItemCategory, g_ShopItemId), g_ShopPricePercent);
        g_ShopItemCountMax = g_Zenny / (u32)g_ShopItemPrice;
        held = Item_Count(g_ShopItemCategory, g_ShopItemId, 0) + Item_Count(g_ShopItemCategory, g_ShopItemId, 1);
        if ((u8)held >= 100) {
            g_ShopItemCount    = 0;
            g_ShopItemCountMax = 0;
        } else if ((u8)(99 - held) < (u32)g_ShopItemCountMax) {
            g_ShopItemCountMax = (u8)(99 - held);
            if (g_ShopItemCountMax != 0) {
                g_ShopItemCount = 1;
            } else {
                g_ShopItemCount = 0;
            }
        }
        if (g_Zenny >= (u32)g_ShopItemPrice) {
            D_8014865B = 1;
            SND_PlayCue(EMI_CUE_ID(1, 3));
            D_80148652 += 1;
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 7));
        }
    } else if (g_InputPressed & D_80145AC4) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        for (i = 0; i < (u8)Party_CountOrder(0); i++) {
            g_MenuPanelTasks[i + 3].state = 1;
        }
        D_80148453 = 1;
        D_80148651 = 1;
        D_80148652 = 0;
    }
}
