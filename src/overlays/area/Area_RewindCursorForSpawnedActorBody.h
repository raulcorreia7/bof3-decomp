/* Rewinds the script cursor when the spawned actor at (0x41, 0x3A) is in use, or when the first party member is in field mode 0x12B; otherwise calls func_801BE1B0(0). */
/* func_801F30E8 (area095/13), func_801F3078 (area096/13) */
#define AREA_REWIND_CURSOR_FOR_SPAWNED_ACTOR_BODY()                                                                                                                    \
    u8 i;                                                                                                                                                              \
                                                                                                                                                                       \
    for (i = 0; i < ACTOR_SLOT_COUNT; i++) {                                                                                                                           \
        if ((g_SpawnedActors[i].header.flags & ACTOR_FLAG_IN_USE) && g_SpawnedActors[i].pos.x.part.integer == 0x41 && g_SpawnedActors[i].pos.y.part.integer == 0x3A) { \
            break;                                                                                                                                                     \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
    if (i != ACTOR_SLOT_COUNT) {                                                                                                                                       \
        g_ScriptState->cursor -= 2;                                                                                                                                    \
    } else if (g_Game.members[0].u.field.mode_12B.u8_value != 0) {                                                                                                     \
        g_ScriptState->cursor -= 2;                                                                                                                                    \
        Game_SetScriptActive();                                                                                                                                        \
    } else {                                                                                                                                                           \
        func_801BE1B0(0);                                                                                                                                              \
    }
