#include "start_08.h"

extern void func_801D49F8(s32 handler_index);

MATCH void func_801D3A98(void) {
    MenuPanelTask* task;
    s32            input;
    u8             entry;
    u8*            rows;

    Menu_DrawClutStrip(D_80144953);
    g_MenuPanelTasks[13].unk_0C = 0xFF;
    g_MenuPanelTasks[11].unk_10 = 0x18;
    g_MenuPanelTasks[21].active = 1;
    g_MenuPanelTasks[13].unk_0C = 0xFF;
    task                        = &g_MenuPanelTasks[14];
    task->unk_0C                = 0xFF;
    g_MenuPanelTasks[21].x      = task->x + 5;
    g_MenuPanelTasks[21].y      = task->y + (task->unk_0B * 16 + 26);

    input = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown));
    if (input & PADLup) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        if ((s8)--task->unk_0B < 0) {
            task->unk_0B = D_801EC3E0[task->unk_0A * 6] - 1;
        }
    } else if (input & PADLdown) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        task->unk_0B++;
        if (D_801EC3E0[task->unk_0A * 6] - 1 < task->unk_0B) {
            task->unk_0B = 0;
        }
    }

    if (g_InputPressed & D_80145AC2) {
        SND_PlayCue(EMI_CUE_ID(1, 3));
        rows  = D_801EC3E0;
        entry = (rows + task->unk_0A * 6 + task->unk_0B)[1];
        if (entry != 0) {
            func_801D49F8(entry);
            return;
        }
        g_MenuPanelTasks[13].flags  = 0xFF;
        g_MenuPanelTasks[13].unk_0C = s_ChoiceMenuCursors[g_MenuPanelTasks[13].unk_0A];
        /* D_80148652 through D_80148651: retail keeps the symbol-relative
         * address in a register for the read-modify-write. */
        (&D_80148651)[1]++;
    } else if (g_InputPressed & D_80145AC4) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        task->active = 0;
        (&D_80148651)[1]--;
    }
}
