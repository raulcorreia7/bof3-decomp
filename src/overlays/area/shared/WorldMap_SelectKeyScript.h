/* Selects the script of a world-map scene from its key table: the entry area's row on step 1, a fixed mode on steps 2 to 4; every change must verify every member. */
/* A member declares the locals: Actor* scratch, Actor* check, s32 key, FAKE_REG(u32, i, "a1"), u32 next, u32 mode, u8 state, u32 window, u32 window_span. */
#define WORLD_MAP_SELECT_KEY_SCRIPT(keys)                      \
    scratch               = g_Self;                            \
    scratch->option_flags = scratch->param.unk_0B;             \
                                                               \
    check = g_Self;                                            \
    if (check->param.unk_0B == 1) {                            \
        key = g_GameEntryAreaId;                               \
        i   = 0;                                               \
    scan:                                                      \
        next = i;                                              \
        if (key == MEM(WorldMapKey, (u8*)(keys) + next).key) { \
            goto found;                                        \
        }                                                      \
        i = next + 4;                                          \
        goto scan;                                             \
    } else {                                                   \
        scratch = g_Self;                                      \
        state   = scratch->param.unk_0B;                       \
        if (state == 2) {                                      \
            mode = 3;                                          \
            goto arm;                                          \
        }                                                      \
        if (state == 3) {                                      \
            mode = 0;                                          \
            goto arm;                                          \
        }                                                      \
        goto check4;                                           \
    }                                                          \
                                                               \
    found:                                                     \
    window_span      = 0x10000;                                \
    scratch          = g_Self;                                 \
    window           = 2;                                      \
    scratch->unk_18  = key;                                    \
    scratch->scale.x = 0;                                      \
    scratch->scale.y = window_span;                            \
    scratch->unk_48  = window;                                 \
    scratch          = g_Self;                                 \
    scratch->timer   = 8;                                      \
    mode             = MEM(WorldMapKey, (u8*)(keys) + i).mode; \
    goto tail;                                                 \
                                                               \
    check4:                                                    \
    if (state == 4) {                                          \
        mode = 1;                                              \
    } else {                                                   \
        return;                                                \
    }                                                          \
                                                               \
    arm:                                                       \
    window_span      = 0x10000;                                \
    scratch->scale.x = 0;                                      \
    scratch->scale.y = window_span;                            \
    window           = 2;                                      \
    scratch->unk_48  = window;                                 \
    scratch          = g_Self;                                 \
    scratch->timer   = 8;                                      \
    tail:                                                      \
    Script_Select(mode);                                       \
                                                               \
    check              = g_Self;                               \
    check->header.mode = window;
