#include "battle_15.h"

/* Drives the primary battle-selection panel: seeds the scroll band, reads the 0xF00C triggers (group cycle,
 * cursor walk, page up and down over seven-entry pages), restages the ring handle, then commits the selection,
 * opens the confirm prompt or pages the group entry. The selection work is a MenuChoicePanel; the confirm gate and
 * the commit group are read through the global, not the panel pointer, because the original reloads them by
 * absolute address after the pointer is dead.
 */
MATCH void func_80098450(void) {
    volatile u8*     phase;
    MenuChoicePanel* panel;
    s32              trigger;
    u8               old_cursor;
    u32              slot;
    u8*              handle;
    u32              value;

    phase = &g_BattleChoicePanel[3];
    if (*phase != 0u) {
        return;
    }
    slot = g_BattleMessageSlot[5];
    g_BattlePartyBattlers[slot].damage_flags.volatile_value &= 0xBFFFu;
    if (*phase == 0u) {
        D_801485DC = 1u;
        D_801485E0 = (D_80148574 + 7);
        D_801485E2 = (D_80148576 + ((D_8014857C - D_8014857B) * 0xD + 0x1A));
    }
    panel   = (MenuChoicePanel*)g_BattleChoicePanel;
    trigger = INPUT_REPEATED(g_InputPressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    if ((trigger & PADLleft) != 0) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        D_80148580 = 0x32;
        D_8014857A -= 1;
        if ((s8)D_8014857A < 0) {
            D_8014857A = 3;
        }
    } else if ((trigger & PADLright) != 0) {
        D_80148580 = 0x31;
        SND_PlayCue(EMI_CUE_ID(1, 1));
        D_8014857A += 1;
        if (D_8014857A >= 4u) {
            D_8014857A = 0;
        }
    }
    old_cursor = panel->group_cursor;
    if ((trigger & PADLup) != 0) {
        if (old_cursor != 0u) {
            panel->group_cursor = (old_cursor - 1);
        }
        if (panel->group_cursor < panel->group_first) {
            panel->confirm_gate = 0xF0;
        }
    } else if ((trigger & PADLdown) != 0) {
        if (old_cursor < 0x7Fu) {
            panel->group_cursor = (old_cursor + 1);
        }
        if (panel->group_first + 7 <= panel->group_cursor) {
            panel->confirm_gate = 0x10;
        }
    } else if ((trigger & 0x4) != 0) {
        if (panel->group_first == 0u) {
            panel->group_cursor = 0u;
        } else if (panel->group_first < 7u) {
            panel->group_cursor = (old_cursor - panel->group_first);
            panel->group_first  = 0u;
        } else {
            panel->group_cursor = (old_cursor - 7);
            panel->group_first -= 7;
        }
    } else if ((trigger & 0x8) != 0) {
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
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    handle = Resource_GetText(Item_GetDescription(D_8014857A, D_801C893C[D_8014857A][D_8014857C]) & HALF_MASK);
    D_801EB5B4[((D_801EC328 - 1) & 0xF) * 2] = handle;
    if (((MenuChoicePanel*)g_BattleChoicePanel)->confirm_gate != 0) {
        return;
    }
    if ((trigger & PADLup) != 0 && old_cursor == 0u) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        D_80148625     = 8u;
        D_80148626     = 5u;
        D_80148624     = 1u;
        D_8014862F     = 0xFFu;
        g_BattleUIStep = 6u;
        D_8014862E     = 0u;
        D_801483C0     = 0u;
        D_80148628     = (D_80148574 + 0x20);
        D_8014862A     = (D_80148576 - 0x16);
        return;
    }
    if ((g_InputPressed & D_80145AC4) != 0u) {
        g_BattleChoicePhase                      = 1u;
        D_801485DC                               = 0u;
        D_801EB5B1[((D_801EC328 - 1) & 0xF) * 8] = 1u;
        D_801454FD                               = D_8014857A;
        D_801454FE                               = D_8014857B;
        D_801454FF                               = D_8014857C;
        g_BattleMessageSlot[0x119]               = 0u;
        SND_PlayCue(EMI_CUE_ID(1, 6));
        *(u8*)&g_BattleUIStep += 1u;
        return;
    }
    if ((g_InputPressed & D_80145AC2) != 0u) {
        value                   = D_801C893C[D_8014857A][D_8014857C] + (D_8014857A << 8);
        *(u16*)(D_801EB4D8 + 2) = value;
        if ((func_801AF494(D_80148578, 0, ((MenuChoicePanel*)g_BattleChoicePanel)->group, value) & BYTE_MASK) == 0) {
            SND_PlayCue(EMI_CUE_ID(1, 7));
            return;
        }
        D_801454FD = D_8014857A;
        D_801454FE = D_8014857B;
        D_801454FF = D_8014857C;
        SND_PlayCue(EMI_CUE_ID(1, 3));
        g_BattleChoicePhase = 1u;
        D_801485DC          = 0u;
        g_BattleUIStep      = 3u;
    }
}
