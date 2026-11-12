#include "scena07_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801F6E10(void) {
    SYS_DISPATCH_TASK(D_801FDD3C, 2, g_Task);
}

MATCH void func_801F6E54(void) {
    void* work;

    func_801F8358();
    work                   = SP_REF(void*, 0x44);
    FIELD(s32, work, 0xCu) = 0x40;
    FIELD(u8, work, 0x2u)  = (FIELD(u8, work, 0x2u) + 1);
}

MATCH void func_801F6E90(void) {
    u8* row;

    if ((g_Task->vx & 7) == 0) {
        row = func_801F8394();
        if (row != NULL) {
            func_801F83D0(row);
        }
    }
    func_801F85D8();
    if (--g_Task->vx == 0) {
        g_Task->header.step++;
    }
}

MATCH void func_801F6F14(void) {
    if (!(func_801F85D8() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F6F48(void) {
    SYS_DISPATCH_TASK(D_801FDD48, 2, g_Task);
}

MATCH void func_801F6F8C(void) {
    void* work;

    work                    = SP_REF(void*, 0x44);
    FIELD(s32, work, 0x10u) = -8;
    FIELD(u8, work, 0x2u)   = (FIELD(u8, work, 0x2u) + 1);
}

MATCH void func_801F6FB0(void) {
    func_801F3C3C(g_Task->vy);
    g_Task->vy += (g_FrameCount & 0xF) == 0;
    if (g_Task->vy == 0) {
        Actor_Clear();
    }
}

MATCH void func_801F700C(void) {
    SYS_DISPATCH_TASK(D_801FDD50, 2, g_Task);
}

MATCH void func_801F7050(void) {
    Actor* work;
    Actor* actor;
    u8     i;

    /* FAKE: the second pointer reproduces retail's copy of the scratch pointer (move into a2). */
    work       = g_Task;
    D_800E4C1E = 0xC0;
    actor      = work;
    actor->vz  = 0;
    for (i = 0; i < 16; i++) {
        actor->vz += 0x800000;
        actor->pos.x.fixed += TO_COORD(1);
        actor->pos.y.fixed += 0;
        actor->pos.z.fixed += actor->vz;
    }
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));
    g_Task->vz = -g_Task->vz;
    g_Task->header.step++;
}

INCLUDE_ASM(func_801F70F8);

MATCH void func_801F71C0(void) {
    func_801F88B8(SCENA07_PANEL_ROWS);
    func_801F8BE8(SCENA07_PANEL_ROWS);
    if (--g_Task->timer == 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
        g_Task->timer = 32;
        g_Task->header.step++;
    }
}

MATCH void func_801F724C(void) {
    SCENA07_PANEL_BRIGHTEN_STEP();
}

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
    SYS_DISPATCH_TASK(D_801FDD70, 2, g_Task);
}

MATCH void func_801F7408(void) {
    /* FAKE: the retail frame holds 0x10 bytes no statement explains. */
    FAKE_STACK_PADS(u8, 0x10);

    g_Task->pos.z.fixed = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) << 16;
    func_801F9DA8();
    g_Task->timer = 0;
    g_Task->vx    = 95;
    g_Task->header.step++;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 5));
}

INCLUDE_ASM(func_801F7480);

MATCH void func_801F75C0(void) {
    if (!(func_801F9EFC() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F75F4(void) {
    SYS_DISPATCH_TASK(D_801FDD8C, 2, g_Task);
}

INCLUDE_ASM(func_801F7638);

INCLUDE_ASM(func_801F76D0);

MATCH void func_801F77AC(void) {
    D_801FDFBC->unk_10 += 4;
    func_801F97E0(D_801FDFBC);
    if (--g_Task->vx == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801F7810(void) {
    D_801FDFBC->z += 0x1000000;
    func_801F97E0(D_801FDFBC);
    if (D_801FDFBC->z > 0xFFFFFFF) {
        func_80196070();
    }
}

MATCH void func_801F786C(void) {
    SYS_DISPATCH_TASK(D_801FDDAC, 2, g_Task);
}

INCLUDE_ASM(func_801F78B0);

MATCH void func_801F7960(void) {
    Scene_TurnBurst(64);
}

MATCH void func_801F79EC(void) {
    SYS_DISPATCH_TASK(D_801FDDB4, 2, g_Task);
}

INCLUDE_ASM(func_801F7A30);

INCLUDE_ASM(func_801F7AB0);

MATCH void func_801F7B68(void) {
    if (!(func_801F85D8() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F7B9C(void) {
    SYS_DISPATCH_TASK(D_801FDDC0, 2, g_Task);
}

INCLUDE_ASM(func_801F7BE0);

MATCH void func_801F7C9C(void) {
    Scene_TurnBurst(-64);
}

MATCH void func_801F7D28(void) {
    SYS_DISPATCH_TASK(D_801FDDC8, 2, g_Task);
}

INCLUDE_ASM(func_801F7D6C);

MATCH void func_801F7DDC(void) {
    func_801FA38C();
    g_Task->vx = g_Task->vx - 1;
    if (g_Task->vx == 0) {
        Actor_Clear();
    }
}

MATCH void func_801F7E24(void) {
    SYS_DISPATCH_TASK(D_801FDDD0, 2, g_Task);
}

MATCH void func_801F7E68(void) {
    u8 i;

    D_800E4C1E = 0xC0;
    for (i = 0; i < 32; i++) {
        func_801F88B8(SCENA07_PANEL_ROWS);
    }
    if (g_Task->unk_06 != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
    }
    g_Task->header.step++;
}

MATCH void func_801F7EF8(void) {
    func_801F88B8(SCENA07_PANEL_ROWS);
    func_801F8BE8(SCENA07_PANEL_ROWS);
    g_Task->pos.x.fixed += g_Task->vx;
    g_Task->pos.y.fixed += g_Task->vy;
    g_Task->pos.z.fixed += g_Task->vz;
    if (g_Task->pos.x.fixed == g_Task->unk_18 && g_Task->pos.y.fixed == g_Task->unk_1C) {
        g_Task->timer = 47;
        g_Task->header.step++;
    }
}

MATCH void func_801F7FA4(void) {
    func_801F88B8(SCENA07_PANEL_ROWS);
    func_801F8BE8(SCENA07_PANEL_ROWS);
    if (--g_Task->timer == 0) {
        if (g_Task->unk_06 == 0) {
            Actor_Clear();
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 4));
            g_Task->timer = 32;
            g_Task->header.step++;
        }
    }
}

MATCH void func_801F805C(void) {
    SCENA07_PANEL_BRIGHTEN_STEP();
}

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

    p = MEM_PTR(u8, AREA_WORK);
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

    p = MEM_PTR(u8, AREA_WORK);
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

MATCH u8 func_801F85D8(void) {
    u8     active;
    u8*    rec;
    s32    i;
    MATRIX matrix;

    active = 0;
    GFX_AddDitheredDrawMode(1, GetTPage(0, 1, FONT_TPAGE_X, FONT_TPAGE_Y));
    Area_SetCameraMatrix(&matrix);
    rec = MEM_PTR(u8, AREA_WORK);
    i   = 0;
    do {
        if (rec[0] != 0) {
            D_801FDDF0[rec[1]](rec);
            active = 1;
            func_801F81D4(rec);
        }
        i++;
        rec += SCRATCH_ROW_STRIDE;
    } while ((u32)(i & BYTE_MASK) < 8);
    return active;
}

MATCH void func_801F86BC(u8* row) {
    u8 next;

    row[3] += 6;
    if (--row[2] == 0) {
        next   = row[1] + 1;
        row[2] = row[4];
        row[1] = next;
        if (D_801FDFC4 == 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
            D_801FDFC4 = 1;
        }
    }
}

#include "overlays/scenario/Actor_Wait.h"

INCLUDE_ASM(func_801F8764);

MATCH void func_801F8804(u8 shade) {
    TILE* tile;

    GFX_AddDitheredDrawMode(1, GetTPage(0, 2, FONT_TPAGE_X, FONT_TPAGE_Y));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    setXY0(tile, 0, 0);
    setWH(tile, 320, 240);
    setRGB0(tile, shade, shade, shade);
    GFX_AddPrim(1, sizeof(TILE));
}

INCLUDE_ASM(func_801F88B8);

INCLUDE_ASM(func_801F8BE8);

#include "shared/AngleAverage12.h"

#include "shared/GFX_DrawFan.h"

INCLUDE_ASM(func_801F90F4);

INCLUDE_ASM(func_801F9330);

INCLUDE_ASM(func_801F97E0);

INCLUDE_ASM(func_801F9A80);

INCLUDE_ASM(func_801F9BDC);

MATCH void func_801F9DA8(void) {
    s32 index;
    s8* row;

    row   = (s8*)(AREA_WORK + 0x95C);
    index = 0;
    do {
        *row = 0;
        index += 1;
        row += 0x20;
    } while ((index & BYTE_MASK) < 0x40U);
}

MATCH u8* func_801F9DD4(void) {
    u8* row;
    u8  i;

    row = MEM_PTR(u8, AREA_WORK + 0x95C);
    for (i = 0; i < 64; i++) {
        if (row[0] == 0) {
            return row;
        }
        row += 0x20;
    }
    return NULL;
}

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

MATCH void func_801FAA70(void) {
    u8* step = &g_SceneState.step_05;

    switch (*step) {
        case 0:
            if (g_UiWindowEffectBusy == 0) {
                Message_StartAreaMessage(1);
                g_GameStateIndex = 2;
                *step            = 1;
            }
            break;
        case 1:
            if (g_GameStateIndex != 2) {
                UI_SetMode(1);
                g_AreaScrollTargetX = 0x2D8000;
                g_AreaScrollTargetY = 0x5D0000;
                func_80153DE8();
                g_AreaDrawFlags = 0x1F;
                *step           = 2;
            }
            break;
        case 2:
            if (g_UiWindowEffectBusy == 0) {
                *g_ScriptVars = 1;
                *step         = 3;
            }
            break;
        case 3:
            if (*g_ScriptVars == 0x15) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0);
                *g_ScriptVars         = 0;
                g_SceneState.state_04 = 0;
                *step                 = 0;
            }
            break;
    }
}

INCLUDE_ASM(func_801FABD8);

INCLUDE_ASM(func_801FB6DC);

INCLUDE_ASM(func_801FB914);

INCLUDE_ASM(func_801FC094);

MATCH void func_801FC1C4(void) {
    u8* step;

    step = &g_SceneState.step_05;
    switch (*step) {
        case 0:
            func_8019FA28(0x35, 0x120000, 0x180000, 1);
            g_GamePrevSelection = 0x4D;
            *step               = 1;
            break;
        case 1:
            if (g_UiWindowEffectBusy == 0) {
                *step = 2;
            }
            break;
        case 2:
            if (*g_ScriptVars == 9) {
                SYS_SetFlag(g_SceneFlags, 7);
                func_8019FA28(0x58, 0x350000, 0x230000, 3);
                g_GameFlags &= ~GAME_FLAG_SCROLL_LOCK;
                Game_ClearScriptActive();
                g_SceneState.state_04 = 0;
                *step                 = 0;
            }
            break;
    }
}

INCLUDE_ASM(func_801FC2D0);

MATCH void func_801FCFB4(void) {
    u8 cam                   = D_801FDE88[g_FrameCount & 3];
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = g_AreaCameraOffsetY + ((cam << 24) >> 22);
}

INCLUDE_ASM(func_801FD000);

INCLUDE_ASM(func_801FD0DC);

MATCH void func_801FD35C(void) {
    u8* timer;

    timer = &g_SceneState.step_05;
    if (*timer == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        Game_ClearScriptActive();
        g_SceneState.state_04 = 0;
        *timer                = 0;
    }
}

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH void func_801FD3FC(Actor* actor) {
    SYS_SetFlag(g_SceneFlags, 0xA);
    Game_SetScriptActive();
    SCENE_START_ACTOR(actor, 3, 0x5);
}

MATCH void func_801FD45C(Actor* actor) {
    SYS_SetFlag(g_SceneFlags, 0xB);
    Item_VitalAdd(VITAL_ITEM_GUILD_LETTER);
    Game_SetScriptActive();
    SCENE_START_ACTOR(actor, 4, 6);
}

MATCH void func_801FD4C4(Actor* actor) {
    SYS_SetFlag(g_SceneFlags, 0xC);
    Game_SetScriptActive();
    SCENE_START_ACTOR(actor, 9, 0x1D);
}

MATCH void func_801FD524(void) {
    Game_SetScriptActive();
    g_ScriptVars[0] = 0;
    g_ScriptVars[1] = 0;
    g_ScriptVars[2] = 0;
    g_ScriptVars[3] = 0;
    if (SYS_TestFlag(D_80144EB8, 0x22) == 0) {
        g_SceneState.step_05 = 0;
    } else {
        g_SceneState.step_05 = 0x14;
    }
    g_SceneState.state_04 = 7;
}

MATCH void func_801FD5A0(void) {
    Game_SetScriptActive();
    g_ScriptVars[0] = 0;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    if (SYS_TestFlag(D_80144EB8, 0x23)) {
        D_80146875 = 0x14;
    } else {
        D_80146875 = 0xA;
    }
    D_80146874 = 7;
}

MATCH ActorSlot* func_801FD610(u8 mode) {
    ActorSlot* slot;
    s32        index;

    index = Actor_FindFreeSlot() & BYTE_MASK;
    slot  = &g_ActorSlots[index];
    if (index != 0xFF) {
        slot->header.flags = 1;
        slot->type         = 0x49;
        slot->header.mode  = mode;
    }
    return slot;
}

INCLUDE_ASM(func_801FD67C);

MATCH s32 func_801FD960(s32 x, s32 y) {
    s32 value;

    if (g_GameAreaId == AREA_ID_MOUNT_ZUBLO_GISSHAN) {
        if ((SYS_TestFlag(g_SceneFlags, 3) == 0) && (y <= TO_COORD(32))) {
            if (((x >> 0x10) - 74) < 2U) {
                Game_SetScriptActive();
                value = g_SndBGMId * 4;
                SND_StartDecrescendo(g_SelectionCues[value], g_SelectionCues[value + 1], 0x64, 0x20);
                g_SceneState.state_04 = 4;
                g_SceneState.step_05  = 0;
                return 1;
            }
        }
    }
    return 0;
}

MATCH bool func_801FDA34(void) {
    u8 i;

    for (i = 0; i < g_Game.party_size; i++) {
        if (g_Game.members[i].chr.character_id == 2) {
            return 1;
        }
    }
    return 0;
}

#include "overlays/scenario/Scene_DispatchByPosition.h"

MATCH void func_801FDAFC(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 6;
    g_SceneState.step_05  = 0xA;
}

#include "overlays/scenario/Scene_SetPartyRyuYoungNinaYoungMomo.h"

MATCH void Scene_SetPartyRyuYoungNinaYoungGarr(void) {
    SCENE_SET_PARTY_NO_RESTAGE(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_GARR);
}

MATCH void func_801FDBCC(void) {
    Party_RemoveMember(D_80146189);
}

INCLUDE_ASM(func_801FDBF4);
