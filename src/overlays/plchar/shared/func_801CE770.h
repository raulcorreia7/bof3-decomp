/* One route step for a field character that takes the step height at face value: turn the facing when the route index is even, probe the step ahead, then play the walk or the blocked animation and bump the task state. */
MATCH void func_801CE770(void) {
    s16 dist;
    s32 x;
    s32 y;

    if ((g_Task->direction & 1) == 0) {
        g_Task->direction = (g_Task->direction - 1) & 7;
        if ((u8)PlChar_ProbeFacingCell() == 0) {
            g_Task->direction = (g_Task->direction + 2) & 7;
            if ((u8)PlChar_ProbeFacingCell() == 0) {
                g_Task->direction = (g_Task->direction - 2) & 7;
            }
        }
    }
    x    = g_Task->pos.x.fixed + g_FacingSteps[g_Task->direction].x;
    y    = g_Task->pos.y.fixed + g_FacingStepY[g_Task->direction * 2];
    dist = Area_HeightReadStep(x, y, g_Task->direction);
    if (SP_REF(u8, 0x0u) != 0 && dist >= 65) {
        Script_Request((g_Task->direction - 1) / 2 + 0x46);
        g_Task->header.step++;
    } else {
        g_Task->unk_2B = 1;
        x              = g_Task->pos.x.fixed + g_FacingSteps[FACING_RIGHT].x;
        y              = g_Task->pos.y.fixed + g_FacingSteps[FACING_RIGHT].y;
        dist           = Area_HeightReadStep(x, y, FACING_RIGHT);
        if (SP_REF(u8, 0x0u) != 0 && dist >= 65 && COORD_INT(g_Task->pos.z) < Area_HeightRead(x, y)) {
            g_Task->unk_2B = 0;
        }
        x    = g_Task->pos.x.fixed + g_FacingSteps[FACING_DOWN].x;
        y    = g_Task->pos.y.fixed + g_FacingSteps[FACING_DOWN].y;
        dist = Area_HeightReadStep(x, y, FACING_DOWN);
        if (SP_REF(u8, 0x0u) != 0 && dist >= 65 && COORD_INT(g_Task->pos.z) < Area_HeightRead(x, y)) {
            g_Task->unk_2B = 0;
        }
        /* FAKE: retail reads SND_SEPlay as void(s32). */
        ((void (*)(s32))SND_SEPlay)(g_Task->unk_2C + 0x100);
        Script_Request((g_Task->direction - 1) / 2 + 0x42);
        g_Task->unk_0A = 5;
    }
    g_Task->param.unk_0B = 0;
    g_Task->header.step++;
}
