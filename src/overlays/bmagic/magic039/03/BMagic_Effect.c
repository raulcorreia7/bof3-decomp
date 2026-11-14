#include "magic039_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC94(void) {
    u8   i;
    u8   slot;
    u16* dst;
    u16* src;

    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    g_Task->unk_04       = func_801EEF3C();
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    slot = Battle_AllocEffect(1, 59);
    {
        PartyMember* work;

        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].unk_04       = g_Task->unk_04 - 2;
    }
    g_Task->param.unk_0B += 1;
    for (i = 0; i < 8; i++) {
        PartyMember* work;

        slot                               = Battle_AllocEffect(1, 59);
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].unk_04       = g_Task->unk_04 - 2;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = D_801F041C[i] + 9;
        g_Task->param.unk_0B += 1;
    }
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/Effect_NextStepOnZeroTick.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH s32 func_801EEF3C(void) {
    u16* id;

    id = (u16*)&g_Battle.action_id;
    switch (*id) {
        case 0x27:
        default:
            return 2;
        case 0xA3:
            return 3;
    }
}

/* func_801EEF64 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFA8(void) {
    BMagicEffectFuncs handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if ((g_Task->header.flags & 0x1) && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFAA4();
        func_801F0054();
        PopMatrix();
    }
}

MATCH void func_801EF070(void) {
    PartyMember* src;

    src                 = (PartyMember*)g_BattleEffectBattler;
    g_Task->pos.x.fixed = src->pos.x.fixed;
    g_Task->pos.y.fixed = src->pos.y.fixed;
    g_Task->pos.z       = src->pos.z;
    g_Task->unk_09      = 0;
    g_Task->timer       = 1;
    g_Task->header.step = g_Task->header.step + 1;
}

MATCH void func_801EF0D4(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 2;
    g_Task->unk_09 = timer;
    if ((timer & BYTE_MASK) == 16) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF134(void) {
    u8            timer_next;
    PartyMember** selected;

    g_Task->unk_09 += 1;
    timer_next    = g_Task->timer + 2;
    g_Task->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 0x18) {
        selected = &g_Battle.selected_actor;
        GFX_FreePaletteFadeTarget(*selected);
        g_Task->param.unk_0B = GFX_AllocPaletteFade(*selected, 0, 0, 0, 1);
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF1F4(void) {
    g_Task->unk_09 += 1;
    g_PaletteFades[g_Task->param.unk_0B].offset.red += 2;
    g_PaletteFades[g_Task->param.unk_0B].offset.green += 2;
    g_PaletteFades[g_Task->param.unk_0B].offset.blue += 2;
    if (g_PaletteFades[g_Task->param.unk_0B].offset.red == 0x10) {
        g_Task->header.step += 1;
    }
}

/* Counts the effect counter up and fades the palette row the effect claimed down to zero, then steps. */
MATCH void func_801EF320(void) {
    g_Task->unk_09 += 1;
    g_PaletteFades[g_Task->param.unk_0B].offset.red -= 2;
    g_PaletteFades[g_Task->param.unk_0B].offset.green -= 2;
    g_PaletteFades[g_Task->param.unk_0B].offset.blue -= 2;
    if (g_PaletteFades[g_Task->param.unk_0B].offset.red == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF44C(void) {
    u8 timer_next;

    g_Task->unk_09 += 1;
    timer_next    = g_Task->timer - 2;
    g_Task->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF4E4(void) {
    Magic039Steps handlers;

    handlers = D_801EEC28;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (ACTOR_IN_USE(*g_Task) && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801EF758();
    }
}

INCLUDE_ASM(func_801EF584);

MATCH void func_801EF690(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 16;
    g_Task->unk_09 = timer;
    if (timer == 128) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(8);
}

/* Draw the effect as a shaded box above its screen point, white at the top edge and tinted
 * at the bottom by the colour row the effect picks. */
MATCH void func_801EF758(void) {
    POLY_G4* prim;
    s32      tpage;

    D_1F800000.view.effect.params[3] = g_Task->unk_09;
    D_1F800000.view.effect.params[4] = g_Task->timer;
    D_1F800000.view.effect.params[5] = g_Task->unk_2E.half;
    D_1F800000.view.effect.params[6] = g_Task->unk_30.half;
    D_1F800000.view.effect.params[0] = D_801F040C[g_Task->unk_04][0];
    D_1F800000.view.effect.params[1] = D_801F040C[g_Task->unk_04][1];
    D_1F800000.view.effect.params[2] = D_801F040C[g_Task->unk_04][2];
    tpage                            = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(DR_MODE));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, D_1F800000.view.effect.params[5] - D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[6] - D_1F800000.view.effect.params[3],
           D_1F800000.view.effect.params[5] + D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[6] - D_1F800000.view.effect.params[3],
           D_1F800000.view.effect.params[5] - D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[5] + D_1F800000.view.effect.params[4],
           D_1F800000.view.effect.params[6]);
    setRGB0(prim, 1, 1, 1);
    setRGB1(prim, 1, 1, 1);
    setRGB2(prim, D_1F800000.view.effect.params[0], D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[2]);
    setRGB3(prim, D_1F800000.view.effect.params[0], D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[2]);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(POLY_G4));
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* Draw the magic039 flame as 64 shaded quads round the effect, each with a random wobble in its
 * height and outer radius, dark at the base and tinted at the top by the colour row it picks. */
MATCH void func_801EFAA4(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      x;
    s32      y;
    s32      tpage;
    s32      wobble;

    D_1F800000.view.effect.params[4] = g_Task->timer;
    D_1F800000.view.effect.params[5] = (((rand() & 3) + g_Task->unk_09) & 0xF) * 256;
    D_1F800000.view.effect.params[3] = FIXED_MUL(rsin(D_1F800000.view.effect.params[5]) << 1, D_1F800000.view.effect.params[4]) - D_1F800000.view.effect.params[4] * 6;
    D_1F800000.view.effect.params[6] = 0x80;
    wobble                           = FIXED_MUL(rsin(D_1F800000.view.effect.params[5]) << 2, D_1F800000.view.effect.params[4]) - 0x80;
    D_1F800000.view.effect.params[7] = D_1F800000.view.effect.params[4] * 8 - wobble;
    if (g_Task->unk_09 < 16) {
        D_1F800000.view.effect.params[0] = D_801F0414[g_Task->unk_04][0] * g_Task->unk_09;
        D_1F800000.view.effect.params[1] = D_801F0414[g_Task->unk_04][1] * g_Task->unk_09;
        D_1F800000.view.effect.params[2] = D_801F0414[g_Task->unk_04][2] * g_Task->unk_09;
    } else {
        D_1F800000.view.effect.params[0] = D_801F0414[g_Task->unk_04][0] * 16;
        D_1F800000.view.effect.params[1] = D_801F0414[g_Task->unk_04][1] * 16;
        D_1F800000.view.effect.params[2] = D_801F0414[g_Task->unk_04][2] * 16;
    }
    D_1F800014[1].vx = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[7]);
    D_1F800014[1].vy = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[7]);
    D_1F800014[1].vz = D_1F800000.view.effect.params[3];
    D_1F800014[3].vx = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[6]);
    D_1F800014[3].vy = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[6]);
    D_1F800014[2].vz = 0;
    D_1F800014[3].vz = 0;
    for (i = 1; i <= 64; i++) {
        D_1F800000.view.effect.params[5] = (((rand() & 3) + i + g_Task->unk_09) & 0xF) * 256;
        D_1F800000.view.effect.params[3] = FIXED_MUL(rsin(D_1F800000.view.effect.params[5]) << 1, D_1F800000.view.effect.params[4]) - D_1F800000.view.effect.params[4] * 6;
        wobble                           = FIXED_MUL(rsin(D_1F800000.view.effect.params[5]) << 2, D_1F800000.view.effect.params[4]) - 0x80;
        D_1F800000.view.effect.params[7] = D_1F800000.view.effect.params[4] * 8 - wobble;
        D_1F800014[0].vx                 = D_1F800014[1].vx;
        D_1F800014[0].vy                 = D_1F800014[1].vy;
        D_1F800014[0].vz                 = D_1F800014[1].vz;
        D_1F800014[1].vx                 = FIXED_MUL(rcos(i << 6), D_1F800000.view.effect.params[7]);
        D_1F800014[1].vy                 = FIXED_MUL(rsin(i << 6), D_1F800000.view.effect.params[7]);
        D_1F800014[1].vz                 = D_1F800000.view.effect.params[3];
        D_1F800014[2].vx                 = D_1F800014[3].vx;
        D_1F800014[2].vy                 = D_1F800014[3].vy;
        D_1F800014[3].vx                 = FIXED_MUL(rcos(i << 6), D_1F800000.view.effect.params[6]);
        D_1F800014[3].vy                 = FIXED_MUL(rsin(i << 6), D_1F800000.view.effect.params[6]);
        x                                = (D_1F800014[3].vx << 9) + g_Task->pos.x.fixed;
        y                                = (D_1F800014[3].vx << 9) + g_Task->pos.y.fixed;
        tpage                            = getTPage(0, 1, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, D_1F800000.view.effect.params[0], D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[2]);
        setRGB3(prim, D_1F800000.view.effect.params[0], D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[2]);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        Area_AddCellPrim(x, y, 0, sizeof(POLY_G4));
    }
}

/* Draw the magic039 disc as a fan of sixteen shaded triangles, white at the centre and tinted at
 * the rim by the colour row the effect picks, the tint growing with the effect size up to 16. */
MATCH void func_801F0054(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[3] = 0x88;
    if (g_Task->unk_09 < 16) {
        D_1F800000.view.effect.params[0] = D_801F0404[g_Task->unk_04][0] * g_Task->unk_09;
        D_1F800000.view.effect.params[1] = D_801F0404[g_Task->unk_04][1] * g_Task->unk_09;
        D_1F800000.view.effect.params[2] = D_801F0404[g_Task->unk_04][2] * g_Task->unk_09;
    } else {
        D_1F800000.view.effect.params[0] = D_801F0404[g_Task->unk_04][0] * 16;
        D_1F800000.view.effect.params[1] = D_801F0404[g_Task->unk_04][1] * 16;
        D_1F800000.view.effect.params[2] = D_801F0404[g_Task->unk_04][2] * 16;
    }
    D_1F800014[2].vx = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[3]);
    D_1F800014[2].vy = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[3]);
    D_1F800014[2].vz = 0;
    D_1F800014[1].vz = 0;
    D_1F800014[0].vz = 0;
    for (i = 1; i <= 16; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[3]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[3]);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, D_1F800000.view.effect.params[0], D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[2]);
        setRGB2(prim, D_1F800000.view.effect.params[0], D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[2]);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
    tpage = getTPage(0, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}
