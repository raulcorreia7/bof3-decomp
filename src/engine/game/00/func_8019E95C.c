#include "game_00.h"

MATCH void func_8019E95C(void) {
    Actor* work;
    Actor* other;

    if ((u8)Area_FindSceneRecord(0x46) != 0) {
        Actor_Clear();
        return;
    }

    g_SpadWork->unk_29   = (u8)(g_SpadWork->unk_29 + 1);
    g_SpadWork->unk_2A   = 0;
    g_SpadWork->flags_24 = 0;
    g_SpadWork->unk_2B   = (u8)(g_SpadWork->unk_2B + 1);
    g_SpadWork->unk_48   = 1;

    work                          = g_SpadWork;
    work->tint.bytes.unk_5D       = 0;
    other                         = g_SpadWork;
    work->vy                      = -0x2000;
    work->vx                      = 0;
    work->vz                      = 0x40;
    other->tint.bytes.unk_5E      = 0;
    g_SpadWork->tint.bytes.unk_5F = 0;
    Actor_SelectScript(0);
    g_SpadWork->state_02 = (u8)(g_SpadWork->state_02 + 1);
}
