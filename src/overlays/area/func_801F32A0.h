/* Centres the actor on screen and arms the actor step fields unless the entry
 * state is 1 and the step matches its previous value, then adds the actor. One
 * definition shared by the area overlays; every change here must verify every
 * member. */
/* func_801F32A0 (area016), func_801F32A0 (area045) */
MATCH void func_801F32A0(void) {
    Actor* scratch;
    u8     step;

    Actor_CenterOnScreen();
    if (g_GameEntryState != 1) {
        scratch = g_SpadWork;
        step    = scratch->unk_0B;
        if (step == scratch->option_flags && g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) {
            if (step != 1) {
                goto tail; /* skips the arming stores: run the step only */
            }
            if (scratch->unk_18 == g_GameContextSeed) {
                goto tail; /* skips the arming stores: run the step only */
            }
        }
        g_SpadWork->unk_48 = 2;
        g_SpadWork->unk_09 = 8;
        g_SpadWork->unk_01 = 4;
    }
tail:
    Area_AddActor();
}
