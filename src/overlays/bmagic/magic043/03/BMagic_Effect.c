#include "magic043_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    Magic043Steps handlers;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);

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

MATCH void func_801EED30(void) {
    PartyMember* actor;
    PartyMember* work;
    u16*         src;
    u16*         dst;
    u8           slot;
    u8           i;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    actor                = g_BattleSelectedActor;
    g_Task->facing       = actor->facing;
    g_Task->pos.x.fixed  = actor->pos.x.fixed;
    g_Task->pos.y.fixed  = actor->pos.y.fixed;
    g_Task->pos.z.fixed  = actor->pos.z.fixed;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 9;
    g_Task->header.mode += 1;
    for (i = 0; i < 8; i++) {
        slot = BMagic_AllocEffect();
        if (slot != 0xFF) {
            work                                   = g_Task;
            BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 8 + 1;
            BMAGIC_EFFECT_SLOTS[slot].target.party = work;
            g_Task->param.unk_0B += 1;
        }
    }
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
}

MATCH void func_801EEEF0(void) {
    PartyMember* battler;
    u8           value;

    battler        = g_Battle.selected_actor;
    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer  = GFX_AllocPaletteFade(battler, 0, 0, 0, 1);
        g_Task->unk_09 = 4;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEF98(void) {
    u8 count;

    g_PaletteFades[g_Task->timer].offset.red += 2;
    g_PaletteFades[g_Task->timer].offset.green += 2;
    g_PaletteFades[g_Task->timer].offset.blue += 2;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        g_Task->unk_09 = 4;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF0B4(void) {
    u8*          selector;
    u8           slot;
    PartyMember* work;
    u8           count;

    g_PaletteFades[g_Task->timer].offset.red -= 2;
    g_PaletteFades[g_Task->timer].offset.green -= 2;
    g_PaletteFades[g_Task->timer].offset.blue -= 2;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count != 0) {
        return;
    }
    if (g_Task->param.unk_0B < 2) {
        GFX_FreePaletteFade(g_Task->timer);
        selector = (u8*)&g_Battle.target_selector;
        func_800AF814(*selector);
        if (g_Battle.action_id == 0x2B) {
            if (func_800AED5C(1, *selector) & BYTE_MASK) {
                slot                               = Battle_AllocEffect(1, 72);
                work                               = g_Task;
                g_BattleEffects[slot].unk_04       = 0;
                g_BattleEffects[slot].arg.unk_09   = 1;
                g_BattleEffects[slot].unk_0A       = 0;
                g_BattleEffects[slot].target.party = work;
                g_Task->param.unk_0B += 1;
            } else {
                slot                               = Battle_AllocEffect(1, 72);
                work                               = g_Task;
                g_BattleEffects[slot].unk_04       = 8;
                g_BattleEffects[slot].arg.unk_09   = 1;
                g_BattleEffects[slot].unk_0A       = 0;
                g_BattleEffects[slot].target.party = work;
                g_Task->param.unk_0B += 1;
            }
        }
        g_Task->header.mode += 1;
    } else {
        g_Task->unk_09 = 4;
        g_Task->header.mode -= 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF360 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF3A4(void) {
    SYS_DISPATCH_BYTE(D_801EFC8C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF72C();
        func_801EF7F8();
        PopMatrix();
    }
}

MATCH void func_801EF42C(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0) {
        g_Task->facing = g_BattleEffectBattler->facing;
        g_Task->unk_0C = 0x20000;
        g_Task->unk_10 = 0;
        func_801DD350(g_Task);
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(256);
        g_Task->unk_0C      = -0x1000;
        g_Task->unk_10      = 0;
        func_801DD350(g_Task);
        g_Task->unk_14 = ratan2(g_BattleEffectBattler->pos.x.fixed - g_AreaScrollTargetX, g_BattleEffectBattler->pos.y.fixed - g_AreaScrollTargetY);
        g_Task->unk_09 = 0;
        g_Task->timer  = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF55C(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    g_Task->unk_09 += 1;
    g_Task->timer += 2;
    if (g_Task->timer == 16) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF5E0(void) {
    PartyMember* work;
    u8           count;

    work         = g_Task;
    count        = work->unk_09 + 1;
    work->unk_09 = count;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    if (count == 24) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF64C(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    g_Task->unk_09 += 1;
    g_Task->timer -= 2;
    if (g_Task->timer == 0) {
        BMAGIC_TICK_EFFECT_WORK();
        BMagic_ResetLocalWork();
    }
}

MATCH void func_801EF72C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 1024;
    rot.vy = D_801EFC9C[g_Task->facing];
    rot.vz = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EF7F8);

/* func_801EFC24 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
