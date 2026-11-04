#include "scena07_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6DD4(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801FDD14[entity[1]]();
}

MATCH void func_801F6E10(void) {
    SYS_DISPATCH_TASK(D_801FDD3C, 2, g_SpadWork);
}

MATCH void func_801F6E54(void) {
    void* temp_v0_9;

    func_801F8358();
    temp_v0_9                   = SP_REF(void*, 0x44);
    FIELD(s32, temp_v0_9, 0xCu) = 0x40;
    FIELD(u8, temp_v0_9, 0x2u)  = (u8)(FIELD(u8, temp_v0_9, 0x2u) + 1);
}

MATCH void func_801F6E90(void) {
    u8* row;

    if ((g_SpadWork->unk_0C & 7) == 0) {
        row = func_801F8394();
        if (row != NULL) {
            func_801F83D0(row);
        }
    }
    func_801F85D8();
    if (--g_SpadWork->unk_0C == 0) {
        g_SpadWork->state_02++;
    }
}

MATCH void func_801F6F14(void) {
    if (!(func_801F85D8() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F6F48(void) {
    SYS_DISPATCH_TASK(D_801FDD48, 2, g_SpadWork);
}

MATCH void func_801F6F8C(void) {
    void* temp_v0_5;

    temp_v0_5                    = SP_REF(void*, 0x44);
    FIELD(s32, temp_v0_5, 0x10u) = -8;
    FIELD(u8, temp_v0_5, 0x2u)   = (u8)(FIELD(u8, temp_v0_5, 0x2u) + 1);
}

MATCH void func_801F6FB0(void) {
    func_801F3C3C(g_SpadWork->unk_10);
    g_SpadWork->unk_10 += (g_FrameCount & 0xF) == 0;
    if (g_SpadWork->unk_10 == 0) {
        Actor_Clear();
    }
}

MATCH void func_801F700C(void) {
    SYS_DISPATCH_TASK(D_801FDD50, 2, g_SpadWork);
}

INCLUDE_ASM(func_801F7050);

INCLUDE_ASM(func_801F70F8);

INCLUDE_ASM(func_801F71C0);

INCLUDE_ASM(func_801F724C);

MATCH void func_801F72E0(void) {
    SCENA07_PANEL_FADE_STEP();
}

MATCH void func_801F7364(void) {
    Scene_AdvanceActorState();
}

MATCH void func_801F7384(void) {
    Scene_AdvanceActorState();
}

MATCH void func_801F73A4(void) {
    Actor_Clear();
}

MATCH void func_801F73C4(void) {
    SYS_DISPATCH_TASK(D_801FDD70, 2, g_SpadWork);
}

INCLUDE_ASM(func_801F7408);

INCLUDE_ASM(func_801F7480);

MATCH void func_801F75C0(void) {
    if (!(func_801F9EFC() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F75F4(void) {
    SYS_DISPATCH_TASK(D_801FDD8C, 2, g_SpadWork);
}

INCLUDE_ASM(func_801F7638);

INCLUDE_ASM(func_801F76D0);

INCLUDE_ASM(func_801F77AC);

INCLUDE_ASM(func_801F7810);

MATCH void func_801F786C(void) {
    SYS_DISPATCH_TASK(D_801FDDAC, 2, g_SpadWork);
}

INCLUDE_ASM(func_801F78B0);

INCLUDE_ASM(func_801F7960);

MATCH void func_801F79EC(void) {
    SYS_DISPATCH_TASK(D_801FDDB4, 2, g_SpadWork);
}

INCLUDE_ASM(func_801F7A30);

INCLUDE_ASM(func_801F7AB0);

MATCH void func_801F7B68(void) {
    if (!(func_801F85D8() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F7B9C(void) {
    SYS_DISPATCH_TASK(D_801FDDC0, 2, g_SpadWork);
}

INCLUDE_ASM(func_801F7BE0);

INCLUDE_ASM(func_801F7C9C);

MATCH void func_801F7D28(void) {
    SYS_DISPATCH_TASK(D_801FDDC8, 2, g_SpadWork);
}

INCLUDE_ASM(func_801F7D6C);

INCLUDE_ASM(func_801F7DDC);

MATCH void func_801F7E24(void) {
    SYS_DISPATCH_TASK(D_801FDDD0, 2, g_SpadWork);
}

MATCH void func_801F7E68(void) {
    u8 i;

    D_800E4C1E = 0xC0;
    for (i = 0; i < 32; i++) {
        func_801F88B8(MEM_PTR(void, 0x800E48E0u));
    }
    if (g_SpadWork->unk_06 != 0) {
        SND_PlayCue(0x203);
    }
    g_SpadWork->state_02++;
}

INCLUDE_ASM(func_801F7EF8);

INCLUDE_ASM(func_801F7FA4);

INCLUDE_ASM(func_801F805C);

MATCH void func_801F80F0(void) {
    SCENA07_PANEL_FADE_STEP();
}

MATCH void func_801F8174(void) {
    Scene_AdvanceActorState();
}

MATCH void func_801F8194(void) {
    Scene_AdvanceActorState();
}

MATCH void func_801F81B4(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801F81D4);

MATCH void func_801F8358(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK_WINDOW_ADDRESS);
    i = 0;
    do {
        p[0] = 0;
        i++;
        p += 0x1C;
    } while (i < 8);
    D_801FDFC4 = 0;
    D_801FDFC8 = 0;
}

MATCH u8* func_801F8394(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK_WINDOW_ADDRESS);
    for (i = 0; i < 8; i++) {
        if (p[SCRATCH_ROW_OFFSET] == 0) {
            return p;
        }
        p += SCRATCH_ROW_STRIDE;
    }
    return NULL;
}

INCLUDE_ASM(func_801F83D0);

INCLUDE_ASM(func_801F8478);

INCLUDE_ASM(func_801F85D8);

INCLUDE_ASM(func_801F86BC);

#include "overlays/scenario/Actor_WaitAndStep.h"

INCLUDE_ASM(func_801F8764);

MATCH void func_801F8804(u8 shade) {
    TILE* tile;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 2, 960, 0), 0);
    GFX_AddPrim(1, 0x0C);
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    PSX_SET_SEMI_TRANSPARENT(tile);
    tile->w  = 320;
    tile->x0 = 0;
    tile->y0 = 0;
    tile->h  = 240;
    setRGB0(tile, shade, shade, shade);
    GFX_AddPrim(1, 0x10);
}

INCLUDE_ASM(func_801F88B8);

INCLUDE_ASM(func_801F8BE8);

#include "shared/AngleAverage12.h"

INCLUDE_ASM(func_801F8F90);

INCLUDE_ASM(func_801F90F4);

INCLUDE_ASM(func_801F9330);

INCLUDE_ASM(func_801F97E0);

INCLUDE_ASM(func_801F9A80);

INCLUDE_ASM(func_801F9BDC);

MATCH void func_801F9DA8(void) {
    s32 var_v1_6;
    s8* var_a0_5;

    var_a0_5 = (s8*)(AREA_WORK_WINDOW + 0x95C);
    var_v1_6 = 0;
    do {
        *var_a0_5 = 0;
        var_v1_6 += 1;
        var_a0_5 += 0x20;
    } while ((u32)(var_v1_6 & BYTE_MASK) < 0x40U);
}

INCLUDE_ASM(func_801F9DD4);

INCLUDE_ASM(func_801F9E10);

INCLUDE_ASM(func_801F9EFC);

INCLUDE_ASM(func_801FA01C);

INCLUDE_ASM(func_801FA38C);

MATCH void func_801FA65C(void) {
    SYS_DISPATCH_BYTE(D_801FDE10, D_80146872);
}

MATCH void func_801FA698(void) {
    D_80144EC0 = 0;
    D_80146872 = 1;
}

INCLUDE_ASM(func_801FA6B4);

MATCH void func_801FAA2C(void) {
    SYS_DISPATCH_BYTE(D_801FDE1C, g_SceneState.state_04);
}

MATCH void func_801FAA68(void) {
}

INCLUDE_ASM(func_801FAA70);

INCLUDE_ASM(func_801FABD8);

INCLUDE_ASM(func_801FB6DC);

INCLUDE_ASM(func_801FB914);

INCLUDE_ASM(func_801FC094);

INCLUDE_ASM(func_801FC1C4);

INCLUDE_ASM(func_801FC2D0);

INCLUDE_ASM(func_801FCFB4);

INCLUDE_ASM(func_801FD000);

INCLUDE_ASM(func_801FD0DC);

INCLUDE_ASM(func_801FD35C);

MATCH void func_801FD3BC(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FDF8C[index];
    handler(entity, g_SceneFlags);
}

INCLUDE_ASM(func_801FD3FC);

INCLUDE_ASM(func_801FD45C);

INCLUDE_ASM(func_801FD4C4);

INCLUDE_ASM(func_801FD524);

INCLUDE_ASM(func_801FD5A0);

INCLUDE_ASM(func_801FD610);

INCLUDE_ASM(func_801FD67C);

INCLUDE_ASM(func_801FD960);

INCLUDE_ASM(func_801FDA34);

INCLUDE_ASM(func_801FDA98);

MATCH void func_801FDAFC(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 6;
    g_SceneState.step_05  = 0xA;
}

MATCH void func_801FDB34(void) {
    EMI_LoaderStreamFamily(0, 1, 5, 0);
    g_PartySize = 0;
    func_801C187C(0);
    func_801C187C(1);
    func_801C187C(5);
}

MATCH void func_801FDB80(void) {
    EMI_LoaderStreamFamily(0, 1, 2, 0);
    g_PartySize = 0;
    Party_JoinMember(0);
    Party_JoinMember(1);
    Party_JoinMember(2);
}

MATCH void func_801FDBCC(void) {
    func_801C1ABC(D_80146189);
}

INCLUDE_ASM(func_801FDBF4);
