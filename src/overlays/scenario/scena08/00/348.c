#define FAKE_DECL_AREA_SCROLL_TARGET_VOLATILE
#define FAKE_DECL_AREA_SCROLL_TARGET_Y_VOLATILE
#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801F6F8C(void) {
    Actor* work;

    func_801F7DE8();
    work     = TASK(Actor);
    work->vx = 0;
    work->header.mode += 1;
}

MATCH void func_801F6FC4(void) {
    if ((g_FrameCount & 0x3) == 0) {
        func_801F802C();
    }
    func_801F7E14();
    TASK(Actor)->vx = (TASK(Actor)->vx + 0x80) & 0xFFF;
    if (--TASK(Actor)->timer == 0) {
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_801F7048(void) {
    if (func_801F7E14() & BYTE_MASK) {
        Actor_Clear();
    }
}

MATCH void func_801F707C(void) {
    SYS_DISPATCH_TASK(D_801FE8A0, 1, g_Task);
}

MATCH void func_801F70C0(void) {
    u8 i;

    SCENA08_SPARKLE_START(i, EMI_SE_ID(SND_BANK_AREA, 0x08));
}

MATCH void func_801F7164(void) {
    u16 count;
    u16 timer;

    SCENA08_SPARKLE_STEP(count, timer, 0x96);
}

MATCH void func_801F7200(void) {
    func_801F8534();
    TASK(Actor)->script_pc += RANDOM_MASK(BYTE_MASK);
    if (g_ScriptVars[0] == 0xB) {
        TASK(Actor)->frame_cells = 0x20;
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_801F7268(void) {
    u16 timer;

    func_801F8534();
    TASK(Actor)->script_pc += RANDOM_MASK(BYTE_MASK);
    if ((TASK(Actor)->frame_cells & 0x3) == 0) {
        TASK(Actor)->unk_2C -= 1;
    }
    if (TASK(Actor)->frame_cells == 2) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x0C));
    }
    timer                    = TASK(Actor)->frame_cells - 1;
    TASK(Actor)->frame_cells = timer;
    if (timer == 0) {
        TASK(Actor)->frame_cells = 0x40;
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_801F7320(void) {
    u16 count;
    u16 timer;

    func_801F85F0((s16)TASK(Actor)->screen_x, (s16)TASK(Actor)->screen_y, (s16)TASK(Actor)->unk_32);
    if ((TASK(Actor)->frame_cells & 3) == 0) {
        TASK(Actor)->unk_32--;
    }
    timer                    = TASK(Actor)->frame_cells - 1;
    TASK(Actor)->frame_cells = timer;
    if (timer == 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 9));
        TASK(Actor)->frame_cells = 20;
        TASK(Actor)->header.mode++;
    }
}

MATCH void func_801F73D4(void) {
    Actor* work;

    SCENA08_SCREEN_EFFECT_STEP(work, 0x10);
}

MATCH void func_801F743C(void) {
    u8 i;

    SCENA08_SPARKLE_START(i, EMI_SE_ID(SND_BANK_AREA, 0x02));
}

MATCH void func_801F74E0(void) {
    u16 count;
    u16 timer;

    SCENA08_SPARKLE_STEP(count, timer, 0x2D);
}

MATCH void func_801F757C(void) {
    func_801F8534();
    TASK(Actor)->script_pc += RANDOM_MASK(BYTE_MASK);
    if (g_ScriptVars[0] == 0xB) {
        TASK(Actor)->frame_cells = 0x20;
        TASK(Actor)->header.mode += 1;
    }
}

/* Draws the sprite at its projected position, advances the animation, and ends
 * the effect when its frame timer runs out. */
MATCH void func_801F75E4(void) {
    u16 count;
    u16 timer;

    func_801F85F0((s16)TASK(Actor)->screen_x, (s16)TASK(Actor)->screen_y, (s16)TASK(Actor)->unk_32);
    TASK(Actor)->script_pc += RANDOM_MASK(BYTE_MASK);
    if ((TASK(Actor)->frame_cells & 0x3) == 0) {
        TASK(Actor)->unk_2C -= 1;
    }
    count                    = TASK(Actor)->unk_32 - 1;
    timer                    = TASK(Actor)->frame_cells - 1;
    TASK(Actor)->unk_32      = count;
    TASK(Actor)->frame_cells = timer;
    if (timer == 0) {
        func_80196070();
    }
}

MATCH void func_801F7688(void) {
    s32     pos[3];
    DVECTOR screen;
    MATRIX  camera;
    Actor*  work;

    Camera_SetMatrix(&camera);
    pos[0] = TASK(Actor)->pos.x.fixed;
    pos[1] = TASK(Actor)->pos.y.fixed;
    pos[2] = TASK(Actor)->pos.z.fixed;
    Camera_ProjectPoint(pos, &screen);
    work           = TASK(Actor);
    work->screen_x = screen.vx;
    work->screen_y = screen.vy;
    work->unk_32   = 0x140;
    work->header.mode += 1;
    work->frame_cells = 0x14;
    func_801F8108((s16)TASK(Actor)->screen_x, (s16)TASK(Actor)->screen_y);
    func_801F85F0((s16)TASK(Actor)->screen_x, (s16)TASK(Actor)->screen_y, (s16)TASK(Actor)->unk_32);
}

MATCH void func_801F774C(void) {
    Actor* work;

    SCENA08_SCREEN_EFFECT_STEP(work, -0x10);
}

/* Draw a red-tinted billboard sprite of the given half size at the sprite's world position. */
MATCH void func_801F77B4(Scena08Billboard* sprite) {
    POLY_FT4* prim;
    DVECTOR   screen;
    DVECTOR   scale;
    VECTOR    pos;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    screen.vx = sprite->size >> 6;
    pos       = sprite->pos;
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
    setRGB0(prim, sprite->shade, 0, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
}

MATCH void func_801F7928(void) {
    SYS_DISPATCH_TASK(D_801FE8D0, 1, g_Task);
}

MATCH void func_801F796C(void) {
    SYS_DISPATCH_TASK(D_801FE8D8, 2, g_Task);
}

MATCH void func_801F79B0(void) {
    Actor* work;

    func_801F8AE8();
    work              = TASK(Actor);
    work->frame_cells = 0x40;
    work->header.step = work->header.step + 1;
}

MATCH void func_801F79EC(void) {
    FallingSpark* spark;

    if (TASK(Actor)->frame_cells == 4) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x01));
    }
    if ((TASK(Actor)->frame_cells & 0x7) == 0) {
        spark = func_801F8B14();
        if (spark != NULL) {
            Scene_InitSpark(spark);
        }
    }
    func_801F8BF8();
    if (--TASK(Actor)->frame_cells == 0) {
        TASK(Actor)->header.step += 1;
    }
}

MATCH void func_801F7A9C(void) {
    if (!(func_801F8BF8() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F7AD0(void) {
    SYS_DISPATCH_TASK(D_801FE8E4, 2, g_Task);
    Trail_Update(SCENA08_TRAIL);
    Trail_Draw(SCENA08_TRAIL);
}

MATCH void func_801F7B2C(void) {
    D_800E4C1E         = 0xC0;
    TASK(Actor)->pos.x = 7012352;
    TASK(Actor)->pos.y = 4587520;
    TASK(Actor)->pos.z = Area_HeightSample(TASK(Actor)->pos.x.fixed, 4587520) << 16;
    TASK(Actor)->timer = 32;
    TASK(Actor)->header.step += 1;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x02));
}

MATCH void func_801F7BA8(void) {
    Actor* work;
    u8     timer;

    work  = TASK(Actor);
    timer = work->timer - 1;
    work->pos.y.fixed += TO_COORD(1);
    work->timer = timer;
    if (timer == 0) {
        TASK(Actor)->timer       = 16;
        TASK(Actor)->header.step = TASK(Actor)->header.step + 1;
    }
}

MATCH void func_801F7C08(void) {
    if (--TASK(Actor)->timer == 0) {
        TASK(Actor)->pos.x = 6553600;
        TASK(Actor)->pos.y = 7733248;
        TASK(Actor)->pos.z = Area_HeightSample(TASK(Actor)->pos.x.fixed, 7733248) << 16;
        TASK(Actor)->timer = 32;
        TASK(Actor)->header.step += 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x02));
    }
}

MATCH void func_801F7C98(void) {
    Actor* work;
    u8     timer;

    work  = TASK(Actor);
    timer = work->timer - 1;
    work->pos.y.fixed -= TO_COORD(1);
    work->timer = timer;
    if (timer == 0) {
        TASK(Actor)->timer       = 128;
        TASK(Actor)->header.step = TASK(Actor)->header.step + 1;
    }
}

MATCH void func_801F7CF8(void) {
    u8 timer;

    timer              = TASK(Actor)->timer - 1;
    TASK(Actor)->timer = timer;
    if (timer == 0) {
        TASK(Actor)->timer       = 8;
        TASK(Actor)->header.step = TASK(Actor)->header.step + 1;
    }
}

MATCH void func_801F7D54(void) {
    u8 timer;

    D_800E4C1E -= 0x18;
    timer              = TASK(Actor)->timer - 1;
    TASK(Actor)->timer = timer;
    if (timer == 0) {
        Actor_Clear();
    }
}

MATCH u8* func_801F7DAC(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK);
    for (i = 0; i < 64; i++) {
        if (p[SCRATCH_ROW_OFFSET] == 0) {
            return p;
        }
        p += SCRATCH_ROW_STRIDE;
    }
    return NULL;
}

MATCH void func_801F7DE8(void) {
    s32 index;
    s8* cell;

    cell  = (s8*)AREA_WORK;
    index = 0;
    do {
        *cell = 0;
        index += 1;
        cell += 0x28;
    } while ((index & BYTE_MASK) < 0x40U);
}

/* steps the fade phase of each active billboard, draws it and moves it; returns 1 when none is active */
MATCH s32 func_801F7E14(void) {
    Scena08Billboard* billboard;
    VECTOR            pos;
    MATRIX            camera;
    s32               drawn;
    u8                i;

    GFX_ADD_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x2C0, 0x100) & 0xFFFF);
    Camera_SetMatrix(&camera);
    drawn     = 1;
    billboard = MEM_PTR(Scena08Billboard, AREA_WORK);
    for (i = 0; i < 0x40; billboard++, i++) {
        if (billboard->unk_00[0] != 0) {
            drawn = 0;
            switch (billboard->unk_00[2]) {
                case 0:
                    billboard->unk_00[1] = 8;
                    billboard->shade     = 0;
                    billboard->size      = 0;
                    billboard->unk_00[2]++;
                    break;
                case 1:
                    billboard->shade += 8;
                    if (billboard->unk_00[1] == 0) {
                        billboard->unk_00[1] = 0x10;
                        billboard->unk_00[2]++;
                    }
                    break;
                case 2:
                    if (billboard->unk_00[1] == 0) {
                        billboard->unk_00[1] = 8;
                        billboard->unk_00[2]++;
                    }
                    break;
                case 3:
                    billboard->shade -= 8;
                    if (billboard->unk_00[1] == 0) {
                        billboard->unk_00[0] = 0;
                    }
                    break;
            }
            pos = billboard->pos;
            pos.vz <<= 8;
            func_801F77B4(billboard);
            billboard->pos.vx += ((VECTOR*)billboard->unk_14)->vx;
            billboard->pos.vy += ((VECTOR*)billboard->unk_14)->vy;
            billboard->pos.vz += ((VECTOR*)billboard->unk_14)->vz;
            ((VECTOR*)billboard->unk_14)->vz += 0x200;
            billboard->size += 0x200;
            billboard->unk_00[1]--;
        }
    }
    return drawn;
}

MATCH void func_801F802C(void) {
    AreaSprite* work;
    u32         angle;

    work = (AreaSprite*)func_801F7DAC();
    if (work != NULL) {
        work->flags    = 1;
        work->count    = 0;
        work->origin.x = TASK(Actor)->pos.x.fixed;
        work->origin.y = TASK(Actor)->pos.y.fixed;
        work->origin.z = TASK(Actor)->pos.z.fixed >> 8;
        angle          = (u32)rsin(TASK(Actor)->vx) >> 4;
        if (TASK(Actor)->unk_06 == 7) {
            angle = (u16)angle;
            angle += ANGLE_180;
        } else {
            angle = (u16)angle;
            angle += ANGLE_90;
        }
        setVector(&work->normal, rcos(angle) * 3, rsin(angle) * 3, 0);
    }
}

MATCH void func_801F8108(s32 x, s32 y) {
    RECT rect;
    s32  width;
    s32  height;
    s32  frame_y;

    width   = 64;
    height  = 128;
    rect.x  = x - 64;
    frame_y = g_GfxBufferIndex * 240 - 64;
    rect.y  = y + frame_y;
    rect.w  = width;
    rect.h  = height;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 832, 256);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(DR_MOVE));

    rect.x  = x;
    frame_y = g_GfxBufferIndex * 240 - 64;
    rect.y  = y + frame_y;
    rect.w  = width;
    rect.h  = height;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 832, 384);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(DR_MOVE));
}

MATCH void func_801F81F4(u16 value) {
    s32 count;
    s32 index;

    count = 64;
    do {
        index = count & BYTE_MASK;
        count -= 1;
        D_801FE9EC[index] = D_801FE9EC[index - 1];
    } while (count & BYTE_MASK);
    D_801FE9EC[0] = value;
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F823C(s16 x, s16 y, s16 height, s16 width) {
    POLY_GT4* prim;
    s16       row;
    s32       half;
    s32       skew;
    s16       top;
    u8        i;
    u8        h;

    row = height - 1;
    for (i = 0; i < height * 2; i++) {
        h    = height;
        half = SquareRoot0(height * height - row * row);
        skew = (width * rsin(D_801FE9EC[i])) >> 12;
        prim = (POLY_GT4*)g_GfxPrimCursor;
        row -= 1;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 0);
        top      = i + (y - height);
        prim->x2 = prim->x0 = x - half + skew;
        prim->y1 = prim->y0 = top;
        prim->x3 = prim->x1 = x - half + skew + half;
        prim->y3 = prim->y2 = top + 1;
        prim->u2 = prim->u0 = 0x40 - half;
        prim->u3 = prim->u1 = 0x40;
        prim->v1 = prim->v0 = i - (h - 0x40);
        prim->v3 = prim->v2 = i + 0x40 - h + 1;
        prim->tpage         = GetTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 0x340, 0x100);
        prim->g0            = 0x40;
        prim->r0            = 0x40;
        prim->b0            = 0x80;
        prim->b1            = 0x60;
        prim->g1            = 0x60;
        prim->r1            = 0x60;
        prim->g2            = 0x40;
        prim->r2            = 0x40;
        prim->b2            = 0x80;
        prim->b3            = 0x60;
        prim->g3            = 0x60;
        prim->r3            = 0x60;
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_GT4));

        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 0);
        prim->y1 = prim->y0 = top;
        prim->y3 = prim->y2 = top + 1;
        prim->u2 = prim->u0 = 0;
        prim->x2 = prim->x0 = x + skew;
        prim->x3 = prim->x1 = x + skew + half;
        prim->v1 = prim->v0 = i + 0x40 - h - 0x80;
        prim->u3 = prim->u1 = half;
        prim->v3 = prim->v2 = i + 0x40 - h - 0x7F;
        prim->tpage         = GetTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 0x340, 0x100);
        prim->b0            = 0x60;
        prim->g0            = 0x60;
        prim->r0            = 0x60;
        prim->r1            = 0x80;
        prim->b1            = 0x40;
        prim->g1            = 0x40;
        prim->b2            = 0x60;
        prim->g2            = 0x60;
        prim->r2            = 0x60;
        prim->r3            = 0x80;
        prim->b3            = 0x40;
        prim->g3            = 0x40;
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_GT4));
    }
}
#else
INCLUDE_ASM(func_801F823C);
#endif

MATCH void func_801F8534(void) {
    s32     point[3];
    DVECTOR sxy;
    u8      camera[0x20];
    u16     screen_y;

    Camera_SetMatrix(camera);
    point[0] = TASK(Actor)->pos.x.fixed;
    point[1] = TASK(Actor)->pos.y.fixed;
    point[2] = TASK(Actor)->pos.z.fixed;
    Camera_ProjectPoint(point, &sxy);
    TASK(Actor)->screen_x = sxy.vx;
    screen_y              = sxy.vy;
    TASK(Actor)->screen_y = screen_y;
    func_801F8108((s16)TASK(Actor)->screen_x, (s16)screen_y);
    func_801F81F4(TASK(Actor)->script_pc);
    func_801F823C((s16)TASK(Actor)->screen_x, (s16)TASK(Actor)->screen_y, (s16)TASK(Actor)->unk_32, (s16)TASK(Actor)->unk_2C);
}

/* Draw a 16-slice disc of blended quads around (x, y); the colours keep retail's store order, which setRGB0..3 change. */
MATCH void func_801F85F0(s16 x, s16 y, s16 radius) {
    POLY_GT4* prim;
    u16       angle;
    s32       a;
    s32       b;
    u8        count;

    count = 0;
    angle = 0xFC00;
    do {
        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 0);
        a        = angle;
        prim->x0 = x - ((radius * rcos(a)) >> 12);
        prim->x1 = x;
        b        = (u16)(angle + 128);
        prim->y0 = prim->y1 = y + ((radius * rsin(a)) >> 12);
        prim->x2            = x - ((radius * rcos(b)) >> 12);
        prim->x3            = x;
        prim->y2 = prim->y3 = y + ((radius * rsin(b)) >> 12);
        prim->u0            = 63 - ((rcos(a) << 5) >> 12);
        prim->u1            = 63;
        prim->v0 = prim->v1 = 64 + ((rsin(a) << 5) >> 12);
        prim->u2            = 63 - ((rcos(b) << 5) >> 12);
        prim->u3            = 63;
        prim->v2 = prim->v3 = 64 + ((rsin(b) << 5) >> 12);
        prim->b0            = 0x80;
        prim->g0            = 0x40;
        prim->r0            = 0x40;
        prim->b1            = 0x60;
        prim->g1            = 0x60;
        prim->r1            = 0x60;
        prim->g2            = 0x40;
        prim->r2            = 0x40;
        prim->b2            = 0x80;
        prim->b3            = 0x60;
        prim->g3            = 0x60;
        prim->r3            = 0x60;
        setTPage(prim, TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 0x340, 0x100);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_GT4));

        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 0);
        prim->x0 = x;
        prim->x1 = x + ((radius * rcos(a)) >> 12);
        prim->y0 = prim->y1 = y + ((radius * rsin(a)) >> 12);
        prim->x2            = x;
        prim->x3            = x + ((radius * rcos(b)) >> 12);
        prim->y2 = prim->y3 = y + ((radius * rsin(b)) >> 12);
        count += 1;
        angle += 128;
        prim->u0 = 0;
        prim->u1 = (rcos(a) << 5) >> 12;
        prim->v0 = prim->v1 = ((rsin(a) << 5) >> 12) - 64;
        prim->u2            = 0;
        prim->u3            = (rcos(b) << 5) >> 12;
        prim->v2 = prim->v3 = ((rsin(b) << 5) >> 12) - 64;
        prim->b0            = 0x60;
        prim->g0            = 0x60;
        prim->r0            = 0x60;
        prim->b1            = 0x40;
        prim->g1            = 0x40;
        prim->r1            = 0x80;
        prim->b2            = 0x60;
        prim->g2            = 0x60;
        prim->r2            = 0x60;
        prim->r3            = 0x80;
        prim->b3            = 0x40;
        prim->g3            = 0x40;
        setTPage(prim, TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 0x340, 0x100);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_GT4));
    } while (count < 16);
}

#include "shared/GFX_DrawProjectedDisc.h"

MATCH void func_801F8964(FallingSpark* spark) {
    GFX_DRAW_PROJECTED_DISC(&spark->pos.vx, spark->header.shade, 0x20, 1);
}

MATCH void func_801F8AE8(void) {
    s32           index;
    FallingSpark* spark;

    spark = (FallingSpark*)AREA_WORK;
    index = 0;
    do {
        spark->header.active = 0;
        index += 1;
        spark += 1;
    } while ((index & BYTE_MASK) < SCENA08_SPARK_COUNT);
}

MATCH FallingSpark* func_801F8B14(void) {
    FallingSpark* spark;
    u8            i;

    spark = (FallingSpark*)AREA_WORK;
    for (i = 0; i < SCENA08_SPARK_COUNT; i++) {
        if (spark->header.active == 0) {
            return spark;
        }
        spark += 1;
    }
    return NULL;
}

#include "overlays/scenario/shared/Scene_InitSpark.h"

MATCH u8 func_801F8BF8(void) {
    u8            i;
    s32           live;
    FallingSpark* spark;
    u8            buffer[0x20];

    live = 0;
    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    Camera_SetMatrix(buffer);
    spark = (FallingSpark*)AREA_WORK;
    for (i = 0; i < SCENA08_SPARK_COUNT; i += 1, spark += 1) {
        if (spark->header.active != 0) {
            D_801FE8FC[spark->header.type](spark);
            live = 1;
            func_801F8964(spark);
        }
    }
    return live;
}

MATCH void func_801F8CDC(FallingSpark* spark) {
    u8 life;

    life = spark->header.life - 1;
    spark->header.shade += 6;
    spark->header.life = life;
    if (life == 0) {
        spark->header.life = spark->life_reload;
        spark->header.type += 1;
    }
}

#include "overlays/scenario/shared/Actor_Wait.h"

MATCH void func_801F8D4C(FallingSpark* spark) {
    u8  life;
    s32 speed;

    life               = spark->header.life - 1;
    speed              = spark->speed + TO_COORD(4);
    spark->header.life = life;
    spark->speed       = speed;
    spark->pos.vz += speed;
    spark->header.shade += 6;
    if (life == 0) {
        spark->header.active = 0;
    }
}

#include "shared/Trail_Update.h"

#include "shared/Trail_Draw.h"

#include "shared/MATH_AverageAngle.h"

#include "shared/GFX_DrawFan.h"

MATCH void func_801F95D4(void) {
    SYS_DISPATCH_TASK(D_801FE908, 1, g_Task);
}

MATCH void func_801F9618(void) {
    func_801F9688();
    /* kept: the LOHU halfword compare matches retail; the plain u16 lvalue adds four bytes. */
    if (LOHU(g_GameAreaId) != AREA_ID_DAUNA_MINE_WORKER) {
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_801F9668(void) {
    Actor_Clear();
}

/* Draw the 16 semi-transparent segments of a screen-sized ellipse ring, dark at the inner edge and bright at the outer. */
MATCH void func_801F9688(void) {
    DVECTOR  inner;
    DVECTOR  outer;
    POLY_G4* prim;
    s32      angle;
    u8       i;

    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 960, 256) & HALF_MASK);
    inner.vx = 240;
    inner.vy = 120;
    outer.vx = 400;
    outer.vy = 120;
    angle    = 0;
    i        = 0;
    do {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY2(prim, inner.vx, inner.vy, outer.vx, outer.vy);
        angle += 0x100;
        inner.vx = 160 + ((rcos((u16)angle) * 80) >> 12);
        inner.vy = 120 + ((rsin((u16)angle) * 60) >> 12);
        outer.vx = 160 + ((rcos((u16)angle) * 240) >> 12);
        outer.vy = 120 + ((rsin((u16)angle) * 180) >> 12);
        prim->x2 = inner.vx;
        prim->y2 = inner.vy;
        prim->x3 = outer.vx;
        prim->y3 = outer.vy;
        setRGB0(prim, 0, 0, 0);
        setRGB1(prim, 255, 255, 255);
        setRGB2(prim, 0, 0, 0);
        setRGB3(prim, 255, 255, 255);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
        i++;
    } while (i < 16);
}

MATCH void func_801F986C(void) {
    SYS_DISPATCH_TASK(D_801FE910, 1, g_Task);
}

/* Stores 60 in timer and increments mode of the current task. */
MATCH void func_801F98B0(void) {
    TASK(Actor)->timer = 60;
    TASK(Actor)->header.mode++;
}

MATCH void func_801F98E0(void) {
    if (--TASK(Actor)->timer == 0) {
        TASK(Actor)->pos.x = 5308416;
        TASK(Actor)->pos.y = 4325376;
        TASK(Actor)->pos.z = 0x2C00000;
        TASK(Actor)->vz    = 8388608;
        TASK(Actor)->header.mode += 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x02));
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x03));
    }
}

MATCH void func_801F995C(void) {
    TASK(Actor)->pos.x.fixed -= 0x10000;
    TASK(Actor)->pos.z.fixed += TASK(Actor)->vz;
    TASK(Actor)->vz -= 2097152;
    func_801F9F8C(&TASK(Actor)->pos, 0x20, 8, 0);
    if (TASK(Actor)->pos.x.fixed == 0x490000) {
        setVector(TASK(Actor), 14563, 65536, 12116878);
        TASK(Actor)->header.mode += 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
    }
}

MATCH void func_801F9A10(void) {
    TASK(Actor)->pos.x.fixed += TASK(Actor)->vx;
    TASK(Actor)->pos.y.fixed += TASK(Actor)->vy;
    TASK(Actor)->pos.z.fixed += TASK(Actor)->vz;
    TASK(Actor)->vz -= 2097152;
    func_801F9F8C(&TASK(Actor)->pos, 0x20, 8, 0);
    if (TASK(Actor)->pos.y.fixed == 0x4B0000) {
        TASK(Actor)->timer = 60;
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_801F9AC0(void) {
    if (--TASK(Actor)->timer == 0) {
        TASK(Actor)->pos.x = 4915200;
        TASK(Actor)->pos.y = 4915200;
        TASK(Actor)->pos.z = Area_HeightSample(TASK(Actor)->pos.x.fixed, 4915200) << 16;
        setVector(TASK(Actor), 0xFFFF4925, 0xFFFF0000, 4993220);
        TASK(Actor)->header.mode += 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x02));
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x03));
    }
}

MATCH void func_801F9B68(void) {
    TASK(Actor)->pos.x.fixed += TASK(Actor)->vx;
    TASK(Actor)->pos.y.fixed += TASK(Actor)->vy;
    TASK(Actor)->pos.z.fixed += TASK(Actor)->vz;
    TASK(Actor)->vz -= 1048576;
    func_801F9F8C(&TASK(Actor)->pos, 0x20, 8, 0);
    if (TASK(Actor)->pos.y.fixed == 0x360000) {
        func_80196070();
    }
}

MATCH void func_801F9C00(void) {
    Actor* work;

    work              = TASK(Actor);
    work->pos.x.fixed = TO_COORD(39);
    work->pos.y.fixed = TO_COORD(8);
    work->pos.z.fixed = TO_COORD(2048);
    work->vz          = 0;
    work->header.mode += 1;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 4));
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 5));
}

MATCH void func_801F9C58(void) {
    TASK(Actor)->pos.y.fixed += 0x10000;
    TASK(Actor)->pos.z.fixed += TASK(Actor)->vz;
    TASK(Actor)->vz -= 2097152;
    func_801F9F8C(&TASK(Actor)->pos, 0x20, 8, 0);
    if (TASK(Actor)->pos.x.fixed == 0xF0000) {
        func_80196070();
    }
}

MATCH void func_801F9CE0(void) {
    Actor* work;

    work              = TASK(Actor);
    work->pos.x.fixed = TO_COORD(25);
    work->pos.y.fixed = TO_COORD(15);
    work->pos.z.fixed = TO_COORD(1536);
    work->vz          = 0;
    work->header.mode += 1;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 10));
}

MATCH void func_801F9D30(void) {
    TASK(Actor)->pos.y.fixed += 0x10000;
    TASK(Actor)->pos.z.fixed += TASK(Actor)->vz;
    TASK(Actor)->vz -= 2097152;
    func_801F9F8C(&TASK(Actor)->pos, 0x20, 8, 4);
    if (TASK(Actor)->pos.y.fixed > 0x18FFFF) {
        func_80196070();
    }
}

MATCH void func_801F9DBC(void) {
    SYS_DISPATCH_TASK(D_801FE938, 1, g_Task);
}

MATCH void func_801F9E00(void) {
    Actor* work;
    u8     mode;

    work              = TASK(Actor);
    mode              = work->header.mode + 1;
    work->pos.x.fixed = TO_COORD(25) + COORD_HALF;
    work->pos.y.fixed = TO_COORD(25) + COORD_HALF;
    work->pos.z.fixed = TO_COORD(1024);
    setVector(work, work->pos.x.fixed + TO_COORD(4), work->pos.y.fixed, work->pos.z.fixed);
    work->header.mode = mode;
}

MATCH void func_801F9E50(void) {
    TASK(Actor)->pos.x.fixed -= TO_COORD(2);
    TASK(Actor)->vx -= TO_COORD(2);
    func_801FA19C(&TASK(Actor)->pos, &TASK(Actor)->vx);
    if (TASK(Actor)->pos.x.fixed == 0x98000) {
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_801F9EC4(void) {
    TASK(Actor)->vx -= TO_COORD(2);
    func_801FA19C(&TASK(Actor)->pos, &TASK(Actor)->vx);
    if (TASK(Actor)->vx == 622592) {
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_801F9F2C(void) {
    Scene_AdvanceActorMode();
}

MATCH void func_801F9F4C(void) {
    Scene_AdvanceActorMode();
}

MATCH void func_801F9F6C(void) {
    Actor_Clear();
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F9F8C(WorldPos* pos, s32 unused, s32 jitter, s32 layer) {
    LINE_F2* line;
    DVECTOR  screen;
    DVECTOR  size;
    DVECTOR  scale;
    MATRIX   camera;
    s32      angle;
    s16      i;
    s32      depth;
    s32      root;

    FAKE_STACK_PADS(u8, 0x20); /* FAKE: retail reserves unused stack bytes. */

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 0x3C0, 0x100) & 0xFFFF, 0);
    Area_CellAddPrim(pos->x.fixed, pos->y.fixed, (s8)layer, 12);
    Camera_SetMatrix(&camera);
    Camera_ProjectPoint(&pos->x.fixed, &screen);
    size.vx = size.vy = 0x50;
    Game_ProjectWorldPoint(pos, &size, &scale);
    angle = rand() & 0xFFF;
    depth = layer;
    for (i = -scale.vx; i <= scale.vx; i++) {
        root = SquareRoot0((scale.vx * scale.vx) - (i * i));
        line = (LINE_F2*)g_GfxPrimCursor;
        SetLineF2(line);
        SetSemiTrans(line, 1);
        line->x0 = jitter + (screen.vx + ((rsin((u16)angle) * 16) >> 12)) - root;
        line->x1 = root + (jitter + (screen.vx + ((rsin((u16)angle) * 16) >> 12)));
        line->y0 = line->y1 = screen.vy + i;
        setRGB0(line, 0, 0, 0);
        Area_CellAddPrim(pos->x.fixed, pos->y.fixed, (s8)depth, sizeof(LINE_F2));
        jitter = -jitter;
        angle += rand() & 0xFF;
    }
}
#else
INCLUDE_ASM(func_801F9F8C);
#endif

MATCH void func_801FA19C(WorldPos* pos, s32* vx) {
    LINE_G2* prim;
    DVECTOR  xy;
    MATRIX   camera;

    GFX_SET_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 960, 256));
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    prim = (LINE_G2*)g_GfxPrimCursor;
    SetLineG2(prim);
    SetSemiTrans(prim, 1);
    Camera_SetMatrix(&camera);
    Camera_ProjectPoint(&pos->x.fixed, &xy);
    setXY0(prim, xy.vx, xy.vy);
    Camera_ProjectPoint(vx, &xy);
    prim->x1 = xy.vx;
    prim->y1 = xy.vy;
    setRGB0(prim, 64, 64, 64);
    setRGB1(prim, 0, 0, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_G2));
}

MATCH void func_801FA294(void) {
    SYS_DISPATCH_BYTE(D_801FE964, D_80146872);
}

MATCH void func_801FA2D0(void) {
    D_80144EC8[0]    = 0;
    g_ScriptVarsWord = 0;
    D_80146872       = 1;
    func_801FA32C();
    func_801FE12C();
    SYS_SetFlag(&D_80144EC8[0x60], 67);
}

MATCH void func_801FA32C(void) {
    u8 i;

    for (i = 0; i < CHAR_INDEX_COUNT; i++) {
        g_Characters[i].party_flags |= PARTY_FLAG_JOINED;
    }
    Char_RebuildPartyStats();
    for (i = 1; i < CHAR_INDEX_COUNT; i++) {
        g_Characters[i].party_flags &= ~PARTY_FLAG_JOINED;
    }
}

/* starts the scene events of the area and cell the party enters */
MATCH void func_801FA3E4(void) {
    u8  i;
    u8  slot;
    u8* flags;

    if (LOHU(g_GameAreaId) == 0 && g_GameCellType == 0 && !SYS_TestFlag(g_SceneFlags, 10)) {
        SYS_SetFlag(g_SceneFlags, 10);
        Scene_RunScenario(3);
        Scene_SetupParty(5);
    }
    if (LOHU(g_GameAreaId) == 1) {
        if (g_GameCellType == 2 && !SYS_TestFlag(g_SceneFlags, 6)) {
            Game_SetScriptActive();
            Scene_SetupParty(3);
            Area_ScrollAdvance(Area_HeightSample(g_AreaScrollTargetX = TO_COORD_HALF(81), g_AreaScrollTargetY = TO_COORD_HALF(30)));
            Area_InitMapRenderer();
            g_Actors[0].header.mode  = 4;
            g_Actors[0].unk_77       = 13;
            g_Actors[1].unk_77       = 14;
            g_Actors[1].header.mode  = 4;
            g_ScenarioState.state_04 = 4;
            g_ScenarioState.step     = 10;
        }
    }
    if (LOHU(g_GameAreaId) == 2 && SYS_TestFlag(g_SceneFlags, 6) && !SYS_TestFlag(g_SceneFlags, 7)) {
        slot                        = Actor_FindFreeSpawned();
        g_ScratchPad.cells.bytes[0] = slot;
        g_AreaCameraAngle.vx        = -0x23C;
        if (slot != GAME_NONE) {
            g_SpawnedActors[slot].header.flags                          = 1;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x302;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = g_AreaCameraAngle.vz;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0xFF;
        }
    }
    if (LOHU(g_GameAreaId) == 3) {
        if (!SYS_TestFlag(g_SceneFlags, 14)) {
            Scene_RunScenario(3);
            flags = &g_Game.members[1].header.flags;
            *flags |= 0x40;
        }
    }
    if (LOHU(g_GameAreaId) == 12 && !SYS_TestFlag(g_SceneFlags, 12) && SYS_TestFlag(g_SceneFlags, 11)) {
        Game_SetScriptActive();
        g_AreaDrawFlags          = 0;
        g_ScenarioState.state_04 = 8;
        g_ScenarioState.step     = 0;
        D_801FEA70               = g_Game.members[0].facing;
        D_801FEA74               = g_Game.members[0].pos.x.fixed;
        D_801FEA78               = g_Game.members[0].pos.y.fixed;
    }
    if (LOHU(g_GameAreaId) == 15) {
        if (SYS_TestFlag(g_SceneFlags, 14) && !SYS_TestFlag(g_SceneFlags, 15)) {
            Game_SetScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 9;
            g_ScenarioState.step     = 0;
            Scene_RunScenario(4);
            Scene_SetupParty(10);
        }
    }
    if (LOHU(g_GameAreaId) == 18 && !SYS_TestFlag(g_SceneFlags, 23)) {
        i = 0;
        do {
            Area_CellSetCode(i + 26, 24, 16);
            i++;
        } while (i < 11);
    }
    if (LOHU(g_GameAreaId) == 21 && g_GameCellType == 0) {
        g_ScriptVars[3] = 0;
        if (SYS_TestFlag(g_SceneFlags, 15)) {
            if (!SYS_TestFlag(g_SceneFlags, 17)) {
                SND_BGMRequest(0x74);
                while (!EMI_IsReady()) {
                    SYS_ThreadWait(1);
                }
                Scene_SetupParty(0);
                Area_ScrollAdvance(Area_HeightSample(g_AreaScrollTargetX = TO_COORD_HALF(41), g_AreaScrollTargetY = TO_COORD(13)));
                Area_InitMapRenderer();
                SYS_SetFlag(g_SceneFlags, 17);
            }
            if (SYS_TestFlag(g_SceneFlags, 19) && !SYS_TestFlag(g_SceneFlags, 20)) {
                Game_SetScriptActive();
                Scene_SetupParty(2);
                Area_ScrollAdvance(Area_HeightSample(g_AreaScrollTargetX = TO_COORD_HALF(10), g_AreaScrollTargetY = TO_COORD(20)));
                Area_InitMapRenderer();
                /* retail bug: an extra flags argument shifts 20 out, so flag 20 is never set here */
                ((void (*)(void*, void*, u8))SYS_SetFlag)(g_SceneFlags, g_SceneFlags, 20);
                g_ScenarioState.state_04 = 10;
                g_ScenarioState.step     = 10;
            }
        }
    }
    if (LOHU(g_GameAreaId) == 32) {
        if (g_GameCellType == 5) {
            if (!SYS_TestFlag(g_SceneFlags, 0)) {
                Game_SetScriptActive();
                g_AreaDrawFlags = 0;
                Scene_SetupParty(0);
                g_ScenarioState.state_04 = 1;
                g_ScenarioState.step     = 0;
                g_ScenarioState.timer_06 = 150;
            }
        }
        if (g_GameCellType == 1) {
            if (!SYS_TestFlag(g_SceneFlags, 0)) {
                Scene_SetupParty(1);
                g_AreaDrawFlags = 0x1F;
            } else if (!SYS_TestFlag(g_SceneFlags, 1)) {
                Scene_RunScenario(1);
                Scene_SetupParty(2);
                g_AreaDrawFlags = 0;
            }
        }
        if (g_GameCellType == 0 && !SYS_TestFlag(g_SceneFlags, 2)) {
            Scene_RunScenario(2);
            Scene_SetupParty(3);
            SYS_SetFlag(g_SceneFlags, 2);
            g_GameFlags &= 0xFFDF;
        }
    }
    D_80146872 = 2;
}

MATCH void func_801FAB5C(void) {
    SYS_DISPATCH_BYTE(D_801FE970, g_ScenarioState.state_04);
}

MATCH void func_801FAB98(void) {
}
