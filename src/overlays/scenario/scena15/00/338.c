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
    Scene_DrawLightPillar(g_Task->timer);
    if (g_FrameCount & 0x1) {
        Area_AddSpark();
    }
    Scene_GetZFixed();
    g_Task->timer = (g_Task)->timer + 4;
    if (g_Task->timer == 0) {
        g_Task->timer       = 32;
        g_Task->header.mode = (g_Task)->header.mode + 1;
    }
}

MATCH void func_801F7078(void) {
    Scene_DrawLightPillar(0xFF);
    if (g_FrameCount & 0x1) {
        Area_AddSpark();
    }
    Scene_GetZFixed();
    if (g_ScriptVars[0] == 0x1F) {
        g_Task->timer       = 252;
        g_Task->header.mode = (g_Task)->header.mode + 1;
    }
}

MATCH void func_801F7100(void) {
    Scene_DrawLightPillar(g_Task->timer);
    Scene_GetZFixed();
    g_Task->timer = (g_Task)->timer - 4;
    if (g_Task->timer == 0) {
        g_Task->header.mode = (g_Task)->header.mode + 1;
    }
}

MATCH void func_801F717C(void) {
    if (!(Scene_GetZFixed() & BYTE_MASK)) {
        Actor_Clear();
    }
}

/* Draws a pillar of light at the task's position: thirty-two semi-transparent Gouraud quads between a ring at the
 * task's radius and the same ring higher up, dimmed by fade. */
/* func_801F71B0 */
MATCH void Scene_DrawLightPillar(u8 fade) {
    DVECTOR  last_inner;
    DVECTOR  last_outer;
    DVECTOR  inner;
    DVECTOR  outer;
    s32      point[3];
    MATRIX   matrix;
    POLY_G4* prim;
    s32      angle;
    s32      shade;
    u32      color;
    u8       i;

    Area_SetCameraMatrix(&matrix);
    angle    = 0;
    point[0] = g_Task->pos.x.fixed + (((s16)g_Task->screen_x * rcos(0)) >> 4);
    point[1] = g_Task->pos.y.fixed + (((s16)g_Task->screen_x * rsin(0)) >> 4);
    point[2] = g_Task->pos.z.fixed;
    Area_ProjectPoint(point, &inner);
    point[2] = g_Task->pos.z.fixed + TO_COORD((s16)g_Task->screen_y);
    Area_ProjectPoint(point, &outer);
    shade = ((g_FrameCount & 1) << 2) | 0x40;
    for (i = 0; i < 32; i++) {
        last_inner = inner;
        last_outer = outer;
        angle += 0x80;
        point[0] = g_Task->pos.x.fixed + (((s16)g_Task->screen_x * rcos((u16)angle)) >> 4);
        point[1] = g_Task->pos.y.fixed + (((s16)g_Task->screen_x * rsin((u16)angle)) >> 4);
        point[2] = g_Task->pos.z.fixed;
        Area_ProjectPoint(point, &inner);
        point[2] = g_Task->pos.z.fixed + TO_COORD((s16)g_Task->screen_y);
        Area_ProjectPoint(point, &outer);

        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
        if ((u8)(i - 11) >= 17) {
            GFX_AddPrim(1, 12);
        }
        prim = GFX_BeginPolyG4(1);
        setXY4(prim, last_inner.vx, last_inner.vy, last_outer.vx, last_outer.vy, inner.vx, inner.vy, outer.vx, outer.vy);
        color = (u32)(fade * (u8)shade) >> 8;
        setRGB0(prim, color, color, color);
        setRGB1(prim, color, color, color);
        if ((u8)(i - 8) >= 16) {
            shade += 8;
        } else {
            shade -= 8;
        }
        color = (u32)(fade * (u8)shade) >> 8;
        setRGB2(prim, color, color, color);
        setRGB3(prim, color, color, color);
        if ((u8)(i - 11) >= 17) {
            GFX_AddPrim(1, 36);
        }
    }
}

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

#include "shared/Area_AddSpark.h"

/* func_801F7748 */
MATCH bool Scene_GetZFixed(void) {
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
            Area_AddGridActor();
            i += 1;
        } while ((u32)(i & BYTE_MASK) < g_PartySize);
    }
    g_Task                     = work;
    tint                       = -0x80;
    work->tint.bytes.rgb.blue  = tint;
    work->tint.bytes.rgb.green = tint;
    work->tint.bytes.rgb.red   = tint;
    g_Task->header.mode        = 1;
}

MATCH void func_801F7900(void) {
    func_801F79C4();
}

MATCH void func_801F7920(void) {
    Actor* work;
    u8*    counter;

    work = g_Task;
    if (work->tint.signed_bytes.delta.red != 0) {
        work->tint.signed_bytes.delta.red -= 2;
        g_Task->tint.bytes.rgb.green -= 2;
        g_Task->tint.bytes.rgb.blue -= 2;
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
    Screen_DrawTintLayer(3, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, FONT_TPAGE_X, FONT_TPAGE_Y));
}

MATCH void func_801F7AA8(void) {
    SYS_DISPATCH_TASK(D_801FE5A0, 1, g_Task);
}

void func_801F7D1C(void);

MATCH void func_801F7AEC(void) {
    TILE* tile;
    u8*   cursor;
    u32   idx;

    if (g_GameStateIndex == 3 || g_GameStateIndex == 1) {
        return;
    }

    idx = g_Task->param.unk_0B;
    g_Actors[idx].active_flags |= 8;
    {
        Actor* task;
        s32    px;
        s32    pz;

        task                       = g_Task;
        px                         = g_Actors[idx].pos.x.fixed;
        g_Actors[idx].screen_x     = task->screen_x;
        g_Actors[idx].screen_y     = task->screen_y;
        task->pos.x.fixed          = px;
        task->pos.y.fixed          = g_Actors[idx].pos.y.fixed;
        pz                         = g_Actors[idx].pos.z.fixed;
        task->tint.bytes.rgb.blue  = 0;
        task->tint.bytes.rgb.green = 0;
        task->tint.bytes.rgb.red   = 0;
        task->pos.z.fixed          = pz;
    }

    cursor             = g_GfxPrimCursor;
    g_GfxPrimCursor    = cursor + sizeof(RECT);
    ((RECT*)cursor)->x = 0x340;
    ((RECT*)cursor)->y = 0x100;
    ((RECT*)cursor)->w = 0xC0;
    ((RECT*)cursor)->h = 0x100;
    SetDrawArea((DR_AREA*)g_GfxPrimCursor, (RECT*)cursor);
    GFX_AddPrim(7, sizeof(DR_AREA));

    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    {
        Actor* task;

        task     = g_Task;
        tile->x0 = task->screen_x + 0x334;
        tile->y0 = (u16)(task->screen_y + (((g_FrameBufferIndex ^ 1) * 0xF0) - 0x15));
    }
    tile->w  = 0x18;
    tile->h  = 0x30;
    tile->r0 = 0;
    tile->g0 = 0;
    tile->b0 = 0;
    GFX_AddPrim(7, sizeof(TILE));

    cursor          = g_GfxPrimCursor;
    g_GfxPrimCursor = cursor + sizeof(RECT);
    memcpy(cursor, g_GfxCurrentDisplayFrame + 0x14, sizeof(RECT));
    SetDrawArea((DR_AREA*)g_GfxPrimCursor, (RECT*)cursor);
    GFX_AddPrim(7, sizeof(DR_AREA));

    if (g_Task->unk_06 == 0) {
        func_801F7D1C();
        g_Task->header.mode = 1;
    } else {
        g_Task->header.mode = 2;
    }
}

MATCH void func_801F7D1C(void) {
    Pos2u pos;

    if (g_GameStateIndex == 3 || g_GameStateIndex == 1) {
        g_Actors[g_Task->param.actor_slot].active_flags &= 0xF7;
        g_Task->header.mode = 0;
    } else {
        func_801F83AC(&pos);
        g_Task->timer += 8;
        g_Task->tint.signed_bytes.delta.red   = rsin(g_Task->timer << 4) >> 7;
        g_Task->tint.signed_bytes.delta.green = rcos(g_Task->timer << 4) >> 7;
        func_801F7FFC(pos.x, pos.y);
    }
}

MATCH void func_801F7E2C(void) {
    Pos2u pos;

    func_801F83AC(&pos);
    if (g_Task->tint.signed_bytes.delta.red < 0x70) {
        g_Task->tint.signed_bytes.delta.red += 2;
    }
    if (g_Task->tint.signed_bytes.delta.green < 0x30) {
        g_Task->tint.signed_bytes.delta.green += 1;
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
    Pos2u pos;

    func_801F83AC(&pos);
    if (g_Task->tint.signed_bytes.delta.red != 0) {
        g_Task->tint.signed_bytes.delta.red -= 2;
    }
    if (g_Task->tint.signed_bytes.delta.green != 0) {
        g_Task->tint.signed_bytes.delta.green -= 1;
    }
    func_801F81D8(pos.x, pos.y);
    if ((g_Task->tint.word & 0xFFFF00) == 0) {
        Actor_Clear();
    }
}

/* Draw the sprite quad in a fixed grey with the tint's red and green lifted into the lower vertices. */
MATCH void func_801F7FFC(s16 x, s16 y) {
    POLY_GT4* prim;
    u8        red;
    u8        green;

    prim  = (POLY_GT4*)g_GfxPrimCursor;
    red   = g_Task->tint.bytes.rgb.red + 0x20;
    green = g_Task->tint.bytes.rgb.green + 0x20;
    SetPolyGT4(prim);
    SCENA15_SPRITE_GEOMETRY(prim, x, y);
    setRGB0(prim, 0x90, 0x90, 0x90);
    setRGB1(prim, 0x90, 0x90, 0x90);
    setRGB2(prim, 0, red, 0);
    setRGB3(prim, 0, green, 0);
    SCENA15_SPRITE_END(prim);
}

/* Draw the 24 by 48 tinted sprite at the screen point, its texture window centred on the work record's screen position. */
MATCH void func_801F81D8(s16 x, s16 y) {
    POLY_GT4* prim;
    u8        red;
    u8        green;

    prim  = (POLY_GT4*)g_GfxPrimCursor;
    red   = g_Task->tint.bytes.rgb.red;
    green = g_Task->tint.bytes.rgb.green;
    SetPolyGT4(prim);
    SCENA15_SPRITE_GEOMETRY(prim, x, y);
    setRGB0(prim, red, red, red);
    setRGB1(prim, red, red, red);
    setRGB2(prim, green, green, green);
    setRGB3(prim, green, green, green);
    SCENA15_SPRITE_END(prim);
}

MATCH void func_801F83AC(Pos2u* out) {
    SVECTOR vec;
    long    depth;
    long    flag;
    u8      slot;

    slot                    = g_Task->param.actor_slot;
    g_Actors[slot].screen_x = g_Task->screen_x;
    g_Actors[slot].screen_y = g_Task->screen_y;
    setVector(&vec, (g_Task->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (g_Task->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, -COORD_INT(g_Task->pos.z) / 2);
    g_Task->unk_60 = RotTransPers(&vec, (long*)out, &depth, &flag);
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
    g_Task                     = work;  \
    work->tint.bytes.rgb.blue  = 0;     \
    work->tint.bytes.rgb.green = 0;     \
    work->tint.bytes.rgb.red   = 0;     \
    g_Task->header.mode        = 1

MATCH void func_801F84CC(void) {
    Actor* work;
    u8     i;

    SCENA15_PARTY_SETUP();
}

MATCH void func_801F8548(void) {
    Actor* work;
    u8*    counter;

    work = g_Task;
    if (work->tint.signed_bytes.delta.red < 0x7C) {
        work->tint.signed_bytes.delta.red += 4;
        g_Task->tint.bytes.rgb.green += 4;
        g_Task->tint.bytes.rgb.blue += 4;
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

MATCH void func_801F8618(void) {
    u8 i;

    if (g_Task->tint.signed_bytes.delta.red != 0) {
        g_Task->tint.signed_bytes.delta.red -= 2;
        g_Task->tint.bytes.rgb.green -= 2;
        g_Task->tint.bytes.rgb.blue -= 2;
    } else {
        for (i = 0; i < g_PartySize; i++) {
            g_Game.members[i].unk_29 = g_AreaDrawMode;
        }
        func_80196070();
        return;
    }
    func_801F79C4();
    func_801F8704();
}

MATCH void func_801F8704(void) {
    Actor*       actor;
    PartyMember* member;
    s32          shade;
    u8           i;

    actor = g_Task;
    shade = -((s8)actor->tint.bytes.rgb.red / 2); /* kept: retail sign-extends the u8 load (lbu, sll, sra); signed_bytes emits lb. */
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
    if (work->tint.bytes.rgb.red < 0xF8) {
        work->tint.bytes.rgb.red += 8;
        g_Task->tint.bytes.rgb.green += 8;
        g_Task->tint.bytes.rgb.blue += 8;
    } else {
        work->tint.signed_bytes.delta.blue  = -1;
        work->tint.signed_bytes.delta.green = -1;
        work->tint.signed_bytes.delta.red   = -1;
        counter                             = &g_SceneState.step_05;
        *counter                            = *counter + 1;
        g_Task->header.mode                 = 2;
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
            Area_AddGridActor();
        }
        if (func_801ACE9C(g_Actors[i].unk_2C) == 0x308 && SYS_TestFlag(g_SceneFlags, 0x11)) {
            work             = &g_Actors[i];
            g_Task           = work;
            work->draw_layer = 3;
            Area_AddGridActor();
        }
    }
    g_Task = actor;
}

MATCH void func_801F8A5C(void) {
    SYS_DISPATCH_TASK(D_801FE5CC, 1, g_Task);
}

MATCH void func_801F8AA0(void) {
    s32 cue;

    g_Task->vx = 0;
    g_Task->vy = 0;
    g_Task->vz = 0;
    if (!(g_Task->unk_06 & 0x1)) {
        g_Task->unk_18 = 0x3000;
        g_Task->unk_1C = 0;
    } else {
        g_Task->unk_18 = 0;
        g_Task->unk_1C = 0x3000;
    }
    g_Task->gravity = 0x200000;
    if (g_Task->unk_06 & 0x8) {
        g_Task->vx += g_Task->unk_18 << 3;
        g_Task->vy += g_Task->unk_1C << 3;
        g_Task->vz += g_Task->gravity << 3;
        g_Task->header.mode += 3;
    } else {
        g_Task->timer       = 8;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
    if (!(g_Task->param.unk_0B & 0x1)) {
        cue = 0x202;
        if (!(g_Task->unk_06 & 0x4)) {
            cue = 0x207;
        }
        SND_PlayCue(cue);
    }
}

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

/* Spin the actor's sweep value, shift its position on alternate frames, and advance when the script variable equals its option. */
MATCH void func_801F8D30(void) {
    MATRIX camera;
    s32*   cell;

    cell = &D_801FE740;
    *cell += g_Task->gravity >> 1;
    if (*cell == g_Task->vz) {
        *cell = -*cell;
    }
    Area_SetCameraMatrix(&camera);
    if (g_FrameCount & 1) {
        func_801F9A20(&g_Task->pos, &g_Task->vx);
        if (!(g_Task->unk_06 & 1)) {
            g_Task->pos.x.fixed += 0x4000;
        } else {
            g_Task->pos.y.fixed += 0x4000;
        }
        func_801F9500(&g_Task->pos, &g_Task->vx);
        if (!(g_Task->unk_06 & 1)) {
            g_Task->pos.x.fixed -= 0x4000;
        } else {
            g_Task->pos.y.fixed -= 0x4000;
        }
    } else {
        func_801F97CC(&g_Task->pos, cell - 2);
    }
    if (g_ScriptVarsReq.byte == g_Task->option_flags) {
        g_Task->header.mode++;
    }
}

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

MATCH void func_801F9020(Coord* position, s32* step) {
    LINE_F4* line4;
    LINE_F2* line2;
    s32      point[3];
    DVECTOR  screen[4];

    FAKE_STACK_PADS(u8, 0x20); /* FAKE: retail keeps the point and screen rows in a 96-byte frame. */

    point[0] = position[0].fixed + step[0];
    point[1] = position[1].fixed + step[1];
    point[2] = position[2].fixed + step[2];
    Area_ProjectPoint(point, &screen[0]);

    if (!(g_Task->unk_06 & 1)) {
        point[0] = position[0].fixed - step[0];
        point[1] = position[1].fixed + step[1];
    } else {
        point[0] = position[0].fixed + step[0];
        point[1] = position[1].fixed - step[1];
    }
    point[2] = position[2].fixed + step[2];
    FAKE_BARRIER(); /* FAKE: keep the point stores before the call setup. */
    Area_ProjectPoint(point, &screen[1]);

    if (!(g_Task->unk_06 & 1)) {
        point[0] = position[0].fixed + step[0];
        point[1] = position[1].fixed - step[1];
    } else {
        point[0] = position[0].fixed - step[0];
        point[1] = position[1].fixed + step[1];
    }
    point[2] = position[2].fixed - step[2];
    FAKE_BARRIER(); /* FAKE: keep the point stores before the call setup. */
    Area_ProjectPoint(point, &screen[2]);

    point[0] = position[0].fixed - step[0];
    point[1] = position[1].fixed - step[1];
    point[2] = position[2].fixed - step[2];
    Area_ProjectPoint(point, &screen[3]);

    line4 = (LINE_F4*)g_GfxPrimCursor;
    SetLineF4(line4);
    SetSemiTrans(line4, 0);
    line4->x0 = screen[0].vx;
    line4->y0 = screen[0].vy;
    line4->x1 = screen[1].vx;
    line4->y1 = screen[1].vy;
    line4->x2 = screen[3].vx;
    line4->y2 = screen[3].vy;
    line4->x3 = screen[2].vx;
    line4->y3 = screen[2].vy;
    setRGB0(line4, 0xFF, 0xFF, 0xFF);
    Area_AddCellPrim(position[0].fixed, position[1].fixed, 0, sizeof(LINE_F4));

    line2 = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line2);
    SetSemiTrans(line2, 0);
    line2->x0 = screen[0].vx;
    line2->y0 = screen[0].vy;
    line2->x1 = screen[2].vx;
    line2->y1 = screen[2].vy;
    setRGB0(line2, 0xFF, 0xFF, 0xFF);
    Area_AddCellPrim(position[0].fixed, position[1].fixed, 0, sizeof(LINE_F2));
}

MATCH void func_801F92F0(Coord* position, s32* step) {
    POLY_F4* poly;
    s32*     delta;
    Coord*   origin;
    s32      point[4];

    FAKE_STACK_PADS(u8, 0xC); /* FAKE: retail keeps the point row aligned in a 64-byte frame. */

    poly   = (POLY_F4*)g_GfxPrimCursor;
    delta  = step;
    origin = position;
    SetPolyF4(poly);
    SetSemiTrans(poly, 0);

    point[0] = origin[0].fixed + delta[0];
    point[1] = origin[1].fixed + delta[1];
    point[2] = origin[2].fixed + delta[2];
    Area_ProjectPoint(point, (DVECTOR*)&poly->x0);
    if (!(g_Task->unk_06 & 1)) {
        point[0] = origin[0].fixed - delta[0];
        point[1] = origin[1].fixed + delta[1];
    } else {
        point[0] = origin[0].fixed + delta[0];
        point[1] = origin[1].fixed - delta[1];
    }
    point[2] = origin[2].fixed + delta[2];
    FAKE_BARRIER(); /* FAKE: keep the second projected point stores before its call setup. */
    Area_ProjectPoint(point, (DVECTOR*)&poly->x1);
    if (!(g_Task->unk_06 & 1)) {
        point[0] = origin[0].fixed + delta[0];
        point[1] = origin[1].fixed - delta[1];
    } else {
        point[0] = origin[0].fixed - delta[0];
        point[1] = origin[1].fixed + delta[1];
    }
    point[2] = origin[2].fixed - delta[2];
    FAKE_BARRIER(); /* FAKE: keep the third projected point stores before its call setup. */
    Area_ProjectPoint(point, (DVECTOR*)&poly->x2);

    point[0] = origin[0].fixed - delta[0];
    point[1] = origin[1].fixed - delta[1];
    point[2] = origin[2].fixed - delta[2];
    Area_ProjectPoint(point, (DVECTOR*)&poly->x3);
    setRGB0(poly, 255, 255, 255);
    Area_AddCellPrim(origin[0].fixed, origin[1].fixed, 0, sizeof(POLY_F4));
}

MATCH void func_801F9500(WorldPos* pos, s32* vx) {
    POLY_FT4*          prim;
    Scena15SpriteCell* cell;
    s32                point[3];

    FAKE_STACK_PADS(u8, 0x10); /* FAKE: retail keeps the point row in a 72-byte frame. */

    cell = D_801FE5E8;
    if (g_Task->unk_06 & 0x4) {
        cell++;
    }
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);

    if (!(g_Task->unk_06 & 1)) {
        point[0] = pos->x.fixed - vx[0];
        point[1] = pos->y.fixed + vx[1];
    } else {
        point[0] = pos->x.fixed + vx[0];
        point[1] = pos->y.fixed - vx[1];
    }
    point[2] = pos->z.fixed + vx[2];
    FAKE_BARRIER(); /* FAKE: keep the point stores before the call setup. */
    Area_ProjectPoint(point, (DVECTOR*)&prim->x0);

    point[0] = pos->x.fixed + vx[0];
    point[1] = pos->y.fixed + vx[1];
    point[2] = pos->z.fixed + vx[2];
    Area_ProjectPoint(point, (DVECTOR*)&prim->x1);

    point[0] = pos->x.fixed - vx[0];
    point[1] = pos->y.fixed - vx[1];
    point[2] = pos->z.fixed - vx[2];
    Area_ProjectPoint(point, (DVECTOR*)&prim->x2);

    if (!(g_Task->unk_06 & 1)) {
        point[0] = pos->x.fixed + vx[0];
        point[1] = pos->y.fixed - vx[1];
    } else {
        point[0] = pos->x.fixed - vx[0];
        point[1] = pos->y.fixed + vx[1];
    }
    point[2] = pos->z.fixed - vx[2];
    FAKE_BARRIER(); /* FAKE: keep the point stores before the call setup. */
    Area_ProjectPoint(point, (DVECTOR*)&prim->x3);

    setUV4(prim, cell->u, cell->v, cell->u + 0x18, cell->v, cell->u, cell->v + 0x10, cell->u + 0x18, cell->v + 0x10);
    prim->tpage = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, cell->page_x, cell->page_y);
    setClut(prim, 0xA0, 0x1F0);
    setRGB0(prim, 0x20, 0x20, 0x20);
    Area_AddCellPrim(pos->x.fixed, pos->y.fixed, 0, sizeof(POLY_FT4));
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F97CC(WorldPos* pos, s32* arg) {
    POLY_F4* poly;
    s32      point[8];
    s32      lift;

    poly = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(poly);
    SetSemiTrans(poly, 0);

    point[0] = pos->x.fixed + arg[0];
    point[1] = pos->y.fixed + arg[1];
    point[2] = pos->z.fixed + arg[2];
    Area_ProjectPoint(point, (DVECTOR*)&poly->x0);
    if (!(g_Task->unk_06 & 1)) {
        point[0] = pos->x.fixed - arg[0];
        point[1] = pos->y.fixed + arg[1];
    } else {
        point[0] = pos->x.fixed + arg[0];
        point[1] = pos->y.fixed - arg[1];
    }
    point[2] = pos->z.fixed + arg[2];
    FAKE_BARRIER(); /* FAKE: keep the point stores before the call setup. */
    Area_ProjectPoint(point, (DVECTOR*)&poly->x1);

    point[0] = pos->x.fixed + arg[0];
    point[1] = pos->y.fixed + arg[1];
    lift     = 0x100000;
    point[2] = pos->z.fixed + arg[2] + lift;
    Area_ProjectPoint(point, (DVECTOR*)&poly->x2);
    if (!(g_Task->unk_06 & 1)) {
        point[0] = pos->x.fixed - arg[0];
        point[1] = pos->y.fixed + arg[1];
    } else {
        point[0] = pos->x.fixed + arg[0];
        point[1] = pos->y.fixed - arg[1];
    }
    point[2] = pos->z.fixed + arg[2] + lift;
    FAKE_BARRIER(); /* FAKE: keep the point stores before the call setup. */
    Area_ProjectPoint(point, (DVECTOR*)&poly->x3);

    poly->r0 = (g_Task->unk_06 & 2) != 0 ? 0x80 : 0;
    poly->b0 = 0;
    poly->g0 = (g_Task->unk_06 & 2) == 0 ? 0x80 : 0;
    Area_AddCellPrim(pos->x.fixed, pos->y.fixed, 0, sizeof(POLY_F4));
}
#else
INCLUDE_ASM(func_801F97CC);
#endif

MATCH void func_801F9A20(WorldPos* pos, s32* vx) {
    POLY_F4* poly;
    s32      point[3];

    FAKE_STACK_PADS(u8, 0x20); /* FAKE: retail keeps the point row in an 88-byte frame. */

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y) & 0xFFFF, 0);
    Area_AddCellPrim(pos->x.fixed, pos->y.fixed, 0, sizeof(DR_MODE));
    poly = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(poly);
    SetSemiTrans(poly, 1);

    point[0] = pos->x.fixed + vx[0];
    point[1] = pos->y.fixed + vx[1];
    point[2] = pos->z.fixed + vx[2];
    Area_ProjectPoint(point, (DVECTOR*)&poly->x0);

    if (!(g_Task->unk_06 & 1)) {
        point[0] = pos->x.fixed - vx[0];
        point[1] = pos->y.fixed + vx[1];
    } else {
        point[0] = pos->x.fixed + vx[0];
        point[1] = pos->y.fixed - vx[1];
    }
    point[2] = pos->z.fixed + vx[2];
    FAKE_BARRIER(); /* FAKE: keep the point stores before the call setup. */
    Area_ProjectPoint(point, (DVECTOR*)&poly->x1);

    if (!(g_Task->unk_06 & 1)) {
        point[0] = pos->x.fixed + vx[0];
        point[1] = pos->y.fixed - vx[1];
    } else {
        point[0] = pos->x.fixed - vx[0];
        point[1] = pos->y.fixed + vx[1];
    }
    point[2] = pos->z.fixed - vx[2];
    FAKE_BARRIER(); /* FAKE: keep the point stores before the call setup. */
    Area_ProjectPoint(point, (DVECTOR*)&poly->x2);

    point[0] = pos->x.fixed - vx[0];
    point[1] = pos->y.fixed - vx[1];
    point[2] = pos->z.fixed - vx[2];
    Area_ProjectPoint(point, (DVECTOR*)&poly->x3);

    poly->r0 = (g_Task->unk_06 & 2) != 0 ? 0x80 : 0;
    poly->g0 = (g_Task->unk_06 & 2) == 0 ? 0x80 : 0;
    poly->b0 = 0;
    Area_AddCellPrim(pos->x.fixed, pos->y.fixed, 0, sizeof(POLY_F4));
}

MATCH void func_801F9CAC(void) {
    SYS_DISPATCH_BYTE(D_801FE66C, D_80146872);
}

MATCH void func_801F9CE8(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F9CFC);

MATCH void func_801FA6BC(u8 point) {
    u8  slot;
    s32 row;
    s32 x;
    s32 y;

    Game_SetScriptActive();
    g_ScriptVars[0] = 1;
    slot            = Actor_FindFreeSpawned();
    D_801FE748      = slot;
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags = 1;
        g_SpawnedActors[D_801FE748].type   = 0x89;
        g_SpawnedActors[D_801FE748].link   = point;
    }
    row                 = point * 10;
    g_AreaScrollTargetX = LOH(D_801FE608[row]) << 8;
    g_AreaScrollTargetY = LOH(D_801FE608[row + 2]) << 8;
    Area_InitMapRenderer();
    g_Game.unk_3CE[2] = 0;
    Scene_SetupParty(0);
    x = LOH(D_801FE608[row + 4]) << 8;
    y = LOH(D_801FE608[row + 6]) << 8;
    g_Game.walk_flags &= ~AREA_WALK_ACCEPT_LOCK;
    func_801BFE34(x, y, D_801FE608[row + 9]);
    g_AreaDrawMode        = 4;
    g_SceneState.state_04 = 2;
    g_SceneState.step_05  = 0;
}

#include "overlays/scenario/Scene_SpawnActor.h"

MATCH bool Scene_SpawnActor(u8 type, s16 angle_x, s16 angle_y, s16 angle_z, u8 layer, s32 scene_step){SCENE_SPAWN_ACTOR(D_801FE748)}

MATCH void func_801FA998(void) {
    SYS_DISPATCH_BYTE(D_801FE678, g_SceneState.state_04);
}

MATCH void func_801FA9D4(void) {
}
