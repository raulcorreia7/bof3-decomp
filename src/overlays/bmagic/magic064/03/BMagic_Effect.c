#include "magic064_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC7C */
#include "overlays/bmagic/BMagic_RunStep.h"

MATCH void func_801EECDC(void) {
    g_SpadWork->step_01 += 1;
}

MATCH void func_801EECFC(void) {
    BMagic064Steps steps;

    steps = D_801EEC10;
    steps.handlers[g_SpadWork->unk_02]();
}

INCLUDE_ASM(func_801EED7C);

MATCH void func_801EEE1C(void) {
    PartyBattler* battler;

    battler    = g_SpadWork;
    g_SpadWork = &g_BattlePartyBattlers[g_BattleActingBattler];
    if (!(func_8014DAEC() & 0xFF)) {
        g_SpadWork                   = battler;
        battler->word_08.byte.unk_09 = 0x10;
        return;
    }
    g_SpadWork = battler;
    battler->unk_02 += 1;
}

INCLUDE_ASM(func_801EEEA8);

INCLUDE_ASM(func_801EEFF8);

MATCH void func_801EF0D8(void) {
}

INCLUDE_ASM(func_801EF0E0);

INCLUDE_ASM(func_801EF20C);

MATCH void func_801EF29C(void) {
}

MATCH void func_801EF2A4(void) {
    PartyBattler* battler;
    u32           value;

    battler    = g_SpadWork;
    g_SpadWork = &g_BattlePartyBattlers[g_BattleActingBattler];
    func_801F0EEC(1, 2, (0x80 - battler->word_08.byte.unk_09) & 0xFF);
    func_801F0EEC(0, 1, (0x80 - battler->word_08.byte.unk_09) & 0xFF);
    func_801F0EEC(3, 2, battler->word_08.byte.unk_09);
    func_801F0EEC(2, 1, battler->word_08.byte.unk_09);
    g_SpadWork = battler;
    if (D_801EB4E0->unk_2C.half == 0) {
        value = 0x242;
        if ((u8)D_801EB4E0->word_08.byte.unk_08 < 2U) {
            value = 0x240;
        }
    } else {
        value = 0x243;
        if ((u8)D_801EB4E0->word_08.byte.unk_08 < 2U) {
            value = 0x241;
        }
    }
    EMI_LoaderStreamInitSlot(value);
    g_SpadWork->unk_02 += 1;
}

INCLUDE_ASM(func_801EF3C8);

MATCH void func_801EF570(void) {
    PartyBattler* battler;

    battler    = g_SpadWork;
    g_SpadWork = &g_BattlePartyBattlers[g_BattleActingBattler];
    if (!(func_8014DAEC() & 0xFF)) {
        g_SpadWork = battler;
        return;
    }
    g_SpadWork = battler;
    battler->unk_02 += 1;
}

INCLUDE_ASM(func_801EF5FC);

INCLUDE_ASM(func_801EF69C);

MATCH void func_801EF78C(void) {
    BattleResultRings table;

    table = D_801EEC40;
    SYS_DISPATCH_TASK(table.handlers, 1, g_SpadWork);
}

MATCH void func_801EF7F8(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC50;
    handlers.handlers[g_SpadWork->unk_02]();
    if (g_SpadWork->flags_00) {
        func_8014D290();
    }
}

MATCH void func_801EF87C(void) {
    g_SpadWork->unk_02 += 1;
}

MATCH void func_801EF89C(void) {
    Callback table[2] = {func_801EF8F4, func_801F001C};

    table[SP_REF(u8*, 0x44)[3]]();
}

INCLUDE_ASM(func_801EF8F4);

INCLUDE_ASM(func_801F001C);

MATCH void func_801F007C(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801F009C);

MATCH void func_801F01C4(void) {
    g_SpadWork->word_08.byte.unk_0B = 0;
    g_SpadWork->word_08.byte.unk_09 = 64;
    func_801F03D8();
    g_SpadWork->unk_02++;
}

MATCH void func_801F0214(void) {
    u8 timer;

    func_801F03D8();
    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801F0278);

INCLUDE_ASM(func_801F0310);

INCLUDE_ASM(func_801F0364);

INCLUDE_ASM(func_801F03D8);

MATCH void func_801F0448(void) {
    Callback table[2] = {func_801F04A0, func_801F05A4};

    table[((u8*)D_801F28B4)[1]]();
}

INCLUDE_ASM(func_801F04A0);

INCLUDE_ASM(func_801F05A4);

INCLUDE_ASM(func_801F0B8C);

MATCH void func_801F0C38(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC70;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        func_8014D290();
    }
}

INCLUDE_ASM(func_801F0CBC);

MATCH void func_801F0D14(void) {
    g_SpadWork->unk_02 += 1;
}

MATCH void func_801F0D34(void) {
    GFX_FreePaletteFadeTarget(g_SpadWork);
    func_801E5988();
}

MATCH void func_801F0D64(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectFuncs, 2, g_SpadWork);
}

#include "overlays/bmagic/Effect_ClearTimerNextStep.h"

MATCH void func_801F0DD8(void) {
    PartyBattler* work;
    s8            counter;

    work                      = g_SpadWork;
    counter                   = work->word_08.byte.unk_09 - 1;
    work->word_08.byte.unk_09 = counter;
    if (counter == -6) {
        g_SpadWork->unk_02++;
    }
    Area_UpdatePaletteTint((s8)g_SpadWork->word_08.byte.unk_09);
}

MATCH void func_801F0E50(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->unk_02 == 10) {
        work         = SP_REF(PartyBattler*, 0x44u);
        work->unk_02 = work->unk_02 + 1;
    }
}

MATCH void func_801F0E90(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->word_08.byte.unk_09++;
    if (work->word_08.byte.unk_09 == 0) {
        func_801E5988();
    }
    Area_UpdatePaletteTint((s8)g_SpadWork->word_08.byte.unk_09);
}

INCLUDE_ASM(func_801F0EEC);

INCLUDE_ASM(func_801F103C);

/* Report the map cell the projected point lands on: out[0] and out[1] receive
 * the cell, or zero when the probe leaves the map or hits an empty cell. */
MATCH void func_801F12B8(s32 px, s32 py, u8* out) {
    u8* buffer;
    s32 width;
    s32 x2;
    s32 x;
    s32 y;
    u16 value;

    x = g_AreaTileOriginX + (px + 1) / 2 + py;
    y = g_AreaTileOriginY + px / 2 - py;

    if (x > 0) {
        buffer = MEM_PTR(u8, 0x80104000u); /* the map bundle, include/world/area.h */
        width  = buffer[0];
        if (x < width - 1) {
            if (y > 0) {
                if (y < D_80104001 - 1) {
                    value = *(u16*)(buffer + ((D_80104002 * 4) + (x2 = x * 2) + (y * width * 2)));
                    if (value != 0) {
                        out[0] = x;
                        out[1] = y;
                        return;
                    }
                }
            }
        }
    }
    out[0] = 0;
    out[1] = 0;
}
