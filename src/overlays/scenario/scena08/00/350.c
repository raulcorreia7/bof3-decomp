#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6F50(void) {
    u8* entity;

    D_801FE894[entity[1]]();
}

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

INCLUDE_ASM(func_801F70C0);

INCLUDE_ASM(func_801F7164);

/* Hint: reads D_801492DA as lhu for the scroll argument and as lh for the compare, so one signed type fails either way. */
INCLUDE_ASM(func_801F7200);

INCLUDE_ASM(func_801F7268);

INCLUDE_ASM(func_801F7320);

/* Hint: reads screen_x and screen_y as signed halves (lh); the Actor members are u16, so the draft loads lhu. */
INCLUDE_ASM(func_801F73D4);

INCLUDE_ASM(func_801F743C);

INCLUDE_ASM(func_801F74E0);

MATCH void func_801F757C(void) {
    func_801F8534();
    g_Task->script_pc += rand() & 0xFF;
    if (g_ScriptVars[0] == 0xB) {
        g_Task->unk_5A = 0x20;
        g_Task->header.mode += 1;
    }
}

INCLUDE_ASM(func_801F75E4);

INCLUDE_ASM(func_801F7688);

/* Hint: same shape as func_801F73D4 (lh of screen_x and screen_y, u16 members); here the 0x32 update is -0x10. */
INCLUDE_ASM(func_801F774C);

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

INCLUDE_ASM(func_801F79EC);

MATCH void func_801F7A9C(void) {
    if (!(func_801F8BF8() & BYTE_MASK)) {
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F7AD0);

INCLUDE_ASM(func_801F7B2C);

MATCH void func_801F7BA8(void) {
    Actor* work;
    u8     timer;

    work  = g_Task;
    timer = work->timer - 1;
    work->pos.y.fixed += TO_COORD(1);
    work->timer = timer;
    if (timer == 0) {
        g_Task->timer       = 0x10;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

INCLUDE_ASM(func_801F7C08);

MATCH void func_801F7C98(void) {
    Actor* work;
    u8     timer;

    work  = g_Task;
    timer = work->timer - 1;
    work->pos.y.fixed -= TO_COORD(1);
    work->timer = timer;
    if (timer == 0) {
        g_Task->timer       = 0x80;
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

MATCH void func_801F81F4(u16 arg0) {
    s32 count;
    s32 index;

    count = 0x40;
    do {
        index = count & 0xFF;
        count -= 1;
        D_801FE9EC[index] = D_801FE9EC[index - 1];
    } while (count & 0xFF);
    D_801FE9EC[0] = arg0;
}

INCLUDE_ASM(func_801F823C);

INCLUDE_ASM(func_801F8534);

INCLUDE_ASM(func_801F85F0);

INCLUDE_ASM(func_801F8964);

MATCH void func_801F8AE8(void) {
    s32 index;
    s8* cell;

    cell  = (s8*)AREA_WORK;
    index = 0;
    do {
        *cell = 0;
        index += 1;
        cell += 0x1C;
    } while ((index & BYTE_MASK) < 8U);
}

MATCH u8* func_801F8B14(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK);
    for (i = 0; i < 8; i++) {
        if (*p == 0) {
            return p;
        }
        p += 0x1C;
    }
    return NULL;
}

INCLUDE_ASM(func_801F8B50);

MATCH s32 func_801F8BF8(void) {
    u8  i;
    s32 live;
    u8* slot;
    u8  buffer[0x20];

    live = 0;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, 0x3C0, 0), 0);
    GFX_AddPrim(1, 0xC);
    Area_SetCameraMatrix(buffer);
    slot = MEM_PTR(u8, AREA_WORK);
    for (i = 0; i < 8; i += 1, slot += 0x1C) {
        if (slot[0] != 0) {
            D_801FE8FC[slot[1]](slot);
            live = 1;
            func_801F8964(slot);
        }
    }
    return live;
}

MATCH void func_801F8CDC(Actor* actor) {
    u8 state;

    state = actor->header.step - 1;
    actor->unk_03 += 6;
    actor->header.step = state;
    if (state == 0) {
        actor->header.step = actor->unk_04;
        actor->header.mode += 1;
    }
}

#include "overlays/scenario/Actor_Wait.h"

/* blocker: row load order; first diff: +0x10 lw v1,20(a2) (candidate) against lbu v1,3(a2) (retail). */
/* Hint: steps a 3-byte-header record: byte 0x02 counts down, 0x03 adds 6, word 0x08 adds 0x40000, word 0x14 accumulates 0x08; the record type with word 0x08 and 0x14 is not named yet. */
INCLUDE_ASM(func_801F8D4C);

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

/* Stores 60 in byte 9 and increments byte 1 of the scratchpad buffer at slots[0x11]. */
MATCH void func_801F98B0(void) {
    u8** slots;

    slots          = SP_PTR(u8*, 0u);
    slots[0x11][9] = 0x3C;
    slots          = SP_PTR(u8*, 0u);
    slots[0x11][1]++;
}

MATCH void func_801F98E0(void) {
    if (--g_Task->timer == 0) {
        g_Task->pos.x = 0x510000;
        g_Task->pos.y = 0x420000;
        g_Task->pos.z = 0x2C00000;
        g_Task->vz    = 0x800000;
        g_Task->header.mode += 1;
        SND_PlayCue(0x202);
        SND_PlayCue(0x203);
    }
}

INCLUDE_ASM(func_801F995C);

INCLUDE_ASM(func_801F9A10);

INCLUDE_ASM(func_801F9AC0);

INCLUDE_ASM(func_801F9B68);

MATCH void func_801F9C00(void) {
    Actor* work;

    work              = g_Task;
    work->pos.x.fixed = TO_COORD(39);
    work->pos.y.fixed = TO_COORD(8);
    work->pos.z.fixed = TO_COORD(2048);
    work->vz          = 0;
    work->header.mode += 1;
    SND_PlayCue(EMI_CUE_ID(2, 4));
    SND_PlayCue(EMI_CUE_ID(2, 5));
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
    SND_PlayCue(EMI_CUE_ID(2, 10));
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

/* blocker: ori in the work load delay slot; first diff: +4 ori v1,v1,0x8000 against lui v0,0x1f80. */
INCLUDE_ASM(func_801F9E00);

INCLUDE_ASM(func_801F9E50);

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

INCLUDE_ASM(func_801FA2D0);

INCLUDE_ASM(func_801FA32C);

INCLUDE_ASM(func_801FA3E4);

MATCH void func_801FAB5C(void) {
    SYS_DISPATCH_BYTE(D_801FE970, g_SceneState.state_04);
}

MATCH void func_801FAB98(void) {
}

INCLUDE_ASM(func_801FABA0);

INCLUDE_ASM(func_801FB168);

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

INCLUDE_ASM(func_801FDF84);

MATCH void func_801FE018(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FE9C0[index];
    handler(entity, g_SceneFlags);
}

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
    } while ((index & 0xFF) < 0x20U);
}

MATCH s32 func_801FE170(s32 arg0, s32 arg1) {
    if ((g_GameAreaId == AREA_ID_DAUNA_MINE_ADULT) && (arg0 == TO_COORD(51) + COORD_HALF) &&
        (((arg1 >> 0x10) - 39) < 2U)) {
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
    if ((g_GameAreaId == AREA_ID_MOUNT_LEVETT) && (arg0 == TO_COORD(56) + COORD_HALF) && (((arg1 >> 0x10) - 46) < 4U)) {
        SYS_SetFlag(g_SceneFlags, 0x16U);
    }
    return 0;
}

INCLUDE_ASM(func_801FE2A0);

MATCH void func_801FE698(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_WHELP, 0);
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_WHELP);
    Party_StagePalettes();
}

MATCH void func_801FE6DC(void) {
    g_Characters[g_CharSlot[10]].unk_07 &= 0xFE;
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
}

MATCH void func_801FE740(void) {
    Party_JoinMember(CHAR_ID_GARR);
}

MATCH void func_801FE760(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_REI, 0);
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_GARR);
    Party_StagePalettes();
}

#include "overlays/scenario/Scene_SetPartyRyuAdultGarrNinaAdult.h"

MATCH void func_801FE800(void) {
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    Party_JoinMember(CHAR_ID_REI);
    Party_StagePalettes();
}

MATCH void func_801FE840(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_REI, 0U);
    func_801FE800();
}

MATCH void func_801FE874(void) {
    Party_RemoveMember(CHAR_ID_GARR);
}
