#include "battle_03.h"

/* nonmatching unmeasured: tried the first-draft body with the volatile D_80145AC2 view and one-member struct views for the
 * pad rows (62.12%). residual: retail keeps s5/s6 live across the draw calls (frame 0x30 against our 0x28) and the
 * body is 20 bytes short. resume: a source shape whose pad cursor and state base stay live across the calls. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D1E8C(void) {
    PartyBattler* temp_v0_66;
    u8*           state;
    u16*          pad;
    s32           temp_v1_80;
    s32           var_s0;
    s32           var_s1;
    s32           var_v0_199;
    s32           var_v0_210;
    s8            temp_a0_239;
    s8            temp_v0_50;
    u16*          var_s5;
    u16           temp_v1_206;
    u8*           var_s2;
    u8*           var_s3;
    u8*           var_s4;
    u8*           var_s6;
    u8            var_v0_215;

    state = &g_BattleRowCursor;
    pad   = &g_InputPressed;
    if (*state != 0) {
        --*state;
    }
    if ((D_80145AC4 & *pad) && ((s8)g_BattleCommandCount != 0)) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        temp_v0_50           = (u8)g_BattleCommandCount - 1;
        g_BattleCommandCount = temp_v0_50;
        g_BattleStep -= 1;
        temp_v0_66              = &g_BattlePartyBattlers[D_801462F6[temp_v0_50]];
        g_BattleMessageSlot     = &temp_v0_66->header.flags;
        temp_v0_66->header.mode = 2;
        temp_v0_66->action_flags.value &= ~4;
        if (FIELD(u8, g_BattleMessageSlot, 0x119u) == 5) {
            temp_v1_80 = FIELD(s32, g_BattleMessageSlot, 0x124u);
            if (!(temp_v1_80 & 0x4000)) {
                func_801DDE7C((u32)FIELD(u8, g_BattleMessageSlot, 0x122u),
                              (u32)FIELD(u16, g_BattleMessageSlot, 0x11Au));
            } else {
                FIELD(s32, g_BattleMessageSlot, 0x124u) = (s32)(temp_v1_80 & ~0x4000);
            }
        }
        FIELD(s32, g_BattleMessageSlot, 0x124u) = 0;
        FIELD(u8, g_BattleMessageSlot, 0x119u)  = 0U;
        return;
    }
    if (D_80145AC2 & *pad) {
        if (((u32)(g_BattlePanelSlot - 2) < 2U) && (FIELD(s32, D_801EB4D8, 0x10u) & 2)) {
            SND_PlayCue(EMI_CUE_ID(1, 7));
            return;
        }
        SND_PlayCue(EMI_CUE_ID(1, 4));
        D_8014839F          = 2;
        *(u8*)(&D_8014837B) = 2;
        g_BattleStep += 2;
        g_BattleSubStep = g_BattlePanelSlot;
        return;
    }
    if (g_InputHeld & PADselect) {
        SND_PlayCue(EMI_CUE_ID(1, 4));
        *(u8*)(&D_8014837B) = 2;
        D_80148357          = 2;
        D_8014839F          = 2;
        func_801D7A40(D_8014837C, D_8014837E);
        func_801D8450((u32)g_BattlePanelSlot);
        func_801D750C((s32)D_80148358, (s32)D_8014835A);
        g_BattleStep += 1;
        return;
    }
    var_s0 = 5;
    if (g_InputHeld & (INPUT_DIRECTIONAL | PADL1 | PADR1)) {
        var_s5     = pad - 4;
        var_s6     = &D_8014837B;
        var_s6     = &D_8014837B;
        var_s3     = &g_BattlePanelEntry;
        var_s3     = &g_BattlePanelEntry;
        var_s2     = &g_BattlePanelEntry - 5;
        var_s4     = &g_BattlePanelEntry - 1;
        var_v0_199 = 5 << 0x18;
    loop_18:
        var_s1      = var_v0_199 >> 0x18;
        temp_v1_206 = *(&D_801EABCC + (var_s1 * 2));
        var_v0_210  = var_s0 - 1;
        if (temp_v1_206 & var_s5[2]) {
            var_v0_215 = var_s0 + 1;
            if (temp_v1_206 & FIELD(u16, var_s5, 0x4u)) {
                SND_PlayCue(EMI_CUE_ID(1, 1));
                if (*(u8*)(&g_BattlePanelEntry) == (var_s1 + 1)) {
                    if (*(u8*)((u8*)(&g_BattlePanelEntry) + -1) != 0) {
                        if (((u32)((var_s0 - 1) & BYTE_MASK) >= 2U) || !(FIELD(s32, D_801EB4D8, 0x10u) & 2)) {
                            temp_a0_239                                    = var_s0 + 1;
                            FIELD(s8, (&D_8014837B), 0x24u)                = 2;
                            *(u8*)(&D_8014837B)                            = 2;
                            FIELD(s8, (&(&g_BattlePanelEntry)[-5]), 0x13u) = temp_a0_239;
                            FIELD(s8, (&(&g_BattlePanelEntry)[-5]), 0x1u)  = temp_a0_239;
                            FIELD(s8, (&(&g_BattlePanelEntry)[-5]), 0x4u)  = 0;
                            FIELD(s8, (&(&g_BattlePanelEntry)[-5]), 0x5u)  = 0;
                            *(u8*)((u8*)(&g_BattlePanelEntry) + -5) = (u8)(*(u8*)((u8*)(&g_BattlePanelEntry) + -5) + 2);
                            return;
                        }
                        *(u8*)((u8*)(&g_BattlePanelEntry) + -1) = 0U;
                        *(u8*)(&g_BattlePanelEntry)             = 0;
                        return;
                    }
                    goto block_26;
                }
            block_26:
                *(u8*)((u8*)(&g_BattlePanelEntry) + -1) = 8U;
                *(u8*)(&g_BattlePanelEntry)             = var_s0 + 1;
                var_v0_215                              = var_s0 + 1;
                goto block_27;
            }
        block_27:
            g_BattlePanelSlot = var_v0_215;
            var_v0_210        = var_s0 - 1;
            goto block_28;
        }
    block_28:
        var_s0     = var_v0_210;
        var_v0_199 = var_s0 << 0x18;
        if (var_v0_210 & 0x80) {
            return;
        }
        goto loop_18;
    }
    if (g_BattlePanelSlot != 0) {
        g_BattlePanelSlot = 0;
    }
}
#else
INCLUDE_ASM(func_801D1E8C);
#endif
