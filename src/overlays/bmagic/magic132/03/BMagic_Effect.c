#include "magic132_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC18.h"

MATCH void func_801EEC88(void) {
    u8            slot;
    u32           i;
    u16*          dst;
    u16*          src;
    PartyMember*  work;
    PartyMember** selected;

    g_Task->facing = g_BattleEffectBattler->facing;
    Battle_CenterCamera();
    slot                               = Battle_AllocEffect(1, 100);
    work                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 24;
    g_BattleEffects[slot].target.party = work;
    for (i = 0, dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW), src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW); i < 256; i++) {
        *dst++ = *src++ | 0x8000;
    }
    selected            = &D_8014637C;
    g_GfxPalettePending = 1;
    GFX_FreePaletteFadeTarget(*selected);
    g_Task->timer = GFX_AllocPaletteFade(*selected, 0, 0, 0, 1);
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.mode += 1;
}

MATCH void func_801EEDD0(void) {
    g_PaletteFades[g_Task->timer].offset.red++;
    g_PaletteFades[g_Task->timer].offset.green++;
    g_PaletteFades[g_Task->timer].offset.blue++;
    if (++g_Task->unk_09 == 16) {
        D_8014637C->unk_29 = 2;
        g_Task->header.mode++;
    }
}

MATCH void func_801EEEF4(void) {
    g_PaletteFades[g_Task->timer].offset.red--;
    g_PaletteFades[g_Task->timer].offset.green--;
    g_PaletteFades[g_Task->timer].offset.blue--;
    if (--g_Task->unk_09 == 0) {
        GFX_FreePaletteFadeTarget(D_8014637C);
        func_800AF814(g_Battle.active_battler);
        g_Task->unk_09 = 16;
        g_Task->header.mode++;
    }
}

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

MATCH void func_801EF0A4(void) {
    if (g_Task->param.unk_0B == 0xFF) {
        D_8014637C->unk_29 = 4;
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

/* func_801EF114 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF158(void) {
    D_801EFD5C[g_Task->header.step]();
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        if (g_Task->header.step >= 2) {
            g_Task->timer += 1;
        }
        func_801EF4A4();
        func_801EF5B0();
        func_801EF914();
        PopMatrix();
    }
}

MATCH void func_801EF200(void) {
    u8  timer;
    s32 z;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if ((timer & BYTE_MASK) == 0) {
        g_Task->facing = g_BattleEffectBattler->facing;
        g_Task->unk_0C = -0x80000;
        g_Task->unk_10 = -0xF0000;
        func_801DD350(g_Task);
        g_Task->pos.x.fixed = g_AreaScrollTargetX + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_AreaScrollTargetY + g_Task->unk_10;
        z                   = g_BattleEffectBattler->pos.z.fixed + 0x800000;
        g_Task->unk_0C      = 0x8000;
        g_Task->unk_10      = 0;
        g_Task->pos.z.fixed = z;
        func_801DD350(g_Task);
        g_Task->param.unk_0B = 0x1A;
        g_Task->unk_09       = 0x2C;
        g_Task->timer        = 0;
        g_Task->unk_1C       = 0;
        g_Task->unk_20       = 0x80;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF324(void) {
    PartyMember* work;
    u8           count;

    work         = g_Task;
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    if (count == 0) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF388(void) {
    s32 phase;

    g_Task->param.unk_0B = (g_Task->param.unk_0B - 1) & 0x3F;
    phase                = g_Task->unk_1C + 2;
    g_Task->unk_1C       = phase;
    if (phase == 0x80) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF3E0(void) {
    g_Task->param.unk_0B = (g_Task->param.unk_0B - 1) & 0x3F;
    g_Task->unk_1C -= 2;
    g_Task->unk_20 -= 2;
    if (g_Task->unk_1C == 0x20) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF44C(void) {
    g_Task->unk_1C -= 1;
    g_Task->unk_20 -= 2;
    if (g_Task->unk_1C == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 0xFF;
        func_801E5988();
    }
}

MATCH void func_801EF4A4(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    switch (g_Task->facing) {
        case 0:
            rot.vz = 1024;
            break;
        case 1:
            rot.vz = 2048;
            break;
        case 2:
            rot.vz = 3072;
            break;
        default:
            rot.vz = 0;
            break;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

/* Draw the magic132 breath as a strip of 63 textured quads whose height follows a sine wave
 * running with the effect ticker, its texture rows cycling with the timer. */
MATCH void func_801EF5B0(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;

    tpage = getTPage(1, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = g_Task->unk_20;
    D_1F800000.view.effect.params[1] = (g_Task->param.unk_0B & 0x3F) << 7;
    if (g_Task->header.step == 4) {
        D_1F800000.view.effect.params[2] = (g_Task->unk_1C / 2) << 3;
    } else {
        D_1F800000.view.effect.params[2] = 0x80;
    }
    D_1F800014[2].vx = 0;
    D_1F800014[2].vy = 0;
    D_1F800014[2].vz = FIXED_MUL(rsin(D_1F800000.view.effect.params[1]), D_1F800000.view.effect.params[0]);
    for (i = 1; i < 64; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx                 = 0;
        D_1F800014[0].vy                 = D_1F800014[2].vy;
        D_1F800014[0].vz                 = D_1F800014[2].vz;
        D_1F800014[1].vx                 = 0xE00;
        D_1F800014[1].vy                 = D_1F800014[2].vy;
        D_1F800014[1].vz                 = D_1F800014[2].vz;
        D_1F800000.view.effect.params[1] = ((g_Task->param.unk_0B + i) & 0x3F) << 7;
        D_1F800014[2].vx                 = 0;
        D_1F800014[2].vy                 = i << 6;
        D_1F800014[2].vz                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[1]), D_1F800000.view.effect.params[0]);
        D_1F800014[3].vx                 = 0xE00;
        D_1F800014[3].vy                 = D_1F800014[2].vy;
        D_1F800014[3].vz                 = D_1F800014[2].vz;
        setRGB0(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
        prim->tpage                      = GetTPage(1, 1, 832, 256);
        prim->clut                       = GetClut(0, 506);
        D_1F800000.view.effect.params[3] = ((g_Task->timer + i) % 14) * 16 + 8;
        setUV4(prim, 8, D_1F800000.view.effect.params[3], 248, D_1F800000.view.effect.params[3], 8, D_1F800000.view.effect.params[3] + 16, 248, D_1F800000.view.effect.params[3] + 16);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        GFX_AddPrim(2, sizeof(POLY_FT4));
    }
    tpage = getTPage(1, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
}

/* Draw the two magic132 breath bands as shaded quads along the sine wave of the effect ticker,
 * the first tinted red at its far edge and the second at its near edge, dark at the other. */
MATCH void func_801EF914(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;
    s32      phase;

    tpage = getTPage(1, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    if (g_Task->header.step == 4) {
        D_1F800000.view.effect.params[2] = (g_Task->unk_1C / 2) << 3;
    } else {
        D_1F800000.view.effect.params[2] = 0x80;
    }
    D_1F800000.view.effect.params[0] = g_Task->unk_20;
    phase                            = g_Task->param.unk_0B & 0x3F;
    D_1F800014[2].vx                 = 0;
    D_1F800014[2].vy                 = -0x80;
    D_1F800000.view.effect.params[1] = phase << 7;
    D_1F800014[2].vz                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[1]), D_1F800000.view.effect.params[0]);
    for (i = 1; i < 3; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx                 = 0;
        D_1F800014[0].vy                 = D_1F800014[2].vy;
        D_1F800014[0].vz                 = D_1F800014[2].vz;
        D_1F800014[1].vx                 = 0xC00;
        D_1F800014[1].vy                 = D_1F800014[2].vy;
        D_1F800014[1].vz                 = D_1F800014[2].vz;
        D_1F800000.view.effect.params[1] = ((g_Task->param.unk_0B + i) & 0x3F) << 7;
        D_1F800014[2].vx                 = 0;
        D_1F800014[2].vy                 = (i - 1) << 6;
        D_1F800014[2].vz                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[1]), D_1F800000.view.effect.params[0]);
        D_1F800014[3].vx                 = 0xC00;
        D_1F800014[3].vy                 = D_1F800014[2].vy;
        D_1F800014[3].vz                 = D_1F800014[2].vz;
        if (g_Task->header.step == 4) {
            D_1F800000.view.effect.params[2] = (g_Task->unk_1C / 2) * 12;
        } else {
            D_1F800000.view.effect.params[2] = 0xC0;
        }
        if (i == 1) {
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, 1);
            setRGB2(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2] / 4, D_1F800000.view.effect.params[2] / 4);
            setRGB3(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2] / 4, D_1F800000.view.effect.params[2] / 4);
        } else {
            setRGB0(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2] / 4, D_1F800000.view.effect.params[2] / 4);
            setRGB1(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2] / 4, D_1F800000.view.effect.params[2] / 4);
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        GFX_AddPrim(2, sizeof(POLY_G4));
    }
    tpage = getTPage(1, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
}
