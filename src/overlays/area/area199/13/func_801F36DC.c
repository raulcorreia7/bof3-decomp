#include "area199_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F36DC(void) {
    s32 radius;
    s32 shade;
    s32 x;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, (GetGraphType() == 1 || GetGraphType() == 2) ? 0x2A5 : 0xB5, 0);
    GFX_AddPrim(4, sizeof(DR_MODE));

    if (g_Task->timer < 0xFF) {
        g_Task->timer++;
    }

    radius = 0x20;
    shade  = g_Task->timer;
    if (shade >= 0x15) {
        radius += (shade - 0x14) * 20;
    }
    if (radius >= 0x1F5) {
        radius = 0x1F4;
    }

    shade = g_Task->timer;
    if (shade >= 0x15) {
        shade = 0x80 + (shade - 0x14) * 12;
    } else {
        shade = 0x80;
    }
    if (shade >= 0x100) {
        shade = 0xFF;
    }
    func_801F3EA0(0x82, g_Task->timer + 0xA, radius, shade);

    radius = g_Task->timer * 12;
    if (radius >= 0x31) {
        radius = 0x30;
    }

    shade = rsin(0x100);
    x     = 0x82 + shade * (0x10E - g_Task->timer * 9) / ONE;
    shade = rcos(0x100);
    shade = g_Task->timer + 0xA + shade * (0x10E - g_Task->timer * 9) / ONE;
    func_801F3AB0(x, shade, 0x40, radius);

    shade = rsin(0x100);
    x     = 0x82 + shade * (0xF0 - g_Task->timer * 8) / ONE;
    shade = rcos(0x100);
    shade = g_Task->timer + 0xA + shade * (0xF0 - g_Task->timer * 8) / ONE;
    func_801F3AB0(x, shade, 0x20, radius);

    shade = rsin(0x100);
    x     = 0x82 + shade * (0xB4 - g_Task->timer * 6) / ONE;
    shade = rcos(0x100);
    shade = g_Task->timer + 0xA + shade * (0xB4 - g_Task->timer * 6) / ONE;
    func_801F3AB0(x, shade, 8, radius);

    shade = rsin(0x100);
    x     = 0x82 + shade * (0x78 - g_Task->timer * 4) / ONE;
    shade = rcos(0x100);
    shade = g_Task->timer + 0xA + shade * (0x78 - g_Task->timer * 4) / ONE;
    func_801F3AB0(x, shade, 0x10, radius);
}
#else
INCLUDE_ASM(func_801F36DC);
#endif
