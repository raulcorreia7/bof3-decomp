#include "start_08.h"

MATCH void func_801E9554(void) {
    u8* resource;
    s32 panel_x;
    u32 label_dx;

    g_MenuStartPanel4StateFuncs[g_MenuCurrentPanel->state]();
    Menu_DrawHeaderBar(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, 0x48, 0x13, g_WindowStyle);
    resource = Resource_GetText(g_MenuCurrentPanel->unk_10);
    label_dx = (func_801AF20C(resource) & BYTE_MASK) * 4 - 0x25;
    panel_x  = (s16)(g_MenuCurrentPanel->pos.x - label_dx);
    UI_DrawText(panel_x, g_MenuCurrentPanel->pos.y + 3, 0, func_801AF20C(resource) & BYTE_MASK, resource);
}
