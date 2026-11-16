#include "area196_13.h"

MATCH void func_801F2E48(void) {
    Actor* work;
    s32    i;
    s32    timer;
    s32    actor;

    g_Task->timer += 1;

    for (i = 0; i < 9; i++) {
        if (D_801F412C[i] == 0) {
            continue;
        }
        D_801F412C[i] = D_801F412C[i] - 2;
        if (D_801F412C[i] >= 0x61) {
            break;
        }
        D_801F412C[i + 1] = D_801F412C[i + 1] - 2;
        if (D_801F412C[i + 1] >= 0x61) {
            break;
        }
        D_801F412C[i + 2] = D_801F412C[i + 2] - 2;
        if (D_801F412C[i + 2] >= 0x61) {
            break;
        }
        D_801F412C[i + 3] = D_801F412C[i + 3] - 2;
        break;
    }

    timer = g_Task->timer;
    if (timer <= 0x60) {
        actor = timer;
    } else {
        actor = 0x60;
    }
    Game_SetCurrentActor(actor);
    g_Task->unk_0A += 4;
    g_Task->unk_0A &= 0x3F;
    func_801F3850();
    if (D_801F4134 == 0) {
        g_Task->timer = 0x60;
        g_Task->header.step += 1;
    }
}
