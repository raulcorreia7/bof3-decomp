#include "area108_14.h"

MATCH void func_801F376C(void) {
    Actor* task;
    u16*   screen;
    u16    screen_y;

    screen = (u16*)D_1F800034;
    Camera_ProjectPoint((s32*)&TASK(Actor)->pos, (DVECTOR*)screen);
    TASK(Actor)->screen_x = screen[0];
    screen_y              = screen[1];
    TASK(Actor)->screen_y = screen_y;
    GFX_DrawShadedDisc(TASK(Actor)->screen_x, (s16)screen_y, TASK(Actor)->unk_18, 0xFF, TASK(Actor)->tint.bytes.flags);
    task = TASK(Actor);
    task->tint.bytes.flags += 2;
    task->unk_18 += 5;
    if (TASK(Actor)->unk_18 >= 0x191) {
        TASK(Actor)->timer = 0xF;
        TASK(Actor)->header.mode += 1;
    }
}
