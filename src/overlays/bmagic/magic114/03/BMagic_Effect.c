#include "magic114_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC44(void) {
    Callback handlers[7];
    s32      tpage;

    __builtin_memcpy(handlers, D_801EEC04, sizeof(handlers));
    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
    if (g_Task->header.flags != 0 && g_Task->header.mode != 0) {
        func_801EF128();
    }
    SYS_DISPATCH_BYTE(handlers, g_Task->header.mode);
    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
}

INCLUDE_ASM(func_801EEDA0);

MATCH void func_801EEE84(void) {
    u8 count;

    count         = g_Task->timer + 1;
    g_Task->timer = count;
    if ((count & BYTE_MASK) >= 0x21U) {
        g_Task->header.mode += 1;
        g_Task->unk_09 = 0;
    }
}

MATCH void func_801EEEE4(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) >= 0x21U) {
        g_Task->header.mode += 1;
        g_Task->unk_09 = 0;
    }
}

MATCH void func_801EEF44(void) {
    u8  count;
    u32 slot;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) < 0x20U) {
        return;
    }
    g_Task->header.mode += 1;
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x01));
    slot                               = Battle_AllocEffect(1, 7) & BYTE_MASK;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].unk_08       = g_BattleEffectBattler->facing;
    g_BattleEffects[slot].target.party = g_BattleEffectBattler;
}

MATCH void func_801EEFFC(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->header.mode += 1;
        return;
    }
    func_801F0FBC();
}

MATCH void func_801EF060(void) {
    u8 count;

    count         = g_Task->timer - 1;
    g_Task->timer = count;
    if (!(count & BYTE_MASK)) {
        g_Task->header.mode += 1;
        g_Task->unk_09 = 0x40;
    }
}

#include "overlays/bmagic/Effect_CountDownAndPlay.h"

INCLUDE_ASM(func_801EF128);

INCLUDE_ASM(func_801EF280);

MATCH void func_801EF6A8(void) {
    PartyMember* src;
    SVECTOR      pos;
    SVECTOR      rot;
    MATRIX       matrix;
    long         flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = ((g_Task->timer & 0x1F) - 2) << 7;
    src    = (PartyMember*)g_BattleEffectBattler;
    pos.vx = (src->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (src->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -(COORD_INT(src->pos.z) + 0x200) / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

/* func_801EF774 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF7B8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 3), 2, g_Task);
}

INCLUDE_ASM(func_801EF7FC);

INCLUDE_ASM(func_801EF8C0);

INCLUDE_ASM(func_801EFA80);

MATCH void func_801EFDD8(void) {
    SYS_DISPATCH_BYTE(D_801F1230, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F093C();
        func_801F04D4(g_Task->param.unk_0B);
        func_801F0004();
    }
}

INCLUDE_ASM(func_801EFE70);

/* func_801EFF1C */
MATCH void BMagic_ApplyDamageFlags(void) {
    s32 value;

    g_Task->unk_20 -= 5;
    if (g_Task->unk_14 == 0x30) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
    }
    value          = g_Task->unk_14 + 2;
    g_Task->unk_14 = value;
    if (value == 0xC0) {
        g_Task->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFFB0(void) {
    PartyMember* work  = g_Task;
    u8           timer = work->unk_09 - 1;
    work->unk_09       = timer;
    work->unk_20 -= 5;
    work->unk_14 += 2;
    if (timer == 0) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F0004);

INCLUDE_ASM(func_801F04D4);

INCLUDE_ASM(func_801F093C);

MATCH void func_801F0D08(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F1230 + 3, g_Task->header.step);
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

MATCH void func_801F0D6C(void) {
    PartyMember* work;

    g_Task->unk_25    = 0x1D;
    g_Task->unk_26    = 0;
    g_Task->unk_27    = 0x1A;
    g_Task->unk_28    = 1;
    g_Task->unk_2A    = (g_Task->facing - 0x1) & 1;
    g_Task->unk_29    = 4;
    g_Task->unk_24    = 0;
    work              = g_Task;
    work->unk_2B      = 0;
    work->unk_2C.half = 0;
    g_Task->unk_09    = 0;
    g_Task->header.step += 1;
    Actor_SelectScript(0);
    func_8014D290();
}

MATCH void func_801F0E4C(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        func_801E5988();
        return;
    }
    func_8014D290();
}

INCLUDE_ASM(func_801F0E90);

INCLUDE_ASM(func_801F0FBC);
