/* Adds one to D_801448EC unless the game is in state 2. One definition
 * shared by the commu overlays; every change here must verify every member. */
/* func_801D5A9C (commu02/08), func_801D1670 (commu04/06), func_801D121C (commu03/06); the second copy in commu02/08,
   Commu_AdvanceStep_801D7E30, uses the statements macro */
#define COMMU_ADVANCE_STEP()                            \
    do {                                                \
        u8* state;                                      \
                                                        \
        if (g_GameStateIndex != GAME_REQUEST_MESSAGE) { \
            state = &D_801448EC;                        \
            *state += 1;                                \
        }                                               \
    } while (0)

MATCH void Commu_AdvanceStep(void) {
    COMMU_ADVANCE_STEP();
}
