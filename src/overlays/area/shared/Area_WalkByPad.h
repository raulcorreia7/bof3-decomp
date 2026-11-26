/* The walking step of the lead actor: after the gates (script, entry, menu) it turns by the pad, limits
 * a turn to one facing step, then walks, runs the panel or stops. The three arguments are the image's
 * own gate, interrupt and blocked-step functions. Members: area104/14 func_801F4608, area121/14
 * func_801F4B4C; verify both after a change. */
#define AREA_WALK_BY_PAD(is_held, is_interrupted, on_blocked)                                                                                         \
    {                                                                                                                                                 \
        u8     saved_facing;                                                                                                                          \
        u8     current_facing;                                                                                                                        \
        u8     candidate_facing;                                                                                                                      \
        u8     adjusted_facing;                                                                                                                       \
        Actor* task;                                                                                                                                  \
        Actor* panel_task;                                                                                                                            \
        Actor* moving_task;                                                                                                                           \
                                                                                                                                                      \
        if (is_held() & 0xFF) {                                                                                                                       \
            return;                                                                                                                                   \
        }                                                                                                                                             \
        if (g_Game.flags & GAME_FLAG_SCRIPT_ACTIVE) {                                                                                                 \
            return;                                                                                                                                   \
        }                                                                                                                                             \
        if (g_Game.walk_flags & AREA_WALK_ENTRY_PENDING) {                                                                                            \
            return;                                                                                                                                   \
        }                                                                                                                                             \
        if (g_GameStateIndex != GAME_REQUEST_IDLE) {                                                                                                  \
            return;                                                                                                                                   \
        }                                                                                                                                             \
        if (SELF(Actor)->unk_0A != 0) {                                                                                                               \
            return;                                                                                                                                   \
        }                                                                                                                                             \
        if (g_Game.input != 0 && !(g_Characters[g_Game.current->character_index].status & STATUS_CONFUSED)) {                                         \
            g_Game.current->u.field.step.value = 0;                                                                                                   \
        }                                                                                                                                             \
        if (func_801B6674() & 0xFF) {                                                                                                                 \
            return;                                                                                                                                   \
        }                                                                                                                                             \
        if (Game_RequestMenuOnInput() & 0xFF) {                                                                                                       \
            return;                                                                                                                                   \
        }                                                                                                                                             \
        if (func_801B6258() & 0xFF) {                                                                                                                 \
            return;                                                                                                                                   \
        }                                                                                                                                             \
        if (is_interrupted() & 0xFF) {                                                                                                                \
            return;                                                                                                                                   \
        }                                                                                                                                             \
        saved_facing = SELF(Actor)->direction;                                                                                                        \
        if ((!(Actor_TurnByPad() & 0xFF) && !(g_PadStates[0].held & g_InputMasks[WORLD_INPUT_RUN])) || (task = g_Self, task->param.unk_0B == 0x40)) { \
            SELF(Actor)->direction             = saved_facing;                                                                                        \
            g_Game.current->u.field.mode.value = 0;                                                                                                   \
            Actor_StopMoving();                                                                                                                       \
            goto stop;                                                                                                                                \
        }                                                                                                                                             \
        if (g_PadStates[0].held & g_InputMasks[WORLD_INPUT_RUN]) {                                                                                    \
            task->direction = saved_facing;                                                                                                           \
        }                                                                                                                                             \
        current_facing = SELF(Actor)->direction;                                                                                                      \
        if (current_facing != saved_facing) {                                                                                                         \
            adjusted_facing  = current_facing;                                                                                                        \
            candidate_facing = saved_facing;                                                                                                          \
            if (abs((s8)saved_facing - (s8)adjusted_facing) >= 3) {                                                                                   \
                if ((s8)saved_facing < (s8)adjusted_facing) {                                                                                         \
                    candidate_facing = saved_facing + 8;                                                                                              \
                } else {                                                                                                                              \
                    adjusted_facing += 8;                                                                                                             \
                }                                                                                                                                     \
            }                                                                                                                                         \
            if (abs((s8)candidate_facing - (s8)adjusted_facing) == 2) {                                                                               \
                if ((s8)adjusted_facing < (s8)candidate_facing) {                                                                                     \
                    SELF(Actor)->direction = saved_facing - 1;                                                                                        \
                } else {                                                                                                                              \
                    SELF(Actor)->direction = saved_facing + 1;                                                                                        \
                }                                                                                                                                     \
            }                                                                                                                                         \
            SELF(Actor)->direction &= 7;                                                                                                              \
        }                                                                                                                                             \
        switch (func_801B0E44() & 0xFF) {                                                                                                             \
            case 0:                                                                                                                                   \
                if ((s8)func_801BDF08() != 0) {                                                                                                       \
                    g_Game.current->u.field.mode.value = 0;                                                                                           \
                    SELF(Actor)->header.step           = 0;                                                                                           \
                    on_blocked();                                                                                                                     \
                    return;                                                                                                                           \
                }                                                                                                                                     \
                Area_UpdatePanelRun();                                                                                                                \
                if (g_Game.current->u.field.counter.unsigned_value == 4 && (panel_task = g_Self, panel_task->direction != saved_facing)) {            \
                    panel_task->direction              = saved_facing;                                                                                \
                    g_Game.current->u.field.mode.value = 0;                                                                                           \
                    break;                                                                                                                            \
                }                                                                                                                                     \
                Area_RunWalk();                                                                                                                       \
                func_801C4C48();                                                                                                                      \
                moving_task = g_Self;                                                                                                                 \
                moving_task->timer--;                                                                                                                 \
                func_801B0DFC();                                                                                                                      \
                g_Game.current->u.field.mode.value = 1;                                                                                               \
                SELF(Actor)->header.step           = 1;                                                                                               \
                return;                                                                                                                               \
            case 1:                                                                                                                                   \
            case 0xFF:                                                                                                                                \
                SELF(Actor)->direction                         = saved_facing;                                                                        \
                g_Game.current->u.field.mode.value             = 0;                                                                                   \
                g_Game.current->u.field.counter.unsigned_value = 3;                                                                                   \
            stop:                                                                                                                                     \
                SELF(Actor)->timer = 0;                                                                                                               \
                break;                                                                                                                                \
            default:                                                                                                                                  \
                return;                                                                                                                               \
        }                                                                                                                                             \
        SELF(Actor)->header.step = 0;                                                                                                                 \
    }
