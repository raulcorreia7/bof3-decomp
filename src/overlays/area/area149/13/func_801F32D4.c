#include "area149_13.h"

MATCH void func_801F32D4(void) {
    s16  height;
    u8   i;
    s32* scroll_target;
    s32* party_x;
    s32* focus_x;

    i = 0;
    if (g_AreaCameraX == 0x63FF) {
        g_AreaCameraX = 0x77FF;
        scroll_target = &g_AreaScrollTargetX;
        *scroll_target -= TO_COORD(20);
        g_AreaTileOriginX -= 20;
        party_x = &g_PartyX;
        *party_x -= TO_COORD(20);
        height         = Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
        g_ScrollHeight = height;
        Area_ScrollAdvance(height);
        Area_CellRefreshGrid();
        /* The live type 0x37 actors move with the camera and stay on the ground. */
        for (; i < ACTOR_SLOT_COUNT; i++) {
            if (ACTOR_IN_USE(g_SpawnedActors[i]) && g_SpawnedActors[i].type == 0x37) {
                g_SpawnedActors[i].pos.x.fixed -= TO_COORD(20);
                COORD_INT(g_SpawnedActors[i].pos.z) = Area_HeightSample(g_SpawnedActors[i].pos.x.fixed, g_SpawnedActors[i].pos.y.fixed);
            }
        }
        focus_x = &g_PartyActors[0].pos.x.fixed;
        *focus_x -= TO_COORD(20);
        D_80147A96 = Area_HeightSample(*focus_x, g_AreaFocusY);
    }
}
