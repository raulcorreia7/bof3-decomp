#ifndef SCENARIO_SCENE_ADVANCE_BAND_MOTION_H
#define SCENARIO_SCENE_ADVANCE_BAND_MOTION_H

/* Runs one frame of the scene band: the work velocity steps by its acceleration, with the sign choosing
 * the direction, then the camera matrix is rebuilt, the caller's projector steps the band at the work
 * position with the velocity, and the countdown advances the mode when it ends. A statement macro: the
 * declarations must start the function body. */
/* func_801F8BC4 (scena15), func_801F8F4C (scena15) */
#define SCENE_ADVANCE_BAND_MOTION(ADD, PROJECT)                                                        \
    MATRIX matrix;                                                                                     \
    Actor* work;                                                                                       \
    Actor* actor;                                                                                      \
    u8     timer;                                                                                      \
                                                                                                       \
    work = g_Self;                                                                                     \
    setVector(work, work->vx ADD work->unk_18, work->vy ADD work->unk_1C, work->vz ADD work->gravity); \
                                                                                                       \
    Camera_SetMatrix(&matrix);                                                                         \
                                                                                                       \
    actor = g_Self;                                                                                    \
    PROJECT(&actor->pos.x, &actor->vx);                                                                \
                                                                                                       \
    timer              = SELF(Actor)->timer - 1;                                                       \
    SELF(Actor)->timer = timer;                                                                        \
    if (timer == 0) {                                                                                  \
        SELF(Actor)->header.mode++;                                                                    \
    }

#endif
