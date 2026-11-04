#include "game_00.h"

MATCH void func_801B0568(void) {
    s32    tmp0;
    s32    val0;
    s32    tmp1;
    s32    tmp2;
    u8     tmp3;
    s32    tmp10;
    u8     tmp4;
    Actor* tmp5;
    Actor* tmp6;
    Actor* tmp7;
    Actor* tmp8;
    Actor* tmp9;

    if (!GAME_SCRIPT_ACTIVE() && !(g_AreaWalkFlags & AREA_WALK_ENTRY_PENDING) && !(func_801B6258() & BYTE_MASK) &&
        !(func_801B5684() & BYTE_MASK) && !(func_801B5758() & BYTE_MASK) && !(func_801B5EBC() & BYTE_MASK) &&
        !(func_801B5884() & BYTE_MASK) && !(func_801B5910() & BYTE_MASK)) {
        tmp9 = g_SpadWork;
        tmp4 = tmp9->unk_0A;
        if (tmp4 != 0) {
            tmp9->unk_0A = (u8)(tmp4 - 1);
            return;
        }
        if (!(func_801B59B4() & BYTE_MASK)) {
            func_801B5BDC(g_SpadWork->direction_08);
            g_GameState->counter_11C.u8_value = 3U;
            g_GameState->mode_12B.s8_value    = 0;
            Actor_ClearVelocity();
            g_SpadWork->option_flags = 0;
            g_SpadWork->unk_09       = 0U;
            g_SpadWork->unk_0B       = 0;
            g_AreaCameraStep         = 0;
            g_AreaCameraHeightStep   = 0;
            g_SpadWork->state_02     = 0;
            return;
        }
        tmp0 = func_801B0E44() & BYTE_MASK;
        if (tmp0 == 3) {
            goto case_3; /* retail branch layout: the case bodies sit after the compare chain */
        }
        if (tmp0 < 4) {
            if (tmp0 == 1) {
                goto case_1; /* retail branch layout: the case bodies sit after the compare chain */
            }
            if (tmp0 >= 2) {
                goto case_2; /* retail branch layout: the case bodies sit after the compare chain */
            }
            if (tmp0 == 0) {
                goto case_0; /* retail branch layout: the case bodies sit after the compare chain */
            }
            return;
        }
        if (tmp0 == 5) {
            goto case_5; /* retail branch layout: the case bodies sit after the compare chain */
        }
        if (tmp0 < 5) {
            return;
        }
        if (tmp0 == 6) {
            goto case_6; /* retail branch layout: the case bodies sit after the compare chain */
        }
        if (tmp0 == GAME_NONE) {
            goto case_255; /* retail branch layout: the case bodies sit after the compare chain */
        }
        return;
        {
        case_0:
            if ((func_801BDF08() << 0x18) != 0) {
                g_GameState->mode_12B.s8_value = 0;
                func_801B5BDC(g_SpadWork->direction_08);
                goto block_35; /* shares the state-1 tail */
            }
            g_SpadWork->unk_0B = 0;
            func_801B0C88();
            func_801C24D0();
            func_801C4C48();
            g_SpadWork->unk_0B = 0;
            if (g_GameRequestFlags & 1) {
                if (g_AreaWalkFlags & (AREA_WALK_TRANSITION | 0x2000)) {
                    tmp5         = g_SpadWork;
                    tmp1         = tmp5->unk_09;
                    tmp2         = tmp5->x.fixed + (tmp5->unk_0C * tmp1);
                    tmp10        = tmp5->y.fixed + (tmp5->unk_10 * tmp1);
                    tmp5->unk_06 = (u8)(tmp5->unk_06 - 1);
                    if ((g_SpadWork->unk_06 == 0) ||
                        (Area_GetCellCode((s16)((s32)tmp2 >> 0x10), (s16)((s32)tmp10 >> 0x10)) & BYTE_MASK)) {
                        D_80143F22 = 0;
                        g_AreaWalkFlags &= ~(AREA_WALK_TRANSITION | 0x2000);
                        Area_RollEncounterThreshold(0U);
                    }
                } else if (Area_CanStartEncounter() & BYTE_MASK) {
                    func_801B6418();
                    g_GameEntryPosX    = 0x190000;
                    g_GameEntryPosY    = 0x190000;
                    g_GameContextKind  = 4;
                    g_SpadWork->unk_06 = 4U;
                    g_AreaWalkFlags |= AREA_WALK_TRANSITION;
                }
            }
            func_801B5BDC((g_SpadWork->direction_08 + 8) & BYTE_MASK);
            tmp6         = g_SpadWork;
            tmp6->unk_09 = (u8)(tmp6->unk_09 - 1);
            func_801B0DFC();
            g_GameState->mode_12B.s8_value = 1;
            g_SpadWork->state_02           = 2;
            return;
        case_1:
            if (func_801B5F68(g_GameState->counter_11C.u8_value) & BYTE_MASK) {
                return;
            }
            g_GameState->mode_12B.s8_value    = 0;
            g_GameState->counter_11C.u8_value = 3U;
            g_SpadWork->unk_09                = 0U;
            func_801B5BDC(g_SpadWork->direction_08);
            g_GameState->mode_12B.s8_value = 0;
        block_35:
            g_SpadWork->state_02 = 1;
            func_801B6044();
            return;
        case_2:
            g_GameState->counter_11C.u8_value = 3U;
            Actor_RequestScript(g_SpadWork->direction_08);
            g_SpadWork->unk_01   = 2;
            g_SpadWork->state_02 = 4;
            tmp7                 = g_SpadWork;
            tmp2                 = tmp7->direction_08;
            if ((tmp2 == 1) || (tmp2 == 7)) {
                tmp7->unk_03 = 0;
            } else {
                tmp7->unk_03 = 1;
            }
            g_GameState->mode_12B.s8_value  = 3;
            g_GameState->flags_12C.u8_value = (u8)(g_GameState->flags_12C.u8_value | 2);
            g_AreaWalkFlags |= 0x80;
            return;
        case_3:
            val0                              = 2;
            g_GameState->counter_11C.u8_value = 2U;
            Actor_RequestScript(g_SpadWork->direction_08);
            g_SpadWork->unk_01              = 2;
            g_SpadWork->state_02            = 5;
            g_GameState->mode_12B.s8_value  = 2;
            g_GameState->flags_12C.u8_value = (u8)(g_GameState->flags_12C.u8_value | 2);
            g_AreaWalkFlags |= 0x100;
            return;
        case_5:
            val0                              = 3;
            g_GameState->counter_11C.u8_value = 3U;
            Actor_RequestScript(g_SpadWork->direction_08);
            g_GameState->mode_12B.s8_value = 4;
            g_SpadWork->unk_01             = 2;
            g_SpadWork->state_02           = 3;
            return;
        case_6:
            val0                              = 3;
            g_GameState->counter_11C.u8_value = 3U;
            Actor_RequestScript(g_SpadWork->direction_08);
            g_GameState->mode_12B.s8_value = 3;
            g_SpadWork->unk_01             = 8;
            tmp8                           = g_SpadWork;
            tmp3                           = tmp8->direction_08;
            if ((tmp3 == 1) || (tmp3 == 7)) {
                tmp8->state_02 = 0;
                return;
            }
            tmp8->state_02 = 1;
            return;
        case_255:
            g_GameState->mode_12B.s8_value    = 0;
            g_GameState->counter_11C.u8_value = 3U;
            g_SpadWork->unk_09                = 0U;
            g_SpadWork->unk_0B                = 0;
            func_801B5BDC(g_SpadWork->direction_08);
            g_GameState->mode_12B.s8_value = 0;
            return;
        }
    }
}
