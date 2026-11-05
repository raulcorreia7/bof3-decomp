#include "shop_00.h"

MATCH void func_801D543C(void) {
    s32 resource;
    u8* timer_p;
    u8  next;
    u8  panel_timer;

    resource    = 0;
    panel_timer = 0x12;
    switch (g_SaveCardStatus) {
        case CARD_EVENT_TIMEOUT:
            resource = 3;
            break;
        case CARD_EVENT_NEW:
            resource    = 4;
            D_801E607C  = 0;
            D_8014865B  = 0;
            panel_timer = 0xF;
            break;
        case CARD_EVENT_ERROR:
            resource = 5;
            break;
        case CARD_EVENT_CAPACITY:
            resource = 6;
            break;
        case 5:
            Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, D_80144952);
            panel_timer = 8;
            UI_DrawText(28, 22, 0, 0xFFU, Resource_GetText(GAME_TEXT_NO_SAVE_FILE));
            func_801DDFB0(0x62, 0x4C, D_801E60F8, LOBU(g_SaveCardPort), 1);
            g_SaveSlotCount             = 3;
            D_801E60FC                  = 0xF;
            D_8014865B                  = 0;
            g_SaveSlotFirst             = 0;
            g_SaveSlots[2].source_index = 0xFF;
            g_SaveSlots[1].source_index = 0xFF;
            g_SaveSlots[0].source_index = 0xFF;
            break;
        case 6:
            resource = 7;
            break;
        case 7:
            resource = 8;
            break;
        case 8:
            Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, D_80144952);
            panel_timer = 0xB;
            UI_DrawText(28, 22, 0, 0xFFU, Resource_GetText(GAME_TEXT_SAVE_COMPLETE));
            SAVE_DrawSlots(0x20, 0x30, 0U);
            D_801E6080 = 1;
            D_801E6110 = 1;
            break;
        case 9:
            Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, D_80144952);
            panel_timer = 8;
            UI_DrawText(28, 22, 0, 0xFFU, Resource_GetText(GAME_TEXT_INIT_COMPLETE));
            func_801DDFB0(0x62, 0x4C, D_801E60F8, LOBU(g_SaveCardPort), 1);
            g_SaveSlotCount             = 3;
            D_801E60FC                  = 0xF;
            D_8014865B                  = 0;
            g_SaveSlotFirst             = 0;
            g_SaveSlots[2].source_index = 0xFF;
            g_SaveSlots[1].source_index = 0xFF;
            g_SaveSlots[0].source_index = 0xFF;
            break;
        case 10:
            Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, D_80144952);
            panel_timer = 0xB;
            UI_DrawText(28, 22, 0, 0xFFU, Resource_GetText(0x96));
            SAVE_DrawSlots(0x20, 0x30, 0U);
            D_801E6080 = 1;
            D_801E6110 = 1;
            break;
        case 11:
            Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, D_80144952);
            panel_timer = 8;
            UI_DrawText(28, 22, 0, 0xFFU, Resource_GetText(0x8BU));
            SAVE_DrawSlots(0x20, 0x30, 0U);
            break;
        default:
            resource = 9;
            break;
    }
    if (resource != 0) {
        Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, D_80144952);
        UI_DrawText(28, 22, 0, 0xFFU, Resource_GetText(resource + 0x85));
    }
    if ((g_InputPressed != 0) ||
        (((g_SaveCardStatus == 0xA) || (g_SaveCardStatus == 8)) &&
         (timer_p = &D_80148654, next = *timer_p - 1, *timer_p = next, ((next & BYTE_MASK) == 0)))) {
        D_80148654 = 0;
        if ((g_SaveCardStatus != 8) && (g_SaveCardStatus != 0xA)) {
            SND_PlayCue(EMI_CUE_ID(1, 4));
        }
        D_80148652 = panel_timer;
    }
}
