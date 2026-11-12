/* Runs the step of the current effect work record D_801F17B0; one still in use after its first step draws its disc, and its rays on three frames in four. */
/* func_801EF37C (magic162), func_801EF37C (magic168) */
MATCH void func_801EF37C(void) {
    BMagicEffectWorkSteps handlers;
    u8                    radius;

    handlers = D_801EEC1C;
    handlers.steps[D_801F17B0->header.step]();
    if ((D_801F17B0->header.flags & BMAGIC_EFFECT_IN_USE) && D_801F17B0->header.step != 0) {
        func_801EFCD8();
        if (D_801F17B0->phase_0C & 3) {
            Effect_DrawSparkleRays(g_FrameCount >> 1, D_801F17B0->unk_06);
            radius = D_801F17B0->unk_06;
            func_801EFA40((g_FrameCount >> 1) + 4, radius + (radius >> 1));
        }
    }
}
