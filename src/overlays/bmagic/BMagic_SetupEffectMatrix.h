/* Sets up the effect matrix from the task position and frame. */
/* func_801EF2F0 (magic158), func_801EF284 (magic166) */
#define BMAGIC_SETUP_EFFECT_MATRIX()                                           \
    SVECTOR      pos;                                                          \
    SVECTOR      rot;                                                          \
    MATRIX       matrix;                                                       \
    long         flags;                                                        \
    PartyMember* work;                                                         \
    s32          roll;                                                         \
                                                                               \
    PushMatrix();                                                              \
    work   = g_Task;                                                           \
    rot.vx = 0x400;                                                            \
    rot.vy = 0xE00;                                                            \
    if (work->param.unk_0B & 1) {                                              \
        roll = g_FrameCount ^ 0x1F;                                            \
    } else {                                                                   \
        roll = g_FrameCount;                                                   \
    }                                                                          \
    rot.vz = (roll & 0x1F) << 7;                                               \
    FAKE_BARRIER(); /* FAKE: keeps the roll store before the position load. */ \
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;                              \
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;                              \
    pos.vz = -COORD_INT(g_Task->pos.z) / 2;                                    \
    RotTrans(&pos, (VECTOR*)matrix.t, &flags);                                 \
    RotMatrix(&rot, &matrix);                                                  \
    MulMatrix2(&g_CameraMatrix, &matrix);                                      \
    SetRotMatrix(&matrix);                                                     \
    SetTransMatrix(&matrix)
