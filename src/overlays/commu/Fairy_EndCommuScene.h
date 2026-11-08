/* Ends a commu scene: adds one to g_SceneEventStep unless a message is requested. One definition
 * shared by the commu overlays; every change here must verify every member. */
/* func_801D5A9C (commu02/08), func_801D1670 (commu04/06), func_801D121C (commu03/06); the second copy in commu02/08,
   Fairy_EndCommuSceneEvent3, uses the statements macro */
#define COMMU_ADVANCE_STEP()                            \
    do {                                                \
        u8* state;                                      \
                                                        \
        if (g_GameStateIndex != GAME_REQUEST_MESSAGE) { \
            state = &g_SceneEventStep;                  \
            *state += 1;                                \
        }                                               \
    } while (0)

MATCH void Fairy_EndCommuScene(void) {
    COMMU_ADVANCE_STEP();
}
