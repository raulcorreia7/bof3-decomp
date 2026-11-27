/* Clears the actor velocity words and sets the game overlay byte to 3. */
/* func_801F5108 (area104), func_801F564C (area121) */
MATCH void Actor_StopMoving(void) {
    Actor* work;

    g_Game.current->u.field.counter.unsigned_value = 3;
    work                                           = SELF(Actor);
    g_AreaCameraSpeed                              = 0;
    g_AreaCameraHeightDelta                        = 0;
    setVector(work, 0, 0, 0);
}
