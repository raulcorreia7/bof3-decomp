#include "area139_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2CE0(void) {
    u8  i;
    s32 z;

    g_Task->unk_06             = 0;
    g_Task->vx                 = TO_COORD(92);
    g_Task->unk_18             = TO_COORD(92);
    g_Task->vy                 = TO_COORD_HALF(9);
    g_Task->pos.z.part.integer = Area_SampleHeight(g_Task->vx, (g_Task->unk_1C + g_Task->vy) / 2);
    func_801F308C(0);

    for (i = 0; i < 2; i++) {
        g_Task->pos.x.fixed = g_Task->vx;
        g_Task->unk_1C      = g_Task->vy + 0x20000;
        z                   = g_Task->pos.z.part.integer + 0x100;
        g_Task->gravity     = TO_COORD(z);
        g_Task->vz          = g_Task->gravity;
        g_Task->pos.y.fixed = (g_Task->vy + g_Task->unk_1C) / 2;
        func_801F3288(&g_Task->vx, &g_Task->unk_18);

        z               = g_Task->pos.z.part.integer + 0x200;
        g_Task->gravity = TO_COORD(z);
        g_Task->vz      = g_Task->gravity;
        func_801F3288(&g_Task->vx, &g_Task->unk_18);
        func_801F3A7C(&g_Task->vx, &g_Task->unk_18);

        z              = g_Task->unk_1C;
        g_Task->unk_1C = z + 0x20000;
        g_Task->vy     = z;
    }

    if (SYS_TestFlag(g_SceneEventFlags, 0x5C) != 0) {
        SND_PlayCue(0x206);
        g_Task->header.mode = 3;
    }
}
#else
INCLUDE_ASM(func_801F2CE0);
#endif
