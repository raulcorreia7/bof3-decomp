#include "area108_14.h"

MATCH void func_801F384C(void) {
    u16 y;
    u8  timer;

    Camera_ProjectPoint(&SELF(Actor)->pos.x.fixed, (DVECTOR*)D_1F800034);
    SELF(Actor)->screen_x = D_1F800034[0];
    y                     = D_1F800034[1];
    SELF(Actor)->screen_y = y;
    GFX_DrawShadedDisc((s16)SELF(Actor)->screen_x, (s16)y, (s16)SELF(Actor)->unk_18, 0xFF, 0xFF);
    ACTOR_COUNT_DOWN(SELF(Actor), timer, timer);
    if ((timer & BYTE_MASK) == 0) {
        Actor* task;

        task                   = SELF(Actor);
        task->tint.bytes.rgb.b = 0x60;
        task->tint.bytes.rgb.g = 0x60;
        task->tint.bytes.rgb.r = 0x60;
        SELF(Actor)->header.mode++;
    }
}
