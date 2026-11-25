#include "area049_13.h"
#include "overlays/area/shared/AreaSprite.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_8011700C(void) {
    /* Retail reads the handler record from the entry $v0; the uninitialised local reads it. */
    u8* entity;

    SYS_DISPATCH_TASK(D_8011818C, 1, entity);
}

MATCH void func_80117048(void) {
    TASK(Actor)->pos.x.fixed = TO_COORD(11) + COORD_HALF;
    TASK(Actor)->pos.y.fixed = TO_COORD(84) + COORD_HALF;
    TASK(Actor)->pos.z.fixed = TO_COORD(256);
    func_801172D0();
    TASK(Actor)->header.mode += 1;
}

MATCH void func_801170A4(void) {
    if (!(func_80117410() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801170D8(AreaSprite* sprite) {
    DVECTOR   screen;
    u16       size[2];
    s32*      object;
    POLY_FT4* primitive;
    u8        flags;
    u8        red;
    u8        green;
    u8        blue;

    object    = (s32*)&sprite->origin;
    primitive = (POLY_FT4*)g_GfxPrimCursor;

    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);

    Camera_ProjectPoint(object, &screen);
    size[0] = sprite->half_size;
    size[1] = sprite->half_size;
    Game_ProjectWorldPoint(object, size, size);

    setXY4(primitive, screen.vx - ((s16)size[0] >> 1), screen.vy - ((s16)size[1] >> 1), (screen.vx - ((s16)size[0] >> 1)) + size[0], screen.vy - ((s16)size[1] >> 1), screen.vx - ((s16)size[0] >> 1),
           (screen.vy - ((s16)size[1] >> 1)) + size[1], (screen.vx - ((s16)size[0] >> 1)) + size[0], (screen.vy - ((s16)size[1] >> 1)) + size[1]);
    /* The tile rectangle and texture page have no owner names; every matched sibling spells
     * these values raw. The palette row is the stage palette plus three rows. */
    setUV4(primitive, 224, 48, 255, 48, 224, 79, 255, 79);
    setClut(primitive, 80, STAGE_PALETTE_Y + 3);
    primitive->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256);
    flags            = sprite->unk_26;
    red              = 0;
    if (flags & 4) {
        red = sprite->tick;
    }
    green = 0;
    if (flags & 2) {
        green = sprite->tick;
    }
    blue = 0;
    if (flags & 1) {
        blue = sprite->tick;
    }
    setRGB0(primitive, red, green, blue);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_FT4));
}

MATCH void func_801172D0(void) {
    Actor*      actor;
    AreaSprite* work;
    u8          i;
    s32         speed;
    u16         angle;

    D_801181DC = MEM_PTR(AreaSprite, AREA_WORK);
    i          = 0;
    do {
        actor                 = TASK(Actor);
        work                  = D_801181DC;
        work->origin.x        = actor->pos.x.fixed;
        work->origin.y        = actor->pos.y.fixed;
        work->origin.z        = actor->pos.z.fixed;
        speed                 = RANDOM_MASK(0x7F);
        angle                 = RANDOM_MASK(ANGLE_90 - 1) + ANGLE_45;
        D_801181DC->normal.vx = ((speed << 2) * rcos(angle)) >> 7;
        D_801181DC->normal.vy = ((speed << 2) * rsin(angle)) >> 7;
        D_801181DC->flags     = 1;
        D_801181DC->stage     = 0;
        D_801181DC->half_size = 0;
        D_801181DC->tick      = 0x40;
        D_801181DC->unk_26    = 7;
        D_801181DC->count     = 4;
        i++;
        D_801181DC++;
    } while (i < 16);
}

MATCH u8 func_80117410(void) {
    u8  scratch[32];
    u8  i;
    s32 result;

    Camera_SetMatrix(scratch);
    GFX_SET_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, 12);

    result     = 0;
    D_801181DC = MEM_PTR(AreaSprite, AREA_WORK);
    i          = 0;

    do {
        if (D_801181DC->flags != 0) {
            D_80118194[D_801181DC->stage]();
            func_801170D8(D_801181DC);
            result = 1;
        }
        D_801181DC++;
        i++;
    } while (i < 16);

    return result;
}

MATCH void func_80117514(void) {
    AreaSprite* work = D_801181DC;
    u8          count;

    count = work->count - 1;
    work->origin.x += work->normal.vx * 2;
    work->origin.y += work->normal.vy * 2;
    work->count = count;
    work->half_size += 0x80;
    if (!(count & BYTE_MASK)) {
        ((AreaSprite*)D_801181DC)->count = 0x40;
        ((AreaSprite*)D_801181DC)->stage++;
    }
}

MATCH void func_8011759C(void) {
    AreaSprite* work = D_801181DC;
    u8          count;

    work->origin.x += work->normal.vx;
    work->tick--;
    work->origin.y += work->normal.vy;
    count = --((AreaSprite*)D_801181DC)->count;
    if (!(count & BYTE_MASK)) {
        ((AreaSprite*)D_801181DC)->flags = 0;
    }
}

MATCH void func_80117610(void) {
    SYS_DISPATCH_TASK(D_8011819C, 1, g_Task);
    func_80117900();
}

MATCH void func_8011765C(void) {
    g_GameFlags |= GAME_FLAG_MENU_LOCK;
    func_801172D0();
    TASK(Actor)->timer = 180;
    TASK(Actor)->header.mode += 1;
}

MATCH void func_801176B8(void) {
    u8     timer;
    Actor* task;

    if (!(g_FrameCount & 3)) {
        D_801181DC = (AreaSprite*)Area_FindFreeWorkRow();
        if (D_801181DC != 0) {
            func_80117864(D_801181DC);
            D_801181DC->normal.vz = TO_COORD(32);
        }
    }
    timer              = TASK(Actor)->timer - 1;
    TASK(Actor)->timer = timer;
    if (timer == 0) {
        task        = TASK(Actor);
        task->timer = 0x40;
        task->vx    = TO_COORD(32);
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_80117768(void) {
    u8 timer;

    if (!(g_FrameCount & 3)) {
        D_801181DC = (AreaSprite*)Area_FindFreeWorkRow();
        if (D_801181DC != 0) {
            func_80117864(D_801181DC);
            TASK(Actor)->vx -= TO_COORD(1);
            D_801181DC->normal.vz = TASK(Actor)->vx;
        }
    }
    timer              = TASK(Actor)->timer - 1;
    TASK(Actor)->timer = timer;
    if (timer == 0) {
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_80117818(void) {
    if (func_80117900() == 0) {
        func_80196070();
        D_80146258 &= ~0x40;
    }
}

MATCH void func_80117864(void* arg0) {
    struct {
        u8  unk_00;
        u8  unk_01;
        u8  unk_02;
        u8  unk_03;
        s32 unk_04;
        s32 unk_08;
        s32 unk_0C;
        u8  pad_10[0xC];
        s32 unk_1C;
        u8  pad_20[4];
        u16 unk_24;
        u8  unk_26;
    }* p = arg0;

    Actor* a = TASK(Actor);
    s32    v;

    p->unk_04 = a->pos.x.fixed;
    p->unk_08 = a->pos.y.fixed;
    v         = a->pos.z.fixed;
    p->unk_00 = 1;
    p->unk_24 = 0x80;
    p->unk_03 = 0xC0;
    p->unk_26 = 2;
    p->unk_1C = 0;
    p->unk_01 = 0;
    p->unk_02 = 0x20;
    p->unk_0C = v;
}

#include "overlays/area/shared/Area_FindFreeWorkRow.h"

MATCH u8 func_80117900(void) {
    u8          scratch[32];
    u8          i;
    u8          count;
    s32         result;
    AreaSprite* work;

    Camera_SetMatrix(scratch);
    GFX_SET_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, 12);

    result     = 0;
    D_801181DC = MEM_PTR(AreaSprite, AREA_WORK);
    i          = 0;

    do {
        work = D_801181DC;
        if (work->flags != 0) {
            work->origin.z += work->normal.vz;
            work->tick -= 6;
            work->half_size += 8;
            count = --D_801181DC->count;
            if (!(count & BYTE_MASK)) {
                D_801181DC->flags = 0;
            }
            func_801170D8(D_801181DC);
            result = 1;
        }
        D_801181DC++;
        i++;
    } while (i < 16);

    return result;
}

MATCH void func_80117A30(void) {
    SYS_DISPATCH_BYTE(D_801181AC, TASK(Actor)->header.step);
}

MATCH void func_80117A74(void) {
    if (SYS_TestFlag(D_80144ED0, 62) != 0) {
        func_80117B60(0x40);
        func_80196070();
    }
    TASK(Actor)->header.step++;
}

MATCH void func_80117ACC(void) {
    if (SYS_TestFlag(D_80144ED0, 62) != 0) {
        TASK(Actor)->timer++;
        func_80117B60(0x80 - (TASK(Actor)->timer >> 1));
        if (TASK(Actor)->timer >= 128) {
            func_80196070();
        }
    }
}

MATCH void func_80117B60(s32 scale) {
    u32  color;
    s32  red;
    s32  green;
    s32  blue;
    u16* dst;
    s32  i;

    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 0x740u);
    do {
        color = dst[-0x2000];
        red   = ((s32)(color & 0x1F) * scale) / 0x80;
        green = (color & 0xFFFF) >> 5 & 0x1F;
        blue  = ((s32)((color & 0xFFFF) >> 10 & 0x1F) * scale) / 0x80;
        *dst  = (u16)((color & PSX_COLOR_STP_BIT) | (blue << 10) | (green << 5) | red);
        dst++;
        i++;
    } while (i < 0x10);
    g_GfxPalettePending = 1;
}

MATCH void func_80117BF4(void) {
    SYS_DISPATCH_BYTE(D_801181B4, TASK(Actor)->header.step);
}

MATCH void func_80117C38(void) {
    Scene_AdvanceActorStep();
}

MATCH void func_80117C58(void) {
    u32 slot;

    if (SYS_TestFlag(D_80144ED0, D_801181D0[COORD_INT(TASK(Actor)->pos.x)]) != 0) {
        SND_SEPlay(0x20A);
        slot = Actor_FindFreeSpawned() & BYTE_MASK;
        if (slot != GAME_NONE) {
            g_SpawnedActors[slot].header.flags = ACTOR_FLAG_IN_USE;
            g_SpawnedActors[slot].type         = 0x6E;
            g_SpawnedActors[slot].pos.x.fixed  = D_801181C0[COORD_INT(TASK(Actor)->pos.x)].x;
            g_SpawnedActors[slot].pos.y.fixed  = D_801181C0[COORD_INT(TASK(Actor)->pos.x)].y;
            g_SpawnedActors[slot].pos.z.fixed  = TO_COORD(1920);
        }
        slot = Actor_FindFreeSpawned() & BYTE_MASK;
        if (slot != GAME_NONE) {
            g_SpawnedActors[slot].header.flags = ACTOR_FLAG_IN_USE;
            g_SpawnedActors[slot].type         = 0x6D;
            g_SpawnedActors[slot].unk_06       = COORD_INT(TASK(Actor)->pos.x);
        }
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.step += 1;
    }
    func_80117E78(0x80, 0);
}

MATCH void func_80117DF0(void) {
    if (!(g_FrameCount & 0x1)) {
        TASK(Actor)->timer += 1;
    }
    if (TASK(Actor)->timer >= 128U) {
        Actor_Clear();
    }
    func_80117E78(128 - TASK(Actor)->timer, 0);
}

#ifdef NON_MATCHING
NON_MATCHING void func_80117E78(s32 brightness, s32 unused) {
    POLY_FT4* primitive;
    SVECTOR*  corner;
    s32       row;
    s32       col;
    s32       half;
    s32       sum;
    long      depth;
    long      flag;
    /* FAKE: retail frame is 0x50; no statement explains the last 8 bytes. */
    FAKE_STACK_PADS(u8, 8);

    corner = g_ScratchPadVectors;
    for (row = D_801181D4[COORD_INT(TASK(Actor)->pos.x)][1]; row < D_801181D4[COORD_INT(TASK(Actor)->pos.x)][3]; row++) {
        for (col = D_801181D4[COORD_INT(TASK(Actor)->pos.x)][0]; col < D_801181D4[COORD_INT(TASK(Actor)->pos.x)][2]; col++) {
            sum = row + col;
            if (sum & 1) {
                setVector(corner, ((col - 0x80) << 7) + 0x40, ((row - 0x80) << 7) + 0x40, -0x340);
                RotTransPers(corner, (long*)D_1F800034_U16, &depth, &flag);
                half = 3 - ((g_FrameCount / 3 + sum) & 7);
                if (half < 0) {
                    half = -half;
                }
                half += 24;
                primitive = (POLY_FT4*)g_GfxPrimCursor;
                SetPolyFT4(primitive);
                SetShadeTex(primitive, 0);
                setXY4(primitive, D_1F800034_U16[0] - half, D_1F800034_U16[1] - half, D_1F800034_U16[0] + half, D_1F800034_U16[1] - half, D_1F800034_U16[0] - half, D_1F800034_U16[1] + half,
                       D_1F800034_U16[0] + half, D_1F800034_U16[1] + half);
                SetSemiTrans(primitive, 1);
                setUV4(primitive, 224, 48, 255, 48, 224, 79, 255, 79);
                primitive->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256);
                primitive->clut  = getClut(80, STAGE_PALETTE_Y + 3);
                setRGB0(primitive, brightness / 2, brightness, brightness / 2);
                Area_CellAddPrim(col << 16, row << 16, 1, sizeof(POLY_FT4));
            }
        }
    }
}
#else
INCLUDE_ASM(func_80117E78);
#endif
