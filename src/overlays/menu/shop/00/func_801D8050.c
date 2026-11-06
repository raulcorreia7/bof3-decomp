#include "shop_00.h"

/* Target-local declarations; the module header is owned elsewhere. */

MATCH void func_801D8050(s32 panel_x) {
    s32 s2;
    s16 s0;
    s32 s1;
    u32 cnt;
    u8  id;
    u8  call_arg4;

    if (panel_x & 0xFF) {
        s2 = D_80148654;
    } else {
        s2 = 0;
    }
    s0        = s2 & 0xFF;
    call_arg4 = D_80144952;
    Menu_DrawHeaderBar(MENU_HEADER_X, (0x10 - (s0 * 0xA)) & 0xFFFE, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, call_arg4);
    s1 = 0;
    s0 = s0 << 5;
    s0 = 0x11 - s0;
loop:
    cnt = Party_CountOrder(0);
    if ((s1 & 0xFF) < (cnt & 0xFF)) {
        id = D_80145FCC[(s1 & 0xFF)][0];
        if (g_Characters[id].inoculations != 0) {
            Menu_DrawCharacterWindow(s0 & 0xFFFF, (((s1 & 0xFF) * 0x36) + 0x3E) & 0xFFFE, id, 1, 0);
        } else {
            Menu_DrawCharacterWindow(s0 & 0xFFFF, (((s1 & 0xFF) * 0x36) + 0x3E) & 0xFFFE, id, 0, 0);
        }
        s1 += 1;
        goto loop; /* try the next entry */
    }
    Menu_DrawZennyWindow((s2 << 5) + 0xB4, 0x26, 0, g_Zenny);
}
