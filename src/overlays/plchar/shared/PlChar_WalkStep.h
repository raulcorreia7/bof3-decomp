/* One route step for a field character: turn the facing when the route index is even, probe the step ahead, then play the walk or the blocked animation and bump the task state. PlChar_ProbeFacingCell is the image-local probe; the route table and the animation player are the resident executable's. */
/* func_801CE898 (plp478), func_801CEC78 (plp578), func_801CEE74 (plp278), func_801CEE74 (plp27a), func_801CEE94
   (plp457), func_801CF090 (plp247), func_801CF470 (plp257), func_801CF724 (plp678), func_801CF940 (plp467),
   func_801CFD20 (plp567), func_801CFF1C (plp267) */
MATCH void PlChar_WalkStep(void) {
    s16 dist;
    s32 x;
    s32 y;

    if ((SELF(Actor)->direction & 1) == 0) {
        SELF(Actor)->direction = (SELF(Actor)->direction - 1) & 7;
        if ((u8)PlChar_ProbeFacingCell() == 0) {
            SELF(Actor)->direction = (SELF(Actor)->direction + 2) & 7;
            if ((u8)PlChar_ProbeFacingCell() == 0) {
                SELF(Actor)->direction = (SELF(Actor)->direction - 2) & 7;
            }
        }
    }
    x    = SELF(Actor)->pos.x.fixed + g_FacingSteps[SELF(Actor)->direction].x;
    y    = SELF(Actor)->pos.y.fixed + g_FacingSteps[SELF(Actor)->direction].y;
    dist = Area_HeightRead(x, y) - COORD_INT(SELF(Actor)->pos.z);
    Area_HeightReadStep(x, y, SELF(Actor)->direction);
    if (SP_REF(u8, 0x0u) != 0 && dist >= 65) {
        Script_Request((SELF(Actor)->direction - 1) / 2 + 0x46);
        SELF(Actor)->header.step++;
    } else {
        SELF(Actor)->unk_2B = 1;
        x                   = SELF(Actor)->pos.x.fixed + g_FacingSteps[FACING_RIGHT].x;
        y                   = SELF(Actor)->pos.y.fixed + g_FacingSteps[FACING_RIGHT].y;
        dist                = Area_HeightReadStep(x, y, FACING_RIGHT);
        if (SP_REF(u8, 0x0u) != 0 && dist >= 65 && COORD_INT(SELF(Actor)->pos.z) < Area_HeightRead(x, y)) {
            SELF(Actor)->unk_2B = 0;
        }
        x    = SELF(Actor)->pos.x.fixed + g_FacingSteps[FACING_DOWN].x;
        y    = SELF(Actor)->pos.y.fixed + g_FacingSteps[FACING_DOWN].y;
        dist = Area_HeightReadStep(x, y, FACING_DOWN);
        if (SP_REF(u8, 0x0u) != 0 && dist >= 65 && COORD_INT(SELF(Actor)->pos.z) < Area_HeightRead(x, y)) {
            SELF(Actor)->unk_2B = 0;
        }
        /* FAKE: retail reads SND_SEPlay as void(s32). */
        ((void (*)(s32))SND_SEPlay)(SELF(Actor)->unk_2C + 0x100);
        Script_Request((SELF(Actor)->direction - 1) / 2 + 0x42);
        SELF(Actor)->unk_0A = 5;
    }
    SELF(Actor)->param.unk_0B = 0;
    SELF(Actor)->header.step++;
}
