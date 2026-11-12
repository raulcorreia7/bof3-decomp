#include "shop_00.h"

MATCH void func_801D543C(void) {
    s32 resource;
    u8* timer_p;
    u8  next;
    u8  panel_timer;

    resource    = 0;
    panel_timer = 18;
    switch (g_SaveCardStatus) {
        case CARD_EVENT_TIMEOUT:
            resource = 3;
            break;
        case CARD_EVENT_NEW:
            resource    = 4;
            D_801E607C  = 0;
            D_8014865B  = 0;
            panel_timer = 15;
            break;
        case CARD_EVENT_ERROR:
            resource = 5;
            break;
        case CARD_EVENT_CAPACITY:
            resource = 6;
            break;
        case SAVE_STATUS_NO_FILE:
            MENU_DRAW_HEADER();
            panel_timer = 8;
            UI_DrawText(28, 22, 0, 255U, Message_GetText(GAME_TEXT_NO_SAVE_FILE));
            SAVE_DrawPortTabs(98, 76, D_801E60F8, g_SaveCardPort, 1);
            g_SaveSlotCount             = 3;
            D_801E60FC                  = 0xF;
            D_8014865B                  = 0;
            g_SaveSlotFirst             = 0;
            g_SaveSlots[2].source_index = GAME_NONE;
            g_SaveSlots[1].source_index = GAME_NONE;
            g_SaveSlots[0].source_index = GAME_NONE;
            break;
        case SAVE_STATUS_WRITE_FAILED:
            resource = 7;
            break;
        case SAVE_STATUS_FORMAT_FAILED:
            resource = 8;
            break;
        case SAVE_STATUS_SAVED:
            MENU_DRAW_HEADER();
            panel_timer = 11;
            UI_DrawText(28, 22, 0, 255U, Message_GetText(GAME_TEXT_SAVE_COMPLETE));
            SAVE_DrawSlots(SAVE_SLOTS_X, SAVE_SLOTS_Y, 0U);
            D_801E6080 = 1;
            D_801E6110 = 1;
            break;
        case SAVE_STATUS_FORMATTED:
            MENU_DRAW_HEADER();
            panel_timer = 8;
            UI_DrawText(28, 22, 0, 255U, Message_GetText(GAME_TEXT_INIT_COMPLETE));
            SAVE_DrawPortTabs(98, 76, D_801E60F8, g_SaveCardPort, 1);
            g_SaveSlotCount             = 3;
            D_801E60FC                  = 0xF;
            D_8014865B                  = 0;
            g_SaveSlotFirst             = 0;
            g_SaveSlots[2].source_index = GAME_NONE;
            g_SaveSlots[1].source_index = GAME_NONE;
            g_SaveSlots[0].source_index = GAME_NONE;
            break;
        case SAVE_STATUS_CREATED:
            MENU_DRAW_HEADER();
            panel_timer = 11;
            UI_DrawText(28, 22, 0, 255U, Message_GetText(0x96));
            SAVE_DrawSlots(SAVE_SLOTS_X, SAVE_SLOTS_Y, 0U);
            D_801E6080 = 1;
            D_801E6110 = 1;
            break;
        case 11:
            MENU_DRAW_HEADER();
            panel_timer = 8;
            UI_DrawText(28, 22, 0, 255U, Message_GetText(0x8BU));
            SAVE_DrawSlots(SAVE_SLOTS_X, SAVE_SLOTS_Y, 0U);
            break;
        default:
            resource = 9;
            break;
    }
    if (resource != 0) {
        MENU_DRAW_HEADER();
        UI_DrawText(28, 22, 0, 255U, Message_GetText(resource + 0x85));
    }
    if ((g_InputPressed != 0) ||
        (((g_SaveCardStatus == SAVE_STATUS_CREATED) || (g_SaveCardStatus == SAVE_STATUS_SAVED)) && (timer_p = &D_80148654, next = *timer_p - 1, *timer_p = next, ((next & BYTE_MASK) == 0)))) {
        D_80148654 = 0;
        if ((g_SaveCardStatus != SAVE_STATUS_SAVED) && (g_SaveCardStatus != SAVE_STATUS_CREATED)) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
        }
        g_MenuStep.state = panel_timer;
    }
}
