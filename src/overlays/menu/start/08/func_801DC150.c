#include "start_08.h"

#include "overlays/menu/Menu_DrawExperienceWindow.h"

MATCH void func_801DC150(s16 x, s16 y, u8 index, u8 flag) {
    MENU_DRAW_EXPERIENCE_WINDOW(g_MenuLabelEquip + 8, g_MenuLabelEquip + 12, g_MenuExperienceSprites)
}
