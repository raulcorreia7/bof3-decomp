#include "area108_14.h"

MATCH void func_801F3920(void) {
    Actor* task;
    u16    y;

    Camera_ProjectPoint(&TASK(Actor)->pos.x.fixed, (DVECTOR*)D_1F800034);
    TASK(Actor)->screen_x = D_1F800034[0];
    y                     = D_1F800034[1];
    TASK(Actor)->screen_y = y;
    GFX_DrawShadedDisc((s16)TASK(Actor)->screen_x, (s16)y, (s16)TASK(Actor)->unk_18, 0xFF, TASK(Actor)->tint.bytes.flags);
    Area_DrawScreenTint();
    func_801F3C84();
    task = TASK(Actor);
    task->tint.bytes.flags -= 2;
    task->unk_18 -= 0xA;
    if (TASK(Actor)->unk_18 <= 0) {
        g_ScriptVars[0]++;
        TASK(Actor)->header.mode++;
    }
}
