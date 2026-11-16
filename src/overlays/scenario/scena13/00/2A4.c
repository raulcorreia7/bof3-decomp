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
        g_Task->tint.bytes.rgb.red += 7;
        g_Task->tint.bytes.rgb.green += 7;
        g_Task->tint.bytes.rgb.blue += 7;
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
    Screen_DrawTintLayer(5, (GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK));
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
            Area_AddGridActor();
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

    work                       = g_Task;
    work->tint.bytes.rgb.blue  = 0;
    work->tint.bytes.rgb.green = 0;
    work->tint.bytes.rgb.red   = 0;
    g_Task->param.unk_0B       = 0x33;
    MESSAGE_START_WAIT(g_Task->param.unk_0B);
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
        g_Task->tint.bytes.rgb.red += 2;
        g_Task->tint.bytes.rgb.green += 2;
        g_Task->tint.bytes.rgb.blue += 2;
    } else {
        g_Task->timer       = 30;
        g_Task->header.mode = 3;
    }
    Scene_DrawScreenTint();
    func_801F7568();
}

MATCH void func_801F735C(void) {
    Actor* work;
    s16    message_id;

    g_Task->timer -= 1;
    if (g_Task->timer == 0) {
        g_Task->param.unk_0B += 1;
        work       = g_Task;
        message_id = work->param.unk_0B;
        if ((u8)message_id == 0x37) {
            work->tint.signed_bytes.delta.blue  = -1;
            work->tint.signed_bytes.delta.green = -1;
            work->tint.signed_bytes.delta.red   = -1;
            g_Task->header.mode                 = 4;
            g_ScriptVars[0] += 1;
        } else {
            MESSAGE_START_WAIT(message_id);
            g_Task->header.mode = 1;
        }
    }
    Scene_DrawScreenTint();
    func_801F7568();
}

MATCH void func_801F7444(void) {
    if (g_ScriptVars[0] == 0x35) {
        Actor_Clear();
    }
    Scene_DrawScreenTint();
    func_801F7568();
}

/* func_801F7484 */
MATCH void Scene_DrawScreenTint(void) {
    Screen_DrawTintLayer(5, (GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK));
}

MATCH void func_801F7568(void) {
    Actor* work;
    Actor* actor;

    work              = g_Task;
    actor             = &g_Actors[work->unk_06];
    g_Task            = actor;
    actor->draw_layer = 2;
    Area_AddGridActor();
    TASK_SET(g_Game.members);
    g_Game.members[0].unk_29 = 2;
    Area_AddGridActor();
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

    scratch                               = (s16*)g_ScratchPad.cells.bytes;
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

MATCH void func_801F7A1C(void) {
    if (g_Task->timer != 0) {
        g_Actors[g_Task->unk_03].tint.bytes.rgb.red += 8;
        g_Actors[g_Task->unk_03].tint.bytes.rgb.green += 8;
        g_Actors[g_Task->unk_03].tint.bytes.rgb.blue += 8;
        g_Actors[g_Task->unk_04].tint.bytes.rgb.red += 8;
        g_Actors[g_Task->unk_04].tint.bytes.rgb.green += 8;
        g_Actors[g_Task->unk_04].tint.bytes.rgb.blue += 8;
        g_Task->timer--;
    } else {
        g_ScriptVars[0]++;
        g_Task->header.mode = 3;
    }
}

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
    Char_RebuildPartyStats();
    Scene_RunScenario(0);
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
