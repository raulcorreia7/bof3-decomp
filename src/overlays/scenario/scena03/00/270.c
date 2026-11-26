#include "scena03_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801F6EB4(void) {
    u8*  work;
    u8*  data;
    u8*  cell;
    u8   cell4;
    u32  cell3;
    s16* scratch;

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

    scratch                                    = (s16*)g_ScratchPad.cells.bytes;
    data                                       = (u8*)D_801FCF30;
    g_Actors[SELF(Actor)->unk_04].header.flags = 1;
    work                                       = SELF(u8);
    *scratch                                   = work[3];
    Actor_SpawnPartyFromRecord(data);
    Script_Begin(0x61, 0xC);
    *scratch = work[4];
    Actor_SpawnPartyFromRecord(data);
    Script_Begin(0x61, 0xC);
    SELF_SET(work);

    g_Actors[work[3]].pos.x.fixed += ONE;
    g_Actors[work[3]].pos.y.fixed -= ONE;
    g_Actors[work[4]].pos.x.fixed -= ONE;
    g_Actors[work[4]].pos.y.fixed += ONE;
    g_Actors[work[3]].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Actors[SELF(Actor)->unk_04].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    cell                           = SELF(u8);
    cell4                          = cell[4];
    cell3                          = cell[3];
    D_801468E4[cell4 * ACTOR_SIZE] = 0;
    D_801468E4[cell3 * ACTOR_SIZE] = 0;
    GFX_PaletteAllocFade(&g_Actors[work[3]], 15, 0, 0, 1);
    GFX_PaletteAllocFade(&g_Actors[work[4]], 0, 0, 15, 1);
    SELF(Actor)->timer       = 4;
    SELF(Actor)->header.mode = 1;
}

MATCH void func_801F7260(void) {
    if (SELF(Actor)->timer != 0) {
        g_Game.members->header.flags |= 0x40;
        SELF(Actor)->timer -= 1;
        return;
    }
    g_Game.members->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
    g_Actors[SELF(Actor)->unk_03].header.flags = 0;
    g_Actors[SELF(Actor)->unk_04].header.flags = 0;
    SELF(Actor)->header.mode                   = 2;
}

#include "shared/Actor_FreePaletteFades.h"

MATCH void func_801F73BC(void) {
    RECT     rect;
    DR_MOVE* prim;

    if (SELF(Actor)->timer == 0) {
        prim = (DR_MOVE*)g_GfxPrimCursor;
        setRECT(&rect, *(&D_801FCF40 + SELF(Actor)->header.mode * 2) / 4 + 0x2C0, *(&D_801FCF42 + SELF(Actor)->header.mode * 2) + 0x100, 0x10, 0x28);
        SetDrawMove(prim, &rect, D_801FCF40 / 4 + 0x2C0, D_801FCF42 + 0x100);
        SELF(Actor)->header.mode++;
        SELF(Actor)->draw_layer = 0;
        SELF(Actor)->timer      = SELF(Actor)->header.mode;
        GFX_AddPrim(SELF(Actor)->draw_layer, sizeof(DR_MOVE));
        if (SELF(Actor)->header.mode == 4) {
            Actor_Clear();
        }
    } else {
        SELF(Actor)->timer--;
    }
}

MATCH void func_801F7508(void) {
    SYS_DISPATCH_TASK(D_801FCF50, 1, g_Self);
}

#include "overlays/Actor_StartFadePair.h"

MATCH void func_801F754C(void) {
    ACTOR_START_FADE_PAIR(D_801FCF5C);
}

#include "shared/Actor_Reveal.h"

MATCH void Actor_FreePaletteFades2(void) {
    ACTOR_FREE_PALETTE_FADES();
}

MATCH void func_801F7A9C(void) {
    SYS_DISPATCH_TASK(D_801FCF70, 1, g_Self);
}

MATCH void func_801F7AE0(void) {
    u8* work;

    work    = SELF(u8);
    work[9] = 0xF;
    work    = SELF(u8);
    work[1]++;
}

MATCH void func_801F7B10(void) {
    Actor* actor;
    s32*   ptr;
    u8     value;

    actor = SELF(Actor);
    ptr   = &actor->vx;
    func_801F7FFC((Scena03Quad*)ptr);
    func_801F8170(ptr);
    actor->tint.halves.unk_5E += 1;
    value              = SELF(Actor)->timer - 1;
    SELF(Actor)->timer = value;
    if (!(value & BYTE_MASK)) {
        SELF(Actor)->timer = 8;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801F7BB0(void) {
    Actor* actor;
    s32*   ptr;
    u8     value;

    actor = SELF(Actor);
    ptr   = &actor->vx;
    func_801F7FFC((Scena03Quad*)ptr);
    func_801F8170(ptr);
    actor->script_pc += 4;
    value              = SELF(Actor)->timer - 1;
    SELF(Actor)->timer = value;
    if (!(value & BYTE_MASK)) {
        SELF(Actor)->timer = 8;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801F7C50(void) {
    s32* ptr;
    u8   value;

    ptr = &SELF(Actor)->vx;
    func_801F7FFC((Scena03Quad*)ptr);
    func_801F8170(ptr);
    value              = SELF(Actor)->timer - 1;
    SELF(Actor)->timer = value;
    if (!(value & BYTE_MASK)) {
        SELF(Actor)->timer = 128;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801F7CE0(void) {
    Actor* work;
    s32*   pos;
    u8     remaining;

    work = SELF(Actor);
    pos  = &work->vx;
    func_801F7FFC((Scena03Quad*)pos);
    func_801F8170(pos);
    work->frame_cells -= 8;
    work->tint.halves.unk_5C -= 0x40;
    remaining          = SELF(Actor)->timer - 1;
    SELF(Actor)->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801F7D80(void) {
    Actor* work;
    s32*   pos;
    s16    script_pc;

    work = SELF(Actor);
    pos  = &work->vx;
    func_801F7FFC((Scena03Quad*)pos);
    func_801F8170(pos);
    script_pc       = work->script_pc - 8;
    work->script_pc = script_pc;
    if (script_pc < 0) {
        SELF(Actor)->unk_06 = 1;
        Actor_Clear();
    }
}

MATCH void func_801F7DF0(void) {
    SYS_DISPATCH_TASK(D_801FCF88, 1, g_Self);
}

MATCH void func_801F7E34(void) {
    Actor* work;

    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 9));
    work = SPAD(0u)->task;
    work->header.mode += 1;
}

MATCH void func_801F7E6C(void) {
    SpawnedActor** effects;
    SpawnedActor*  spawned;
    Actor*         record;
    Actor*         actor;
    u8             i;
    u8             slot;

    effects = (SpawnedActor**)&SELF(Actor)->vx;
    for (i = 0; i < 5; i++) {
        slot = Actor_FindFreeSpawned();
        if (slot != GAME_NONE) {
            spawned                    = &g_SpawnedActors[slot];
            effects[i]                 = spawned;
            spawned->header.flags      = 1;
            spawned->unk_06            = 0;
            spawned->type              = 0x21;
            actor                      = SELF(Actor);
            spawned->vx                = actor->pos.x.fixed;
            spawned->selection         = actor->pos.y.fixed;
            spawned->unk_14            = actor->pos.z.fixed;
            record                     = (Actor*)spawned;
            record->script_pc          = 6;
            record->frame_cells        = 0;
            record->tint.halves.unk_5C = i * 819;
            record->tint.halves.unk_5E = 0;
        }
    }
    SELF(Actor)->header.mode += 1;
}

MATCH void func_801F7F84(void) {
    SpawnedActor** effects; /* the five effect slots spawned at +0x0C */
    u8             i;

    effects = (SpawnedActor**)&SELF(Actor)->vx;
    for (i = 0; i < 5; i++) {
        if (effects[i]->unk_06 == 0) {
            return;
        }
    }
    g_ScriptVars[0] += 1;
    Actor_Clear();
}

MATCH void func_801F7FFC(Scena03Quad* quad) {
    MATRIX mat;
    VECTOR in;
    VECTOR out;
    s32    dx;
    s32    dy;
    u8     i;

    i  = 0;
    dx = (quad->length * rcos(quad->angle)) << 4;
    dy = (quad->length * rsin(quad->angle)) << 4;
    MATH_SetIdentity(&mat);
    RotMatrixY(quad->rotation_y, &mat);
    RotMatrixZ(quad->rotation_z, &mat);
    /* Retail applies the matrix once to the uninitialised vector before the loop. */
    ApplyMatrixLV(&mat, &in, &out);
    in.vz = 0;
    do {
        switch (i) {
            case 0:
                in.vx = 0;
                in.vy = 0;
                break;
            case 1:
                in.vx = dx;
                in.vy = dy;
                break;
            case 2:
                in.vx = dx;
                in.vy = 0;
                break;
            default:
                in.vx = dx;
                in.vy = -dy;
                break;
        }
        ApplyMatrixLV(&mat, &in, &out);
        quad->corner[i].vx = quad->x + out.vx;
        quad->corner[i].vy = quad->y + out.vy;
        quad->corner[i].vz = quad->z + (out.vz << 8);
        i++;
    } while (i < 4);
}

MATCH void func_801F8170(s32* vertices) {
    MATRIX camera;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    Camera_SetMatrix(&camera);
    func_801F8200(vertices, 0, 1, 2);
    func_801F8200(vertices, 0, 3, 2);
}

MATCH void func_801F8200(s32* vertices, s32 v0, s32 v1, s32 v2) {
    POLY_G3* primitive;
    s32*     point_0;
    s32*     point_1;
    s32*     point_2;

    point_0   = (s32*)((u8*)vertices + (((u8)v0 << 4) + 0xC));
    point_1   = (s32*)((u8*)vertices + (((u8)v1 << 4) + 0xC));
    point_2   = (s32*)((u8*)vertices + (((u8)v2 << 4) + 0xC));
    primitive = GFX_BeginPolyG3(1);
    Camera_ProjectPoint(point_0, (DVECTOR*)&primitive->x0);
    Camera_ProjectPoint(point_1, (DVECTOR*)&primitive->x1);
    Camera_ProjectPoint(point_2, (DVECTOR*)&primitive->x2);
    setRGB0(primitive, 0x40, 0x40, 0x40);
    setRGB1(primitive, 0, 0, 0);
    setRGB2(primitive, 0x80, 0x80, 0x80);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G3));
}

MATCH void func_801F82E4(void) {
    SYS_DISPATCH_TASK(D_801FCF94, 1, g_Self);
}

MATCH void func_801F8328(void) {
    SELF(Actor)->timer = 96;
    SELF(Actor)->header.mode++;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 4));
}

MATCH void func_801F8370(void) {
    SpawnedActor* actor;
    s32           actor_index;
    u8            remaining;

    if (SELF(Actor)->timer & 0x4) {
        actor_index = func_8019601C() & BYTE_MASK;
        if (actor_index != 0xFF) {
            actor               = &g_SpawnedActors[actor_index];
            actor->header.flags = 1;
            actor->type         = 0x24;
        }
    }
    remaining          = SELF(Actor)->timer - 1;
    SELF(Actor)->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801F842C(void) {
    Actor_Clear();
}

MATCH void func_801F844C(void) {
    SYS_DISPATCH_TASK(D_801FCFA0, 1, g_Self);
}

MATCH void func_801F8490(void) {
    Scena03Work* work;

    work                   = SELF(Scena03Work);
    work->line.radius      = 0x600;
    work->line.start_scale = 0x100;
    work->line.end_scale   = 0x100;
    work->line.yaw         = rand() & 0x700;
    work->line.pitch       = rand() & 0xF00;
    work->line.color.b     = 255;
    work->line.color.g     = 255;
    work->line.color.r     = 255;
    if (rand() & 1) {
        work->line.color.r = 0;
    }
    if (rand() & 1) {
        work->line.color.b = 0;
    }
    SELF(Actor)->header.mode++;
}

MATCH void func_801F853C(void) {
    Scena03Work* work;
    s16          value;

    work = SELF(Scena03Work);
    func_801F88FC(&work->line);
    value                  = work->line.start_scale - 0x10;
    work->line.start_scale = value;
    if (value < 0) {
        work->line.start_scale = 0;
    }
    if (work->line.start_scale < 0x80) {
        work->line.end_scale -= 0x10;
    }
    if (work->line.end_scale < 0) {
        work->line.start_scale = 0;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801F85DC(void) {
    Actor_Clear();
}

MATCH void func_801F85FC(void) {
    SYS_DISPATCH_TASK(D_801FCFAC, 1, g_Self);
}

#include "shared/Actor_TrackFocus.h"

MATCH void func_801F8710(void) {
    GFX_DrawShadedDisc((s16)SELF(Actor)->screen_x, (s16)SELF(Actor)->screen_y, SELF(Actor)->timer, 0x80, 0);
    SELF(Actor)->timer += 15;
    if (SELF(Actor)->timer >= 61) {
        SELF(Actor)->timer = 255;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801F87A4(void) {
    u8 count;

    GFX_DrawShadedDisc((s16)SELF(Actor)->screen_x, (s16)SELF(Actor)->screen_y, (SELF(Actor)->timer & 0x1) | 0x3C, 0x80, 0);
    if (SELF(Actor)->timer == 215) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 8));
    }
    count              = SELF(Actor)->timer - 1;
    SELF(Actor)->timer = count;
    if (count == 0) {
        SELF(Actor)->timer = 60;
        SELF(Actor)->header.mode += 1;
    }
}

/* Shrinks the disc effect. */
/* func_801F885C */
MATCH void Area_ShrinkDisc(void) {
    GFX_DrawShadedDisc((s16)SELF(Actor)->screen_x, (s16)SELF(Actor)->screen_y, SELF(Actor)->timer, 0x80, 0);
    SELF(Actor)->timer -= 1;
    if ((s8)SELF(Actor)->timer < 0) {
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801F88DC(void) {
    Actor_Clear();
}

MATCH void func_801F88FC(Scena03Line* line) {
    VECTOR   point;
    VECTOR   rot;
    VECTOR   prev;
    MATRIX   camera;
    LINE_G2* primitive;
    s16      scale;
    s8       i;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    i = 0;
    setVector(&rot, (rsin(line->yaw) * rcos(line->pitch)) >> 8, (rsin(line->yaw) * rsin(line->pitch)) >> 8, rcos(line->yaw) << 4);
    Camera_SetMatrix(&camera);
    do {
        primitive = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(primitive);
        SetSemiTrans(primitive, 1);

        scale = (line->radius * line->start_scale) >> 8;
        setVector(&point, g_Game.members[0].pos.x.fixed + ((scale * rot.vx) >> 8), g_Game.members[0].pos.y.fixed + ((scale * rot.vy) >> 8), g_Game.members[0].pos.z.fixed + (scale * rot.vz));
        Camera_ProjectPoint(&point.vx, (DVECTOR*)&primitive->x0);
        setRGB0(primitive, (line->start_scale * line->color.r) >> 8, (line->start_scale * line->color.g) >> 8, (line->start_scale * line->color.b) >> 8);

        scale = (line->radius * line->end_scale) >> 8;
        setVector(&point, g_Game.members[0].pos.x.fixed + ((scale * rot.vx) >> 8), g_Game.members[0].pos.y.fixed + ((scale * rot.vy) >> 8), g_Game.members[0].pos.z.fixed + (scale * rot.vz));
        Camera_ProjectPoint(&point.vx, (DVECTOR*)&primitive->x1);
        setRGB1(primitive, (line->end_scale * line->color.r) >> 8, (line->end_scale * line->color.g) >> 8, (line->end_scale * line->color.b) >> 8);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_G2));

        i++;
        prev   = rot;
        rot.vx = -prev.vy;
        rot.vy = prev.vx;
    } while (i < 4);
}

#include "shared/GFX_DrawShadedDisc.h"

MATCH void func_801F8DA8(void) {
    SYS_DISPATCH_BYTE(D_801FCFD4, D_80146872);
}

MATCH void func_801F8DE4(void) {
    D_80146872 = 1;
    D_80144EA0 = 0;
}

MATCH void func_801F8E00(void) {
    if (g_GameAreaId == AREA_ID_WYNDIA_LOWER && !SYS_TestFlag(g_SceneFlags, 0x15)) {
        g_AreaDrawFlags = 0x1F;
    }
    if (g_GameAreaId == AREA_ID_WYNDIA_UPPER) {
        Area_CellSetCode(0xC, 0x1C, 0);
        Area_CellSetCode(0xC, 0x1E, 0);
    }
    if (g_GameAreaId == AREA_ID_WYNDIA_CASTLE && !SYS_TestFlag(g_SceneFlags, 3)) {
        ((ScriptVarsRecord*)g_ScriptVars)->word = 0;
        g_AreaDrawFlags                         = 0;
    }
    if (g_GameAreaId == AREA_ID_WYNDIA_CASTLE_BASEMENT && !SYS_TestFlag(g_SceneFlags, 3)) {
        g_ScenarioState.timer_06                = 60;
        g_AreaCameraAngle.vx                    = -0x344;
        ((ScriptVarsRecord*)g_ScriptVars)->word = 0;
        g_AreaCameraAngle.vy                    = 0;
        g_AreaCameraAngle.vz                    = 0x10E;
        Scene_SetupParty(0);
    }
    if (g_GameAreaId == AREA_ID_WYNDIA_WORLD_MAP) {
        if (SYS_TestFlag(g_SceneFlags, 1) && !SYS_TestFlag(g_SceneFlags, 2)) {
            Game_SetScriptActive();
            Scene_RunScenario(0);
            ((ScriptVarsRecord*)g_ScriptVars)->word = 0;
            Area_ScrollAdvance(448);
            g_AreaCameraOffsetZ = 0x2BC;
            Area_ScrollStartRoute(1);
        }
        if (SYS_TestFlag(g_SceneFlags, 0x18) && !SYS_TestFlag(g_SceneFlags, 0x19)) {
            Game_SetScriptActive();
            g_AreaCameraAngle.vx = -0x2EC;
            g_AreaCameraAngle.vz = 0x376;
            Area_ScrollStartRoute(2);
            g_AreaDrawFlags = 0x1F;
        }
    }
    if (g_GameAreaId == AREA_ID_GENMEL) {
        ((ScriptVarsRecord*)g_ScriptVars)->word = 0;
    }
    if (g_GameAreaId == AREA_ID_WYNDIAN_CATACOMBS && g_GameCellType == 1 && !SYS_TestFlag(g_SceneFlags, 0xF)) {
        SYS_SetFlag(g_SceneFlags, 0xF);
        ((ScriptVarsRecord*)g_ScriptVars)->word = 0;
        Scene_SetupParty(0);
    }
    if (g_GameAreaId == AREA_ID_EYGNOCK_ROAD) {
        if (g_GameCellType == 0) {
            if (!SYS_TestFlag(g_SceneFlags, 0x16)) {
                Scene_SetupParty(3);
                SYS_SetFlag(g_SceneFlags, 0x16);
            } else if (g_GameLastCellType == 1 && !SYS_TestFlag(g_SceneFlags, 0x18)) {
                Game_SetScriptActive();
                SND_BGMFadeOut(g_SndBGMId, 100, 8);
                SND_BGMPlay(20, 0, 8);
                D_80146258 |= 0x80;
                Scene_SetupParty(5);
                SYS_SetFlag(g_SceneFlags, 0x18);
                g_ScenarioState.state_04 = 5;
                g_ScenarioState.step     = 2;
            }
        }
        if (g_GameCellType == 1 && !SYS_TestFlag(g_SceneFlags, 0x17)) {
            func_801C1E3C(0);
            Scene_SetupParty(4);
            SND_SEPlay(0x201);
            SYS_SetFlag(g_SceneFlags, 0x17);
        }
    }
    if (g_GameAreaId == AREA_ID_MOUNT_BOUMORE_SECOND && !SYS_TestFlag(g_SceneFlags, 0x1E)) {
        Area_CellSetCode(0x19, 0x77, 0x50);
        Area_CellSetCode(0x19, 0x78, 0x50);
        Area_CellSetCode(0x19, 0x79, 0x50);
    }
    if (g_GameAreaId == AREA_ID_MOUNT_BOUMORE_FIRST && !SYS_TestFlag(g_SceneFlags, 0x1B)) {
        if (g_GameCellType == 2) {
            g_AreaDrawFlags = 0x1F;
        }
        if (g_GameCellType == 3) {
            Game_SetScriptActive();
            ((ScriptVarsRecord*)g_ScriptVars)->word = 0;
            g_AreaScrollTargetX                     = 0x58000;
            g_AreaScrollTargetY                     = 0xB8000;
            Scene_SetupParty(1);
            g_AreaDrawFlags = 0;
            SYS_SetFlag(g_SceneFlags, 0x1B);
            g_ScenarioState.timer_06 = 30;
            g_ScenarioState.state_04 = 6;
            g_ScenarioState.step     = 6;
        }
    }
    g_ScenarioState.mode_02 = 2;
}

MATCH void func_801F92F4(void) {
    SYS_DISPATCH_BYTE(D_801FCFE0, g_ScenarioState.state_04);
}

MATCH void func_801F9330(void) {
}
