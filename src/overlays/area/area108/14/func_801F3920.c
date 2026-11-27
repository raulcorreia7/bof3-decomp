#include "area108_14.h"

MATCH void func_801F3920(void) {
    Actor* task;
    u16    y;

    Camera_ProjectPoint(&SELF(Actor)->pos.x.fixed, (DVECTOR*)D_1F800034);
    SELF(Actor)->screen_x = D_1F800034[0];
    y                     = D_1F800034[1];
    SELF(Actor)->screen_y = y;
    GFX_DrawShadedDisc((s16)SELF(Actor)->screen_x, (s16)y, (s16)SELF(Actor)->unk_18, 0xFF, SELF(Actor)->tint.bytes.flags);
    Area_DrawScreenTint();
    func_801F3C84();
    task = SELF(Actor);
    task->tint.bytes.flags -= 2;
    task->unk_18 -= 0xA;
    if (SELF(Actor)->unk_18 <= 0) {
        g_ScriptVars[0]++;
        SELF(Actor)->header.mode++;
    }
}
