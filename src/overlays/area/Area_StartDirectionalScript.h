/* Selects the actor script for the current direction; verify both area images. */
MATCH void Area_StartDirectionalScript(Actor* actor) {
    u8 direction;

    g_ScriptState->unk_04 = 1;
    direction             = g_Task->direction_08 & 7;
    g_ScriptState->flag_00 |= 0x40;
    g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    Actor_SelectScript(direction | 8);
    g_ScriptState->unk_07 = 2;
    if (direction == 7) {
        direction = 3;
        Area_MoveActorRoute(g_ScriptState, 3);
    } else {
        direction = 7;
        Area_MoveActorRoute(g_ScriptState, 7);
    }
    g_Task->direction_08 = direction;
}
