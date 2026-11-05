#include "area120_13.h"

MATCH void func_801F2C5C(void) {
    Actor* actor;

    func_801F35B8();
    actor         = g_Task;
    actor->unk_06 = 0;
    actor->unk_32 = 0x78;
    g_Task->mode++;
    SND_PlayCue(0x201);
}
