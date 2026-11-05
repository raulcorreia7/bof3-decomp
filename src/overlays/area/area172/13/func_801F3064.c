#include "area172_13.h"

MATCH void func_801F3064(void) {
    u16 screen_x;
    u8  mode;

    screen_x           = g_SpadWork->unk_2E + 0x18;
    g_SpadWork->unk_2E = screen_x;
    func_801F36C0(&g_SpadWork->x, (s16)screen_x, 7);
    mode               = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = mode;
    if (!(mode & 0xFF)) {
        g_SpadWork->unk_09 = 0x40;
        g_SpadWork->unk_01 += 1;
    }
}
