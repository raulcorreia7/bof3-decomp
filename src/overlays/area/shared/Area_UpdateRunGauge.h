/* Steps the press-and-hold gauge at g_Self +0x0B, 0 to 0x40, while the re-arm timer at +0x0A is spent: the masked input WORLD_INPUT_RUN held against g_PadStates[0].held raises the gauge by 1 per frame (a full 0x40 re-arms the timer to 0x1E), releasing lowers it by a level step of 1, 2 or 3, halved per parity when the state byte at +0x02 is set; the stored value is clamped to the 0..0x40 range. */
/* func_801F5254 (area104/14), func_801F5798 (area121/14) */
MATCH void Area_UpdateRunGauge(void) {
    Actor* w;
    s8     clamped;
    s8     stored;
    u32    step;
    u8     timer;
    u8     held;
    u8     level;

    timer = SELF(Actor)->unk_0A;

    if (timer != 0) {
        SELF(Actor)->unk_0A = timer - 1;
    }

    if (SELF(Actor)->unk_0A == 0) {
        if (g_PadStates[0].held & g_InputMasks[WORLD_INPUT_RUN]) {
            held = SELF(Actor)->param.unk_0B;
            if (held < 0x40U) {
                SELF(Actor)->param.unk_0B = held + 1;
            }

            if (SELF(Actor)->param.unk_0B == 0x40) {
                SELF(Actor)->unk_0A = 0x1E;
            }
        } else {
            level = SELF(Actor)->param.unk_0B;
            if (level != 0) {
                if (level >= 0x31U) {
                    step = 3;
                } else {
                    step = 1;
                    if (level >= 0x21U) {
                        step = 2;
                    }
                }

                if (SELF(Actor)->header.step != 0) {
                    SELF(Actor)->param.unk_0B -= step >> 1;
                    if (g_FrameCount & 1) {
                        SELF(Actor)->param.unk_0B -= step & 1;
                    }
                } else {
                    SELF(Actor)->param.unk_0B -= step;
                }
            }
        }

        w       = SELF(Actor);
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
