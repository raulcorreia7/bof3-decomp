#include "commu04_06.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The commu04 overlay entry: the shared commu step byte selects the handler,
 * then the menu panels refresh while the game state is still zero. */
MATCH void func_801D0C04(void) {
    g_Commu04Steps[D_801F294C]();
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        UI_PanelUpdateTasks();
    }
}

MATCH void func_801D0C5C(void) {
    SYS_DISPATCH_BYTE(g_Commu04Step0Steps, D_801F294D);
}

MATCH void func_801D0C98(void) {
    u8* state = &g_GameStateIndex;

    if (*state != GAME_REQUEST_MESSAGE) {
        UI_MessageStartArea(MSG_AREA175_PICK_ITEM);
        *state = GAME_REQUEST_MESSAGE;
        D_801F294D += 1;
    }
}

MATCH void func_801D0CF4(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        UI_PanelResetTasks();
        func_801D16A4();
        D_801D1774 = 4;
        D_801F294D += 1;
    }
}

/* The fairy job picker: the choice panel walks the item list and confirm stores the pick. */
MATCH void func_801D0D4C(void) {
    s32 buttons;
    u32 row_limit;
    u32 row_count;
    u8  old_cursor;
    u8  new_row;
    u8  item_entry;
    u8* selection;

    if (D_801D1774 != 0) {
        D_801D1774--;
    }
    UI_WindowDraw(0x14, (0x12 - (D_801D1774 * 12)) & 0xFFFE, 0x118, 0x13, UI_WINDOW_OPEN_ALL | UI_WINDOW_STYLE_TRANSLUCENT, g_WindowStyle);
    UI_WindowDrawOutline(0x16, 0x14 - (D_801D1774 * 12), 0x113, 0xF, 0);
    if (g_UiPanelTasks[0].state != 0) {
        return;
    }
    g_UiPanelTasks[1].active = 1;
    g_UiPanelTasks[1].pos.vx = g_UiPanelTasks[0].pos.vx + 7;
    g_UiPanelTasks[1].pos.vy = (u16)(g_UiPanelTasks[0].pos.vy + ((g_Commu04ItemPanel.group_cursor - g_Commu04ItemPanel.group_first) * 0xD + 0x1A));
    buttons                  = INPUT_REPEATED(g_PadStates[0].pressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    if (buttons & PADLleft) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        g_Commu04ItemPanel.message_id = 0x32;
        g_Commu04ItemPanel.group--;
        if ((s8)g_Commu04ItemPanel.group < 0) {
            g_Commu04ItemPanel.group = 3;
        }
    } else if (buttons & PADLright) {
        g_Commu04ItemPanel.message_id = 0x31;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        g_Commu04ItemPanel.group++;
        if (g_Commu04ItemPanel.group >= 4U) {
            g_Commu04ItemPanel.group = 0;
        }
    }
    old_cursor = g_Commu04ItemPanel.group_cursor;
    if (buttons & PADLup) {
        if (old_cursor != 0) {
            g_Commu04ItemPanel.group_cursor = (g_Commu04ItemPanel.group_cursor - 1);
        }
        if (g_Commu04ItemPanel.group_cursor < g_Commu04ItemPanel.group_first) {
            g_Commu04ItemPanel.confirm_timer = 0xF0;
        }
    } else if (buttons & PADLdown) {
        if (old_cursor < 0x7FU) {
            g_Commu04ItemPanel.group_cursor = (g_Commu04ItemPanel.group_cursor + 1);
        }
        if (g_Commu04ItemPanel.group_cursor >= g_Commu04ItemPanel.group_first + 9) {
            g_Commu04ItemPanel.confirm_timer = 0x10;
        }
    } else if (buttons & PADL1) {
        row_limit = g_Commu04ItemPanel.group_first & BYTE_MASK;
        if (row_limit == 0) {
            g_Commu04ItemPanel.group_cursor = 0U;
        } else if (row_limit < 9U) {
            g_Commu04ItemPanel.group_cursor = (g_Commu04ItemPanel.group_cursor - g_Commu04ItemPanel.group_first);
            g_Commu04ItemPanel.group_first  = 0U;
        } else {
            g_Commu04ItemPanel.group_cursor = (g_Commu04ItemPanel.group_cursor - 9);
            g_Commu04ItemPanel.group_first  = g_Commu04ItemPanel.group_first - 9;
        }
    } else if (buttons & PADR1) {
        row_count = g_Commu04ItemPanel.group_first & BYTE_MASK;
        if (row_count == 119) {
            g_Commu04ItemPanel.group_cursor = 0x7FU;
        } else if (row_count >= 111U) {
            new_row                         = g_Commu04ItemPanel.group_cursor + 0x77;
            g_Commu04ItemPanel.group_cursor = new_row - g_Commu04ItemPanel.group_first;
            g_Commu04ItemPanel.group_first  = 0x77;
        } else {
            g_Commu04ItemPanel.group_cursor = (g_Commu04ItemPanel.group_cursor + 9);
            g_Commu04ItemPanel.group_first  = g_Commu04ItemPanel.group_first + 9;
        }
    }
    if (old_cursor != g_Commu04ItemPanel.group_cursor) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    if (g_Commu04ItemPanel.confirm_timer == 0) {
        if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
            g_UiPanelTasks[1].active = 0;
            g_UiPanelTasks[0].state  = 1;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            D_801F294D += 1;
        } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
            item_entry = g_ItemCategoryIds[g_Commu04ItemPanel.group][g_Commu04ItemPanel.group_cursor];
            if (item_entry == 0) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                return;
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 5));
            selection                            = &g_SceneEventSelection;
            g_FairyJobs[*selection].record_state = item_entry;
            g_FairyJobs[*selection].unk_03       = g_Commu04ItemPanel.group;
            g_UiPanelTasks[0].state              = 1;
            g_UiPanelTasks[1].active             = 0;
            D_801F294D                           = 4;
        }
        item_entry = g_ItemCategoryIds[g_Commu04ItemPanel.group][g_Commu04ItemPanel.group_cursor];
        if (item_entry != 0) {
            UI_TextDraw(0x1D, 0x15, 0, 0xFF, UI_MessageGetText(Item_GetDescription(g_Commu04ItemPanel.group, item_entry) & HALF_MASK));
        }
    }
}

MATCH void func_801D11DC(void) {
    if (D_801D1774 < 4U) {
        D_801D1774 += 1;
    }
    UI_WindowDraw(0x14, (0x12 - (D_801D1774 * 12)) & 0xFFFE, 0x118, 0x13, UI_WINDOW_OPEN_ALL | UI_WINDOW_STYLE_TRANSLUCENT, g_WindowStyle);
    UI_WindowDrawOutline(0x16, 0x14 - (D_801D1774 * 12), 0x113, 0xF, 0);
    if (g_UiPanelTasks[0].state == 0) {
        UI_PanelResetTasks();
        MESSAGE_START_WAIT(MSG_AREA175_SEE_YOU_LATER);
        D_801F294C += 1;
    }
}

MATCH void func_801D12C8(void) {
    u8* record;
    s32 i;
    u8  flags;

    if (D_801D1774 < 4U) {
        D_801D1774 += 1;
    }
    UI_WindowDraw(0x14, (0x12 - (D_801D1774 * 12)) & 0xFFFE, 0x118, 0x13, UI_WINDOW_OPEN_ALL | UI_WINDOW_STYLE_TRANSLUCENT, g_WindowStyle);
    UI_WindowDrawOutline(0x16, 0x14 - (D_801D1774 * 12), 0x113, 0xF, 0);
    if (g_UiPanelTasks[0].state != 0) {
        return;
    }

    UI_PanelResetTasks();
    /* kept: retail indexes g_FairyJobs by the selection at every use; a FairyJob local shrinks the image by 0x50 bytes. */
    switch (g_FairyJobs[g_SceneEventState.selection].unk_03 & 0xF) {
        case ITEM_CATEGORY_ITEM:
            flags = g_Items[g_FairyJobs[g_SceneEventState.selection].record_state].flags;
            break;
        case ITEM_CATEGORY_WEAPON:
            flags = g_Weapons[g_FairyJobs[g_SceneEventState.selection].record_state].header.flags;
            break;
        case ITEM_CATEGORY_ARMOR:
            flags = g_Armors[g_FairyJobs[g_SceneEventState.selection].record_state].header.flags;
            break;
        default:
            flags = g_Accessories[g_FairyJobs[g_SceneEventState.selection].record_state].header.flags;
            break;
    }

    /* The copy shop handles the unsellable rows like the vital items. */
    if (flags & ITEM_UNSELLABLE) {
        UI_MessageStartArea(MSG_AREA175_COPY_CANNOT_HELP);
        D_801F294D = 6;
    } else {
        record = Item_GetRecord(g_FairyJobs[g_SceneEventState.selection].unk_03, g_FairyJobs[g_SceneEventState.selection].record_state);
        for (i = 0; i < ITEM_NAME_LENGTH; i++) {
            g_TextVariables[0][i] = record[i];
        }
        g_TextVariables[0][ITEM_NAME_LENGTH] = 0;
        UI_MessageStartArea(MSG_AREA175_CONFIRM_ITEM);
        D_801D1774 = 0;
        D_801F294D += 1;
    }
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
}

MATCH void func_801D1568(void) {
    u8* selection;
    u8  step;
    u8  job_index;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        selection = &g_SceneEventState.selection;
        Item_Remove(g_FairyJobs[*selection].unk_03, g_FairyJobs[*selection].record_state, 1, 0);
        g_FairyJobs[*selection].unk_03 |= 0x10;
        step      = D_801F294C;
        job_index = *selection;
        step += 1;
        g_FairyJobs[job_index].progress_anchor = g_BattleCount;
        D_801F294C                             = step;
    }
}

MATCH void func_801D1628(void) {
    u8* state = &g_GameStateIndex;

    if (*state != GAME_REQUEST_MESSAGE) {
        UI_MessageStartArea(MSG_AREA175_ASK_CHOOSE_OTHER);
        *state = GAME_REQUEST_MESSAGE;
    }
}

#include "overlays/commu/shared/Fairy_EndCommuScene.h"

MATCH void func_801D16A4(void) {
    g_UiPanelTasks[0].panel    = 2;
    g_UiPanelTasks[0].mode     = 0;
    g_UiPanelTasks[0].state    = 2;
    g_UiPanelTasks[0].active   = 1;
    g_UiPanelTasks[0].pos.vx   = -0xAA;
    g_UiPanelTasks[0].pos.vy   = 0x3E;
    g_UiPanelTasks[0].unk_0A   = 0;
    g_UiPanelTasks[0].unk_0B   = 0;
    g_UiPanelTasks[0].unk_0C   = 0;
    g_UiPanelTasks[0].flags    = 0xFF;
    g_UiPanelTasks[0].unk_08   = 0;
    g_UiPanelTasks[0].unk_09   = 0;
    g_UiPanelTasks[0].u.grow.w = 0;
    g_UiPanelTasks[0].u.grow.h = 0;

    g_UiPanelTasks[1].panel  = 2;
    g_UiPanelTasks[1].mode   = 1;
    g_UiPanelTasks[1].state  = 0;
    g_UiPanelTasks[1].active = 0;
}
