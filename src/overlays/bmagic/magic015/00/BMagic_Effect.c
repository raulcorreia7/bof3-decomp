#include "magic015_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EECA0(void) {
    BattleResultRings table = D_801EEC04;

    SYS_DISPATCH_TASK(table.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EED0C);

MATCH void func_801EF150(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_800AFC54();
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;
        g_SpadWork->step_01 += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EF248(void) {
    BattleResultRings table = D_801EEC14;

    SYS_DISPATCH_TASK(table.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EF2B4);

MATCH void func_801EF594(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_800AFC54();
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;
        g_SpadWork->step_01 += 1;
    }
}

MATCH void Effect_StartPlaying_801EF610(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EF644(void) {
    BattleResultRings table = D_801EEC24;

    SYS_DISPATCH_TASK(table.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EF6B0);

MATCH void func_801EF93C(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_800AFC54();
        BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;
        func_800AEF98(4, 0);
        g_SpadWork->step_01 += 1;
    }
}

MATCH void Effect_StartPlaying_801EF9B0(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EF9E4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EFA28);

INCLUDE_ASM(func_801EFAE4);

MATCH void func_801EFB90(void) {
    if ((func_8014DAEC() & BYTE_MASK) != 0u) {
        g_SpadWork->unk_02 += 1u;
    }
}

INCLUDE_ASM(func_801EFBD8);

INCLUDE_ASM(func_801EFCC4);

INCLUDE_ASM(func_801EFD7C);

INCLUDE_ASM(func_801EFDE8);

INCLUDE_ASM(func_801EFE84);

MATCH void func_801EFEFC(void) {
    func_801E5988();
}

MATCH void func_801EFF1C(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC54;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_8014D290();
    }
}

INCLUDE_ASM(func_801EFFC0);

MATCH void func_801F014C(void) {
    if ((func_8014DAEC() & BYTE_MASK) != 0u) {
        g_SpadWork->unk_02 += 1u;
    }
}

INCLUDE_ASM(func_801F0194);

INCLUDE_ASM(func_801F0248);

#include "overlays/bmagic/Effect_TickDownAndClear.h"

INCLUDE_ASM(func_801F0334);

INCLUDE_ASM(func_801F045C);

INCLUDE_ASM(func_801F0570);

INCLUDE_ASM(func_801F0654);

INCLUDE_ASM(func_801F0770);

INCLUDE_ASM(func_801F0864);

INCLUDE_ASM(func_801F0A94);

MATCH void func_801F0B8C(void) {
    g_SpadWork->unk_5D += 0x10;
    g_SpadWork->unk_5E += 0x10;
    g_SpadWork->unk_5F += 0x10;
    if ((s8)g_SpadWork->unk_5D == -0x40) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F0C30);

MATCH void func_801F0D48(void) {
    g_SpadWork->unk_14                = 0x80;
    g_SpadWork->unk_20                = -0x10;
    g_SpadWork->unk_27                = BATTLE_ACTIVE_WORK->unk_27;
    g_SpadWork->word_08.byte.unk_09   = 0x14;
    g_SpadWork->word_08.byte.timer_0A = 7;
    g_SpadWork->unk_02 += 1;
}

INCLUDE_ASM(func_801F0DB4);

INCLUDE_ASM(func_801F0E54);

INCLUDE_ASM(func_801F0F2C);

INCLUDE_ASM(func_801F1088);

INCLUDE_ASM(func_801F1180);

MATCH void func_801F1230(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801F1250);

MATCH void func_801F131C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_BattleSelectedActor);
}

INCLUDE_ASM(func_801F13D4);
