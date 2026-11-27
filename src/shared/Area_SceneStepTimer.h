/* Tick the scene timer and run AREA_SCENE_TIMER_EXPIRED or the motion update. */
/* func_80167800 (slus), func_801BC3B8 (game) */
MATCH void Area_SceneStepTimer(void) {
    Actor* work;
    u8     timer;

    work  = SELF(Actor);
    timer = work->timer;
    if (timer == 0) {
        AREA_SCENE_TIMER_EXPIRED();
        return;
    }
    work->timer = timer - 1;
    Actor_MovementUpdate();
}
