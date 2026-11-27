/* Selects the actor script for the current direction; verify both area images. */
MATCH void Area_StartDirectionalScript(Actor* actor) {
    u8 direction;

    g_ScriptState->move_mode = 1;
    direction                = SELF(Actor)->direction & 7;
    g_ScriptState->flags |= 0x40;
    SELF(Actor)->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    Script_Select(direction | 8);
    g_ScriptState->steps = 2;
    if (direction == 7) {
        direction = 3;
        Area_MoveActorRoute(g_ScriptState, 3);
    } else {
        direction = 7;
        Area_MoveActorRoute(g_ScriptState, 7);
    }
    SELF(Actor)->direction = direction;
}
