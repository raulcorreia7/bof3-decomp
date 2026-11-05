#include "scena08_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6F50(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801FE894[entity[1]]();
}

MATCH void func_801F6F8C(void) {
    Actor* work;

    func_801F7DE8();
    work         = g_SpadWork;
    work->unk_0C = 0;
    work->unk_01 += 1;
}

INCLUDE_ASM(func_801F6FC4);

MATCH void func_801F7048(void) {
    if (func_801F7E14() & BYTE_MASK) {
        Actor_Clear();
    }
}

MATCH void func_801F707C(void) {
    SYS_DISPATCH_TASK(D_801FE8A0, 1, g_SpadWork);
}

INCLUDE_ASM(func_801F70C0);

INCLUDE_ASM(func_801F7164);

INCLUDE_ASM(func_801F7200);

INCLUDE_ASM(func_801F7268);

INCLUDE_ASM(func_801F7320);

INCLUDE_ASM(func_801F73D4);

INCLUDE_ASM(func_801F743C);

INCLUDE_ASM(func_801F74E0);

INCLUDE_ASM(func_801F757C);

INCLUDE_ASM(func_801F75E4);

INCLUDE_ASM(func_801F7688);

INCLUDE_ASM(func_801F774C);

INCLUDE_ASM(func_801F77B4);

MATCH void func_801F7928(void) {
    SYS_DISPATCH_TASK(D_801FE8D0, 1, g_SpadWork);
}

MATCH void func_801F796C(void) {
    SYS_DISPATCH_TASK(D_801FE8D8, 2, g_SpadWork);
}

MATCH void func_801F79B0(void) {
    Actor* work;

    func_801F8AE8();
    work           = g_SpadWork;
    work->unk_5A   = 0x40;
    work->state_02 = work->state_02 + 1;
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

    work          = g_SpadWork;
    timer         = work->unk_09 - 1;
    work->y.fixed = work->y.fixed + 0x10000;
    work->unk_09  = timer;
    if (timer == 0) {
        g_SpadWork->unk_09   = 0x10;
        g_SpadWork->state_02 = g_SpadWork->state_02 + 1;
    }
}

INCLUDE_ASM(func_801F7C08);

MATCH void func_801F7C98(void) {
    Actor* work;
    u8     timer;

    work          = g_SpadWork;
    timer         = work->unk_09 - 1;
    work->y.fixed = work->y.fixed - 0x10000;
    work->unk_09  = timer;
    if (timer == 0) {
        g_SpadWork->unk_09   = 0x80;
        g_SpadWork->state_02 = g_SpadWork->state_02 + 1;
    }
}

MATCH void func_801F7CF8(void) {
    u8 timer;

    timer              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = timer;
    if (timer == 0) {
        g_SpadWork->unk_09   = 8;
        g_SpadWork->state_02 = g_SpadWork->state_02 + 1;
    }
}

MATCH void func_801F7D54(void) {
    u8 timer;

    D_800E4C1E -= 0x18;
    timer              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = timer;
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
    } while ((u32)(index & BYTE_MASK) < 0x40U);
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
    } while ((u32)(index & BYTE_MASK) < 8U);
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

INCLUDE_ASM(func_801F8BF8);

INCLUDE_ASM(func_801F8CDC);

#include "overlays/scenario/Actor_WaitAndStep.h"

INCLUDE_ASM(func_801F8D4C);

INCLUDE_ASM(func_801F8D98);

INCLUDE_ASM(func_801F90C8);

#include "shared/AngleAverage12.h"

INCLUDE_ASM(func_801F9470);

MATCH void func_801F95D4(void) {
    SYS_DISPATCH_TASK(D_801FE908, 1, g_SpadWork);
}

INCLUDE_ASM(func_801F9618);

MATCH void func_801F9668(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801F9688);

MATCH void func_801F986C(void) {
    SYS_DISPATCH_TASK(D_801FE910, 1, g_SpadWork);
}

/* Stores 60 in byte 9 and increments byte 1 of the scratchpad buffer at slots[0x11]. */
MATCH void func_801F98B0(void) {
    void** slots;
    void*  sp_ptr;

    slots            = SP_PTR(void*, 0u);
    sp_ptr           = slots[0x11];
    ((u8*)sp_ptr)[9] = 0x3C;
    sp_ptr           = slots[0x11];
    ((u8*)sp_ptr)[1]++;
}

INCLUDE_ASM(func_801F98E0);

INCLUDE_ASM(func_801F995C);

INCLUDE_ASM(func_801F9A10);

INCLUDE_ASM(func_801F9AC0);

INCLUDE_ASM(func_801F9B68);

INCLUDE_ASM(func_801F9C00);

INCLUDE_ASM(func_801F9C58);

MATCH void func_801F9CE0(void) {
    Actor* work;

    work          = g_SpadWork;
    work->x.fixed = 0x190000;
    work->y.fixed = 0xF0000;
    work->z.fixed = 0x6000000;
    work->vz      = 0;
    work->unk_01 += 1;
    SND_PlayCue(0x20A);
}

INCLUDE_ASM(func_801F9D30);

MATCH void func_801F9DBC(void) {
    SYS_DISPATCH_TASK(D_801FE938, 1, g_SpadWork);
}

INCLUDE_ASM(func_801F9E00);

INCLUDE_ASM(func_801F9E50);

INCLUDE_ASM(func_801F9EC4);

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
    } while ((u32)(index & 0xFF) < 0x20U);
}

MATCH s32 func_801FE170(s32 arg0, s32 arg1) {
    if ((g_GameAreaId == 1) && (arg0 == 0x338000) && ((u32)((arg1 >> 0x10) - 0x27) < 2U)) {
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
    if ((g_GameAreaId == 0x46) && (arg0 == 0x388000) && ((u32)((arg1 >> 0x10) - 0x2E) < 4U)) {
        SYS_SetFlag(g_SceneFlags, 0x16U);
    }
    return 0;
}

INCLUDE_ASM(func_801FE2A0);

MATCH void func_801FE698(void) {
    EMI_LoaderStreamFamily(7, 2, 10, 0);
    g_PartySize = 0;
    Party_JoinMember(10);
    func_801C1630();
}

MATCH void func_801FE6DC(void) {
    g_Characters[g_CharSlot[10]].unk_07 &= 0xFE;
    g_PartySize = 0;
    Party_JoinMember(7);
}

MATCH void func_801FE740(void) {
    Party_JoinMember(2);
}

MATCH void func_801FE760(void) {
    EMI_LoaderStreamFamily(7, 2, 4, 0);
    g_PartySize = 0;
    Party_JoinMember(7);
    Party_JoinMember(2);
    func_801C1630();
}

MATCH void func_801FE7AC(void) {
    EMI_LoaderStreamFamily(7, 2, 8, 0);
    g_PartySize = 0;
    func_801C187C(7);
    func_801C187C(2);
    func_801C187C(8);
    func_801C1630();
}

MATCH void func_801FE800(void) {
    g_PartySize = 0;
    Party_JoinMember(7);
    Party_JoinMember(8);
    Party_JoinMember(4);
    func_801C1630();
}

MATCH void func_801FE840(void) {
    EMI_LoaderStreamFamily(7U, 8U, 4U, 0U);
    func_801FE800();
}

MATCH void func_801FE874(void) {
    func_801C1ABC(2);
}
