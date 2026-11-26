#include "area085_13.h"

/* Spawns two actors from D_801F3D4C and starts the script D_801F3D70 picks for the party's selector. */
MATCH void func_801F30E0(void) {
    Actor* work;
    u8     selector;
    u8     index;
    s16*   scratch;

    SELF(Actor)->unk_03 = Actor_FindFreeField();
    if (SELF(Actor)->unk_03 == GAME_NONE) {
        return;
    }

    g_Actors[SELF(Actor)->unk_03].header.flags = 1;
    SELF(Actor)->unk_04                        = Actor_FindFreeField();
    if (SELF(Actor)->unk_04 == GAME_NONE) {
        g_Actors[SELF(Actor)->unk_03].header.flags = 0;
        return;
    }

    g_Actors[SELF(Actor)->unk_04].header.flags = 1;
    work                                       = g_Self;
    if (work->param.unk_0B != 0) {
        selector = g_Game.members[0].unk_4B;
    } else {
        selector = g_Actors[2].script_record;
    }
    for (index = 0; index < 5; index++) {
        if (selector == D_801F3D70[index].selector) {
            break;
        }
    }

    scratch  = (s16*)&g_ScratchPad;
    *scratch = work->unk_03;
    Actor_SpawnFromRecord(D_801F3D4C + work->param.unk_0B * 17);
    Script_Begin(D_801F3D70[index].script_index, D_801F3D70[index].position);
    *scratch = work->unk_04;
    Actor_SpawnFromRecord(D_801F3D4C + work->param.unk_0B * 17);
    Script_Begin(D_801F3D70[index].script_index, D_801F3D70[index].position);
    SELF_SET(work);

    g_Actors[work->unk_03].pos.x.fixed -= ONE;
    g_Actors[work->unk_03].pos.y.fixed += ONE;
    g_Actors[work->unk_04].pos.x.fixed += ONE;
    g_Actors[work->unk_04].pos.y.fixed -= ONE;
    g_Actors[work->unk_03].pos.z.fixed = g_Actors[work->unk_04].pos.z.fixed = g_Game.members[0].pos.z.fixed;
    g_Actors[work->unk_03].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Actors[SELF(Actor)->unk_04].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Actors[SELF(Actor)->unk_03].tint.bytes.flags = g_Actors[SELF(Actor)->unk_04].tint.bytes.flags = 0;
    GFX_PaletteAllocFade(&g_Actors[work->unk_03], 15, 0, 0, 1);
    GFX_PaletteAllocFade(&g_Actors[work->unk_04], 0, 0, 15, 1);
    SELF(Actor)->timer       = 4;
    SELF(Actor)->header.mode = 1;
}
