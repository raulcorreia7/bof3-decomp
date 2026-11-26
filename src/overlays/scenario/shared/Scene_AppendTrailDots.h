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
    u16       n;                                                                                                                                \
                                                                                                                                                \
    Camera_SetMatrix(&matrix);                                                                                                                  \
    pos[0] = ((Actor*)SELF(Actor)->unk_4C)->pos.x.fixed;                                                                                        \
    pos[1] = ((Actor*)SELF(Actor)->unk_4C)->pos.y.fixed;                                                                                        \
    pos[2] = ((Actor*)SELF(Actor)->unk_4C)->pos.z.fixed;                                                                                        \
    Camera_ProjectPoint(pos, &screen);                                                                                                          \
    for (row = (D_801D393C[D_801D40AC].h >> 1) * SELF(Actor)->timer; row < (D_801D393C[D_801D40AC].h >> 1) * (SELF(Actor)->timer + 1); row++) { \
        for (col = 0; col < D_801D393C[D_801D40AC].w; col++) {                                                                                  \
            if (*D_801D40B0 != 0) {                                                                                                             \
                dot        = D_801D40B4;                                                                                                        \
                dot->color = *D_801D40B0;                                                                                                       \
                dot->x     = screen.vx - D_801D393C[D_801D40AC].x + col;                                                                        \
                D_801D40B4 = dot + 1;                                                                                                           \
                dot->y     = screen.vy - D_801D393C[D_801D40AC].y + row;                                                                        \
                n          = D_801D40A8 + 1;                                                                                                    \
                D_801D40A8 = n;                                                                                                                 \
            }                                                                                                                                   \
            D_801D40B0++;                                                                                                                       \
        }                                                                                                                                       \
    }                                                                                                                                           \
    step               = SELF(Actor)->timer + 1;                                                                                                \
    SELF(Actor)->timer = step;                                                                                                                  \
    if (step == 2) {                                                                                                                            \
        SELF(Actor)->header.mode += 1;                                                                                                          \
    }

#endif
