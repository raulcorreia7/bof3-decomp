#include "scena15_00.h"

#include "shared/Area_DrawScreenTint.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

/* func_801F6F7C */
MATCH void Scene_InitTaskArea(void) {
    Actor* work;

    work           = g_Task;
    work->screen_x = 640;
    work->screen_y = 1536;
    work->timer    = 0;
    Area_ClearWorkColumn();
    (g_Task)->header.mode = (g_Task)->header.mode + 1;
}

MATCH void func_801F6FCC(void) {
    func_801F71B0(g_Task->timer);
    if (g_FrameCount & 0x1) {
        func_801F75D8();
    }
    func_801F7748();
    g_Task->timer = (g_Task)->timer + 4;
    if (g_Task->timer == 0) {
        g_Task->timer       = 32;
        g_Task->header.mode = (g_Task)->header.mode + 1;
    }
}

MATCH void func_801F7078(void) {
    func_801F71B0(0xFF);
    if (g_FrameCount & 0x1) {
        func_801F75D8();
    }
    func_801F7748();
    if (g_ScriptVars[0] == 0x1F) {
        g_Task->timer       = 252;
        g_Task->header.mode = (g_Task)->header.mode + 1;
    }
}

MATCH void func_801F7100(void) {
    func_801F71B0(g_Task->timer);
    func_801F7748();
    g_Task->timer = (g_Task)->timer - 4;
    if (g_Task->timer == 0) {
        g_Task->header.mode = (g_Task)->header.mode + 1;
    }
}

MATCH void func_801F717C(void) {
    if (!(func_801F7748() & BYTE_MASK)) {
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F71B0);

MATCH void func_801F752C(AreaSpark* spark) {
    DVECTOR screen;
    TILE_1* tile;
    u8      shade;

    Area_ProjectPoint(&spark->pos.x, &screen);
    tile = (TILE_1*)g_GfxPrimCursor;
    SetTile1(tile);
    SetSemiTrans(tile, 0);
    setXY0(tile, screen.vx, screen.vy);
    shade    = -RANDOM_MASK(1);
    tile->b0 = shade;
    tile->g0 = shade;
    tile->r0 = shade;
    GFX_AddPrim(1, sizeof(TILE_1));
}

#include "shared/Area_ClearWorkColumn.h"

INCLUDE_ASM(func_801F75D8);

MATCH bool func_801F7748(void) {
    AreaSpark* spark;
    u8         i;
    bool       alive;

    alive = false;
    spark = MEM_PTR(AreaSpark, AREA_WORK);
    i     = 0;
    do {
        if (spark->active != 0) {
            spark->pos.z -= spark->fall_speed << 8;
            func_801F752C(spark);
            if (spark->pos.z < g_Task->pos.z.fixed) {
                spark->active = 0;
            }
            alive = true;
        }
        spark++;
        i++;
    } while (i < AREA_SPARK_COUNT);
    return alive;
}

MATCH void func_801F77F8(void) {
    SYS_DISPATCH_TASK(D_801FE590, 1, g_Task);
}

MATCH void func_801F783C(void) {
    Actor*       work;
    PartyMember* battler;
    s32          i;
    s8           tint;

    work = g_Task;
    i    = 0;
    if (g_PartySize != 0) {
        do {
            battler = &g_Game.members[i & BYTE_MASK];
            TASK_SET(battler);
            battler->unk_29 = 3;
            func_8014D290();
            i += 1;
        } while ((u32)(i & BYTE_MASK) < g_PartySize);
    }
    g_Task                  = work;
    tint                    = -0x80;
    work->tint.bytes.unk_5F = tint;
    work->tint.bytes.unk_5E = tint;
    work->tint.bytes.unk_5D = tint;
    g_Task->header.mode     = 1;
}

MATCH void func_801F7900(void) {
    func_801F79C4();
}

MATCH void func_801F7920(void) {
    Actor* work;
    u8*    counter;

    work = g_Task;
    if (work->tint.signed_bytes.unk_5D != 0) {
        work->tint.signed_bytes.unk_5D -= 2;
        g_Task->tint.bytes.unk_5E -= 2;
        g_Task->tint.bytes.unk_5F -= 2;
    } else {
        counter           = &g_SceneState.step_05;
        *counter          = *counter + 1;
        work->header.mode = 3;
    }
    func_801F79C4();
}

MATCH void func_801F79BC(void) {
}

MATCH void func_801F79C4(void) {
    Screen_DrawTintLayer(3, GetTPage(0, 2, 960, 0));
}

MATCH void func_801F7AA8(void) {
    SYS_DISPATCH_TASK(D_801FE5A0, 1, g_Task);
}

INCLUDE_ASM(func_801F7AEC);

MATCH void func_801F7D1C(void) {
    UPoint2D pos;

    if (g_GameStateIndex == 3 || g_GameStateIndex == 1) {
        g_Actors[g_Task->param.actor_slot].active_flags &= 0xF7;
        g_Task->header.mode = 0;
    } else {
        func_801F83AC(&pos);
        g_Task->timer += 8;
        g_Task->tint.signed_bytes.unk_5D = rsin(g_Task->timer << 4) >> 7;
        g_Task->tint.signed_bytes.unk_5E = rcos(g_Task->timer << 4) >> 7;
        func_801F7FFC(pos.x, pos.y);
    }
}

MATCH void func_801F7E2C(void) {
    UPoint2D pos;

    func_801F83AC(&pos);
    if (g_Task->tint.signed_bytes.unk_5D < 0x70) {
        g_Task->tint.signed_bytes.unk_5D += 2;
    }
    if (g_Task->tint.signed_bytes.unk_5E < 0x30) {
        g_Task->tint.signed_bytes.unk_5E += 1;
    }
    func_801F81D8(pos.x, pos.y);
    if (g_GameStateIndex == 3 || g_GameStateIndex == 1) {
        g_Actors[g_Task->param.actor_slot].active_flags &= 0xF7;
        g_Task->header.mode = 0;
    }
    if ((g_Task->tint.word & 0xFFFF00) == 0x307000) {
        g_Task->unk_06      = 0;
        g_Task->header.mode = 1;
    }
}

MATCH void func_801F7F5C(void) {
    UPoint2D pos;

    func_801F83AC(&pos);
    if (g_Task->tint.signed_bytes.unk_5D != 0) {
        g_Task->tint.signed_bytes.unk_5D -= 2;
    }
    if (g_Task->tint.signed_bytes.unk_5E != 0) {
        g_Task->tint.signed_bytes.unk_5E -= 1;
    }
    func_801F81D8(pos.x, pos.y);
    if ((g_Task->tint.word & 0xFFFF00) == 0) {
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F7FFC);

INCLUDE_ASM(func_801F81D8);

MATCH void func_801F83AC(UPoint2D* out) {
    SVECTOR vec;
    long    depth;
    long    flag;
    u8      slot;

    slot                    = g_Task->param.actor_slot;
    g_Actors[slot].screen_x = g_Task->screen_x;
    g_Actors[slot].screen_y = g_Task->screen_y;
    vec.vx                  = (g_Task->pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
    vec.vy                  = (g_Task->pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
    vec.vz                  = -COORD_INT(g_Task->pos.z) / 2;
    g_Task->unk_60          = RotTransPers(&vec, (long*)out, &depth, &flag);
    out->x -= 12;
    out->y -= 37;
}

MATCH void func_801F8488(void) {
    SYS_DISPATCH_TASK(D_801FE5B0, 1, g_Task);
}

/* The statements of func_801F84CC and func_801F87F8, byte-identical twins: set +0x29 of every party battler row to 3, clear the three tint bytes of the current work and move it to step 1. Each member declares work and i. */
#define SCENA15_PARTY_SETUP()           \
    work = g_Task;                      \
    for (i = 0; i < g_PartySize; i++) { \
        g_Game.members[i].unk_29 = 3;   \
    }                                   \
    g_Task                  = work;     \
    work->tint.bytes.unk_5F = 0;        \
    work->tint.bytes.unk_5E = 0;        \
    work->tint.bytes.unk_5D = 0;        \
    g_Task->header.mode     = 1

MATCH void func_801F84CC(void) {
    Actor* work;
    u8     i;

    SCENA15_PARTY_SETUP();
}

MATCH void func_801F8548(void) {
    Actor* work;
    u8*    counter;

    work = g_Task;
    if (work->tint.signed_bytes.unk_5D < 0x7C) {
        work->tint.signed_bytes.unk_5D += 4;
        g_Task->tint.bytes.unk_5E += 4;
        g_Task->tint.bytes.unk_5F += 4;
    } else {
        counter           = g_ScriptVars;
        *counter          = *counter + 1;
        work->header.mode = 2;
    }
    func_801F79C4();
    func_801F8704();
}

MATCH void func_801F85F0(void) {
    func_801F79C4();
    func_801F8704();
}

INCLUDE_ASM(func_801F8618);

MATCH void func_801F8704(void) {
    Actor*       actor;
    PartyMember* member;
    s32          shade;
    u8           i;

    actor = g_Task;
    shade = -((s8)actor->tint.bytes.unk_5D / 2); /* kept: retail sign-extends the u8 load (lbu, sll, sra); signed_bytes emits lb. */
    for (i = 0; i < g_PartySize; i++) {
        if (g_Game.members[i].chr.character_id != CHAR_ID_RYU_ADULT) {
            member                   = &g_Game.members[i];
            member->unk_5F           = shade;
            member->unk_5E           = shade;
            g_Game.members[i].unk_5D = shade;
        }
    }
    TASK_SET(actor);
}

MATCH void func_801F87B4(void) {
    SYS_DISPATCH_TASK(D_801FE5C0, 1, g_Task);
}

MATCH void func_801F87F8(void) {
    Actor* work;
    u8     i;

    SCENA15_PARTY_SETUP();
}

MATCH void func_801F8874(void) {
    Actor* work;
    u8*    counter;

    work = g_Task;
    if (work->tint.bytes.unk_5D < 0xF8) {
        work->tint.bytes.unk_5D += 8;
        g_Task->tint.bytes.unk_5E += 8;
        g_Task->tint.bytes.unk_5F += 8;
    } else {
        work->tint.signed_bytes.unk_5F = -1;
        work->tint.signed_bytes.unk_5E = -1;
        work->tint.signed_bytes.unk_5D = -1;
        counter                        = &g_SceneState.step_05;
        *counter                       = *counter + 1;
        g_Task->header.mode            = 2;
    }
    func_801F79C4();
    func_801F8958();
}

MATCH void func_801F8930(void) {
    func_801F79C4();
    func_801F8958();
}

MATCH void func_801F8958(void) {
    Actor* actor;
    Actor* work;
    u8     i;

    actor = g_Task;
    for (i = 0; i < ACTOR_COUNT; i++) {
        if (func_801ACE9C(g_Actors[i].unk_2C) == 0x261) {
            work             = &g_Actors[i];
            g_Task           = work;
            work->draw_layer = 3;
            func_8014D290();
        }
        if (func_801ACE9C(g_Actors[i].unk_2C) == 0x308 && SYS_TestFlag(g_SceneFlags, 0x11)) {
            work             = &g_Actors[i];
            g_Task           = work;
            work->draw_layer = 3;
            func_8014D290();
        }
    }
    g_Task = actor;
}

MATCH void func_801F8A5C(void) {
    SYS_DISPATCH_TASK(D_801FE5CC, 1, g_Task);
}

INCLUDE_ASM(func_801F8AA0);

#include "overlays/scenario/Scene_AdvanceBandMotion.h"

MATCH void func_801F8BC4(void) {
    SCENE_ADVANCE_BAND_MOTION(+, func_801F9020);
}

MATCH void func_801F8C78(void) {
    MATRIX matrix;
    Actor* work;

    Area_SetCameraMatrix(&matrix);
    func_801F9020(&g_Task->pos.x, &g_Task->vx);
    func_801F92F0(&g_Task->pos.x, &g_Task->vx);
    work         = g_Task;
    D_801FE738.x = -work->vx;
    D_801FE738.y = -work->vy;
    D_801FE738.z = -work->vz;
    work->timer  = 128;
    g_Task->header.mode++;
}

INCLUDE_ASM(func_801F8D30);

MATCH void func_801F8EA8(void) {
    MATRIX matrix;
    Actor* work;
    s32    cue;

    Area_SetCameraMatrix(&matrix);
    work = g_Task;
    func_801F92F0(&work->pos.x, &work->vx);
    g_Task->timer       = 8;
    g_Task->header.mode = g_Task->header.mode + 1;
    if (!(g_Task->param.unk_0B & 0x2)) {
        cue = 0x203;
        if (!(g_Task->unk_06 & 0x4)) {
            cue = 0x208;
        }
        SND_PlayCue(cue);
    }
}

MATCH void func_801F8F4C(void) {
    SCENE_ADVANCE_BAND_MOTION(-, func_801F9020);
}

/* func_801F9000 */
MATCH void Scene_ClearActor(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801F9020);

INCLUDE_ASM(func_801F92F0);

INCLUDE_ASM(func_801F9500);

INCLUDE_ASM(func_801F97CC);

INCLUDE_ASM(func_801F9A20);

MATCH void func_801F9CAC(void) {
    SYS_DISPATCH_BYTE(D_801FE66C, D_80146872);
}

MATCH void func_801F9CE8(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F9CFC);

INCLUDE_ASM(func_801FA6BC);

MATCH bool func_801FA854(u8 type, s16 angle_x, s16 angle_y, s16 angle_z, u8 layer, s32 scene_step) {
    u8 slot;

    slot       = Actor_FindFreeSlot();
    D_801FE748 = slot;
    if (slot != GAME_NONE) {
        g_ActorSlots[slot].header.flags         = 1;
        g_ActorSlots[D_801FE748].type           = type;
        g_ActorSlots[D_801FE748].camera_angle.x = angle_x;
        g_ActorSlots[D_801FE748].camera_angle.y = angle_y;
        g_ActorSlots[D_801FE748].camera_angle.z = angle_z;
        g_ActorSlots[D_801FE748].scene_step     = scene_step;
        g_ActorSlots[D_801FE748].layer          = layer;
    } else {
        return false;
    }
    return true;
}

MATCH void func_801FA998(void) {
    SYS_DISPATCH_BYTE(D_801FE678, g_SceneState.state_04);
}

MATCH void func_801FA9D4(void) {
}

INCLUDE_ASM(func_801FA9DC);

INCLUDE_ASM(func_801FADFC);

INCLUDE_ASM(func_801FAFA8);

INCLUDE_ASM(func_801FB788);

INCLUDE_ASM(func_801FC100);

INCLUDE_ASM(func_801FC1D8);

INCLUDE_ASM(func_801FCA3C);

INCLUDE_ASM(func_801FCBAC);

MATCH void func_801FDB84(void) {
    if (D_801FE74C == 0) {
        g_ScriptVars[1] = 1;
        D_801FE74C      = (RANDOM_MOD(38) + 42) / 2;
    } else {
        D_801FE74C--;
    }
}

MATCH void func_801FDC10(s32 shift) {
    s32 offset;

    if (D_801FE750 != 0) {
        offset                   = D_801FE6E8[g_FrameCount & 0x3];
        g_AreaCameraRefreshCount = 2;
        g_AreaCameraOffsetY += offset << shift;
    }
}

MATCH s32 func_801FDC6C(s32 x, s32 y, s32 unk_06, s32 unk_07, u8 link) {
    u8 slot;

    slot = Actor_FindFreeSlot();
    if (slot != GAME_NONE) {
        g_ActorSlots[slot].header.flags = 1;
        g_ActorSlots[slot].pos.x.fixed  = x;
        g_ActorSlots[slot].type         = 0x9E;
        g_ActorSlots[slot].pos.y.fixed  = y;
        g_ActorSlots[slot].pos.z.fixed  = (Area_SampleHeight(g_ActorSlots[slot].pos.x.fixed, y) << 16) + TO_COORD(512);
        g_ActorSlots[slot].unk_06       = unk_06;
        g_ActorSlots[slot].unk_07       = unk_07;
        g_ActorSlots[slot].link         = link;
        return 1;
    }
    return 0;
}

#include "overlays/scenario/Scene_DispatchActor.h"

/* func_801FDDC0 */
MATCH void Scene_ShowEntityMessage(void* entity) {
    u8 message;

    message = D_801FE71C[((Actor*)entity)->callback_index];
    if (g_GameAreaId == AREA_ID_DESERT_CAMP_SECOND) {
        Message_StartAreaMessage(func_801F326C(message));
    } else {
        Message_StartAreaMessage(func_801F37AC(message));
    }
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
}

MATCH void func_801FDE2C(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 3;
    g_SceneState.step_05  = 0x32;
}

MATCH void func_801FDE64(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    SYS_SetFlag(g_SceneFlags, 13);
    func_801BE1B0(11);
    actor->unk_7E = actor->unk_7E + 1;
}

MATCH void func_801FDEB4(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    SYS_SetFlag(g_SceneFlags, 14);
    func_801BE1B0(12);
    actor->unk_7E = actor->unk_7E + 1;
}

MATCH void func_801FDF04(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    SYS_SetFlag(g_SceneFlags, 12);
    actor->unk_7E = actor->unk_7E + 1;
}

MATCH void func_801FDF4C(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    SYS_SetFlag(g_SceneFlags, 16);
    func_801BE1B0(14);
    actor->unk_7E = actor->unk_7E + 1;
}

MATCH void func_801FDF9C(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    SYS_SetFlag(g_SceneFlags, 15);
    func_801BE1B0(13);
    actor->unk_7E = actor->unk_7E + 1;
}

MATCH void func_801FDFEC(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    actor->unk_7E = actor->unk_7E + 1;
}

INCLUDE_ASM(func_801FE024);

MATCH s32 func_801FE18C(s32 x, s32 y) {
    if (g_GameAreaId == 0xAE) {
        if (SYS_TestFlag(g_SceneFlags, 2) == 0) {
            if (x > 4456447 && (u32)((y >> 16) - 3) < 2) {
                Game_SetScriptActive();
                g_SceneState.state_04 = 3;
                g_SceneState.step_05  = 0x14;
            }
            return 0;
        }
        if (SYS_TestFlag(g_SceneFlags, 4) == 0) {
            if (x <= 5439488 && (u32)((y >> 16) - 0x2E) < 3) {
                Game_SetScriptActive();
                g_SceneState.state_04 = 3;
                g_SceneState.step_05  = 0x1E;
            }
            return 0;
        }
        if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
            if (y <= 3801088 && (u32)((x >> 16) - 0x23) < 4) {
                Game_SetScriptActive();
                g_SceneState.state_04 = 3;
                g_SceneState.step_05  = 0x28;
            }
            return 0;
        }
        if (x == 3211264 && (u32)((y >> 16) - 0x27) < 2) {
            if (SYS_TestFlag(g_SceneFlags, 12) && SYS_TestFlag(g_SceneFlags, 14) && SYS_TestFlag(g_SceneFlags, 13) && SYS_TestFlag(g_SceneFlags, 15) && SYS_TestFlag(g_SceneFlags, 16)) {
                Game_SetScriptActive();
                g_SceneState.state_04 = 5;
                g_SceneState.step_05  = 5;
            } else {
                Game_SetScriptActive();
                g_SceneState.state_04 = 5;
                g_SceneState.step_05  = 0;
            }
        }
    }
    return 0;
}

MATCH void func_801FE3C8(void) {
    u8 ids[PARTY_SLOT_COUNT];
    u8 slot;

    for (slot = 0; slot < g_PartySize; slot++) {
        ids[slot] = g_Game.members[slot].chr.character_id;
    }
    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        Party_RemoveMember(ids[slot]);
    }
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_GARR, 0);
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

MATCH void func_801FE49C(void) {
    Party_JoinMember(CHAR_ID_REI);
    Party_JoinMember(CHAR_ID_GARR);
    Party_LoadPalettes();
}

MATCH void Scene_SetPartyRyuAdultNinaAdultGarr(void) {
    SCENE_SET_PARTY(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_GARR);
}

#include "overlays/scenario/Scene_SetPartyRyuAdultNinaAdultRei.h"

MATCH void func_801FE574(void) {
}
