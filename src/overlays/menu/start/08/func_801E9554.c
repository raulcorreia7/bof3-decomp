#include "start_08.h"

MATCH void func_801E9554(void) {
    u8* resource;
    s32 panel_x;
    u32 label_dx;

    D_801ED3D4[g_MenuCurrentPanel->state]();
    Menu_DrawHeaderBar(g_MenuCurrentPanel->x, g_MenuCurrentPanel->y, 0x48, 0x13, D_80144952);
    resource = Resource_GetText(g_MenuCurrentPanel->unk_10);
    label_dx = (func_801AF20C(resource) & 0xFF) * 4 - 0x25;
    panel_x  = (s16)(g_MenuCurrentPanel->x - label_dx);
    UI_DrawText(panel_x, g_MenuCurrentPanel->y + 3, 0, func_801AF20C(resource) & 0xFF, resource);
}
