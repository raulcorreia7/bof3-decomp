#include "boss013_16.h"

MATCH void func_800C1934(void) {
    register u8* flags;

    if (g_Battle.encounter != 0x10) {
        return;
    }
    if ((g_Battle.boss_flags & 1) && !(g_Battle.boss_flags & 2)) {
        g_Battle.action_type = 0;
        g_MenuPanelMode      = 2;
        Message_StartAreaMessage(0x26);
        g_Battle.boss_flags |= 2;
    }
    flags = &g_Battle.boss_flags;
    if (!(*flags & 0x10)) {
        return;
    }
    if (*flags & 0x20) {
        return;
    }
    g_Battle.action_type = 3;
    g_MenuPanelMode      = 2;
    Message_StartAreaMessage(0x29);
    *flags |= 0x20;
}
