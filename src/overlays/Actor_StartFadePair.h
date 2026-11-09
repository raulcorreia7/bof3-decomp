/* Takes two free actors, passes each to func_801A4D54 with DATA, moves them one unit apart diagonally, makes both semi-transparent and starts palette fades (15, 0, 0) on the first and (0, 0, 15) on the second; sets the timer to 4 and mode 1. Returns if no actor is free. */
/* ACTOR_START_FADE_PAIR (area032 0x801F30EC, scena03 0x801F754C) */
#define ACTOR_START_FADE_PAIR(DATA)                                       \
    Actor* work;                                                          \
    u8*    data;                                                          \
    Actor* cell;                                                          \
    u8     cell4;                                                         \
    u32    cell3;                                                         \
    s16*   scratch;                                                       \
    g_Task->unk_03 = Actor_FindFree();                                    \
    if (g_Task->unk_03 == GAME_NONE) {                                    \
        return;                                                           \
    }                                                                     \
    g_Actors[g_Task->unk_03].header.flags = 1;                            \
    g_Task->unk_04                        = Actor_FindFree();             \
    if (g_Task->unk_04 == GAME_NONE) {                                    \
        g_Actors[g_Task->unk_03].header.flags = 0;                        \
        return;                                                           \
    }                                                                     \
    scratch                               = (s16*)D_1F800000;             \
    data                                  = (u8*)DATA;                    \
    g_Actors[g_Task->unk_04].header.flags = 1;                            \
    work                                  = g_Task;                       \
    *scratch                              = work->unk_03;                 \
    func_801A4D54(data);                                                  \
    *scratch = work->unk_04;                                              \
    func_801A4D54(data);                                                  \
    SP_REF(Actor*, 0x44) = work;                                          \
    g_Actors[work->unk_03].pos.x.fixed -= ONE;                            \
    g_Actors[work->unk_03].pos.y.fixed += ONE;                            \
    g_Actors[work->unk_04].pos.x.fixed += ONE;                            \
    g_Actors[work->unk_04].pos.y.fixed -= ONE;                            \
    g_Actors[work->unk_03].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;   \
    g_Actors[g_Task->unk_04].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT; \
    cell                                     = g_Task;                    \
    cell4                                    = cell->unk_04;              \
    cell3                                    = cell->unk_03;              \
    FIELD(u8, D_801468E4, cell4* ACTOR_SIZE) = 0;                         \
    FIELD(u8, D_801468E4, cell3* ACTOR_SIZE) = 0;                         \
    GFX_AllocPaletteFade(&g_Actors[work->unk_03], 15, 0, 0, 1);           \
    GFX_AllocPaletteFade(&g_Actors[work->unk_04], 0, 0, 15, 1);           \
    g_Task->timer       = 4;                                              \
    g_Task->header.mode = 1;
