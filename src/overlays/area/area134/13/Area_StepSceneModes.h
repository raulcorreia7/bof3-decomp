/* Run the dispatch dance over the first party record, then set the work mode from the lead actor's
 * position and the scene's script bytes. The party record goes into the cell through its untyped view,
 * which keeps the write the next one overwrites. Both members of area134/13 use it: verify each after a
 * change. */
#define AREA_TASK_PLAIN ((Actor*)*(struct Task**)&g_Task)

#define AREA_STEP_SCENE_MODES(work)                                 \
    work             = TASK(Actor);                                 \
    g_Task           = (void*)g_Actors;                             \
    g_GameState      = g_Game.members;                              \
    g_Task           = (void*)work;                                 \
    *(void**)&g_Task = g_Game.members;                              \
    g_Task           = (void*)work;                                 \
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
