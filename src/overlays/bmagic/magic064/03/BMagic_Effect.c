#include "magic064_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Four words, the copy unit of the effect work record's head. */
typedef struct WorkChunk {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} WorkChunk;

/* func_801EEC7C */
#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EECDC(void) {
    g_Task->header.mode += 1;
}

MATCH void func_801EECFC(void) {
    BMagic064Steps steps;

    steps = D_801EEC10;
    steps.handlers[g_Task->header.step]();
}

MATCH void func_801EED7C(void) {
    PartyMember* saved;
    PartyMember* battler;

    saved   = g_Task;
    battler = &g_Game.members[g_Battle.active_battler];
    g_Task  = battler;
    Actor_RequestScript((battler->facing + 0x38) & BYTE_MASK);
    g_Task = saved;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
    g_Task->param.unk_0B = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EEE1C(void) {
    PartyMember* battler;

    battler = g_Task;
    g_Task  = &g_Game.members[g_Battle.active_battler];
    if (!(Actor_StepAnimOnce() & BYTE_MASK)) {
        g_Task          = battler;
        battler->unk_09 = 0x10;
        return;
    }
    g_Task = battler;
    battler->header.step += 1;
}

INCLUDE_ASM(func_801EEEA8);

MATCH void func_801EEFF8(void) {
    u32          effect_slot;
    u8           timer;
    PartyMember* task;

    if (g_Task->timer != 0) {
        Area_IndexCells();
        g_Task->timer = 0;
    }

    timer          = g_Task->unk_09;
    g_Task->unk_09 = timer + 0xFF;
    if (timer != 0) {
        return;
    }

    effect_slot                               = Battle_AllocEffect(1, 58) & BYTE_MASK;
    task                                      = g_Task;
    g_BattleEffects[effect_slot].header.mode  = 1;
    g_BattleEffects[effect_slot].target.party = task;
    g_Task->param.unk_0B &= 0xFE;
    SND_PlayCue(0x101);
    g_Task->header.step++;
}

MATCH void func_801EF0D8(void) {
}

MATCH void func_801EF0E0(void) {
    u32        effect_slot;
    WorkChunk* src;
    WorkChunk* dst;
    WorkChunk* end;

    effect_slot = Battle_AllocEffect(1, 58);
    dst         = (WorkChunk*)&g_BattleEffects[effect_slot & BYTE_MASK];
    src         = (WorkChunk*)&BATTLE_ACTIVE_PARTY;
    end         = src + 7;
    do {
        *dst = *src;
        src += 1;
        dst += 1;
    } while (src != end);
    /* FAKE: hold tail store before tail. */
    FAKE_ORDER_LOCK(dst->w0 = src->w0);
    g_BattleEffects[effect_slot & BYTE_MASK].target.party  = g_Task;
    g_BattleEffects[effect_slot & BYTE_MASK].header.mode   = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].header.step   = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_03        = 0;
    g_BattleEffects[effect_slot & BYTE_MASK].unk_06        = 1;
    g_BattleEffects[effect_slot & BYTE_MASK].handler_index = 58;
    g_Task->unk_09                                         = 1;
    g_Task->header.step += 1;
}

MATCH void func_801EF20C(void) {
    u8 timer;

    timer = g_Task->unk_09;
    if (timer != 0) {
        g_Task->unk_09 = timer - 1;
        return;
    }
    GFX_FreePaletteFadeTarget(g_BattleEffectBattler);
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    g_Task->unk_09 = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF29C(void) {
}

MATCH void func_801EF2A4(void) {
    PartyMember* battler;
    u32          value;

    battler = g_Task;
    g_Task  = &g_Game.members[g_Battle.active_battler];
    func_801F0EEC(1, 2, (0x80 - battler->unk_09) & BYTE_MASK);
    func_801F0EEC(0, 1, (0x80 - battler->unk_09) & BYTE_MASK);
    func_801F0EEC(3, 2, battler->unk_09);
    func_801F0EEC(2, 1, battler->unk_09);
    g_Task = battler;
    if (g_BattleEffectBattler->unk_2C.half == 0) {
        value = 0x242;
        if (g_BattleEffectBattler->facing < 2U) {
            value = 0x240;
        }
    } else {
        value = 0x243;
        if (g_BattleEffectBattler->facing < 2U) {
            value = 0x241;
        }
    }
    EMI_LoadArchive(value);
    g_Task->header.step += 1;
}

INCLUDE_ASM(func_801EF3C8);

MATCH void func_801EF570(void) {
    PartyMember* battler;

    battler = g_Task;
    g_Task  = &g_Game.members[g_Battle.active_battler];
    if (!(Actor_StepAnimOnce() & BYTE_MASK)) {
        g_Task = battler;
        return;
    }
    g_Task = battler;
    battler->header.step += 1;
}

MATCH void func_801EF5FC(void) {
    PartyMember* work;

    work = g_Task;
    if (!(work->param.unk_0B & 0x1)) {
        g_AreaScrollTargetX = work->pos.x.fixed;
        FAKE_BARRIER(); /* FAKE: retail reads each field after storing the previous target */
        g_AreaScrollTargetY = work->pos.y.fixed;
        FAKE_BARRIER();
        g_AreaCameraHeight = COORD_INT(work->pos.z);
        func_801F103C();
        g_Task->unk_09      = 0x40;
        g_Task->timer       = 1;
        g_Task->header.mode = 2;
        g_Task->header.step = 0;
    }
}

MATCH void func_801EF69C(void) {
    u8 timer;

    if (g_Task->timer != 0) {
        Area_IndexCells();
        g_Task->timer = 0;
    }

    timer          = g_Task->unk_09;
    g_Task->unk_09 = timer + 0xFF;
    if (timer != 0) {
        return;
    }

    g_Game.members[g_Battle.active_battler].u.turn.action_flags.value |= COMBATANT_FLAG_DRAGON_FORM_QUEUED;
    g_Game.members[g_Battle.active_battler].counter_136 = 0;
    g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
    Battle_MarkDamaged(g_Battle.target_selector);
    func_801E5988();
}

MATCH void func_801EF78C(void) {
    Magic064Steps table;

    table = D_801EEC40;
    SYS_DISPATCH_TASK(table.steps, 1, g_Task);
}

MATCH void func_801EF7F8(void) {
    Magic064SecondSteps handlers;

    handlers = D_801EEC50;
    handlers.steps[g_Task->header.step]();
    if (g_Task->header.flags) {
        func_8014D290();
    }
}

MATCH void func_801EF87C(void) {
    g_Task->header.step += 1;
}

MATCH void func_801EF89C(void) {
    Callback table[2] = {func_801EF8F4, func_801F001C};

    table[g_Task->unk_03]();
}

INCLUDE_ASM(func_801EF8F4);

MATCH void func_801F001C(void) {
    Actor_StepAnimOnce();
    g_BattleEffectBattler->header.step += 1;
    g_Task->header.step += 1;
    g_Task->unk_03 = 0;
}

MATCH void func_801F007C(void) {
    func_801E5988();
}

/* Run the magic064 step, then draw every live ring under one draw mode. */
MATCH void func_801F009C(void) {
    Magic064RingSteps handlers;
    s32               tpage;
    u16               i;

    handlers = D_801EEC5C;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x8F;
    } else {
        tpage = 0x2F;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    for (i = 0; i < MAGIC064_RING_COUNT; i++) {
        if (D_801F13B4[i].unk_00 != 0) {
            D_801F28B4 = &D_801F13B4[i];
            func_801F0448();
        }
    }
}

MATCH void func_801F01C4(void) {
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 64;
    func_801F03D8();
    g_Task->header.step++;
}

MATCH void func_801F0214(void) {
    u8 timer;

    func_801F03D8();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F0278(void) {
    u8 ticks;

    func_801F03D8();
    if (!(g_FrameCount & 0x1)) {
        ticks = g_Task->param.unk_0B;
        if (ticks >= 0x18U) {
            g_BattleEffectBattler->header.step += 1;
            g_Task->header.step += 1;
            return;
        }
        g_Task->param.unk_0B = ticks + 1;
    }
}

MATCH void func_801F0310(void) {
    if (g_BattleEffectBattler->header.step == 0xA) {
        g_Task->header.step += 1;
    }
    func_801F03D8();
}

MATCH void func_801F0364(void) {
    u16 i;
    u32 off;

    i = 0;
    do {
        off = (u16)i * 0x1C;
        if (FIELD(u8, D_801F13B4, off) != 0) {
            return;
        }
        i++;
    } while (i < 0xC0);
    g_BattleEffectBattler->param.unk_0B &= 0xFE;
    func_801E5988();
}

MATCH void func_801F03D8(void) {
    u16 count;
    u16 i;
    u32 off;

    count = 0;
    i     = 0;
    do {
        off = (u16)i * 0x1C;
        if (FIELD(u8, D_801F13B4, off) == 0) {
            FIELD(u8, D_801F13B4, off) = 1;
            count++;
            if (count == 6) {
                return;
            }
        }
        i++;
    } while (i < 0xC0);
}

MATCH void func_801F0448(void) {
    Callback table[2] = {func_801F04A0, func_801F05A4};

    table[D_801F28B4->mode]();
}

/* Start the magic064 ring at the active battler: a random angle, both radii at the effect ticker,
 * their speeds, and the centre at the battler screen point plus its facing offset. */
MATCH void func_801F04A0(void) {
    D_801F28B4->angle       = rand() & 0xFFF;
    D_801F28B4->inner.fixed = TO_COORD(g_Task->param.unk_0B);
    D_801F28B4->outer.fixed = TO_COORD(g_Task->param.unk_0B);
    D_801F28B4->inner_speed = 0x32000;
    D_801F28B4->outer_speed = 0x19800;
    D_801F28B4->x           = BATTLE_ACTIVE_PARTY.unk_2E.signed_half + D_801F138C[BATTLE_ACTIVE_PARTY.facing][0];
    D_801F28B4->y           = BATTLE_ACTIVE_PARTY.unk_30.signed_half + D_801F138C[BATTLE_ACTIVE_PARTY.facing][1];
    D_801F28B4->mode += 1;
}

/* Spread the magic064 ring: grow both radii by their speeds, raise the speeds by a quarter and
 * draw five spokes between the radii; past an outer radius of 448 the ring ends. */
MATCH void func_801F05A4(void) {
    D_801F28B4->inner.fixed += D_801F28B4->inner_speed;
    D_801F28B4->outer.fixed += D_801F28B4->outer_speed;
    D_801F28B4->inner_speed = D_801F28B4->inner_speed * 5 / 4;
    D_801F28B4->outer_speed = D_801F28B4->outer_speed * 5 / 4;
    func_801F0B8C(D_801F28B4->x + FIXED_MUL(rcos(D_801F28B4->angle), D_801F28B4->inner.part.integer), D_801F28B4->y + FIXED_MUL(rsin(D_801F28B4->angle), D_801F28B4->inner.part.integer),
                  D_801F28B4->x + FIXED_MUL(rcos(D_801F28B4->angle), D_801F28B4->outer.part.integer), D_801F28B4->y + FIXED_MUL(rsin(D_801F28B4->angle), D_801F28B4->outer.part.integer));
    func_801F0B8C(D_801F28B4->x + FIXED_MUL(rcos(D_801F28B4->angle + 1), D_801F28B4->inner.part.integer), D_801F28B4->y + FIXED_MUL(rsin(D_801F28B4->angle + 1), D_801F28B4->inner.part.integer),
                  D_801F28B4->x + FIXED_MUL(rcos(D_801F28B4->angle + 1), D_801F28B4->outer.part.integer), D_801F28B4->y + FIXED_MUL(rsin(D_801F28B4->angle + 1), D_801F28B4->outer.part.integer));
    func_801F0B8C(D_801F28B4->x + FIXED_MUL(rcos(D_801F28B4->angle + 2), D_801F28B4->inner.part.integer), D_801F28B4->y + FIXED_MUL(rsin(D_801F28B4->angle + 2), D_801F28B4->inner.part.integer),
                  D_801F28B4->x + FIXED_MUL(rcos(D_801F28B4->angle + 2), D_801F28B4->outer.part.integer), D_801F28B4->y + FIXED_MUL(rsin(D_801F28B4->angle + 2), D_801F28B4->outer.part.integer));
    func_801F0B8C(D_801F28B4->x + FIXED_MUL(rcos(D_801F28B4->angle + 3), D_801F28B4->inner.part.integer), D_801F28B4->y + FIXED_MUL(rsin(D_801F28B4->angle + 3), D_801F28B4->inner.part.integer),
                  D_801F28B4->x + FIXED_MUL(rcos(D_801F28B4->angle + 3), D_801F28B4->outer.part.integer), D_801F28B4->y + FIXED_MUL(rsin(D_801F28B4->angle + 3), D_801F28B4->outer.part.integer));
    func_801F0B8C(D_801F28B4->x + FIXED_MUL(rcos(D_801F28B4->angle + 4), D_801F28B4->inner.part.integer), D_801F28B4->y + FIXED_MUL(rsin(D_801F28B4->angle + 4), D_801F28B4->inner.part.integer),
                  D_801F28B4->x + FIXED_MUL(rcos(D_801F28B4->angle + 4), D_801F28B4->outer.part.integer), D_801F28B4->y + FIXED_MUL(rsin(D_801F28B4->angle + 4), D_801F28B4->outer.part.integer));
    if (D_801F28B4->outer.part.integer > 0x1C0) {
        D_801F28B4->unk_00 = 0;
        D_801F28B4->mode   = 0;
    }
}

MATCH void func_801F0B8C(s16 x0, s16 y0, s16 x1, s16 y1) {
    LINE_G2* primitive;

    primitive = (LINE_G2*)g_GfxPrimCursor;
    SetLineG2(primitive);
    setRGB0(primitive, 240, 20, 120);
    setRGB1(primitive, 0, 0, 0);
    setXY2(primitive, x0, y0, x1, y1);
    SetSemiTrans(primitive, 1);
    GFX_AddPrim(2, sizeof(LINE_G2));
}

MATCH void func_801F0C38(void) {
    Magic064SecondSteps handlers;

    handlers = D_801EEC70;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}

MATCH void func_801F0CBC(void) {
    Actor_RequestScript(g_Task->param.unk_0B);
    do {
    } while (!(Actor_StepAnimOnce() & BYTE_MASK));
    g_Task->header.step += 1;
}

MATCH void func_801F0D14(void) {
    g_Task->header.step += 1;
}

MATCH void func_801F0D34(void) {
    GFX_FreePaletteFadeTarget(g_Task);
    func_801E5988();
}

MATCH void func_801F0D64(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes, 2, g_Task);
}

#include "overlays/bmagic/Effect_ClearTimerNextStep.h"

MATCH void func_801F0DD8(void) {
    PartyMember* work;
    s8           counter;

    work         = g_Task;
    counter      = work->unk_09 - 1;
    work->unk_09 = counter;
    if (counter == -6) {
        g_Task->header.step++;
    }
    Area_UpdatePaletteTint((s8)g_Task->unk_09);
}

MATCH void func_801F0E50(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->header.step == 10) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801F0E90(void) {
    PartyMember* work;

    work = g_Task;
    work->unk_09++;
    if (work->unk_09 == 0) {
        func_801E5988();
    }
    Area_UpdatePaletteTint((s8)g_Task->unk_09);
}

MATCH void func_801F0EEC(u32 sprite, s32 blend, s32 color) {
    SPRT* prim;
    /* FAKE: the task pointer must stay in v0 across the branch; an unpinned local lands in v1, and the best pure-C body is 0x14C against retail's 0x150. */
    FAKE_REG(PartyMember*, task, "v0");
    u16 tpage;

    tpage = GetTPage(2, blend & BYTE_MASK, 832, 256);
    GFX_SET_DRAW_MODE(tpage);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(DR_MODE));
    prim = (SPRT*)g_GfxPrimCursor;
    SetSprt(prim);
    setRGB0(prim, color, color, color);
    if ((sprite & BYTE_MASK) < 2) {
        task     = g_Task;
        prim->x0 = task->unk_2E.half - 32;
    } else {
        task     = g_Task;
        prim->x0 = task->unk_2E.half - 40;
    }
    prim->y0 = task->unk_30.half - 64;
    /* FAKE: the barrier keeps the prim copy out of the load delay, as retail. */
    FAKE_BARRIER();
    setUV0(prim, D_801F13A4[sprite & BYTE_MASK].x, D_801F13A4[sprite & BYTE_MASK].y);
    setWH(prim, 80, 72);
    SetSemiTrans(prim, 1);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(SPRT));
}

/* Rebuild the field map view around the scroll target: clear the cell links, place the camera,
 * stream the cell rows the remainder has passed and project every cell of the grid. */
MATCH void func_801F103C(void) {
    AreaCell* cell;
    u16*      order;
    s32       row;
    s32       col;

    for (row = 0; row < 0x400; row++) {
        for (col = 0; col < 2; col++) {
            g_AreaCellPrims[row][col].pad1 = 0;
            g_AreaCellPrims[row][col].pad2 = 0;
        }
    }
    g_AreaCameraX     = 0x7FFF - (g_AreaScrollTargetX >> 8);
    g_AreaCameraY     = 0x8000 - (g_AreaScrollTargetY >> 8);
    g_AreaTileOriginX = (g_AreaScrollTargetX >> 16) - 24;
    g_AreaTileOriginY = (g_AreaScrollTargetY >> 16) + 3;
    D_8014933D        = 0;
    if (g_AreaMapBundle.scroll_1E != 0) {
        g_AreaTileRemainderY = g_AreaMapBundle.scroll_1E;
    } else {
        g_AreaTileRemainderY = -g_AreaCameraHeight * 2;
    }
    D_80149336 = 0;
    while ((s16)g_AreaTileRemainderY >= 0x200) {
        Area_LoadCellRowsNext();
        g_AreaTileRemainderY -= 0x200;
    }
    while ((s16)g_AreaTileRemainderY < -0x1FF) {
        Area_LoadCellRowsPrev();
        g_AreaTileRemainderY += 0x200;
    }
    g_AreaCameraStep          = 0;
    g_AreaCameraHeightStep    = 0;
    g_AreaHeightOffsetEnabled = 0;
    g_AreaCameraRefreshCount  = 3;
    for (row = 0; row < 56; row++) {
        for (col = 0; col < 28; col++) {
            cell          = &g_AreaCells[row][col];
            cell->prim_id = 0;
            BMagic_ProjectCell(row, col, cell);
        }
    }
    row   = 0x3FF;
    order = &g_AreaCellPrimFreeIds[0x3FF];
    for (; row >= 0; row--) {
        *order = row;
        order--;
    }
    g_AreaCellPrimFreeIndex = 1;
    g_AreaGridColCursor     = 0x1B;
    g_AreaGridRowCursor     = 0x37;
    func_80154438();
    Area_RunBundleOpcodes();
}

/* Report the map cell the projected point lands on: out receives
 * the cell, or zero when the probe leaves the map or hits an empty cell. */
/* func_801F12B8 */
MATCH void BMagic_ProjectCell(s32 px, s32 py, AreaCell* out) {
    u8* buffer;
    s32 width;
    s32 x2;
    s32 x;
    s32 y;
    u16 value;

    x = g_AreaTileOriginX + (px + 1) / 2 + py;
    y = g_AreaTileOriginY + px / 2 - py;

    if (x > 0) {
        buffer = MEM_PTR(u8, 0x80104000u); /* the map bundle, include/area/area.h */
        width  = buffer[0];
        if (x < width - 1) {
            if (y > 0) {
                if (y < g_AreaMapBundle.height - 1) {
                    value = *(u16*)(buffer + ((g_AreaMapBundle.grid_off4_02 * 4) + (x2 = x * 2) + (y * width * 2)));
                    if (value != 0) {
                        out->tile_x = x;
                        out->tile_y = y;
                        return;
                    }
                }
            }
        }
    }
    out->tile_x = 0;
    out->tile_y = 0;
}
