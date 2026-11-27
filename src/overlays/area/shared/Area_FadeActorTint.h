/* Shared by area172/13/func_801F47F0.c and area141/13/func_801F390C.c; verify both images after changes. */
#define AREA_FADE_ACTOR_TINT_BODY(increment)                        \
    do {                                                            \
        s8     tintA;                                               \
        s8     tintB;                                               \
        s8     tintC;                                               \
        Actor* spad;                                                \
        Actor* spad2;                                               \
                                                                    \
        spad = g_Self;                                              \
        spad->pos.x.fixed += spad->vx;                              \
        spad->pos.y.fixed += spad->vy;                              \
        tintA = spad->tint.steps.delta.r;                           \
        if (tintA < -0x40) {                                        \
            spad->tint.steps.delta.r = tintA + (increment);         \
        }                                                           \
        spad2 = g_Self;                                             \
        tintB = spad2->tint.steps.delta.g;                          \
        if (tintB < -0x40) {                                        \
            spad2->tint.steps.delta.g = tintB + (increment);        \
            spad2                     = g_Self;                     \
        }                                                           \
        tintC = spad2->tint.steps.delta.b;                          \
        if (tintC < -0x40) {                                        \
            spad2->tint.steps.delta.b = tintC + (increment);        \
        }                                                           \
        if ((SELF(Actor)->tint.raw & ~0xFFU) == (0xC0C0C0U << 8)) { \
            SELF(Actor)->header.flags &= ~0x20;                     \
            SELF(Actor)->tint.bytes.flags = 0;                      \
            {                                                       \
                Actor* spad            = g_Self;                    \
                spad->tint.bytes.rgb.b = 0;                         \
                spad->tint.bytes.rgb.g = 0;                         \
                spad->tint.bytes.rgb.r = 0;                         \
            }                                                       \
            SELF(Actor)->unk_04 = 0;                                \
        } else {                                                    \
            g_CurrentActor->unk_7E -= 2;                            \
        }                                                           \
    } while (0)
