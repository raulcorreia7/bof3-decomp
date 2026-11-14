#include "magic003_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC28(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    SYS_DISPATCH_BYTE(D_801F0AD8, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].target.party;
            BMagic_DispatchEffectMode();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED14);

MATCH void func_801EEDAC(void) {
    u8 timer;

    func_801F07B0(1);
    func_801F0164(1);
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->unk_09 = 0x1E;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEE28(void) {
    u8 timer;

    func_801F07B0(2);
    func_801F0164(2);
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->unk_09 = 0xA;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEEA4(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        g_Task->param.unk_0B = RANDOM_MASK(3);
        if (g_Task->timer < 16) {
            g_Task->unk_09 = D_801F0A84[g_Task->timer];
        } else {
            g_Task->unk_09 = 3;
        }
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEF4C(void) {
    u8 count;
    u8 timer;

    func_801F07B0(4);
    func_801F03F0(g_Task->param.unk_0B);
    if (g_InputPressed & (PADRup | PADRdown | PADRleft | PADRright)) {
        if (g_InputPressed != D_801F0A98[g_Task->param.unk_0B]) {
            g_Task->unk_09      = 6;
            g_Task->header.mode = 5;
        } else {
            g_Task->unk_09 = 6;
            count          = g_Task->timer + 1;
            g_Task->timer  = count;
            if (count < 32) {
                g_Task->header.mode = 3;
            } else {
                g_Task->header.mode = 5;
            }
        }
    } else {
        timer          = g_Task->unk_09 - 1;
        g_Task->unk_09 = timer;
        if (timer == 0) {
            g_Task->unk_09      = 6;
            g_Task->header.mode = 5;
        }
    }
}

MATCH void func_801EF04C(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_09      = 0x1E;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EF0A8(void) {
    u8 timer;

    func_801F07B0(0);
    func_801F0550(g_Task->timer);
    func_801F0164(0);
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF12C(void) {
    g_Task->facing       = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    func_800AEF98(0xC, 2);
    func_801EFD4C();
    func_801EFEC8();
    g_Task->unk_04 = g_Task->param.unk_0B;
    g_BattleEffectBattler->header.flags |= ACTOR_FLAG_HIDDEN;
    SND_QueueSelectionEffect(0x100);
}

MATCH void func_801EF1FC(void) {
    if (g_Task->param.unk_0B == 0) {
        *D_8014637C &= 0xBF;
        func_800AEF98(4, 0);
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF268(void) {
    SND_QueueSelectionEffect(258);
    D_801463D6 = g_Task->timer;
    Battle_MarkDamaged(g_BattleTargetSelector);
    g_BattleState = g_Battle.state | BATTLE_STATE_EFFECT_PLAYING;
    func_801E5988();
}

MATCH void func_801EF2CC(void) {
    Callback handlers[2] = {func_801EF324, func_801EF708};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EF324(void) {
    Magic003Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Area_SetDrawMode();
    }
}

MATCH void func_801EF3C8(void) {
    s32 x;
    s32 y;
    u32 z;
    u8  timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        x               = g_Task->pos.x.fixed;
        y               = g_Task->pos.y.fixed;
        z               = g_Task->pos.z.fixed;
        g_Task->unk_0C  = 0x2000;
        g_Task->unk_14  = 0x300000;
        g_Task->unk_10  = 0;
        g_Task->unk_20  = -0x80000;
        g_Task->unk_18  = x;
        g_Task->unk_1C  = y;
        g_Task->scale.y = z;
        func_801DD350(g_Task);
        g_Task->unk_09 = func_800AFF98();
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF478(void) {
    s32 value;
    u8  value2;

    value2 = g_Task->unk_09;
    value  = value2 & BYTE_MASK;
    if (value != 0) {
        if (value != 0xFF) {
            g_Task->unk_09 = value2 - 1;
        }
    } else {
        SND_QueueSelectionEffect(0x101);
        func_800AFC98(2, 0);
        func_801F0078();
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        g_Task->unk_09 = 0xFF;
    }
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    g_Task->pos.z.fixed += g_Task->unk_14;
    g_Task->unk_14 += g_Task->unk_20;
    Actor_StepAnimOnce();
    if (g_Task->pos.z.fixed == g_Task->scale.y) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF578(void) {
    s32 value;
    u8  value2;

    value2 = g_Task->unk_09;
    value  = value2 & BYTE_MASK;
    if (value != 0) {
        if (value != 0xFF) {
            g_Task->unk_09 = value2 - 1;
        }
    } else {
        SND_QueueSelectionEffect(0x101);
        func_800AFC98(2, 0);
        func_801F0078();
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        g_Task->unk_09 = 0xFF;
    }
    Actor_StepAnimOnce();
    if (g_Task->unk_09 == 0xFF) {
        g_Task->unk_0C = -0x2000;
        g_Task->unk_10 = 0;
        func_801DD350(g_Task);
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF644(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    Actor_StepAnimOnce();
    if (g_Task->pos.x.fixed == g_Task->unk_18 && g_Task->pos.y.fixed == g_Task->unk_1C) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF6CC(void) {
    PartyMember* work;
    u8           step;

    work = BATTLE_ACTIVE_WORK;
    step = work->param.unk_0B;
    if (step < 2) {
        work->param.unk_0B = step - 1;
        func_801E5988();
    }
}

MATCH void func_801EF708(void) {
    Magic003SecondSteps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Area_SetDrawMode();
    }
}

MATCH void func_801EF7A8(void) {
    s32 x;
    s32 y;
    u32 z;
    u8  timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        x               = g_Task->pos.x.fixed;
        y               = g_Task->pos.y.fixed;
        z               = g_Task->pos.z.fixed;
        g_Task->unk_0C  = 0x2000;
        g_Task->unk_14  = 0x300000;
        g_Task->unk_10  = 0;
        g_Task->unk_20  = -0x80000;
        g_Task->unk_18  = x;
        g_Task->unk_1C  = y;
        g_Task->scale.y = z;
        func_801DD350(g_Task);
        g_Task->header.flags |= 0x20;
        g_Task->unk_5C = 3;
        g_Task->unk_5D = -(g_Task->param.unk_0B << 4);
        g_Task->unk_5F = -(g_Task->param.unk_0B << 4);
        g_Task->unk_5E = -(g_Task->param.unk_0B << 4);
        GFX_AllocPaletteFade(g_Task, D_801F0A78[g_Task->param.unk_0B].red, D_801F0A78[g_Task->param.unk_0B].green, D_801F0A78[g_Task->param.unk_0B].blue, 1);
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF918(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    g_Task->pos.z.fixed += g_Task->unk_14;
    g_Task->unk_14 += g_Task->unk_20;
    Actor_StepAnimOnce();
    if (g_Task->pos.z.fixed == g_Task->scale.y) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF9AC(void) {
    g_Task->unk_0C = -0x2000;
    g_Task->unk_10 = 0;
    func_801DD350(g_Task);
    Actor_StepAnimOnce();
    g_Task->header.step += 1;
}

MATCH void func_801EF9FC(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    Actor_StepAnimOnce();
    if ((g_Task->pos.x.fixed == g_Task->unk_18) && (g_Task->pos.y.fixed == g_Task->unk_1C)) {
        GFX_FreePaletteFadeTarget(g_Task);
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

/* func_801EFA9C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

#include "overlays/bmagic/BMagic_RunEffectStep.h"

MATCH void func_801EFAE0(void) {
    BMAGIC_RUN_EFFECT_STEP(func_801EFB8C, func_801EFCF8);
}

MATCH void func_801EFB8C(void) {
    PartyMember* actor;
    PartyMember* work;
    u8           timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        actor               = g_BattleSelectedActor;
        g_Task->facing      = actor->facing;
        g_Task->pos.x.fixed = actor->pos.x.fixed;
        g_Task->pos.y.fixed = actor->pos.y.fixed;
        g_Task->pos.z.fixed = actor->pos.z.fixed;
        Battle_ProjectRange();
        g_Task->unk_29    = 0;
        g_Task->unk_25    = 0x1D;
        g_Task->unk_26    = 0;
        g_Task->unk_24    = 0x84;
        work              = g_Task;
        work->unk_2B      = 0;
        work->unk_2C.half = 0;
        g_Task->unk_28    = 0;
        g_Task->unk_27    = D_801F0B04[g_Task->param.unk_0B] + 0xB0;
        if (g_Task->unk_04 & 1) {
            g_Task->unk_2A = 1;
        } else {
            g_Task->unk_2A = 0;
        }
        Actor_SelectScript(g_Task->param.unk_0B);
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFCF8(void) {
    PartyMember* work;

    Actor_StepAnimOnce();
    if (Actor_StepAnimOnce() != 0u) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_CopyActiveBattlerToSlot.h"

MATCH void func_801EFD4C(void) {
    BattleEffect* image;
    u32           slot;

    slot = Battle_AllocEffect(1, 1);
    Effect_CopyActiveBattlerToSlot(slot);
    D_801EC3A4[slot & BYTE_MASK].target.party = g_Task;
    image                                     = &g_BattleEffects[slot & BYTE_MASK];
    image->unk_06                             = 1;
    image->handler_index                      = 1;
    image->header.mode                        = 0;
    image->header.step                        = 0;
    image->arg.unk_09                         = 1;
    g_Task->param.unk_0B += 1;
}

MATCH void func_801EFEC8(void) {
    BattleEffect* image;
    u32           slot;
    u8            i;

    for (i = 0; i < 4; i++) {
        slot = Battle_AllocEffect(1, 1);
        Effect_CopyActiveBattlerToSlot(slot);
        D_801EC3A4[slot & BYTE_MASK].target.party = g_Task;
        image                                     = &g_BattleEffects[slot & BYTE_MASK];
        image->unk_06                             = 1;
        image->handler_index                      = 1;
        image->header.mode                        = 1;
        image->header.step                        = 0;
        image->unk_0B                             = i;
        image->arg.unk_09                         = (i + 1) * 4 + 1;
        g_Task->param.unk_0B += 1;
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

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    length = D_801F0A9C[(u8)index];
    x      = g_Task->unk_2E.half - ((length >> 1) * 12 + (length & 1) * 6);
    y      = g_Task->unk_30.half;
    for (i = 0; D_801F0AA0[(u8)index][i] != 0; i++) {
        glyph = D_801F0AA0[(u8)index][i] - 0x3F;
        if (D_801F0AA0[(u8)index][i] != 0xFF) {
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            setXY4(prim, x, y, x + 12, y, x, y + 12, x + 12, y + 12);
            prim->tpage = GetTPage(0, 0, 0x3C0, 0);
            prim->clut  = GetClut(0, 0x1E0);
            setRGB0(prim, 0x80, 0x80, 0x80);
            u = (glyph % 21) * 12;
            v = (glyph / 21) * 12;
            setUV4(prim, u, v + 36, u + 12, v + 36, u, v + 48, u + 12, v + 48);
            GFX_AddPrim(2, sizeof(POLY_FT4));
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

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    x    = g_Task->unk_2E.half;
    y    = g_Task->unk_30.half;
    SetPolyFT4(prim);
    setXY4(prim, x, y, x + 12, y, x, y + 12, x + 12, y + 12);
    prim->tpage = GetTPage(0, 0, 0x3C0, 0);
    prim->clut  = GetClut(D_801F0AD4[(u8)dir], 0x1E0);
    u           = ((u8)dir + 15) * 12;
    setUV4(prim, u, 0x30, u + 12, 0x30, u, 0x3C, u + 12, 0x3C);
    setRGB0(prim, 0x80, 0x80, 0x80);
    GFX_AddPrim(2, sizeof(POLY_FT4));
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

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    tens = (u8)value / 10;
    ones = (u8)value % 10;
    prim = (POLY_FT4*)g_GfxPrimCursor;
    x    = g_Task->unk_2E.half;
    y    = g_Task->unk_30.half;
    left = x - 66;
    SetPolyFT4(prim);
    setXY4(prim, left, y, x - 54, y, left, y + 12, x - 54, y + 12);
    prim->tpage = GetTPage(0, 0, 0x3C0, 0);
    prim->clut  = GetClut(0, 0x1E0);
    u           = ones * 12;
    setUV4(prim, u + 72, 24, u + 84, 24, u + 72, 36, u + 84, 36);
    setRGB0(prim, 0x80, 0x80, 0x80);
    GFX_AddPrim(2, sizeof(POLY_FT4));
    left = x - 78;
    if (tens != 0) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        setXY4(prim, left, y, x - 66, y, left, y + 12, x - 66, y + 12);
        prim->tpage = GetTPage(0, 0, 0x3C0, 0);
        prim->clut  = GetClut(0, 0x1E0);
        u           = tens * 12;
        setUV4(prim, u + 72, 24, u + 84, 24, u + 72, 36, u + 84, 36);
        setRGB0(prim, 0x80, 0x80, 0x80);
        GFX_AddPrim(2, sizeof(POLY_FT4));
    }
}

MATCH void func_801F07B0(s32 index) {
    TILE* tile;
    s32   tpage;

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x125 : 0x55;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    tile->x0 = g_Task->unk_2E.half - (D_801F0B10[(u8)index].x + 4);
    tile->y0 = g_Task->unk_30.half - (D_801F0B10[(u8)index].y + 4);
    tile->w  = D_801F0B10[(u8)index].w + 8;
    tile->h  = D_801F0B10[(u8)index].h + 8;
    setRGB0(tile, 0x20, 0x20, 0x20);
    GFX_AddPrim(2, sizeof(TILE));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    tile->x0 = g_Task->unk_2E.half - (D_801F0B10[(u8)index].x + 6);
    tile->y0 = g_Task->unk_30.half - (D_801F0B10[(u8)index].y + 6);
    tile->w  = D_801F0B10[(u8)index].w + 12;
    tile->h  = D_801F0B10[(u8)index].h + 12;
    setRGB0(tile, 0x20, 0x20, 0x20);
    GFX_AddPrim(2, sizeof(TILE));
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
}

/* func_801F09C4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0A28 */
#include "overlays/bmagic/Actor_Clear.h"
