#include "area174_13.h"

/* func_801F2EC4 */
MATCH u8 Area_UpdateShots(void) {
    MATRIX    camera;
    AreaShot* shot;
    Actor*    work;
    u8        active;
    u16       i;
    u8        life;

    active = 0;
    Area_SetCameraMatrix(&camera);
    shot = MEM_PTR(AreaShot, AREA_WORK);
    i    = 0;
    do {
        if (shot->active != 0) {
            active = 1;
            work   = g_Task;
            shot->pos.x.fixed += shot->velocity.x;
            shot->pos.y.fixed += shot->velocity.y;
            shot->pos.z.fixed += shot->velocity.z;
            shot->angle = func_801F3320(&work->pos.x.fixed, &work->vx);
            life        = shot->timer - 1;
            shot->timer = life;
            if (life == 0 || shot->pos.x.fixed >= D_80147A8C - TO_COORD(1)) {
                shot->active = 0;
            }
            func_801F2FEC(&shot->pos.x.fixed, shot->unk_08, shot->unk_0A, shot->angle, 128, 0);
        }
        shot++;
        i++;
    } while (i < 32);
    return active;
}
