/* Shared by area172/13/func_801F47F0.c and area141/13/func_801F390C.c; verify both images after changes. */
#define AREA_FADE_ACTOR_TINT_BODY(increment)                            \
    do {                                                                \
        s8     tintA;                                                   \
        s8     tintB;                                                   \
        s8     tintC;                                                   \
        Actor* spad;                                                    \
        Actor* spad2;                                                   \
                                                                        \
        spad = g_Task;                                                  \
        spad->pos.x.fixed += spad->vx;                                  \
        spad->pos.y.fixed += spad->vy;                                  \
        tintA = spad->tint.signed_bytes.delta.red;                      \
        if (tintA < -0x40) {                                            \
            spad->tint.signed_bytes.delta.red = tintA + (increment);    \
        }                                                               \
        spad2 = g_Task;                                                 \
        tintB = spad2->tint.signed_bytes.delta.green;                   \
        if (tintB < -0x40) {                                            \
            spad2->tint.signed_bytes.delta.green = tintB + (increment); \
            spad2                                = g_Task;              \
        }                                                               \
        tintC = spad2->tint.signed_bytes.delta.blue;                    \
        if (tintC < -0x40) {                                            \
            spad2->tint.signed_bytes.delta.blue = tintC + (increment);  \
        }                                                               \
        if ((g_Task->tint.word & ~0xFFU) == (0xC0C0C0U << 8)) {         \
            g_Task->header.flags &= ~0x20;                              \
            g_Task->tint.bytes.flags = 0;                               \
            {                                                           \
                Actor* spad                = g_Task;                    \
                spad->tint.bytes.rgb.blue  = 0;                         \
                spad->tint.bytes.rgb.green = 0;                         \
                spad->tint.bytes.rgb.red   = 0;                         \
            }                                                           \
            g_Task->unk_04 = 0;                                         \
        } else {                                                        \
            g_CurrentActor->unk_7E -= 2;                                \
        }                                                               \
    } while (0)
