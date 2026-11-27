#include "scena04_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801F6D44(void) {
    SceneBox* box;
    Actor*    work;

    work              = SELF(Actor);
    box               = (SceneBox*)&work->vx;
    work->vz          = TO_COORD(256);
    box->far.pos.vz   = TO_COORD(256);
    work->vx          = 5668864;
    work->vy          = 1212416;
    work->unk_1C      = 0;
    work->gravity     = TO_COORD(544);
    box->far.pos.vx   = 5668864;
    box->far.pos.vy   = 1212416;
    work->pos.x.fixed = 0x4000;
    work->pos.y.fixed = TO_COORD(544);
    func_801F747C();
    SELF(Actor)->timer = 8;
    SELF(Actor)->header.mode += 1;
}

MATCH void func_801F6DD4(void) {
    Actor*    work;
    SceneBox* box;
    s32       fraction;

    work     = SELF(Actor);
    box      = (SceneBox*)&work->vx;
    fraction = (0x10 - work->timer * 2) & 0xFE;
    box->far.pos.vx += 0x10000;
    work->pos.x.fixed += 0x2000;
    work->pos.y.fixed += 0x220000;
    func_801F75BC(fraction, 0xFF);
    func_801F7084(box);
    if (--SELF(Actor)->timer == 0) {
        SELF(Actor)->timer = 0x40;
        SELF(Actor)->header.mode++;
    }
}

MATCH void func_801F6EA4(void) {
    Actor* work;
    Actor* actor;
    u8     mode;

    work = SELF(Actor);
    func_801F7084((SceneBox*)&work->vx);
    func_801F75BC(0x10, 0xFF);
    actor        = SELF(Actor);
    mode         = actor->timer - 1;
    actor->timer = mode;
    if (mode == 0) {
        SELF(Actor)->timer = 4;
        SELF(Actor)->header.mode += 1;
    }
}

/* Steps the scene's entrance focus one cell and fades out the shade as the timer runs down. */
MATCH void func_801F6F2C(void) {
    Actor* work;
    Actor* actor;
    u8     mode;
    u8     level;

    work              = SELF(Actor);
    work->unk_1C      = work->unk_1C + 0x4000;
    work->pos.x.fixed = work->pos.x.fixed + TO_COORD(1);
    func_801F7084(&work->vx);
    level = SELF(Actor)->timer;
    func_801F75BC(0x10, (level == 8) ? 0xFF : level << 5);
    actor        = SELF(Actor);
    mode         = actor->timer - 1;
    actor->timer = mode;
    if (mode == 0) {
        SELF(Actor)->timer = 32;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801F6FF8(void) {
    Actor* work;

    func_801F7084((SceneBox*)&SELF(Actor)->vx);
    work = SELF(Actor);
    work->timer--;
    if (work->timer == 0) {
        SELF(Actor)->header.mode++;
    }
}

MATCH void func_801F7064(void) {
    Actor_Clear();
}

/* Fill the eight vertex records of the box: each cross-section's corner point and its two half extents. */
MATCH void func_801F7084(SceneBox* box) {
    ScenePathPoint* vertex;
    s32*            scratch;
    u16             tpage;

    tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddDitheredDrawMode(GFX_LAYER_UI, tpage);
    vertex = D_801FA240;
    setVector(vertex, box->near.pos.vx, box->near.pos.vy + box->near.half_y, box->near.pos.vz + box->near.half_z);
    vertex++;
    setVector(vertex, box->near.pos.vx, box->near.pos.vy - box->near.half_y, box->near.pos.vz + box->near.half_z);
    vertex++;
    setVector(vertex, box->near.pos.vx, box->near.pos.vy + box->near.half_y, box->near.pos.vz);
    vertex++;
    setVector(vertex, box->near.pos.vx, box->near.pos.vy - box->near.half_y, box->near.pos.vz);
    vertex++;
    setVector(vertex, box->far.pos.vx, box->far.pos.vy + box->far.half_y, box->far.pos.vz + box->far.half_z);
    vertex++;
    setVector(vertex, box->far.pos.vx, box->far.pos.vy - box->far.half_y, box->far.pos.vz + box->far.half_z);
    vertex++;
    setVector(vertex, box->far.pos.vx, box->far.pos.vy + box->far.half_y, box->far.pos.vz);
    scratch = &vertex->vx;
    vertex++;
    setVector(vertex, box->far.pos.vx, box->far.pos.vy - box->far.half_y, box->far.pos.vz);
    Camera_SetMatrix(scratch);
    func_801F732C(0, 1, 2, 3, 1, 1);
    func_801F732C(0, 1, 4, 5, 1, 0);
    func_801F732C(2, 0, 6, 4, 1, 0);
    func_801F732C(1, 3, 5, 7, 1, 0);
    func_801F732C(2, 3, 6, 7, 1, 0);
}

/* Draws a Gouraud quad through four path points, two corners per shade, flickering with the frame parity. */
MATCH void func_801F732C(u8 v0, u8 v1, u8 v2, u8 v3, s32 shade0, s32 shade1) {
    POLY_G4* primitive;
    u8       color0;
    u8       color1;

    primitive = GFX_BeginPolyG4(1);
    Camera_ProjectPoint((s32*)&D_801FA240[v0], (DVECTOR*)&primitive->x0);
    Camera_ProjectPoint((s32*)&D_801FA240[v1], (DVECTOR*)&primitive->x1);
    Camera_ProjectPoint((s32*)&D_801FA240[v2], (DVECTOR*)&primitive->x2);
    Camera_ProjectPoint((s32*)&D_801FA240[v3], (DVECTOR*)&primitive->x3);
    color0 = (shade0 << 7) | ((g_FrameCount & 1) << 2);
    color1 = (shade1 << 7) | ((g_FrameCount & 1) << 2);
    setRGB0(primitive, color0, color0, color0 >> 1);
    setRGB1(primitive, color0, color0, color0 >> 1);
    setRGB2(primitive, color1, color1, color1 >> 1);
    setRGB3(primitive, color1, color1, color1 >> 1);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
}

MATCH void func_801F747C(void) {
    s32* key;

    key        = D_801FA2C0;
    *key       = 0x568000;
    D_801FA2C4 = 0x118000;
    D_801FA2C8 = TO_COORD(768);
    D_801FA2D0 = 0x5E8000;
    D_801FA2D4 = 0xF0000;
    D_801FA2D8 = TO_COORD(1024);
    key += 8;
    *key       = 0x568000;
    D_801FA2E4 = 0x118000;
    D_801FA2E8 = TO_COORD(576);
    D_801FA2F0 = 0x5E8000;
    D_801FA2F4 = 0xF0000;
    D_801FA2F8 = TO_COORD(576);
    key += 8;
    *key       = 0x568000;
    D_801FA304 = 0x138000;
    D_801FA308 = TO_COORD(768);
    D_801FA310 = 0x5E8000;
    D_801FA314 = 0x158000;
    D_801FA318 = TO_COORD(1024);
    key += 8;
    *key       = 0x568000;
    D_801FA324 = 0x138000;
    D_801FA328 = TO_COORD(640);
    D_801FA330 = 0x5E8000;
    D_801FA334 = 0x160000;
    D_801FA338 = TO_COORD(704);
    key += 8;
    *key       = 0x568000;
    D_801FA344 = 0x138000;
    D_801FA348 = TO_COORD(288);
    D_801FA350 = 0x5E8000;
    D_801FA354 = 0x160000;
    D_801FA358 = TO_COORD(288);
}

#define KEY_WORD(off, n) (*(s32*)((u8*)D_801FA2C0 + (off) + (n) * 4))

MATCH void func_801F75BC(u8 weight, u8 shade) {
    LINE_G2* line;
    s32      point[3];
    u8       i;
    u32      off;
    u32      flicker;
    u8       first_tint;
    s16      tint;

    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    ((void (*)(void))Camera_SetMatrix)();
    for (i = 0; i < 5; i++) {
        line = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(line);
        SetSemiTrans(line, 1);
        off      = i << 5;
        point[0] = (((KEY_WORD(off, 4) - KEY_WORD(off, 0)) * weight) >> 4) + KEY_WORD(off, 0);
        point[1] = (((KEY_WORD(off, 5) - KEY_WORD(off, 1)) * weight) >> 4) + KEY_WORD(off, 1);
        point[2] = (((KEY_WORD(off, 6) - KEY_WORD(off, 2)) * weight) >> 4) + KEY_WORD(off, 2);
        Camera_ProjectPoint((s32*)((u8*)D_801FA2C0 + off), (DVECTOR*)&line->x0);
        Camera_ProjectPoint(point, (DVECTOR*)&line->x1);
        flicker    = (g_FrameCount & 1) << 2;
        first_tint = (u8)(((flicker + 0x80) * shade) >> 8);
        setRGB0(line, ((flicker + 0x80) * shade) >> 8, ((flicker + 0x80) * shade) >> 8, first_tint >> 1);
        tint = (flicker * shade) >> 8;
        setRGB1(line, tint, tint, (u8)tint >> 1);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_G2));
    }
}

MATCH void func_801F77A8(void) {
    SYS_DISPATCH_TASK(D_801FA198, 1, g_Self);
}

MATCH void func_801F77EC(void) {
    ScenePath* work;
    u8         i;

    work = MEM_PTR(ScenePath, AREA_WORK + 0x1400);
    setVector(&work->focus, g_PartyActors[0].pos.x.fixed, g_AreaFocus.y.fixed, g_PartyActors[0].pos.z.fixed >> 8);
    i = 0;
    do {
        work->points[i].vx = work->focus.vx + D_801FA1A4[i];
        work->points[i].vy = work->focus.vy + D_801FA1C4[i];
        {
            Coord sample_x = {work->points[i].vx};
            Coord sample_y = {work->points[i].vy};

            work->points[i].vz = (s16)Area_HeightSample(sample_x.fixed, sample_y.fixed) << 8;
        }
        i++;
    } while (i < ARRAY_COUNT(work->points));
    func_801F7FCC();
    SELF(Actor)->vx = 512;
    SELF(Actor)->header.mode++;
}

/* Every 16 ticks, spawn a particle from the path origin toward each path point; then follow the focus and leave on the last tick. */
MATCH void func_801F78F4(void) {
    /* FAKE: retail reserves 16 bytes of unused stack. */
    FAKE_STACK_PADS(u8, 16);
    ScenePath*     work;
    SceneParticle* particle;
    u8             i;

    work = MEM_PTR(ScenePath, AREA_WORK + 0x1400);
    if ((SELF(Actor)->vx & 0xF) == 0) {
        i = 0;
        do {
            particle = (SceneParticle*)func_801F7FF8();
            if (particle != NULL) {
                *(ScenePathPoint*)particle = *(ScenePathPoint*)work;
                particle->velocity.vx      = (work->points[i].vx - work->focus.vx) >> 4;
                particle->velocity.vy      = (work->points[i].vy - work->focus.vy) >> 4;
                particle->velocity.vz      = (work->points[i].vz - work->focus.vz) >> 4;
                VectorNormal(&particle->velocity.vx, &particle->velocity.vx);
                particle->unk_24 = 0x80;
                particle->unk_20 = 0x1000;
                particle->life   = 0x80;
            }
            i++;
        } while (i < 8);
    }
    setVector(&work->focus, g_PartyActors[0].pos.x.fixed, g_AreaFocus.y.fixed, g_PartyActors[0].pos.z.fixed >> 8);
    func_801F7EC0();
    if (--SELF(Actor)->vx == 0) {
        SELF(Actor)->header.mode++;
    }
}

MATCH void func_801F7A64(void) {
    Actor_Clear();
}

MATCH void func_801F7A84(void) {
    SYS_DISPATCH_TASK(D_801FA1E4, 1, g_Self);
}

MATCH void func_801F7AC8(void) {
    Actor* work;

    func_801F7FCC();
    work = SELF(Actor);
    work->header.mode += 1;
}

MATCH void func_801F7B00(void) {
    /* FAKE: unused frame, 16 bytes; `particle` and `shade` also stay uninitialized
       when the frame count skips the spawn, as in retail. */
    FAKE_STACK_PADS(u8, 16);
    u8* particle;
    s32 shade;
    s32 height;

    if ((g_FrameCount & 0x7) == 0) {
        particle = func_801F7FF8();
        shade    = 0x80;
        if (particle != NULL) {
            FIELD(s32, particle, 0x00) = D_80146954;
            FIELD(s32, particle, 0x04) = g_Actors[1].pos.y.fixed;
            height                     = g_Actors[1].pos.z.fixed;
            FIELD(s32, particle, 0x10) = 0;
            FIELD(s32, particle, 0x14) = 0;
            FIELD(s32, particle, 0x18) = 0;
            FIELD(s8, particle, 0x24)  = shade;
            FIELD(s32, particle, 0x20) = 0x800;
            FIELD(s8, particle, 0x25)  = shade;
            FIELD(s32, particle, 0x08) = height >> 8;
        }
    }
    func_801F7EC0(shade, particle);
    if (g_ScriptVarsReq.byte == 3) {
        Scene_AdvanceActorMode();
    }
}

MATCH void func_801F7BC0(void) {
    u8*  particle;
    u8   i;
    s32  angle;
    s32* spot;

    i    = 0;
    spot = &D_80146954;
    for (; i < 16; i++) {
        particle = func_801F7FF8();
        if (particle != NULL) {
            FIELD(s32, particle, 0x00) = spot[0];
            angle                      = i << 8;
            FIELD(s32, particle, 0x04) = spot[1];
            FIELD(s32, particle, 0x08) = spot[2] >> 8;
            FIELD(s32, particle, 0x10) = rsin(angle) >> 2;
            FIELD(s32, particle, 0x14) = rcos(angle) >> 2;
            FIELD(s32, particle, 0x18) = 0;
            FIELD(s8, particle, 0x24)  = 0x40;
            FIELD(s32, particle, 0x20) = 0x800;
            FIELD(s8, particle, 0x25)  = 0x40;
        }
    }
    func_801F7EC0();
    SELF(Actor)->vx = 0x40;
}

MATCH void func_801F7CA8(void) {
    func_801F7EC0();
    SELF(Actor)->vx = SELF(Actor)->vx - 1;
    if (SELF(Actor)->vx == 0) {
        func_80196070();
    }
}

/* Draw one particle as a semi-transparent billboard quad at its projected position, shaded by its brightness. */
MATCH void func_801F7CF0(SceneParticle* particle) {
    POLY_FT4* prim;
    DVECTOR   screen;
    DVECTOR   scale;
    VECTOR    pos;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256) & HALF_MASK, 0);
    {
        Coord cell_x = {particle->pos.vx};
        Coord cell_y = {particle->pos.vy};

        Area_CellAddPrim(cell_x.fixed, cell_y.fixed, 1, sizeof(DR_MODE));
    }
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    screen.vx = (u32)particle->unk_20 >> 6;
    pos       = particle->pos;
    pos.vz <<= 8;
    Game_ProjectWorldPoint(&pos, &screen, &scale);
    Camera_ProjectPoint((s32*)&pos, &screen);
    prim->x0 = prim->x2 = screen.vx - scale.vx;
    prim->x1 = prim->x3 = screen.vx + scale.vx;
    prim->y0 = prim->y1 = screen.vy - scale.vx;
    prim->y2 = prim->y3 = screen.vy + scale.vx;
    setClut(prim, 160, STAGE_PALETTE_Y + 3);
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256);
    setUVWH(prim, 224, 48, 31, 31);
    setRGB0(prim, particle->unk_24, particle->unk_24, particle->unk_24);
    {
        Coord cell_x = {particle->pos.vx};
        Coord cell_y = {particle->pos.vy};

        Area_CellAddPrim(cell_x.fixed, cell_y.fixed, 1, sizeof(POLY_FT4));
    }
}

MATCH void func_801F7EC0() {
    u8             camera[32];
    SceneParticle* particle;
    u8             i;
    s32            height;

    Camera_SetMatrix(camera);
    particle = MEM_PTR(SceneParticle, AREA_WORK);
    for (i = 0; i < 128; particle++, i++) {
        if (particle->life != 0) {
            func_801F7CF0(particle);
            particle->pos.vx += particle->velocity.vx;
            particle->pos.vy += particle->velocity.vy;
            particle->pos.vz += particle->velocity.vz;
            height = Area_HeightSample(particle->pos.vx, particle->pos.vy);
            if (particle->pos.vz < height) {
                particle->pos.vz      = height;
                particle->velocity.vz = 0;
                VectorNormal(&particle->velocity.vx, &particle->velocity.vx);
            }
            particle->unk_24--;
            particle->unk_20 += 4;
            particle->life--;
        }
    }
}

MATCH void func_801F7FCC(void) {
    s32   index;
    void* cell;

    cell  = (void*)AREA_WORK;
    index = 0;
    do {
        FIELD(s8, cell, 0x25u) = 0;
        index += 1;
        cell += 0x28;
    } while ((index & BYTE_MASK) < 0x80U);
}

MATCH u8* func_801F7FF8(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK);
    for (i = 0; i < 128; i++) {
        if (p[SCRATCH_ROW_OFFSET] == 0) {
            return p;
        }
        p += SCRATCH_ROW_STRIDE;
    }
    return NULL;
}

/* Area_CellAddPrim with the caller's tag stored in the slot and an unmasked size. */
MATCH void func_801F8034(s32 x, s32 y, s32 depth, s32 size, u32 tag) {
    u8*  cursor;
    u8*  next;
    u8*  packet;
    u32* slot;
    u32  offset;
    u32  limit;
    s32  index;
    s32  value;
    s32  cell;
    s32  seed;
    s32  count;
    s32  addend;

    index = (x >> 16) - g_AreaTileOriginX;
    value = (y >> 16) - g_AreaTileOriginY;
    if (x & HALF_MASK) {
        value += 1;
    }
    /* FAKE: keeps index in its own pseudo so the sum lands in a fresh register, as in Area_CellAddPrim. */
    index++;
    index--;
    cell = index;
    cell += value;
    seed = (s8)depth;
    if (y & HALF_MASK) {
        addend = seed + 1;
        count  = cell + addend;
    } else {
        count = cell + seed;
    }
    if ((u32)count < 56) {
        cursor = g_GfxPrimCursor;
        limit  = g_GfxBufferIndex * 0x9000 + PRIM_ARENA_BASE;
        next   = cursor + size;
        if (next < limit) {
            offset = (g_GfxBufferIndex + 4) * 8 + count * 0x30;
            packet = *(u8**)(D_80142CC4 + offset);
            setaddr(packet, cursor);
            g_GfxPrimCursor = next;
            slot            = (u32*)(D_80142CC4 + offset);
            *slot           = tag;
        }
    }
}

MATCH void func_801F8124(void) {
    SYS_DISPATCH_BYTE(D_801FA204, D_80146872);
}

MATCH void func_801F8160(void) {
    D_80146872 = 1;
    D_80144EA8 = 0;
}

/* Momo Tower First Floor: run the scene hand-over for area 0x28, then the area 0x2A, 0x30, 0x36 and 0x41 tail. */
MATCH void func_801F817C(void) {
    u8  index;
    u8* slot;
    u8* pad_flag;

    if (g_GameAreaId == AREA_ID_MOMO_TOWER_FIRST_FLOOR) {
        if (g_GameCellType == 7) {
            if (SYS_TestFlag(g_SceneFlags, 3) == 0) {
                SYS_SetFlag(g_SceneFlags, 3);
                g_ScriptVarsWord = 0;
                SND_BGMFadeOut(g_SndBGMId, 0x64, 8);
                SND_BGMPlay(0x3F, 0x64, 8);
                Game_SetScriptActive();
                g_ScenarioState.state_04 = 1;
                g_ScenarioState.step     = 7;
                Scene_RunScenario(1);
                Scene_SetupParty(1);
            }
        }
        if (SYS_TestFlag(g_SceneFlags, 4) != 0) {
            if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
                switch (g_ScriptVars[1]) {
                    case 0:
                        g_AreaDrawFlags = 0x1F;
                        break;
                    case 1:
                        Area_ScrollStartRoute(1);
                    case 2:
                    default:
                        Party_BattlersHide();
                        break;
                }
            }
        }
    }
    if (g_GameAreaId == AREA_ID_MOMO_TOWER_OUTSIDE) {
        if (SYS_TestFlag(g_SceneFlags, 1) == 0) {
            SYS_SetFlag(g_SceneFlags, 1);
            g_ScriptVarsWord = 0;
            Scene_RunScenario(0);
            Scene_SetupParty(0);
        }
        if (SYS_TestFlag(g_SceneFlags, 3) != 0) {
            if (SYS_TestFlag(g_SceneFlags, 4) == 0) {
                Party_BattlersHide();
                g_AreaDrawFlags = 0x1F;
            }
        }
    }
    if (g_GameAreaId == AREA_ID_MOMO_TOWER_TOP) {
        if (g_GameCellType == 3) {
            g_ScriptVarsWord = 0;
            if (SYS_TestFlag(g_SceneFlags, 6) == 0) {
                SYS_SetFlag(g_SceneFlags, 6);
                D_80143F1D = 5;
                Scene_SetupParty(3);
            }
            if (SYS_TestFlag(g_SceneFlags, 7) == 0) {
                Area_CellSetCode(0x83, 6, 0x51);
                Area_CellSetCode(0x84, 6, 0x51);
            }
        }
    }
    if (g_GameAreaId == AREA_ID_ROCKET_LANDING) {
        g_ScriptVarsWord = 0;
    }
    if (g_GameAreaId == AREA_ID_MOMO_TOWER_WORLD_MAP) {
        if (SYS_TestFlag(g_SceneFlags, 7) != 0) {
            if (SYS_TestFlag(g_SceneFlags, 0xC) == 0) {
                g_ScriptVarsWord = 0;
                Area_ScrollStartRoute(0);
                pad_flag = &g_Game.members[0].unk_24;
                *pad_flag &= 0xDF;
                g_Game.members[1].unk_24 &= 0xDF;
                g_Game.members[2].unk_24 &= 0xDF;
                /* kept: the slot index round-trips through the scratch word so
                 * each row address re-reads it; a local index drops 0xA8 bytes
                 * (0x418 vs 0x4C0) and typed g_SpawnedActors rows drop 0xC0. */
                slot  = (u8*)&g_ScratchPad;
                index = Actor_FindFreeSpawned();
                *slot = index;
                if (index != 0xFF) {
                    D_80143FC8[*slot * 0x74u]             = 1;
                    D_80143FCD[*slot * 0x74u]             = 0x13;
                    FIELD(s32, D_8014402C, *slot * 0x74u) = -0xC6;
                    FIELD(s32, D_80144030, *slot * 0x74u) = D_801492DA;
                    FIELD(s32, D_80144034, *slot * 0x74u) = D_801492DC;
                    D_80143FD1[*slot * 0x74u]             = 0x40;
                }
                index = Actor_FindFreeSpawned();
                *slot = index;
                if (index != 0xFF) {
                    D_80143FC8[*slot * 0x74u] = 1;
                    D_80143FCD[*slot * 0x74u] = 0x2E;
                }
            }
        }
    }
    D_80146872 = 2;
}

MATCH void func_801F863C(void) {
    SYS_DISPATCH_BYTE(D_801FA210, g_ScenarioState.state_04);
}

MATCH void func_801F8678(void) {
}
