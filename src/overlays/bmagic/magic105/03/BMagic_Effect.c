#include "magic105_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC14);

INCLUDE_ASM(func_801EED1C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEF78(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEFBC(void) {
    MagicTaskFuncs handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 3) {
        func_801EF2F0();
        func_801EF3A0();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF06C);

INCLUDE_ASM(func_801EF124);

MATCH void func_801EF250(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 64) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801EF2F0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    pos.vx = (g_SpadWork->coord_x_34.raw >> 9) - 0x4000;
    pos.vy = (g_SpadWork->coord_y_38.raw >> 9) - 0x4000;
    pos.vz = -g_SpadWork->word_3C.half.span_3E / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF3A0);

MATCH void func_801EF880(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 11), 1, g_SpadWork);
}

MATCH void func_801EF8C4(void) {
    g_ScriptBank = 0x800C3800u;
    SYS_DISPATCH_BYTE(D_801F0078, g_SpadWork->unk_02);
    func_800AF764();
    g_ScriptBank = AREA_SCRIPT_BANK;
}

INCLUDE_ASM(func_801EF930);

MATCH void func_801EFB68(void) {
    g_SpadWork->word_08.byte.timer_0A += 1;
    g_SpadWork->coord_x_34.raw += (s32)(rsin((g_SpadWork->word_08.byte.timer_0A & 0x3F) << 8) * 8) >> 3;
    g_SpadWork->coord_y_38.raw += (s32)(rcos((g_SpadWork->word_08.byte.timer_0A & 0x3F) << 8) * 8) >> 3;
    g_SpadWork->word_3C.half.span_3E = (u16)g_SpadWork->word_3C.half.span_3E - 8;
    if ((func_8014DAEC() & 0xFF) || (g_SpadWork->word_3C.half.span_3E < g_SpadWork->unk_14)) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        g_SpadWork->flags_00 = 0;
        g_SpadWork->step_01  = 0;
        g_SpadWork->unk_02   = 0;
    }
}

/* func_801EFC8C */
#include "overlays/bmagic/BMagic_AllocEffect.h"

INCLUDE_ASM(func_801EFCF0);
