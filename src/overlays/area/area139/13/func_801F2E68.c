#include "area139_13.h"

/* Sweeps the platform actor two steps from its start cell and raises the scene flag. */
MATCH void func_801F2E68(void) {
    u8 i;

    g_Task->unk_06             = 0;
    g_Task->vx                 = TO_COORD_HALF(61);
    g_Task->unk_1C             = TO_COORD(68);
    g_Task->vy                 = TO_COORD(68);
    g_Task->pos.z.part.integer = Area_SampleHeight((g_Task->vx + g_Task->unk_18) / 2, g_Task->vy);
    func_801F308C(1);

    for (i = 0; i < 2; i++) {
        g_Task->unk_18      = g_Task->vx + TO_COORD(2);
        g_Task->pos.x.fixed = (g_Task->vx + g_Task->unk_18) / 2;
        g_Task->pos.y.fixed = g_Task->vy;
        g_Task->gravity     = TO_COORD(g_Task->pos.z.part.integer + 256);
        g_Task->vz          = g_Task->gravity;
        func_801F3288(&g_Task->vx, &g_Task->unk_18);

        g_Task->gravity = TO_COORD(g_Task->pos.z.part.integer + 512);
        g_Task->vz      = g_Task->gravity;
        func_801F3288(&g_Task->vx, &g_Task->unk_18);
        func_801F3A7C(&g_Task->vx, &g_Task->unk_18);

        g_Task->vx = g_Task->unk_18;
        g_Task->unk_18 += TO_COORD(2);
    }

    if (SYS_TestFlag(g_SceneEventFlags, 0x5D) == 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
        g_Task->header.mode = 3;
    }
}
