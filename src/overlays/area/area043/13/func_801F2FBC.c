#include "area043_13.h"

MATCH void func_801F2FBC(void) {
    Actor* work;

    func_80196718(g_Task);
    Area_SceneSelectRecord(0x1BD);
    Script_Select(0);
    TASK(Actor)->mirror           = 0;
    TASK(Actor)->scale.x          = 57344;
    TASK(Actor)->scale.y          = 57344;
    g_CurrentActor->unk_93        = func_8019651C(TASK(u8), 0, 0, 0, 1);
    TASK(Actor)->tint.bytes.flags = 1;
    work                          = TASK(Actor);
    work->tint.steps.delta.b      = 0x14;
    work->tint.steps.delta.g      = 0x14;
    work->tint.steps.delta.r      = 0x14;
    TASK(Actor)->unk_2B           = 3;
}
