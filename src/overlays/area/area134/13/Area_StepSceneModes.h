/* Run the dispatch dance over the first party record, then set the work mode from the lead actor's
 * position and the scene's script bytes. The dance keeps every write of the work cell (the unit
 * declares it volatile); the mode stores read the cell through its plain view. Both members of
 * area134/13 use it: verify each after a change. */
#define AREA_TASK_PLAIN ((Actor*)*(struct Self**)&g_Self)

#define AREA_STEP_SCENE_MODES(work)                                 \
    work        = SELF(Actor);                                      \
    g_Self      = (void*)g_Actors;                                  \
    g_GameState = g_Game.members;                                   \
    g_Self      = (void*)work;                                      \
    SELF_SET(g_Game.members);                                       \
    g_Self = (void*)work;                                           \
    if (g_Actors[0].pos.x.fixed >= g_Game.members[0].pos.x.fixed) { \
        work->header.mode = 0x16;                                   \
    }                                                               \
    if (g_ScriptVars[2] == 0x80) {                                  \
        AREA_TASK_PLAIN->header.mode = 0x17;                        \
    }                                                               \
    switch (g_ScriptVars[1]) {                                      \
        case 0xFF:                                                  \
            Actor_Clear();                                          \
            break;                                                  \
        case 5:                                                     \
            AREA_TASK_PLAIN->header.mode = 2;                       \
            break;                                                  \
        case 4:                                                     \
            AREA_TASK_PLAIN->header.mode = 4;                       \
            break;                                                  \
        case 3:                                                     \
            AREA_TASK_PLAIN->header.mode = 6;                       \
            break;                                                  \
    }
