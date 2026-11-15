#include "area080_13.h"

MATCH void func_801F395C(void) {
    u8       scratch[0x30];
    CVECTOR* colors;
    u16      angle;
    s16      spread;
    s32      turn;
    u8       i;

    D_801F44A4 = func_801F3B98();
    if ((g_FrameCount & 3) != 0) {
        return;
    }
    if (D_801F44A4 == NULL) {
        return;
    }
    D_801F44A4->origin.x.fixed = g_Task->pos.x.fixed;
    D_801F44A4->origin.y.fixed = g_Task->pos.y.fixed;
    D_801F44A4->origin.z.fixed = g_Task->pos.z.fixed + TO_COORD(1536);

    angle  = rand() & 0xFFF;
    spread = (rand() & 0x1FF) - 0x100;

    D_801F44A4->pos.x.fixed = g_Task->pos.x.fixed + (rcos(angle) << 8);
    D_801F44A4->pos.y.fixed = g_Task->pos.y.fixed + (rsin(angle) << 8);
    D_801F44A4->pos.z.fixed = Area_SampleHeight(D_801F44A4->pos.x.fixed, D_801F44A4->pos.y.fixed) << 16;

    turn                   = angle + spread + 0x800;
    D_801F44A4->velocity_x = rcos(turn) << 4;
    D_801F44A4->velocity_y = rsin(turn) << 4;
    D_801F44A4->velocity_z = 0;

    /* The eight spark colours follow the handler table in the image's data blob. */
    colors             = (CVECTOR*)(D_801F3DAC + 0x18);
    D_801F44A4->color  = colors[rand() & 7];
    D_801F44A4->active = 1;
    D_801F44A4->life   = 0x20;

    Area_SetCameraMatrix(scratch);
    Area_ProjectPoint(&D_801F44A4->origin.x.fixed, &D_801F44A4->origin_trail[0]);
    Area_ProjectPoint(&D_801F44A4->pos.x.fixed, &D_801F44A4->pos_trail[0]);
    for (i = 1; i < AREA_SPARK_TRAIL_POINTS; i++) {
        D_801F44A4->origin_trail[i] = D_801F44A4->origin_trail[0];
        D_801F44A4->pos_trail[i]    = D_801F44A4->pos_trail[0];
    }
}
