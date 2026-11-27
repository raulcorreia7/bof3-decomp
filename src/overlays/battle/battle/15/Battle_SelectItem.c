#include "battle_15.h"

/* Drives the primary battle-selection panel: seeds the scroll band, reads the 0xF00C triggers (group cycle,
 * cursor walk, page up and down over seven-entry pages), restages the ring handle, then commits the selection,
 * opens the confirm prompt or pages the group entry. The selection work is a MenuChoicePanel; the confirm gate and
 * the commit group are read through the global, not the panel pointer, because the original reloads them by
 * absolute address after the pointer is dead.
 */
/* D_8014857A stays an address symbol at the cursor steps: a g_UIPanelTasks[16] view changes the code. */
/* func_80098450 */
MATCH void Battle_SelectItem(void) {
    MenuChoicePanel* panel;
    s32              trigger;
    u8               old_cursor;
    u32              slot;
    u8*              handle;
    u32              value;

    if (g_BattleChoicePanel.items.state != 0u) {
        return;
    }
    slot = g_BattleMessageSlot[5];
    g_Game.members[slot].u.turn.damage_flags.volatile_value &= 0xBFFFu;
    if (g_BattleChoicePanel.items.state == 0u) {
        D_801485DC = 1u;
        D_801485E0 = (g_UIPanelTasks[16].pos.vx + 7);
        D_801485E2 = (g_UIPanelTasks[16].pos.vy + ((g_UIPanelTasks[16].unk_0C - g_UIPanelTasks[16].unk_0B) * 0xD + 0x1A));
    }
    panel   = &g_BattleChoicePanel.items;
    trigger = INPUT_REPEATED(g_PadStates[0].pressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    if ((trigger & PADLleft) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        g_UIPanelTasks[16].u.message.id = 0x32;
        D_8014857A -= 1;
        if ((s8)D_8014857A < 0) {
            g_UIPanelTasks[16].unk_0A = 3;
        }
    } else if ((trigger & PADLright) != 0) {
        g_UIPanelTasks[16].u.message.id = 0x31;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        D_8014857A += 1;
        if (D_8014857A >= 4u) {
            g_UIPanelTasks[16].unk_0A = 0;
        }
    }
    old_cursor = panel->group_cursor;
    if ((trigger & PADLup) != 0) {
        if (old_cursor != 0u) {
            panel->group_cursor = (old_cursor - 1);
        }
        if (panel->group_cursor < panel->group_first) {
            panel->confirm_timer = 0xF0;
        }
    } else if ((trigger & PADLdown) != 0) {
        if (old_cursor < 0x7Fu) {
            panel->group_cursor = (old_cursor + 1);
        }
        if (panel->group_first + 7 <= panel->group_cursor) {
            panel->confirm_timer = 0x10;
        }
    } else if ((trigger & PADL1) != 0) {
        if (panel->group_first == 0u) {
            panel->group_cursor = 0u;
        } else if (panel->group_first < 7u) {
            panel->group_cursor = (old_cursor - panel->group_first);
            panel->group_first  = 0u;
        } else {
            panel->group_cursor = (old_cursor - 7);
            panel->group_first -= 7;
        }
    } else if ((trigger & PADR1) != 0) {
        if (panel->group_first == 0x79u) {
            panel->group_cursor = 0x7Fu;
        } else if (panel->group_first >= 0x73u) {
            panel->group_cursor = (old_cursor + (0x79 - panel->group_first));
            panel->group_first  = 0x79u;
        } else {
            panel->group_cursor = (old_cursor + 7);
            panel->group_first += 7;
        }
    }
    if (old_cursor != panel->group_cursor) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    handle = UI_MessageGetText(Item_GetDescription(g_UIPanelTasks[16].unk_0A, g_ItemCategoryIds[g_UIPanelTasks[16].unk_0A][g_UIPanelTasks[16].unk_0C]) & HALF_MASK);
    g_BattleMessages[((D_801EC328 - 1) & 0xF)].text = handle;
    if (g_BattleChoicePanel.items.confirm_timer != 0) {
        return;
    }
    if ((trigger & PADLup) != 0 && old_cursor == 0u) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        D_80148625       = 8u;
        D_80148626       = 5u;
        D_80148624       = 1u;
        D_8014862F       = 0xFFu;
        g_Battle.ui_step = 6u;
        D_8014862E       = 0u;
        D_801483C0       = 0u;
        D_80148628       = (g_UIPanelTasks[16].pos.vx + 0x20);
        D_8014862A       = (g_UIPanelTasks[16].pos.vy - 0x16);
        return;
    }
    if ((g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_BattleChoicePhase                                    = 1u;
        D_801485DC                                             = 0u;
        g_BattleMessages[((D_801EC328 - 1) & 0xF)].record_type = 1u;
        D_801454FD                                             = g_UIPanelTasks[16].unk_0A;
        D_801454FE                                             = g_UIPanelTasks[16].unk_0B;
        D_801454FF                                             = g_UIPanelTasks[16].unk_0C;
        g_BattleMessageSlot[0x119]                             = 0u;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_Battle.ui_step += 1u;
        return;
    }
    if ((g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        value                         = g_ItemCategoryIds[g_UIPanelTasks[16].unk_0A][g_UIPanelTasks[16].unk_0C] + (g_UIPanelTasks[16].unk_0A << 8);
        g_BattleActorTurn->command.id = value;
        if ((Item_PassesTest(g_UIPanelTasks[16].unk_08, CHAR_ID_RYU_YOUNG, g_BattleChoicePanel.items.group, value) & BYTE_MASK) == 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
            return;
        }
        D_801454FD = D_8014857A;
        D_801454FE = g_UIPanelTasks[16].unk_0B;
        D_801454FF = g_UIPanelTasks[16].unk_0C;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        g_BattleChoicePhase = 1u;
        D_801485DC          = 0u;
        g_Battle.ui_step    = 3u;
    }
}
