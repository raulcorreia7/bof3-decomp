#include "magic064_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC7C */
#include "overlays/bmagic/BMagic_RunStep.h"

MATCH void func_801EECDC(void) {
    g_Task->header.mode += 1;
}

MATCH void func_801EECFC(void) {
    BMagic064Steps steps;

    steps = D_801EEC10;
    steps.handlers[g_Task->header.step]();
}

MATCH void func_801EED7C(void) {
    PartyBattler* saved;
    PartyBattler* battler;

    saved   = g_Task;
    battler = &g_BattlePartyBattlers[g_BattleActiveBattler];
    g_Task  = battler;
    Actor_RequestScript((battler->facing + 0x38) & BYTE_MASK);
    g_Task = saved;
    SND_PlayCue(0x100U);
    g_Task->param.unk_0B = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EEE1C(void) {
    PartyBattler* battler;

    battler = g_Task;
    g_Task  = &g_BattlePartyBattlers[g_BattleActiveBattler];
    if (!(func_8014DAEC() & 0xFF)) {
        g_Task          = battler;
        battler->unk_09 = 0x10;
        return;
    }
    g_Task = battler;
    battler->header.step += 1;
}

INCLUDE_ASM(func_801EEEA8);

INCLUDE_ASM(func_801EEFF8);

MATCH void func_801EF0D8(void) {
}

INCLUDE_ASM(func_801EF0E0);

MATCH void func_801EF20C(void) {
    u8 temp_v0;

    temp_v0 = g_Task->unk_09;
    if (temp_v0 != 0) {
        g_Task->unk_09 = temp_v0 - 1;
        return;
    }
    GFX_FreePaletteFadeTarget(g_BattleEffectBattler);
    g_BattleEffectBattler->header.flags |= PARTY_BATTLER_FLAG_HANDLER_BUSY;
    g_Task->unk_09 = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF29C(void) {
}

MATCH void func_801EF2A4(void) {
    PartyBattler* battler;
    u32           value;

    battler = g_Task;
    g_Task  = &g_BattlePartyBattlers[g_BattleActiveBattler];
    func_801F0EEC(1, 2, (0x80 - battler->unk_09) & 0xFF);
    func_801F0EEC(0, 1, (0x80 - battler->unk_09) & 0xFF);
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
    EMI_LoaderStreamInitSlot(value);
    g_Task->header.step += 1;
}

/* hint: with u8* active = &g_BattleActiveBattler and party = g_BattlePartyBattlers every instruction matches except retail's li a1,2 after the s2 address setup (2 slots late) at +0x8. */
INCLUDE_ASM(func_801EF3C8);

MATCH void func_801EF570(void) {
    PartyBattler* battler;

    battler = g_Task;
    g_Task  = &g_BattlePartyBattlers[g_BattleActiveBattler];
    if (!(func_8014DAEC() & 0xFF)) {
        g_Task = battler;
        return;
    }
    g_Task = battler;
    battler->header.step += 1;
}

MATCH void func_801EF5FC(void) {
    PartyBattler* work;

    work = g_Task;
    if (!(work->param.unk_0B & 1)) {
        g_AreaScrollTargetX = work->pos.x.fixed;
        MATCH_FAKE_BARRIER(); /* FAKE: retail reads each field after storing the previous target */
        g_AreaScrollTargetY = work->pos.y.fixed;
        MATCH_FAKE_BARRIER();
        g_AreaCameraHeight = COORD_INT(work->pos.z);
        func_801F103C();
        g_Task->unk_09      = 0x40;
        g_Task->timer       = 1;
        g_Task->header.mode = 2;
        g_Task->header.step = 0;
    }
}

INCLUDE_ASM(func_801EF69C);

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

    table[TASK_BYTES[3]]();
}

INCLUDE_ASM(func_801EF8F4);

MATCH void func_801F001C(void) {
    func_8014DAEC();
    g_BattleEffectBattler->header.step += 1;
    g_Task->header.step += 1;
    g_Task->unk_03 = 0;
}

MATCH void func_801F007C(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801F009C);

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
    if (!(g_FrameCount & 1)) {
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

/* blocker: a 0x1C-stride record table (D_801F13B4, flags byte at 0, 0xC0 rows) has no record type in this image; needs: type. */
INCLUDE_ASM(func_801F0364);

/* blocker: the loop keeps the constants 1 and 6 in registers; first diff: addiu a3 against the table address at 0x801F03E0. */
INCLUDE_ASM(func_801F03D8);

MATCH void func_801F0448(void) {
    Callback table[2] = {func_801F04A0, func_801F05A4};

    table[((u8*)D_801F28B4)[1]]();
}

INCLUDE_ASM(func_801F04A0);

INCLUDE_ASM(func_801F05A4);

INCLUDE_ASM(func_801F0B8C);

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
    } while (!(func_8014DAEC() & 0xFF));
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
    PartyBattler* work;
    s8            counter;

    work         = g_Task;
    counter      = work->unk_09 - 1;
    work->unk_09 = counter;
    if (counter == -6) {
        g_Task->header.step++;
    }
    Area_UpdatePaletteTint((s8)g_Task->unk_09);
}

MATCH void func_801F0E50(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->header.step == 10) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801F0E90(void) {
    PartyBattler* work;

    work = g_Task;
    work->unk_09++;
    if (work->unk_09 == 0) {
        func_801E5988();
    }
    Area_UpdatePaletteTint((s8)g_Task->unk_09);
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
