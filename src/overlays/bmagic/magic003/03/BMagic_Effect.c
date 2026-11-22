#include "magic003_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC28(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    SYS_DISPATCH_BYTE(D_801F0AD8, TASK(PartyMember)->header.mode);

    BMAGIC_RUN_EFFECT_SLOTS(BMAGIC_EFFECT_SLOTS, BMagic_DispatchEffectMode);
}

MATCH void func_801EED14(void) {
    u32 i;
    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    TASK(PartyMember)->screen_x.value = 160;
    TASK(PartyMember)->screen_y.value = 112;
    TASK(PartyMember)->param.unk_0B   = 0;
    TASK(PartyMember)->unk_09         = 30;
    TASK(PartyMember)->timer          = 0;
    TASK(PartyMember)->header.mode += 1;
}

MATCH void func_801EEDAC(void) {
    u8 timer;

    func_801F07B0(1);
    func_801F0164(1);
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        TASK(PartyMember)->unk_09 = 0x1E;
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EEE28(void) {
    u8 timer;

    func_801F07B0(2);
    func_801F0164(2);
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        TASK(PartyMember)->unk_09 = 0xA;
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EEEA4(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count == 0) {
        TASK(PartyMember)->param.unk_0B = RANDOM_MASK(3);
        if (TASK(PartyMember)->timer < 16) {
            TASK(PartyMember)->unk_09 = D_801F0A84[TASK(PartyMember)->timer];
        } else {
            TASK(PartyMember)->unk_09 = 3;
        }
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EEF4C(void) {
    u8 count;
    u8 timer;

    func_801F07B0(4);
    func_801F03F0(TASK(PartyMember)->param.unk_0B);
    if (g_PadStates[0].pressed & (PADRup | PADRdown | PADRleft | PADRright)) {
        if (g_PadStates[0].pressed != D_801F0A98[TASK(PartyMember)->param.unk_0B]) {
            TASK(PartyMember)->unk_09      = 6;
            TASK(PartyMember)->header.mode = 5;
        } else {
            TASK(PartyMember)->unk_09 = 6;
            count                     = TASK(PartyMember)->timer + 1;
            TASK(PartyMember)->timer  = count;
            if (count < 32) {
                TASK(PartyMember)->header.mode = 3;
            } else {
                TASK(PartyMember)->header.mode = 5;
            }
        }
    } else {
        timer                     = TASK(PartyMember)->unk_09 - 1;
        TASK(PartyMember)->unk_09 = timer;
        if (timer == 0) {
            TASK(PartyMember)->unk_09      = 6;
            TASK(PartyMember)->header.mode = 5;
        }
    }
}

MATCH void func_801EF04C(void) {
    u8 timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        TASK(PartyMember)->unk_09      = 0x1E;
        TASK(PartyMember)->header.mode = TASK(PartyMember)->header.mode + 1;
    }
}

MATCH void func_801EF0A8(void) {
    u8 timer;

    func_801F07B0(0);
    func_801F0550(TASK(PartyMember)->timer);
    func_801F0164(0);
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EF12C(void) {
    TASK(PartyMember)->facing       = g_BattleEffectBattler->facing;
    TASK(PartyMember)->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    func_801EFD4C();
    func_801EFEC8();
    TASK(PartyMember)->unk_04 = TASK(PartyMember)->param.unk_0B;
    g_BattleEffectBattler->header.flags |= ACTOR_FLAG_HIDDEN;
    SND_SEQueueSelection(0x100);
}

MATCH void func_801EF1FC(void) {
    if (TASK(PartyMember)->param.unk_0B == 0) {
        D_8014637C->header.flags &= 0xBF;
        Battle_SelectActiveBattlerScript(4, 0);
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EF268(void) {
    SND_SEQueueSelection(258);
    g_Battle.unk_EF[7] = TASK(PartyMember)->timer;
    Battle_MarkDamaged(g_BattleTargetSelector);
    g_BattleState = g_Battle.flags | BATTLE_STATE_EFFECT_PLAYING;
    Effect_Reset();
}

MATCH void func_801EF2CC(void) {
    Callback handlers[2] = {func_801EF324, func_801EF708};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EF324(void) {
    Magic003Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.step != 0 && TASK(PartyMember)->header.flags != 0) {
        Area_SetDrawMode();
    }
}

MATCH void func_801EF3C8(void) {
    s32 x;
    s32 y;
    u32 z;
    u8  timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        x                          = TASK(PartyMember)->pos.x.fixed;
        y                          = TASK(PartyMember)->pos.y.fixed;
        z                          = TASK(PartyMember)->pos.z.fixed;
        TASK(PartyMember)->unk_0C  = 0x2000;
        TASK(PartyMember)->unk_14  = 0x300000;
        TASK(PartyMember)->unk_10  = 0;
        TASK(PartyMember)->unk_20  = -0x80000;
        TASK(PartyMember)->unk_18  = x;
        TASK(PartyMember)->unk_1C  = y;
        TASK(PartyMember)->scale.y = z;
        Effect_RotatePosition(g_Task);
        TASK(PartyMember)->unk_09 = func_800AFF98();
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF478(void) {
    s32 value;
    u8  value2;

    value2 = TASK(PartyMember)->unk_09;
    value  = value2 & BYTE_MASK;
    if (value != 0) {
        if (value != 0xFF) {
            TASK(PartyMember)->unk_09 = value2 - 1;
        }
    } else {
        SND_SEQueueSelection(0x101);
        Battle_PlayActiveBattlerSE(2, 0);
        func_801F0078();
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        TASK(PartyMember)->unk_09 = 0xFF;
    }
    TASK(PartyMember)->pos.x.fixed += TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed += TASK(PartyMember)->unk_10;
    TASK(PartyMember)->pos.z.fixed += TASK(PartyMember)->unk_14;
    TASK(PartyMember)->unk_14 += TASK(PartyMember)->unk_20;
    Script_AnimStepOnce();
    if (TASK(PartyMember)->pos.z.fixed == TASK(PartyMember)->scale.y) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF578(void) {
    s32 value;
    u8  value2;

    value2 = TASK(PartyMember)->unk_09;
    value  = value2 & BYTE_MASK;
    if (value != 0) {
        if (value != 0xFF) {
            TASK(PartyMember)->unk_09 = value2 - 1;
        }
    } else {
        SND_SEQueueSelection(0x101);
        Battle_PlayActiveBattlerSE(2, 0);
        func_801F0078();
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        TASK(PartyMember)->unk_09 = 0xFF;
    }
    Script_AnimStepOnce();
    if (TASK(PartyMember)->unk_09 == 0xFF) {
        TASK(PartyMember)->unk_0C = -0x2000;
        TASK(PartyMember)->unk_10 = 0;
        Effect_RotatePosition(g_Task);
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF644(void) {
    TASK(PartyMember)->pos.x.fixed += TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed += TASK(PartyMember)->unk_10;
    Script_AnimStepOnce();
    if (TASK(PartyMember)->pos.x.fixed == TASK(PartyMember)->unk_18 && TASK(PartyMember)->pos.y.fixed == TASK(PartyMember)->unk_1C) {
        TASK(PartyMember)->header.step++;
    }
}

MATCH void func_801EF6CC(void) {
    PartyMember* work;
    u8           step;

    work = BATTLE_ACTIVE_WORK;
    step = work->param.unk_0B;
    if (step < 2) {
        work->param.unk_0B = step - 1;
        Effect_Reset();
    }
}

MATCH void func_801EF708(void) {
    Magic003SecondSteps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.step != 0 && TASK(PartyMember)->header.flags != 0) {
        Area_SetDrawMode();
    }
}

MATCH void func_801EF7A8(void) {
    s32 x;
    s32 y;
    u32 z;
    u8  timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        x                          = TASK(PartyMember)->pos.x.fixed;
        y                          = TASK(PartyMember)->pos.y.fixed;
        z                          = TASK(PartyMember)->pos.z.fixed;
        TASK(PartyMember)->unk_0C  = 0x2000;
        TASK(PartyMember)->unk_14  = 0x300000;
        TASK(PartyMember)->unk_10  = 0;
        TASK(PartyMember)->unk_20  = -0x80000;
        TASK(PartyMember)->unk_18  = x;
        TASK(PartyMember)->unk_1C  = y;
        TASK(PartyMember)->scale.y = z;
        Effect_RotatePosition(g_Task);
        TASK(PartyMember)->header.flags |= 0x20;
        TASK(PartyMember)->unk_5C = 3;
        TASK(PartyMember)->unk_5D = -(TASK(PartyMember)->param.unk_0B << 4);
        TASK(PartyMember)->unk_5F = -(TASK(PartyMember)->param.unk_0B << 4);
        TASK(PartyMember)->unk_5E = -(TASK(PartyMember)->param.unk_0B << 4);
        GFX_PaletteAllocFade(g_Task, D_801F0A78[TASK(PartyMember)->param.unk_0B].r, D_801F0A78[TASK(PartyMember)->param.unk_0B].g, D_801F0A78[TASK(PartyMember)->param.unk_0B].b, 1);
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF918(void) {
    TASK(PartyMember)->pos.x.fixed += TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed += TASK(PartyMember)->unk_10;
    TASK(PartyMember)->pos.z.fixed += TASK(PartyMember)->unk_14;
    TASK(PartyMember)->unk_14 += TASK(PartyMember)->unk_20;
    Script_AnimStepOnce();
    if (TASK(PartyMember)->pos.z.fixed == TASK(PartyMember)->scale.y) {
        TASK(PartyMember)->header.step++;
    }
}

MATCH void func_801EF9AC(void) {
    TASK(PartyMember)->unk_0C = -0x2000;
    TASK(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    Script_AnimStepOnce();
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF9FC(void) {
    TASK(PartyMember)->pos.x.fixed += TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed += TASK(PartyMember)->unk_10;
    Script_AnimStepOnce();
    if ((TASK(PartyMember)->pos.x.fixed == TASK(PartyMember)->unk_18) && (TASK(PartyMember)->pos.y.fixed == TASK(PartyMember)->unk_1C)) {
        GFX_PaletteFreeFadeTarget(g_Task);
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

/* func_801EFA9C */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

#include "overlays/bmagic/shared/BMagic_RunEffectStep.h"

MATCH void func_801EFAE0(void) {
    BMAGIC_RUN_EFFECT_STEP(func_801EFB8C, func_801EFCF8);
}

MATCH void func_801EFB8C(void) {
    PartyMember* actor;
    PartyMember* work;
    u8           timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        actor                          = g_BattleSelectedActor;
        TASK(PartyMember)->facing      = actor->facing;
        TASK(PartyMember)->pos.x.fixed = actor->pos.x.fixed;
        TASK(PartyMember)->pos.y.fixed = actor->pos.y.fixed;
        TASK(PartyMember)->pos.z.fixed = actor->pos.z.fixed;
        Battle_ProjectRange();
        TASK(PartyMember)->unk_29 = 0;
        TASK(PartyMember)->unk_25 = 0x1D;
        TASK(PartyMember)->unk_26 = 0;
        TASK(PartyMember)->unk_24 = 0x84;
        work                      = TASK(PartyMember);
        work->unk_2B              = 0;
        work->unk_2C.value        = 0;
        TASK(PartyMember)->unk_28 = 0;
        TASK(PartyMember)->unk_27 = D_801F0B04[TASK(PartyMember)->param.unk_0B] + 0xB0;
        if (TASK(PartyMember)->unk_04 & 1) {
            TASK(PartyMember)->unk_2A = 1;
        } else {
            TASK(PartyMember)->unk_2A = 0;
        }
        Script_Select(TASK(PartyMember)->param.unk_0B);
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFCF8(void) {
    PartyMember* work;

    Script_AnimStepOnce();
    if (Script_AnimStepOnce() != 0u) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/shared/Effect_CopyActiveBattlerToSlot.h"

MATCH void func_801EFD4C(void) {
    BattleEffect* image;
    u32           slot;

    slot = Battle_AllocEffect(1, 1);
    Effect_CopyActiveBattlerToSlot(slot);
    D_801EC3A4[slot & BYTE_MASK].target.party = TASK(PartyMember);
    image                                     = &g_BattleEffects[slot & BYTE_MASK];
    image->unk_06                             = 1;
    image->step_index                         = 1;
    image->header.mode                        = 0;
    image->header.step                        = 0;
    image->arg.unk_09                         = 1;
    TASK(PartyMember)->param.unk_0B += 1;
}

MATCH void func_801EFEC8(void) {
    BattleEffect* image;
    u32           slot;
    u8            i;

    for (i = 0; i < 4; i++) {
        slot = Battle_AllocEffect(1, 1);
        Effect_CopyActiveBattlerToSlot(slot);
        D_801EC3A4[slot & BYTE_MASK].target.party = TASK(PartyMember);
        image                                     = &g_BattleEffects[slot & BYTE_MASK];
        image->unk_06                             = 1;
        image->step_index                         = 1;
        image->header.mode                        = 1;
        image->header.step                        = 0;
        image->unk_0B                             = i;
        image->arg.unk_09                         = (i + 1) * 4 + 1;
        TASK(PartyMember)->param.unk_0B += 1;
    }
}

MATCH void func_801F0078(void) {
    PartyMember* battler;
    u8           i;
    u8           slot;

    for (i = 0; i < g_BattleEffectBattler->timer; i++) {
        slot                                   = BMagic_AllocEffect();
        battler                                = g_BattleEffectBattler;
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[slot].header.step  = 0;
        BMAGIC_EFFECT_SLOTS[slot].unk_04       = i;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = (i / 2) & 0x7;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = (i * 4) + 1;
        BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
        g_BattleEffectBattler->param.unk_0B += 1;
    }
}

MATCH void func_801F0164(s32 index) {
    POLY_FT4* prim;
    s32       tpage;
    u16       x;
    u16       y;
    u8        i;
    u8        glyph;
    u8        length;
    s32       u;
    s32       v;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    length = D_801F0A9C[(u8)index];
    x      = TASK(PartyMember)->screen_x.value - ((length >> 1) * 12 + (length & 1) * 6);
    y      = TASK(PartyMember)->screen_y.value;
    for (i = 0; D_801F0AA0[(u8)index][i] != 0; i++) {
        glyph = D_801F0AA0[(u8)index][i] - 0x3F;
        if (D_801F0AA0[(u8)index][i] != 0xFF) {
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            setXYWH(prim, x, y, 12, 12);
            prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
            prim->clut  = GetClut(0, 0x1E0);
            setRGB0(prim, 0x80, 0x80, 0x80);
            u = (glyph % 21) * 12;
            v = (glyph / 21) * 12;
            setUV4(prim, u, v + 36, u + 12, v + 36, u, v + 48, u + 12, v + 48);
            GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_FT4));
        } else {
            x -= 6;
        }
        x += 12;
    }
}

MATCH void func_801F03F0(s32 dir) {
    POLY_FT4* prim;
    s32       tpage;
    u16       x;
    u16       y;
    s32       u;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    prim = (POLY_FT4*)g_GfxPrimCursor;
    x    = TASK(PartyMember)->screen_x.value;
    y    = TASK(PartyMember)->screen_y.value;
    SetPolyFT4(prim);
    setXYWH(prim, x, y, 12, 12);
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    prim->clut  = GetClut(D_801F0AD4[(u8)dir], 0x1E0);
    u           = ((u8)dir + 15) * 12;
    setUV4(prim, u, 0x30, u + 12, 0x30, u, 0x3C, u + 12, 0x3C);
    setRGB0(prim, 0x80, 0x80, 0x80);
    GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_FT4));
}

MATCH void func_801F0550(s32 value) {
    POLY_FT4* prim;
    s32       tpage;
    u16       x;
    u16       y;
    u8        ones;
    u8        tens;
    s32       u;
    u16       left;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    tens = (u8)value / 10;
    ones = (u8)value % 10;
    prim = (POLY_FT4*)g_GfxPrimCursor;
    x    = TASK(PartyMember)->screen_x.value;
    y    = TASK(PartyMember)->screen_y.value;
    left = x - 66;
    SetPolyFT4(prim);
    setXY4(prim, left, y, x - 54, y, left, y + 12, x - 54, y + 12);
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    prim->clut  = GetClut(0, 0x1E0);
    u           = ones * 12;
    setUV4(prim, u + 72, 24, u + 84, 24, u + 72, 36, u + 84, 36);
    setRGB0(prim, 0x80, 0x80, 0x80);
    GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_FT4));
    left = x - 78;
    if (tens != 0) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        setXY4(prim, left, y, x - 66, y, left, y + 12, x - 66, y + 12);
        prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
        prim->clut  = GetClut(0, 0x1E0);
        u           = tens * 12;
        setUV4(prim, u + 72, 24, u + 84, 24, u + 72, 36, u + 84, 36);
        setRGB0(prim, 0x80, 0x80, 0x80);
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_FT4));
    }
}

MATCH void func_801F07B0(s32 index) {
    TILE* tile;
    s32   tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    setXY0(tile, TASK(PartyMember)->screen_x.value - (D_801F0B10[(u8)index].box.x + 4), TASK(PartyMember)->screen_y.value - (D_801F0B10[(u8)index].box.y + 4));
    setWH(tile, D_801F0B10[(u8)index].box.w + 8, D_801F0B10[(u8)index].box.h + 8);
    setRGB0(tile, 0x20, 0x20, 0x20);
    GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(TILE));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    setXY0(tile, TASK(PartyMember)->screen_x.value - (D_801F0B10[(u8)index].box.x + 6), TASK(PartyMember)->screen_y.value - (D_801F0B10[(u8)index].box.y + 6));
    setWH(tile, D_801F0B10[(u8)index].box.w + 12, D_801F0B10[(u8)index].box.h + 12);
    setRGB0(tile, 0x20, 0x20, 0x20);
    GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(TILE));
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
}

/* func_801F09C4 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801F0A28 */
#include "overlays/bmagic/shared/Actor_Clear.h"
