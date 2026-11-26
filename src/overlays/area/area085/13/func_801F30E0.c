#include "area085_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F30E0(void) {
    Actor* work;
    u8     selector;
    u8     index;
    s16*   scratch;

    TASK(Actor)->unk_03 = Actor_FindFreeField();
    if (TASK(Actor)->unk_03 == GAME_NONE) {
        return;
    }

    g_Actors[TASK(Actor)->unk_03].header.flags = 1;
    TASK(Actor)->unk_04                        = Actor_FindFreeField();
    if (TASK(Actor)->unk_04 == GAME_NONE) {
        g_Actors[TASK(Actor)->unk_03].header.flags = 0;
        return;
    }

    g_Actors[TASK(Actor)->unk_04].header.flags = 1;
    work                                       = g_Task;
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

    scratch  = (s16*)&g_ScratchPad;
    *scratch = work->unk_03;
    Actor_SpawnFromRecord(D_801F3D4C + work->param.unk_0B * 17);
    Script_Begin(D_801F3D70[index * 3 + 1], D_801F3D70[index * 3 + 2]);
    *scratch = work->unk_04;
    Actor_SpawnFromRecord(D_801F3D4C + work->param.unk_0B * 17);
    Script_Begin(D_801F3D70[index * 3 + 1], D_801F3D70[index * 3 + 2]);
    TASK_SET(work);

    g_Actors[work->unk_03].pos.x.fixed -= ONE;
    g_Actors[work->unk_03].pos.y.fixed += ONE;
    g_Actors[work->unk_04].pos.x.fixed += ONE;
    g_Actors[work->unk_04].pos.y.fixed -= ONE;
    g_Actors[work->unk_03].pos.z.fixed = g_Actors[work->unk_04].pos.z.fixed = g_Game.members[0].pos.z.fixed;
    g_Actors[work->unk_03].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Actors[TASK(Actor)->unk_04].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Actors[TASK(Actor)->unk_03].tint.bytes.flags = g_Actors[TASK(Actor)->unk_04].tint.bytes.flags = 0;
    GFX_PaletteAllocFade(&g_Actors[work->unk_03], 15, 0, 0, 1);
    GFX_PaletteAllocFade(&g_Actors[work->unk_04], 0, 0, 15, 1);
    TASK(Actor)->timer       = 4;
    TASK(Actor)->header.mode = 1;
}
#else
INCLUDE_ASM(func_801F30E0);
#endif
