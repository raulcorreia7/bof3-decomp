#include "area056_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3354(void) {
    s16 height;

    g_Task->vz += g_Task->gravity;
    Actor_MovementUpdate();
    height = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    if (COORD_INT(g_Task->pos.z) < height) {
        COORD_INT(g_Task->pos.z) = height;
        g_Task->vz               = 0;
        g_Task->gravity          = 0;
        g_Task->unk_04           = 2;
    }
    if ((g_Task->unk_05 == 0) && (((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE)) == 0)) {
        Area_AdvanceScroll(COORD_INT(g_Task->pos.z));
    }
    g_Game.current->u.field.unk_122 -= 2;
}
#else
INCLUDE_ASM(func_801F3354);
#endif
