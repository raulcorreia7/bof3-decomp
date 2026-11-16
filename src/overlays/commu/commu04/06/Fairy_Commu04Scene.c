#include "commu04_06.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The commu04 overlay entry: the shared commu step byte selects the handler,
 * then the menu panels refresh while the game state is still zero. */
MATCH void func_801D0C04(void) {
    g_Commu04States[D_801F294C]();
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        Menu_UpdatePanelTasks();
    }
}

MATCH void func_801D0C5C(void) {
    SYS_DISPATCH_BYTE(g_Commu04Step0Funcs, D_801F294D);
}

MATCH void func_801D0C98(void) {
    u8* state = &g_GameStateIndex;

    if (*state != GAME_REQUEST_MESSAGE) {
        Message_StartAreaMessage(0x60);
        *state = GAME_REQUEST_MESSAGE;
        D_801F294D += 1;
    }
}

MATCH void func_801D0CF4(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        Menu_ResetPanelTasks();
        func_801D16A4();
        D_801D1774 = 4;
        D_801F294D += 1;
    }
}

INCLUDE_ASM(func_801D0D4C);

MATCH void func_801D11DC(void) {
    if (D_801D1774 < 4U) {
        D_801D1774 += 1;
    }
    UI_DrawWindow(0x14, (0x12 - (D_801D1774 * 12)) & 0xFFFE, 0x118, 0x13, 0xF2, g_WindowStyle);
    UI_DrawWindowOutline(0x16, 0x14 - (D_801D1774 * 12), 0x113, 0xF, 0);
    if (g_MenuPanelTasks[0].state == 0) {
        Menu_ResetPanelTasks();
        Message_StartAreaMessage(0x5F);
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
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
    UI_DrawWindow(0x14, (0x12 - (D_801D1774 * 12)) & 0xFFFE, 0x118, 0x13, 0xF2, g_WindowStyle);
    UI_DrawWindowOutline(0x16, 0x14 - (D_801D1774 * 12), 0x113, 0xF, 0);
    if (g_MenuPanelTasks[0].state != 0) {
        return;
    }

    Menu_ResetPanelTasks();
    /* kept: retail indexes g_FairyJobs by the selection at every use; a FairyJob local shrinks the image by 0x50 bytes. */
    switch (g_FairyJobs[g_SceneEventState.selection].unk_03 & 0xF) {
        case ITEM_CAT_ITEM:
            flags = g_Items[g_FairyJobs[g_SceneEventState.selection].record_state].flags;
            break;
        case ITEM_CAT_WEAPON:
            flags = g_Weapons[g_FairyJobs[g_SceneEventState.selection].record_state].header.flags;
            break;
        case ITEM_CAT_ARMOR:
            flags = g_Armors[g_FairyJobs[g_SceneEventState.selection].record_state].header.flags;
            break;
        default:
            flags = g_Accessories[g_FairyJobs[g_SceneEventState.selection].record_state].header.flags;
            break;
    }

    /* Bit 3 is ITEM_TARGET_ALL on an item and an equipability flag on the other three tables. */
    if (flags & 0x8) {
        Message_StartAreaMessage(0xEB);
        D_801F294D = 6;
    } else {
        record = Item_GetRecord(g_FairyJobs[g_SceneEventState.selection].unk_03, g_FairyJobs[g_SceneEventState.selection].record_state);
        for (i = 0; i < ITEM_NAME_LENGTH; i++) {
            g_TextVariables[0][i] = record[i];
        }
        g_TextVariables[0][ITEM_NAME_LENGTH] = 0;
        Message_StartAreaMessage(0x61);
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
        Message_StartAreaMessage(0x63);
        *state = GAME_REQUEST_MESSAGE;
    }
}

#include "overlays/commu/Fairy_EndCommuScene.h"

MATCH void func_801D16A4(void) {
    g_MenuPanelTasks[0].handler       = 2;
    g_MenuPanelTasks[0].mode          = 0;
    g_MenuPanelTasks[0].state         = 2;
    g_MenuPanelTasks[0].active        = 1;
    LOH(g_MenuPanelTasks[0].pos.x)    = -0xAA;
    g_MenuPanelTasks[0].pos.y         = 0x3E;
    g_MenuPanelTasks[0].unk_0A        = 0;
    g_MenuPanelTasks[0].unk_0B        = 0;
    g_MenuPanelTasks[0].unk_0C        = 0;
    g_MenuPanelTasks[0].flags         = 0xFF;
    g_MenuPanelTasks[0].unk_08        = 0;
    g_MenuPanelTasks[0].unk_09        = 0;
    g_MenuPanelTasks[0].u.grow.width  = 0;
    g_MenuPanelTasks[0].u.grow.height = 0;

    g_MenuPanelTasks[1].handler = 2;
    g_MenuPanelTasks[1].mode    = 1;
    g_MenuPanelTasks[1].state   = 0;
    g_MenuPanelTasks[1].active  = 0;
}
