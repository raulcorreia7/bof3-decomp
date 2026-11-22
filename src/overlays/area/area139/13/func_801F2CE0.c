#include "area139_13.h"

/* Sets the platform actor's start height and sweeps it up two steps, then raises the scene flag. */
MATCH void func_801F2CE0(void) {
    u8 i;

    g_Task->unk_06             = 0;
    g_Task->vx                 = TO_COORD(92);
    g_Task->unk_18             = TO_COORD(92);
    g_Task->vy                 = TO_COORD_HALF(9);
    g_Task->pos.z.part.integer = Area_HeightSample(g_Task->vx, (g_Task->unk_1C + g_Task->vy) / 2);
    func_801F308C(0);

    for (i = 0; i < 2; i++) {
        g_Task->unk_1C      = g_Task->vy + TO_COORD(2);
        g_Task->pos.x.fixed = g_Task->vx;
        g_Task->gravity     = TO_COORD(g_Task->pos.z.part.integer + 256);
        g_Task->vz          = g_Task->gravity;
        g_Task->pos.y.fixed = (g_Task->vy + g_Task->unk_1C) / 2;
        func_801F3288(&g_Task->vx, &g_Task->unk_18);

        g_Task->gravity = TO_COORD(g_Task->pos.z.part.integer + 512);
        g_Task->vz      = g_Task->gravity;
        func_801F3288(&g_Task->vx, &g_Task->unk_18);
        func_801F3A7C(&g_Task->vx, &g_Task->unk_18);

        g_Task->vy = g_Task->unk_1C;
        g_Task->unk_1C += TO_COORD(2);
    }

    if (SYS_TestFlag(g_SceneEventFlags, 0x5C) != 0) {
        SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 6));
        g_Task->header.mode = 3;
    }
}
