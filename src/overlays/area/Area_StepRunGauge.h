/* Steps the press-and-hold gauge at g_Task +0x0B, 0 to 0x40, while the
 * re-arm timer at +0x0A is spent: the masked input WORLD_INPUT_RUN held against
 * g_InputHeld raises the gauge by 1 per frame (a full 0x40 re-arms the timer to
 * 0x1E), releasing lowers it by a level step of 1, 2 or 3, halved per parity
 * when the state byte at +0x02 is set; the stored value is clamped to the
 * 0..0x40 range. One definition shared by the world area overlays. Every change
 * here must verify every member address.
 */
/* func_801F5254 (area104/14), func_801F5798 (area121/14) */
MATCH void Area_StepRunGauge(void) {
    Actor* w;
    s8     clamped;
    s8     stored;
    u32    step;
    u8     timer;
    u8     held;
    u8     level;

    timer = g_Task->unk_0A;

    if (timer != 0) {
        g_Task->unk_0A = timer - 1;
    }

    if (g_Task->unk_0A == 0) {
        if (g_InputHeld & g_InputMasks[WORLD_INPUT_RUN]) {
            held = g_Task->param.unk_0B;
            if (held < 0x40U) {
                g_Task->param.unk_0B = held + 1;
            }

            if (g_Task->param.unk_0B == 0x40) {
                g_Task->unk_0A = 0x1E;
            }
        } else {
            level = g_Task->param.unk_0B;
            if (level != 0) {
                if (level >= 0x31U) {
                    step = 3;
                } else {
                    step = 1;
                    if (level >= 0x21U) {
                        step = 2;
                    }
                }

                if (g_Task->header.step != 0) {
                    g_Task->param.unk_0B -= step >> 1;
                    if (g_FrameCount & 1) {
                        g_Task->param.unk_0B -= step & 1;
                    }
                } else {
                    g_Task->param.unk_0B -= step;
                }
            }
        }

        w       = g_Task;
        clamped = (s8)w->param.unk_0B;
        if (clamped >= 0) {
            stored = 0x40;
            if (clamped < 0x41) {
                stored = clamped;
            }
        } else {
            stored = 0;
        }
        w->param.unk_0B = (u8)stored;
    }
}
