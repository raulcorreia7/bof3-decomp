#include "magic131_03.h"
#include "sys/scratchpad.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC24(void) {
    Callback     handlers[8];
    PartyMember* saved_battler;
    s32          tpage;
    u8           i;

    __builtin_memcpy(handlers, D_801EEC04, sizeof(handlers));
    SYS_DISPATCH_BYTE(handlers, g_Task->header.mode);
    if (GetGraphType() == 1) {
        tpage = 0x125;
    } else if (GetGraphType() == 2) {
        tpage = 0x125;
    } else {
        tpage = 0x55;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    for (i = 0; i < ARRAY_COUNT(D_801F1CA0); i++) {
        if (D_801F1CA0[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_battler         = g_BattleEffectBattler;
            D_801F24E0            = &D_801F1CA0[i];
            g_BattleEffectBattler = D_801F1CA0[i].battler;
            func_801F10F4();
            g_BattleEffectBattler = saved_battler;
        }
    }
    if (GetGraphType() == 1) {
        tpage = 0x25;
    } else if (GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
}

MATCH void func_801EEDEC(void) {
    PartyMember* target;
    u16*         src;
    u16*         dst;
    u16          i;
    u32          slot;

    for (i = 0; i < ARRAY_COUNT(D_801F1CA0); i++) {
        D_801F1CA0[i].header.flags = 0;
        D_801F1CA0[i].header.mode  = 0;
        D_801F1CA0[i].header.step  = 0;
    }
    g_Task->facing = g_BattleEffectBattler->facing;
    Battle_CenterCamera();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 10;
    g_Task->timer        = 0;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 105) & BYTE_MASK;
    target                             = g_Task;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].target.party = target;
    g_Task->param.unk_0B += 1;
    BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i);
    g_GfxPalettePending = 1;
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
}

INCLUDE_ASM(func_801EEF64);

MATCH void func_801EF000(void) {
    u16          i;
    u32          slot;
    PartyMember* work;

    if (!EMI_IsReady()) {
        return;
    }
    g_Game.members[0].header.flags     = 0;
    g_Game.members[1].header.flags     = 0;
    g_Game.members[2].header.flags     = 0;
    slot                               = Battle_AllocEffect(1, 0x69) & BYTE_MASK;
    work                               = g_Task;
    g_BattleEffects[slot].unk_04       = 0x21;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 0x18;
    g_BattleEffects[slot].target.party = work;
    g_Task->param.unk_0B += 1;
    for (i = 0; i < 256; i++) {
        MEM(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW + i * 2) = MEM(u16, AREA_PALETTE_ARENA_33C00 + i * 2);
    }
    g_GfxPalettePending = 1;
    g_Task->header.mode += 1;
}

MATCH void func_801EF110(void) {
    PartyMember* work;
    u32          slot;

    if (g_Task->param.unk_0B == 0) {
        slot                               = Battle_AllocEffect(1, 0x69) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B++;
        g_Task->unk_09 = 10;
        g_Task->header.mode++;
    }
}

MATCH void func_801EF1C0(void) {
    u8 count;
    u8 found;
    u8 i;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    found          = 0;
    if (count != 0) {
        return;
    }
    for (i = 0; i < g_Game.party_size; i++) {
        if (g_Game.members[i].chr.character_id == CHAR_ID_REI && (g_Game.members[i].u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM_QUEUED)) {
            found = 1;
        }
    }
    if (found) {
        if (g_EmiLoadedCharacterIndex == 7) {
            EMI_LoadArchive((g_Battle.scroll_dir & 0x2) ? 0x205 : 0x201);
        }
        if (g_EmiLoadedCharacterIndex == 0xD) {
            EMI_LoadArchive((g_Battle.scroll_dir & 0x2) ? 0x206 : 0x202);
        }
        if (g_EmiLoadedCharacterIndex == 0xE) {
            EMI_LoadArchive((g_Battle.scroll_dir & 0x2) ? 0x207 : 0x203);
        }
        if (g_EmiLoadedCharacterIndex == 0xF) {
            if (g_Battle.scroll_dir & 0x2) {
                EMI_LoadArchive(0x208);
            } else {
                EMI_LoadArchive(0x204);
            }
        }
    } else {
        if (g_Battle.scroll_dir & 0x2) {
            EMI_GetArchiveId(g_EmiLoadedCharacterIndex & 0x7F, 2);
        } else {
            EMI_GetArchiveId(g_EmiLoadedCharacterIndex & 0x7F, 1);
        }
    }
    g_Task->header.mode += 1;
}

MATCH void func_801EF3D0(void) {
    if (!EMI_IsReady()) {
        return;
    }
    if (g_Battle.scroll_dir & 0x2) {
        EMI_LoadArchive(D_800B499C[g_Battle.dragon_form][1][g_EmiLoadedCharacterIndex]);
    } else {
        EMI_LoadArchive(D_800B499C[g_Battle.dragon_form][0][g_EmiLoadedCharacterIndex]);
    }
    g_Task->header.mode += 1;
}

MATCH void func_801EF488(void) {
    PartyMember* prev;
    PartyMember* battler;
    s32          i;
    s32          slot;

    if (EMI_IsReady() != 0) {
        i = 0;
        if (g_Game.party_size != 0) {
            do {
                slot                              = i & BYTE_MASK;
                g_Game.members[slot].header.flags = 1;
                prev                              = g_Task;
                battler                           = &g_Game.members[slot];
                g_Task                            = battler;
                Actor_SelectScript((battler->facing + 4) & BYTE_MASK);
                if (g_Game.members[slot].chr.status & 0x2080) {
                    Actor_SelectScript((g_Task->facing + 0x18) & BYTE_MASK);
                }
                if (g_Game.members[slot].chr.status & 0x800) {
                    Actor_SelectScript((g_Task->facing + 0x30) & BYTE_MASK);
                }
                if (Battle_SlotIsBlocked(slot) & BYTE_MASK) {
                    Actor_SelectScript((g_Task->facing + 0x1C) & BYTE_MASK);
                }
                i++;
                g_Task = prev;
            } while ((u32)(i & BYTE_MASK) < g_PartySize);
        }
        g_Task->header.mode++;
    }
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EF668 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

INCLUDE_ASM(func_801EF6AC);

MATCH void func_801EF7FC(void) {
    PartyMember* work;
    PartyMember* task;
    PartyMember* actor;
    u8           count;
    u8           i;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count != 0) {
        return;
    }
    if (g_Battle.scroll_dir == 0 || g_Battle.scroll_dir == 3) {
        g_Task->unk_2E.half = 0x3D;
        g_Task->unk_30.half = 0x46;
        g_Task->unk_0C      = -4;
        g_Task->unk_10      = -4;
        g_Task->unk_18      = -1;
        g_Task->unk_1C      = -1;
        g_Task->unk_2A      = 1;
    } else {
        g_Task->unk_2E.half = 0x103;
        g_Task->unk_30.half = 0x46;
        g_Task->unk_0C      = 4;
        g_Task->unk_10      = -4;
        g_Task->unk_18      = 1;
        g_Task->unk_1C      = -1;
        g_Task->unk_2A      = 0;
    }
    work = g_Task;
    for (i = 0; i < 16; i++) {
        work->unk_0C += work->unk_18;
        work->unk_10 += work->unk_1C;
        work->unk_2E.half += work->unk_0C;
        work->unk_30.half += work->unk_10;
    }
    task           = g_Task;
    task->unk_0C   = ~task->unk_0C + 1;
    task->unk_25   = 5;
    task->unk_10   = ~task->unk_10 + 1;
    g_Task->unk_26 = 0;
    g_Task->unk_27 = 2;
    g_Task->unk_28 = 1;
    g_Task->unk_24 = 0x80;
    actor          = g_Task;
    actor->unk_48  = 0;
    actor->scale.x = 0x10000;
    actor->scale.y = 0x10000;
    g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Task->unk_5C      = 0;
    g_Task->unk_5D      = 0;
    g_Task->unk_5E      = 0;
    g_Task->unk_5F      = 0;
    g_Task->unk_29      = 2;
    g_Task->unk_2C.half = 0;
    g_Task->unk_2B      = 0;
    Actor_SelectScript(0);
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x01));
    g_Task->unk_09 = 0x10;
    g_Task->header.step += 1;
}

MATCH void func_801EFA68(void) {
    u8 count;

    g_Task->unk_2E.half += g_Task->unk_0C;
    g_Task->unk_30.half += g_Task->unk_10;
    g_Task->unk_0C += g_Task->unk_18;
    g_Task->unk_10 += g_Task->unk_1C;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count & BYTE_MASK) {
        return;
    }
    if (g_Battle.scroll_dir == 0 || g_Battle.scroll_dir == 3) {
        g_Task->unk_0C = 4;
        g_Task->unk_10 = 4;
        g_Task->unk_18 = -1;
        g_Task->unk_1C = -1;
    } else {
        g_Task->unk_0C = -4;
        g_Task->unk_10 = 4;
        g_Task->unk_18 = 1;
        g_Task->unk_1C = -1;
    }
    g_Task->unk_09 = 6;
    g_Task->header.step++;
}

MATCH void func_801EFB64(void) {
    PartyMember* work  = g_Task;
    u8           timer = work->unk_09 - 1;
    work->unk_0C += work->unk_18;
    work->unk_09 = timer;
    work->unk_10 += work->unk_1C;
    work->unk_2E.half += work->unk_0C;
    work->unk_30.half += work->unk_10;
    if (timer == 0) {
        g_Task->unk_09 = 0x24;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFBF8(void) {
    u8 count;

    Actor_StepAnimLoop();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        Actor_SelectScript(1U);
        g_Task->unk_09 = 0x29;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EFC74);

MATCH void func_801EFEF0(void) {
    if (Actor_StepAnimOnce() != 0u) {
        g_Task->unk_09      = 0xF;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EFF48(void) {
    u32 direction;
    u8  timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        direction = LOBU(g_Battle.scroll_dir);
        if (direction == 0 || direction == 3) {
            g_Task->unk_0C = 8;
            g_Task->unk_10 = -1;
            g_Task->unk_18 = 1;
            g_Task->unk_1C = -1;
        } else {
            g_Task->unk_0C = -8;
            g_Task->unk_10 = -1;
            g_Task->unk_18 = -1;
            g_Task->unk_1C = -1;
        }
        g_Task->unk_09 = 0;
        g_Task->timer  = 30;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0034(void) {
    u8           timer;
    u8           count;
    PartyMember* work;

    if (g_FrameCount & 0x1) {
        count = g_Task->unk_09;
        if (count < 8U) {
            g_Task->unk_09 = count + 1;
            g_Task->unk_10 += g_Task->unk_1C;
        }
    }
    work        = g_Task;
    timer       = work->timer - 1;
    work->timer = timer;
    work->unk_2E.half += work->unk_0C;
    work->unk_30.half += work->unk_10;
    if (!(timer & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801F0100(void) {
    SYS_DISPATCH_BYTE(D_801F1BF4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F030C();
    }
}

#include "overlays/bmagic/Effect_ClearTimerNextStep.h"

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void func_801F01F8(void) {
    if ((BATTLE_ACTIVE_WORK->unk_09 == 0) && (EMI_IsReady() != 0)) {
        g_Task->timer = 8;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_DrawFullScreenQuad.h"

MATCH void func_801F030C(void) {
    POLY_F4* prim;
    s32      shade;
    s32      tpage;

    EFFECT_DRAW_FULL_SCREEN_QUAD(2);
}

MATCH void func_801F0438(void) {
    SYS_DISPATCH_BYTE(D_801F1C08, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F06B4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F04C0);

MATCH void func_801F053C(void) {
    EFFECT_ADVANCE_AT_COUNT(4, 0x40);
}

MATCH void func_801F058C(void) {
    PartyMember* work;
    PartyMember* active;
    s8           count;

    work = g_Task;
    work->unk_09 += 2;
    work         = g_Task;
    count        = work->unk_5D - 4;
    work->unk_5D = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F06B4);

MATCH void func_801F0B44(void) {
    SYS_DISPATCH_BYTE(D_801F1C24, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F0D44();
        func_801F0DF4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F0BCC);

MATCH void func_801F0C4C(void) {
    s32 value;

    value          = g_Task->unk_14 + 0x20;
    g_Task->unk_14 = value;
    if (value == 0x200) {
        g_Task->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

MATCH void Effect_CountDownAndStep2(void) {
    BMAGIC_COUNT_DOWN_AND_STEP();
}

MATCH void func_801F0CE4(void) {
    PartyMember* work = g_Task;
    u8           timer;

    work->unk_14 += 0x10;

    timer        = work->unk_09 - 2;
    work->unk_09 = timer;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void Effect_SetActorMatrix4(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

MATCH void func_801F0DF4(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;
    s32       u;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = ((g_Task->param.unk_0B & 3) << 7) | 0x25;
    } else {
        tpage = ((g_Task->param.unk_0B & 3) << 5) | 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = g_Task->unk_14;
    D_1F800000.view.effect.params[4] = g_Task->unk_09 << 3;
    D_1F800000.view.effect.params[5] = g_Task->unk_09 << 3;
    D_1F800000.view.effect.params[6] = g_Task->unk_09 << 3;
    D_1F800014[1].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    for (i = 1; i <= 16; i++) {
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[0].vz = -1024;
        D_1F800014[2].vx = D_1F800014[1].vx;
        D_1F800014[2].vy = D_1F800014[1].vy;
        D_1F800014[2].vz = 0;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz = -1024;
        D_1F800014[3].vx = D_1F800014[1].vx;
        D_1F800014[3].vy = D_1F800014[1].vy;
        D_1F800014[3].vz = 0;
        prim             = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetSemiTrans(prim, g_Task->param.unk_0B);
        prim->tpage = GetTPage(1, g_Task->param.unk_0B, 832, 256);
        prim->clut  = GetClut(0, 506);
        u           = (i & 1) << 6;
        setUV4(prim, u, 0, u + 63, 0, u, 191, u + 63, 191);
        setRGB0(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        if (i < 7 || i > 14) {
            GFX_AddPrim(3, sizeof(POLY_FT4));
        }
    }
}

MATCH void func_801F10F4(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 27), 1, D_801F24E0);
}

MATCH void func_801F1138(void) {
    SYS_DISPATCH_BYTE(D_801F1C48, D_801F24E0->header.step);
    if (D_801F24E0->header.flags != 0 && D_801F24E0->header.step != 0) {
        func_801F1B14();
        func_801F1844();
    }
}

MATCH void func_801F11B8(void) {
    s16* angle_cell;
    s32  z;
    u8   phase;

    phase                   = D_801F1C38[D_801F24E0->unk_07];
    angle_cell              = &D_1F800006;
    *angle_cell             = phase << 7;
    D_801F24E0->pos.x.fixed = g_AreaScrollTargetX + ((rsin(phase << 7) << 6) >> 3);
    D_801F24E0->pos.y.fixed = g_AreaScrollTargetY + ((rcos(*angle_cell) << 6) >> 3);
    z                       = g_BattleEffectBattler->pos.z.fixed;
    D_801F24E0->pos.z.fixed = z;
    D_801F24E0->phase_0C    = 0x40;
    D_801F24E0->timer_05    = 16;
    D_801F24E0->unk_06      = 20;
    D_801F24E0->header.step++;
}

MATCH void func_801F12A0(void) {
    s16* angle_cell;
    u8   phase;

    MAGIC131_ORBIT_GROW(D_801F1C38, 7);
}

MATCH void func_801F13A4(void) {
    s16* angle_cell;
    u8   phase;
    u8   timer;

    MAGIC131_ORBIT_CLOSE(D_801F1C38, 7);
}

MATCH void func_801F14A0(void) {
    s16 timer;

    SYS_DISPATCH_BYTE(D_801F1C94, D_801F24E0->header.step);
    timer = D_801F24E0->unk_26;
    if (timer != 0) {
        D_801F24E0->unk_26 = timer - 1;
        return;
    }
    if (D_801F24E0->header.flags != 0 && D_801F24E0->header.step != 0) {
        func_801F1B14();
        func_801F1844();
    }
}

MATCH void func_801F153C(void) {
    s16* angle_cell;
    u8   phase;

    phase                   = D_801F1C54[D_801F24E0->unk_07];
    angle_cell              = &D_1F800006;
    *angle_cell             = phase << 6;
    D_801F24E0->pos.x.fixed = g_AreaScrollTargetX + ((rsin(phase << 6) << 6) >> 3);
    D_801F24E0->pos.y.fixed = g_AreaScrollTargetY + ((rcos(*angle_cell) << 6) >> 3);
    D_801F24E0->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    COORD_INT(D_801F24E0->pos.z) += D_801F1C74[D_801F24E0->unk_07] << 6;
    D_801F24E0->phase_0C = 0x40;
    D_801F24E0->timer_05 = 16;
    D_801F24E0->unk_06   = 8;
    D_801F24E0->header.step += 1;
}

MATCH void func_801F1644(void) {
    s16* angle_cell;
    u8   phase;

    MAGIC131_ORBIT_GROW(D_801F1C54, 6);
}

MATCH void func_801F1748(void) {
    s16* angle_cell;
    u8   phase;
    u8   timer;

    MAGIC131_ORBIT_CLOSE(D_801F1C54, 6);
}

MATCH void func_801F1844(void) {
    POLY_G3* prim;
    s32      shade;
    u8       i;

    D_1F800000.view.effect.params[0] = D_801F24E0->unk_06 + (rand() & 3);
    if (D_801F24E0->header.mode != 0) {
        shade = ((rand() & 3) + 4) * D_801F24E0->timer_05;
    } else {
        shade = D_801F24E0->timer_05 * 14;
    }
    D_1F800000.view.effect.params[6] = D_801F24E0->unk_20;
    D_1F800000.view.effect.params[7] = D_801F24E0->unk_22;
    for (i = 0; i < 8; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        prim->x0                         = D_1F800000.view.effect.params[6];
        prim->y0                         = D_1F800000.view.effect.params[7];
        D_1F800000.view.effect.params[3] = (i << 9) & 0xFFF;
        prim->x1                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[0]);
        prim->y1                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[0]);
        D_1F800000.view.effect.params[3] = ((i + 1) << 9) & 0xFFF;
        prim->x2                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[0]);
        prim->y2                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[0]);
        setRGB0(prim, shade, shade, shade);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(2, sizeof(POLY_G3));
    }
}

MATCH u8 func_801F1A58(void) {
    u8 i;

    for (i = 0; i < 48; i++) {
        if (!(D_801F1CA0[i].header.flags & 0x1)) {
            D_801F1CA0[i].header.flags |= 1;
            return i;
        }
    }
    return GAME_NONE;
}

MATCH void func_801F1AC4(void) {
    D_801F24E0->header.flags = 0;
    D_801F24E0->header.mode  = 0;
    D_801F24E0->header.step  = 0;
    D_801F24E0->unk_03       = 0;
    D_801F24E0->unk_04       = 0;
}

MATCH void func_801F1B14(void) {
    BMagicEffectWork* work;
    s16               vec[3];
    TILE_1*           primitive;

    work      = D_801F24E0;
    vec[0]    = (work->pos.x.fixed >> 9) - 0x4000;
    primitive = (TILE_1*)g_GfxPrimCursor;
    vec[1]    = (work->pos.y.fixed >> 9) - 0x4000;
    vec[2]    = -(COORD_INT(work->pos.z) / 2);
    SetTile1(primitive);
    RotTransPers((SVECTOR*)vec, (long*)&primitive->x0, (long*)vec, (long*)&vec[2]);
    D_801F24E0->unk_20 = primitive->x0;
    D_801F24E0->unk_22 = primitive->y0;
}
