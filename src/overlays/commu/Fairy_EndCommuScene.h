/* Ends a commu scene: adds one to g_SceneEventState.step unless a message is requested. */
/* func_801D5A9C (commu02/08), func_801D1670 (commu04/06), func_801D121C (commu03/06); the second copy in commu02/08,
   Fairy_EndCommuSceneEvent3, uses the statements macro */
#define COMMU_ADVANCE_STEP()                            \
    do {                                                \
        u8* state;                                      \
                                                        \
        if (g_GameStateIndex != GAME_REQUEST_MESSAGE) { \
            state = &g_SceneEventState.step;            \
            *state += 1;                                \
        }                                               \
    } while (0)

MATCH void Fairy_EndCommuScene(void) {
    COMMU_ADVANCE_STEP();
}
