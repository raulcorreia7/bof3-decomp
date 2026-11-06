#include "start_08.h"

MATCH void func_801D4884(void) {
    u8* ptr = &D_801484BC;
    u8  value;

    g_MenuPanelTasks[11].handler = 6;
    g_MenuPanelTasks[11].mode    = 9;
    g_MenuPanelTasks[11].state   = 2;
    *ptr                         = 1;
    g_MenuPanelTasks[11].pos.x   = 0x14;
    D_801484C2                   = -0x14;
    g_MenuPanelTasks[11].unk_10  = 0;
    ptr += 0x24;
    g_MenuPanelTasks[12].handler = 6;
    g_MenuPanelTasks[12].mode    = 0xD;
    g_MenuPanelTasks[12].state   = 2;
    *ptr                         = 1;
    D_801484E6                   = -0x14;
    g_MenuPanelTasks[12].pos.x   = 0x40;
    g_MenuPanelTasks[12].unk_0A  = 0;
    {
        /* FAKE: keep the retail byte value in $a0 across both stores. */
        MATCH_REG(u8, byte, "a0");

        byte                         = 0xFF;
        g_MenuPanelTasks[12].unk_0B  = byte;
        g_MenuPanelTasks[13].handler = 6;
        g_MenuPanelTasks[13].mode    = 0xC;
        g_MenuPanelTasks[13].state   = 2;
        ptr += 0x24;
        *ptr = 1;
        ptr += 0xD8;
        g_MenuPanelTasks[13].unk_0C = byte;
        g_MenuPanelTasks[13].flags  = byte;
    }
    value                        = *s_ChoiceMenuValues;
    D_80148508                   = -0xC8;
    g_MenuPanelTasks[13].pos.y   = 0x3E;
    g_MenuPanelTasks[19].mode    = 0xA;
    g_MenuPanelTasks[13].unk_0A  = 0;
    g_MenuPanelTasks[13].unk_08  = 0;
    g_MenuPanelTasks[13].unk_09  = 0;
    g_MenuPanelTasks[13].unk_10  = 0;
    g_MenuPanelTasks[13].unk_12  = 0;
    g_MenuPanelTasks[19].handler = 6;
    g_MenuPanelTasks[13].unk_0B  = value;
    *ptr                         = 0;
    g_MenuPanelTasks[19].unk_0A  = 1;
    g_MenuPanelTasks[19].unk_0B  = 1;
    g_MenuPanelTasks[21].handler = 6;
    g_MenuPanelTasks[21].mode    = 0xE;
    D_80148627                   = 0;
    /* FAKE: keep the updated record pointer for the final store. */
    MATCH_FAKE_OPAQUE(ptr);
    ptr[0x48] = 0;
}
