/* The world map message rows: one per context seed, over the message the scenario id selects. The statement macro
 * starts the message of the row that answers the context seed, then waits for the message to close and clears the
 * scene event. Every change must verify every member. */
/* func_801F2D18 (area033), func_801F2CA8 (area152) */
typedef union WorldMapMessageRow {
    u16 seed;
    s16 messages[16];
} WorldMapMessageRow;

ASSERT_SIZE(WorldMapMessageRow, 0x20);
ASSERT_OFFSET(WorldMapMessageRow, seed, 0x00);
ASSERT_OFFSET(WorldMapMessageRow, messages, 0x00);

#define WORLD_MAP_SHOW_MESSAGE(table, count)                                          \
    {                                                                                 \
        s32                 i;                                                        \
        u16                 seed;                                                     \
        WorldMapMessageRow* rows;                                                     \
        s8*                 step;                                                     \
        u8*                 counter;                                                  \
                                                                                      \
        step = &g_SceneEventState.step;                                               \
        switch (*step) {                                                              \
            case 0:                                                                   \
                Game_SetScriptActive();                                               \
                seed = g_GameContextSeed;                                             \
                for (i = 0; i < (count); i++) {                                       \
                    if (seed == (table)[i].seed) {                                    \
                        break;                                                        \
                    }                                                                 \
                }                                                                     \
                rows = (table);                                                       \
                Message_StartAreaMessage(rows[i].messages[g_SceneState.scenario_id]); \
                g_GameStateIndex = 2;                                                 \
                counter          = (u8*)&g_SceneEventState.step;                      \
                *counter += 1;                                                        \
                break;                                                                \
                                                                                      \
            case 1:                                                                   \
                if (g_GameStateIndex != 2) {                                          \
                    Game_ClearScriptActive();                                         \
                    g_SceneEventState.mode      = 0;                                  \
                    *step                       = 0;                                  \
                    g_SceneEventState.selection = 0;                                  \
                }                                                                     \
                break;                                                                \
        }                                                                             \
    }
