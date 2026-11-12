#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801F6EE8(void) {
    u8* first;
    u8* second;
    u8* third;

    first       = (u8*)g_Task;
    first[0x5F] = 0;
    first[0x5E] = 0;
    first[0x5D] = 0;

    second    = (u8*)g_Task;
    second[9] = 0x0F;

    third    = (u8*)g_Task;
    third[1] = 1;
}

MATCH void func_801F6F24(void) {
    g_Task->timer -= 1;
    if (g_Task->timer != 0) {
        g_Task->tint.bytes.unk_5D += 7;
        g_Task->tint.bytes.unk_5E += 7;
        g_Task->tint.bytes.unk_5F += 7;
    } else {
        g_Task->header.mode = 2;
    }
    Area_DrawScreenTint();
    func_801F70DC();
}

MATCH void func_801F6FD0(void) {
    Area_DrawScreenTint();
    func_801F70DC();
}

#include "shared/Area_DrawScreenTint.h"

MATCH void Area_DrawScreenTint(void) {
    Screen_DrawTintLayer(5, (GetTPage(0, 2, 960, 0) & HALF_MASK));
}

MATCH void func_801F70DC(void) {
    Actor* actor;
    Actor* actor2;
    s32    i;

    actor = g_Task;
    i     = 0;
    do {
        actor2 = &g_Actors[i & BYTE_MASK];
        g_Task = actor2;
        if ((actor2->header.flags & 0x1) && (actor2->unk_06 == 6)) {
            actor2->draw_layer = 5;
            func_8014D290();
        }
        i += 1;
    } while ((i & BYTE_MASK) < 0x1EU);
    g_Task = actor;
}

MATCH void func_801F7198(void) {
    SYS_DISPATCH_TASK(D_801FBEFC, 1, g_Task);
}

MATCH void func_801F71DC(void) {
    Actor* work;

    work                    = g_Task;
    work->tint.bytes.unk_5F = 0;
    work->tint.bytes.unk_5E = 0;
    work->tint.bytes.unk_5D = 0;
    g_Task->param.unk_0B    = 0x33;
    Message_StartAreaMessage(g_Task->param.unk_0B);
    g_GameStateIndex    = GAME_REQUEST_MESSAGE;
    g_Task->header.mode = 1;
}

MATCH void func_801F7248(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        g_Task->timer       = 30;
        g_Task->header.mode = 2;
    }
    Scene_DrawScreenTint();
    func_801F7568();
}

MATCH void func_801F72A0(void) {
    g_Task->timer -= 1;
    if (g_Task->timer != 0) {
        g_Task->tint.bytes.unk_5D += 2;
        g_Task->tint.bytes.unk_5E += 2;
        g_Task->tint.bytes.unk_5F += 2;
    } else {
        g_Task->timer       = 30;
        g_Task->header.mode = 3;
    }
    Scene_DrawScreenTint();
    func_801F7568();
}

INCLUDE_ASM(func_801F735C);

MATCH void func_801F7444(void) {
    if (g_ScriptVars[0] == 0x35) {
        Actor_Clear();
    }
    Scene_DrawScreenTint();
    func_801F7568();
}

/* func_801F7484 */
MATCH void Scene_DrawScreenTint(void) {
    Screen_DrawTintLayer(5, (GetTPage(0, 2, 960, 0) & HALF_MASK));
}

MATCH void func_801F7568(void) {
    Actor* work;
    Actor* actor;

    work              = g_Task;
    actor             = &g_Actors[work->unk_06];
    g_Task            = actor;
    actor->draw_layer = 2;
    func_8014D290();
    TASK_SET(g_Game.members);
    g_Game.members[0].unk_29 = 2;
    func_8014D290();
    g_Task = work;
}

MATCH void func_801F75F8(void) {
    SYS_DISPATCH_TASK(D_801FBF10, 1, g_Task);
}

MATCH void func_801F763C(void) {
    u8*  work;
    u8*  data;
    u8*  cell;
    u8   cell4;
    u32  cell3;
    s16* scratch;

    g_Task->unk_03 = Actor_FindFree();
    if (g_Task->unk_03 == GAME_NONE) {
        return;
    }

    g_Actors[g_Task->unk_03].header.flags = 1;
    g_Task->unk_04                        = Actor_FindFree();
    if (g_Task->unk_04 == GAME_NONE) {
        g_Actors[g_Task->unk_03].header.flags = 0;
        return;
    }

    scratch                               = (s16*)D_1F800000;
    data                                  = (u8*)D_801FBF20;
    g_Actors[g_Task->unk_04].header.flags = 1;
    work                                  = (u8*)g_Task;
    *scratch                              = work[3];
    func_801A4D54(data);
    *scratch = work[4];
    func_801A4D54(data);
    SP_REF(u8*, 0x44) = work;

    g_Actors[work[3]].pos.y.fixed -= TO_COORD(1);
    g_Actors[work[4]].pos.y.fixed += TO_COORD(1);
    g_Actors[work[3]].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Actors[g_Task->unk_04].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    cell                                      = (u8*)g_Task;
    cell4                                     = cell[4];
    cell3                                     = cell[3];
    FIELD(u8, D_801468E4, cell4 * ACTOR_SIZE) = 1;
    FIELD(u8, D_801468E4, cell3 * ACTOR_SIZE) = 1;
    GFX_AllocPaletteFade(&g_Actors[work[3]], 15, 0, 0, 1);
    GFX_AllocPaletteFade(&g_Actors[work[4]], 0, 0, 15, 1);
    g_Task->timer       = 32;
    g_Task->header.mode = 1;
}

MATCH void func_801F7958(void) {
    if (g_Task->timer != 0) {
        g_Actors[g_Task->unk_03].pos.y.fixed += 0x800;
        g_Actors[g_Task->unk_04].pos.y.fixed -= 0x800;
        g_Task->timer -= 1;
    } else {
        g_Task->timer       = 15;
        g_Task->header.mode = 2;
    }
}

INCLUDE_ASM(func_801F7A1C);

/* func_801F7C24 */
MATCH void Scene_ReleaseActors(void) {
    g_Actors[g_Task->unk_03].header.flags = 0;
    g_Actors[g_Task->unk_04].header.flags = 0;
    GFX_FreePaletteFadeTarget(&g_Actors[g_Task->unk_03]);
    GFX_FreePaletteFadeTarget(&g_Actors[g_Task->unk_04]);
    Actor_Clear();
}

MATCH void func_801F7D14(void) {
    SYS_DISPATCH_BYTE(D_801FBF48, D_80146872);
}

MATCH void func_801F7D50(void) {
    Game_SetScriptActive();
    g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
    func_801C16B8();
    func_801C1DF0(0);
    SYS_SetFlag(g_SceneEventFlags, 67);
    SYS_ClearFlag(g_SceneEventFlags, 66);
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7DBC);

MATCH void func_801F8474(void) {
    SYS_DISPATCH_BYTE(D_801FBF54, g_SceneState.state_04);
}

MATCH void func_801F84B0(void) {
}

INCLUDE_ASM(func_801F84B8);

INCLUDE_ASM(func_801F873C);

MATCH void func_801F8C1C(void) {
    SCENE_START_SCRIPT_PAIR(D_801FBF78);
}

MATCH void func_801F8D0C(void) {
    SCENE_START_SCRIPT_PAIR(D_801FBF98);
}

INCLUDE_ASM(func_801F8DFC);

INCLUDE_ASM(func_801F9570);

INCLUDE_ASM(func_801F9A44);

MATCH void func_801F9E70(u16 phase) {
    s16 volume;
    s32 wave;

    wave   = rsin((phase - 0x4C0) >> 1);
    volume = ABS(wave) << 1;
    SpuSetVoiceVolume(0x11, volume, volume);
    SpuSetVoiceVolume(0x12, volume, volume);
    SpuSetVoiceVolume(0x13, volume, volume);
    wave   = rsin((phase - 0xCC0) >> 1);
    volume = ABS(wave) << 1;
    SpuSetVoiceVolume(0x10, volume, volume);
}

INCLUDE_ASM(func_801F9F18);

INCLUDE_ASM(func_801FA844);

INCLUDE_ASM(func_801FAFA0);

#include "overlays/scenario/GFX_CopyPaletteCapped.h"

/* func_801FB164 */
MATCH void Scene_RestorePalette(void) {
    s32 i;

    i = 0;
    do {
        g_GraphicsPaletteDst[i] = MEM_PTR(const volatile u16, 0x80033800u)[i];
        i++;
    } while (i < 16);
    g_GfxPalettePending = (g_GfxPalettePending + 1u);
}

INCLUDE_ASM(func_801FB1B4);

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH void func_801FB390(void* entity) {
    ((Actor*)entity)->unk_7E = (((Actor*)entity)->unk_7E + 1);
}

MATCH void func_801FB3A4(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 3;
    g_SceneState.step_05  = 5;
}

MATCH void func_801FB3DC(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 6;
    g_SceneState.step_05  = 0x19;
}

MATCH void func_801FB414(void) {
    SYS_SetFlag(g_SceneFlags, 28);
    Scene_StartEvent(44, 0);
    g_SceneEventSelection = 17;
}

INCLUDE_ASM(func_801FB464);

INCLUDE_ASM(func_801FBA34);

MATCH void Scene_JoinPartyRyuAdultPecoMomo(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_PECO, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_PECO);
    Party_JoinMember(CHAR_ID_MOMO);
}

MATCH void func_801FBBC4(void) {
    u8 slot;

    for (slot = 0; slot < 3; slot++) {
        D_80144908[slot] = g_PartyFieldOrder[slot];
        D_8014490B[slot] = g_PartyBattleOrder[slot];
    }
    for (slot = 0; slot < 3; slot++) {
        Party_RemoveMember(D_80144908[slot]);
    }
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

/* func_801FBC88 */
MATCH void Scene_LoadPartyRyuAdult(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_NINA_ADULT, 0U);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
}

MATCH void func_801FBCC4(void) {
    u8 ids[3];
    u8 slot;

    for (slot = 0; slot < 3; slot++) {
        ids[slot] = D_80144908[slot];
    }
    EMI_LoadPartyArchives(ids[0], ids[1], ids[2], 0);
    g_Game.party_size = 0;
    Party_JoinMember(ids[0]);
    Party_JoinMember(ids[1]);
    Party_JoinMember(ids[2]);
    for (slot = 3; slot < 6; slot++) {
        g_PartyFieldOrder[slot] = D_80144908[slot];
    }
}

MATCH void Scene_SetPartyRyuAdultMomoNinaAdult(void) {
    SCENE_SET_PARTY(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_NINA_ADULT);
}

MATCH void func_801FBDD8(void) {
    u8 ids[3];
    u8 slot;

    for (slot = 0; slot < 3; slot++) {
        ids[slot] = g_Game.members[slot].chr.character_id;
    }
    for (slot = 0; slot < 3; slot++) {
        Party_RemoveMember(ids[slot]);
    }
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_GARR, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

/* func_801FBE98 */
MATCH void Scene_JoinRei(void) {
    Party_JoinMember(CHAR_ID_REI);
    Party_LoadPalettes();
}

/* func_801FBEC0 */
MATCH void Scene_JoinGarr(void) {
    Party_JoinMember(CHAR_ID_GARR);
    Party_LoadPalettes();
}

MATCH void func_801FBEE8(void) {
}
