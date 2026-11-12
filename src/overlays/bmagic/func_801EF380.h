/* Runs the step of the current sparkle D_801F17B4; a sparkle still in use after its first step draws its disc, and its rays on three frames in four. */
/* func_801EF380 (magic070), func_801EF380 (magic071), func_801EF380 (magic072) */
MATCH void func_801EF380(void) {
    SparkleEffectSteps handlers;
    u8                 radius;

    handlers = D_801EEC1C;
    handlers.steps[D_801F17B4->header.step]();
    if ((D_801F17B4->header.flags & EFFECT_SPARKLE_IN_USE) && D_801F17B4->header.step != 0) {
        Effect_DrawSparkleDisc();
        if (D_801F17B4->phase_0C & 3) {
            Effect_DrawSparkleRays(g_FrameCount >> 1, D_801F17B4->unk_06);
            radius = D_801F17B4->unk_06;
            Effect_DrawSparkleWedges((g_FrameCount >> 1) + 4, radius + (radius >> 1));
        }
    }
}
