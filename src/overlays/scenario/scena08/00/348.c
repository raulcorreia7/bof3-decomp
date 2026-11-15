#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801F6F8C(void) {
    Actor* work;

    func_801F7DE8();
    work     = g_Task;
    work->vx = 0;
    work->header.mode += 1;
}

MATCH void func_801F6FC4(void) {
    if ((g_FrameCount & 0x3) == 0) {
        func_801F802C();
    }
    func_801F7E14();
    g_Task->vx = (g_Task->vx + 0x80) & 0xFFF;
    if (--g_Task->timer == 0) {
        g_Task->header.mode += 1;
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

    SCENA08_SPARKLE_START(i, EMI_CUE_ID(SND_BANK_AREA, 0x08));
}

MATCH void func_801F7164(void) {
    u16 count;
    u16 timer;

    SCENA08_SPARKLE_STEP(count, timer, 0x96);
}

MATCH void func_801F7200(void) {
    func_801F8534();
    g_Task->script_pc += RANDOM_MASK(BYTE_MASK);
    if (g_ScriptVars[0] == 0xB) {
        g_Task->unk_5A = 0x20;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F7268(void) {
    u16 timer;

    func_801F8534();
    g_Task->script_pc += RANDOM_MASK(BYTE_MASK);
    if ((g_Task->unk_5A & 0x3) == 0) {
        g_Task->unk_2C -= 1;
    }
    if (g_Task->unk_5A == 2) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x0C));
    }
    timer          = g_Task->unk_5A - 1;
    g_Task->unk_5A = timer;
    if (timer == 0) {
        g_Task->unk_5A = 0x40;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F7320(void) {
    u16 count;
    u16 timer;

    func_801F85F0((s16)g_Task->screen_x, (s16)g_Task->screen_y, (s16)g_Task->unk_32);
    if ((g_Task->unk_5A & 3) == 0) {
        g_Task->unk_32--;
    }
    timer          = g_Task->unk_5A - 1;
    g_Task->unk_5A = timer;
    if (timer == 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 9));
        g_Task->unk_5A = 20;
        g_Task->header.mode++;
    }
}

MATCH void func_801F73D4(void) {
    Actor* work;

    SCENA08_SCREEN_EFFECT_STEP(work, 0x10);
}

MATCH void func_801F743C(void) {
    u8 i;

    SCENA08_SPARKLE_START(i, EMI_CUE_ID(SND_BANK_AREA, 0x02));
}

MATCH void func_801F74E0(void) {
    u16 count;
    u16 timer;

    SCENA08_SPARKLE_STEP(count, timer, 0x2D);
}

MATCH void func_801F757C(void) {
    func_801F8534();
    g_Task->script_pc += RANDOM_MASK(BYTE_MASK);
    if (g_ScriptVars[0] == 0xB) {
        g_Task->unk_5A = 0x20;
        g_Task->header.mode += 1;
    }
}

/* Draws the sprite at its projected position, advances the animation, and ends
 * the effect when its frame timer runs out. */
MATCH void func_801F75E4(void) {
    u16 count;
    u16 timer;

    func_801F85F0((s16)g_Task->screen_x, (s16)g_Task->screen_y, (s16)g_Task->unk_32);
    g_Task->script_pc += RANDOM_MASK(BYTE_MASK);
    if ((g_Task->unk_5A & 0x3) == 0) {
        g_Task->unk_2C -= 1;
    }
    count          = g_Task->unk_32 - 1;
    timer          = g_Task->unk_5A - 1;
    g_Task->unk_32 = count;
    g_Task->unk_5A = timer;
    if (timer == 0) {
        func_80196070();
    }
}

MATCH void func_801F7688(void) {
    s32     pos[3];
    DVECTOR screen;
    MATRIX  camera;
    Actor*  work;

    Area_SetCameraMatrix(&camera);
    pos[0] = g_Task->pos.x.fixed;
    pos[1] = g_Task->pos.y.fixed;
    pos[2] = g_Task->pos.z.fixed;
    Area_ProjectPoint(pos, &screen);
    work           = g_Task;
    work->screen_x = screen.vx;
    work->screen_y = screen.vy;
    work->unk_32   = 0x140;
    work->header.mode += 1;
    work->unk_5A = 0x14;
    func_801F8108((s16)g_Task->screen_x, (s16)g_Task->screen_y);
    func_801F85F0((s16)g_Task->screen_x, (s16)g_Task->screen_y, (s16)g_Task->unk_32);
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
    Area_ProjectPoint((s32*)&pos, &screen);
    prim->x0 = prim->x2 = screen.vx - scale.vx;
    prim->x1 = prim->x3 = screen.vx + scale.vx;
    prim->y0 = prim->y1 = screen.vy - scale.vx;
    prim->y2 = prim->y3 = screen.vy + scale.vx;
    setClut(prim, 160, STAGE_PALETTE_Y + 3);
    prim->tpage = GetTPage(0, 1, 704, 256);
    setUVWH(prim, 224, 48, 31, 31);
    setRGB0(prim, sprite->shade, 0, 0);
    GFX_AddPrim(1, sizeof(POLY_FT4));
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
    work              = g_Task;
    work->unk_5A      = 0x40;
    work->header.step = work->header.step + 1;
}

MATCH void func_801F79EC(void) {
    FallingSpark* spark;

    if (g_Task->unk_5A == 4) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x01));
    }
    if ((g_Task->unk_5A & 0x7) == 0) {
        spark = func_801F8B14();
        if (spark != NULL) {
            Scene_InitSpark(spark);
        }
    }
    func_801F8BF8();
    if (--g_Task->unk_5A == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801F7A9C(void) {
    if (!(func_801F8BF8() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F7AD0(void) {
    SYS_DISPATCH_TASK(D_801FE8E4, 2, g_Task);
    func_801F8D98(MEM_PTR(void, 0x800E48E0u));
    func_801F90C8(MEM_PTR(void, 0x800E48E0u));
}

MATCH void func_801F7B2C(void) {
    D_800E4C1E    = 0xC0;
    g_Task->pos.x = 7012352;
    g_Task->pos.y = 4587520;
    g_Task->pos.z = Area_SampleHeight(g_Task->pos.x.fixed, 4587520) << 16;
    g_Task->timer = 32;
    g_Task->header.step += 1;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x02));
}

MATCH void func_801F7BA8(void) {
    Actor* work;
    u8     timer;

    work  = g_Task;
    timer = work->timer - 1;
    work->pos.y.fixed += TO_COORD(1);
    work->timer = timer;
    if (timer == 0) {
        g_Task->timer       = 16;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F7C08(void) {
    if (--g_Task->timer == 0) {
        g_Task->pos.x = 6553600;
        g_Task->pos.y = 7733248;
        g_Task->pos.z = Area_SampleHeight(g_Task->pos.x.fixed, 7733248) << 16;
        g_Task->timer = 32;
        g_Task->header.step += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x02));
    }
}

MATCH void func_801F7C98(void) {
    Actor* work;
    u8     timer;

    work  = g_Task;
    timer = work->timer - 1;
    work->pos.y.fixed -= TO_COORD(1);
    work->timer = timer;
    if (timer == 0) {
        g_Task->timer       = 128;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F7CF8(void) {
    u8 timer;

    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->timer       = 8;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F7D54(void) {
    u8 timer;

    D_800E4C1E -= 0x18;
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
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

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F7E14(void) {
    u8*          slot;
    u8*          data;
    volatile s32 snapshot[4];
    MATRIX       camera;
    s32          drawn;
    s32          step;
    u8           i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 1, 0x2C0, 0x100) & 0xFFFF, 0);
    GFX_AddPrim(1, sizeof(DR_MODE));
    Area_SetCameraMatrix(&camera);
    drawn = 1;
    step  = 8;
    slot  = MEM_PTR(u8, AREA_WORK);
    data  = MEM_PTR(u8, AREA_WORK + 1);
    i     = 0;
    do {
        if (slot[0] != 0) {
            if (data[1] != 1) {
                drawn = 0;
            }
            if (data[1] == 1) {
                data[2] += step;
                if (data[0] == 0) {
                    data[0] = 0x10;
                    data[1]++;
                }
            } else if (data[1] < 2) {
                if (data[1] == 0) {
                    data[0]                       = step;
                    data[2]                       = 0;
                    *(volatile s32*)(data + 0x23) = 0;
                    data[1]++;
                }
            } else if (data[1] == 2) {
                if (data[0] == 0) {
                    data[0] = step;
                    data[1]++;
                }
            } else if (data[1] == 3) {
                data[2] -= step;
                if (data[0] == 0) {
                    slot[0] = 0;
                }
            }
            snapshot[0] = *(volatile s32*)(data + 0x03);
            snapshot[1] = *(volatile s32*)(data + 0x07);
            snapshot[2] = *(volatile s32*)(data + 0x0B);
            snapshot[3] = *(volatile s32*)(data + 0x0F);
            snapshot[2] <<= 8;
            func_801F77B4((Scena08Billboard*)slot);
            *(volatile s32*)(data + 0x03) += *(volatile s32*)(data + 0x13);
            *(volatile s32*)(data + 0x07) += *(volatile s32*)(data + 0x17);
            data[0]--;
            *(volatile s32*)(data + 0x0B) += *(volatile s32*)(data + 0x1B);
            *(volatile s32*)(data + 0x1B) += 0x200;
            *(volatile s32*)(data + 0x23) += 0x200;
        }
        data += 0x28;
        slot += 0x28;
        i++;
    } while (i < 0x40);
    return drawn;
}
#else
INCLUDE_ASM(func_801F7E14);
#endif

MATCH void func_801F802C(void) {
    AreaSprite* work;
    u32         angle;

    work = (AreaSprite*)func_801F7DAC();
    if (work != NULL) {
        work->flags    = 1;
        work->flags_02 = 0;
        work->origin.x = g_Task->pos.x.fixed;
        work->origin.y = g_Task->pos.y.fixed;
        work->origin.z = g_Task->pos.z.fixed >> 8;
        angle          = (u32)rsin(g_Task->vx) >> 4;
        if (g_Task->unk_06 == 7) {
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
    frame_y = g_FrameBufferIndex * 240 - 64;
    rect.y  = y + frame_y;
    rect.w  = width;
    rect.h  = height;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 832, 256);
    GFX_AddPrim(2, sizeof(DR_MOVE));

    rect.x  = x;
    frame_y = g_FrameBufferIndex * 240 - 64;
    rect.y  = y + frame_y;
    rect.w  = width;
    rect.h  = height;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 832, 384);
    GFX_AddPrim(2, sizeof(DR_MOVE));
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

INCLUDE_ASM(func_801F823C);

MATCH void func_801F8534(void) {
    s32     point[3];
    DVECTOR sxy;
    u8      camera[0x20];
    u16     screen_y;

    Area_SetCameraMatrix(camera);
    point[0] = g_Task->pos.x.fixed;
    point[1] = g_Task->pos.y.fixed;
    point[2] = g_Task->pos.z.fixed;
    Area_ProjectPoint(point, &sxy);
    g_Task->screen_x = sxy.vx;
    screen_y         = sxy.vy;
    g_Task->screen_y = screen_y;
    func_801F8108((s16)g_Task->screen_x, (s16)screen_y);
    func_801F81F4(g_Task->script_pc);
    func_801F823C((s16)g_Task->screen_x, (s16)g_Task->screen_y, (s16)g_Task->unk_32, (s16)g_Task->unk_2C);
}

INCLUDE_ASM(func_801F85F0);

#include "shared/GFX_DrawProjectedDisc.h"

MATCH void func_801F8964(FallingSpark* spark) {
    GFX_DRAW_PROJECTED_DISC(&spark->x, spark->fade, 0x20, 1);
}

MATCH void func_801F8AE8(void) {
    s32           index;
    FallingSpark* spark;

    spark = (FallingSpark*)AREA_WORK;
    index = 0;
    do {
        spark->active = 0;
        index += 1;
        spark += 1;
    } while ((index & BYTE_MASK) < SCENA08_SPARK_COUNT);
}

MATCH FallingSpark* func_801F8B14(void) {
    FallingSpark* spark;
    u8            i;

    spark = (FallingSpark*)AREA_WORK;
    for (i = 0; i < SCENA08_SPARK_COUNT; i++) {
        if (spark->active == 0) {
            return spark;
        }
        spark += 1;
    }
    return NULL;
}

#include "overlays/scenario/Scene_InitSpark.h"

MATCH u8 func_801F8BF8(void) {
    u8            i;
    s32           live;
    FallingSpark* spark;
    u8            buffer[0x20];

    live = 0;
    GFX_AddDitheredDrawMode(1, GetTPage(0, 1, 0x3C0, 0));
    Area_SetCameraMatrix(buffer);
    spark = (FallingSpark*)AREA_WORK;
    for (i = 0; i < SCENA08_SPARK_COUNT; i += 1, spark += 1) {
        if (spark->active != 0) {
            D_801FE8FC[spark->kind](spark);
            live = 1;
            func_801F8964(spark);
        }
    }
    return live;
}

MATCH void func_801F8CDC(FallingSpark* spark) {
    u8 life;

    life = spark->life - 1;
    spark->fade += 6;
    spark->life = life;
    if (life == 0) {
        spark->life = spark->life_reload;
        spark->kind += 1;
    }
}

#include "overlays/scenario/Actor_Wait.h"

MATCH void func_801F8D4C(FallingSpark* spark) {
    u8  life;
    s32 speed;

    life         = spark->life - 1;
    speed        = spark->speed + TO_COORD(4);
    spark->life  = life;
    spark->speed = speed;
    spark->z += speed;
    spark->fade += 6;
    if (life == 0) {
        spark->active = 0;
    }
}

INCLUDE_ASM(func_801F8D98);

INCLUDE_ASM(func_801F90C8);

#include "shared/MATH_AverageAngle.h"

#include "shared/GFX_DrawFan.h"

MATCH void func_801F95D4(void) {
    SYS_DISPATCH_TASK(D_801FE908, 1, g_Task);
}

MATCH void func_801F9618(void) {
    func_801F9688();
    /* kept: the LOHU halfword compare matches retail; the plain u16 lvalue adds four bytes. */
    if (LOHU(g_GameAreaId) != AREA_ID_DAUNA_MINE_WORKER) {
        g_Task->header.mode += 1;
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

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 2, 960, 256) & HALF_MASK, 0);
    GFX_AddPrim(1, sizeof(DR_MODE));
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
        prim->x0 = inner.vx;
        prim->y0 = inner.vy;
        prim->x1 = outer.vx;
        prim->y1 = outer.vy;
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
        GFX_AddPrim(1, sizeof(POLY_G4));
        i++;
    } while (i < 16);
}

MATCH void func_801F986C(void) {
    SYS_DISPATCH_TASK(D_801FE910, 1, g_Task);
}

/* Stores 60 in timer and increments mode of the current task. */
MATCH void func_801F98B0(void) {
    g_Task->timer = 60;
    g_Task->header.mode++;
}

MATCH void func_801F98E0(void) {
    if (--g_Task->timer == 0) {
        g_Task->pos.x = 5308416;
        g_Task->pos.y = 4325376;
        g_Task->pos.z = 0x2C00000;
        g_Task->vz    = 8388608;
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x02));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x03));
    }
}

MATCH void func_801F995C(void) {
    g_Task->pos.x.fixed -= 0x10000;
    g_Task->pos.z.fixed += g_Task->vz;
    g_Task->vz -= 2097152;
    func_801F9F8C(&g_Task->pos, 0x20, 8, 0);
    if (g_Task->pos.x.fixed == 0x490000) {
        setVector(g_Task, 14563, 65536, 12116878);
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
    }
}

MATCH void func_801F9A10(void) {
    g_Task->pos.x.fixed += g_Task->vx;
    g_Task->pos.y.fixed += g_Task->vy;
    g_Task->pos.z.fixed += g_Task->vz;
    g_Task->vz -= 2097152;
    func_801F9F8C(&g_Task->pos, 0x20, 8, 0);
    if (g_Task->pos.y.fixed == 0x4B0000) {
        g_Task->timer = 60;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F9AC0(void) {
    if (--g_Task->timer == 0) {
        g_Task->pos.x = 4915200;
        g_Task->pos.y = 4915200;
        g_Task->pos.z = Area_SampleHeight(g_Task->pos.x.fixed, 4915200) << 16;
        setVector(g_Task, 0xFFFF4925, 0xFFFF0000, 4993220);
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x02));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x03));
    }
}

MATCH void func_801F9B68(void) {
    g_Task->pos.x.fixed += g_Task->vx;
    g_Task->pos.y.fixed += g_Task->vy;
    g_Task->pos.z.fixed += g_Task->vz;
    g_Task->vz -= 1048576;
    func_801F9F8C(&g_Task->pos, 0x20, 8, 0);
    if (g_Task->pos.y.fixed == 0x360000) {
        func_80196070();
    }
}

MATCH void func_801F9C00(void) {
    Actor* work;

    work              = g_Task;
    work->pos.x.fixed = TO_COORD(39);
    work->pos.y.fixed = TO_COORD(8);
    work->pos.z.fixed = TO_COORD(2048);
    work->vz          = 0;
    work->header.mode += 1;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 4));
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 5));
}

MATCH void func_801F9C58(void) {
    g_Task->pos.y.fixed += 0x10000;
    g_Task->pos.z.fixed += g_Task->vz;
    g_Task->vz -= 2097152;
    func_801F9F8C(&g_Task->pos, 0x20, 8, 0);
    if (g_Task->pos.x.fixed == 0xF0000) {
        func_80196070();
    }
}

MATCH void func_801F9CE0(void) {
    Actor* work;

    work              = g_Task;
    work->pos.x.fixed = TO_COORD(25);
    work->pos.y.fixed = TO_COORD(15);
    work->pos.z.fixed = TO_COORD(1536);
    work->vz          = 0;
    work->header.mode += 1;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 10));
}

MATCH void func_801F9D30(void) {
    g_Task->pos.y.fixed += 0x10000;
    g_Task->pos.z.fixed += g_Task->vz;
    g_Task->vz -= 2097152;
    func_801F9F8C(&g_Task->pos, 0x20, 8, 4);
    if (g_Task->pos.y.fixed > 0x18FFFF) {
        func_80196070();
    }
}

MATCH void func_801F9DBC(void) {
    SYS_DISPATCH_TASK(D_801FE938, 1, g_Task);
}

MATCH void func_801F9E00(void) {
    Actor* work;
    u8     mode;

    work              = g_Task;
    mode              = work->header.mode + 1;
    work->pos.x.fixed = TO_COORD(25) + COORD_HALF;
    work->pos.y.fixed = TO_COORD(25) + COORD_HALF;
    work->pos.z.fixed = TO_COORD(1024);
    setVector(work, work->pos.x.fixed + TO_COORD(4), work->pos.y.fixed, work->pos.z.fixed);
    work->header.mode = mode;
}

MATCH void func_801F9E50(void) {
    g_Task->pos.x.fixed -= TO_COORD(2);
    g_Task->vx -= TO_COORD(2);
    func_801FA19C(&g_Task->pos, &g_Task->vx);
    if (g_Task->pos.x.fixed == 0x98000) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F9EC4(void) {
    g_Task->vx -= TO_COORD(2);
    func_801FA19C(&g_Task->pos, &g_Task->vx);
    if (g_Task->vx == 622592) {
        g_Task->header.mode += 1;
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

    FAKE_STACK_PADS(u8, 0x28); /* FAKE: retail reserves 40 unused stack bytes. */

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 0, 0x3C0, 0x100) & 0xFFFF, 0);
    Area_AddCellPrim(pos->x.fixed, pos->y.fixed, (s8)layer, 12);
    Area_SetCameraMatrix(&camera);
    Area_ProjectPoint(&pos->x.fixed, &screen);
    size.vx = size.vy = 0x50;
    Game_ProjectWorldPoint(pos, &size, &scale);
    angle = rand() & 0xFFF;
    depth = layer;
    i     = -scale.vx;
    if (scale.vx >= -scale.vx) {
        do {
            s32 offset;

            root = SquareRoot0((scale.vx * scale.vx) - (i * i));
            line = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(line);
            SetSemiTrans(line, 1);
            offset   = (rsin((u16)angle) * 16) >> 12;
            line->x0 = screen.vx + offset + jitter - root;
            offset   = (rsin((u16)angle) * 16) >> 12;
            line->x1 = screen.vx + offset + jitter + root;
            line->y0 = screen.vy + i;
            line->y1 = screen.vy + i;
            setRGB0(line, 0, 0, 0);
            Area_AddCellPrim(pos->x.fixed, pos->y.fixed, (s8)depth, sizeof(LINE_F2));
            jitter = -jitter;
            angle += rand() & 0xFF;
            i++;
        } while (i <= scale.vx);
    }
}
#else
INCLUDE_ASM(func_801F9F8C);
#endif

MATCH void func_801FA19C(WorldPos* pos, s32* vx) {
    LINE_G2* prim;
    DVECTOR  xy;
    MATRIX   camera;

    GFX_SET_DRAW_MODE(GetTPage(0, 1, 960, 256));
    GFX_AddPrim(1, sizeof(DR_MODE));
    prim = (LINE_G2*)g_GfxPrimCursor;
    SetLineG2(prim);
    SetSemiTrans(prim, 1);
    Area_SetCameraMatrix(&camera);
    Area_ProjectPoint(&pos->x.fixed, &xy);
    setXY0(prim, xy.vx, xy.vy);
    Area_ProjectPoint(vx, &xy);
    prim->x1 = xy.vx;
    prim->y1 = xy.vy;
    setRGB0(prim, 64, 64, 64);
    setRGB1(prim, 0, 0, 0);
    GFX_AddPrim(1, sizeof(LINE_G2));
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

    for (i = 0; i < CHARACTER_COUNT; i++) {
        g_Characters[i].unk_07 |= 1;
    }
    Char_RebuildPartyStats();
    for (i = 1; i < CHARACTER_COUNT; i++) {
        g_Characters[i].unk_07 &= 0xFE;
    }
}

INCLUDE_ASM(func_801FA3E4);

MATCH void func_801FAB5C(void) {
    SYS_DISPATCH_BYTE(D_801FE970, g_SceneState.state_04);
}

MATCH void func_801FAB98(void) {
}

INCLUDE_ASM(func_801FABA0);

MATCH void func_801FB168(void) {
    u8* step;

    step = &D_80146875;
    switch (*step) {
        case 0:
            D_80147ACF = 3;
            D_80147AD6 = 0;
            *step      = 1;
            break;
        case 1:
            if (D_80146867 == 0x12) {
                D_80146876 = 0x10;
                *step      = 2;
            }
            break;
        case 2:
            if (D_80146876-- == 0) {
                SYS_SetFlag(g_SceneFlags, 3);
                D_801448EE       = 1;
                g_SceneEventMode = 5;
                g_SceneEventStep = 3;
                D_80146874       = 0;
                *step            = 0;
            }
            break;
    }
}

INCLUDE_ASM(func_801FB270);
