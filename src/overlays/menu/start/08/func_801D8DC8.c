#include "start_08.h"

MATCH void func_801D8DC8(void) {
    MenuPanelTask* panel;
    s32            buttons;
    u8             old;
    u8             column;
    s32            next;

    Menu_DrawClutStrip(D_80144953);
    panel = &g_MenuPanelTasks[17];
    if (D_801485A0 != 0) {
        g_MenuPanelTasks[11].unk_10 = D_801485A0 + 0x4183;
    } else {
        g_MenuPanelTasks[11].unk_10 = 0;
    }
    g_MenuPanelTasks[21].active = 1;
    g_MenuPanelTasks[21].pos.x  = panel->pos.x + 7;
    g_MenuPanelTasks[21].pos.y  = panel->pos.y + ((panel->unk_0B - panel->unk_0A) * 0xD + 0x1A);
    buttons                     = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown | PADL1 | PADR1));
    old                         = panel->unk_0B;
    if (buttons & PADLup) {
        if (old != 0) {
            panel->unk_0B = old - 1;
        }
        if (panel->unk_0B < panel->unk_0A) {
            panel->unk_08 = 0xF0;
        }
    } else if (buttons & PADLdown) {
        if (old < 0x11) {
            panel->unk_0B = old + 1;
        }
        if (panel->unk_0B >= panel->unk_0A + 9) {
            panel->unk_08 = 0x10;
        }
    } else if (buttons & PADL1) {
        column = panel->unk_0A;
        if (column == 0) {
            panel->unk_0B = 0;
        } else if (column < 9) {
            panel->unk_0B = old - column;
            panel->unk_0A = 0;
        } else {
            panel->unk_0B = old - 9;
            panel->unk_0A = panel->unk_0A - 9;
        }
    } else if (buttons & PADR1) {
        if (panel->unk_0A == 9) {
            panel->unk_0B = 0x11;
        } else if (panel->unk_0A != 0) {
            next          = old + 9;
            panel->unk_0B = next - panel->unk_0A;
            panel->unk_0A = 9;
        } else {
            panel->unk_0B = old + 9;
            panel->unk_0A = panel->unk_0A + 9;
        }
    }
    D_801ED891 = g_BattleListCursor;
    D_801ED890 = g_MenuPanelTasks[17].unk_0A;
    if (old != panel->unk_0B) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    if (g_InputPressed & D_80145AC4) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        D_80148597                  = 1;
        g_MenuPanelTasks[21].active = 0;
        D_80148654                  = 7;
        D_80148652 += 1;
    }
}
