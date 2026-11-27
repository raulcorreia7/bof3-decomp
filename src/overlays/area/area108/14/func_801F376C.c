#include "area108_14.h"

MATCH void func_801F376C(void) {
    Actor* task;
    u16*   screen;
    u16    screen_y;

    screen = (u16*)D_1F800034;
    Camera_ProjectPoint((s32*)&SELF(Actor)->pos, (DVECTOR*)screen);
    SELF(Actor)->screen_x = screen[0];
    screen_y              = screen[1];
    SELF(Actor)->screen_y = screen_y;
    GFX_DrawShadedDisc(SELF(Actor)->screen_x, (s16)screen_y, SELF(Actor)->unk_18, 0xFF, SELF(Actor)->tint.bytes.flags);
    task = SELF(Actor);
    task->tint.bytes.flags += 2;
    task->unk_18 += 5;
    if (SELF(Actor)->unk_18 >= 0x191) {
        SELF(Actor)->timer = 0xF;
        SELF(Actor)->header.mode += 1;
    }
}
