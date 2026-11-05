#include "start_08.h"

MATCH void func_801D1FDC(void) {
    s32            i;
    u8             count;
    u32            idx;
    MenuPanelTask* panel;

    Menu_ResetPanelTasks();
    i = 0;
    for (;;) {
        count = Party_CountOrder(0);
        idx   = i & BYTE_MASK;
        if (idx >= (u32)count) {
            break;
        }
        panel = &g_MenuPanelTasks[4 + idx];

        panel->unk_0A = i;
        i += 1;
        panel->unk_00[1] = 6;
        panel->unk_00[0] = 1;
        panel->unk_00[2] = 0;
        panel->state     = 0;
        panel->x         = 0x62;
        panel->y         = idx * 0x36 + 0x3E;
        panel->unk_0B    = 0;
        panel->unk_0C    = 0;
    }
    panel            = &g_MenuPanelTasks[7];
    D_8014842D       = 6;
    D_8014842E       = 1;
    D_8014842F       = 0;
    panel->unk_00[0] = 1;
    panel++;
    D_80148430       = 0xC8;
    D_80148432       = 0x10;
    D_80148451       = 6;
    D_80148452       = 2;
    D_80148453       = 0;
    panel->unk_00[0] = 1;
    panel++;
    D_80148476       = 3;
    D_80148454       = 0x10;
    D_80148456       = 0x10;
    D_80148475       = 6;
    D_80148477       = 0;
    panel->unk_00[0] = 1;
    D_80148478       = 0x68;
    D_8014847A       = 0x2A;
    D_8014849A       = 4;
    D_8014847E       = 0;
    D_8014847F       = 0;
    D_80148480       = 0;
    D_80148484       = 0;
    D_80148499       = 6;
    D_8014849B       = 0;
    panel++;
    panel->unk_00[0] = 1;
    D_8014849C       = 0x73;
    D_8014849E       = 0x10;
    D_801484A8       = 0;
}
