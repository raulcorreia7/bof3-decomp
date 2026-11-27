#include "area139_13.h"

/* Sets the platform actor's start height and sweeps it up two steps, then raises the scene flag. */
MATCH void func_801F2CE0(void) {
    u8 i;

    SELF(Actor)->unk_06             = 0;
    SELF(Actor)->vx                 = TO_COORD(92);
    SELF(Actor)->unk_18             = TO_COORD(92);
    SELF(Actor)->vy                 = TO_COORD_HALF(9);
    SELF(Actor)->pos.z.part.integer = Area_HeightSample(SELF(Actor)->vx, (SELF(Actor)->unk_1C + SELF(Actor)->vy) / 2);
    func_801F308C(0);

    for (i = 0; i < 2; i++) {
        SELF(Actor)->unk_1C      = SELF(Actor)->vy + TO_COORD(2);
        SELF(Actor)->pos.x.fixed = SELF(Actor)->vx;
        SELF(Actor)->gravity     = TO_COORD(SELF(Actor)->pos.z.part.integer + 256);
        SELF(Actor)->vz          = SELF(Actor)->gravity;
        SELF(Actor)->pos.y.fixed = (SELF(Actor)->vy + SELF(Actor)->unk_1C) / 2;
        func_801F3288(&SELF(Actor)->vx, &SELF(Actor)->unk_18);

        SELF(Actor)->gravity = TO_COORD(SELF(Actor)->pos.z.part.integer + 512);
        SELF(Actor)->vz      = SELF(Actor)->gravity;
        func_801F3288(&SELF(Actor)->vx, &SELF(Actor)->unk_18);
        func_801F3A7C(&SELF(Actor)->vx, &SELF(Actor)->unk_18);

        SELF(Actor)->vy = SELF(Actor)->unk_1C;
        SELF(Actor)->unk_1C += TO_COORD(2);
    }

    if (SYS_TestFlag(g_SceneEventFlags, 0x5C) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 6));
        SELF(Actor)->header.mode = 3;
    }
}
