#include "area139_13.h"

/* Sweeps the platform actor two steps from its start cell and raises the scene flag. */
MATCH void func_801F2E68(void) {
    u8 i;

    TASK(Actor)->unk_06             = 0;
    TASK(Actor)->vx                 = TO_COORD_HALF(61);
    TASK(Actor)->unk_1C             = TO_COORD(68);
    TASK(Actor)->vy                 = TO_COORD(68);
    TASK(Actor)->pos.z.part.integer = Area_HeightSample((TASK(Actor)->vx + TASK(Actor)->unk_18) / 2, TASK(Actor)->vy);
    func_801F308C(1);

    for (i = 0; i < 2; i++) {
        TASK(Actor)->unk_18      = TASK(Actor)->vx + TO_COORD(2);
        TASK(Actor)->pos.x.fixed = (TASK(Actor)->vx + TASK(Actor)->unk_18) / 2;
        TASK(Actor)->pos.y.fixed = TASK(Actor)->vy;
        TASK(Actor)->gravity     = TO_COORD(TASK(Actor)->pos.z.part.integer + 256);
        TASK(Actor)->vz          = TASK(Actor)->gravity;
        func_801F3288(&TASK(Actor)->vx, &TASK(Actor)->unk_18);

        TASK(Actor)->gravity = TO_COORD(TASK(Actor)->pos.z.part.integer + 512);
        TASK(Actor)->vz      = TASK(Actor)->gravity;
        func_801F3288(&TASK(Actor)->vx, &TASK(Actor)->unk_18);
        func_801F3A7C(&TASK(Actor)->vx, &TASK(Actor)->unk_18);

        TASK(Actor)->vx = TASK(Actor)->unk_18;
        TASK(Actor)->unk_18 += TO_COORD(2);
    }

    if (SYS_TestFlag(g_SceneEventFlags, 0x5D) == 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 6));
        TASK(Actor)->header.mode = 3;
    }
}
