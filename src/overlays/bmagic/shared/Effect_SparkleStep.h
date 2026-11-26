/* Runs the step that header.step of the current sparkle selects; a sparkle still in use after its first step draws its disc, and its rays and wedges on three frames in four. */
/* func_801EF380 (magic070), func_801EF380 (magic071), func_801EF380 (magic072) */
MATCH void Effect_SparkleStep(void) {
    BMagicSparkleSteps handlers;
    u8                 radius;

    handlers = g_BMagicSparkleSteps;
    handlers.steps[g_BMagicSparkle->header.step]();
    if ((g_BMagicSparkle->header.flags & EFFECT_SPARKLE_IN_USE) && g_BMagicSparkle->header.step != 0) {
        Effect_SparkleDrawDisc();
        if (g_BMagicSparkle->phase_0C & 3) {
            Effect_SparkleDrawRays(g_FrameCount >> 1, g_BMagicSparkle->unk_06);
            radius = g_BMagicSparkle->unk_06;
            Effect_SparkleDrawWedges((g_FrameCount >> 1) + 4, radius + (radius >> 1));
        }
    }
}
