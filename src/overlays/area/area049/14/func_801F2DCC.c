#include "area049_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2DCC(void) {
    PartyMember* saved;
    PartyMember* record;
    u32          index;
    s32          i;
    u8           bounds;
    u8           kind;
    u16          one;
    u8*          flags;

    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE && g_GameAreaId != g_GameContextSeed) {
        func_801F2C80();
        return;
    }

    g_GameFlags &= 0xDFFF;
    saved = (PartyMember*)g_Task;
    i     = 0;
    if (g_PartySize != 0) {
        do {
            flags = &g_Scenario2Flags[0x38];
            /* FAKE: the loop pass gives retail's BIT mask constant a saved register; pure C re-loads 1 in each block. */
            FAKE_HOLD(one, 1);
            index       = i & 0xFF;
            record      = &g_Game.members[index];
            g_GameState = record;
            TASK_SET(record);
            if (SYS_TestFlag(flags, 0x25) != 0 || SYS_TestFlag(&g_Scenario2Flags[0x18], 0x3A) != 0 || (bounds = func_801F2D00((u8)index)) == 0xFF) {
                if (((saved->param.unk_0B >> index) & 1) != 0) {
                    saved->param.unk_0B &= ~(one << index);
                    g_AreaWalkFlags &= ~(one << index);
                }
                goto next_record;
            }
            if (((saved->param.unk_0B >> index) & 1) == 0) {
                if ((((g_GameFlags | g_AreaWalkFlags) >> index) & 1) != 0) {
                    goto next_record;
                }
                g_GameState->u.field.counter_11C.u8_value = 2;
                ((PartyMember*)g_Task)->unk_09            = 0;
                saved->param.unk_0B |= (one << index);
                g_AreaWalkFlags |= (one << index);
                ((PartyMember*)g_Task)->facing = D_801F5C0C[bounds * 6];
                if (SYS_TestFlag(&g_Scenario2Flags[0x90], D_801F5C0D[bounds * 6]) != 0) {
                    ((PartyMember*)g_Task)->facing ^= 4;
                }
                Actor_RequestScript(((PartyMember*)g_Task)->facing);
                goto next_record;
            }
            if (((PartyMember*)g_Task)->unk_09 == 0) {
                func_801C2538();
                if (index == 0) {
                    func_801C2710();
                }
            } else {
                kind = D_801F5C08[bounds * 6 + 4];
                if (SYS_TestFlag(&g_Scenario2Flags[0x90], D_801F5C0D[bounds * 6]) != 0) {
                    kind ^= 4;
                }
                if (((PartyMember*)g_Task)->facing != kind) {
                    ((PartyMember*)g_Task)->facing = kind;
                    ((PartyMember*)g_Task)->unk_0C = -((PartyMember*)g_Task)->unk_0C;
                    ((PartyMember*)g_Task)->unk_10 = -((PartyMember*)g_Task)->unk_10;
                    ((PartyMember*)g_Task)->unk_14 = -((PartyMember*)g_Task)->unk_14;
                    ((PartyMember*)g_Task)->unk_09 = 8 - ((PartyMember*)g_Task)->unk_09;
                }
            }
            func_801B0DFC();
            ((PartyMember*)g_Task)->unk_09--;
            Actor_StepAnimLoop();
            g_GameFlags |= 0x2000;
        next_record:
            i++;
        } while ((u32)(i & 0xFF) < g_PartySize);
    }

    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        g_GameFlags &= 0xDFFF;
    }

    TASK_SET(saved);
}
#else
INCLUDE_ASM(func_801F2DCC);
#endif
