/* Tick the scene timer and run the expiry reset or the motion update. each image includes this file where the function sits. */
/* func_80167800 (slus), func_801BC3B8 (game) */
MATCH void Area_StepSceneTimer(void) {
    Actor* work;
    u8     timer;

    work  = g_Task;
    timer = work->timer;
    if (timer == 0) {
        Area_ResetScene();
        return;
    }
    work->timer = timer - 1;
    func_801B0DFC();
}
