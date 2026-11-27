#include "boss013_16.h"

MATCH void func_800C1B4C(void) {
    u8           flags;
    volatile u8* live;

    if (g_Battle.encounter == 16) {
        flags = g_Battle.boss_flags;
        if (flags & 1) {
            if (!(flags & 4)) {
                g_Battle.action_type = 0;
                g_UIPanelMode        = 2;
                UI_MessageStartArea(MSG_BOSS013_037);
                g_Battle.boss_flags |= 4;
                live  = &g_Battle.boss_flags;
                flags = *live;
            }
            if (flags & 8) {
                if (!(flags & 0x10)) {
                    g_Battle.action_type = 0;
                    g_UIPanelMode        = 2;
                    UI_MessageStartArea(MSG_BOSS013_040);
                    g_Battle.boss_flags |= 0x10;
                }
            }
            if (g_Battle.boss_flags & 0x20) {
                g_Battle.action_type = 3;
                g_UIPanelMode        = 2;
                UI_MessageStartArea(MSG_BOSS013_042);
            }
        }
    }
}
