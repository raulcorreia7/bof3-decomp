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
    if ((g_FrameCount & 3) == 0) {
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
    if ((g_Task->unk_5A & 3) == 0) {
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

INCLUDE_ASM(func_801F7320);

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

INCLUDE_ASM(func_801F75E4);

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

INCLUDE_ASM(func_801F77B4);

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
    Scena08Spark* spark;

    if (g_Task->unk_5A == 4) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x01));
    }
    if ((g_Task->unk_5A & 7) == 0) {
        spark = func_801F8B14();
        if (spark != NULL) {
            func_801F8B50(spark);
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
    g_Task->pos.x = 0x6B0000;
    g_Task->pos.y = 0x460000;
    g_Task->pos.z = Area_SampleHeight(g_Task->pos.x.fixed, 0x460000) << 16;
    g_Task->timer = 0x20;
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
        g_Task->pos.x = 0x640000;
        g_Task->pos.y = 0x760000;
        g_Task->pos.z = Area_SampleHeight(g_Task->pos.x.fixed, 0x760000) << 16;
        g_Task->timer = 0x20;
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

INCLUDE_ASM(func_801F7E14);

INCLUDE_ASM(func_801F802C);

INCLUDE_ASM(func_801F8108);

MATCH void func_801F81F4(u16 value) {
    s32 count;
    s32 index;

    count = 0x40;
    do {
        index = count & BYTE_MASK;
        count -= 1;
        D_801FE9EC[index] = D_801FE9EC[index - 1];
    } while (count & BYTE_MASK);
    D_801FE9EC[0] = value;
}

INCLUDE_ASM(func_801F823C);

INCLUDE_ASM(func_801F8534);

INCLUDE_ASM(func_801F85F0);

INCLUDE_ASM(func_801F8964);

MATCH void func_801F8AE8(void) {
    s32           index;
    Scena08Spark* spark;

    spark = (Scena08Spark*)AREA_WORK;
    index = 0;
    do {
        spark->active = 0;
        index += 1;
        spark += 1;
    } while ((index & BYTE_MASK) < SCENA08_SPARK_COUNT);
}

MATCH Scena08Spark* func_801F8B14(void) {
    Scena08Spark* spark;
    u8            i;

    spark = (Scena08Spark*)AREA_WORK;
    for (i = 0; i < SCENA08_SPARK_COUNT; i++) {
        if (spark->active == 0) {
            return spark;
        }
        spark += 1;
    }
    return NULL;
}

INCLUDE_ASM(func_801F8B50);

MATCH u8 func_801F8BF8(void) {
    u8            i;
    s32           live;
    Scena08Spark* spark;
    u8            buffer[0x20];

    live = 0;
    GFX_AddDitheredDrawMode(1, GetTPage(0, 1, 0x3C0, 0));
    Area_SetCameraMatrix(buffer);
    spark = (Scena08Spark*)AREA_WORK;
    for (i = 0; i < SCENA08_SPARK_COUNT; i += 1, spark += 1) {
        if (spark->active != 0) {
            D_801FE8FC[spark->kind](spark);
            live = 1;
            func_801F8964(spark);
        }
    }
    return live;
}

MATCH void func_801F8CDC(Scena08Spark* spark) {
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

MATCH void func_801F8D4C(Scena08Spark* spark) {
    u8  life;
    s32 speed;

    life         = spark->life - 1;
    speed        = spark->speed + 0x40000;
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

#include "shared/AngleAverage12.h"

INCLUDE_ASM(func_801F9470);

MATCH void func_801F95D4(void) {
    SYS_DISPATCH_TASK(D_801FE908, 1, g_Task);
}

MATCH void func_801F9618(void) {
    func_801F9688();
    if (g_GameAreaId != AREA_ID_DAUNA_MINE_WORKER) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F9668(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801F9688);

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
        g_Task->pos.x = 0x510000;
        g_Task->pos.y = 0x420000;
        g_Task->pos.z = 0x2C00000;
        g_Task->vz    = 0x800000;
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x02));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x03));
    }
}

INCLUDE_ASM(func_801F995C);

MATCH void func_801F9A10(void) {
    g_Task->pos.x.fixed += g_Task->vx;
    g_Task->pos.y.fixed += g_Task->vy;
    g_Task->pos.z.fixed += g_Task->vz;
    g_Task->vz -= 0x200000;
    func_801F9F8C(&g_Task->pos, 0x20, 8, 0);
    if (g_Task->pos.y.fixed == 0x4B0000) {
        g_Task->timer = 0x3C;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F9AC0(void) {
    if (--g_Task->timer == 0) {
        g_Task->pos.x = 0x4B0000;
        g_Task->pos.y = 0x4B0000;
        g_Task->pos.z = Area_SampleHeight(g_Task->pos.x.fixed, 0x4B0000) << 16;
        g_Task->vx    = 0xFFFF4925;
        g_Task->vy    = 0xFFFF0000;
        g_Task->vz    = 0x4C30C4;
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x02));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x03));
    }
}

MATCH void func_801F9B68(void) {
    g_Task->pos.x.fixed += g_Task->vx;
    g_Task->pos.y.fixed += g_Task->vy;
    g_Task->pos.z.fixed += g_Task->vz;
    g_Task->vz -= 0x100000;
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
    g_Task->vz -= 0x200000;
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
    g_Task->vz -= 0x200000;
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
    work->vx          = work->pos.x.fixed + TO_COORD(4);
    work->vy          = work->pos.y.fixed;
    work->vz          = work->pos.z.fixed;
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
    g_Task->vx -= 0x20000;
    func_801FA19C(&g_Task->pos, &g_Task->vx);
    if (g_Task->vx == 0x98000) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F9F2C(void) {
    Scene_AdvanceActorStep();
}

MATCH void func_801F9F4C(void) {
    Scene_AdvanceActorStep();
}

MATCH void func_801F9F6C(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801F9F8C);

INCLUDE_ASM(func_801FA19C);

MATCH void func_801FA294(void) {
    SYS_DISPATCH_BYTE(D_801FE964, D_80146872);
}

MATCH void func_801FA2D0(void) {
    D_80144EC8[0]    = 0;
    g_ScriptVarsWord = 0;
    D_80146872       = 1;
    func_801FA32C();
    func_801FE12C();
    SYS_SetFlag(&D_80144EC8[0x60], 0x43);
}

INCLUDE_ASM(func_801FA32C);

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

INCLUDE_ASM(func_801FB8A0);

INCLUDE_ASM(func_801FBA70);

INCLUDE_ASM(func_801FBCA4);

INCLUDE_ASM(func_801FC21C);

INCLUDE_ASM(func_801FC45C);

INCLUDE_ASM(func_801FD07C);

INCLUDE_ASM(func_801FD1A4);

INCLUDE_ASM(func_801FD400);

INCLUDE_ASM(func_801FD704);

MATCH void func_801FDF84(void) {
    g_Characters[CHAR_INDEX_REI].exp += 10000;
    func_801ADDD4(CHAR_INDEX_REI);
    g_Characters[CHAR_INDEX_REI].equip.weapon = WEAPON_MOON_SWORD;
    g_Characters[CHAR_INDEX_REI].equip.shield = ARMOR_STEEL_GAUNTLETS;
    g_Characters[CHAR_INDEX_REI].equip.helmet = ARMOR_BANDANA;
    g_Characters[CHAR_INDEX_REI].equip.armor  = ARMOR_LIGHT_CLOTHING;
    Char_RebuildStats(&g_Characters[CHAR_INDEX_REI]);
    Char_RestoreHP(CHAR_INDEX_REI, 0, 0);
    Char_RestoreAP(CHAR_INDEX_REI, 0, 0);
}

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH void func_801FE058(void) {
    g_ScriptVars[0] = 0;
    Game_SetScriptActive();
    D_80146874 = 7;
    D_80146876 = 32;
    D_80146875 = 0;
}

MATCH void func_801FE0A0(void) {
    g_ScriptVars[0] = 0;
    Game_SetScriptActive();
    g_SceneState.state_04 = 7;
    g_SceneState.step_05  = 0xA;
}

MATCH void func_801FE0E0(void) {
    g_ScriptVars[0] = 0;
    Game_SetScriptActive();
    D_80146874 = 10;
    D_80146875 = 0;
    SYS_SetFlag(g_SceneFlags, 19);
}

MATCH void func_801FE12C(void) {
    s32 index;
    u8* item;

    item  = &g_VitalItemIds;
    index = 0;
    do {
        if (*item == 4) {
            *item = 0xE;
        }
        index += 1;
        item += 1;
    } while ((index & BYTE_MASK) < 0x20U);
}

MATCH s32 func_801FE170(s32 x, s32 y) {
    if ((g_GameAreaId == AREA_ID_DAUNA_MINE_ADULT) && (x == TO_COORD(51) + COORD_HALF) && (((y >> 0x10) - 39) < 2U)) {
        if (SYS_TestFlag(g_SceneFlags, 6) == 0) {
            Game_SetScriptActive();
            D_80146874 = 4;
            D_80146875 = 5;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 7) == 0) {
            Game_SetScriptActive();
            *g_ScriptVars = 0;
            D_80146874    = 5;
            D_80146875    = 0;
            return 1;
        }
        goto block_7;
    }
block_7:
    if ((g_GameAreaId == AREA_ID_MOUNT_LEVETT) && (x == TO_COORD(56) + COORD_HALF) && (((y >> 0x10) - 46) < 4U)) {
        SYS_SetFlag(g_SceneFlags, 0x16U);
    }
    return 0;
}

INCLUDE_ASM(func_801FE2A0);

/* func_801FE698 */
MATCH void Scene_SetPartyWhelp(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_WHELP, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_WHELP);
    Party_LoadPalettes();
}

/* func_801FE6DC */
MATCH void Scene_SetPartyRyuAdult(void) {
    g_Characters[g_CharSlot[10]].unk_07 &= 0xFE;
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
}

/* func_801FE740 */
MATCH void Party_JoinGarr(void) {
    Party_JoinMember(CHAR_ID_GARR);
}

MATCH void func_801FE760(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_REI, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_GARR);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_SetPartyRyuAdultGarrNinaAdult.h"

MATCH void func_801FE800(void) {
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    Party_JoinMember(CHAR_ID_REI);
    Party_LoadPalettes();
}

MATCH void func_801FE840(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_REI, 0U);
    func_801FE800();
}

/* func_801FE874 */
MATCH void Party_RemoveGarr(void) {
    Party_RemoveMember(CHAR_ID_GARR);
}
