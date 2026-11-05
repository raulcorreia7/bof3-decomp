/* Clears the actor velocity words and sets the game overlay byte to 3. One
 * definition shared by the two world area overlays; every change here must
 * verify every member. */
/* func_801F5108 (area104), func_801F564C (area121) */
MATCH void Actor_StopMoving(void) {
    Actor* work;

    g_GameState->counter_11C.u8_value = 3;
    work                              = g_SpadWork;
    g_AreaCameraStep                  = 0;
    g_AreaCameraHeightStep            = 0;
    work->vx                          = 0;
    work->vy                          = 0;
    work->vz                          = 0;
}
