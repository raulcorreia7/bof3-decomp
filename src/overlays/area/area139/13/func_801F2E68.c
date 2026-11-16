#include "area139_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2E68(void) {
    DVECTOR start;
    DVECTOR end;
    s32     point[3];
    MATRIX  camera;

    g_Task->pos.x.fixed = TO_COORD(24) + COORD_HALF;
    g_Task->pos.y.fixed = TO_COORD(18);
    g_Task->pos.z.fixed = (Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) << 16) + TO_COORD(0x800);
    g_Task->screen_x    = 0x80;
    g_Task->screen_y    = 0x180;
    g_Task->unk_32      = 0;
    g_Task->timer       = 8;
    g_Task->header.mode++;
    Area_SetCameraMatrix(&camera);
    point[0] = g_Task->pos.x.fixed;
    point[1] = g_Task->pos.y.fixed;
    point[2] = g_Task->pos.z.fixed;
    Area_ProjectPoint(point, &start);
    point[2] -= TO_COORD(256);
    Area_ProjectPoint(point, &end);
    g_Task->unk_32 = ratan2(end.vy - start.vy, end.vx - start.vx) + 0x400;
    SND_PlayCue(0x202);
}
#else
INCLUDE_ASM(func_801F2E68);
#endif
