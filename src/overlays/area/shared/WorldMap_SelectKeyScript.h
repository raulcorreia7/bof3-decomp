/* Selects the script of a world-map scene from its WorldMapKey table: on step 1 the mode of the row whose key is g_GameEntryAreaId, on steps 2 to 4 a fixed mode; every change must verify every member. */
/* A member declares the locals: Actor* scratch, s32 i, u32 key, u8 state, u8 next_step, s32 full_scale. */
#define WORLD_MAP_SELECT_KEY_SCRIPT(keys)             \
    scratch               = SELF(Actor);              \
    scratch->option_flags = scratch->param.unk_0B;    \
                                                      \
    if (SELF(Actor)->param.unk_0B == 1) {             \
        key = g_GameEntryAreaId;                      \
        for (i = 0;; i++) {                           \
            if (key == (keys)[i].key) {               \
                full_scale       = 0x10000;           \
                scratch          = SELF(Actor);       \
                next_step        = 2;                 \
                scratch->unk_18  = key;               \
                scratch->scale.x = 0;                 \
                scratch->scale.y = full_scale;        \
                scratch->unk_48  = next_step;         \
                scratch          = SELF(Actor);       \
                scratch->timer   = 8;                 \
                Script_Select((keys)[i].mode);        \
                SELF(Actor)->header.mode = next_step; \
                return;                               \
            }                                         \
        }                                             \
    }                                                 \
    scratch = SELF(Actor);                            \
    state   = scratch->param.unk_0B;                  \
    if (state == 2) {                                 \
        state = 3;                                    \
    } else if (state == 3) {                          \
        state = 0;                                    \
    } else if (state == 4) {                          \
        state = 1;                                    \
    } else {                                          \
        return;                                       \
    }                                                 \
    full_scale       = 0x10000;                       \
    scratch->scale.x = 0;                             \
    scratch->scale.y = full_scale;                    \
    next_step        = 2;                             \
    scratch->unk_48  = next_step;                     \
    scratch          = SELF(Actor);                   \
    scratch->timer   = 8;                             \
    Script_Select(state);                             \
    SELF(Actor)->header.mode = next_step;
