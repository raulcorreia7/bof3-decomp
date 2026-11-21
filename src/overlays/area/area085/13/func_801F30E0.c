#include "area085_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F30E0(void) {
    Actor* work;
    u8     selector;
    u8     index;
    s16*   scratch;

    g_Task->unk_03 = Actor_FindFreeField();
    if (g_Task->unk_03 == GAME_NONE) {
        return;
    }

    g_Actors[g_Task->unk_03].header.flags = 1;
    g_Task->unk_04                        = Actor_FindFreeField();
    if (g_Task->unk_04 == GAME_NONE) {
        g_Actors[g_Task->unk_03].header.flags = 0;
        return;
    }

    g_Actors[g_Task->unk_04].header.flags = 1;
    work                                  = g_Task;
    if (work->param.unk_0B != 0) {
        selector = g_Game.members[0].unk_4B;
    } else {
        selector = g_Actors[2].script_record;
    }
    for (index = 0; index < 5; index++) {
        if (D_801F3D70[index * 3] == selector) {
            break;
        }
    }

    scratch  = SP_PTR(s16, 0u);
    *scratch = work->unk_03;
    Actor_SpawnFromRecord(D_801F3D4C + work->param.unk_0B * 17);
    Actor_BeginScript(D_801F3D70[index * 3 + 1], D_801F3D70[index * 3 + 2]);
    *scratch = work->unk_04;
    Actor_SpawnFromRecord(D_801F3D4C + work->param.unk_0B * 17);
    Actor_BeginScript(D_801F3D70[index * 3 + 1], D_801F3D70[index * 3 + 2]);
    TASK_SET(work);

    g_Actors[work->unk_03].pos.x.fixed -= ONE;
    g_Actors[work->unk_03].pos.y.fixed += ONE;
    g_Actors[work->unk_04].pos.x.fixed += ONE;
    g_Actors[work->unk_04].pos.y.fixed -= ONE;
    g_Actors[work->unk_03].pos.z.fixed = D_80145ECC;
    g_Actors[work->unk_04].pos.z.fixed = D_80145ECC;
    g_Actors[work->unk_03].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Actors[work->unk_04].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Actors[work->unk_04].tint.bytes.flags = 0;
    g_Actors[work->unk_03].tint.bytes.flags = 0;
    GFX_AllocPaletteFade(&g_Actors[work->unk_03], 15, 0, 0, 1);
    GFX_AllocPaletteFade(&g_Actors[work->unk_04], 0, 0, 15, 1);
    g_Task->timer       = 4;
    g_Task->header.mode = 1;
}
#else
INCLUDE_ASM(func_801F30E0);
#endif
