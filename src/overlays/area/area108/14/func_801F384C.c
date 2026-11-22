#include "area108_14.h"

MATCH void func_801F384C(void) {
    u16 y;
    u8  timer;

    Camera_ProjectPoint(&TASK(Actor)->pos.x.fixed, (DVECTOR*)D_1F800034);
    TASK(Actor)->screen_x = D_1F800034[0];
    y                     = D_1F800034[1];
    TASK(Actor)->screen_y = y;
    GFX_DrawShadedDisc((s16)TASK(Actor)->screen_x, (s16)y, (s16)TASK(Actor)->unk_18, 0xFF, 0xFF);
    ACTOR_COUNT_DOWN(TASK(Actor), timer, timer);
    if ((timer & BYTE_MASK) == 0) {
        Actor* task;

        task                   = TASK(Actor);
        task->tint.bytes.rgb.b = 0x60;
        task->tint.bytes.rgb.g = 0x60;
        task->tint.bytes.rgb.r = 0x60;
        TASK(Actor)->header.mode++;
    }
}
