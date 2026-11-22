#ifndef SHARED_SCENE_APPEND_TRAIL_DOTS_H
#define SHARED_SCENE_APPEND_TRAIL_DOTS_H

/* Appends the frame's capture pixels to the dot trail: projects the capture once, then adds one
 * dot per lit palette pixel of the capture row the timer picks. A statement macro: the
 * declarations must start the function body. */
/* func_801D2474 (sce15ef1), func_801D30AC (sce15ef1) */
#define SCENE_APPEND_TRAIL_DOTS()                                                                                                               \
    s32       pos[3];                                                                                                                           \
    DVECTOR   screen;                                                                                                                           \
    MATRIX    matrix;                                                                                                                           \
    TrailDot* dot;                                                                                                                              \
    u8        row;                                                                                                                              \
    u8        col;                                                                                                                              \
    u8        step;                                                                                                                             \
    /* FAKE: retail keeps the dot count in a1. */                                                                                               \
    FAKE_REG(u16, n, "a1");                                                                                                                     \
                                                                                                                                                \
    Camera_SetMatrix(&matrix);                                                                                                                  \
    pos[0] = ((Actor*)TASK(Actor)->unk_4C)->pos.x.fixed;                                                                                        \
    pos[1] = ((Actor*)TASK(Actor)->unk_4C)->pos.y.fixed;                                                                                        \
    pos[2] = ((Actor*)TASK(Actor)->unk_4C)->pos.z.fixed;                                                                                        \
    Camera_ProjectPoint(pos, &screen);                                                                                                          \
    for (row = (D_801D393C[D_801D40AC].h >> 1) * TASK(Actor)->timer; row < (D_801D393C[D_801D40AC].h >> 1) * (TASK(Actor)->timer + 1); row++) { \
        for (col = 0; col < D_801D393C[D_801D40AC].w; col++) {                                                                                  \
            if (*(u16*)D_801D40B0 != 0) {                                                                                                       \
                dot = (TrailDot*)D_801D40B4;                                                                                                    \
                /* FAKE: the dot and count loads swap without the lock; best plain form is 4 rows off. */                                       \
                FAKE_ORDER_LOCK_BEGIN                                                                                                           \
                    n          = D_801D40A8;                                                                                                    \
                    dot->color = *(u16*)D_801D40B0;                                                                                             \
                    n++;                                                                                                                        \
                    D_801D40A8 = n;                                                                                                             \
                    dot->x     = screen.vx - D_801D393C[D_801D40AC].x + col;                                                                    \
                    D_801D40B4 = (u32)(dot + 1);                                                                                                \
                    dot->y     = screen.vy - D_801D393C[D_801D40AC].y + row;                                                                    \
                FAKE_ORDER_LOCK_END;                                                                                                            \
            }                                                                                                                                   \
            D_801D40B0 += 2;                                                                                                                    \
        }                                                                                                                                       \
    }                                                                                                                                           \
    step               = TASK(Actor)->timer + 1;                                                                                                \
    TASK(Actor)->timer = step;                                                                                                                  \
    if (step == 2) {                                                                                                                            \
        TASK(Actor)->header.mode += 1;                                                                                                          \
    }

#endif
